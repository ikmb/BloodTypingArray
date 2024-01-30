/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   CSubstitutions.h
 * Author: mschmoehl
 *
 * Created on April 23, 2023, 12:11 AM
 */

#ifndef CSUBSTITUTIONS_H
#define CSUBSTITUTIONS_H
#include "CSNPNameLookupServiceInterface.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <regex>

class CSubstitutions : public CSNPNameLookupServiceInterface {
public:
    CSubstitutions();
    CSubstitutions(const std::string& filename);
    CSubstitutions(const CSubstitutions& orig);
    virtual ~CSubstitutions();
    
    virtual std::string lookupSNPName(const std::string& originalSnpName) const;

    std::string getSubstituteFor(const std::string& originalSnpName) const;
    
    bool readSubstitutionsFromFile(const std::string& filename);
    bool readSubstitutionsFromFile(std::ifstream& in);
    
    void printSubstitutions() const;
    
    std::string ltrim(const std::string &s);
    std::string rtrim(const std::string &s);
    std::string trim(const std::string &s);

private:
    const std::string WHITESPACE = " \n\r\t\f\v";
    const std::string DELIMITER = "/";
    const std::string COMMENTSYMBOL = "#";
    
protected:
    std::map<std::string, std::string> m_substitutions;

};

#endif /* CSUBSTITUTIONS_H */

