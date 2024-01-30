/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CABO.cpp
 * Author: mwittig
 * 
 * Created on July 6, 2018, 8:57 AM
 */
#include <string>
#include <set>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <regex>

#include "CSNP.h"

#include "CRBCsnps.h"
#include "CABO.h"

using namespace std;

CABO::CABO() 
{
    initSNPs();
}

CABO::CABO(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService) {
    m_snp_name_lookup_service = snpNameLookupService;
    initSNPs();
}

CABO::CABO(const CABO& orig) 
{
    m_snps = orig.m_snps;
}

CABO::~CABO() {
}

void CABO::initSNPs() {
    m_snps.insert(CSNP(lookupSNPName("rs8176747"), "chr9", 136131315));
    m_snps.insert(CSNP(lookupSNPName("rs41302905"), "chr9", 136131316));
    m_snps.insert(CSNP(lookupSNPName("rs8176719"), "chr9", 136132908)); // T is deletion and TC is insertion
}

std::string CABO::phenotype(bool trivial)
{
    if(isRelevantGtMissing())
        return "#N/A";
    vector<string> alleles;
    CSNP rs8176747  = *(m_snps.find(CSNP(lookupSNPName("rs8176747"))));
    CSNP rs41302905 = *(m_snps.find(CSNP(lookupSNPName("rs41302905"))));
    CSNP rs8176719  = *(m_snps.find(CSNP(lookupSNPName("rs8176719"))));
    
    // Die Deletion kodiert für das häufige O-Allel (O1), und ist der "kausale" SNP 
    // (es gibt keine funktionierende Glycosyltransferase, da vorzeitiger Kettenabbruch an der berühmten kodierenden Base 261, Exon 6). 
    // Alle folgenden Allele haben diese Deletion NICHT.
    if(rs8176719.isHetero())
        alleles.push_back("O1");
    if(rs8176719.isHomoFor("D"))
    {
        alleles.push_back("O1");alleles.push_back("O1");
    }
    
    // Das seltene A kodiert für das 2. häufigste O-Allel (O2) und ist der "kausale" SNP (kodierende Base 802, Gly268Arg)! 
    // Und ist ansonsten "normal" = entspricht, glaube ich (!), in den allermeisten anderen Positionen dem kaukasischen (häufigen) Wildtyp.
    if(rs41302905.isHetero())
        alleles.push_back("O2");
    if(rs41302905.isHomoFor("T"))
    {
        alleles.push_back("O2");alleles.push_back("O2");
    }

    // Das seltene C kodiert für Blutgruppe B, und ist der "kausale" SNP (kodierende Base 803, Gly268Ala)! 
    // Das Blutgruppe B-Allel hat darüber hinaus viele zusätzliche gelinkte, "spezifische" allelische Varianten an anderen Genpositionen. 
    // Das, glaube ich, verwendet Ihr gerne "for imputation", richtig? Allel für Blutgruppe A: ist "normal" (nicht O1, nicht O2, nicht B) 
    // an den genannten Positionen. Dieses Allel wird also immer per Ausschluss der anderen definiert. 
    if(rs8176747.isHetero())
        alleles.push_back("B");
    if(rs8176747.isHomoFor("G"))
    {
        alleles.push_back("B");alleles.push_back("B");
    }

    alleles.push_back("A");
    alleles.push_back("A");
    

    result_vector_sorting(alleles);
    
    string result = alleles[0]+alleles[1];
       
    if(trivial)
    {
        std::regex e ("O1|O2");   // matches words beginning by "sub"
        result = std::regex_replace (result,e,"O");
        e = std::regex("A1|A2");   // matches words beginning by "sub"
        result = std::regex_replace (result,e,"A");
        e = std::regex("AA|AO");   // matches words beginning by "sub"
        result = std::regex_replace (result,e,"A");
        e = std::regex("BB|BO");   // matches words beginning by "sub"
        result = std::regex_replace (result,e,"B");
        e = std::regex("OO");   // matches words beginning by "sub"
        result = std::regex_replace (result,e,"O");
    }
   
    return result;
    
}

