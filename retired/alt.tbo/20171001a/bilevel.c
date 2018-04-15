/*
	Developed by Daniel Pelikan 2013,2014
	http://digibird1.wordpress.com/
	Reviewed by @kelu124
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/time.h>
#include <linux/io.h>
#include <linux/vmalloc.h>
#include <linux/delay.h>
#include <linux/fcntl.h> /*Helps fix O_ACCMODE*/

#include <linux/sched.h> /*Helps fix TASK_UNINTERRUPTIBLE */

#include <linux/fs.h> /*Helps fix the struct intializer */

int __init init_module(void);
void __exit cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "hsdk"// Dev name 
#define BUF_LEN 80//Max length of device message 

//---------------------------------------------------------------------------------------------------------
//Things for the GPIO Port 

#define BCM2708_PERI_BASE       0x20000000
#define GPIO_BASE               (BCM2708_PERI_BASE + 0x200000)	// GPIO controller  
//#define BLOCK_SIZE 		(4*1024)

#define INP_GPIO(g)   *(gpio.addr + ((g)/10)) &= ~(7<<(((g)%10)*3)) 
#define OUT_GPIO(g)   *(gpio.addr + ((g)/10)) |=  (1<<(((g)%10)*3)) //001
//alternative function
#define SET_GPIO_ALT(g,a) *(gpio.addr + (((g)/10))) |= (((a)<=3?(a) + 4:(a)==4?3:2)<<(((g)%10)*3))
 
#define GPIO_SET  *(gpio.addr + 7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR  *(gpio.addr + 10) // clears bits which are 1 ignores bits which are 0
 
#define GPIO_READ(g)  *(gpio.addr + 13) &= (1<<(g))


//GPIO Clock
#define CLOCK_BASE              (BCM2708_PERI_BASE + 0x00101000)
#define GZ_CLK_BUSY (1 << 7)

//---------------------------------------------------------------------------------------------------------

//How many samples to capture
#define SAMPLE_SIZE 	5000
#define REPEAT_SIZE 	10	

//Define GPIO Pins

//ADC 1
#define BIT0_PIN 16
#define BIT1_PIN 17
#define BIT2_PIN 18
#define BIT3_PIN 19
#define BIT4_PIN 20
#define BIT5_PIN 22
#define BIT6_PIN 25
#define BIT7_PIN 26
#define BIT8_PIN 27

//ADC 2
#define BIT0_PIN2 7
#define BIT1_PIN2 8
#define BIT2_PIN2 9
#define BIT3_PIN2 10
#define BIT4_PIN2 11
#define BIT5_PIN2 12
#define BIT6_PIN2 13
#define BIT7_PIN2 14
#define BIT8_PIN2 15

// Pulser
#define PPuls_ON 23
#define NPuls_ON 24

#define Puls_OFF 21


#define PPWWMM 6

#define MY_NOP(__N)                 __asm ("nop");    // or sth like "MOV R0,R0"


//---------------------------------------------------------------------------------------------------------

// IO Acces
struct bcm2835_peripheral {
	unsigned long addr_p;
	int mem_fd;
	void *map;
	volatile unsigned int *addr;
	
};

static int map_peripheral(struct bcm2835_peripheral *p);
static void unmap_peripheral(struct bcm2835_peripheral *p);
static void readScope(void);


static int Major;		/* Major number assigned to our device driver */
static int Device_Open = 0;	/* Is device open?  
				 * Used to prevent multiple access to device */
static char msg[BUF_LEN];	/* The msg the device will give when asked */
static char *msg_Ptr;


static uint32_t *ScopeBuffer_Ptr;
static unsigned char *buf_p;


static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

//---------------------------------------------------------------------------------------------------------

/*
We need to assign the addresses of GPIO and the clock to a variable that we can find the hardware. A data structure is defined to hold our values we read out from the ADC, as well as the time from start of the readout to the end of the readout. This time is needed in order to calculate the time step between each sample. Additional two pointers are defined for later operations.
*/

static struct bcm2835_peripheral myclock = {CLOCK_BASE};

static struct bcm2835_peripheral gpio = {GPIO_BASE};


static struct DataStruct{
	uint32_t Buffer[REPEAT_SIZE*SAMPLE_SIZE];
	uint32_t time;
};

struct DataStruct dataStruct;

static unsigned char *ScopeBufferStart;
static unsigned char *ScopeBufferStop;

//---------------------------------------------------------------------------------------------------------
/*
Since we want to manipulate hardware registers we need to map the hardware registers into memory. This can be done by two functions, one for the mapping and one for the unmapping.
*/
static int map_peripheral(struct bcm2835_peripheral *p)
{
	p->addr=(uint32_t *)ioremap(GPIO_BASE, 41*4); //41 GPIO register with 32 bit (4*8)
   return 0;
}
 
