/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CScianna.cpp
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
#include "CScianna.h"

using namespace std;

CScianna::CScianna() 
{
    initSNPs();
}

CScianna::CScianna(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService) {
    m_snp_name_lookup_service = snpNameLookupService;
    initSNPs();
}

CScianna::CScianna(const CScianna& orig) 
{
    m_snps = orig.m_snps;
}

CScianna::~CScianna() {
}

void CScianna::initSNPs() {
    m_snps.insert(CSNP(lookupSNPName("rs56025238"), "chr1", 43296522)); // Scianna	013	SC:1, SC:2	ERMAP	SC*01 (wt)/SC*02	G/A	Gly57Arg	rs56025238  1	43296522
}

std::string CScianna::phenotype()
{
    vector<string> alleles;
    
    CSNP rs56025238  = *(m_snps.find(CSNP(lookupSNPName("rs56025238"))));
    if(rs56025238.isNA())
        return "#N/A";
    
    // Forward strand
    if(rs56025238.isHetero())
        alleles.push_back("Sc2");
    if(rs56025238.isHomoFor("A"))
    {
        alleles.push_back("Sc2");alleles.push_back("Sc2");
    }
    alleles.push_back("Sc1");
    alleles.push_back("Sc1");
    
    result_vector_sorting(alleles);
    set<string> result;
    result.insert(alleles[0]);
    result.insert(alleles[1]);
    
    bool isA = result.find("Sc1") != result.end();
    bool isB = result.find("Sc2") != result.end();
    
    
    return string("Sc1")+(isA ? "+" : "-")+"Sc2"+(isB ? "+" : "-");
    
   
}

