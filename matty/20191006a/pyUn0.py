# -*- coding: utf-8 -*-
"""Most updated library for the lit3rick platform.
@todo: improve doc: http://sametmax.com/les-docstrings/
"""
import json
import time
import os
import sys
import re
import numpy as np
import matplotlib.pyplot as plt

from spi_connector import SpiConnector

__author__ = "kelu124"
__copyright__ = "Copyright 2018, Kelu124"
__license__ = "GPLv3"


"""
Processing part.
"""


def make_clean(path):
    os.chdir(path)
    if not os.path.exists(path + "data"):
        os.makedirs(path + "data")
        print("'data' folder created")
    if not os.path.exists(path + "images"):
        os.makedirs(path + "images")
        print("'images' folder created")
    for root, dirs, files in os.walk(path):
        for filename in files:
            if filename.endswith(".json"):
                original_file = os.path.join(root, filename)
                if "data/" not in original_file:
                    print(("Moved '", original_file, " to ", "./data/" + filename))
                    os.rename(original_file, "./data/" + filename)
    return 0


def metadatag_images_batch(list_modules, exp_id, img_category, img_desc):
    """
        Used to add proper tags to all images. Dangerous to use...
    """
    try:
        import pyexiv2
        Imgs = []
        for dirpath, dirnames, filenames in os.walk("."):
            for filename in [
                f for f in filenames if (f.endswith(".jpg") or f.endswith(".png"))
            ]:
                Imgs.append(os.path.join(dirpath, filename))
        for file_name in Imgs:
            metadata = pyexiv2.ImageMetadata(file_name)
            try:
                metadata.read()
            except IOError:
                print("Not an image")
            else:
                # Modules
                metadata["Exif.Image.Software"] = list_modules  # "matty, cletus"
                metadata["Exif.Image.Make"] = exp_id  # "20180516a"
                metadata["Exif.Photo.MakerNote"] = img_category  # "oscilloscope"
                metadata["Exif.Image.ImageDescription"] = img_desc  # "Unpacking data"
                metadata.write()
            print(file_name, "done")
    except ImportError:
        print("PyExiv not present")
    return 0


def tag_image(file_name, module, experiment, category, description):
    try:
        import pyexiv2
        metadata = pyexiv2.ImageMetadata(file_name)
        try:
            metadata.read()
        except IOError:
            print("Not an image")
        else:
            metadata["Exif.Image.Software"] = module  # "matty, cletus"
            metadata["Exif.Image.Make"] = experiment  # "20180516a"
            metadata["Exif.Photo.MakerNote"] = category  # "oscilloscope"
            metadata["Exif.Image.ImageDescription"] = description  # "Unpacking data"
            metadata.write()
    except ImportError:
        print("PyExiv not present")
    return 1


