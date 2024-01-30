/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CKidd.cpp
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
#include "CKidd.h"

using namespace std;

CKidd::CKidd() 
{
    initSNPs();
}

CKidd::CKidd(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService) {
    m_snp_name_lookup_service = snpNameLookupService;
    initSNPs();
}

CKidd::CKidd(const CKidd& orig) 
{
    m_snps = orig.m_snps;
}

CKidd::~CKidd() {
}

void CKidd::initSNPs() {
    m_snps.insert(CSNP(lookupSNPName("rs1058396"), "chr18", 43319519));
    m_snps.insert(CSNP(lookupSNPName("rs78937798"), "chr18", 43314238));
    m_snps.insert(CSNP(lookupSNPName("ilmnseq_rs34756616.2_F2BT"), "chr18", 43316532)); //
    m_snps.insert(CSNP(lookupSNPName("rs78242949"), "chr18", 43319552)); //
     
}

std::string CKidd::phenotype()
{
    if(isRelevantGtMissing())
        return "#N/A";
    
    vector<string> alleles;
    // MALDI
    CSNP rs1058396  = *(m_snps.find(CSNP(lookupSNPName("rs1058396")))); // Jka /Jkb	SLC14A1	18q	JK*01, or JK*A	JK*02, or JK*B	G/A Asn280Asp
    // MALDI rs78937798 NULL allele  JK*01N.06, JK*02N.01, JK*02N.02. So, one 01 and two 02 alleles
    CSNP rs78937798 = *(m_snps.find(CSNP(lookupSNPName("rs78937798")))); // Jka,b / Jk null	SLC14A1	18q	JK*02	JK*02N.02	342-1g>c	G	C	-
    // MALDI rs34756616 in ISBT table under Null phenotypes, JK*01 alleles
    CSNP ilmnseq_rs34756616 = *(m_snps.find(CSNP(lookupSNPName("ilmnseq_rs34756616.2_F2BT")))); // Jka,b / Jk null	JK*01	JK*01N.03	582	C 	G	Tyr194Stop
    // rs78242949in ISBT table under Null phenotypes, JK*02 alleles
    CSNP rs78242949 = *(m_snps.find(CSNP(lookupSNPName("rs78242949")))); // Jka,b / Jk null	18q11-q12	JK*02	JK*02N.06	871	T	C	Ser291Pro

    //& PLUS strand 
    // Die Deletion kodiert für das häufige O-Allel (O1), und ist der "kausale" SNP 
    // (es gibt keine funktionierende Glycosyltransferase, da vorzeitiger Kettenabbruch an der berühmten kodierenden Base 261, Exon 6). 
    // Alle folgenden Allele haben diese Deletion NICHT.
    
    
    int isNullA=0;
    int isNullB=0;
    
    
    
    if(rs78937798.isHetero())
    {
        if(!rs1058396.isHomoFor("G"))
            isNullB++;
    }
    else if(!rs78937798.isHomoFor("G"))
    {
        if(rs1058396.isHomoFor("A"))
            isNullB+=2;
        if(rs1058396.isHetero())
        {
            isNullA++;isNullB++;
        }
        if(rs1058396.isHomoFor("G"))
            isNullA+=2;
    }
    if(ilmnseq_rs34756616.isHetero())
        isNullA++;
    if(ilmnseq_rs34756616.isHomoFor("G"))
        isNullA+=2;
    if(rs78242949.isHetero())
        isNullB++;
    if(rs78242949.isHomoFor("C"))
        isNullB+=2;
    
    if(rs1058396.isHetero())
        alleles.push_back("Jkb");
    if(rs1058396.isHomoFor("A"))
    {
        alleles.push_back("Jkb");alleles.push_back("Jkb");
    }
    alleles.push_back("Jka");
    alleles.push_back("Jka");
    result_vector_sorting(alleles);

    multiset<string> result;
    result.insert(alleles[0]);
    result.insert(alleles[1]);
    
    // Turn into NULL alleles
    while(isNullA-->0)
        result.erase(result.find("Jka"));
    while(isNullB-->0)
        result.erase(result.find("Jkb"));
    
    bool isA = result.find("Jka") != result.end();
    bool isB = result.find("Jkb") != result.end();
    
    
    return string("Jk(a")+(isA ? "+" : "-")+"b"+(isB ? "+" : "-")+")";
    
}

