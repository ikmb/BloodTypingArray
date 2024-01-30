/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CCartwright.h
 * Author: mwittig
 *
 * Created on July 6, 2018, 8:57 AM
 */

#ifndef CCartwright_H
#define CCartwright_H

#include <set>

#include "CRBCsnps.h"
#include "CSNPNameLookupMixin.h"




class CCartwright : public CRBCsnps, public CSNPNameLookupMixin
{
public:
    CCartwright();
    CCartwright(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService);
    CCartwright(const CCartwright& orig);
    virtual ~CCartwright();
    
    
    std::string phenotype();
   
    
private:
    void initSNPs();
    
};


#endif /* CCartwright_H */