static void unmap_peripheral(struct bcm2835_peripheral *p) {
 	iounmap(p->addr);//unmap the address
}


//---------------------------------------------------------------------------------------------------------
/*
 In our case we are only taking 10k samples so not too much time. Before the sample taking we take a time stamp. Then we read out 10k times the GPIO register and save it in our data structure. The GPIO register is a 32bit value so it is made out of 32 ‘1’s and ‘0’s each defining if the GPIO port is high (3.3V) or low (GND). After the read out we take another time stamp and turn on all interrupts again. The two time stamps we took are important since we can calculate how long it took to read in the 10k samples. The time difference divided by 10k gives us the time between each sample point. In case the sample frequency is too high and should be reduced one can add some delay and waste some time during each readout step. Here the aim is to achieve the maximal performance.
*/

static void readScope(){

	int counter=0;
	int counterline = 0;
	int limit = 0;

	int Pon=0;
	int Poff=0;
	//int Fail=0;

	//disable IRQ
	local_irq_disable();
	local_fiq_disable();

	struct timespec ts_start,ts_stop;
	//Start time

	set_current_state(TASK_UNINTERRUPTIBLE);
	getnstimeofday(&ts_start);



	while(counterline<REPEAT_SIZE){ 

		limit = (counterline+1)*SAMPLE_SIZE;

		printk(KERN_INFO "Shooting line %d\n", counterline);
		INP_GPIO(PPuls_ON);
		INP_GPIO(NPuls_ON);
		INP_GPIO(Puls_OFF);
		OUT_GPIO(PPuls_ON);
		OUT_GPIO(NPuls_ON);
		OUT_GPIO(Puls_OFF);

		GPIO_SET = 1 << NPuls_ON;
		while(Pon<10){ // Nb of NOPs for PulseOn
			MY_NOP(__N);
			Pon++;
		}
		GPIO_CLR = 1 << NPuls_ON;

		GPIO_SET = 1 << Puls_OFF;
		while(Poff<100){ // Nb of NOPs for PulseOff
			MY_NOP(__N);
			Poff++;
		}
		GPIO_CLR = 1 << Puls_OFF;

		Poff = 0;
		while(Poff<1400){ // Nb of NOPs for PulseOff
			MY_NOP(__N);
			Poff++;
		}

		Pon = 0;
		GPIO_SET = 1 << PPuls_ON;
		while(Pon<10){ // Nb of NOPs for PulseOn
			MY_NOP(__N);
			Pon++;
		}
		GPIO_CLR = 1 << PPuls_ON;

		Poff = 0;
		//GPIO_SET = 1 << Puls_OFF;
		while(Poff<1500){ // Nb of NOPs for PulseOff
			MY_NOP(__N);
			Poff++;
		}
		//GPIO_CLR = 1 << Puls_OFF;



		INP_GPIO(PPuls_ON);
		INP_GPIO(NPuls_ON);
		INP_GPIO(Puls_OFF);

		//take samples
		/*
		if(counterline < (REPEAT_SIZE-1) ){
			limit = counterline*(SAMPLE_SIZE+1);
		}else{
			limit = (REPEAT_SIZE)*SAMPLE_SIZE;
		}
		*/

		while(counter<(limit) ){
			dataStruct.Buffer[counter++]= *(gpio.addr + 13); 
		}
		
		// to avoid freezes
		msleep(10);

		counterline++;
	}



	//Stop time
	getnstimeofday(&ts_stop);

	set_current_state(TASK_INTERRUPTIBLE);
	//enable IRQ
	local_fiq_enable();
	local_irq_enable();

	//save the time difference
	dataStruct.time=timespec_to_ns(&ts_stop)-timespec_to_ns(&ts_start);//ns resolution

	buf_p=&dataStruct;//cound maybe removed

	ScopeBufferStart=&dataStruct;

	ScopeBufferStop=ScopeBufferStart+sizeof(struct DataStruct);
}

//---------------------------------------------------------------------------------------------------------
/*
In order to make a kernel module work the module needs some special entry functions. One of these functions is the init_module(void) which is called when the kernel module is loaded. Here the function to map the periphery is called, the GPIO pins are defined as inputs and a device file in /dev/ is created for communication with the kernel module. Additionally a 10 MHz clock signal on the GPIO Pin 4 is defined. This clock signal is needed in order to feed the ADC with an input clock. A 500 MHz signal from a PLL is used and the clock divider is set to divide by 50, which gives the required 10 MHz signal. More details on this clock can found in chapter 6.3 General Purpose GPIO Clocks in [4]. 
*/
/*
 * This function is called when the module is loaded
 */
