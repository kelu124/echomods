#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -------------------------
# (c) kelu124
# cc-by-sa/4.0/
# -------------------------

'''Description: XX.'''

__author__      = "kelu124"
__copyright__   = "Copyright 2016, Kelu124"
__license__ 	= "cc-by-sa/4.0/"

import sys
import numpy as np
from operator import itemgetter, attrgetter
import Image
from math import *
import math
import scipy.misc

# Prend en argument un fichier au bon format echopen (CSV enrichi)


from numpy import genfromtxt
my_data = genfromtxt('tmp_1.csv', delimiter=';')
print my_data
scipy.misc.imsave('tmp_1.jpg', my_data)
