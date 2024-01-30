/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CABO.h
 * Author: mwittig
 *
 * Created on July 6, 2018, 8:57 AM
 */

#ifndef CABO_H
#define CABO_H

#include <set>

#include "CRBCsnps.h"
#include "CSNPNameLookupMixin.h"




class CABO : public CRBCsnps, public CSNPNameLookupMixin
{
public:
    CABO();
    CABO(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService);
    CABO(const CABO& orig);
    virtual ~CABO();
    
    
    std::string phenotype(bool trivial = false);
   
    
private:
    void initSNPs();
    
};


#endif /* CABO_H */

