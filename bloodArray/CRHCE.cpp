/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CRHCE.cpp
 * Author: mwittig
 * 
 * Created on July 6, 2018, 8:57 AM
 */
#include <string>
#include <set>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <map>

#include "CSNP.h"

#include "CRBCsnps.h"
#include "CRHCE.h"

using namespace std;

CRHCE::CRHCE() 
{
    initSNPs();
}

CRHCE::CRHCE(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService) {
    m_snp_name_lookup_service = snpNameLookupService;
    initSNPs();
}

CRHCE::CRHCE(const CRHCE& orig) 
{
    m_snps = orig.m_snps;
}

CRHCE::~CRHCE() {
}

void CRHCE::initSNPs() {
    CSNP a(lookupSNPName("rs676785"), "chr1", 25735202);
    m_snps.insert(a);
    CSNP b(lookupSNPName("rs609320"), "chr1", 25717365);
    m_snps.insert(b);
    
    /*
     - Alleles C/c
    -- check rs676785. C is allele C and T identifies allele c. Maybe there is a probe design for the 109bp deletion, which should be more robust.
    - Alleles E/e
    -- check rs609320 for E/e discrimination. (G for e and C for E) 
     */
    
}

std::string CRHCE::phenotype()
{
    
    
    CSNP rs609320  = *(m_snps.find(CSNP(lookupSNPName("rs609320"))));
    CSNP rs676785  = *(m_snps.find(CSNP(lookupSNPName("rs676785"))));
    
    vector<string> C_alleles;
    vector<string> E_alleles;
    
    // RHCE is on the reverse strand, so the alleles must be switched
    
    
    if(rs609320.isHetero())
        E_alleles.push_back("e");
    if(rs609320.isHomoFor("C"))
    {
        E_alleles.push_back("e");E_alleles.push_back("e");
    }
    E_alleles.push_back("E");
    E_alleles.push_back("E");
    result_vector_sorting(E_alleles);      
            
    if(rs676785.isHetero())
        C_alleles.push_back("C");
    if(rs676785.isHomoFor("A"))
    {
        C_alleles.push_back("C");C_alleles.push_back("C");
    }
    C_alleles.push_back("c");
    C_alleles.push_back("c");
    result_vector_sorting(C_alleles); 
   
    return string("Rh(")+C_alleles[0]+C_alleles[1]+string(",")+E_alleles[0]+E_alleles[1]+string(")");
}

