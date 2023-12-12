/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   CSNPNameLookupMixin.cpp
 * Author: mschmoehl
 * 
 * Created on April 26, 2023, 5:22 PM
 */

#include "CSNPNameLookupMixin.h"

CSNPNameLookupMixin::CSNPNameLookupMixin() {
}

CSNPNameLookupMixin::CSNPNameLookupMixin(const CSNPNameLookupMixin& orig) {
    m_snp_name_lookup_service = orig.m_snp_name_lookup_service;
}

CSNPNameLookupMixin::~CSNPNameLookupMixin() {
}

std::string CSNPNameLookupMixin::lookupSNPName(const std::string& snpName) const {
    if (m_snp_name_lookup_service) {
        return m_snp_name_lookup_service->lookupSNPName(snpName);
    } else {
        return snpName;
    }
};
