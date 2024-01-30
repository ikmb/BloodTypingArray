/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CRBCsnps.cpp
 * Author: mwittig
 * 
 * Created on July 11, 2018, 8:06 AM
 */

#include <string>
#include <set>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <sstream>

#include "CSNP.h"

#include "CRBCsnps.h"


using namespace std;


CRBCsnps::CRBCsnps() {
}

CRBCsnps::CRBCsnps(const CRBCsnps& orig) {
}

CRBCsnps::~CRBCsnps() {
}

bool CRBCsnps::isRelevantSnpId(const string& id)const
{
    for(const auto a : m_snps)
    {
        if(a.id().compare(id)==0)
            return true;
    }
    return false;
}

bool CRBCsnps::remove_phenotype(std::vector<std::string>& v, const string& phen)
{
    for(std::vector<std::string>::iterator i = v.begin(); i != v.end(); i++)
    {
        if(i->compare(phen) == 0)
        {
            v.erase(i);
            return true;
        }
    }
    return false;
}


void CRBCsnps::result_vector_sorting(std::vector<std::string>& v)
{
    if(v.size() >1)
    {
        sort(v.begin(),v.begin()+2);
    }
}

std::string CRBCsnps::getSNPsAsString(const std::string& separator, const std::string& prefix, const std::string& suffix) const
{
    string strRet("");
    for(const auto a : m_snps)
    {
        if(strRet.length() != 0)
            strRet.append(separator);
        strRet.append(prefix);
        strRet.append(a.id());
        strRet.append(suffix);
    }
    return strRet;
}

bool CRBCsnps::isRelevantGtMissing()const
{
    for(const auto a : m_snps)
    {
        if(a.isNA())
            return true;
    }
    return false;
}

bool my_allele_sorting(const string& a, const string& b)
{
    for(int i = 0; i < a.size() && i < b.size(); i++)
    {
        if(a[i] < b[i])
            return true;
        if(a[i] > b[i])
            return false;
    }
    if(a.size() < b.size())
        return true;
    return false;
}

std::ostream& operator<<(std::ostream& os, const CRBCsnps& me)
{
    for(std::set<CSNP>::const_iterator i =  me.m_snps.begin(); i != me.m_snps.end(); i++)
    {
        if(i != me.m_snps.begin())
            os << endl;
        os << i->id() << '\t' << i->chrom() << '\t' << i->pos() << '\t' << i->gt();
    }
    return os;
}


std::string CRBCsnps::gt(const std::string& delim,bool reverse_compl)const
{
    ostringstream os;
    for(std::set<CSNP>::const_iterator i =  m_snps.begin(); i != m_snps.end(); i++)
    {
        if(i != m_snps.begin())
            os << '\t';
        os << i->gt(delim,reverse_compl);
    }
    return os.str();
}

std::string CRBCsnps::gt_header()const
{
    ostringstream os;
    for(std::set<CSNP>::const_iterator i =  m_snps.begin(); i != m_snps.end(); i++)
    {
        if(i != m_snps.begin())
            os << '\t';
        os << i->id();
    }
    return os.str();
}


