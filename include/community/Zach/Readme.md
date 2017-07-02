---
who: Zach
place: Nashville, TN 37235, États-Unis
pos: 36.1447034,-86.8026551
entity: Vanderbilt University
---

# 2016-10-26_Zach Implementing image processing techniques [](@description Zach's worklog, simplified, on murgen)

Data is received at each angle. It then undergoes processing to reconstruct it into an image. Each stage of image processing will be demonstrated.

### Setup
![](/include/community/Zach/images/Setup.png)

Here's the setup.

### Original
![](/include/community/Zach/images/Original.png)

Clearly needs some noise reduction. I'll add a Butterworth filter.


### Implementing a Butterworth Bandpass Filter
![](/include/community/Zach/images/Butter.png)

Needs more noise reduction. I'll add a Hilbert transformation.


### Implementing Envelope Detection
![](/include/community/Zach/images/Hilbert.png)

Good image... But it seems to fade with distance. I'll add time gain compensation.


### Implementing Time Gain Compensation
![](/include/community/Zach/images/TGC.png)

Most up to date image.
