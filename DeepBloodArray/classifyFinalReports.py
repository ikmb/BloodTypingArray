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
import subprocess
import json
from argparse import ArgumentParser
file_path = os.path.abspath(os.path.dirname(__file__))
parser = ArgumentParser()
parser.add_argument("-f", "--finalreport", dest="FinalReportFile", default="%s/test/FinalReport1.txt" % (file_path), help='The final report file that contains all the SNP calls and intensities')
parser.add_argument("-s", "--scratch", dest="ScratchPath", default="/tmp/",help='A scratch directory for temporary files')
parser.add_argument("-e", "--evoker", dest="EvokerCmd", default="%s/../FinalReportToEvoker/dist/Release/GNU-Linux/finalreporttoevoker" % (file_path),help='Executable "finalreporttoevoker". This programm generates temporary evoker fam, bim and bnt files in the scratch directory.')
parser.add_argument("-t", "--typer", dest="DirectTyper", default="%s/../bloodArray/dist/Release/GNU-Linux/bloodarray" % (file_path),help='Executable "bloodarray". This programm does direct typing of the non paralogous loci.')
parser.add_argument("-d", "--dependency", dest="DependencyPath", default="%s" % (file_path),help='This is the path where all configuration files are.')
parser.add_argument("-o", "--output", dest="OutputFile", default='data_%s.json',help='This is the output path. It has to have a %s at which the sample id will be inserted.')

args = parser.parse_args()

sys.path.append(args.DependencyPath)

import loadEvoker as evk




'''
######## EDIT path, class, transformation and/or input file set 
'''
EVOKERCOMMAND=args.EvokerCmd
BLOODARRAYCOMMAND=args.DirectTyper
THEFINALREPORTFILE=args.FinalReportFile
THERESULTFILE=args.OutputFile
MYWORKINGPATH=args.DependencyPath
THECLASSTOPREDICT="N"
transformation='Cartesian'
THEFAMFILE="%s/fr2evoker.fam" % (args.ScratchPath)
THEBIMFILE="%s/fr2evoker.bim" % (args.ScratchPath)
THEBNTFILE="%s/fr2evoker.bnt" % (args.ScratchPath)
CONFIDENCETHRESHOLD = [0.4 , 0.6]
THERESULT= {}
THESNPSETFILE = 'consider_those.csv'
THESNPSETFILE = os.path.join(MYWORKINGPATH, THESNPSETFILE)

def getScore(X,Y):
    if X >= 0.5:
        X = (X - 0.5) * 2
    if X < 0.5:
        X = (0.5 - X) * 2
    if Y >= 0.5:
        Y = (Y - 0.5) * 2
    if Y < 0.5:
        Y = (0.5 - Y) * 2
    return 2*X*Y/(X+Y)

## RUN direct typing
p1 = subprocess.Popen([BLOODARRAYCOMMAND,THEFINALREPORTFILE],stderr=subprocess.PIPE, universal_newlines=True,stdout=subprocess.PIPE)
header = subprocess.Popen(["tail", "-n 5"], stdin=p1.stdout, stdout=subprocess.PIPE, universal_newlines=True)
header = header.communicate()[0].split('\n')
values = header[4].split('\t')
header = header[1].split('\t')

for x,y in zip(header,values):
    THERESULT.update({x : y})

## convert final report to evoker
subprocess.check_call([EVOKERCOMMAND,THESNPSETFILE,THEFAMFILE,THEBIMFILE,THEBNTFILE,THEFINALREPORTFILE])

