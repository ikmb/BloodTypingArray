/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CDuffy.h
 * Author: mwittig
 *
 * Created on July 6, 2018, 8:57 AM
 */

#ifndef CDuffy_H
#define CDuffy_H

#include <set>

#include "CRBCsnps.h"
#include "CSNPNameLookupMixin.h"




class CDuffy : public CRBCsnps, public CSNPNameLookupMixin
{
public:
    CDuffy();
    CDuffy(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService);
    CDuffy(const CDuffy& orig);
    virtual ~CDuffy();
    
    
    std::string phenotype();
   
    
private:
    void initSNPs();

};


#endif /* CDuffy_H */