int init_module(void)
{
    Major = register_chrdev(0, DEVICE_NAME, &fops);

	if (Major < 0) {
	  printk(KERN_ALERT "Registering char device failed with %d\n", Major);
	  return Major;
	}

	printk(KERN_INFO "I was assigned major number %d. To talk to\n", Major);
	printk(KERN_INFO "the driver, create a dev file with\n");
	printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major);
	printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n");
	printk(KERN_INFO "the device file.\n");
	printk(KERN_INFO "Remove the device file and module when done.\n");

	//Map GPIO

	if(map_peripheral(&gpio) == -1) 
	{
		printk(KERN_ALERT,"Failed to map the physical GPIO registers into the virtual memory space.\n");
		return -1;
	}

	//Define Scope pins
	// ADC1
	INP_GPIO(BIT0_PIN);
	INP_GPIO(BIT1_PIN);
	INP_GPIO(BIT2_PIN);
	INP_GPIO(BIT3_PIN);
	INP_GPIO(BIT4_PIN);
	INP_GPIO(BIT5_PIN);
	INP_GPIO(BIT6_PIN);
	INP_GPIO(BIT7_PIN);
	INP_GPIO(BIT8_PIN);

	// ADC2
	INP_GPIO(BIT0_PIN2);
	INP_GPIO(BIT1_PIN2);
	INP_GPIO(BIT2_PIN2);
	INP_GPIO(BIT3_PIN2);
	INP_GPIO(BIT4_PIN2);
	INP_GPIO(BIT5_PIN2);
	INP_GPIO(BIT6_PIN2);
	INP_GPIO(BIT7_PIN2);
	INP_GPIO(BIT8_PIN2);

	// Setting pins for pulser
	OUT_GPIO(PPuls_ON);
	OUT_GPIO(NPuls_ON);
	OUT_GPIO(Puls_OFF);

	//Set a clock signal on Pin 4
	struct bcm2835_peripheral *p=&myclock;
	p->addr=(uint32_t *)ioremap(CLOCK_BASE, 41*4);

 	INP_GPIO(4);
	SET_GPIO_ALT(4,0);

	// Preparing the clock
	int speed_id = 6; //1 for to start with 19Mhz or 6 to start with 500 MHz
	*(myclock.addr+28)=0x5A000000 | speed_id; //Turn off the clock
	while (*(myclock.addr+28) & GZ_CLK_BUSY) {}; //Wait until clock is no longer busy (BUSY flag)
	*(myclock.addr+29)= 0x5A000000 | (0x29 << 12) | 0;//Set divider //divide by 50 (0x32) -- ideally 41 (29) to fall on 12MHz clock
	*(myclock.addr+28)=0x5A000010 | speed_id;//Turn clock on

	return SUCCESS;
}
//---------------------------------------------------------------------------------------------------------
/*
 * This function is called when the module is unloaded
 */
void cleanup_module(void)
{
	unregister_chrdev(Major, DEVICE_NAME);
	unmap_peripheral(&gpio);
	unmap_peripheral(&myclock);
}
//---------------------------------------------------------------------------------------------------------
/* 
 * Called when a process tries to open the device file, like
 * "cat /dev/mycharfile"
 */
/*
Furthermore a function is needed which is called when the device file belonging to our kernel module is opened. When this happens the measurement is done by calling the readScope() function and saved in memory.
*/
static int device_open(struct inode *inode, struct file *file)
{
	static int counter = 0;

	if (Device_Open)
		return -EBUSY;

	Device_Open++;
	sprintf(msg, "I already told you %d times Hello world!\n", counter++);
	msg_Ptr = msg;

	readScope();//Read n Samples into memory

	try_module_get(THIS_MODULE);

	return SUCCESS;
}
//---------------------------------------------------------------------------------------------------------
/* 
 * Called when a process closes the device file.
 */
static int device_release(struct inode *inode, struct file *file)
{
	Device_Open--;		/* We're now ready for our next caller */
	module_put(THIS_MODULE);
	return 0;
}
//---------------------------------------------------------------------------------------------------------
/* 
 * Called when a process, which already opened the dev file, attempts to
 * read from it.
 */
static ssize_t device_read(struct file *filp,	
			   char *buffer,	
			   size_t length,
			   loff_t * offset)
{
	
	// Number of bytes actually written to the buffer 
	int bytes_read = 0;

	if (*msg_Ptr == 0)
		return 0;

	//Check that we do not overfill the buffer

	while (length && buf_p<ScopeBufferStop) {

		if(0!=put_user(*(buf_p++), buffer++))
			printk(KERN_INFO "Problem with copy\n");
		length--;
		bytes_read++;
	}

	return bytes_read;
}
//---------------------------------------------------------------------------------------------------------
/*  
 * Called when a process writes to dev file: echo "hi" > /dev/hello 
 */
static ssize_t
device_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{
	printk(KERN_ALERT "Sorry, this operation isn't supported.\n");
	return -EINVAL;
}


MODULE_AUTHOR("kelu124");
MODULE_LICENSE("GPL"); // HOLY GPL !
MODULE_VERSION("1");
