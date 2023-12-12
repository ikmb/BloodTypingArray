/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CDombrock.cpp
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
#include "CDombrock.h"

using namespace std;

CDombrock::CDombrock() 
{
    initSNPs();
}

CDombrock::CDombrock(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService) {
    m_snp_name_lookup_service = snpNameLookupService;
    initSNPs();
}

CDombrock::CDombrock(const CDombrock& orig) 
{
    m_snps = orig.m_snps;
}

CDombrock::~CDombrock() {
}

void CDombrock::initSNPs() {
    m_snps.insert(CSNP(lookupSNPName("rs11276"), "chr12", 14993439)); // Dombrock	014	Doa / Dob	ART4	DO*01(wt)	DO*02	A	G	Asn265Asp   rs11276	12	14993439
    m_snps.insert(CSNP(lookupSNPName("rs28362797"), "chr12", 14993909)); // Dombrock	014	Hy+ / Hy-	ART4	DO*02	DO*02.–04	G	T	Gly108Val   rs28362797	12	14993909
    m_snps.insert(CSNP(lookupSNPName("ilmnseq_rs28362798.1_F2BT"), "chr12", 14993882)); // Dombrock	014	Jo(a+) / Jo(a-)	ART4	DO*02	DO*01.–05	C	T	Thr117Ile   ilmnseq_rs28362798.1_F2BT	12	14993882
}

std::string CDombrock::phenotype()
{
    vector<string> allelesD;
    vector<string> allelesH;
    vector<string> allelesJ;
    
    CSNP rs11276  = *(m_snps.find(CSNP(lookupSNPName("rs11276"))));
    CSNP rs28362797  = *(m_snps.find(CSNP(lookupSNPName("rs28362797"))));
    CSNP ilmnseq_rs28362798  = *(m_snps.find(CSNP(lookupSNPName("ilmnseq_rs28362798.1_F2BT"))));
    
    // Reverse strand
    if(rs11276.isHetero())
        allelesD.push_back("Do(b+)");
    if(rs11276.isHomoFor("C"))
    {
        allelesD.push_back("Do(b+)");allelesD.push_back("Do(b+)");
    }
    allelesD.push_back("Do(a+)");
    allelesD.push_back("Do(a+)");
    
    
    if(rs28362797.isHetero())
        allelesH.push_back("Hy-");
    if(rs28362797.isHomoFor("A"))
    {
        allelesH.push_back("Hy-");allelesH.push_back("Hy-");
    }
    allelesH.push_back("Hy+");
    allelesH.push_back("Hy+");
    
    if(ilmnseq_rs28362798.isHetero())
        allelesJ.push_back("Jo(a-)");
    if(ilmnseq_rs28362798.isHomoFor("A"))
    {
        allelesJ.push_back("Jo(a-)");allelesJ.push_back("Jo(a-)");
    }
    allelesJ.push_back("Jo(a+)");
    allelesJ.push_back("Jo(a+)");
    
    
    result_vector_sorting(allelesD);
    result_vector_sorting(allelesH);
    result_vector_sorting(allelesJ);
    
    set<string> resultD;
    resultD.insert(allelesD[0]);
    resultD.insert(allelesD[1]);
    bool isA = resultD.find("Do(a+)") != resultD.end();
    bool isB = resultD.find("Do(b+)") != resultD.end();
    string result_out_d = string("Do(a")+(isA ? "+" : "-")+"b"+(isB ? "+" : "-")+")";
    string result_out_Hy = (allelesH.size() == 4 ?  ",Hy-" : ",Hy+");
    string result_out_Jo = (allelesJ.size() == 4 ?  ",Jo-" : ",Jo+");
    
    if(rs11276.isNA())
        result_out_d="#N/A";
    if(rs28362797.isNA())
        result_out_Hy=",#N/A";
    if(ilmnseq_rs28362798.isNA())
        result_out_Jo=",#N/A";
    
    
    return result_out_d+result_out_Hy +result_out_Jo;
    
}

