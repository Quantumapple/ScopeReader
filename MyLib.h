
bool verbose = true;

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

vector<double> getTimes(string fileName){

////////////////////////////////////////////////////////////////////


/*
Reads one of the waveform files produced by the Tek scope 
and returns the times of all the samples in a vector of doubles.
Time unit is seconds.
Uses fileName to open the file. Returns empty vector if open fails
*/

vector<double> times;	
	std::ifstream file(fileName);
  	if(file) {
			std::string str; 
			double time; 
			while (getline(file,str,',')){
				for(int i = 0; i != 3; ++i) getline(file,str,',');
				stringstream(str) >> time;
				times.push_back(time);
				getline(file,str,'\n');
			}
	}	
	return times;
	file.close();
	
}// end of getTimes /////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

vector<double> getVoltages(string fileName){

////////////////////////////////////////////////////////////////////

/*
Reads one of the waveform files produced by the Tek scope 
and returns the voltages of all the samples in a vector of doubles.
Time unit is volts.
Uses fileName to open the file. Returns empty vector if open fails
*/

vector<double> voltages;	
	std::ifstream file(fileName);
  	if(file) {
			std::string str; 
			double voltage; 
			while (getline(file,str,',')){
				for(int i = 0; i != 3; ++i) getline(file,str,',');
				getline(file,str,'\n');
				stringstream(str) >> voltage;
				voltages.push_back(voltage);
			}
	}	
	return voltages;
	file.close();
	
}// end of getVoltages ////////////////////////////////////////////



////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

int getParameters(string fileName, int& recLen, double& sampleInt, int& trigPoint, double& trigTime){

////////////////////////////////////////////////////////////////////


/*
Reads one of the waveform files produced by the Tek scope 
and returns the value of parameters in the header.

recLen = record length
sampleInt = sample interval in seconds
trigPoint = sample number corresponding to time of trigger
trigTime = trigger time in seconds

Uses fileName to open the file. 
Returns !=0 if open fails
*/

	std::ifstream file(fileName);
  	if(file) {
			std::string str; 
			getline(file,str,',');
			getline(file,str,',');
			stringstream(str) >> recLen;
			for(int i = 0; i != 4; ++i)getline(file,str,',');
			stringstream(str) >> sampleInt;		
			for(int i = 0; i != 4; ++i)getline(file,str,',');
			stringstream(str) >> trigPoint;			
			for(int i = 0; i != 4; ++i)getline(file,str,',');
			stringstream(str) >> trigTime;			
			file.close();
			return 0;
			}
	else return 1;	
	
}// end of getParameters //////////////////////////////////////////



////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

int parseFileName(string fileName, string prefix, int& channel, int& event) {

////////////////////////////////////////////////////////////////////

/*

Parses fileName to extract channel number and event number.
Checks file prefix.
Assumes file name sintax is:

	pppppnnnnn_xxxxm.zzzz
	
	where:
	ppppp is the prefix (specified as input parameter)
	nnnnn is the event number (any number of characters)
	xxxx is any number of random characters except '.'
	m is the channel number (a single character)
	zzzz is the file extension (ignored)
	
Return codes:

	0 = all ok
	1 = filename is empty
	2 = filename starts with '.' (fileName is not parsed)
	3 = prefix does not match
	4 = '_' not found
	5 = '.' not found
	
	If return code != 0, both channel and event are unspecified
	
*/

	if(!fileName.length()) return 1;
	if(fileName.at(0) == '.') return 2;
	unsigned prefixLength = prefix.length();
	if(fileName.substr(0, prefixLength) != prefix) return 3;
	unsigned n2 = fileName.find('_', prefixLength);
	if(n2 == (unsigned)string::npos) return 4;
	unsigned n3 = fileName.find('.', n2);	
	if(n3 == (unsigned)string::npos) return 5;	
	stringstream(fileName.substr()) >> event;
	stringstream(fileName.substr()) >> channel;
	return 0;
	
}// end of parseFileName ///////////////////////////////////////////


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

