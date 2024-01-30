#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu May  7 09:53:21 2020

@author: hisham
"""
## load the modules
import tensorflow as tf 
import numpy as np
from sklearn.model_selection import train_test_split
## First let's take the average
zscores_mn_array_avg=np.mean(zscores_mn_array,axis=-1)
numerical_labels=np.array(curated_MN_phenotypic_data.MN,dtype=np.float64)
## split the data into training and validation
train_x,test_x,train_y,test_y=train_test_split(zscores_mn_array_avg,
                                               numerical_labels,test_size=0.2)
## define the model
model_1_mn=tf.keras.models.Sequential([
    tf.keras.layers.Dense(9,input_shape=(513,),activation="relu"),
    tf.keras.layers.Dense(6,activation="relu"),
    tf.keras.layers.Dense(6,activation="relu"),
    tf.keras.layers.Dense(6,activation="relu"),
    tf.keras.layers.Dense(6,activation="relu"),
    tf.keras.layers.Dense(3),
    ])
## compile the models
model_1_mn.compile(
    loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
    optimizer="adam",
    metrics=['accuracy'])
## fitting the model
model_1_mn.fit(x=train_x,y=train_y,validation_data=(test_x,test_y),
               batch_size=32, epochs=100)
model_one_performance=pd.DataFrame(model_1_mn.history.history)
## write the results to the report 
model_one_performance.to_csv("Performance_of_MN_locus_trial_one.csv")
### ********************************************************************* ####
#### Stacked Model
zscores_mn_array_concat=zscores_mn_array.reshape(zscores_mn_array.shape[0],-1)
numerical_labels=np.array(curated_MN_phenotypic_data.MN,dtype=np.float64)
## split the data into training and validation
train_x,test_x,train_y,test_y=train_test_split(zscores_mn_array_concat,
                                               numerical_labels,test_size=0.2)
## define the model
model_2_mn=tf.keras.models.Sequential([
    tf.keras.layers.Dense(9,input_shape=(1026,),activation="relu"),
    tf.keras.layers.Dense(6,activation="relu"),
    tf.keras.layers.Dense(3),
    ])
## compile the model
model_2_mn.compile(
    loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
    optimizer="adam",
    metrics=['accuracy'])
## fitting the model
model_2_mn.fit(x=train_x,y=train_y,validation_data=(test_x,test_y),
               batch_size=32, epochs=100)
model_two_performance=pd.DataFrame(model_2_mn.history.history)
## write the results to the report 
model_two_performance.to_csv("Performance_of_MN_locus_trial_two.csv")

## testing the stability of the signal 
signals=[]
for _ in range(50):
    train_x,test_x,train_y,test_y=train_test_split(zscores_mn_array_concat,
                                               numerical_labels,test_size=0.2)
    model_2_mn=tf.keras.models.Sequential([
    tf.keras.layers.Dense(9,input_shape=(1026,),activation="relu"),
    tf.keras.layers.Dense(6,activation="relu"),
    tf.keras.layers.Dense(3),
    ])
    ## compile the model
    model_2_mn.compile(
        loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
        optimizer="adam",
        metrics=['accuracy'])
    ## fitting the model
    model_2_mn.fit(x=train_x,y=train_y,validation_data=(test_x,test_y),
               batch_size=32, epochs=100)
    signals.append(max(model_2_mn.history.history['val_accuracy']))    
sing_30=signals[:30]
sst=pd.DataFrame({'signal':sing_30})
sst.to_csv("SignalStabilityResults.csv",index=False)
##############################################################################
zscores_he_array_concat=zscores_he_array.reshape(zscores_he_array.shape[0],-1)
numerical_labels=np.array(curated_HE_phenotypic_data.He,dtype=np.float64)
## split the data into training and validation
train_x,test_x,train_y,test_y=train_test_split(zscores_he_array_concat,
                                               numerical_labels,test_size=0.2)
## define the model
model_he=tf.keras.models.Sequential([
    tf.keras.layers.Dense(6,input_shape=(1026,),activation="relu"),
    tf.keras.layers.Dense(3,activation="relu"),
    tf.keras.layers.Dense(1,activation="sigmoid"),
    ])
## compile the model
model_he.compile(
    loss=tf.keras.losses.BinaryCrossentropy(from_logits=True),
    optimizer="adam",
    metrics=['accuracy'])
## fitting the model
model_he.fit(x=train_x,y=train_y,validation_data=(test_x,test_y),
               batch_size=32, epochs=100)
model_he_performance=pd.DataFrame(model_he.history.history)
## write the results to the report 
model_he_performance.to_csv("Performance_of_he_locus_trial_one.csv")
##*************************************************************************##
# Test the stability of signal 
singals=[]
frequ_base=[]
for idx in range(30):
    train_x,test_x,train_y,test_y=train_test_split(zscores_he_array_concat,
                                               numerical_labels,test_size=0.2)
    ## define the model
    model_he=tf.keras.models.Sequential([
    tf.keras.layers.Dense(6,input_shape=(1026,),activation="relu"),
    tf.keras.layers.Dense(3,activation="relu"),
    tf.keras.layers.Dense(1,activation="sigmoid"),
    ])
    ## compile the model
    model_he.compile(
    loss=tf.keras.losses.BinaryCrossentropy(from_logits=True),
    optimizer="adam",
    metrics=['accuracy'])
    ## fitting the model
    model_he.fit(x=train_x,y=train_y,validation_data=(test_x,test_y),
               batch_size=32, epochs=100,verbose=2)
    singals.append(max(model_he.history.history['val_accuracy']))
    frequ_base.append(sum(test_y==0)/len(test_y))
    print(f'current iteration is {idx}')
    idx+=1

stability_testing=pd.DataFrame({'signal':singals,'base':frequ_base})
stability_testing.to_csv("ModelPerformance_relative_to_base.csv")
###############################################################################
#### Stacked Model
zscores_SS_array_concat=zscores_SS_array.reshape(zscores_SS_array.shape[0],-1)
numerical_labels=np.array(curated_SS_phenotypic_data.Ss,dtype=np.float64)
## split the data into training and validation
train_x,test_x,train_y,test_y=train_test_split(zscores_SS_array_concat,
                                               numerical_labels,test_size=0.2)
## define the model
model_ss=tf.keras.models.Sequential([
    tf.keras.layers.Dense(9,input_shape=(2648,),activation="relu"),
    tf.keras.layers.Dense(6,activation="relu"),
    tf.keras.layers.Dense(3),
    ])
## compile the model
model_ss.compile(
    loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
    optimizer="adam",
    metrics=['accuracy'])
## fitting the model
model_ss.fit(x=train_x,y=train_y,validation_data=(test_x,test_y),
               batch_size=32, epochs=100)
model_ss=pd.DataFrame(model_ss.history.history)
## write the results to the report 
modeel_ss.to_csv("Performance_of_SS_concat_model.csv")

## testing the stability of the signal 
signals=[]
for _ in range(50):
    train_x,test_x,train_y,test_y=train_test_split(zscores_mn_array_concat,
                                               numerical_labels,test_size=0.2)
    model_2_mn=tf.keras.models.Sequential([
    tf.keras.layers.Dense(9,input_shape=(1026,),activation="relu"),
    tf.keras.layers.Dense(6,activation="relu"),
    tf.keras.layers.Dense(3),
    ])
    ## compile the model
    model_2_mn.compile(
        loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
        optimizer="adam",
        metrics=['accuracy'])
    ## fitting the model
    model_2_mn.fit(x=train_x,y=train_y,validation_data=(test_x,test_y),
               batch_size=32, epochs=100)
    signals.append(max(model_2_mn.history.history['val_accuracy']))    
sing_30=signals[:30]
sst=pd.DataFrame({'signal':sing_30})
sst.to_csv("SignalStabilityResults.csv",index=False)







