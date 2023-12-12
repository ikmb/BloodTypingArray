/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CIndian.cpp
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
#include "CIndian.h"

using namespace std;

CIndian::CIndian() 
{
    initSNPs();
}

CIndian::CIndian(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService) {
    m_snp_name_lookup_service = snpNameLookupService;
    initSNPs();
}

CIndian::CIndian(const CIndian& orig) 
{
    m_snps = orig.m_snps;
}

CIndian::~CIndian() {
}

void CIndian::initSNPs() {
    m_snps.insert(CSNP(lookupSNPName("ilmnseq_rs369473842.1_F2BT"), "chr11", 35198191)); // 
    
}

std::string CIndian::phenotype()
{
    vector<string> alleles;
    
    CSNP rs369473842  = *(m_snps.find(CSNP(lookupSNPName("ilmnseq_rs369473842.1_F2BT")))); // c.137G>C is In(a+b–)
    // => G is b+
    
    if(isRelevantGtMissing())
        return "#N/A";
    
    
    if(rs369473842.isHetero())
        alleles.push_back("Ina");
    if(rs369473842.isHomoFor("C"))
    {
        alleles.push_back("Ina");alleles.push_back("Ina");
    }
    
    
    alleles.push_back("Inb");
    alleles.push_back("Inb");
    set<string> result;
    result.insert(alleles[0]);
    result.insert(alleles[1]);
    
    bool isA = result.find("Ina") != result.end();
    bool isB = result.find("Inb") != result.end();
    
    return string("In(a")+(isA ? "+" : "-")+"b"+(isB ? "+" : "-")+")";


}

