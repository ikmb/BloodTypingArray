/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CColton.h
 * Author: mwittig
 *
 * Created on July 6, 2018, 8:57 AM
 */

#ifndef CColton_H
#define CColton_H

#include <set>

#include "CRBCsnps.h"
#include "CSNPNameLookupMixin.h"




class CColton : public CRBCsnps, public CSNPNameLookupMixin
{
public:
    CColton();
    CColton(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService);
    CColton(const CColton& orig);
    virtual ~CColton();
    
    
    std::string phenotype();
   
    
private:
    void initSNPs();
    
};


#endif /* CColton_H */

