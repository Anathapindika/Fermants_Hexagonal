# -*- coding: utf-8 -*-
"""
Created on Mon Apr 25 01:50:46 2016

@author: Anathapindika
"""

import numpy as np
import matplotlib.pyplot as plt

field = np.loadtxt("field.txt")
#field2 = np.zeros_like(field)
#for i in range(np.shape(field)[0]):
#    for j in range(np.shape(field)[0]):
#        if field[i,j]>0:
#            field2[i,j] = 1
#field /= field
plt.imshow(field, interpolation="None")
plt.show()