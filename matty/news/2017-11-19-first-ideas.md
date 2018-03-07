---
layout: post
title: First idea
excerpt: "Getting the first schematics in place."
categories: [worklog]
comments: false
---

## Basic idea

What I want is to get a small, open-source electronic board to do ultrasound imaging.

I'm not fully new to it, as I've been working on [ultrasound imaging with Raspberry Pi](https://kelu124.gitbooks.io/echomods/content/RPI.html), using [arduino-like modules](https://github.com/kelu124/echomods/) -- and even getting an [article out on this](http://openhardware.metajnl.com/articles/10.5334/joh.2/).

As I want an open-source framework, the only resource we have in terms of FPGA are the Lattice ice40 series. Let's focus on that!

![](https://raw.githubusercontent.com/kelu124/echomods/master/matty/images/0flow.jpg)

## Refined idea

Actually, the main issue lies around the FPGA. THe UP5K did not have enough IOs. As of this date, the UP5K is/was not supported by the open-source toolchain.

Not having a UP5K with internal RAM forces to use an external ram - which also impacts the number of IOs.

![](https://raw.githubusercontent.com/kelu124/echomods/master/matty/images/idea.jpg)
