/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CScianna.h
 * Author: mwittig
 *
 * Created on July 6, 2018, 8:57 AM
 */

#ifndef CScianna_H
#define CScianna_H

#include <set>

#include "CRBCsnps.h"
#include "CSNPNameLookupMixin.h"




class CScianna : public CRBCsnps, public CSNPNameLookupMixin
{
public:
    CScianna();
    CScianna(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService);
    CScianna(const CScianna& orig);
    virtual ~CScianna();
    
    
    std::string phenotype();
   
    
private:
    void initSNPs();
 
};


#endif /* CScianna_H */

