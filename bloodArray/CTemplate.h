/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CTemplate.h
 * Author: mwittig
 *
 * Created on July 6, 2018, 8:57 AM
 */

#ifndef CTemplate_H
#define CTemplate_H

#include <set>

#include "CRBCsnps.h"




class CTemplate : public CRBCsnps
{
public:
    CTemplate();
    CTemplate(const CTemplate& orig);
    virtual ~CTemplate();
    
    
    std::string phenotype()const;
   
    
private:
    
};


#endif /* CTemplate_H */

