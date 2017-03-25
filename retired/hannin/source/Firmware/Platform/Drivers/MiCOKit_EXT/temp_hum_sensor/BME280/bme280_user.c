/**
******************************************************************************
* @file    bme280_user.h 
* @author  Eshen Wang
* @version V1.0.0
* @date    17-Mar-2015
* @brief     bme280 user controller. 
  operation
******************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MXCHIP Inc. SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2014 MXCHIP Inc.</center></h2>
******************************************************************************
*/ 


/*---------------------------------------------------------------------------*/
/* Includes*/
/*---------------------------------------------------------------------------*/
#include "bme280.h"
#include "bme280_user.h"
#include "MICO.h"

#define BME280_API                      // use bme280 api
#define BME280_ONE_U8X     (1)          // a uint8_t data
#define BME280_TWO_U8X     (2)          // two uint8_t data

#define BME280_TEMP_FORMAT_0_0_1      100
#define BME280_HUM_FORMAT_Q24_8       8
#define BME280_PRESS_FORMAT_Q22_10    10

#define bme280_user_log(M, ...) custom_log("BME280_USER", M, ##__VA_ARGS__)
#define bme280_user_log_trace() custom_log_trace("BME280_USER")

/* I2C device */
mico_i2c_device_t user_i2c_device = {
  BME280_I2C_DEVICE, 0x76, I2C_ADDRESS_WIDTH_7BIT, I2C_STANDARD_SPEED_MODE
};

/*----------------------------------------------------------------------------*
*  The following functions are used for reading and writing of
*	sensor data using I2C or SPI communication
*----------------------------------------------------------------------------*/
#ifdef BME280_API
/*	\Brief: The function is used as I2C bus read
 *	\Return : Status of the I2C read
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be read
 *	\param reg_data : This data read from the sensor, which is hold in an array
 *	\param cnt : The no of byte of data to be read
 */
s8 BME280_I2C_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
 /*	\Brief: The function is used as I2C bus write
 *	\Return : Status of the I2C write
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be written
 *	\param reg_data : It is a value hold in the array,
 *		will be used for write the value into the register
 *	\param cnt : The no of byte of data to be write
 */
s8 BME280_I2C_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
/*	\Brief: The function is used as SPI bus write
 *	\Return : Status of the SPI write
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be written
 *	\param reg_data : It is a value hold in the array,
 *		will be used for write the value into the register
 *	\param cnt : The no of byte of data to be write
 */
s8 BME280_SPI_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
/*	\Brief: The function is used as SPI bus read
 *	\Return : Status of the SPI read
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be read
 *	\param reg_data : This data read from the sensor, which is hold in an array
 *	\param cnt : The no of byte of data to be read */
s8 BME280_SPI_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
/*
 * \Brief: SPI/I2C init routine
*/
s8 I2C_routine(void);
s8 SPI_routine(void);
#endif
/********************End of I2C/SPI function declarations***********************/
/*	Brief : The delay routine
 *	\param : delay in ms
*/
void BME280_delay_msek(u16 msek);
/* This function is an example for reading sensor data
 *	\param: None
 *	\return: communication result
 */
s32 bme280_data_readout_template(void);
/*----------------------------------------------------------------------------*
 *  struct bme280_t parameters can be accessed by using bme280
 *	bme280_t having the following parameters
 *	Bus write function pointer: BME280_WR_FUNC_PTR
 *	Bus read function pointer: BME280_RD_FUNC_PTR
 *	Delay function pointer: delay_msec
 *	I2C address: dev_addr
 *	Chip id of the sensor: chip_id
 *---------------------------------------------------------------------------*/
struct bme280_t bme280;
/* This function is an example for reading sensor data
 *	\param: None
 *	\return: communication result
 */
