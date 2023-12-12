/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   CSNPNameLookupMixin.h
 * Author: mschmoehl
 *
 * Created on April 26, 2023, 5:22 PM
 */

#ifndef CSNPNAMELOOKUPMIXIN_H
#define CSNPNAMELOOKUPMIXIN_H

#include <memory>
#include <string>
#include "CSNPNameLookupServiceInterface.h"

class CSNPNameLookupMixin {
public:
    CSNPNameLookupMixin();
    CSNPNameLookupMixin(const CSNPNameLookupMixin& orig);
    virtual ~CSNPNameLookupMixin();
private:
    
protected:
    std::shared_ptr<CSNPNameLookupServiceInterface> m_snp_name_lookup_service;
    std::string lookupSNPName(const std::string& snpName) const;
};

#endif /* CSNPNAMELOOKUPMIXIN_H */

