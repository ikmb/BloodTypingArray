/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CLU.cpp
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
#include "CLU.h"

using namespace std;

CLU::CLU() 
{
    initSNPs();
}

CLU::CLU(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService) {
    m_snp_name_lookup_service = snpNameLookupService;
    initSNPs();
}

CLU::CLU(const CLU& orig) 
{
    m_snps = orig.m_snps;
}

CLU::~CLU() {
}

void CLU::initSNPs() {
    CSNP b(lookupSNPName("ilmnseq_rs28399653.1_F2BT"), "chr19", 45315445); //Lub / Lua	BCAM	LU*02 (wt)/LU*01	G/A	Arg77His
    m_snps.insert(b);
    CSNP c(lookupSNPName("rs28399656"), "chr19", 45316704); // Lu8 / Lu14	BCAM	LU*02 (wt)/LU*02.14 	T/A	Met204Lys
    m_snps.insert(c);
    CSNP e(lookupSNPName("rs1135062"), "chr19", 45322744); // Aua / Aub	BCAM	LU*02 (wt)/LU*02.19 	A/G	Thr539Ala
    m_snps.insert(e);
}

std::string CLU::phenotype()
{
    
    // PLUS strand
    vector<string> alleles;
    vector<string> allelesLu;
    vector<string> allelesAu;
    CSNP ilmnseq_rs28399653  = *(m_snps.find(CSNP(lookupSNPName("ilmnseq_rs28399653.1_F2BT"))));
    CSNP rs28399656 = *(m_snps.find(CSNP(lookupSNPName("rs28399656"))));
    CSNP rs1135062  = *(m_snps.find(CSNP(lookupSNPName("rs1135062"))));
    
    if(ilmnseq_rs28399653.isHetero())
        alleles.push_back("Lu(a+)");
    if(ilmnseq_rs28399653.isHomoFor("A"))
    {
        alleles.push_back("Lu(a+)");alleles.push_back("Lu(a+)");
    }
    alleles.push_back("Lu(b+)");
    alleles.push_back("Lu(b+)");
    
    if(rs28399656.isHetero())
        allelesLu.push_back("Lu14");
    if(rs28399656.isHomoFor("A"))
    {
        allelesLu.push_back("Lu14");allelesLu.push_back("Lu14");
    }
    allelesLu.push_back("Lu8");
    allelesLu.push_back("Lu8");
    
    
    if(rs1135062.isHetero())
    {
        allelesAu.push_back("Au(b+)");
    }
    if(rs1135062.isHomoFor("G"))
    {
        allelesAu.push_back("Au(b+)");;allelesAu.push_back("Au(b+)");
    }
    allelesAu.push_back("Au(a+)");
    allelesAu.push_back("Au(a+)");

    result_vector_sorting(alleles);
    result_vector_sorting(allelesAu);
    result_vector_sorting(allelesLu);
    
    
    string result = alleles[0]+alleles[1];

    if(result.compare("Lu(a+)Lu(b+)") == 0)
        result = "Lu(a+b+)";
    else if(result.compare("Lu(a+)Lu(a+)") == 0)
        result = "Lu(a+b-)";
    else if(result.compare("Lu(b+)Lu(b+)") == 0)
        result = "Lu(a-b+)";
    
    set<string> resultAu;
    resultAu.insert(allelesAu[0]);
    resultAu.insert(allelesAu[1]);
    
    bool isA = resultAu.find("Au(a+)") != resultAu.end();
    bool isB = resultAu.find("Au(b+)") != resultAu.end();
    string result_au = string("Au(") + (isA ? "a+" : "a-") + (isB ? "b+" : "b-") + ")";
    
    set<string> resultLU;
    resultLU.insert(allelesLu[0]);
    resultLU.insert(allelesLu[1]);
    
    isA = resultLU.find("Lu8") != resultLU.end();
    isB = resultLU.find("Lu14") != resultLU.end();
    string result_LU = string("")+(isA ? "Lu8+" : "Lu8-") + (isB ? "Lu14+" : "Lu14-");
    
    if(ilmnseq_rs28399653.isNA())
        result = "#N/A";
    if(rs1135062.isNA())
        result_au = "#N/A";
    if(rs28399656.isNA())
        result_LU = "#N/A";
    
    return result + "," + result_au  + "," + result_LU;
    
}

