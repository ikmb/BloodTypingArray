#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Jun 10 12:54:53 2020

@author: mwittig
"""
#%%
import sys

import pandas as pd
import numpy as np 
import tensorflow as tf
import os
import getpass
from sklearn.model_selection import train_test_split
from argparse import ArgumentParser

THEROOTPATH = os.path.abspath(os.path.dirname(__file__))
sys.path.append(THEROOTPATH)

import plotting as myplot
import loadEvoker as evk
import model_zoo as zoo

parser = ArgumentParser()
parser.add_argument("-o", "--output", dest="Outpath", default="/home/mwittig/ramDisk/", help='The output directory for models and pictures.')
args = parser.parse_args()
#THEROOTPATH="/home/mwittig/data/Genotypisierung/Haemocarta/bloodArray/publication/data_20230911/TensorFlow"
THESAVEPATHISHERE=args.Outpath


def reformatTablesForTraining(curated_ordered_array,shrinked_phenotypic_table,transformation='Cartesian',THECLASSTOFIND=''):
    the_norm_values = curated_ordered_array[:, :, 0] + curated_ordered_array[:, :, 1]
    the_teta_values = curated_ordered_array[:, :, 1] / the_norm_values
    input_array = np.concatenate([the_norm_values, the_teta_values], axis=-1)
    if transformation == 'Cartesian':
        print("using intensities in Cartesian coordinates")
        input_array = np.concatenate([curated_ordered_array[:, :, 0], curated_ordered_array[:, :, 1]], axis=-1)
    elif transformation == 'Polar':
        print("using intensities in Polar coordinates")
    else:
        raise Exception("Please specify data transformation. Either Cartesian or Polar")
    ## reshape the 3D object to a 2D object with always intensity 1 as even and intensity 2 as odd row
    input_array_concat = input_array.reshape(input_array.shape[0], -1)
    phenotype_column_idx = evk.getRelevantColumnIndex(THECLASSTOFIND, shrinked_phenotypic_table)
    numerical_labels = np.array(shrinked_phenotypic_table.iloc[:, phenotype_column_idx], dtype=np.float64)
    return input_array_concat,phenotype_column_idx,numerical_labels

def trainAndTest(THECLASSTOFIND,NUMBEROF_EPOCHS=100,make_plot=False,
                 outfile=os.path.join(THESAVEPATHISHERE,"Performance.csv"),transformation='Cartesian',
                 MODELS_tO_USE=[0,1,2,3,4],
                 OPTIMIZER_TO_USE=['Adadelta','Adagrad','Adam','Adamax','Ftrl','Nadam','RMSprop','SGD'],
                 MYWORKINGPATH=".",
                 MYSAVEPATH=""):
    """
    This is the main function for running a blood group training with tensor Flow.5 Model Architectures and 7 Optimizers are available. It is important to provide the right infrastructure by different types of inpurt files. These are:
      Antigen_Evoker.csv: Has a list of Evoker file set for every Antigen
      Curated_Phenotypes_20200724.csv: Has all the Antigen-sample correlations.
      consider_those.csv: contains the relevant SNPs for the different Antigens
    This function can run multiple models and/or optimizers by one call
      
    Available Models (Layer setup):
        0 - (9-relu)(6-relu)(1-sigmoid)
        1 - (3-relu)(4-relu)(4-relu)(4-relu)(1-sigmoid)
        2 - (3-relu)(12-relu)(Dropout(rate=0.6))(8-relu)(Dropout(rate=0.4))(4-relu)(1-sigmoid)
        3 - (3-relu)(Dropout(rate=0.3))(12-relu)(0-opout(rate=0.6))(8-relu)(Dropout(rate=0.3))(4-relu)(1-sigmoid)
        4 - (3-relu)(1-sigmoid)
    Parameters
    ----------
    THECLASSTOFIND : TYPE
        The Alleele/Antigen to predict. One of ['c','C','e','E','Cw','M','N','s','S','He+']
    NUMBEROF_EPOCHS : TYPE, optional
        Number of interations per training. The default is 100.
    make_plot : TYPE, optional
        Generate scatter plots. The default is False.
    outfile : TYPE, optional
        A file that contains details about the performance of the training. The default is "./Performance.csv".
    transformation : TYPE, optional
        Data transformation that can be performed on the intensities. 'Cartesian' means as is, 'Polar' is a transformation to polar coordinates. The default is 'Cartesian'.
    MODELS_tO_USE : TYPE, optional
        There are different models Implemented. The default is [0,1,2,3,4].
    OPTIMIZER_TO_USE : TYPE, optional
        Different optimizers can be used. The default is ['Adadelta','Adagrad','Adam','Adamax','Ftrl','Nadam','RMSprop','SGD'].
    MYWORKINGPATH : TYPE, optional
        This is the working path and all config files are expected relative to this location. The default is "/home/mwittig/data/Genotypisierung/Haemocarta/bloodArray/TensorFlow/DeepBloodArray".
    MYSAVEPATH : TYPE, optional
        Set this if you would like to save the model. An empty string means no saving. The default is "".

    Raises
    ------
    Exception
        DESCRIPTION.

    Returns
    -------
    None.

    """
                
    #Available optimizer: ['Adadelta','Adagrad','Adam','Adamax','Ftrl','Nadam','RMSprop','SGD']
    # I have 4 models [0,1,2,3,4]

    THEPHENOTYPEFILE='Curated_Phenotypes_20200724.csv'
    THESNPSETFILE='consider_those.csv'
    THEFAMFILE = 'Evoker_Files/HEM_MLD_v1.fam'
    THEBIMFILE = 'Evoker_Files/HEM_MLD_v1.bim'
    THEBNTFILE = 'Evoker_Files/HEM_MLD_v1.bnt'
    THEBATCHESFILE='Evoker_Files/batches.csv'

    ## build pathes
    MYWORKINGPATH=THEROOTPATH
    THEFAMFILE=os.path.join(MYWORKINGPATH,THEFAMFILE)
    THEBIMFILE=os.path.join(MYWORKINGPATH,THEBIMFILE)
    THEBNTFILE=os.path.join(MYWORKINGPATH,THEBNTFILE)
    THEPHENOTYPEFILE=os.path.join(MYWORKINGPATH,THEPHENOTYPEFILE)
    THESNPSETFILE=os.path.join(MYWORKINGPATH,THESNPSETFILE)
    
    ## read data: Evoker, phenotype table and SNP set for machine learning
    sample_ids, snp_ids, ordered_data  = evk.loadEvoker(THEFAMFILE,THEBIMFILE,THEBNTFILE)
    batch_table = pd.read_csv(os.path.join(MYWORKINGPATH,THEBATCHESFILE), sep='\t')
    relevant_SNP_table = pd.read_csv(THESNPSETFILE, sep=',')
    relevant_SNP_set=relevant_SNP_table.loc[relevant_SNP_table['Antigen']==THECLASSTOFIND,'SNP'].tolist()
    
    phenotypic_table=pd.read_csv(THEPHENOTYPEFILE) 
    phenotypic_table=evk.removeNAvalues(phenotypic_table, THECLASSTOFIND)

    curated_ordered_array, shrinked_phenotypic_table, snp_id_filter = evk.getRelevantDataSet(ordered_data,
                                                                                             relevant_SNP_set,
                                                                                             phenotypic_table,
                                                                                             sample_ids, snp_ids)
    batch_north_german = batch_table[batch_table['HGDP'] == 0]
    batch_HGDP = batch_table[batch_table['HGDP'] == 1]
    idx = shrinked_phenotypic_table['don_number'].isin(batch_north_german['sample_id'])
    batch_north_german_phen_table = shrinked_phenotypic_table[idx]
    batch_north_german_curated_ordered_array = curated_ordered_array[idx]
    idx = shrinked_phenotypic_table['don_number'].isin(batch_HGDP['sample_id'])
    batch_HGDP_phen_table = shrinked_phenotypic_table[idx]
    batch_HGDP_curated_ordered_array = curated_ordered_array[idx]

    input_array_concat_NG, phenotype_column_idx_NG, numerical_labels_NG=reformatTablesForTraining(
        batch_north_german_curated_ordered_array,batch_north_german_phen_table,transformation,THECLASSTOFIND)
    input_array_concat_HGDP, phenotype_column_idx_HGDP, numerical_labels_HGDP = reformatTablesForTraining(
        batch_HGDP_curated_ordered_array, batch_HGDP_phen_table, transformation, THECLASSTOFIND)

    ## split the data into training and validation
    # We want two datasets. One with the north german batch, one with the Ceph diversity batch. We split both seperate and merge the two fractions later

    train_x_NG,test_x_NG,train_y_NG,test_y_NG=train_test_split(input_array_concat_NG,numerical_labels_NG,
                                                                    test_size=0.2)
    train_x_HGDP, test_x_HGDP, train_y_HGDP, test_y_HGDP = train_test_split(input_array_concat_HGDP, numerical_labels_HGDP,
                                                               test_size=0.2)
    train_x=np.concatenate((train_x_NG,train_x_HGDP),axis=0)
    test_x = np.concatenate((test_x_NG, test_x_HGDP), axis=0)
    train_y = np.concatenate((train_y_NG , train_y_HGDP), axis=0)
    test_y = np.concatenate((test_y_NG , test_y_HGDP), axis=0)

    train_x[np.isnan(train_x)] = 0.0
    test_x[np.isnan(test_x)] = 0.0

    ## define the models and compile
    my_models = zoo.getModels(input_layer_length=len(relevant_SNP_set)*2,model_by_index=MODELS_tO_USE)
    
    ## fitting the model
    performance_message=[]
    if not os.path.isfile(outfile):
        performance_message.append("Antigen,Training Size,Training Cases,Test Size,Test Cases,Fraction Training Cases,Fraction Test Cases,Pred true,Pred False,Pred Failed,Conc. Rate,Accuracy,Precision,Recall,AUC,Optimizer,Layer,Epochs\n")

    for idx, item in enumerate(my_models):                  # for each model
        for idxO, itemO in enumerate(OPTIMIZER_TO_USE):     # for each optimizer
            act_model = zoo.compileModel(my_models[idx],itemO)
            act_model.fit(x=train_x,y=train_y,validation_data=(test_x,test_y),batch_size=32, epochs=NUMBEROF_EPOCHS)
            model_performance=pd.DataFrame(act_model.history.history)
            model_as_string = zoo.getModelDetailsAsString(act_model)
            if MYSAVEPATH != "":
                model_savename = os.path.join(MYSAVEPATH,"%s-%s-%d-%s.mdl" % (THECLASSTOFIND,transformation,NUMBEROF_EPOCHS,model_as_string))
                act_model.save(model_savename)
            if make_plot:
                pred_result=act_model.predict(x=test_x)
                test_size, wrong_predicted, not_predicted = myplot.plot_result(train_x,train_y,test_x,test_y,pred_result,snp_id_filter,os.path.join(MYSAVEPATH,"%s-%s-%d-%s" % (THECLASSTOFIND,transformation,NUMBEROF_EPOCHS,model_as_string)))
            for  act_message in performance_message:
                print(act_message,sep="")
            concordance_rate = 0;
            if test_size-not_predicted != 0:
                concordance_rate = (test_size-not_predicted-wrong_predicted)/(test_size-not_predicted )
            performance_message.append("%s,%d,%d,%d,%d,%1.4f,%1.4f,%d,%d,%d,%1.4f,%1.4f,%1.4f,%1.4f,%1.4f,%s,%s,%d\n" % (THECLASSTOFIND,
               len(train_y), sum(train_y),
               len(test_x), sum(test_y),
               sum(train_y) / len(train_y),
               sum(test_y) / len(test_y),
               test_size - wrong_predicted - not_predicted,
               wrong_predicted,
               not_predicted,
               (test_size-not_predicted-wrong_predicted)/(test_size-not_predicted ),
               model_performance.iloc[
                   NUMBEROF_EPOCHS - 1][1],
               model_performance.iloc[
                   NUMBEROF_EPOCHS - 1][2],
               model_performance.iloc[
                   NUMBEROF_EPOCHS - 1][3],
               model_performance.iloc[
                   NUMBEROF_EPOCHS - 1][4],
               act_model.optimizer.get_config()[
                   'name'],
               model_as_string,
               NUMBEROF_EPOCHS
               ))

    text_file = open(outfile, "a")
    text_file.writelines(performance_message)
    text_file.close()
    return

## Here we run the training for the GWAS classification
#THESAVEPATHISHERE="/home/mwittig/data/Genotypisierung/Haemocarta/bloodArray/TensorFlow/Models_for_GWAS_v2"
Antigen_List = ['e','E','c','C','M','N','s','S']
#for r in list(range(12)):
for i,j in enumerate(Antigen_List):
    trainAndTest(j,100,True,"%s/Performance.csv" % (THESAVEPATHISHERE),'Cartesian',
                     [0],['RMSprop'],THEROOTPATH,THESAVEPATHISHERE)

## trainAndTest('He+',100,True,"%s/Performance_sbatch_run_NormTheta.csv" % (THEROOTPATH),'Polar',
##                      [0],['RMSprop'],THEROOTPATH,THESAVEPATHISHERE)



#%%
#Antigen_List = ['c','C','e','E','Cw','M','N','s','S','He+']
#for k, cycle in enumerate([0,1,2,3,4,5,6,7,8,9]):
#    for i,j in enumerate(Antigen_List):
#        trainAndTest(j,100,False,"%s/Performance_sbatch_run_NormTheta.csv" % (THEROOTPATH),'Cartesian',
#                     [0,1,2,3,4],['Adadelta','Adagrad','Adam','Adamax','Nadam','RMSprop','SGD'],
#                     MYWORKINGPATH=THEROOTPATH)


    #trainAndTest(j,2,[0,1],['Adam','RMSprop','SGD'])

'''
    pred_result=models[idx].predict(x=test_x)

    myplot.plot_result(train_x,train_y,test_x,test_y,pred_result,snp_id_filter)
'''
