#include <iostream>
#include <iomanip>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TProfile.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TMath.h>
#include <TComplex.h>

#include "Interpolator.h"
#include "VMaximum.h"
#include "VMinimum.h"
#include "LE.h"
#include "TimeOverThreshold.h"
#include "Correction.h"
#include "GetRiseTime.h"
#include "DrawScope.h"
#include "FrequencySpectrum.h"

#include "MyLib.h"
#include "analyzeWaveforms.h"


using namespace std;

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////


void runAnalysis(){

	//analyzeWaveforms("Aug8_4fC_LGADlike",  prefix);

    //string path="/home/jongho/Physics/MTD/LGAD_ETROC0/Run3_10degree/Sep06/20190906_001436669Wfm_Ch1.csv";
    //string fileName = "20190906_001436669Wfm_Ch1.csv"; 
    //string timeStamp = "";
    //int channel = 0;

    //cout << parseFileNameTimeStamp(fileName, prefix, timeStamp, channel) << endl;
    //cout << timeStamp <<  endl;
    //cout << channel <<  endl;

    //string path="/home/jongho/Physics/MTD/LGAD_ETROC0/data/Run1/Sep24/";
    //string path="/home/jongho/Physics/MTD/LGAD_ETROC0/data/Run2/Aug27/";
    //string path="/home/jongho/Physics/MTD/LGAD_ETROC0/data/Run2/Sep24/";
    string path="/home/jongho/Physics/MTD/LGAD_ETROC0/data/Run3_10degree/Oct2/";
	string prefix = "20191002";
    string filename = "Oct2.txt";
    //string filename = "190930_025900.csv";
    string timestamp = "";
    
    //cout << parseFileNameOldFashion(filename, prefix, timestamp) << endl;
    mergeFiles(path, prefix, filename);

    system("mv Oct2.txt ./_inputFiles");
    system("cp ./_parameterFiles/test_dat.txt ./_parameterFiles/Oct2_dat.txt");

    prefix = "";
	analyzeWaveforms("Oct2",  prefix);
    
	cout << "-------- END OF JOB ------------\n";
	
	return;

}

