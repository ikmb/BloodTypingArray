/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CDuffy.cpp
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
#include "CDuffy.h"

using namespace std;

CDuffy::CDuffy(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService) {
    m_snp_name_lookup_service = snpNameLookupService;
    m_snps.insert(CSNP(lookupSNPName("rs12075"),"chr1",159175354));    // Fya /Fyb	ACKR1	FY*02, or FY*B/FY*01, or FY*A	A/G	Asp42Gly	rs12075	TOP	[A/G]	1	159175354
    m_snps.insert(CSNP(lookupSNPName("rs34599082"),"chr1",159175494)); // Fyb / Fyx	ACKR1	FY*02/FY*02W.01	C/T	Arg89Cys	rs34599082	BOT	[T/C]	1	159175494
    m_snps.insert(CSNP(lookupSNPName("rs13962"),"chr1",159175527));    // Fyb / Fyb,x	ACKR1	FY*02/FY*02; FY*02W.01	G/A	Ala100Thr	rs13962	TOP	[A/G]	1	159175527
    m_snps.insert(CSNP(lookupSNPName("rs2814778"),"chr1",159174683));  // Fya,b / Fy null	DARC	FY*02/FY*02N.01	T/C	-	rs2814778	BOT	[T/C]	1	159174683
 
}

CDuffy::CDuffy(const CDuffy& orig) 
{
    m_snps = orig.m_snps;
}

CDuffy::~CDuffy() {
}

std::string CDuffy::phenotype()
{
    if(isRelevantGtMissing())
        return "#N/A";
    // PLUS strand
    vector<string> alleles;
    CSNP rs12075  = *(m_snps.find(CSNP(lookupSNPName("rs12075"))));
    CSNP rs34599082  = *(m_snps.find(CSNP(lookupSNPName("rs34599082"))));
    CSNP rs13962  = *(m_snps.find(CSNP(lookupSNPName("rs13962"))));
    CSNP rs2814778  = *(m_snps.find(CSNP(lookupSNPName("rs2814778"))));
    
    bool is_plus_w82 = false;
    bool is_plus_w62 = false;
    
    
    if(rs34599082.hasAllele("T"))
        is_plus_w82 = true;
    if(rs13962.hasAllele("A") && is_plus_w82)
        is_plus_w62 = true;
    
    if(rs2814778.isHetero()) // // FY*02N.01 (b-) -67T>C (rs2814778) 
        alleles.push_back("Fy null");
    if(rs2814778.isHomoFor("C"))
    {
        alleles.push_back("Fy null");alleles.push_back("Fy null");
    }
    
    if(rs12075.isHetero()) // FY*02 (b+) c.125G>A   (rs12075)   20,51%
    {
        if(rs2814778.isHomoFor("T")) // FY*02N.01 (b-) -67T>C (rs2814778) comes together with 125G>A, so if -67T>C is present it is very likely linked with 125G>A
            alleles.push_back("Fyb");
    }
    if(rs12075.isHomoFor("A"))
    {
        if(rs2814778.isHetero()) // see above. -67T>C is usually linked with 125G>A
            alleles.push_back("Fyb");
        else  if(rs2814778.isHomoFor("T"))
        {
            alleles.push_back("Fyb");alleles.push_back("Fyb");
        }
    }

    alleles.push_back("Fya");
    alleles.push_back("Fya");
    
    
    result_vector_sorting(alleles);
    // sort(alleles.begin(),alleles.end(),my_allele_sorting);
    set<string> result;
    result.insert(alleles[0]);
    result.insert(alleles[1]);
    
    bool isA = result.find("Fya") != result.end();
    bool isB = result.find("Fyb") != result.end();
    //bool isWplus = (isA && is_plus_w82) || (isB && is_plus_w82 && is_plus_w62);
    bool isWplus = (isA && is_plus_w82);
    
    
    
    return string("Fy(a")+(isA ? "+" : "-")+"b"+(isB ? "+" : "-")+(isWplus ? "w" : "" )+")";
    
}

