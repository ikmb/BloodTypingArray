/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CKidd.h
 * Author: mwittig
 *
 * Created on July 6, 2018, 8:57 AM
 */

#ifndef CKidd_H
#define CKidd_H

#include <set>

#include "CRBCsnps.h"
#include "CSNPNameLookupMixin.h"




class CKidd : public CRBCsnps, public CSNPNameLookupMixin
{
public:
    CKidd();
    CKidd(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService);
    CKidd(const CKidd& orig);
    virtual ~CKidd();
    
    
    std::string phenotype();
   
    
private:
    void initSNPs();

};


#endif /* CKidd_H */

