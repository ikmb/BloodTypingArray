/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CRBCsnps.h
 * Author: mwittig
 *
 * Created on July 11, 2018, 8:06 AM
 */

#ifndef CRBCSNPS_H
#define CRBCSNPS_H

#include <set>
#include <iostream>

class CRBCsnps {
public:
    CRBCsnps();
    CRBCsnps(const CRBCsnps& orig);
    virtual ~CRBCsnps();
    
    friend std::ostream& operator<<(std::ostream& os, const CRBCsnps& me);
    
    std::string gt(const std::string& delim = "/",bool reverse_compl = false)const;
    std::string gt_header()const;
    
    /// adds a new SNP or overwrites the current SNP
    void addSNP(const CSNP& v){m_snps.erase(v);m_snps.insert(v);}
    /// Overwrites the genotype data of a current SNP. Does nothing if the SNP is not already stored
    /// I use this to update SNPs that are added in the constructor ...
    void updateSNPcall(const CSNP& v){if(m_snps.find(v) != m_snps.end()){m_snps.erase(v);m_snps.insert(v);}}
    
    bool isRelevantSnpId(const std::string& id)const;
    bool isRelevantGtMissing()const;
    
    std::string getSNPsAsString(const std::string& separator=",", const std::string& prefix="", const std::string& suffix="") const;
    
    
private:

protected:
    std::set<CSNP>  m_snps;
    
    void result_vector_sorting(std::vector<std::string>& v);
    bool remove_phenotype(std::vector<std::string>& v, const std::string& phen);
};

bool my_allele_sorting(const std::string& a, const std::string& b);


#endif /* CRBCSNPS_H */

