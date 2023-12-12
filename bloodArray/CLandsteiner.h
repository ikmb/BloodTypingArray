/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CLandsteiner.h
 * Author: mwittig
 *
 * Created on July 6, 2018, 8:57 AM
 */

#ifndef CLandsteiner_H
#define CLandsteiner_H

#include <set>

#include "CRBCsnps.h"
#include "CSNPNameLookupMixin.h"




class CLandsteiner : public CRBCsnps, public CSNPNameLookupMixin
{
public:
    CLandsteiner();
    CLandsteiner(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService);
    CLandsteiner(const CLandsteiner& orig);
    virtual ~CLandsteiner();
    
    
    std::string phenotype();
   
    
private:
    void initSNPs();
  
};


#endif /* CLandsteiner_H */

