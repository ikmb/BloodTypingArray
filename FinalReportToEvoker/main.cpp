/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: mwittig
 *
 * Created on August 11, 2021, 1:19 PM
 */

#include <cstdlib>

#include <mytools.h>
#include <set>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    try
    {
        if(argc < 5)
        {
            cerr << "please provide at least five parameters:" 
                 << "SNP list file in the format (probe_set_id,antigen)"
                 << "output filename for fam file"
                 << "output filename for bim file"
                 << "output filename for bnt file"
                 << "Final report file(s)" << endl;
            exit(EXIT_FAILURE);
                 
        }
        CParsedTextfile ct(argv[1],",","",-1,true,"#"); // consider those
        set<string> idList_orig;
        if(ct.First())
        {
            do
            {
                idList_orig.insert(ct[0]);
            }while(ct.Next());
        }
        cerr << "Fam: " << argv[2]<< endl;
        ofstream outF(argv[2]);             // FAM
        cerr << "BIM: " << argv[3]<< endl;
        ofstream outB(argv[3]);             // BIM
        cerr << "BNT: " << argv[4]<< endl;
        ofstream outE(argv[4], ios::binary);// BNT
        char mn = 26;
        outE.write( reinterpret_cast<const char*>( &mn ), 1);
        mn = 49;
        outE.write( reinterpret_cast<const char*>( &mn ), 1);
        
        for(set<string>::iterator i = idList_orig.begin(); i != idList_orig.end();i++)
        {
            outB << "0" << '\t' << *i << '\t' << "0" << '\t' << "0" << endl;
        }
        
        
        size_t sample_size = argc-5;
        for(int fileIDX = 5; fileIDX < argc; fileIDX++)
        {
            CParsedTextfile pf(argv[fileIDX],"\t","SNP Name","[Data]",true,"#");
            if(pf.First())
            {
                outF << "0 " << pf["Sample ID"] << " 0 0 0"  << endl;
                size_t snp_pointer = 0; 
                size_t sample_pointer = (fileIDX-5); 
                for(set<string>::iterator i = idList_orig.begin(); i != idList_orig.end();i++,snp_pointer++)
                {
                    CParsedTextfile::iterator iter = pf.find(*i);
                    size_t seekg_pointer = sizeof( float )*2*(snp_pointer*sample_size+sample_pointer)+2;
                    outE.seekp(seekg_pointer);
                    float a = 0.0f;
                    float b = 0.0f;
                    if(iter != pf.end())
                    {
                        a = atof(pf.cell(*i,"X").c_str());
                        b = atof(pf.cell(*i,"Y").c_str());
                    }
                    outE.write( reinterpret_cast<const char*>( &a ), sizeof( float ));
                    outE.write( reinterpret_cast<const char*>( &b ), sizeof( float ));
                    
                }
            }
        }
        outF.close();
        outB.close();
        outE.close();
        return 0;
    }
    catch(const string err)
    {
        cerr << endl << "Error occured " << endl << err << endl;
    }
    catch(const char* err)
    {
        cerr << endl << "Error occured " << endl << err << endl;
    }
    catch(CMyException err)
    {
        cerr << endl << "Error occured " << endl << err << endl;
    }
    catch(...)
    {
        cerr << endl << "unexpected error" << endl;
    }
}

