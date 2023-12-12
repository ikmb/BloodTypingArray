/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CJR.h
 * Author: mwittig
 *
 * Created on July 6, 2018, 8:57 AM
 */

#ifndef CJR_H
#define CJR_H

#include <set>

#include "CRBCsnps.h"
#include "CSNPNameLookupMixin.h"




class CJR : public CRBCsnps, public CSNPNameLookupMixin
{
public:
    CJR();
    CJR(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService);
    CJR(const CJR& orig);
    virtual ~CJR();
    
    
    std::string phenotype();
   
    
private:
    void initSNPs();
 
};


#endif /* CJR_H */

