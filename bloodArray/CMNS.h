/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CMNS.h
 * Author: mwittig
 *
 * Created on July 6, 2018, 8:57 AM
 */

#ifndef CMNS_H
#define CMNS_H

#include <set>

#include "CRBCsnps.h"
#include "CSNPNameLookupMixin.h"




class CMNS : public CRBCsnps, public CSNPNameLookupMixin
{
public:
    CMNS();
    CMNS(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService);
    CMNS(const CMNS& orig);
    virtual ~CMNS();
    
    
    std::string phenotype();
   
    
private:
    void initSNPs();
 
};


#endif /* CMNS_H */

