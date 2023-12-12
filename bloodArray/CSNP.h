/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CSNP.h
 * Author: mwittig
 *
 * Created on July 6, 2018, 9:21 AM
 */

#ifndef CSNP_H
#define CSNP_H

#include <vector>
#include <string>


class CSNP {
public:
    CSNP(const std::string& id,const std::string& chrom = "", long position = -1, float X = 0.0f, float Y = 0.0f, const std::string& gt = "n.a.");
    CSNP(const std::string& id,const std::string& chrom, long position, float X , float Y , const std::vector<std::string>& alleles);
    CSNP(const CSNP& orig);
    virtual ~CSNP();
    
    bool hasAllele(const std::string& v)const;
    bool isHetero()const;
    /// 
    /// \param gt The genotype delimited by /. eg "A/G", or Triploid "A/C/T")
    /// \return  true/false
    bool isHeteroLike(const std::string& gt)const;
    bool isHomoFor(const std::string& allele)const;
    bool isHomo()const{if(m_gt.size() == 0)return false;return !isHetero();}
    
    CSNP& operator=(const CSNP& o);
    //bool operator==(const CSNP& o);
    //bool operator<(const CSNP& o);
    
    friend bool operator==(const CSNP& a,const CSNP& b);
    friend bool operator<(const CSNP& a,const CSNP& b);
    friend std::ostream& operator<<(std::ostream& os, const CSNP& me);
    
    
    std::string                 chrom()const{return m_chrom;}
    long                        pos()const{return  m_position;}
    std::string                 gt(const std::string& delim = "/",bool reverse_compl = false)const;
    std::string                 id()const{return m_id;}
    float                       getX()const{return m_X;}
    float                       getY()const{return m_Y;}
    float                       getNormR()const{return m_X+m_Y;}
    float                       getNormTheta()const{if(getNormR() != 0.0f)return m_Y/getNormR();return 0.0f;}
    
    bool isNA()const{if(m_gt.size()==0)return true;if(m_gt[0].compare("n.a.")==0)return true; return false;}
    

private:
    std::string                 m_chrom;
    long                        m_position;
    std::vector<std::string>    m_gt;
    std::string                 m_id;
    
    float                       m_X;
    float                       m_Y;
};



#endif /* CSNP_H */

