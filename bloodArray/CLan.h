/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CLan.h
 * Author: mwittig
 *
 * Created on July 6, 2018, 8:57 AM
 */

#ifndef CLan_H
#define CLan_H

#include <set>

#include "CRBCsnps.h"
#include "CSNPNameLookupMixin.h"




class CLan : public CRBCsnps, public CSNPNameLookupMixin
{
public:
    CLan();
    CLan(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService);
    CLan(const CLan& orig);
    virtual ~CLan();
    
    
    std::string phenotype();
   
    
private:
    void initSNPs();

};


#endif /* CLan_H */