int parseFileNameTimeStamp(string fileName, string prefix, string& timestamp, int& channel) {

////////////////////////////////////////////////////////////////////

/*

Parses fileName to extract channel number and event number.
Checks file prefix.
Assumes file name sintax is:

	(Date)_(Time)Wfm_(Ch)X.csv
	
	where:
	Date is the prefix (specified as input parameter)
	Time is the timestamp when event was triggered 
	X is the channel number
	csv is the file extension (ignored)
	
Return codes:

	0 = all ok
	1 = filename is empty
	2 = filename starts with '.' (fileName is not parsed)
	3 = prefix does not match
	4 = '_' not found
	5 = '.' not found
	
	If return code != 0, both channel and event are unspecified
	
*/

	if(!fileName.length()) return 1;
	if(fileName.at(0) == '.') return 2;
	unsigned prefixLength = prefix.length();
	if(fileName.substr(0, prefixLength) != prefix) return 3;
	unsigned n2 = fileName.find('_', prefixLength);
	if(n2 == (unsigned)string::npos) return 4;
	unsigned n3 = fileName.find('.', n2);	
	if(n3 == (unsigned)string::npos) return 5;	
	std::size_t found1 = fileName.find("Wfm");
    std::size_t found2 = fileName.find("_");
    stringstream(fileName.substr(found2+1, found1-found2-1)) >> timestamp;
	stringstream(fileName.substr(n3-1, 1)) >> channel;

	return 0;
	
}// end of parseFileNameTimeStamp ///////////////////////////////////////////

int parseFileNameOldFashion(string fileName, string prefix, string& timestamp) {

////////////////////////////////////////////////////////////////////

/*

This function design to deal with the data from Tektronix TDS 7254.  
The input data has only one channel output.
Checks file prefix.
Assumes file name sintax is:

	(Date)_(Time).csv
	
	where:
	Date is the prefix (specified as input parameter)
	Time is the timestamp when event was triggered 
	csv is the file extension (ignored)
	
Return codes:

	0 = all ok
	1 = filename is empty
	2 = filename starts with '.' (fileName is not parsed)
	3 = prefix does not match
	4 = '_' not found
	5 = '.' not found
	
	If return code != 0, both channel and event are unspecified
	
*/

	if(!fileName.length()) return 1;
	if(fileName.at(0) == '.') return 2;
	unsigned prefixLength = prefix.length();
	if(fileName.substr(0, prefixLength) != prefix) return 3;
	unsigned n2 = fileName.find('_', prefixLength);
	if(n2 == (unsigned)string::npos) return 4;
	unsigned n3 = fileName.find('.', n2);	
	if(n3 == (unsigned)string::npos) return 5;
	

	return 0;
	
}// end of parseFileNameOldFashion ///////////////////////////////////////////


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

int mergeFiles(string tekFilesDirectory, string fileNamePrefix, string mergedFileName) {

////////////////////////////////////////////////////////////////////

/*

Opens directory tekFilesDirectory, read all files whose name begins with fileNamePrefix,
parses the filenames for event number and channel number, create a single text file with all
events and all the channels. For the format of Tek file names see comments to parseFileName.
The format is an array of times followed by an array of voltages, one per channel. 
Data are separated by blanks. This file can be accessed using the class TekFileReader

*/


string path = tekFilesDirectory;


	// open input file directory
	DIR *dpdf = opendir(path.c_str());
	struct dirent *epdf;
	vector<string> fileNames;

	if (dpdf == NULL){
		cout << "Error opening directory " << path << endl;
		return 1;
	}
	if (dpdf != NULL){
		cout << "Successfully opened " << path << endl;
		while ((epdf = readdir(dpdf))){
	   	// push all file names into fileNames
		  fileNames.push_back(epdf->d_name);
	   }
	   closedir(dpdf);// close directory
	}
	
	
	// sort filenames alphabetically
	if(verbose) cout << fileNames.size() << " files in directory" << endl;
	std::sort(fileNames.begin(), fileNames.end());
	
	
	// open output file 
	ofstream mergedFile;
  	mergedFile.open (mergedFileName); 	
  	//mergedFile.open ("merged.txt");
  	if(!mergedFile){
  		cout << "Error opening output file " << mergedFileName << endl;
  		return 2;
  	}
  	cout << "Successfully opened " << mergedFileName << " for output" << endl;
  
	
  	int previousEvent = -1;  	
	int event = 0;
	int channel = 0;
	string timeStamp = "";
	string previousTS = "";
	
	cout << "Opening all files in directory " << path << endl;
	
	for(int i = 0; i != (int)fileNames.size(); ++i){
			if(((i+1)%100) == 0) cout << "Opening file " << i + 1 << endl << flush;
			if(verbose) cout << fileNames[i] << " " ;
			//int retCode = parseFileName(fileNames[i],fileNamePrefix, channel, event);
			int retCode = parseFileNameTimeStamp(fileNames[i], fileNamePrefix, timeStamp, channel); // When the fileName consists of the time stamp
			//if(verbose)cout << "channel " << channel << " event " << event << " retCode " << retCode << endl;
			if(verbose)cout << "channel " << channel << " timeStamp " << timeStamp << " retCode " << retCode << endl; // When the fileName consists of the time stamp
			if(retCode == 0) {
				if(event != previousEvent){	
					vector<double> times = getTimes(path+fileNames[i]);
					if(event == 0) {
						int retCode; int recLen; double sampleInt; int trigPoint; double trigTime;
						retCode = getParameters(path+fileNames[i], 
							recLen, sampleInt, trigPoint, trigTime);
						mergedFile << recLen << " " << sampleInt << " " << times[0] << " " << trigPoint << " " << trigTime << endl;
						mergedFile << "begin " << times.size() << endl;
					}
					mergedFile << endl;
					mergedFile << "event " << event << endl;
					for(int iT = 0; iT != (int)times.size(); ++iT) mergedFile << times[iT] << " ";
					mergedFile << endl;	
					previousEvent = event;
					}
				mergedFile << endl;			
				mergedFile << "channel " << channel << endl;	
				vector<double> voltages = getVoltages(path+fileNames[i]);
				for(int iV = 0; iV != (int)voltages.size(); ++iV) mergedFile << voltages[iV] << " ";
				mergedFile << endl;			
				if( i != 0 && i%3 == 1 ) event++;
				
			}
			
	}
	mergedFile << endl << "end " <<  event+1 << " events" << endl;
	mergedFile.close();

	
	return 0;
	
}// end of mergeFiles ////////////////////////////////////////////////////