class DataToJson:
    """
        Class used to process data once acquired.
    """

    metatags = {}
    show_images = True
    IDLine = []
    TT1 = []
    TT2 = []
    tmp = []
    tdac = []
    FFT_x = []
    FFT_y = []
    EnvHil = []
    Duration = 0
    filtered_fft = []
    LengthT = 0
    Nacq = 0
    Raw = []
    Signal = []
    filtered_signal = []
    Registers = {}
    t = []
    fPiezo = 5
    Bandwidth = 1.0
    f = 0  # sampling freq
    piezo = ""
    experiment = ""
    len_acq = 0
    len_line = 0
    N = 0
    V = 0
    single = 0
    processed = False
    iD = 0
    raw_2d_image = []

    metatags["firmware_md5"] = ""

    def json_proccess(self, path):
        """
            Creates actual raw data from the signals acquired.
        """
        IDLine = []
        TT1 = []
        TT2 = []
        tmp = []

        with open(path) as json_data:
            d = json.load(json_data)
            json_data.close()

            self.description = d["experiment"]["description"]
            self.piezo = d["experiment"]["probe"]
            self.metatags["time"] = d["time"]
            self.metatags["original_json"] = d

            A = d["data"]
            for i in range(int(len(A) / 2 - 1)):
                if (A[2 * i + 1]) < 128:
                    value = 128 * (A[2 * i + 0] & 0b00011111) + A[2 * i + 1] - 4 * 512
                    IDLine.append(
                        ((A[2 * i + 0] & 0b11110000) / 16 - 8) / 2
                    )  # Identify the # of the line
                    TT1.append((A[2 * i + 0] & 0b00001000) / 0b1000)
                    TT2.append((A[2 * i + 0] & 0b00010000) / 0b10000)
                    tmp.append(2.0 * value / (4 * 512.0))
                else:
                    value = 128 * (A[2 * i + 1] & 0b00011111) + A[2 * i + 2] - 4 * 512
                    IDLine.append(
                        ((A[2 * i + 1] & 0b00011111) / 16 - 8) / 2
                    )  # Identify the # of the line
                    TT1.append((A[2 * i + 1] & 0b00001000) / 0b1000)
                    TT2.append((A[2 * i + 1] & 0b00010000) / 0b10000)
                    tmp.append(2.0 * value / (4 * 512.0))
            print("Data acquired")
            self.Registers = d["registers"]
            self.timings = d["timings"]
            self.f = float(64 / (1.0 + int(d["registers"]["237"])))

            t = [
                1.0 * x / self.f + self.timings["t4"] / 1000.0 for x in range(len(tmp))
            ]
            self.t = t

            for i in range(len(IDLine)):
                if IDLine[i] < 0:
                    IDLine[i] = 0
            self.LengthT = len(t)

            self.TT1 = TT1
            self.TT2 = TT2
            self.Nacq = d["timings"]["NLines"]
            self.len_acq = len(self.t)
            self.len_line = int(self.len_acq / self.Nacq)

            # Precising the DAC
            REG = [int(x) for x in list(d["registers"].keys()) if int(x) < 100]
            REG.sort()
            dac = []
            for k in REG:
                dac.append(d["registers"][str(k)])
            # Building the DAC timeline
            tdac = []
            for pts in t[0:self.len_line]:  # @todo -> corriger pour avoir une ligne de 200us
                i = int(pts / 5.0)  # time in us
                try:
                    tdac.append(4.0 * d["registers"][str(i + 16)])
                except:
                    tdac.append(-1)

            # Updating the JSON
            self.tdac = tdac
            self.tmp = tmp
            self.single = d["registers"][str(0xEB)]
            self.t = t
            self.IDLine = IDLine
            self.metatags["firmware_md5"] = d["firmware_md5"]
            self.experiment = d["experiment"]
            self.parameters = d["parameters"]
            self.iD = d["experiment"]["id"]
            self.N = d["N"]
            self.V = d["V"]
            self.processed = True
            self.Duration = (
                self.parameters["LengthAcq"] - self.parameters["DeltaAcq"]
            ) / 1000.0

    def create_fft(self):
        self.FFT_x = [X * self.f / self.LengthT for X in range(self.LengthT)]
        self.FFT_y = np.fft.fft(self.tmp)
        self.filtered_fft = np.fft.fft(self.tmp)

        for k in range(int(self.LengthT / 2 + 1)):
            if k < (self.LengthT * self.fPiezo * (1 - self.Bandwidth / 2.0) / self.f):
                self.filtered_fft[k] = 0
                self.filtered_fft[-k] = 0
            if k > (self.LengthT * self.fPiezo * (1 + self.Bandwidth / 2.0) / self.f):
                self.filtered_fft[k] = 0
                self.filtered_fft[-k] = 0

        self.filtered_signal = np.real(np.fft.ifft(self.filtered_fft))

        if self.processed:
            plt.figure(figsize=(15, 5))

            plot_time = self.FFT_x[1:self.LengthT / 2]
            plot_abs_fft = np.abs(self.FFT_y[1:self.LengthT / 2])
            plot_filtered_fft = np.abs(self.filtered_fft[1:self.LengthT / 2])

            plt.plot(plot_time, plot_abs_fft, "b-")
            plt.plot(plot_time, plot_filtered_fft, "y-")

            plt.title("FFT of " + self.iD + " - acq. #: " + str(self.N))
            plt.xlabel("Freq (MHz)")
            plt.tight_layout()
            file_name = "images/" + self.iD + "-" + str(self.N) + "-fft.jpg"
            plt.savefig(file_name)
            if self.show_images:
                plt.show()
            description_experiment = "FFT of the of " + self.iD
            description_experiment += " experiment. " + self.experiment["description"]
            tag_image(
                file_name, "matty, cletus", self.iD, "FFT", description_experiment
            )

    def make_image(self):
        """
           Makes an image from the JSON content
        """
        if self.processed:  # @todo check this to get env  &  al
            fig, ax1 = plt.subplots(figsize=(20, 10))
            ax2 = ax1.twinx()
            ax2.plot(self.t[0 : self.len_line], self.tdac[0 : self.len_line], "g-")
            ax1.plot(self.t[0 : self.len_line], self.tmp[0 : self.len_line], "b-")
            plt.title(self.create_title_text())
            ax1.set_xlabel("Time (us)")
            ax1.set_ylabel("Signal from ADC (V)", color="b")
            ax2.set_ylabel("DAC output in mV (range 0 to 1V)", color="g")
            plt.tight_layout()
            file_name = "images/" + self.iD + "-" + str(self.N) + ".jpg"
            plt.savefig(file_name)
            if self.show_images:
                plt.show()
            tag_image(
                file_name,
                "matty",
                self.iD,
                "graph",
                "Automated image of "
                + self.iD
                + " experiment. "
                + self.experiment["description"],
            )

    @staticmethod
    def tag_image(bricks, experiment_id, img_type, img_desc, file_name):
        """
        Tags an image using available info.
        """
        # file_name = "images/"+self.iD+"-"+str(self.N)+".jpg"
        # @todo : create images folder if not exists
        try:
            import pyexiv2
            metadata = pyexiv2.ImageMetadata(file_name)
            try:
                metadata.read()
            except IOError:
                print("Not an image")
            else:
                metadata["Exif.Image.Software"] = bricks
                metadata["Exif.Image.Make"] = experiment_id
                metadata["Exif.Photo.MakerNote"] = img_type
                metadata["Exif.Image.ImageDescription"] = img_desc
                metadata.write()
        except ImportError:
            print("pyexiv does not exist")

    def mk2DArray(self):
        """
        Creates a 2D array from raw json.
        """
        len_acquisition = len(self.tmp)
        img = []
        tmpline = []
        lineindex = 0

        for k in range(len_acquisition):
            if self.IDLine[k] != lineindex:
                img.append(tmpline)
                lineindex = self.IDLine[k]
                tmpline = []
            else:
                tmpline.append(self.tmp[k])

        duration_self = int(float(self.f) * self.Duration)

        y = [
            s
            for s in img
            if (len(s) > duration_self - 10 and len(s) < duration_self + 10)
        ]
        if self.Nacq > 1:
            clean_image = np.zeros((len(y), len(self.tmp) / len(y)))
        else:
            clean_image = np.zeros((len(y), 1))

        for i in range(len(y)):
            clean_image[i][0 : len(y[i])] = y[i]

        img_size = np.shape(clean_image)
        duration = (self.parameters["LengthAcq"] - self.parameters["DeltaAcq"]) / 1000.0

        clean_image = clean_image[:, : int(duration * self.f)]
        plt.figure(figsize=(15, 10))
        if self.Nacq > 1:
            print(img_size[1], img_size[0])
            plt.imshow(
                np.sqrt(np.abs(clean_image)),
                cmap="gray",
                aspect=0.5 * (img_size[1] / img_size[0]),
                interpolation="nearest",
            )
        else:
            plt.plot(self.t[0 : self.len_line], self.tmp[0 : self.len_line], "b-")

        plt.title(self.create_title_text())
        plt.tight_layout()
        file_name = "images/2DArray_" + self.iD + "-" + str(self.N) + ".jpg"
        plt.savefig(file_name)
        tag_image(
            file_name,
            "matty, " + self.piezo,
            self.iD,
            "BC",
            self.create_title_text().replace("\n", ". "),
        )
        if self.show_images:
            plt.show()
        self.raw_2d_image = clean_image  # @todo: reuse this 2D image ?
        return clean_image

    def save_npz(self):
        """
           Saves the dataset as an NPZ, in the data folder.
        """
        path_npz = (
            "data/" + self.iD + "-" + str(self.N) + ".npz"
        )  # @todo: create folder if not.
        np.savez(path_npz, self)

    def plot_detail(self, nb_line, Start, Stop):  # @todo: use it when processing data
        """
           Shows and displays a given line, with start and stop boundaries.
        """
        # TLine = self.len_line/self.f #@unused
        Offset = nb_line * self.len_line

        plot_time_series = self.t[
            Offset + int(Start / self.f) : Offset + int(Stop * self.f)
        ]
        plot_signal = self.tmp[Offset + int(Start / self.f) : int(Stop * self.f)]
        # @todo .. what happens if no EnvHil ?
        plot_enveloppe = self.EnvHil[Offset + int(Start / self.f) : int(Stop * self.f)]

        plot_title = "Detail of " + self.iD + " - acq. #: " + str(self.N) + ", between "
        plot_title += (
            str(Start) + " and " + str(Stop) + " (line #" + str(nb_line) + ")."
        )

        plt.figure(figsize=(15, 5))
        plt.plot(plot_time_series, plot_signal, "b-")
        plt.plot(plot_time_series, plot_enveloppe, "y-")
        plt.title(plot_title)
        plt.xlabel("Time in us")
        plt.tight_layout()

        file_name = "images/detail_" + self.iD + "-" + str(self.N) + "-"
        file_name += str(Start) + "-" + str(Stop) + "-line" + str(nb_line) + ".jpg"
        plt.savefig(file_name)
        if self.show_images:
            plt.show()

    def make_filtered(self, original_image):
        """
           Takes the image, then filters it around self.fPiezo .
        """
        filtered_image = []
        fft_image_filtered = []
        if len(original_image):
            num_lines, length_lines = np.shape(original_image)
            f_array = [X * self.f / length_lines for X in range(length_lines)]
            for k in range(num_lines):  # number of images
                fft_single_line = np.fft.fft(original_image[k])
                fft_image_filtered.append(fft_single_line)
                for p in range(int(len(fft_single_line) / 2) + 1):
                    f_min = 1000.0 * self.fPiezo * 0.7
                    f_max = 1000.0 * self.fPiezo * 1.27
                    if f_array[p] > f_max or f_array[p] < f_min:
                        fft_single_line[p] = 0
                        fft_single_line[-p] = 0
                filtered_image.append(np.real(np.fft.ifft(fft_single_line)))
        return filtered_image, fft_image_filtered

    def make_spectrum(self, img):
        """
           Creates a 2D array spectrum from 2D image.
        """
        spectrum = []
        if len(img):
            n_lines, len_lines = np.shape(img)
            self.FFT_x = [
                X * self.f / len_lines for X in range(len_lines)
            ]  # @usuned, why?
            for k in range(n_lines):
                fft_single_line = np.fft.fft(img[k])
                spectrum.append(fft_single_line[0 : n_lines / 2])

            plt.figure(figsize=(15, 10))
            plt.imshow(
                np.sqrt(np.abs(spectrum)),
                extent=[0, 1000.0 * self.f / 2, n_lines, 0],
                cmap="hsv",
                aspect=30.0,
                interpolation="nearest",
            )

            plt.axvline(x=(1000 * self.fPiezo * 1.27), linewidth=4, color="b")
            plt.axvline(x=(1000 * self.fPiezo * 0.7), linewidth=4, color="b")

            plt.xlabel("Frequency (kHz)")
            plt.ylabel("Lines #")

            plt.title(self.create_title_text())
            plt.tight_layout()

            file_name = "images/Spectrum_" + self.iD + "-" + str(self.N) + ".jpg"
            plt.savefig(file_name)
            img_desc = self.create_title_text().replace("\n", ". ")
            tag_image(file_name, "matty," + self.piezo, self.iD, "FFT", img_desc)
        else:
            print("2D Array not created yet")

        return np.abs(spectrum)

    def create_title_text(self):
        """
           Creates a string to title images with appropriate acquisition details
        """
        title_text = (
            "Experiment: "
            + self.iD
            + "-"
            + str(self.N)
            + "\nDuration: "
            + str(self.Duration)
        )
        title_text += "us (" + str(self.parameters["LengthAcq"]) + " - "
        title_text += str(self.parameters["DeltaAcq"]) + "), for " + str(self.Nacq)
        title_text += " repeats "
        title_text += "each " + str(self.parameters["PeriodAcq_Real"] / 1000.0) + "us\n"
        title_text += (
            "Fech = "
            + str(self.f)
            + "Msps, total of "
            + str(float(self.f) * self.Duration)
        )
        title_text += " pts per line, Nacq = " + str(self.Nacq) + "\n"
        title_text += self.experiment["description"] + ", probe: "
        title_text += self.piezo + ", target = " + self.experiment["target"] + "\n"
        title_text += "Timestamp = " + str(self.metatags["time"])
        return title_text


