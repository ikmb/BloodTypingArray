/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CColton.cpp
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
#include "CColton.h"

using namespace std;

CColton::CColton() 
{
    initSNPs();
}

CColton::CColton(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService) {
    m_snp_name_lookup_service = snpNameLookupService;
    initSNPs();
}

CColton::CColton(const CColton& orig) 
{
    m_snps = orig.m_snps;
}

CColton::~CColton() {
}

void CColton::initSNPs() {
    m_snps.insert(CSNP(lookupSNPName("rs28362692"), "chr7", 30951658)); // Coa / Cob	AQP1	CO*01.01 (wt)	CO*02		Ala45Val	rs28362692	[C/T]  BOT	[T/C]	7	30951658
    //m_snps.insert(CSNP(lookupSNPName("rs377506522"), "chr7", 30951664)); // Coa,b / Coa-b- CO:3	CO*01.01 (wt)	CO*01.− 04 	Gln47Arg	rs377506522	[A/G]  TOP	[A/G]	7	30951664
}

std::string CColton::phenotype()
{
    vector<string> alleles;
    
    if(isRelevantGtMissing())
        return "#N/A,#N/A";
    
    CSNP rs28362692  = *(m_snps.find(CSNP(lookupSNPName("rs28362692"))));
    //CSNP rs377506522  = *(m_snps.find(CSNP(lookupSNPName("rs377506522"))));
    
    // Plus strand
    
        if(rs28362692.isHetero())
            alleles.push_back("Cob");
        if(rs28362692.isHomoFor("T"))
        {
            alleles.push_back("Cob");alleles.push_back("Cob");
        }
        alleles.push_back("Coa");
        alleles.push_back("Coa");
    
    result_vector_sorting(alleles);
    set<string> result;
    result.insert(alleles[0]);
    result.insert(alleles[1]);
    
    bool isA = result.find("Coa") != result.end();
    bool isB = result.find("Cob") != result.end();
    
    
    //return string("Co(a")+(isA ? "+" : "-")+"b"+(isB ? "+" : "-")+"),"+(result.find("CO:3") != result.end() ?  "CO:3" : "");
    return string("Co(a")+(isA ? "+" : "-")+"b"+(isB ? "+" : "-")+")";

}

