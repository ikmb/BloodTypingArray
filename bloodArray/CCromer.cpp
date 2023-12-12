/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CCromer.cpp
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
#include "CCromer.h"

using namespace std;

CCromer::CCromer() 
{
    initSNPs();
}

CCromer::CCromer(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService) {
    m_snp_name_lookup_service = snpNameLookupService;
    initSNPs();
}

CCromer::CCromer(const CCromer& orig) 
{
    m_snps = orig.m_snps;
}

CCromer::~CCromer() {
}

void CCromer::initSNPs() {
    m_snps.insert(CSNP(lookupSNPName("ilmnseq_rs60822373.1_F2BT"), "chr1", 207504467)); // Cra / Cra-	CD55	CROM*01 (wt)	CROM*–01	G/C	Ala227Pro   ilmnseq_rs60822373.1_F2BT	BOT	[G/C]	37	1	207504467
    m_snps.insert(CSNP(lookupSNPName("ilmnseq_rs28371588.3_F2BT_ilmnrep1"), "chr1", 207495781)); // Tca / Tcb	CD55	CROM*01 (wt)	CROM*01.03	G/T	Arg52Leu    ilmnseq_rs28371588.3_F2BT	TOP	[A/C]	37	1	207495781
    m_snps.insert(CSNP(lookupSNPName("ilmnseq_rs28371588.2_F2BT_ilmnrep1"), "chr1", 207495781)); // Tca / Tcc	CD55	CROM*01 (wt)	CROM*01.04	G/C	Arg52Pro    ilmnseq_rs28371588.2_F2BT	TOP	[C/G]	37	1	207495781
}

std::string CCromer::phenotype()
{
    vector<string> allelesCr;
    vector<string> allelesTc;
    
    CSNP ilmnseq_rs60822373  = *(m_snps.find(CSNP(lookupSNPName("ilmnseq_rs60822373.1_F2BT"))));
    CSNP ilmnseq_rs28371588_3  = *(m_snps.find(CSNP(lookupSNPName("ilmnseq_rs28371588.3_F2BT_ilmnrep1"))));
    CSNP ilmnseq_rs28371588_2  = *(m_snps.find(CSNP(lookupSNPName("ilmnseq_rs28371588.2_F2BT_ilmnrep1"))));
    
    // Reverse strand
    if(ilmnseq_rs60822373.isHetero())
        allelesCr.push_back("Cra-");
    if(ilmnseq_rs60822373.isHomoFor("C"))
    {
        allelesCr.push_back("Cra-");allelesCr.push_back("Cra-");
    }
    allelesCr.push_back("Cra");
    allelesCr.push_back("Cra");
    
    if(ilmnseq_rs28371588_3.isHetero())
        allelesTc.push_back("Tcb");
    if(ilmnseq_rs28371588_3.isHomoFor("T"))
    {
        allelesTc.push_back("Tcb");allelesTc.push_back("Tcb");
    }
    if(ilmnseq_rs28371588_2.isHetero())
        allelesTc.push_back("Tcc");
    if(ilmnseq_rs28371588_2.isHomoFor("C"))
    {
        allelesTc.push_back("Tcc");allelesTc.push_back("Tcc");
    }
    allelesTc.push_back("Tca");
    allelesTc.push_back("Tca");
    
  
    result_vector_sorting(allelesCr);
    result_vector_sorting(allelesTc);
    
    string resultCr = (allelesCr.size() == 4 ? "Cr(a-)" : "Cr(a+)");
    set<string> result;
    result.insert(allelesTc[0]);
    result.insert(allelesTc[1]);
    
    bool isA = result.find("Tca") != result.end();
    bool isB = result.find("Tcb") != result.end();
    bool isC = result.find("Tcc") != result.end();
    
    string resultTC = string("Tc(")+(isA ? "a+" : "a-")+(isB ? "b+" : "b-")+(isC ? "c+" : "c-")+")";
   
    if(ilmnseq_rs60822373.isNA())
        resultCr="#N/A";
    if(ilmnseq_rs28371588_3.isNA() || ilmnseq_rs28371588_2.isNA())
        resultTC="#N/A";
    
    
    return resultCr +','+resultTC;
    
}

