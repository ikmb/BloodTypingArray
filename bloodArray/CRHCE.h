/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CRHCE.h
 * Author: mwittig
 *
 * Created on July 6, 2018, 8:57 AM
 */

#ifndef CRHCE_H
#define CRHCE_H

#include <set>

#include "CRBCsnps.h"
#include "CSNPNameLookupMixin.h"




class CRHCE : public CRBCsnps, public CSNPNameLookupMixin
{
public:
    CRHCE();
    CRHCE(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService);
    CRHCE(const CRHCE& orig);
    virtual ~CRHCE();
    
    
    std::string phenotype();
   
    
private:
    void initSNPs();
   
};


#endif /* CRHCE_H */

