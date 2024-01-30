/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CVel.cpp
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
#include "CVel.h"

using namespace std;

CVel::CVel() 
{
    initSNPs();
}

CVel::CVel(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService) {
    m_snp_name_lookup_service = snpNameLookupService;
    initSNPs();
}

CVel::CVel(const CVel& orig) 
{
    m_snps = orig.m_snps;
}

CVel::~CVel() {
}

void CVel::initSNPs() {
    CSNP b(lookupSNPName("ilmnseq_rs566629828"), "chr1", 3691998); // Vel+ / Vel-	SMIM1	VEL*01 (?)/VEL*−01  -/del 17 bp	ilmnseq_rs566629828	[I/D]	1	3691998
    m_snps.insert(b);
}

std::string CVel::phenotype()
{
    vector<string> alleles;
    if(isRelevantGtMissing())
        return "#N/A";
    
    CSNP ilmnseq_rs566629828  = *(m_snps.find(CSNP(lookupSNPName("ilmnseq_rs566629828"))));
    
    if(ilmnseq_rs566629828.getNormR() < 0.3f)
        return "#N/A";

    if(ilmnseq_rs566629828.isHetero())
        alleles.push_back("Vel-");
    if(ilmnseq_rs566629828.isHomoFor("D"))
    {
        alleles.push_back("Vel-");alleles.push_back("Vel-");
    }
    alleles.push_back("Vel+");
    alleles.push_back("Vel+");
    
    result_vector_sorting(alleles);
    
    return alleles.size() > 3 ? "Vel-" : "Vel+";
    
}

