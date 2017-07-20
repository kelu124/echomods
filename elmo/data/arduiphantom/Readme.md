# Test _20170718-Servo.ipynb_

Access to the [Notebook](/elmo/data/arduiphantom/20170718-Servo.ipynb). Delays between shots, to see if the delays between repeat shots are good (recharging the HV?).

Resource files - NPZ files :

* [Without delays between lines](/elmo/data/arduiphantom/nodelay.npz) 
* [With delays between lines](/elmo/data/arduiphantom/delay.npz) - 20ms between lines

# Tests

## Previous tests on a phantom

It was just ran with the signal emulator, providing a signal at 1.9MHz, yielding these results

![](/elmo/data/twoadcs.jpg)

## Previous experiment with the probe

It was ran with the probe, with a wire phantom in the glass of water, according to this setup:

![](/elmo/images/20170717_210209.jpg)

The processing channel was as follows:

![](/elmo/data/Imgs/Processing_probeX.data.jpg)

yielding this type of image:

![](/elmo/data/Imgs/pic_probeX.data.jpg)

## Previous experiment with the servo

The setup is as follows:

![](/elmo/images/20170717_223857.jpg)

Images.. processing is ongoing =)

-> See this [jupyter notebook to see](/elmo/data/arduiphantom/20170718-Servo.ipynb) the progress. The issue here is to align the beginning of the lines together to have a consistent delay at first.


