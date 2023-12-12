/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CLandsteiner.cpp
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
#include "CLandsteiner.h"

using namespace std;

CLandsteiner::CLandsteiner() 
{
    initSNPs();
}

CLandsteiner::CLandsteiner(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService) {
    m_snp_name_lookup_service = snpNameLookupService;
    initSNPs();
}

CLandsteiner::CLandsteiner(const CLandsteiner& orig) 
{
    m_snps = orig.m_snps;
}

CLandsteiner::~CLandsteiner() {
}

void CLandsteiner::initSNPs() {
    m_snps.insert(CSNP(lookupSNPName("rs77493670"), "chr19", 10397987)); // LWa/LWb	ICAM-4	LW*05 (wt)/LW*07    A/G	Gln100Arg   rs77493670	[A/G]	19	10397987
}

std::string CLandsteiner::phenotype()
{
    vector<string> alleles;
    if(isRelevantGtMissing())
        return "#N/A";
    
    CSNP rs77493670  = *(m_snps.find(CSNP(lookupSNPName("rs77493670"))));
    
    // Plus strand
    if(rs77493670.isHetero())
        alleles.push_back("LWb");
    if(rs77493670.isHomoFor("G"))
    {
        alleles.push_back("LWb");alleles.push_back("LWb");
    }
    alleles.push_back("LWa");
    alleles.push_back("LWa");
    
    result_vector_sorting(alleles);
    set<string> result;
    result.insert(alleles[0]);
    result.insert(alleles[1]);
    
    bool isA = result.find("LWa") != result.end();
    bool isB = result.find("LWb") != result.end();
    
    
    return string("LW(a")+(isA ? "+" : "-")+"b"+(isB ? "+" : "-")+")";

    
}