def config_from_txt(UN0RICK, file_path):
    """
    Used with -f to get inputs from file.
    """
    ConfigText = {}
    with open(file_path) as fp:
        line = fp.readline()
        while line:
            line = line.replace("* ", "").replace(": ", ":")
            line = re.sub("[\(\[].*?[\)\]]", "", line).strip()
            if len(line):
                keys = line.split(":")
                if len(keys) == 2:
                    if keys[1].isdigit():
                        ConfigText[keys[0]] = float(keys[1])
                    else:
                        ConfigText[keys[0]] = keys[1]
            line = fp.readline()

    if "bandwidthpiezo" in list(ConfigText.keys()):
        UN0RICK.Bandwidth = ConfigText["bandwidthpiezo"]
    if "fpiezo" in list(ConfigText.keys()):
        UN0RICK.fPiezo = ConfigText["fpiezo"]
    if "description" in list(ConfigText.keys()):
        UN0RICK.JSON["experiment"]["description"] = ConfigText["description"]
    if "target" in list(ConfigText.keys()):
        UN0RICK.JSON["experiment"]["target"] = ConfigText["target"]
    if "probe" in list(ConfigText.keys()):
        UN0RICK.JSON["experiment"]["probe"] = ConfigText["probe"]
    if "freq" in list(ConfigText.keys()):
        UN0RICK.set_msps(int(ConfigText["freq"]))
    if "nlines" in list(ConfigText.keys()):
        UN0RICK.set_acquisition_number_lines(int(ConfigText["nlines"]))
    if "interlinedelay" in list(ConfigText.keys()):
        ILD = ConfigText["interlinedelay"] * 1000
        UN0RICK.set_period_between_acqs(int(ILD))
    if "gain" in list(ConfigText.keys()):
        g1, g2 = ConfigText["gain"].split(",")
        TGCC = UN0RICK.create_tgc_curve(int(g1), int(g2), True)[0]
        UN0RICK.set_tgc_curve(TGCC)
    if "acqtiming" in list(ConfigText.keys()):
        t1, t2 = ConfigText["acqtiming"].split(",")
        UN0RICK.set_timings(200, 100, 1000, int(t1), int(t2))

    print(ConfigText)
    UN0RICK.JSON["ConfigText"] = ConfigText
    return UN0RICK


