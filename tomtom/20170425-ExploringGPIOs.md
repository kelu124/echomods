# Tomtom 

How can we unlock the GPIOs?

## What I need

### In mind..

![](/tomtom/images/pulses.png)

### But ideally..

* Fire the pulse for a settable time _t_
* Stop the pulse after _t_

## Remarks from USBFM

* Looks like the pigpio has a dedicated C interface: http://abyz.co.uk/rpi/pigpio/cif.html

```
#!/bin/bash 
sudo pigpiod cat /dev/pigout& 
echo "mg 18 5" >/dev/pigpio 
echo "hp 18 2250000 100000" >/dev/pigpio
```

* What is HP? See http://abyz.co.uk/rpi/pigpio/pigs.html#HP

* 2250000: frequency in Hz

_In code I defined the pulse to occupy 10% of the duty cycle, which is around 40ns with a period of 440ns_ -- "That magic 5 changes the GPIO18 pin mode to ALT5"

Other stuff:

* uint32_t gpioTick(void)
* Returns the current system tick.
* Tick is the number of microseconds since system boot. 

## Remarks from @eiffel

Ces deux liens devraient pas mal t'aider je pense ^^ :
* http://www.makelinux.net/ldd3/chp-7-sect-6
* http://www.makelinux.net/ldd3/chp-7-sect-7


* Avec les sleeps ça devrait le faire ? Vu que tu rends le CPU pendant les sleeps
* C'est pas des gros travaux de mettre à high et low des pins, après faut juste pas faire de l'attente active
* Sinon la solution de la workqueue sera plus légère, je pense qu'il est possible de scheduler le réveil de tâches à des instants précis dans le noyau.
* J'essaye de te trouver l'API qui fait ça: https://gist.github.com/yagihiro/309746 (jiffies précisées dans http://www.makelinux.net/ldd3/chp-7-sect-7 )

A base de sleeps?
* https://linux.die.net/man/2/nanosleep

* http://stackoverflow.com/questions/5803715/how-to-make-a-thread-sleep-block-for-nanoseconds-or-at-least-milliseconds



One relatively portable way is to use select() or pselect() with no file descriptors:

```
void sleep(unsigned long nsec) {
    struct timespec delay = { nsec / 1000000000, nsec % 1000000000 };
    pselect(0, NULL, NULL, NULL, &delay, NULL);
}
```
