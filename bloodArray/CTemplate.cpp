/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CTemplate.cpp
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
#include "CTemplate.h"

using namespace std;

CTemplate::CTemplate() 
{
    m_snps.insert(CSNP("SNPID","chr",00000000,"n.a.")); // 

}

CTemplate::CTemplate(const CTemplate& orig) 
{
    m_snps = orig.m_snps;
}

CTemplate::~CTemplate() {
}

std::string CTemplate::phenotype()const
{
    vector<string> alleles;
    
    CSNP SNPID  = *(m_snps.find(CSNP("SNPID")));
    
    // Reverse strand
    if(SNPID.isHetero())
        alleles.push_back("ALT");
    if(SNPID.isHomoFor("N"))
    {
        alleles.push_back("ALT");alleles.push_back("ALT");
    }
    alleles.push_back("REF");
    alleles.push_back("REF");
    
    

    // sort(alleles.begin(),alleles.end(),my_allele_sorting);
    
    if(alleles.size() < 2)
        return "INVALID genotypes";
    else
        return alleles[0]+alleles[1];
    
}