if __name__ == "__main__":
    print("Loaded!")

    if len(sys.argv) > 1:
        if (
            (sys.argv[1] == "-f")
            and (len(sys.argv) == 3)
            and (os.path.exists(sys.argv[2]))
        ):
            print("File exists - OK")
            UN0RICK = SpiConnector()
            UN0RICK.set_multi_lines(True)
            UN0RICK.set_acquisition_number_lines(15)
            UN0RICK = config_from_txt(UN0RICK, sys.argv[2])
            UN0RICK.JSON["data"] = UN0RICK.do_acquisition()

        if "test" in sys.argv[1]:
            UN0RICK = SpiConnector()
            UN0RICK.test_spi(3)

        if "single" in sys.argv[1]:
            UN0RICK = SpiConnector()
            UN0RICK.test_spi(3)
            UN0RICK.set_HV(1000)
            UN0RICK.set_hilo(1)
            TGCC = UN0RICK.create_tgc_curve(600, 600, True)[
                0
            ]  # Gain: linear, 10mV to 980mV
            UN0RICK.set_tgc_curve(TGCC)  # We then apply the curve
            UN0RICK.set_tgc_constant(600)  # Sets in mV from 0 to 1000
            UN0RICK.set_period_between_acqs(int(2500000))  # Setting 2.5ms between shots
            UN0RICK.JSON["N"] = 1  # Experiment ID of the day
            UN0RICK.set_multi_lines(False)  # Single acquisition
            UN0RICK.set_acquisition_number_lines(1)  # Setting the number of lines (1)
            UN0RICK.set_msps(0)  # Sampling speed setting
            A = UN0RICK.set_timings(
                200, 10, 200, 2000, 5000, 110000
            )  # Settings the series of pulses
            UN0RICK.JSON[
                "data"
            ] = UN0RICK.do_acquisition()  # Doing the acquisition and saves
            UN0RICK.set_led_rgb(0, 0, 0)

        if "multi" in sys.argv[1]:
            UN0RICK = SpiConnector()
            UN0RICK.test_spi(3)
            UN0RICK.JSON["N"] = 1  # Experiment ID
            UN0RICK.create_tgc_curve(600, 900, False)  # Gain: expo, 300mV to 900mv
            # UN0RICK.set_tgc_curve(TGCC)                           # We then apply the curve
            UN0RICK.set_period_between_acqs(int(2500000))  # Setting 2.5ms between lines
            UN0RICK.set_multi_lines(True)  # Multi lines acquisition
            UN0RICK.set_acquisition_number_lines(10)  # Setting the number of lines (3)
            UN0RICK.set_msps(0)  # Sampling speed setting
            A = UN0RICK.set_timings(
                200, 100, 1000, 2000, 100000
            )  # Settings the series of pulses
            UN0RICK.JSON[
                "data"
            ] = UN0RICK.do_acquisition()  # Doing the acquisition and saves

        if "process" in sys.argv[1]:
            make_clean("./")
            for MyDataFile in os.listdir("./data/"):
                if MyDataFile.endswith(".json"):
                    print(MyDataFile)
                    y = DataToJson()
                    y.show_images = False
                    y.json_proccess("./data/" + MyDataFile)
                    y.create_fft()
                    y.save_npz()
                    y.make_image()

        if "loop" in sys.argv[1]:
            UN0RICK = SpiConnector()
            UN0RICK.set_multi_lines(True)  # Multi lines acquisition
            UN0RICK.set_acquisition_number_lines(2)  # Setting the number of lines
            UN0RICK.set_msps(3)  # Acquisition Freq
            A = UN0RICK.set_timings(200, 100, 2000, 5000, 200000)  # TODO: check aqq param. Looping on triggers
            while True:
                UN0RICK.write_fpga(0xEA, 0x01)  # trigs
                time.sleep(50.0 / 1000.0)  # Waits 50ms between shots