s32 bme280_data_readout_template(void)
{
	/* The variable used to assign the standby time*/
	u8 v_stand_by_time_u8 = BME280_INIT_VALUE;
	/* The variable used to read uncompensated temperature*/
	s32 v_data_uncomp_tem_s32 = BME280_INIT_VALUE;
	/* The variable used to read uncompensated pressure*/
	s32 v_data_uncomp_pres_s32 = BME280_INIT_VALUE;
	/* The variable used to read uncompensated pressure*/
	s32 v_data_uncomp_hum_s32 = BME280_INIT_VALUE;
	/* The variable used to read real temperature*/
	s32 v_actual_temp_s32 = BME280_INIT_VALUE;
	/* The variable used to read real pressure*/
	u32 v_actual_press_u32 = BME280_INIT_VALUE;
	/* The variable used to read real humidity*/
	u32 v_actual_humity_u32 = BME280_INIT_VALUE;
	/* result of communication results*/
	s32 com_rslt = BME280_ERROR;



 /*********************** START INITIALIZATION ************************/
  /*	Based on the user need configure I2C or SPI interface.
  *	It is example code to explain how to use the bme280 API*/
  #ifdef BME280_API
	I2C_routine();
	/*SPI_routine(); */
	#endif
/*--------------------------------------------------------------------------*
 *  This function used to assign the value/reference of
 *	the following parameters
 *	I2C address
 *	Bus Write
 *	Bus read
 *	Chip id
*-------------------------------------------------------------------------*/
	com_rslt = bme280_init(&bme280);

	/*	For initialization it is required to set the mode of
	 *	the sensor as "NORMAL"
	 *	data acquisition/read/write is possible in this mode
	 *	by using the below API able to set the power mode as NORMAL*/
	/* Set the power mode as NORMAL*/
	com_rslt += bme280_set_power_mode(BME280_NORMAL_MODE);
	/*	For reading the pressure, humidity and temperature data it is required to
	 *	set the OSS setting of humidity, pressure and temperature
	 * The "BME280_CTRLHUM_REG_OSRSH" register sets the humidity
	 * data acquisition options of the device.
	 * changes to this registers only become effective after a write operation to
	 * "BME280_CTRLMEAS_REG" register.
	 * In the code automated reading and writing of "BME280_CTRLHUM_REG_OSRSH"
	 * register first set the "BME280_CTRLHUM_REG_OSRSH" and then read and write
	 * the "BME280_CTRLMEAS_REG" register in the function*/
	com_rslt += bme280_set_oversamp_humidity(BME280_OVERSAMP_1X);

	/* set the pressure oversampling*/
	com_rslt += bme280_set_oversamp_pressure(BME280_OVERSAMP_2X);
	/* set the temperature oversampling*/
	com_rslt += bme280_set_oversamp_temperature(BME280_OVERSAMP_4X);
/*--------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*
************************* START GET and SET FUNCTIONS DATA ****************
*---------------------------------------------------------------------------*/
	/* This API used to Write the standby time of the sensor input
	 *	value have to be given
	 *	Normal mode comprises an automated perpetual cycling between an (active)
	 *	Measurement period and an (inactive) standby period.
	 *	The standby time is determined by the contents of the register t_sb.
	 *	Standby time can be set using BME280_STANDBYTIME_125_MS.
	 *	Usage Hint : bme280_set_standbydur(BME280_STANDBYTIME_125_MS)*/

	com_rslt += bme280_set_standby_durn(BME280_STANDBY_TIME_1_MS);

	/* This API used to read back the written value of standby time*/
	com_rslt += bme280_get_standby_durn(&v_stand_by_time_u8);
/*-----------------------------------------------------------------*
************************* END GET and SET FUNCTIONS ****************
*------------------------------------------------------------------*/

/************************* END INITIALIZATION *************************/

/*------------------------------------------------------------------*
************ START READ UNCOMPENSATED PRESSURE, TEMPERATURE
AND HUMIDITY DATA ********
*---------------------------------------------------------------------*/
	/* API is used to read the uncompensated temperature*/
	com_rslt += bme280_read_uncomp_temperature(&v_data_uncomp_tem_s32);

	/* API is used to read the uncompensated pressure*/
	com_rslt += bme280_read_uncomp_pressure(&v_data_uncomp_pres_s32);

	/* API is used to read the uncompensated humidity*/
	com_rslt += bme280_read_uncomp_humidity(&v_data_uncomp_hum_s32);

	/* API is used to read the uncompensated temperature,pressure
	and humidity data */
	com_rslt += bme280_read_uncomp_pressure_temperature_humidity(
	&v_data_uncomp_tem_s32, &v_data_uncomp_pres_s32, &v_data_uncomp_hum_s32);
/*--------------------------------------------------------------------*
************ END READ UNCOMPENSATED PRESSURE AND TEMPERATURE********
*-------------------------------------------------------------------------*/

/*------------------------------------------------------------------*
************ START READ TRUE PRESSURE, TEMPERATURE
AND HUMIDITY DATA ********
*---------------------------------------------------------------------*/
	/* API is used to read the true temperature*/
	/* Input value as uncompensated temperature and output format*/
	com_rslt += bme280_compensate_temperature_int32(v_data_uncomp_tem_s32);

	/* API is used to read the true pressure*/
	/* Input value as uncompensated pressure */
	com_rslt += bme280_compensate_pressure_int32(v_data_uncomp_pres_s32);

	/* API is used to read the true humidity*/
	/* Input value as uncompensated humidity and output format*/
	com_rslt += bme280_compensate_humidity_int32(v_data_uncomp_hum_s32);

	/* API is used to read the true temperature, humidity and pressure*/
	com_rslt += bme280_read_pressure_temperature_humidity(
	&v_actual_press_u32, &v_actual_temp_s32, &v_actual_humity_u32);
/*--------------------------------------------------------------------*
************ END READ TRUE PRESSURE, TEMPERATURE AND HUMIDITY ********
*-------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*
************************* START DE-INITIALIZATION ***********************
*-------------------------------------------------------------------------*/
	/*	For de-initialization it is required to set the mode of
	 *	the sensor as "SLEEP"
	 *	the device reaches the lowest power consumption only
	 *	In SLEEP mode no measurements are performed
	 *	All registers are accessible
	 *	by using the below API able to set the power mode as SLEEP*/
	 /* Set the power mode as SLEEP*/
	com_rslt += bme280_set_power_mode(BME280_SLEEP_MODE);
/*---------------------------------------------------------------------*
************************* END DE-INITIALIZATION **********************
*---------------------------------------------------------------------*/
return com_rslt;
}

