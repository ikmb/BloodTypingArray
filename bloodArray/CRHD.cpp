/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CRHD.cpp
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
#include "CRHD.h"

using namespace std;

CRHD::CRHD() 
{
    initSNPs();
}

CRHD::CRHD(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService) {
    m_snp_name_lookup_service = snpNameLookupService;
    initSNPs();
}

CRHD::CRHD(const CRHD& orig) 
{
    m_snps = orig.m_snps;
}

CRHD::~CRHD() {
}

void CRHD::initSNPs() {
    /*
    m_snps.insert(CSNP(lookupSNPName("ilmnseq_rs371491457.2_F2BT"), "chr1", 0));
    m_snps.insert(CSNP(lookupSNPName("ilmnseq_rs564084745"), "chr1", 0));
    m_snps.insert(CSNP(lookupSNPName("ilmnseq_rs562501507"), "chr1", 0));
    m_snps.insert(CSNP(lookupSNPName("rs182479103"), "chr1", 0));
    m_snps.insert(CSNP(lookupSNPName("ilmnseq_rs532072917"), "chr1", 0));
    m_snps.insert(CSNP(lookupSNPName("ilmnseq_rs557059432.1_F2BT"), "chr1", 0));
    m_snps.insert(CSNP(lookupSNPName("RHD-785delA"), "chr1", 0));
    m_snps.insert(CSNP(lookupSNPName("ilmnseq_rs590787.1_F2BT"), "chr1", 0));
    */
    m_snps.insert(CSNP(lookupSNPName("rs17418085"), "chr1", 0));
    m_snps.insert(CSNP(lookupSNPName("rs3118454"), "chr1", 0));

}




std::string CRHD::phenotype()
{
    /*
    int count_na = 0;
    const string snps[] = {lookupSNPName("ilmnseq_rs371491457.2_F2BT"),
                           lookupSNPName("ilmnseq_rs564084745"), 
                           lookupSNPName("ilmnseq_rs562501507"), 
                           lookupSNPName("rs182479103"), 
                           lookupSNPName("ilmnseq_rs532072917"), 
                           lookupSNPName("ilmnseq_rs557059432.1_F2BT"), 
                           lookupSNPName("RHD-785delA"), 
                           lookupSNPName("ilmnseq_rs590787.1_F2BT")};
    
    for(int idx = 0; idx < m_snps.size(); idx ++)
    {
        CSNP SNPID  = *(m_snps.find(CSNP(snps[idx])));

        // Reverse strand
        if(SNPID.isNA())
            count_na++;
    }

    return (count_na >= 5 ? "dd" : "D.");
    */
    // SNP               pos   RhCE RhD
    // rs17418085	c.455	C   A
    // rs3118454	c.787   A   G
    if(isRelevantGtMissing())
        return "#N/A";
    
    CSNP rs17418085    = *(m_snps.find(CSNP(lookupSNPName("rs17418085"))));
    CSNP rs3118454    = *(m_snps.find(CSNP(lookupSNPName("rs3118454"))));
    
    string pseudo_call="";
    if(rs17418085.hasAllele("A") && rs3118454.hasAllele("G"))
        return "D.";
    return "dd";



    
}

