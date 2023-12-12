/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CKnoops.h
 * Author: mwittig
 *
 * Created on July 6, 2018, 8:57 AM
 */

#ifndef CKnoops_H
#define CKnoops_H

#include <set>

#include "CRBCsnps.h"
#include "CSNPNameLookupMixin.h"




class CKnoops : public CRBCsnps, public CSNPNameLookupMixin
{
public:
    CKnoops();
    CKnoops(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService);
    CKnoops(const CKnoops& orig);
    virtual ~CKnoops();
    
    
    std::string phenotype();
   
    
private:
    void initSNPs();
  
};


#endif /* CKnoops_H */

