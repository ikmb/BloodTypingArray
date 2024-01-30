/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CKEL.cpp
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
#include "CKEL.h"

using namespace std;

CKEL::CKEL() 
{
    initSNPs();
}

CKEL::CKEL(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService) {
    m_snp_name_lookup_service = snpNameLookupService;
    initSNPs();
}

CKEL::CKEL(const CKEL& orig) 
{
    m_snps = orig.m_snps;
}

CKEL::~CKEL() {
}

void CKEL::initSNPs() {
    m_snps.insert(CSNP(lookupSNPName("ilmnseq_rs8176058.1_F2BT"), "chr7", 142655008)); // k / K	KEL	KEL*02 (wt)/KEL*01	578		C/T
    m_snps.insert(CSNP(lookupSNPName("ilmnseq_rs8176058.2_F2BT"), "chr7", 142655008)); // K,k / Kmod	KEL	KEL*02 (wt)/KEL*01M.01	578		C/G
    m_snps.insert(CSNP(lookupSNPName("rs8176059"), "chr7", 142651354)); // Kpa / Kpb	KEL	KEL*02 (wt)/KEL*02.03	841		C/T
    m_snps.insert(CSNP(lookupSNPName("rs8176038"), "chr7", 142640113)); // Jsa / Jsb	KEL	KEL*02 (wt)/KEL*02.06	T/C	Leu597Pro   rs81760387	142640113
    //m_snps.insert(CSNP(lookupSNPName("rs61729034","chr7",142651290);              // K11 / K17	KEL	KEL*02 (wt)/KEL*02.17	905		T/C 
    m_snps.insert(CSNP(lookupSNPName("rs369569464"), "chr7", 142658446)); // K, k / K0	KEL	KEL*02 (wt)/KEL*02N.06	223+1g>a	G/A
}

std::string CKEL::phenotype()
{
    // Minus strand
    vector<string> allelesKk;
    CSNP ilmnseq_rs8176058_1    = *(m_snps.find(CSNP(lookupSNPName("ilmnseq_rs8176058.1_F2BT"))));
    CSNP ilmnseq_rs8176058_2    = *(m_snps.find(CSNP(lookupSNPName("ilmnseq_rs8176058.2_F2BT"))));
    CSNP rs369569464    = *(m_snps.find(CSNP(lookupSNPName("rs369569464"))));
    
    if(ilmnseq_rs8176058_1.isHetero())
        allelesKk.push_back("k");
    if(ilmnseq_rs8176058_1.isHomoFor("G"))
    {
        allelesKk.push_back("k");allelesKk.push_back("k");
    }
    if(ilmnseq_rs8176058_2.isHetero())
        allelesKk.push_back("Kmod");
    if(ilmnseq_rs8176058_2.isHomoFor("C"))
    {
        allelesKk.push_back("Kmod");allelesKk.push_back("Kmod");
    }
    if(rs369569464.isHetero())
        allelesKk.push_back("K0");
    if(rs369569464.isHomoFor("T"))
    {
        allelesKk.push_back("K0");allelesKk.push_back("K0");
    }
    allelesKk.push_back("K");
    allelesKk.push_back("K");
    
    
    vector<string> allelesKp;
    CSNP rs8176059    = *(m_snps.find(CSNP(lookupSNPName("rs8176059"))));
    
    if(rs8176059.isHetero())
        allelesKp.push_back("Kp(a+)");
    if(rs8176059.isHomoFor("A"))
    {
        allelesKp.push_back("Kp(a+)");allelesKp.push_back("Kp(a+)");
    }
    allelesKp.push_back("Kp(b+)");
    allelesKp.push_back("Kp(b+)");
    
    
    vector<string> allelesJs;
    CSNP rs8176038    = *(m_snps.find(CSNP(lookupSNPName("rs8176038"))));
    
    if(rs8176038.isHetero())
        allelesJs.push_back("Js(a+)");
    if(rs8176038.isHomoFor("G"))
    {
        allelesJs.push_back("Js(a+)");allelesJs.push_back("Js(a+)");
    }
    allelesJs.push_back("Js(b+)");
    allelesJs.push_back("Js(b+)");
    

    result_vector_sorting(allelesKk);
    result_vector_sorting(allelesKp);
    result_vector_sorting(allelesJs);
    
    string resultKp = allelesKp[0]+allelesKp[1];

    if(resultKp.compare("Kp(a+)Kp(b+)") == 0)
        resultKp = "Kp(a+b+)";
    else if(resultKp.compare("Kp(a+)Kp(a+)") == 0)
        resultKp = "Kp(a+b-)";
    else if(resultKp.compare("Kp(b+)Kp(b+)") == 0)
        resultKp = "Kp(a-b+)";
    
    
    string resultJs = allelesJs[0]+allelesJs[1];

    if(resultJs.compare("Js(a+)Js(b+)") == 0)
        resultJs = "Js(a+b+)";
    else if(resultJs.compare("Js(a+)Js(a+)") == 0)
        resultJs = "Js(a+b-)";
    else if(resultJs.compare("Js(b+)Js(b+)") == 0)
        resultJs = "Js(a-b+)";
    
    string resultKk = allelesKk[0]+allelesKk[1];
    if(ilmnseq_rs8176058_1.isNA() && (ilmnseq_rs8176058_1.getNormTheta() > 0.6f || ilmnseq_rs8176058_1.getNormTheta() < 0.35f ) )
        resultKk="#N/A";
    
    if(rs8176059.isNA())
        resultKp = "#N/A";
    if(rs8176038.isNA())
        resultJs="#N/A";
    
    
    return resultKk+","+resultKp+","+resultJs;
    
}

