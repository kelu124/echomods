## Format Rules 

* First part is classical CSV __note that the first item contains the position of the line, in arbitrary unit__
* Second part is comments (starting with #).

In comments can be found meta data, storing for example the following items

* `#timestamp:XX` for the timestamp when the image was taken
* `#lines:XX` contains the number of lines in the image
* `#length:XX` contains the number of pixels per line
* `#frequency:XX` is the frequency of acquisition
* `#piezofrequency:XX` is the piezo frequency
* `#angle:XX` is the angle of the acquisition
* `#anglestep:XX` is the multiplicator between the first item of each line to obtain the position in degree.
