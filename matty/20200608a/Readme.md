
# `20200608a` playing with brd35

## Ino

* Source : [ino file](/matty/20200608a/control.ino) for an atom matrix m5 controlling a drv8834

* Setup:

```
21:22:12.751 -> M0:0
21:22:12.751 -> M1:1
21:22:12.751 -> DIR:0

ledcAttachPin(STP, 0); // broche 18, canal 0.
ledcSetup(0, 32*60/4, 12); // canal = 0, frequence = 5000 Hz, resolution = 12 bits
ledcWrite(0, 2048);   //  canal = 0, rapport cyclique = 2048 (half at 12bits)
```

## Images

![](/matty/20200608a/images/gif_2.jpg)

![](/matty/20200608a/images/movie.gif)

## Signal quality

![](/matty/20200608a/images/20200608a-12.jpg)

![](/matty/20200608a/images/20200608a-12-fft.jpg)

## Images

![](/matty/20200608a/images/2DArray_20200608a-10.jpg)

![](/matty/20200608a/images/2DArray_20200608a-11.jpg)

![](/matty/20200608a/images/2DArray_20200608a-12.jpg)



