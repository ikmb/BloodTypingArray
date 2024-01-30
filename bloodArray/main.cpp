/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: mwittig
 *
 * Created on January 20, 2020, 10:50 AM
 */
#include <libgen.h> // Fix for Mac Compilation get "basename" function from here 
#include <cstdlib>

#include <mytools.h>
#include <string.h>
#include "CSNP.h"
#include "CRBCsnps.h"
#include "CABO.h"
#include "CLU.h"
#include "CKEL.h"
#include "CDuffy.h"
#include "CKidd.h"
#include "CDiegoWright.h"
#include "CCartwright.h"
#include "CScianna.h"
#include "CDombrock.h"
#include "CMNS.h"
#include "CRHD.h"
#include "CRHCE.h"
#include "CColton.h"
#include "CLandsteiner.h"
#include "CCromer.h"
#include "CKnoops.h"
#include "CJR.h"
#include "CLan.h"
#include "CVel.h"
#include "CIndian.h"
#include "CSubstitutions.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    try
    {
        
        shared_ptr<CSubstitutions> subs(new CSubstitutions);

        int argIndexOfSubSwitch = -1;
        int argIndexOfSubFile = -1;
        // look for substitution switch
        for(int argi = 1; argi < argc; argi++) {
            string arg = argv[argi];
            if (arg == "-s") {
                argIndexOfSubSwitch = argi;
                if (argi + 1 < argc ) {
                    argIndexOfSubFile = argi + 1;
                    string arg_sub_file = argv[argi + 1];
                    cerr << "read Substitutions from file " << arg_sub_file << endl;
                    subs->readSubstitutionsFromFile(arg_sub_file);
                    break;
                } else {
                    cerr << "substitution switch without filename provided" << endl;                    
                }
            }
        }
        
        subs->printSubstitutions();
        
        // https://emea.support.illumina.com/array/array_software/illumina-array-analysis-platform/downloads.html
        // https://github.com/freeseek/gtc2vcf
        
        CABO abo(subs);
        CLU  lutheran(subs);
        CKEL kel(subs);
        CDuffy duffy(subs);
        CKidd kidd(subs);
        CDiegoWright diego(subs);
        CCartwright cartwright(subs);
        CScianna scianna(subs);
        CDombrock dombrock(subs);
        CColton colton(subs);
        CLandsteiner landsteiner(subs);
        CCromer cromer(subs);
        CKnoops knoops(subs);
        CJR jr(subs);
        CLan lan(subs);
        CVel vel(subs);
        CIndian indian(subs);
        CMNS mns(subs);
        CRHD rhd(subs);
        CRHCE rhce(subs);
         

        

        //return 0;

        //string arg_fr = "/home/mwittig/ramDisk/FinalReports/Hemo_MLD_v1_FinalReport100.txt";
        //string arg_fr = "/home/mwittig/coding/cpp/bloodArray/config/iScan1739_iSelect_FinalReport1.txt";
        
        bool headerPrinted=false;
        for(int filename_i = 1 ; filename_i < argc;filename_i++)
        {
            // skip substitution related arguments
            if (filename_i == argIndexOfSubSwitch || filename_i == argIndexOfSubFile) {
                continue;
            }
            string arg_fr = argv[filename_i];
            //cerr << "read annotation" << endl;
            //CParsedTextfile anno("/home/mwittig/coding/cpp/bloodArray/config/HEM_MLD_v1_HTS_anno_cpp.csv","\t","Name" , 7, true);
            cerr << "read Final report " << arg_fr << endl;
            CParsedTextfile fr(arg_fr,"\t","SNP Name" , "[Data]", true);


            /*
            0	SNP Name	1:103380393	1:109439680
            1	Sample ID	952726	952726
            2	Allele1 - AB	A	A
            3	Allele2 - AB	B	A
            4	X	0.349	0.563
            5	Y	0.445	0.019
            6	Chr	1	1
            7	Position	103380393	109439680
            8	Allele1 - Top	A	A
            9	Allele2 - Top	G	A
            10	Sample Name	CON512SGR	CON512SGR
            11	Sample Group		

             */
            if(fr.First())
                do
                {
                    string id = fr["SNP Name"];
                    string sample_name = fr["Sample ID"];
                    string A1 = fr["Allele1 - Plus"];
                    string A2 = fr["Allele2 - Plus"];
                    string chrom = fr["Chr"];
                    long pos = stol(fr["Position"]);
                    float intX = stof(fr["X"]);
                    float intY = stof(fr["Y"]);

                    CSNP act_snp(id,chrom,pos,intX,intY,A1+"/"+A2);

                    if(abo.isRelevantSnpId(id))
                        abo.addSNP(act_snp);
                    //if(mns.isRelevantSnpId(id))
                    //    mns.addSNP(act_snp);
                    if(rhd.isRelevantSnpId(id))
                        rhd.addSNP(act_snp);
                    //if(rhce.isRelevantSnpId(id))
                    //    rhce.addSNP(act_snp);
                    if(lutheran.isRelevantSnpId(id))
                        lutheran.addSNP(act_snp);
                    if(kel.isRelevantSnpId(id))
                        kel.addSNP(act_snp);
                    if(duffy.isRelevantSnpId(id))
                        duffy.addSNP(act_snp);
                    if(kidd.isRelevantSnpId(id))
                        kidd.addSNP(act_snp);
                    if(diego.isRelevantSnpId(id))
                        diego.addSNP(act_snp);
                    if(cartwright.isRelevantSnpId(id))
                        cartwright.addSNP(act_snp);
                    if(scianna.isRelevantSnpId(id))
                        scianna.addSNP(act_snp);
                    if(dombrock.isRelevantSnpId(id))
                        dombrock.addSNP(act_snp);
                    if(colton.isRelevantSnpId(id))
                        colton.addSNP(act_snp);
                    if(landsteiner.isRelevantSnpId(id))
                        landsteiner.addSNP(act_snp);
                    if(cromer.isRelevantSnpId(id))
                        cromer.addSNP(act_snp);
                    if(knoops.isRelevantSnpId(id))
                        knoops.addSNP(act_snp);
                    if(jr.isRelevantSnpId(id))
                        jr.addSNP(act_snp);
                    if(lan.isRelevantSnpId(id))
                        lan.addSNP(act_snp);
                    if(vel.isRelevantSnpId(id))
                        vel.addSNP(act_snp);
                    if(indian.isRelevantSnpId(id))
                        indian.addSNP(act_snp);

                }while(fr.Next());
                if(!headerPrinted) //Print header
                {
                    headerPrinted=true;
                    /**/
                    cout << "Sample_ID" << "\t" << "filename" << "\t"
                         << "ABO" << "\t"
                            //<< "MNS" << "\t"
                            << "Rh" << "\t"
                            //<< "Rh" << "\t"
                            << "Lutheran" << "\t"
                            << "Kell" << "\t"
                            << "Duffy" << "\t"
                            << "Kidd" << "\t"
                            << "Diego" << "\t"
                            << "Yt" << "\t"
                            << "Scianna" << "\t"
                            << "Dombrock" << "\t"
                            << "Colton" << "\t"
                            << "Landsteiner-Wiener" << "\t"
                            << "CROM" << "\t"
                            << "Knops" << "\t"
                            << "JR" << "\t"
                            << "LAN" << "\t"
                            << "Vel" << "\t"
                            << "Indian" << endl;
                    cout << "Sample_ID" << "\t" << "filename" << "\t"
                         << "ABO" << "\t"
                            //<< "MNS" << "\t"
                            << "RHD" << "\t"
                            //<< "RH" << "\t"
                            << "LU" << "\t"
                            << "KEL" << "\t"
                            << "FY" << "\t"
                            << "JK" << "\t"
                            << "DI" << "\t"
                            << "YT" << "\t"
                            << "SC" << "\t"
                            << "DO" << "\t"
                            << "CO" << "\t"
                            << "LW" << "\t"
                            << "CROM" << "\t"
                            << "KN" << "\t"
                            << "JR" << "\t"
                            << "LAN" << "\t"
                            << "VEL" << "\t"
                            << "Indian" << endl;
                    cout << "Sample_ID" << "\t" << "filename" << "\t"
                         << "ABO" << "\t"
                            //<< "GYPA,GYPB" << "\t"
                            << "RHD" << "\t"
                            //<< "RHCE" << "\t"
                            << "BCAM" << "\t"
                            << "KEL" << "\t"
                            << "ACKR1" << "\t"
                            << "SLC14A1" << "\t"
                            << "SLC4A1" << "\t"
                            << "ACHE" << "\t"
                            << "ERMAP" << "\t"
                            << "ART4" << "\t"
                            << "AQP1" << "\t"
                            << "ICAM4" << "\t"
                            << "CD55" << "\t"
                            << "CR1" << "\t"
                            << "ABCG2" << "\t"
                            << "ABCB6" << "\t"
                            << "SMIM1" << "\t"
                            << "CD44" << endl;
                    cout << "Sample_ID" << "\t" << "filename" << "\t"
                         << "001" << "\t"
                            //<< "002" << "\t"
                            << "004" << "\t"
                            //<< "004" << "\t"
                            << "005" << "\t"
                            << "006" << "\t"
                            << "008" << "\t"
                            << "009" << "\t"
                            << "010" << "\t"
                            << "011" << "\t"
                            << "013" << "\t"
                            << "014" << "\t"
                            << "015" << "\t"
                            << "016" << "\t"
                            << "021" << "\t"
                            << "022" << "\t"
                            << "032" << "\t"
                            << "033" << "\t"
                            << "034" << "\t"
                            << "023" << endl;
                    
                }
                cout << fr["Sample ID"] << "\t" << basename(&arg_fr[0]) << "\t" //fix for mac: use arg_fr[0] instead of arg_fr.c_str()
                      << abo.phenotype(true) << '\t'
                        //<< mns.phenotype() << '\t'
                        << rhd.phenotype() << '\t'
                        //<< rhce.phenotype() << '\t'
                        << lutheran.phenotype() << '\t'
                        << kel.phenotype() << '\t'
                        << duffy.phenotype() << '\t'
                        << kidd.phenotype() << '\t'
                        << diego.phenotype() << '\t'
                        << cartwright.phenotype() << '\t'
                        << scianna.phenotype() << '\t'
                        << dombrock.phenotype() << '\t'
                        << colton.phenotype() << '\t'
                        << landsteiner.phenotype() << '\t'
                        << cromer.phenotype() << '\t'
                        << knoops.phenotype() << '\t'
                        << jr.phenotype() << '\t'
                        << lan.phenotype() << '\t'
                        << vel.phenotype() << '\t'
                        << indian.phenotype() << endl;   
                
                    /*
                    cout << abo.getSNPsAsString() << endl <<
                        //rhd.getSNPsAsString() << endl <<
                        lutheran.getSNPsAsString() << endl <<
                        kel.getSNPsAsString() << endl <<
                        duffy.getSNPsAsString() << endl <<
                        kidd.getSNPsAsString() << endl <<
                        diego.getSNPsAsString() << endl <<
                        cartwright.getSNPsAsString() << endl <<
                        scianna.getSNPsAsString() << endl <<
                        dombrock.getSNPsAsString() << endl <<
                        colton.getSNPsAsString() << endl <<
                        landsteiner.getSNPsAsString() << endl <<
                        cromer.getSNPsAsString() << endl <<
                        knoops.getSNPsAsString() << endl <<
                        jr.getSNPsAsString() << endl <<
                        lan.getSNPsAsString() << endl <<
                        vel.getSNPsAsString() << endl;
                 /**/
            /*
                cout << fr["Sample ID"] << "\tABO\t" << abo.phenotype() << '\t' << basename(arg_fr.c_str()) << endl;
                cout << fr["Sample ID"] << "\tRhesusD\t" << rhd.phenotype() << '\t' << basename(arg_fr.c_str()) << endl;
                cout << fr["Sample ID"] << "\tLutheran\t" << lutheran.phenotype() << '\t' << basename(arg_fr.c_str()) << endl;
                cout << fr["Sample ID"] << "\tKEL\t" << kel.phenotype() << '\t' << basename(arg_fr.c_str()) << endl;
                cout << fr["Sample ID"] << "\tDuffy\t" << duffy.phenotype() << '\t' << basename(arg_fr.c_str()) << endl;
                cout << fr["Sample ID"] << "\tKidd\t" << kidd.phenotype() << '\t' << basename(arg_fr.c_str()) << endl;
                cout << fr["Sample ID"] << "\tDiego,Wright\t" << diego.phenotype() << '\t' << basename(arg_fr.c_str()) << endl;
                cout << fr["Sample ID"] << "\tCartright\t" << cartwright.phenotype() << '\t' << basename(arg_fr.c_str()) << endl;
                cout << fr["Sample ID"] << "\tScianna\t" << scianna.phenotype() << '\t' << basename(arg_fr.c_str()) << endl;
                cout << fr["Sample ID"] << "\tDombrock\t" << dombrock.phenotype() << '\t' << basename(arg_fr.c_str()) << endl;
                cout << fr["Sample ID"] << "\tColton\t" << colton.phenotype() << '\t' << basename(arg_fr.c_str()) << endl;
                cout << fr["Sample ID"] << "\tLandsteiner-Wiener\t" << landsteiner.phenotype() << '\t' << basename(arg_fr.c_str()) << endl;
                cout << fr["Sample ID"] << "\tCromer\t" << cromer.phenotype() << '\t' << basename(arg_fr.c_str()) << endl;
                cout << fr["Sample ID"] << "\tKnoops\t" << knoops.phenotype() << '\t' << basename(arg_fr.c_str()) << endl;
                cout << fr["Sample ID"] << "\tJR\t" << jr.phenotype() << '\t' << basename(arg_fr.c_str()) << endl;
                cout << fr["Sample ID"] << "\tLAN\t" << lan.phenotype() << '\t' << basename(arg_fr.c_str()) << endl;
                cout << fr["Sample ID"] << "\tVel\t" << vel.phenotype() << '\t' << basename(arg_fr.c_str()) << endl;
             */
        }
        if(argc == 1 || (argc == 3 && argIndexOfSubSwitch != -1 && argIndexOfSubFile  != -1))
        {
            cout    << "System\tSNPs" << endl
                    << "ABO\t" << abo.getSNPsAsString() << endl
                    //<< "MNS\t" << mns.getSNPsAsString() << endl
                    << "RHD\t" << rhd.getSNPsAsString() << endl
                    //<< "RHCE\t" << rhce.getSNPsAsString() << endl
                    << "Lutheran\t"  << lutheran.getSNPsAsString() << endl
                    << "Kel\t" << kel.getSNPsAsString() << endl
                    << "Duffy\t" << duffy.getSNPsAsString() << endl
                    << "kidd\t" << kidd.getSNPsAsString() << endl
                    << "Diego\t" << diego.getSNPsAsString() << endl
                    << "Cartwright\t" << cartwright.getSNPsAsString() << endl
                    << "Scianna\t" << scianna.getSNPsAsString() << endl
                    << "Dombrock\t" << dombrock.getSNPsAsString() << endl
                    << "Colton\t" << colton.getSNPsAsString() << endl
                    << "Landsteiner\t" << landsteiner.getSNPsAsString() << endl
                    << "Cromer\t" << cromer.getSNPsAsString() << endl
                    << "Knoops\t" << knoops.getSNPsAsString() << endl
                    << "Jr\t" << jr.getSNPsAsString() << endl
                    << "Lan\t" << lan.getSNPsAsString() << endl
                    << "Vel\t" << vel.getSNPsAsString() << endl
                    << "Indian\t" << indian.getSNPsAsString() << endl;
        }
        if (argc == 2 && argIndexOfSubSwitch != -1) {
            cout << "# SNP Name Substitution Template" << endl 
                    << "#" << endl
                    << "# define a SNP name substitution by \"old_SNP_name / new_SNP_name\" " << endl
                    << "# one substitution per line, white spaces between tokens (SNP names, \"/\") are usually ignored" << endl
                    << "# \"#\" denotes a comment" << endl
                    << endl
                    << "# ABO\n" << abo.getSNPsAsString("\n", "# ", " / ") << endl << endl
                    //<< "# MNS\n" << mns.getSNPsAsString("\n", "# ", " / ") << endl << endl
                    << "# RHD\n" << rhd.getSNPsAsString("\n", "# ", " / ") << endl << endl
                    //<< "# RHCE\n" << rhce.getSNPsAsString("\n", "# ", " / ") << endl << endl
                    << "# Lutheran\n" << lutheran.getSNPsAsString("\n", "# ", " / ") << endl << endl
                    << "# Kel\n" << kel.getSNPsAsString("\n", "# ", " / ") << endl << endl
                    << "# Duffy\n" << duffy.getSNPsAsString("\n", "# ", " / ") << endl << endl
                    << "# kidd\n" << kidd.getSNPsAsString("\n", "# ", " / ") << endl << endl
                    << "# Diego\n" << diego.getSNPsAsString("\n", "# ", " / ") << endl << endl
                    << "# Cartwright\n" << cartwright.getSNPsAsString("\n", "# ", " / ") << endl << endl
                    << "# Scianna\n" << scianna.getSNPsAsString("\n", "# ", " / ") << endl << endl
                    << "# Dombrock\n" << dombrock.getSNPsAsString("\n", "# ", " / ") << endl << endl
                    << "# Colton\n" << colton.getSNPsAsString("\n", "# ", " / ") << endl << endl
                    << "# Landsteiner\n" << landsteiner.getSNPsAsString("\n", "# ", " / ") << endl << endl
                    << "# Cromer\n" << cromer.getSNPsAsString("\n", "# ", " / ") << endl << endl
                    << "# Knoops\n" << knoops.getSNPsAsString("\n", "# ", " / ") << endl << endl
                    << "# Jr\n" << jr.getSNPsAsString("\n", "# ", " / ") << endl << endl
                    << "# Lan\n" << lan.getSNPsAsString("\n", "# ", " / ") << endl << endl
                    << "# Vel\n" << vel.getSNPsAsString("\n", "# ", " / ") << endl << endl
                    << "# Indian\n" << indian.getSNPsAsString("\n", "# ", " / ") << endl;
        }
    }
    catch(CMyException err)
    {
        cerr << "Error: " << err << endl;
    }
    catch(...)
    {
        cerr << "unexpected error" << endl;
    }
    
    return 0;
}

