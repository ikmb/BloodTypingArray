/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CJR.cpp
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
#include "CJR.h"

using namespace std;

CJR::CJR() 
{
    initSNPs();
}

CJR::CJR(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService) {
    m_snp_name_lookup_service = snpNameLookupService;
    initSNPs();
}

CJR::CJR(const CJR& orig) 
{
    m_snps = orig.m_snps;
}

CJR::~CJR() {
}

void CJR::initSNPs() {
    m_snps.insert(CSNP(lookupSNPName("ilmnseq_rs201121511"), "chr4", 89052996)); // JR	Jr(a+)/Jr(a-)	ABCG2   ABCG2*01 (wt)/ABCG2*01N.04	C/T	Arg113X ilmnseq_rs201121511	BOT	[T/C]	4	89052996
    m_snps.insert(CSNP(lookupSNPName("rs72552713"), "chr4", 89052957)); // JR	Jr(a+)/Jr(a-)	ABCG2	ABCG2*01 (wt)/ABCG2*01N.01	C/T	Gln126X	rs72552713	TOP	[A/G]	4	89052957
    m_snps.insert(CSNP(lookupSNPName("ilmnseq_rs140207606.1_F2BT"), "chr4", 89039396)); // JR	Jr(a+)/Jr(a-)	ABCG2	ABCG2*01 (wt)/ABCG2*01N.02	C/T	Arg236X ilmnseq_rs140207606.1_F2BT	BOT	[T/C]	4	89039396
    m_snps.insert(CSNP(lookupSNPName("JR-730C>T"), "chr4", 89039372)); // JR	Jr(a+)/Jr(a-)	ABCG2	ABCG2*01 (wt)/ABCG2*01N.09	C/T	Gln244X JR-730C>T	TOP	[A/G]	4	89039372
    m_snps.insert(CSNP(lookupSNPName("rs200190472"), "chr4", 89039366)); // JR	Jr(a+)/Jr(a-)	ABCG2	ABCG2*01 (wt)/ABCG2*01N.03 	C/T	Arg246X rs200190472	BOT	[T/C]	4	89039366
    m_snps.insert(CSNP(lookupSNPName("rs200473953"), "chr4", 89039318)); // JR	Jr(a+)/Jr(a-)	ABCG2	ABCG2*01 (wt)/ABCG2*01N.05	G/T	Gly262X rs200473953	TOP	[A/C]	4	89039318
    m_snps.insert(CSNP(lookupSNPName("rs387906870"), "chr4", 89039310)); // JR	Jr(a+)/Jr(a-)	ABCG2	ABCG2*01 (wt)/ABCG2*01N.10 	TT/-	Leu264HisfsX	rs387906870	PLUS	[I/D]	4	89039310
}

std::string CJR::phenotype()
{
    vector<string> alleles;
    
    if(isRelevantGtMissing())
        return "#N/A";
    
    
    const string snps[] = {lookupSNPName("ilmnseq_rs201121511"),lookupSNPName("rs72552713"),lookupSNPName("ilmnseq_rs140207606.1_F2BT"),lookupSNPName("JR-730C>T"),lookupSNPName("rs200190472"),lookupSNPName("rs200473953")};
    
    for(int idx = 0; idx < 6; idx ++)
    {
        CSNP SNPID  = *(m_snps.find(CSNP(snps[idx])));

        // Reverse strand
        if(SNPID.isHetero())
            alleles.push_back("Jr(a-)");
        if(SNPID.isHomoFor("A"))
        {
            alleles.push_back("Jr(a-)");alleles.push_back("Jr(a-)");
        }
        
    }
    
    CSNP rs387906870  = *(m_snps.find(CSNP(lookupSNPName("rs387906870"))));

    // Reverse strand
    if(rs387906870.isHetero())
        alleles.push_back("Jr(a-)");
    if(rs387906870.isHomoFor("D"))
    {
        alleles.push_back("Jr(a-)");alleles.push_back("Jr(a-)");
    }
    alleles.push_back("Jr(a+)");
    alleles.push_back("Jr(a+)");
    // sort(alleles.begin(),alleles.end(),my_allele_sorting);
    
    result_vector_sorting(alleles);
    
    return alleles.size() > 2 ? "Jr(a-)" : "Jr(a+)";
    
}

