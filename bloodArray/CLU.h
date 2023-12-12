/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CLU.h
 * Author: mwittig
 *
 * Created on July 6, 2018, 8:57 AM
 */

#ifndef CLU_H
#define CLU_H

#include <set>

#include "CRBCsnps.h"
#include "CSNPNameLookupMixin.h"




class CLU : public CRBCsnps, public CSNPNameLookupMixin
{
public:
    CLU();
    CLU(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService);
    CLU(const CLU& orig);
    virtual ~CLU();
    
    
    std::string phenotype();
   
    
private:
    void initSNPs();

};


#endif /* CLU_H */

