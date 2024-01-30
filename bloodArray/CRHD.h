/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CRHD.h
 * Author: mwittig
 *
 * Created on July 6, 2018, 8:57 AM
 */

#ifndef CRHD_H
#define CRHD_H

#include <set>

#include "CRBCsnps.h"
#include "CSNPNameLookupMixin.h"




class CRHD : public CRBCsnps, public CSNPNameLookupMixin
{
public:
    CRHD();
    CRHD(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService);
    CRHD(const CRHD& orig);
    virtual ~CRHD();
    
    
    std::string phenotype();
   
    
private:
    void initSNPs();
  
};


#endif /* CRHD_H */

