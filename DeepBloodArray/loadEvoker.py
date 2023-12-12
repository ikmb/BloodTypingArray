#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Jun 10 12:54:53 2020

@author: mwittig
"""
#%%

import pandas as pd
import numpy as np 
import struct


## preparing the data for chromosome four
## Read the sample IDs 

def loadEvoker(THEFAMFILE,THEBIMFILE,THEBNTFILE):
    sample_ids=pd.read_csv(THEFAMFILE,sep=' ',header=None).iloc[:,1].to_list()
    sample_ids=[str(name) for name in sample_ids]
    snp_ids=pd.read_csv(THEBIMFILE,sep='\t',header=None).iloc[:,1].to_list()
    
    data=[]
    with open(THEBNTFILE,'rb') as buffer_handler:
        first_magic_number=buffer_handler.read(1)
        second_magic_number=buffer_handler.read(1)
        while True:
            buf=buffer_handler.read(4)
            if not buf: break
            else: 
                data.append(buf)
             
    # check magic numbers for consistency
    de_m1=int.from_bytes(first_magic_number,'big')
    de_m2=int.from_bytes(second_magic_number,'big')
    ## Assert they are correct magic numbers
    assert de_m1==26 and de_m2==49, f""" 
        A corapted file has been encountered, Magic number did not match!, current magic numbers are {de_m1} and {de_m2}"""
    ## decode the data as float of little endian
    unpacked_data=np.array([struct.unpack('<f',elem) for elem in data])
    ## reshape the data in the 3D shape.
    ordered_data_chr4=unpacked_data.reshape(len(snp_ids),len(sample_ids),2)
    ## Transpose The data
    ordered_data_chr4=np.transpose(ordered_data_chr4,axes=(1,0,2))  
    return  sample_ids, snp_ids, ordered_data_chr4      
        
def removeNAvalues(phenotypic_table,phenotype_column):        
    ## Extracting the genotypic data from the curated phenotypic data
    index_of_NAs=[]
    for index, row in phenotypic_table.iterrows():
        if(row[phenotype_column] == 'n.a.'):
            index_of_NAs.append(index)
    phenotypic_table = phenotypic_table.drop(index_of_NAs)
    
    return phenotypic_table

def shrinkPhenotypes(phenotypic_table,sample_ids):        
    ## Extracting the genotypic data from the curated phenotypic data
    index_of_samples,not_mapped=[],[]
    for pro_id in phenotypic_table.iloc[:,0].to_list():
        if str(pro_id) in sample_ids:
            index_of_samples.append(sample_ids.index(str(pro_id)))
        else:
            index_of_samples.append(-1)
            not_mapped.append(pro_id)
    ## Adding the index columns
    phenotypic_table.insert(phenotypic_table.shape[1],'IndexInEvoker',index_of_samples,True)
    ## Curating the DF results:
    phenotypic_table=phenotypic_table.loc[phenotypic_table.iloc[:,-1]!=-1,:]
    return phenotypic_table

def shrinkSNPset(relevant_SNP_set,snp_ids):
    index_of_snps,not_mapped=[],[]
    for s_id in snp_ids:
        if s_id in relevant_SNP_set:
            index_of_snps.append(snp_ids.index(s_id))
            ##print(s_id)
        else:
            index_of_snps.append(-1)
            not_mapped.append(s_id)
    snp_id_filter=pd.concat(
        [pd.DataFrame(snp_ids),
         pd.DataFrame({'IndexInEvoker':index_of_snps})],
        axis=1)
    ## Curating the DF results:
    snp_id_filter=snp_id_filter.loc[snp_id_filter.iloc[:,-1]!=-1,:]
    return snp_id_filter

def getRelevantDataSet(ordered_data,relevant_SNP_set,phenotypic_table,sample_ids,snp_ids):
    ## extract the tensor data 
    shrinked_phenotypic_table=shrinkPhenotypes(phenotypic_table,sample_ids)
    curated_array=ordered_data[shrinked_phenotypic_table.iloc[:,-1],:,:]
    snp_id_filter=shrinkSNPset(relevant_SNP_set,snp_ids)
    print("Schrinked SNP set")
    curated_array=curated_array[:,snp_id_filter.iloc[:,-1],:]
    # mapped_values={'MM':0,'MN':1,'NN':2}
    # curated_MN_phenotypic_data.MN=curated_MN_phenotypic_data.MN.map(mapped_values)
    return curated_array,shrinked_phenotypic_table,snp_id_filter

def getRelevantColumnIndex(name,phenotypic_table):
    idx = 0
    for act in phenotypic_table.columns:
        if(act == name):
            return idx
        idx +=1
    raise SystemExit('Error: Could not find column %s in phenotype Table.' % (name))
    return -1