for THECLASSTOPREDICT in "eEcCMNsS":

    # HEM_v1 version
    # MODELPATH=MYWORKINGPATH + "/../Models_for_GWAS_v2/" + THECLASSTOPREDICT + '-' + transformation + "-100-(9-relu)(6-relu)(1-sigmoid).mdl"
    # HEM_v2 array has issues (some SNPs are missing). These two models are retrained without the missing SNPs
    # All the other models work fine with setting the missing SNPs to 0
    # missing SNPs: rs201812726, rs28591112, rs28669938, rs35076034, rs4835126, rs596939
    MODELPATH=MYWORKINGPATH + "/../Models/" + THECLASSTOPREDICT + '-' + transformation + "-100-(9-relu)(6-relu)(1-sigmoid).mdl"
    #Available optimizer: ['Adadelta','Adagrad','Adam','Adamax','Ftrl','Nadam','RMSprop','SGD']
    # I have 4 models [0,1,2,3,4]

    #THEFAMFILE=os.path.join(MYWORKINGPATH,THEFAMFILE)
    #THEBIMFILE=os.path.join(MYWORKINGPATH,THEBIMFILE)
    #THEBNTFILE=os.path.join(MYWORKINGPATH,THEBNTFILE)

    ## read data: Evoker, phenotype table and SNP set for machine learning
    sample_ids, snp_ids, ordered_data  = evk.loadEvoker(THEFAMFILE,THEBIMFILE,THEBNTFILE)
    relevant_SNP_table=pd.read_csv(THESNPSETFILE,sep=',')
    relevant_SNP_set=relevant_SNP_table.loc[relevant_SNP_table['Antigen']==THECLASSTOPREDICT,'SNP'].tolist()

    snp_id_filter=evk.shrinkSNPset(relevant_SNP_set,snp_ids)
    curated_ordered_array=ordered_data[:,snp_id_filter.iloc[:,-1],:]

    the_norm_values = curated_ordered_array[:,:,0]+curated_ordered_array[:,:,1]
    the_teta_values = curated_ordered_array[:,:,1]/the_norm_values
    input_array=np.concatenate([the_norm_values,the_teta_values],axis=-1)
    if transformation == 'Cartesian':
        print("using intensities in Cartesian coordinates")
        input_array=np.concatenate([curated_ordered_array[:,:,0],curated_ordered_array[:,:,1]],axis=-1)
    elif transformation == 'Polar':
        print("using intensities in Polar coordinates")
    else:
        raise Exception("Please specify data transformation. Either Cartesian or Polar")
    ## reshape the 3D object to a 2D object with always intensity 1 as even and intensity 2 as odd row
    input_array_concat=input_array.reshape(input_array.shape[0],-1)

    ## define the models and compile
    act_model = tf.keras.models.load_model(MODELPATH)
    pred_result=act_model.predict(x=input_array)

    THERESULT.update({THECLASSTOPREDICT : pred_result[0,0]})

THERESULT.update({"Cc" : ""})
if (THERESULT.get("c") >= CONFIDENCETHRESHOLD[0] and  THERESULT.get("c") <= CONFIDENCETHRESHOLD[0]) or (THERESULT.get("C") >= CONFIDENCETHRESHOLD[0] and  THERESULT.get("C") <= CONFIDENCETHRESHOLD[0]):
    THERESULT.update({"Cc" : "#N/A"})
elif THERESULT.get("c") >= CONFIDENCETHRESHOLD[0] and THERESULT.get("C") >= CONFIDENCETHRESHOLD[0]:
    THERESULT.update({"Cc" : "Cc"})
elif THERESULT.get("c") <= CONFIDENCETHRESHOLD[0] and THERESULT.get("C") >= CONFIDENCETHRESHOLD[0]:
    THERESULT.update({"Cc" : "CC"})
elif THERESULT.get("c") >= CONFIDENCETHRESHOLD[0] and THERESULT.get("C") <= CONFIDENCETHRESHOLD[0]:
    THERESULT.update({"Cc" : "cc"})
THERESULT.update({"Cc-score" : getScore(THERESULT.get("C"),THERESULT.get("c"))})

THERESULT.update({"Ee" : ""})
if (THERESULT.get("e") >= CONFIDENCETHRESHOLD[0] and  THERESULT.get("e") <= CONFIDENCETHRESHOLD[0]) or (THERESULT.get("E") >= CONFIDENCETHRESHOLD[0] and  THERESULT.get("E") <= CONFIDENCETHRESHOLD[0]):
    THERESULT.update({"Ee" : "#N/A"})
elif THERESULT.get("e") >= CONFIDENCETHRESHOLD[0] and THERESULT.get("E") >= CONFIDENCETHRESHOLD[0]:
    THERESULT.update({"Ee" : "Ee"})
elif THERESULT.get("e") <= CONFIDENCETHRESHOLD[0] and THERESULT.get("E") >= CONFIDENCETHRESHOLD[0]:
    THERESULT.update({"Ee" : "EE"})
elif THERESULT.get("e") >= CONFIDENCETHRESHOLD[0] and THERESULT.get("E") <= CONFIDENCETHRESHOLD[0]:
    THERESULT.update({"Ee" : "ee"})
THERESULT.update({"Ee-score" : getScore(THERESULT.get("E"),THERESULT.get("e"))})

THERESULT.update({"Ss" : ""})
if (THERESULT.get("s") >= CONFIDENCETHRESHOLD[0] and  THERESULT.get("s") <= CONFIDENCETHRESHOLD[0]) or (THERESULT.get("S") >= CONFIDENCETHRESHOLD[0] and  THERESULT.get("S") <= CONFIDENCETHRESHOLD[0]):
    THERESULT.update({"Ss" : "#N/A"})
