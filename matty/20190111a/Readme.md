# `20190111a` - Using the pyUn0 python lib


## What ?

Been working on streamlining tests[^1].

From shell, a typical test sequence would look like:

### To test blinky

python pyUn0.py test

### To test acquisitions:

*  to run acquisition of a single line

`python pyUn0.py single`

*  to run acquisition of three lines

`python pyUn0.py multi `

* to process images from JSON files

`python pyUn0.py process `

## Results

* A folder structure with a [data folder](/matty/20190111a/images/) (json and npz) as well as [images folder](/matty/20190111a/data/).

* Images

![](/matty/20190111a/images/20190111a-1.jpg)
![](/matty/20190111a/images/20190111a-1-fft.jpg)
![](/matty/20190111a/images/20190111a-2.jpg)
![](/matty/20190111a/images/20190111a-2-fft.jpg)

[^1]: Excellent footnote.
