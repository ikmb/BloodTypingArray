#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Jun 12 17:52:54 2020

@author: mwittig
"""
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
#import matplotlib as mpl
from matplotlib.lines import Line2D


# scores between these two values are doubtful and treated as NA
LOACAL_PREDICTION_LOWER_THRESHOLD = 0.33
LOACAL_PREDICTION_UPPER_THRESHOLD = 0.67

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

def getAllWithScoreLower(inX,inY,pred_value,thresh=LOACAL_PREDICTION_LOWER_THRESHOLD):
    x = []
    y = []
    for i in range(len(inX)):
        if (pred_value[i] < thresh):
            x.append(inX[i])
            y.append(inY[i])
    return x,y

def getAllWithScoreGreater(inX,inY,pred_value,thresh=LOACAL_PREDICTION_UPPER_THRESHOLD):
    x = []
    y = []
    for i in range(len(inX)):
        if (pred_value[i] > thresh):
            x.append(inX[i])
            y.append(inY[i])
    return x,y

def predicted_wrong_false(inX,inY,classes,pred_value,thresh=LOACAL_PREDICTION_LOWER_THRESHOLD):
    x = []
    y = []
    i = 0;
    for act in classes:
        if (act == 1 and pred_value[i] < thresh):
            x.append(inX[i])
            y.append(inY[i])
        i += 1
    return x,y

def predicted_wrong_true(inX,inY,classes,pred_value,thresh=LOACAL_PREDICTION_UPPER_THRESHOLD):
    x = []
    y = []
    i = 0;
    for act in classes:
        if (act == 0 and pred_value[i] > thresh):
            x.append(inX[i])
            y.append(inY[i])
        i += 1
    return x,y

def predicted_doubtful(inX,inY,classes,pred_value,thresh_l=LOACAL_PREDICTION_LOWER_THRESHOLD,thresh_u=LOACAL_PREDICTION_UPPER_THRESHOLD):
    x = []
    y = []
    i = 0;
    for act in classes:
        if (pred_value[i] >= thresh_l and pred_value[i] <= thresh_u):
            x.append(inX[i])
            y.append(inY[i])
        i += 1
    return x,y



def draw_clusterplot(train,test,predicted,snp_name,outfile=""):
    custom_lines = [Line2D([0], [0], color='lightgrey', lw=4),
                Line2D([0], [0], color='grey', lw=4),
                Line2D([0], [0], color='green', lw=4),
                Line2D([0], [0], color='blue', lw=4),
                Line2D([0], [0], color='red', lw=4),
                Line2D([0], [0], color='orange', lw=4),
                Line2D([0], [0], color='purple', lw=4)]

    test_size = len(predicted[:,0])
    wrong_predicted = 0
    not_predicted = 0
    plt.figure()
    
    px,py = get_all_of_class(train.x,train.y,train.classes,0)
    plt.plot(px, py, 'lightgrey',marker='o',linestyle='')
    max_x=max(0,max(px))
    max_y=max(0,max(py))
    px,py = get_all_of_class(train.x,train.y,train.classes,1)
    plt.plot(px, py, 'grey',marker='o',linestyle='')
    max_x=max(max_x,max(px))
    max_y=max(max_y,max(py))
    
    px,py = get_all_of_class(test.x,test.y,test.classes,0)
    plt.plot(px, py, 'green',marker='+',linestyle='')
    max_x=max(max_x,max(px))
    max_y=max(max_y,max(py))
    px,py = get_all_of_class(test.x,test.y,test.classes,1)
    plt.plot(px, py, 'blue',marker='+',linestyle='')
    max_x=max(max_x,max(px))
    max_y=max(max_y,max(py))
    
    px,py = predicted_wrong_false(test.x,test.y,test.classes,predicted)
    if( len(px) > 0):
        plt.plot(px, py, 'red',marker='o',linestyle='')
        wrong_predicted += len(px) 
    px,py = predicted_wrong_true(test.x,test.y,test.classes,predicted)
    if( len(px) > 0):
        plt.plot(px, py, 'orange',marker='o',linestyle='')
        wrong_predicted += len(px) 
    px,py = predicted_doubtful(test.x,test.y,test.classes,predicted)
    if( len(px) > 0):
        plt.plot(px, py, 'purple',marker='o',linestyle='')
        not_predicted += len(px) 
    
    plt.ylim(bottom=0,top=max(max_x,max_y)*1.1)
    plt.xlim(left=0,right=max(max_x,max_y)*1.1)
    plt.title("%s\ncorrect %1.2f%%, n.a. %1.2f%%" % (snp_name,(test_size-wrong_predicted)/test_size*100,(not_predicted)/test_size*100))
    plt.legend(custom_lines, ['train FALSE', 'train TRUE', 'test FALSE', 'test TRUE', 'pred wrong F', 'pred wrong T', 'pred failed'])
    #plt.savefig("/home/mwittig/ramDisk/test.png")
    if outfile != "":
        plt.savefig("%s_%s.png" % (outfile,snp_name))
    else:
        plt.show()
    return test_size, wrong_predicted, not_predicted


def plot_result(train_x,train_y,test_x,test_y,pred_result,snp_id_filter,outfile=""):
    snp_count = int(len(train_x[0])/2)
    for idx in range(snp_count):
        xIdx = idx
        yIdx = int(xIdx+snp_count)
        #print(xIdx,yIdx)
        train=pd.DataFrame({'x': train_x[:,xIdx], 'y': train_x[:,yIdx], 'classes': train_y })
        test=pd.DataFrame({'x': test_x[:,xIdx], 'y': test_x[:,yIdx], 'classes': test_y })
    
        test_size, wrong_predicted, not_predicted = draw_clusterplot(train,test,np.array(pred_result.tolist()),snp_id_filter.iloc[idx,0],outfile)
    plt.figure()
    plt.hist(pred_result,bins=20)
    plt.title("Distribution of predicted values")
    if outfile != "":
        plt.savefig("%s_distribution.png" % (outfile))
    else:
        plt.show()
    return test_size, wrong_predicted, not_predicted
# plot
# Dataset:
    

