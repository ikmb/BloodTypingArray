/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CMNS.cpp
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
#include "CMNS.h"

using namespace std;

CMNS::CMNS() 
{   
    initSNPs();
}

CMNS::CMNS(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService) {
    m_snp_name_lookup_service = snpNameLookupService;
    initSNPs();
}

CMNS::CMNS(const CMNS& orig) 
{
    m_snps = orig.m_snps;
}

CMNS::~CMNS() {
}

void CMNS::initSNPs() {
    CSNP a(lookupSNPName("rs7682260"), "chr4", 145041720); // M / N GYPA	GYPA*01/GYPA*02	59	C/T	Ser20Leu
    m_snps.insert(a);
    CSNP b(lookupSNPName("rs7687256"), "chr4", 145041708); // M / N GYPA GYPA*01/GYPA*02	71	G/A	Gly24Gly
    m_snps.insert(b);
    CSNP c(lookupSNPName("rs7658293"), "chr4", 145041707); // M / N GYPA	GYPA*01/GYPA*02		72		T/G
    m_snps.insert(c);
    CSNP d(lookupSNPName("rs7683365"), "chr4", 143999443); // MN / Vw GYPB    GYPA*01/GYPA*09	140		C/T	Thr47Met
    m_snps.insert(d);
    /*
     MNS:
    - Alleles M/N
    -- check rs7682260, rs7687256,rs7658293. If they are heterozygous we have M/N. If they are homozygous for the alternative allele we have N/N and vice versa. One SNP is enough to evaluate this, multiple SNPs telling the same give more confidence.
    - Alleles S/s
    -- check rs7683365. C identifies s and T identifies S 
     
     */
}

std::string CMNS::phenotype()
{
    vector<string> M_alleles;
    vector<string> N_alleles;
    CSNP rs7682260  = *(m_snps.find(CSNP(lookupSNPName("rs7682260")))); // c.59C>T
    CSNP rs7687256  = *(m_snps.find(CSNP(lookupSNPName("rs7687256")))); // c.71G>A
    CSNP rs7658293  = *(m_snps.find(CSNP(lookupSNPName("rs7658293")))); // c.72T>G
    CSNP rs7683365  = *(m_snps.find(CSNP(lookupSNPName("rs7683365"))));

    // I am just using one of the three M/N SNPs at this early stage. Please change SNPs if necessary
    // later we can add redundant genotyping to increase confidence
    
    
    // MINUS STRAND Transcript GYPA/GYPB
    vector<string> MN_alleles;
    vector<string> S_alleles;   
    
    if(rs7682260.isHetero())
        MN_alleles.push_back("N");
    if(rs7682260.isHomoFor("A"))
    {
        MN_alleles.push_back("N");MN_alleles.push_back("N");
    }
    MN_alleles.push_back("M");
    MN_alleles.push_back("M");
    result_vector_sorting(MN_alleles);

    if(rs7683365.isHetero())
        S_alleles.push_back("s");
    if(rs7683365.isHomoFor("G"))
    {
        S_alleles.push_back("s");S_alleles.push_back("s");
    }
    S_alleles.push_back("S");
    S_alleles.push_back("S");
    result_vector_sorting(S_alleles);

    return string("MNS(")+MN_alleles[0]+MN_alleles[1]+string(",")+S_alleles[0]+S_alleles[1]+string(")");
    
}

