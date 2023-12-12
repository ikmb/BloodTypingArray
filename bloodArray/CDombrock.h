/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CDombrock.h
 * Author: mwittig
 *
 * Created on July 6, 2018, 8:57 AM
 */

#ifndef CDombrock_H
#define CDombrock_H

#include <set>

#include "CRBCsnps.h"
#include "CSNPNameLookupMixin.h"




class CDombrock : public CRBCsnps, public CSNPNameLookupMixin
{
public:
    CDombrock();
    CDombrock(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService);
    CDombrock(const CDombrock& orig);
    virtual ~CDombrock();
    
    
    std::string phenotype();
   
    
private:
    void initSNPs();

};


#endif /* CDombrock_H */

