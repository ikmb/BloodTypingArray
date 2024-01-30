/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CDiegoWright.h
 * Author: mwittig
 *
 * Created on July 6, 2018, 8:57 AM
 */

#ifndef CDiegoWright_H
#define CDiegoWright_H

#include <set>

#include "CRBCsnps.h"
#include "CSNPNameLookupMixin.h"




class CDiegoWright : public CRBCsnps, public CSNPNameLookupMixin
{
public:
    CDiegoWright();
    CDiegoWright(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService);
    CDiegoWright(const CDiegoWright& orig);
    virtual ~CDiegoWright();
    
    
    std::string phenotype();
   
    
private:
    void initSNPs();
    
};


#endif /* CDiegoWright_H */