#ifdef BME280_API
#define MASK_DATA1	0xFF
#define MASK_DATA2	0x80
#define MASK_DATA3	0x7F
/*--------------------------------------------------------------------------*
*	The following function is used to map the I2C bus read, write, delay and
*	device address with global structure bme280
*-------------------------------------------------------------------------*/
s8 I2C_routine(void) {
/*--------------------------------------------------------------------------*
 *  By using bme280 the following structure parameter can be accessed
 *	Bus write function pointer: BME280_WR_FUNC_PTR
 *	Bus read function pointer: BME280_RD_FUNC_PTR
 *	Delay function pointer: delay_msec
 *	I2C address: dev_addr
 *--------------------------------------------------------------------------*/
	bme280.bus_write = BME280_I2C_bus_write;
	bme280.bus_read = BME280_I2C_bus_read;
	bme280.dev_addr = BME280_I2C_ADDRESS2;
	bme280.delay_msec = BME280_delay_msek;

	return BME280_INIT_VALUE;
}

/*---------------------------------------------------------------------------*
 * The following function is used to map the SPI bus read, write and delay
 * with global structure bme280
 *--------------------------------------------------------------------------*/
s8 SPI_routine(void) {
/*--------------------------------------------------------------------------*
 *  By using bme280 the following structure parameter can be accessed
 *	Bus write function pointer: BME280_WR_FUNC_PTR
 *	Bus read function pointer: BME280_RD_FUNC_PTR
 *	Delay function pointer: delay_msec
 *--------------------------------------------------------------------------*/

	bme280.bus_write = BME280_SPI_bus_write;
	bme280.bus_read = BME280_SPI_bus_read;
	bme280.delay_msec = BME280_delay_msek;

	return BME280_INIT_VALUE;
}

/************** I2C/SPI buffer length ******/
#define	I2C_BUFFER_LEN 8
#define SPI_BUFFER_LEN 5

/*-------------------------------------------------------------------*
*	This is a sample code for read and write the data by using I2C/SPI
*	Use either I2C or SPI based on your need
*	The device address defined in the bme280.h file
*-----------------------------------------------------------------------*/
 /*	\Brief: The function is used as I2C bus write
 *	\Return : Status of the I2C write
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be written
 *	\param reg_data : It is a value hold in the array,
 *		will be used for write the value into the register
 *	\param cnt : The no of byte of data to be write
 */
