## Resources

* https://groups.google.com/forum/#!topic/comp.protocols.dicom/xh0ogPv31aI for an excellent definition of the fields
* http://dicomiseasy.blogspot.fr/2012/08/chapter-12-pixel-data.html

* "there is DICOM meta-data that includes the resolution in the PixelWidth tag".

## Resources

```
file_meta.MediaStorageSOPClassUID = 'Ultrasound Image Storage'
file_meta.MediaStorageSOPInstanceUID = '1.2.840.10008.5.1.4.1.1.6.1' # Ultrasound see -> SOP UID (ee http://www.dicomlibrary.com/dicom/sop/)
file_meta.ImplementationClassUID = '1.3.6.1.4.1.9590.100.1.0.100.4.0' # unknown

ds = FileDataset(filename, {},file_meta = file_meta,preamble="\0"*128)
ds.Modality = 'WSD' # Workstation
ds.ContentDate = str(datetime.date.today()).replace('-','') # data
ds.ContentTime = str(time.time()) # now -> milliseconds since the epoch time
#ds.StudyInstanceUID =  '1.3.6.1.4.1.9590.100.1.1.124313977412360175234271287472804872093' -
#ds.SeriesInstanceUID = '1.3.6.1.4.1.9590.100.1.1.369231118011061003403421859172643143649'
#ds.SOPInstanceUID ='1.3.6.1.4.1.9590.100.1.1.111165684411017669021768385720736873780'
ds.SOPClassUID = 'Ultrasound Image Storage'
ds.SecondaryCaptureDeviceManufctur = 'Kina - Python 2 - http://github.com/kelu124/kina/'
## These are the necessary imaging components of the FileDataset object.
ds.SamplesPerPixel = 1
ds.PhotometricInterpretation = "MONOCHROME2"
ds.PixelRepresentation = 0
ds.HighBit = 15
ds.BitsStored = 16
ds.BitsAllocated = 16
ds.SmallestImagePixelValue = '\\x00\\x00'
ds.LargestImagePixelValue = '\\xff\\xff'
# Creating the image itself
pixel_array = np.array(np.transpose(pixel_array))
ds.Columns = pixel_array.shape[1] # Number of columns
ds.Rows = pixel_array.shape[0] # Number of rows
if pixel_array.dtype != np.uint16:
	pixel_array = pixel_array.astype(np.uint16)
ds.PixelData = pixel_array.tostring()
```
