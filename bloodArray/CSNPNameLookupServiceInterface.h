/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   CSNPNameLookupServiceInterface.h
 * Author: monkeypunch
 *
 * Created on April 26, 2023, 4:14 PM
 */

#ifndef CSNPNAMELOOKUPSERVICEINTERFACE_H
#define CSNPNAMELOOKUPSERVICEINTERFACE_H
#include <string>

class CSNPNameLookupServiceInterface {
public:
    virtual ~CSNPNameLookupServiceInterface() {};
    virtual std::string lookupSNPName(const std::string& originalSnpName) const = 0;

private:

};

#endif /* CSNPNAMELOOKUPSERVICEINTERFACE_H */