s8 BME280_I2C_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
        mico_i2c_message_t user_i2c_msg = {NULL, NULL, 0, 0, 0, false};
  
	s32 iError = BME280_INIT_VALUE;
	u8 array[I2C_BUFFER_LEN];
	u8 stringpos = BME280_INIT_VALUE;
	array[BME280_INIT_VALUE] = reg_addr;
	for (stringpos = BME280_INIT_VALUE; stringpos < cnt; stringpos++) {
		array[stringpos + BME280_ONE_U8X] = *(reg_data + stringpos);
	}
	/*
	* Please take the below function as your reference for
	* write the data using I2C communication
	* "IBME280_ERROR = I2C_WRITE_STRING(DEV_ADDR, ARRAY, CNT+1)"
	* add your I2C write function here
	* iError is an return value of I2C read function
	* Please select your valid return value
	* In the driver BME280_SUCCESS defined as 0
    * and FAILURE defined as -1
	* Note :
	* This is a full duplex operation,
	* The first read data is discarded, for that extra write operation
	* have to be initiated. For that cnt+1 operation done in the I2C write string function
	* For more information please refer data sheet SPI communication:
	*/
        iError = MicoI2cBuildTxMessage(&user_i2c_msg, array, cnt + 1, 3);
        iError = MicoI2cTransfer(&user_i2c_device, &user_i2c_msg, 1);
        if(0 != iError){
          iError = -1;
        }
	return (s8)iError;
}

 /*	\Brief: The function is used as I2C bus read
 *	\Return : Status of the I2C read
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be read
 *	\param reg_data : This data read from the sensor, which is hold in an array
 *	\param cnt : The no of data byte of to be read
 */
s8 BME280_I2C_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
        mico_i2c_message_t user_i2c_msg = {NULL, NULL, 0, 0, 0, false};
    
	s32 iError = BME280_INIT_VALUE;
	u8 array[I2C_BUFFER_LEN] = {BME280_INIT_VALUE};
	//u8 stringpos = BME280_INIT_VALUE;
	array[BME280_INIT_VALUE] = reg_addr;
	/* Please take the below function as your reference
	 * for read the data using I2C communication
	 * add your I2C rad function here.
	 * "IBME280_ERROR = I2C_WRITE_READ_STRING(DEV_ADDR, ARRAY, ARRAY, 1, CNT)"
	 * iError is an return value of SPI write function
	 * Please select your valid return value
     * In the driver BME280_SUCCESS defined as 0
     * and FAILURE defined as -1
	 */
        //iError = MicoI2cBuildRxMessage(&user_i2c_msg, array, cnt + 1, 3);
        iError = MicoI2cBuildCombinedMessage(&user_i2c_msg, array, reg_data, 1, cnt, 3);
         if(0 != iError){
          return (s8)iError; 
        }
        iError = MicoI2cTransfer(&user_i2c_device, &user_i2c_msg, 1);
        if(0 != iError){
          return (s8)iError;
        }
        
	//for (stringpos = BME280_INIT_VALUE; stringpos < cnt; stringpos++) {
	//	*(reg_data + stringpos) = array[stringpos];
	//}
	return (s8)iError;
}

/*	\Brief: The function is used as SPI bus read
 *	\Return : Status of the SPI read
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be read
 *	\param reg_data : This data read from the sensor, which is hold in an array
 *	\param cnt : The no of byte of data to be read
 */
