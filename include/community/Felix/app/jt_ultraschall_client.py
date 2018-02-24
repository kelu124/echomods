# -*- coding: utf-8 -*-
"""
Created on Thu Feb 15 17:01:16 2018

@author: twiefel
"""

import matplotlib.pyplot as plt
import numpy as np
import requests
import copy
from cPickle import loads
class UltraschallCient:
    def __init__(self):
        self.fig = plt.figure(figsize=(15,5))
        plt.ion()
        plt.show()
        pass
        
        
    def fast_image(self):
        filename = "live_image"
        url = "http://raspberrypi.local:8000"
        
        #if testing with a local dummy:
        #url = "http://localhost:8000"
        
        r = requests.get(url,stream=True)
        #print r.content
        data = loads(r.content)
        #print type(data)
        #print len(data)
        #print data[0:10]
        Bytes = np.fromstring(data, dtype = '<i4')

        #Bytes = np.fromfile(filename+".dat", dtype = '<i4')
        bytes = Bytes[:-1]
    
        #ADC2_GPIO = [7, 8,9,10,11,23,24,25]
        #we want to have the bits from 7 to 8 and 23 to 25, so lets do som bit shifting magic...
        sbytes = copy.deepcopy(bytes)
        sbytes = np.right_shift(bytes,7) #so remove right bits below 7
        sbytes = np.bitwise_and(sbytes,31) #31 == 11111, so we keep the 5 bits on the right
    
        bbytes = copy.deepcopy(bytes)
        bbytes = np.right_shift(bbytes,18) #so remove right bits below 18 and not 23, because we need 5 bits for sbytes
        bbytes = np.bitwise_and(bbytes,255) # 255 == 11111111 , 255 should also be ok...
    
        mbytes = sbytes+bbytes #concat the small 5 bits with the big 3 bits, et voila, we have an integer

        M = mbytes
    
        #get sample frequency, duration and the time
        n = len(bytes)
        Duration = Bytes[-1]
        Fech = n*1.0/(Duration*1e-9)/1e6 # 1e-9 because Duration is in ns, 1e6 because Fech in Msps
        print "Duration:",Duration
        print "Fech:",Fech
        t = range(n)
        for k in range(n):
            t[k] = 1.0*t[k]/Fech
        #print t[:10]
    
        rawSig = M
        #rawSig = M - np.average(M)
        #print len(rawSig)
        
        T = t
        #print T[:10]
        
        repeat_size = 400 #repeat size
        sample_size = 5000 #sample size
    
        FH = rawSig
    
        #reshape envelope of the signal
        tableData = np.asarray(FH).reshape((repeat_size,sample_size))
        
        #IndexEmpty = 20 #where does this number come from?
        IndexLine = 104 #where does this number come from?
        
        ExLine = tableData[IndexLine]
        #ExLineRaw = tableData[IndexLine]
        
        #clear the figure
        self.fig.clear()
        
        #plot the index line        
        plt.subplot(211)
        plot_depth=3000

        plt.plot(T[0:plot_depth],ExLine[0:plot_depth],"b", label='Enveloppe of the signal')
        #plt.xticks(range(-400,plot_depth), rotation='vertical')
        plt.title("Details of a line from "+filename.split("/")[-1])
        plt.xlabel("Time in uS")
        plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)
        
        
        #add an offset to the image
        #get average value
        Val = np.average(tableData)
        Offset = 400
        Zeroes = np.zeros((repeat_size,Offset))+Val
        BigTable = []
        BigTable = np.append(Zeroes, tableData, axis=1)
        
        #plot the image        
        plt.subplot(212)
        plt.imshow((abs(BigTable)), aspect='auto')
        plt.title("Image of "+filename.split("/")[-1])
        plt.axhline(IndexLine, color='r', linestyle='--')

        #show it
        plt.draw()
        plt.pause(0.00001)

        
    
if __name__ == "__main__":
    uc = UltraschallCient()
    #uc.fast_image("hannes28")
    
    while True:
        uc.fast_image()