/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CIndian.h
 * Author: mwittig
 *
 * Created on July 6, 2018, 8:57 AM
 */

#ifndef CIndian_H
#define CIndian_H

#include <set>

#include "CRBCsnps.h"
#include "CSNPNameLookupMixin.h"




class CIndian : public CRBCsnps, public CSNPNameLookupMixin
{
public:
    CIndian();
    CIndian(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService);
    CIndian(const CIndian& orig);
    virtual ~CIndian();
    
    
    std::string phenotype();
   
    
private:
    void initSNPs();
  
};


#endif /* CIndian_H */