//s8 BME280_SPI_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
//{
//	s32 iError=BME280_INIT_VALUE;
//	u8 array[SPI_BUFFER_LEN]={MASK_DATA1};
//	u8 stringpos;
//	/*	For the SPI mode only 7 bits of register addresses are used.
//	The MSB of register address is declared the bit what functionality it is
//	read/write (read as 1/write as BME280_INIT_VALUE)*/
//	array[BME280_INIT_VALUE] = reg_addr|MASK_DATA2;/*read routine is initiated register address is mask with 0x80*/
//	/*
//	* Please take the below function as your reference for
//	* read the data using SPI communication
//	* " IBME280_ERROR = SPI_READ_WRITE_STRING(ARRAY, ARRAY, CNT+1)"
//	* add your SPI read function here
//	* iError is an return value of SPI read function
//	* Please select your valid return value
//	* In the driver BME280_SUCCESS defined as 0
//    * and FAILURE defined as -1
//	* Note :
//	* This is a full duplex operation,
//	* The first read data is discarded, for that extra write operation
//	* have to be initiated. For that cnt+1 operation done in the SPI read
//	* and write string function
//	* For more information please refer data sheet SPI communication:
//	*/
//	for (stringpos = BME280_INIT_VALUE; stringpos < cnt; stringpos++) {
//		*(reg_data + stringpos) = array[stringpos+BME280_ONE_U8X];
//	}
//	return (s8)iError;
//}
//
///*	\Brief: The function is used as SPI bus write
// *	\Return : Status of the SPI write
// *	\param dev_addr : The device address of the sensor
// *	\param reg_addr : Address of the first register, will data is going to be written
// *	\param reg_data : It is a value hold in the array,
// *		will be used for write the value into the register
// *	\param cnt : The no of byte of data to be write
// */
//s8 BME280_SPI_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
//{
//	s32 iError = BME280_INIT_VALUE;
//	u8 array[SPI_BUFFER_LEN * BME280_TWO_U8X];
//	u8 stringpos = BME280_INIT_VALUE;
//	for (stringpos = BME280_INIT_VALUE; stringpos < cnt; stringpos++) {
//		/* the operation of (reg_addr++)&0x7F done: because it ensure the
//		   BME280_INIT_VALUE and 1 of the given value
//		   It is done only for 8bit operation*/
//		array[stringpos * BME280_TWO_U8X] = (reg_addr++) & MASK_DATA3;
//		array[stringpos * BME280_TWO_U8X + BME280_ONE_U8X] = *(reg_data + stringpos);
//	}
//	/* Please take the below function as your reference
//	 * for write the data using SPI communication
//	 * add your SPI write function here.
//	 * "IBME280_ERROR = SPI_WRITE_STRING(ARRAY, CNT*2)"
//	 * iError is an return value of SPI write function
//	 * Please select your valid return value
//	 * In the driver BME280_SUCCESS defined as 0
//     * and FAILURE defined as -1
//	 */
//	return (s8)iError;
//}

/*	Brief : The delay routine
 *	\param : delay in ms
*/
void BME280_delay_msek(u16 msek)
{
	/*Here you can write your own delay routine*/
  mico_thread_msleep(msek);
}
#endif


// bme280_sensor_init
OSStatus bme280_sensor_init(void)
{
  OSStatus err = kUnknownErr;
  s32 com_rslt = BME280_ERROR;  // result of communication results
 // u8 v_stand_by_time_u8 = BME280_INIT_VALUE;  //  The variable used to assign the standby time
  
  // I2C init
  MicoI2cFinalize(&user_i2c_device);   // in case error
  err = MicoI2cInitialize(&user_i2c_device);
  require_noerr_action( err, exit, bme280_user_log("BME280_ERROR: MicoI2cInitialize err = %d.", err) );
  if( false == MicoI2cProbeDevice(&user_i2c_device, 5) ){
    bme280_user_log("BME280_ERROR: no i2c device found!");
    err = kNotFoundErr;
    goto exit;
  }
  
  // sensor init

  /*********************** START INITIALIZATION ************************/
  /*	Based on the user need configure I2C or SPI interface.
  *	It is example code to explain how to use the bme280 API*/
#ifdef BME280_API
  I2C_routine();
  com_rslt = bme280_init(&bme280);
  com_rslt += bme280_set_power_mode(BME280_NORMAL_MODE);
  com_rslt += bme280_set_oversamp_humidity(BME280_OVERSAMP_1X);
  com_rslt += bme280_set_oversamp_pressure(BME280_OVERSAMP_2X);
  com_rslt += bme280_set_oversamp_temperature(BME280_OVERSAMP_4X);
  /************************* START GET and SET FUNCTIONS DATA ****************/
  //com_rslt += bme280_set_standby_durn(BME280_STANDBY_TIME_1_MS);
  //com_rslt += bme280_get_standby_durn(&v_stand_by_time_u8);
  /************************** END GET and SET FUNCTIONS **************/
  if(com_rslt < 0){
    bme280_user_log("BME280_ERROR: bme280 sensor init failed!");
    err = kNotInitializedErr;
    goto exit;
  }
  /************************* END INITIALIZATION *************************/
#endif
  return kNoErr;
  
exit:
  return err;
}