class TekFileReader {

	private:
	
	bool bombed = false;
	string tekFileName;
	ifstream file;
	vector<double> times;
	const static unsigned nChannels = 4;
	vector<double> voltages[nChannels];
	string dataType;
	int event;
	int returnEvent;
	int nData;
	int nChan;
	
	public: 
	
	int recLen; 
	double sampleInt;	
	double inputCharge;
	
	int dummy1; 
	double dummy2;


	TekFileReader(string _tekFileName = "convertedFile"){// constructor
	
		tekFileName = _tekFileName;	
		file.open(tekFileName);
		if(!file){
			cout << "error opening file " << tekFileName << endl;
			bombed = true;
			return;
		}
		else cout << "successfully opened " << tekFileName << endl;
		
		//int recLen; double sampleInt; int trigPoint; double trigTime;
		file >> recLen >> sampleInt >> inputCharge >> dummy1 >> dummy2;
		
		cout << endl;
		cout << "Waveform record length: " << recLen << endl;
		cout << "Waveforn sampling interval: " << sampleInt*1.e12 << " ps" << endl << endl;
		
		file >> dataType;
		file >> nData;
		
		times.clear();
		for(int iC = 0; iC != nChannels; ++iC) voltages[iC].clear();
		
		file >> dataType;
		file >> event;
		
		
	}// end of constructor
	
	int newEvent(){
	
		if(bombed) return -1;
	
		returnEvent = event;
		
		times.clear();
		for(int iC = 0; iC != nChannels; ++iC) voltages[iC].clear();
		
		if(verbose) cout << "**** newEvent " << dataType << " " << event << endl;
			
		if(dataType == "end") return -1;
		double data;
		for(int iD = 0; iD != nData; ++ iD) {
			file >> data;
			times.push_back(data);
		}
		if(verbose) cout << "times all read" << endl;
		
		for( int ich = 0; ich !=4; ++ich){

			file >> dataType;
			file >> nChan;
			
			if(dataType != "channel"){
				if(dataType == "event") {
					event = nChan; // correct wrong assumption
					return returnEvent;
					}
				else return returnEvent;
			}
			for(int iD = 0; iD != nData; ++ iD) {
				file >> data;
				voltages[nChan-1].push_back(data);
			}
			if(verbose) cout << "voltages all read" << endl;
		}
		return event;
	}// end of newEvent 
	
	
	vector<double> getTimes(){
		return times;
	}
	
	vector<double> getVoltages(int nChannel){
		return voltages[nChannel-1];
	}
	
	void close(){
		file.close();
	}
	
};// end of tekFileReader /////////////////////////////////////////

