# A kretz AW14/5B/A ultrasound probe - `20180812a`

Apart from testing the kretz probe, which was okay of sorts:

![](/include/images/kretzaw145ba/20180812a/image-20180812a-18-wirephantom-big.png)

There were major flaws in the lib settings:
* LAcq was wrongly calcumated, off by a factor 128*10/1000
* NAcqs was only limited to 160.

Now, some more tests!
* 450 lines at  8 Msps of 100us 
* and 900 lines at 8 Msps for 50 us to be tested =)
