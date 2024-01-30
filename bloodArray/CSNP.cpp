/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CSNP.cpp
 * Author: mwittig
 * 
 * Created on July 6, 2018, 9:21 AM
 */

#include <string>
#include <vector>

#include <mytools.h>

#include "CSNP.h"

using namespace std;

CSNP::CSNP(const string& id,const string& chrom, long position, float X, float Y, const string& gt)
{
    m_chrom = chrom;
    m_position= position;
    m_id = id;
    vector<std::string> alleles = CMyTools::Tokenize(gt,"/|,\\");
    for(auto a : alleles)
    {
        if(a.compare("-") == 0)
            continue;
        m_gt.push_back(a);
    }
    m_X = X;
    m_Y = Y;
}

CSNP::CSNP(const std::string& id,const std::string& chrom, long position, float X, float Y, const std::vector<std::string>& alleles)
{
    m_chrom = chrom;
    m_position= position;
    m_id = id;
    m_gt = alleles;
    m_X = X;
    m_Y = Y;
}
    
CSNP::CSNP(const CSNP& orig) 
{
    m_chrom = orig.m_chrom;
    m_position= orig.m_position;
    m_id = orig.m_id;
    m_gt = orig.m_gt;
    m_X = orig.m_X;
    m_Y = orig.m_Y;
}

CSNP::~CSNP() {
}

bool CSNP::hasAllele(const string& v)const
{
    for(int i = 0; i < m_gt.size(); i++)
        if(m_gt[i].compare(v) == 0)
            return true;
    return false;
}

bool CSNP::isHetero()const
{
    if(m_gt.size() <= 1)
        return false;
    
    const string& a = m_gt[0];
    for(int i = 1; i < m_gt.size(); i++)
        if(m_gt[i].compare(a) != 0)
            return true;
    return false;
}

bool CSNP::isHeteroLike(const std::string& gt)const
{
    vector<string>  parsed = CMyTools::Tokenize(gt,"/");
    set<string> sGT;
    for(int i = 0; i < parsed.size(); i++)
        sGT.insert(parsed[i]);
    
    if(sGT.size() != m_gt.size() || m_gt.size() == 0)
        return false;
    
    size_t count = 0;
    
    for(int i = 0; i < m_gt.size(); i++)
        sGT.erase(m_gt[i]);
    return sGT.empty();
}


bool CSNP::isHomoFor(const std::string& allele)const
{
    if(m_gt.size() == 0)
        return false;
    
    const string& a = m_gt[0];
    if(a.compare(allele) != 0) // same allele?
        return false;
    
    return !isHetero();           
}

CSNP& CSNP::operator=(const CSNP& o)
{
    *this = o;
    return *this;
}

/*
bool CSNP::operator==(const CSNP& o)
{
    return m_id.compare(o.m_id) == 0;
}
   
bool CSNP::operator<(const CSNP& o)
{
   return m_id.compare(o.m_id) < 0; 
}
*/

bool operator==(const CSNP& a,const CSNP& b)
{
    return a.m_id.compare(b.m_id) == 0;
}

bool operator<(const CSNP& a,const CSNP& b)
{
    return a.m_id.compare(b.m_id) < 0; 
}

string CSNP::gt(const string& delim,bool reverse_compl)const
{
    ostringstream osr;
    for(vector<std::string>::const_iterator i = m_gt.begin(); i != m_gt.end(); i++)
    {
        if(i == m_gt.begin())
            osr << *i;
        else
            osr << delim << *i;
    }
    if(reverse_compl)
        return CMyTools::GetComplSequence(osr.str());
    return osr.str();
}

std::ostream& operator<<(std::ostream& os, const CSNP& me)
{
    os << me.id() << '\t' << me.chrom() << '\t' << me.pos() << '\t' << me.gt();
    
    return os;
}

