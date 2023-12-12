/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CKEL.h
 * Author: mwittig
 *
 * Created on July 6, 2018, 8:57 AM
 */

#ifndef CKEL_H
#define CKEL_H

#include <set>

#include "CRBCsnps.h"
#include "CSNPNameLookupMixin.h"




class CKEL : public CRBCsnps, public CSNPNameLookupMixin
{
public:
    CKEL();
    CKEL(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService);
    CKEL(const CKEL& orig);
    virtual ~CKEL();
    
    
    std::string phenotype();
   
    
private:
    void initSNPs();

};


#endif /* CKEL_H */

