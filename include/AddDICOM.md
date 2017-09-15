## Links and resources on DICOM

https://www.researchgate.net/post/What_is_the_difference_between_ultrasound_DICOM_and_raw_DICOM_At_which_stage_in_the_ultrasound_machine_are_the_DICOM_raw_DICOM_images_extracted

MODALITY:

* https://www.dicomlibrary.com/dicom/modality/
* US : ultrasound

https://www.dicomlibrary.com/dicom/sop/

* 1.2.840.10008.5.1.4.1.1.3.1 Ultrasound Multiframe Image Storage
* 1.2.840.10008.5.1.4.1.1.6.1 Ultrasound Image Storage

http://dicom.nema.org/dicom/2013/output/chtml/part04/sect_I.4.html

* 1.2.840.10008.5.1.4.1.1.6.1 Ultrasound Image Storage

http://dicom.nema.org/dicom/2013/output/chtml/part03/sect_A.6.html

* SOP: Common: http://dicom.nema.org/dicom/2013/output/chtml/part03/sect_C.12.html#sect_C.12.1
  * Date
  * Time
  * Operators' Name
  * Device Serial Number

http://dicom.nema.org/dicom/2013/output/chtml/part03/sect_C.7.html#sect_C.7.6.1

* General Equipment Module
* General Image Module ( http://dicom.nema.org/dicom/2013/output/chtml/part03/sect_C.7.html#sect_C.7.6.1 )
  * Image Type -> a.Pixel Data Characteristics 1.is the image an ORIGINAL Image
  * Acquisition DateTime
  * Multiple Items may be present within Source Image Sequence (0008,2112) (Raw + processed)
* Image Pixel Module
  * Rows
  * Columns
  * Pixel Data
  * Pixel Aspect Ratio

# External resoures

* https://groups.google.com/forum/#!topic/comp.protocols.dicom/xh0ogPv31aI for an excellent definition of the fields
* http://dicomiseasy.blogspot.fr/2012/08/chapter-12-pixel-data.html

* http://dicomiseasy.blogspot.com/2012/08/chapter-12-pixel-data.html
* https://www.raddq.com/dicom-processing-segmentation-visualization-in-python/
* http://saravanansubramanian.com/Saravanan/Articles_On_Software/Entries/2014/10/6_DICOM_Basics_-_Extracting_Image_Pixel_Data.html

# Internal resources

 grep -nrw "DICOM" ./ --include "*.md"


* [Testing pydicom](/kina/blob/master/20170411-DICOM.ipynb)
* [Some notes](/tomtom/DicomHandler.md)


# Pieces of codes

Multiple images:

```
import dicom,numpy
dose = dicom.ReadFile("RTDOSE.dcm")
d = numpy.fromstring(dose.PixelData,dtype=numpy.int16)
d = d.reshape((dose.NumberofFrames,dose.Columns,dose.Rows))
```
