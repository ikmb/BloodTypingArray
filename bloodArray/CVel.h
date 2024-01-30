/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CVel.h
 * Author: mwittig
 *
 * Created on July 6, 2018, 8:57 AM
 */

#ifndef CVel_H
#define CVel_H

#include <set>

#include "CRBCsnps.h"
#include "CSNPNameLookupMixin.h"




class CVel : public CRBCsnps, public CSNPNameLookupMixin
{
public:
    CVel();
    CVel(std::shared_ptr<CSNPNameLookupServiceInterface> snpNameLookupService);
    CVel(const CVel& orig);
    virtual ~CVel();
    
    
    std::string phenotype();
   
    
private:
    void initSNPs();

};


#endif /* CVel_H */