elif THERESULT.get("s") >= CONFIDENCETHRESHOLD[0] and THERESULT.get("S") >= CONFIDENCETHRESHOLD[0]:
    THERESULT.update({"Ss" : "Ss"})
elif THERESULT.get("s") <= CONFIDENCETHRESHOLD[0] and THERESULT.get("S") >= CONFIDENCETHRESHOLD[0]:
    THERESULT.update({"Ss" : "SS"})
elif THERESULT.get("s") >= CONFIDENCETHRESHOLD[0] and THERESULT.get("S") <= CONFIDENCETHRESHOLD[0]:
    THERESULT.update({"Ss" : "ss"})
THERESULT.update({"Ss-score" : getScore(THERESULT.get("S"),THERESULT.get("s"))})

THERESULT.update({"MN" : ""})
if (THERESULT.get("M") >= CONFIDENCETHRESHOLD[0] and  THERESULT.get("M") <= CONFIDENCETHRESHOLD[0]) or (THERESULT.get("N") >= CONFIDENCETHRESHOLD[0] and  THERESULT.get("N") <= CONFIDENCETHRESHOLD[0]):
    THERESULT.update({"MN" : "#N/A"})
elif THERESULT.get("M") >= CONFIDENCETHRESHOLD[0] and THERESULT.get("N") >= CONFIDENCETHRESHOLD[0]:
    THERESULT.update({"MN" : "MN"})
elif THERESULT.get("M") <= CONFIDENCETHRESHOLD[0] and THERESULT.get("N") >= CONFIDENCETHRESHOLD[0]:
    THERESULT.update({"MN" : "NN"})
elif THERESULT.get("M") >= CONFIDENCETHRESHOLD[0] and THERESULT.get("N") <= CONFIDENCETHRESHOLD[0]:
    THERESULT.update({"MN" : "MM"})
THERESULT.update({"MN-score" : getScore(THERESULT.get("M"),THERESULT.get("N"))})

for x in THERESULT:
    print("%s %s" % (x,THERESULT[x]))

metadata = {"sample_code":THERESULT["Sample_ID"]}
antigens = {}
## antigens.update({"" : THERESULT[""]})
antigens.update({"ABO" : THERESULT["ABO"]})
antigens.update({"RhD" : THERESULT["RHD"]})
antigens.update({"RhCE-Cc" : THERESULT["Cc"]})
antigens.update({"Cc-score" : THERESULT["Cc-score"]})
antigens.update({"RhCE-Ee" : THERESULT["Ee"]})
antigens.update({"Ee-score" : THERESULT["Ee-score"]})
antigens.update({"MNS-MN" : THERESULT["MN"]})
antigens.update({"MN-score" : THERESULT["MN-score"]})
antigens.update({"MNS-Ss" : THERESULT["Ss"]})
antigens.update({"Ss-score" : THERESULT["Ss-score"]})
antigens.update({"Kk" : THERESULT["KEL"].split(',')[0]})
antigens.update({"Kp" : THERESULT["KEL"].split(',')[1]})
antigens.update({"Js" : THERESULT["KEL"].split(',')[2]})
antigens.update({"Lu" : THERESULT["LU"].split(',')[0]})
antigens.update({"Au" : THERESULT["LU"].split(',')[1]})
antigens.update({"Lu814" : THERESULT["LU"].split(',')[2]})
antigens.update({"Fy" : THERESULT["FY"]})
antigens.update({"Jk" : THERESULT["JK"]})
antigens.update({"Di" : THERESULT["DI"].split(',')[0]})
antigens.update({"Wr" : THERESULT["DI"].split(',')[1]})
antigens.update({"Yt" : THERESULT["YT"]})
antigens.update({"Sc" : THERESULT["SC"]})
antigens.update({"Do" : THERESULT["DO"].split(',')[0]})
antigens.update({"Co" : THERESULT["CO"]})
antigens.update({"Crom" : THERESULT["CROM"]})
antigens.update({"LW" : THERESULT["LW"]})
antigens.update({"KN" : THERESULT["KN"].split(',')[0]})
antigens.update({"McC" : THERESULT["KN"].split(',')[1]})
antigens.update({"Vil" : THERESULT["KN"].split(',')[2]})
antigens.update({"Jr" : THERESULT["JR"]})
antigens.update({"LAN" : THERESULT["LAN"]})
antigens.update({"Vel" : THERESULT["VEL"]})

metadata.update({"data" : antigens})
with open(THERESULTFILE % THERESULT["Sample_ID"], 'w') as f:
        # where data is your valid python dictionary
        json.dump(metadata, f)

os.remove(THEFAMFILE)
os.remove(THEBIMFILE)
os.remove(THEBNTFILE)





