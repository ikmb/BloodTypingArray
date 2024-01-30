/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CCartwright.cpp
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
#include "CCartwright.h"

using namespace std;

CCartwright::CCartwright() 
{
    initSNPs();
}

CCartwright::CCartwright(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService) {
    m_snp_name_lookup_service = snpNameLookupService;
    initSNPs();
}

CCartwright::CCartwright(const CCartwright& orig) 
{
    m_snps = orig.m_snps;
}

CCartwright::~CCartwright() {
}

void CCartwright::initSNPs() {
    m_snps.insert(CSNP(lookupSNPName("rs1799805"), "chr7", 100490797)); // Cartwright	011	Yta / Ytb	ACHE 	YT*01 (wt)/YT*02 C/A	His353Asn	rs1799805	chr7	100490797
}

std::string CCartwright::phenotype()
{
    vector<string> alleles;
    
    CSNP rs1799805  = *(m_snps.find(CSNP(lookupSNPName("rs1799805"))));
    
    if(rs1799805.isNA())
        return "#N/A";
    // Reverse strand
    if(rs1799805.isHetero())
        alleles.push_back("Ytb");
    if(rs1799805.isHomoFor("T"))
    {
        alleles.push_back("Ytb");alleles.push_back("Ytb");
    }
    alleles.push_back("Yta");
    alleles.push_back("Yta");
   
    result_vector_sorting(alleles);
    
    set<string> result;
    result.insert(alleles[0]);
    result.insert(alleles[1]);
    
    bool isA = result.find("Yta") != result.end();
    bool isB = result.find("Ytb") != result.end();
    
    
    return string("Yt(a")+(isA ? "+" : "-")+"b"+(isB ? "+" : "-")+")";
    
}

