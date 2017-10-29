---

layout: post

title: 2017-10-28 News from ther modules and pulser

---


-   DataScience https://jakevdp.github.io/PythonDataScienceHandbook/
-   Butterfly
    http://m.marketwired.com/press-release/first-ultrasound-on-a-chip-receives-broadest-fda-510k-clearance-2238621.htm
    2k\$

-   http://baruch.siach.name/blog/posts/linux\_kernel\_module\_parameters/
    (t1, t2, t3, t4) Pon, Pdamp, Pon, pdamp

-   http://www.tldp.org/LDP/lkmpg/2.4/html/x354.htm !! excellent
-   https://www.linux.com/learn/kernel-newbie-corner-everything-you-wanted-know-about-module-parameters

-   Commands

-   modprobe foo parameter=value
-   modinfo ambassador for params

Sometimes a kernel modules allows setting a parameter at run time. In
this case you'll find the parameter under
/sys/module/modulename/parameters/, with writable file permissions. The
debug parameter of the ambassador module is an example of such a
parameter. Set a value to this parameter with a simple echo command:

    echo -n 1 > /sys/module/ambassador/parameters/debug

-   http://anons.wiki/
-   https://github.com/LappleApple/feedmereadmes/blob/master/README-maturity-model.md

