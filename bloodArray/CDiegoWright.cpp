/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CDiegoWright.cpp
 * Author: mwittig
 * 
 * Created on July 6, 2018, 8:57 AM
 */
#include <string>
#include <set>
#include <sstream>
#include <math.h>
#include <algorithm>

#include "CSNP.h"

#include "CRBCsnps.h"
#include "CDiegoWright.h"

using namespace std;

CDiegoWright::CDiegoWright() 
{
    initSNPs();
}

CDiegoWright::CDiegoWright(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService) {
    m_snp_name_lookup_service = snpNameLookupService;
    initSNPs();
}

CDiegoWright::CDiegoWright(const CDiegoWright& orig) 
{
    m_snps = orig.m_snps;
}

CDiegoWright::~CDiegoWright() {
}

void CDiegoWright::initSNPs() {
    m_snps.insert(CSNP(lookupSNPName("ilmnseq_rs2285644.1_F2BT"), "chr17", 42328621)); // Dia / Dib	SLC4A1	DI*02 (wt)	DI*01	C	T	ilmnseq_rs2285644.1_F2BT	17	42328621
    m_snps.insert(CSNP(lookupSNPName("ilmnseq_rs75731670.2_F2BT"), "chr17", 42331949)); // Wra / Wrb	SLC4A1 	DI*02 (wt)	DI*02.03	G	A	Glu658Lys	ilmnseq_rs75731670.2_F2BT	17	42331949
}

std::string CDiegoWright::phenotype()
{
    vector<string> allelesD;
    vector<string> allelesW;
    CSNP ilmnseq_rs2285644  = *(m_snps.find(CSNP(lookupSNPName("ilmnseq_rs2285644.1_F2BT"))));
    CSNP ilmnseq_rs75731670 = *(m_snps.find(CSNP(lookupSNPName("ilmnseq_rs75731670.2_F2BT"))));

    // Reverse strand
    if(ilmnseq_rs2285644.isHetero())
        allelesD.push_back("Dia");
    if(ilmnseq_rs2285644.isHomoFor("A"))
    {
        allelesD.push_back("Dia");allelesD.push_back("Dia");
    }
    allelesD.push_back("Dib");
    allelesD.push_back("Dib");
    
    if(ilmnseq_rs75731670.isHetero())
        allelesW.push_back("Wra");
    if(ilmnseq_rs75731670.isHomoFor("T"))
    {
        allelesW.push_back("Wra");allelesW.push_back("Wra");
    }
    allelesW.push_back("Wrb");
    allelesW.push_back("Wrb");
    
    

    result_vector_sorting(allelesD);
    result_vector_sorting(allelesW);
    
    set<string> result;
    result.insert(allelesD[0]);
    result.insert(allelesD[1]);
    
    bool isA = result.find("Dia") != result.end();
    bool isB = result.find("Dib") != result.end();
    
    string resultD =  string("Di(a")+(isA ? "+" : "-")+"b"+(isB ? "+" : "-")+")" ;
    result.clear();
    result.insert(allelesW[0]);
    result.insert(allelesW[1]);
    
    isA = result.find("Wra") != result.end();
    isB = result.find("Wrb") != result.end();
    
    string resultW =  string("Wr(a")+(isA ? "+" : "-")+"b"+(isB ? "+" : "-")+")" ;
    
    if(ilmnseq_rs2285644.isNA())
        resultD="#N/A";
    if(ilmnseq_rs75731670.isNA())
        resultW="#N/A";
    
            
   return resultD+','+resultW;
    
}

