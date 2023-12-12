/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CLan.cpp
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
#include "CLan.h"

using namespace std;

CLan::CLan() 
{
    initSNPs();
}

CLan::CLan(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService) {
    m_snp_name_lookup_service = snpNameLookupService;
    initSNPs();
}

CLan::CLan(const CLan& orig) 
{
    m_snps = orig.m_snps;
}

CLan::~CLan() {
}

void CLan::initSNPs() {
    m_snps.insert(CSNP(lookupSNPName("rs149202834"), "chr2", 220082505)); // Lan+/Lan-	 ABCB6  ABCB6*01 (wt)/ABCB6*01N.13	C/T	Arg192Trp   rs149202834	BOT	[T/C]	2	220082505
    m_snps.insert(CSNP(lookupSNPName("rs145526996"), "chr2", 220078006)); // Lan+/Lan weak ABCB6  ABCB6*01 (wt)/ABCB6*01W.03	G/A	Gly588Ser   rs145526996	BOT	[T/C]	2	220078006
    m_snps.insert(CSNP(lookupSNPName("rs376664522"), "chr2", 220077135)); // Lan+/Lan-	 ABCB6	ABCB6*01 (wt)/ABCB6*01N.08	C/T	Arg648X     rs376664522	TOP	[A/G]	2	220077135
}

std::string CLan::phenotype()
{
    vector<string> alleles;
    if(isRelevantGtMissing())
        return "#N/A";
    
    CSNP rs149202834  = *(m_snps.find(CSNP(lookupSNPName("rs149202834"))));
    // Reverse strand
    if(rs149202834.isHetero())
        alleles.push_back("Lan-");
    if(rs149202834.isHomoFor("A"))
    {
        alleles.push_back("Lan-");alleles.push_back("Lan-");
    }
    
    CSNP rs145526996  = *(m_snps.find(CSNP(lookupSNPName("rs145526996"))));
    if(rs145526996.isHetero())
        alleles.push_back("Lan weak");
    if(rs145526996.isHomoFor("T"))
    {
        alleles.push_back("Lan weak");alleles.push_back("Lan weak");
    }
    
    CSNP rs376664522  = *(m_snps.find(CSNP(lookupSNPName("rs376664522"))));
    if(rs376664522.isHetero())
        alleles.push_back("Lan-");
    if(rs376664522.isHomoFor("A"))
    {
        alleles.push_back("Lan-");alleles.push_back("Lan-");
    }
    alleles.push_back("Lan+");
    alleles.push_back("Lan+");
    
    result_vector_sorting(alleles);
    
    
    set<string> result;
    result.insert(alleles[0]);
    result.insert(alleles[1]);
    
    bool isPlus = result.find("Lan+") != result.end();
    bool isMinus = result.find("Lan-") != result.end();
    bool isWeak = result.find("Lan weak") != result.end();
    
    if(isPlus)
        return "Lan+";
    if(isWeak)
        return "Lan weak";
    return "Lan-";
    
}

