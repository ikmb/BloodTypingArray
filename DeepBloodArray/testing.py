#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Jun 12 17:52:54 2020

@author: mwittig
"""
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from matplotlib.lines import Line2D

# Dataset:
train=pd.DataFrame({'x': train_x[:,0], 'y': train_x[:,1], 'classes': train_y })

test=pd.DataFrame({'x': test_x[:,0], 'y': test_x[:,1], 'classes': test_y })


# Returns a list of indices for which teh class == class_value
def get_all_of_class(inX,inY,classes,class_value):
    x = []
    y = []
    i = 0;
    for act in classes:
        if (act == class_value):
            x.append(inX[i])
            y.append(inY[i])
        i += 1
    return x,y

def predicted_wrong_false(inX,inY,classes,pred_value,thresh=0.33):
    x = []
    y = []
    i = 0;
    for act in classes:
        if (act == 1 and pred_value[i] < thresh):
            x.append(inX[i])
            y.append(inY[i])
        i += 1
    return x,y

def predicted_wrong_true(inX,inY,classes,pred_value,thresh=0.66):
    x = []
    y = []
    i = 0;
    for act in classes:
        if (act == 0 and pred_value[i] > thresh):
            x.append(inX[i])
            y.append(inY[i])
        i += 1
    return x,y

def predicted_doubtful(inX,inY,classes,pred_value,thresh_l=0.33,thresh_u=0.66):
    x = []
    y = []
    i = 0;
    for act in classes:
        if (pred_value[i] >= thresh_l and pred_value[i] <= thresh_u):
            x.append(inX[i])
            y.append(inY[i])
        i += 1
    return x,y



def demo(train,test,predicted):
    custom_lines = [Line2D([0], [0], color='lightgrey', lw=4),
                Line2D([0], [0], color='grey', lw=4),
                Line2D([0], [0], color='green', lw=4),
                Line2D([0], [0], color='blue', lw=4),
                Line2D([0], [0], color='red', lw=4),
                Line2D([0], [0], color='orange', lw=4),
                Line2D([0], [0], color='purple', lw=4)]

    plt.figure()
    px,py = get_all_of_class(train.x,train.y,train.classes,0)
    plt.plot(px, py, 'lightgrey',marker='o',linestyle='')
    px,py = get_all_of_class(train.x,train.y,train.classes,1)
    plt.plot(px, py, 'grey',marker='o',linestyle='')

    px,py = get_all_of_class(test.x,test.y,test.classes,0)
    plt.plot(px, py, 'green',marker='+',linestyle='')
    px,py = get_all_of_class(test.x,test.y,test.classes,1)
    plt.plot(px, py, 'blue',marker='+',linestyle='')
    
    px,py = predicted_wrong_false(test.x,test.y,test.classes,predicted)
    if( len(px) > 0):
        plt.plot(px, py, 'red',marker='o',linestyle='')
    px,py = predicted_wrong_true(test.x,test.y,test.classes,predicted)
    if( len(px) > 0):
        plt.plot(px, py, 'orange',marker='o',linestyle='')
    px,py = predicted_doubtful(test.x,test.y,test.classes,predicted)
    if( len(px) > 0):
        plt.plot(px, py, 'purple',marker='o',linestyle='')
    plt.legend(custom_lines, ['train FALSE', 'train TRUE', 'test FALSE', 'test TRUE', 'pred wrong F', 'pred wrong T', 'pred failed'])
    plt.show()



# plot
demo(train,test,np.array(pred_result.tolist()))