int mergeFilesWithOneChannel(string tekFilesDirectory, string fileNamePrefix, string mergedFileName) {

////////////////////////////////////////////////////////////////////

/*

Opens directory tekFilesDirectory, read all files whose name begins with fileNamePrefix,
parses the filenames for event number and channel number, create a single text file with all
events and all the channels. For the format of Tek file names see comments to parseFileName.
The format is an array of times followed by an array of voltages, one per channel. 
Data are separated by blanks. This file can be accessed using the class TekFileReader

*/


string path = tekFilesDirectory;


	// open input file directory
	DIR *dpdf = opendir(path.c_str());
	struct dirent *epdf;
	vector<string> fileNames;

	if (dpdf == NULL){
		cout << "Error opening directory " << path << endl;
		return 1;
	}
	if (dpdf != NULL){
		cout << "Successfully opened " << path << endl;
		while ((epdf = readdir(dpdf))){
	   	// push all file names into fileNames
		  fileNames.push_back(epdf->d_name);
	   }
	   closedir(dpdf);// close directory
	}
	
	
	// sort filenames alphabetically
	if(verbose) cout << fileNames.size() << " files in directory" << endl;
	std::sort(fileNames.begin(), fileNames.end());
	
	
	// open output file 
	ofstream mergedFile;
  	mergedFile.open (mergedFileName); 	
  	//mergedFile.open ("merged.txt");
  	if(!mergedFile){
  		cout << "Error opening output file " << mergedFileName << endl;
  		return 2;
  	}
  	cout << "Successfully opened " << mergedFileName << " for output" << endl;
  
	
  	int previousEvent = -1;  	
	int event = 0;
	int channel = 0;
	string timeStamp = "";
	string previousTS = "";
	
	cout << "Opening all files in directory " << path << endl;
	
	for(int i = 0; i != (int)fileNames.size(); ++i){
			if(((i+1)%100) == 0) cout << "Opening file " << i + 1 << endl << flush;
			if(verbose) cout << fileNames[i] << " " ;
			//int retCode = parseFileName(fileNames[i],fileNamePrefix, channel, event);
			int retCode = parseFileNameTimeStamp(fileNames[i], fileNamePrefix, timeStamp, channel); // When the fileName consists of the time stamp
			//if(verbose)cout << "channel " << channel << " event " << event << " retCode " << retCode << endl;
			if(verbose)cout << "channel " << channel << " timeStamp " << timeStamp << " retCode " << retCode << endl; // When the fileName consists of the time stamp
			if(retCode == 0) {
				if(event != previousEvent){	
					vector<double> times = getTimes(path+fileNames[i]);
					if(event == 0) {
						int retCode; int recLen; double sampleInt; int trigPoint; double trigTime;
						retCode = getParameters(path+fileNames[i], 
							recLen, sampleInt, trigPoint, trigTime);
						mergedFile << recLen << " " << sampleInt << " " << times[0] << " " << trigPoint << " " << trigTime << endl;
						mergedFile << "begin " << times.size() << endl;
					}
					mergedFile << endl;
					mergedFile << "event " << event << endl;
					for(int iT = 0; iT != (int)times.size(); ++iT) mergedFile << times[iT] << " ";
					mergedFile << endl;	
					previousEvent = event;
					}
				mergedFile << endl;			
				mergedFile << "channel " << channel << endl;	
				vector<double> voltages = getVoltages(path+fileNames[i]);
				for(int iV = 0; iV != (int)voltages.size(); ++iV) mergedFile << voltages[iV] << " ";
				mergedFile << endl;			
				//if( i != 0 && i%3 == 1 ) event++;
				
			}
			
	}
	mergedFile << endl << "end " <<  event+1 << " events" << endl;
	mergedFile.close();

	
	return 0;
	
}// end of mergeFiles ////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

int histSlice(TH1D & hist, TH1D & histSliced, double xMin, double xMax){

////////////////////////////////////////////////////////////////////

	int nBins = hist.GetNbinsX();
	int iBin1 = 1;
	for(; iBin1 != nBins+1; ++iBin1){
		if(hist.GetBinLowEdge(iBin1) >= xMin) break;
	
	}
	int iBin2 = iBin1+1;
	for(; iBin2 != nBins+1; ++iBin2){
		if(hist.GetBinLowEdge(iBin2) >= xMax) break;
	
	}
	
	double histLowLim = hist.GetBinLowEdge(iBin1);	
	double histHighLim = hist.GetBinLowEdge(iBin2);
	int histnBins = iBin2-iBin1;
	histSliced.SetBins(histnBins, histLowLim, histHighLim);
	
	for(int iB = 1; iB != histnBins+1; ++iB){
		double x = hist.GetBinContent(iBin1+iB-1);
		histSliced.SetBinContent(iB,x);
	}
	
	return 0;

}// end of histSlice


