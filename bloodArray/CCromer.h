/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CCromer.h
 * Author: mwittig
 *
 * Created on July 6, 2018, 8:57 AM
 */

#ifndef CCromer_H
#define CCromer_H

#include <set>

#include "CRBCsnps.h"
#include "CSNPNameLookupMixin.h"




class CCromer : public CRBCsnps, public CSNPNameLookupMixin
{
public:
    CCromer();
    CCromer(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService);
    CCromer(const CCromer& orig);
    virtual ~CCromer();
    
    
    std::string phenotype();
   
    
private:
    void initSNPs();
    
};


#endif /* CCromer_H */

