/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   CSubstitutions.cpp
 * Author: mschmoehl
 * 
 * Created on April 23, 2023, 12:11 AM
 */

#include "CSubstitutions.h"

#include "CMyException.h"

CSubstitutions::CSubstitutions() {
    /*std::cerr << "hello from standard constructor" << std::endl;
    std::cerr << substitutions.empty() << std::endl;
    substitutions["test"] = "hope";
    std::cerr << substitutions.empty() << std::endl;*/
}

CSubstitutions::CSubstitutions(const std::string& filename) {
    std::ifstream in(filename,  std::ifstream::in);
    if (!in)
        throw CMyException(std::string("Failed to open file: ") + filename);
    if (!readSubstitutionsFromFile(in))
        throw CMyException("Error reading substitutions file!");
    in.close();
}

CSubstitutions::CSubstitutions(const CSubstitutions& orig) {
    m_substitutions=orig.m_substitutions;
}

CSubstitutions::~CSubstitutions() {
}


// returns the substituted snp name of argument "originalSnpName" if found
// returns the argument originalSnpName else
std::string CSubstitutions::getSubstituteFor(const std::string& originalSnpName) const {
    if (m_substitutions.empty()) {
        return originalSnpName;
    } else {
        if (m_substitutions.count(originalSnpName)) {
            return m_substitutions.at(originalSnpName);
        } else {
            return originalSnpName;
        }
    }
}

std::string CSubstitutions::lookupSNPName(const std::string& originalSnpName) const {
    return getSubstituteFor(originalSnpName);
}

bool CSubstitutions::readSubstitutionsFromFile(const std::string& filename) {
    std::ifstream in(filename, std::ifstream::in);
    if (!in)
        throw CMyException(std::string("Failed to open file: ") + filename);
    if (!readSubstitutionsFromFile(in))
        throw CMyException("Error reading substitutions file!");
    in.close();
    return true;
}


bool CSubstitutions::readSubstitutionsFromFile(std::ifstream& in) {
    std::string line;
    while (std::getline(in, line)) {
        // std::cerr << line << std::endl;
        // strip comment from line; comment can begin anywhere in line
        size_t c_pos = line.find(COMMENTSYMBOL);
        if (c_pos < std::string::npos) {
            line = line.substr(0, c_pos);
            //std::cerr << "stripping comment" << std::endl;
        }
        // skip lines containing only whitespaces
        if (line.find_first_not_of(WHITESPACE) != std::string::npos) {
            // find delimiter
            size_t d_pos = line.find(DELIMITER);
            if (d_pos < std::string::npos) {
                // split string at delimiter
                std::string oldName = line.substr(0, d_pos);
                std::string newName = line.substr(d_pos+DELIMITER.length(), line.length() - (d_pos + DELIMITER.length()));
                // trim both tokens 
                oldName = trim(oldName);
                newName = trim(newName);
                // if both are of length > 0, add to substitutions map
                if (oldName.length() > 0 && newName.length() > 0) {
                    //std::cerr << "valid substitution |" << oldName << "| --> |" << newName << "|" << std::endl;
                    m_substitutions[oldName] = newName;
                } else {
                    // std::cerr << "at least one zero-size token" << std::endl;                
                }
            } else {
                //std::cerr << "delimiter not found" << std::endl;                
            }
        } else {
            //std::cerr << "skip empty line" << std::endl;
        }
    }
    return true;
};

void CSubstitutions::printSubstitutions() const{
    for (auto const& s : m_substitutions) {
        std::cerr << s.first << " --> " << s.second << std::endl;
    }
};


// Trim Function copied from here (#4): https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/

std::string CSubstitutions::ltrim(const std::string &s) {
    return std::regex_replace(s, std::regex("^\\s+"), std::string(""));
}

std::string CSubstitutions::rtrim(const std::string &s) {
    return std::regex_replace(s, std::regex("\\s+$"), std::string(""));
}

std::string CSubstitutions::trim(const std::string &s) {
    return ltrim(rtrim(s));
}