OSStatus bme280_data_readout(s32 *v_actual_temp_s32, u32 *v_actual_press_u32, u32 *v_actual_humity_u32)
{
    OSStatus err = kUnknownErr;
    
	/* result of communication results*/
	s32 com_rslt = BME280_ERROR;
        
        //-------------------------- NOTE ----------------------------------
        // this is to avoid i2c pin is re-init by other module because they use the same pin.
        MicoI2cInitialize(&user_i2c_device);
        //------------------------------------------------------------------
          
//        /************ START READ TRUE PRESSURE, TEMPERATURE AND HUMIDITY DATA *********/
//	/* API is used to read the true temperature*/
//	/* Input value as uncompensated temperature and output format*/
//        	com_rslt += bme280_compensate_temperature_int32(v_data_uncomp_tem_s32);
//        	com_rslt += bme280_compensate_pressure_int32(v_data_uncomp_pres_s32);
//        	com_rslt += bme280_compensate_humidity_int32(v_data_uncomp_hum_s32);
        
	/* API is used to read the true temperature, humidity and pressure*/
	com_rslt = bme280_read_pressure_temperature_humidity(v_actual_press_u32, 
                                                             v_actual_temp_s32, 
                                                             v_actual_humity_u32);
        /************ END READ TRUE PRESSURE, TEMPERATURE AND HUMIDITY ********/
        
        if(0 == com_rslt){
          err = kNoErr;
        }
        return err;
}

OSStatus bme280_read_temperature(s32 *v_actual_temp_s32)
{
	s32 com_rslt = BME280_ERROR;  // result of communication results
	s32 v_data_uncomp_tem_s32 = BME280_INIT_VALUE;  // uncompensated temperature
     
        //-------------------------- NOTE ----------------------------------
        // this is to avoid i2c pin is re-init by other module because they use the same pin.
        MicoI2cInitialize(&user_i2c_device);
        //------------------------------------------------------------------
        
        com_rslt = bme280_read_uncomp_temperature(&v_data_uncomp_tem_s32);
         if(0 != com_rslt){
          return kReadErr;
        }
        
        *v_actual_temp_s32 = bme280_compensate_temperature_int32(v_data_uncomp_tem_s32);
        
        return kNoErr;
}

OSStatus bme280_read_humidity(u32 *v_actual_humity_u32)
{
  	s32 com_rslt = BME280_ERROR;  // result of communication results
	s32 v_data_uncomp_hum_s32 = BME280_INIT_VALUE;  // uncompensated humidity
     
        //-------------------------- NOTE ----------------------------------
        // this is to avoid i2c pin is re-init by other module because they use the same pin.
        MicoI2cInitialize(&user_i2c_device);
        //------------------------------------------------------------------
        
        com_rslt = bme280_read_uncomp_humidity(&v_data_uncomp_hum_s32);
         if(0 != com_rslt){
          return kReadErr;
        }
        
        *v_actual_humity_u32 = bme280_compensate_humidity_int32(v_data_uncomp_hum_s32);
        
        return kNoErr;
}

OSStatus bme280_data_pressure(u32 *v_actual_press_u32)
{
    	s32 com_rslt = BME280_ERROR;  // result of communication results
	s32 v_data_uncomp_pres_s32 = BME280_INIT_VALUE;  // uncompensated humidity
     
        //-------------------------- NOTE ----------------------------------
        // this is to avoid i2c pin is re-init by other module because they use the same pin.
        MicoI2cInitialize(&user_i2c_device);
        //------------------------------------------------------------------
        
        com_rslt = bme280_read_uncomp_pressure(&v_data_uncomp_pres_s32);
         if(0 != com_rslt){
          return kReadErr;
        }
        
        *v_actual_press_u32 = bme280_compensate_pressure_int32(v_data_uncomp_pres_s32);
        
        return kNoErr;
}


// bme280_sensor_init
OSStatus bme280_sensor_deinit(void)
{
  OSStatus err = kUnknownErr;
  s32 com_rslt = BME280_ERROR;
  
  err = MicoI2cFinalize(&user_i2c_device);
  require_noerr_action( err, exit, bme280_user_log("BME280_ERROR: MicoI2cFinalize err = %d.", err));
  
  /*********************** START DE-INITIALIZATION ************************/
  /*	For de-initialization it is required to set the mode of
  *	the sensor as "SLEEP"
  *	the device reaches the lowest power consumption only
  *	In SLEEP mode no measurements are performed
  *	All registers are accessible
  *	by using the below API able to set the power mode as SLEEP*/
  /* Set the power mode as SLEEP*/
  com_rslt = bme280_set_power_mode(BME280_SLEEP_MODE);
  /************************** END DE-INITIALIZATION ***********************/
  if(0 == com_rslt){
    err = kNoErr;
  }
  
exit:
  return err;
}
