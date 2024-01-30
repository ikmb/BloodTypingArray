/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CKnoops.cpp
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
#include "CKnoops.h"

using namespace std;

CKnoops::CKnoops() 
{
    initSNPs();
}

CKnoops::CKnoops(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService) {
    m_snp_name_lookup_service = snpNameLookupService;
    initSNPs();
}

CKnoops::CKnoops(const CKnoops& orig) 
{
    m_snps = orig.m_snps;
}

CKnoops::~CKnoops() {
}

void CKnoops::initSNPs() {
    m_snps.insert(CSNP(lookupSNPName("rs41274768"), "chr1", 207782769)); //Kna / Knb	CR1	KN*01 (wt)/KN*02	G/A	Val1561Met rs41274768	TOP	[A/G]	10618452	TAACTTACCAGTGCCACACTGGACCAGATGGAGAACAGCTGTTTGAGCTT			37	1	207782769
    m_snps.insert(CSNP(lookupSNPName("rs17047660"), "chr1", 207782856)); //McCa / McCb	CR1	KN*01 (wt)/KN*01.06	A/G	Lys1590Glu rs17047660	BOT	[T/C]	55707452	CCTGTTTCCTGGTACTCTAATTGCATTTTCAACTTCTGGAGCTGTGCATT			37	1	207782856
    m_snps.insert(CSNP(lookupSNPName("rs17047661"), "chr1", 207782889)); //Vil+ / Vil-	CR1	KN*01 (wt)/KN*01.07	A/G	Arg1601Gly rs17047661	BOT	[T/C]	52612325	AAATCTGATGATCTCAGTGAGGGTAAAGAAACTCCTGTTTCCTGGTACTC			37	1	207782889
}

std::string CKnoops::phenotype()
{
    vector<string> allelesKn;
    CSNP rs41274768  = *(m_snps.find(CSNP(lookupSNPName("rs41274768"))));
    // Plus strand
    if(rs41274768.isHetero())
        allelesKn.push_back("Knb");
    if(rs41274768.isHomoFor("A"))
    {
        allelesKn.push_back("Knb");allelesKn.push_back("Knb");
    }
    allelesKn.push_back("Kna");
    allelesKn.push_back("Kna");
 
    
    vector<string> allelesMc;
    CSNP rs17047660  = *(m_snps.find(CSNP(lookupSNPName("rs17047660"))));
    // Plus strand
    if(rs17047660.isHetero())
        allelesMc.push_back("McCb");
    if(rs17047660.isHomoFor("G"))
    {
        allelesMc.push_back("McCb");allelesMc.push_back("McCb");
    }
    allelesMc.push_back("McCa");
    allelesMc.push_back("McCa");
    
    vector<string> allelesVil;
    CSNP rs17047661  = *(m_snps.find(CSNP(lookupSNPName("rs17047661"))));
    // Plus strand
    if(rs17047661.isHetero())
        allelesVil.push_back("Vil+");
    if(rs17047661.isHomoFor("G"))
    {
        allelesVil.push_back("Vil+");allelesVil.push_back("Vil+");
    }
    allelesVil.push_back("Vil-");
    allelesVil.push_back("Vil-");
    

    result_vector_sorting(allelesKn);
    result_vector_sorting(allelesMc);
    result_vector_sorting(allelesVil);
    
    set<string> resultKn;
    resultKn.insert(allelesKn[0]);
    resultKn.insert(allelesKn[1]);
    bool isA = resultKn.find("Kna") != resultKn.end();
    bool isB = resultKn.find("Knb") != resultKn.end();
    string result_kn = string("Kn(")+(isA ? "a+" : "a-")+(isB ? "b+" : "b-")+")";
    
    set<string> resultMcC;
    resultMcC.insert(allelesMc[0]);
    resultMcC.insert(allelesMc[1]);
    
    isA = resultMcC.find("McCa") != resultMcC.end();
    isB = resultMcC.find("McCb") != resultMcC.end();
    string result_McC = string("McC(")+(isA ? "a+" : "a-")+(isB ? "b+" : "b-")+")";
    
    string resultVil = (allelesVil.size() > 2 ? "Vil+" : "Vil-");
    
    if(rs41274768.isNA())
        result_kn="#N/A";
    if(rs17047660.isNA())
        result_McC="#N/A";
    if(rs17047661.isNA())
        resultVil="#N/A";
    
    
    return result_kn+","+result_McC+","+resultVil;
    
}

