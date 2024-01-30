#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jun 11 18:27:13 2020

@author: Hesham ElAbd
@description: A model'
"""
#%% Load the modules
import tensorflow as tf 
import numpy as np
#%% Model_ARCH_ONE


def getModelDetailsAsString(model):
    strRet = ""
    for idx, item in enumerate(model.layers):
        the_config = item.get_config()
        the_units = 0
        the_activation= ""
        if "units" in the_config:
            the_units=the_config['units']
        if "activation" in the_config:
            the_activation=the_config['activation']
        strRet += "(%d-%s)" % (the_units,the_activation) 
    return strRet
    

def getModels(input_layer_length=1024, model_by_index = [0]):
    models_tmp = getAllModels(input_layer_length)
    models_ret = []
    for i in model_by_index:
        models_ret.append(models_tmp[i])
    return models_ret


def getAllModels(input_layer_length=1024):
    models = []
    
    models.append(
    tf.keras.models.Sequential([
        tf.keras.layers.Dense(9,input_shape=(input_layer_length,),activation="relu"),
        tf.keras.layers.Dense(6,activation="relu"),
        tf.keras.layers.Dense(1,activation="sigmoid"),
        ])
    )
    models.append(
    tf.keras.models.Sequential([
        tf.keras.layers.Dense(3,input_shape=(input_layer_length,),activation="relu"),
        tf.keras.layers.Dense(4,activation="relu"),
        tf.keras.layers.Dense(4,activation="relu"),
        tf.keras.layers.Dense(4,activation="relu"),
        tf.keras.layers.Dense(1,activation="sigmoid"),
        ])
    )
    models.append(
    tf.keras.models.Sequential([
        tf.keras.layers.Dense(3,input_shape=(input_layer_length,),activation="relu"),
        tf.keras.layers.Dense(12,activation="relu"),
        tf.keras.layers.Dropout(rate=0.6),
        tf.keras.layers.Dense(8,activation="relu"),
        tf.keras.layers.Dropout(rate=0.4),
        tf.keras.layers.Dense(4,activation="relu"),
        tf.keras.layers.Dense(1,activation="sigmoid"),
        ])
    )
    models.append(
    tf.keras.models.Sequential([
        tf.keras.layers.Dense(3,input_shape=(input_layer_length,),activation="relu"),
        tf.keras.layers.Dropout(rate=0.3),
        tf.keras.layers.Dense(12,activation="relu"),
        tf.keras.layers.Dropout(rate=0.6),
        tf.keras.layers.Dense(8,activation="relu"),
        tf.keras.layers.Dropout(rate=0.3),
        tf.keras.layers.Dense(4,activation="relu"),
        tf.keras.layers.Dense(1,activation="sigmoid"),
        ])
    )
    models.append(
    tf.keras.models.Sequential([
        tf.keras.layers.Dense(3,input_shape=(input_layer_length,),activation="relu"),
        tf.keras.layers.Dense(1,activation="sigmoid"),
        ])
    )
    models.append(
    tf.keras.models.Sequential([
        tf.keras.layers.Dense(1,input_shape=(input_layer_length,), activation="sigmoid"),
        ])
    )
    return models

    #%% define compilation models
    """
    # Usages:: MODELNAME.compile(...)
    Adding Three metrics:
    1-Precision
    2-Recall
    3-AUC
    """

def compileModel(model , optimizer = "Adam"):
    
    model.compile(
        loss=tf.keras.losses.binary_crossentropy,
        optimizer=optimizer,
        metrics=['accuracy',
                 tf.keras.metrics.Precision(),
                 tf.keras.metrics.Recall(),
                 tf.keras.metrics.AUC()]
        )
    return model

'''
OPTIMIZER
https://www.tensorflow.org/api_docs/python/tf/keras/optimizers

class Adadelta: Optimizer that implements the Adadelta algorithm.
class Adagrad: Optimizer that implements the Adagrad algorithm.
class Adam: Optimizer that implements the Adam algorithm.
class Adamax: Optimizer that implements the Adamax algorithm.
class Ftrl: Optimizer that implements the FTRL algorithm.
class Nadam: Optimizer that implements the NAdam algorithm.
class Optimizer: Updated base class for optimizers.
class RMSprop: Optimizer that implements the RMSprop algorithm.
class SGD: Stochastic gradient descent and momentum optimizer.
'''

