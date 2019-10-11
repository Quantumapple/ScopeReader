////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

int analyzeWaveforms(string dataSetID, string prefix = ""){


////////////////////////////////////////////////////////////////////


	gErrorIgnoreLevel = kWarning; // turns off message when writing one pdf file
	
	cout << endl << endl << "Starting analysis..." << endl << endl;

	// Scope plots
	
	bool scopePlots = true;
	int nScopePlotEvents = 60;
	
	// output filenames prefix
	
	//string prefix = "";
	
	// dataset ID
	
	//string dataSetID = "Aug8_6fC_LGADlike";
	
	// Time windows for signals
	
	double tMin1;
	double tMax1; 
	
	double tMin2;
	double tMax2; 
	
	double tMin3;
	double tMax3; 

	// offsets (to be subtracted)
	
	double off1;
	double off2;
	double off3;
	
	// Thresholds
			
	double thresh1;
	double thresh2;
	double thresh3;
	
		
	// read run-dependent parameters from file 
	{
		string parameterFileName = "_parameterFiles/" + dataSetID + "_dat.txt";
		ifstream parameterFile;
		parameterFile.open(parameterFileName);
			if(!parameterFile){
				cout << "error opening file " << parameterFileName << endl;
				return -1;
			}
			else cout << "successfully opened " << parameterFileName << endl;
	
		string dummy;
		parameterFile >> dummy >> off1 >> dummy >> thresh1 >> dummy >> tMin1 >> dummy >> tMax1;
		parameterFile >> dummy >> off2 >> dummy >> thresh2 >> dummy >> tMin2 >> dummy >> tMax2;
		parameterFile >> dummy >> off3 >> dummy >> thresh3 >> dummy >> tMin3 >> dummy >> tMax3;
		parameterFile.close();
	}
	
	// open global plot file
	
	string gbfFileName = "_globalPlots/data.txt";
	
	ofstream gbf(gbfFileName, ios::app);
	if(!gbf){
				cout << "error opening file " << gbfFileName << endl;
				return -1;
			}
			else cout << "successfully opened " << gbfFileName << endl;
	
	// init data file reader
	
	string inputFileName = "_inputFiles/" + dataSetID + ".txt";
	TekFileReader reader(inputFileName);
	
	if(verbose) cout << "Record length: " << reader.recLen << " sample interval: " << reader.sampleInt << endl;
	 
   	/////////////////////////////////////////////////////////////////////////////////
	// Book histograms
	///////////////////////////////////////////////////////////////////z//////////////
	
	string histFileName  = "_histogramFiles/" + prefix + dataSetID + "_hists";
	TFile* histFile = new TFile((histFileName+".root").c_str(),"RECREATE");  // histogram file
	
	unsigned nSamples = reader.recLen;
	double inputCharge = reader.inputCharge;
	double startTime = 0.;
	double deltaT = reader.sampleInt;
	double endTime = reader.recLen*reader.sampleInt;
	
	double s = reader.sampleInt/2.;
	
	TProfile h_meanPulse1("meanPulse1","meanPulse1", nSamples,
		startTime -s, endTime -s); 
	TProfile h_meanPulse2("meanPulse2","meanPulse2", nSamples,
		startTime -s, endTime -s);
	TProfile h_meanPulse3("meanPulse3","meanPulse3", nSamples,
		startTime -s, endTime -s);
		
	TH1D h_meanPulse1_sliced( "meanPulse1_sliced","meanPulse1_sliced",100,0.,1.);// dummy x axis
	TH1D h_meanPulse2_sliced( "meanPulse2_sliced","meanPulse2_sliced",100,0.,1.);// dummy x axis
	TH1D h_meanPulse3_sliced( "meanPulse3_sliced","meanPulse3_sliced",100,0.,1.);// dummy x axis
		
	TH1D h_vMax1("vMax1","vMax1",2000,0.,1.0);
	TH1D h_vMax2("vMax2","vMax2",2000,0.,1.0);
	TH1D h_vMax3("vMax3","vMax3",2000,0.,1.0);
	TH1D h_LE1("LE1","LE1",10000,tMin1,tMax1);
	TH1D h_LE2("LE2","LE2",10000,tMin2,tMax2);
	TH1D h_LE3("LE3","LE3",10000,tMin3,tMax3);
	TH1D h_TE1("TE1","TE1",10000,tMin1,tMax1);
	TH1D h_TE2("TE2","TE2",10000,tMin2,tMax2);
	TH1D h_TE3("TE3","TE3",10000,tMin3,tMax3);
	TH1D h_LE_time("LE_time","LE_time",10000, tMin1, tMax1);
	TH1D h_TE_time("TE_time","TE_time",10000, tMin1, tMax1);
	//TH1D h_LE_time_corr("LE_time_corr","LE_time_corr",1000, -1.e-9, +1.e-9);
	TH1D h_noise1("noise1","noise1",10000, -1.,+1.);
	TH1D h_noise2("noise2","noise2",10000, -1.,+1.);
	TH1D h_noise3("noise3","noise3",10000, -1.,+1.);
	
	//TProfile h_LE_time_vs_ph("LE_time _vs_ph","LE_time _vs_ph",100,0.,0.2);
	//TProfile h_LE_time_vs_ph_corr("LE_time _vs_ph_corr","LE_time _vs_ph_corr",100,0.,0.2);
	
	
	unsigned nEvents = 0;
	
	vector<double> t;
	
	// average waveforms
	vector<double> v1_avg, v2_avg, v3_avg;
	
	for(int iEv = 0; true; ++iEv){
		int eventNumber = reader.newEvent();
		if(iEv % 100 == 0 || verbose) cout << "cycle " << iEv << " event number " << eventNumber << endl;
		if(eventNumber == -1) break;
		++nEvents;
		t = reader.getTimes();
		if(verbose)cout << "   times: " << t.size() << endl;
		
		vector<double> v1 = reader.getVoltages(1);
		if(verbose)cout << "   voltages 1: " << " " << v1.size() << endl;
		for(int i = 0; i != (int)t.size(); ++i) {
			v1[i] -= off1;
			h_meanPulse1.Fill(t[i],v1[i]);
			if(iEv == 0) v1_avg.push_back(v1[i]);
			else v1_avg[i] += v1[i];
		}
					
		vector<double> v2 = reader.getVoltages(2);
		if(verbose)cout << "   voltages 2: " << " " << v2.size() << endl;
		for(int i = 0; i != (int)t.size(); ++i) {
			v2[i] = - v2[i];
			v2[i] -= off2;
			h_meanPulse2.Fill(t[i],v2[i]);
			if(iEv == 0) v2_avg.push_back(v2[i]);
			else v2_avg[i] += v2[i];
			}
							
		vector<double> v3 = reader.getVoltages(3);
		if(verbose)cout << "   voltages 3: " << " " << v3.size() << endl;
		for(int i = 0; i != (int)t.size(); ++i) {
			//v3[i] = - v3[i];
			v3[i] -= off3;
			h_meanPulse3.Fill(t[i],v3[i]);
			if(iEv == 0) v3_avg.push_back(v3[i]);
			else v3_avg[i] += v3[i];
			}

			
		// Scope plots //////////////////////////////////
		
      	if(scopePlots && iEv < nScopePlotEvents){
			stringstream ss; 
			string fileName;
		
			/*
			// individual waveforms
			
				ss.str("");
				ss << "_scopePlots/" + prefix  + dataSetID + "_ev_" << iEv << "_Ch1";
				fileName = ss.str();			
				DrawScope(t,v1,ss.str());
					
				ss.str("");
				ss << "_scopePlots/" + prefix + dataSetID + "_ev_" << iEv << "_Ch2";
				fileName = ss.str();			
				DrawScope(t,v2,ss.str());
				
				ss.str("");
				ss << "_scopePlots/" + prefix + dataSetID + "_ev_" << iEv << "_Ch3";
				fileName = ss.str();			
				DrawScope(t,v3,ss.str());
			*/	
			// individual waveforms
		
			
				ss.str("");
				ss << "_scopeRootFiles/" + prefix  + dataSetID + "_ev_" << iEv << "_Ch1";
				fileName = ss.str();			
				SaveScope(t,v1,ss.str());
					
				ss.str("");
				ss << "_scopeRootFiles/" + prefix + dataSetID + "_ev_" << iEv << "_Ch2";
				fileName = ss.str();			
				SaveScope(t,v2,ss.str());
				
				ss.str("");
				ss << "_scopeRootFiles/" + prefix + dataSetID + "_ev_" << iEv << "_Ch3";
				fileName = ss.str();			
				SaveScope(t,v3,ss.str());
			
			// all three waveforms
			
				ss.str("");
				ss << "_scopePlots/" + prefix + dataSetID + "_ev_" << iEv ;
				fileName = ss.str();			
				DrawScope3(t,v1,v2,v3,ss.str());
			
		}
		// End scope plots //////////////////////////////////
		
		
		// compute maximum pulse heights	
		
    	double vMax1 = VMaximum(tMin1, tMax1, reader.recLen, t, v1);
    	double vMax2 = VMaximum(tMin2, tMax2, reader.recLen, t, v2);
    	double vMax3 = VMaximum(tMin3, tMax3, reader.recLen, t, v3);
    		h_vMax1.Fill(vMax1);
			h_vMax2.Fill(vMax2);
			h_vMax3.Fill(vMax3);
			
					
		// fill noise histograms
		
		for(int iSample = 0; t[iSample] < tMin1; ++iSample)
			h_noise1.Fill(v1[iSample]);
			
		for(int iSample = 0; t[iSample] < tMin2; ++iSample)
			h_noise2.Fill(v2[iSample]);
			
		for(int iSample = 0; t[iSample] < tMin3; ++iSample)
			h_noise3.Fill(v3[iSample]);
		
		
		/*
		// Leading and trailing edge times
		
		double LE1,TE1;
		{
			int retCode = TimeOverThreshold(thresh1, tMin1, tMax1, nSamples, t, v1, LE1, TE1);
			if(retCode != 0){
				cout << "TOT1 retcode = " << retCode << endl;
				return retCode;
			}
			h_LE1.Fill(LE1);
			h_TE1.Fill(TE1);
		}
				
		double LE2,TE2;
		{
			int retCode = TimeOverThreshold(thresh2, tMin2, tMax2, nSamples, t, v2, LE2, TE2);
			if(retCode != 0){
				cout << "TOT2 retcode = " << retCode << endl;
				return retCode;
			}
			h_LE2.Fill(LE2);
			h_TE2.Fill(TE2);
		}
		
				
		double LE3,TE3;
		{
			int retCode = TimeOverThreshold(thresh3, tMin3, tMax3, nSamples, t, v3, LE3, TE3);
			if(retCode != 0){
				cout << "TOT3 retcode = " << retCode << endl;
				return retCode;
			}
			h_LE3.Fill(LE3);
			h_TE3.Fill(TE3);
		}
		*/
		
		/*
		// assign channels to time reference and discriminator output
		
		double LE_reference = LE3;
		double LE_discriminator = LE1;
		double TE_discriminator = TE1;
		
		// time difference between reference and discriminator output
		
	 	double LE_time = LE_discriminator - LE_reference;
	 	h_LE_time.Fill(LE_time);
	 	double TE_time = TE_discriminator - LE_reference;	 	
	 	h_TE_time.Fill(TE_time);
	 	*/

	 	/*// time vs pulse height
	
		double ph = vMax2;
		h_LE_time_vs_ph.Fill(vMax2, LE_time);
		
		Correction timeWalk;
		double LE_time_corrected = LE_time - timeWalk.corr(vMax2);		
		h_LE_time_vs_ph_corr.Fill(vMax2, LE_time_corrected);
		h_LE_time_corr.Fill(LE_time_corrected);
		
		*/
		
		
	}// end loop on events ///////////////////////////////////////////
	
	reader.close();
		
	// normalize average waveforms
	
	for(int i = 0; i != (int)nSamples; ++i) {
		v1_avg[i] /= (double)nEvents;
		v2_avg[i] /= (double)nEvents;
		v3_avg[i] /= (double)nEvents;
	}
	
	// plot all three average waveforms
	
	stringstream ss; 
	string fileName;
	ss.str("");
	ss << "_scopePlots/" + prefix + dataSetID + "_averageWaveforms" ;
	fileName = ss.str();			
	DrawScope3(t,v1_avg,v2_avg,v3_avg,ss.str());

	// compute some relevant numbers
	
	double riseTime1 =  GetRiseTime(& h_meanPulse1);
	double riseTime2 =  GetRiseTime(& h_meanPulse2);
	double riseTime3 =  GetRiseTime(& h_meanPulse3);
	
	double meanPulseHeight1 = h_vMax1.GetMean();
	double meanPulseHeight2 = h_vMax2.GetMean();
	double meanPulseHeight3 = h_vMax3.GetMean();
	
	double meanPulseRMS1 = h_vMax1.GetRMS();
	double meanPulseRMS2 = h_vMax2.GetRMS();
	double meanPulseRMS3 = h_vMax3.GetRMS();
	
	double meanLE1 = h_LE1.GetMean();
	double meanLE2 = h_LE2.GetMean();
	double meanLE3 = h_LE3.GetMean();
	
	double meanLERMS1 = h_LE1.GetRMS();
	double meanLERMS2 = h_LE2.GetRMS();
	double meanLERMS3 = h_LE3.GetRMS();
	
	
	double leadingEdge = h_LE_time.GetMean();
	double trailingEdge = h_TE_time.GetMean();
	double LEresolution = h_LE_time.GetRMS();
	double TEresolution = h_TE_time.GetRMS();
		
	double rmsNoise1 = h_noise1.GetRMS();
	double rmsNoise2 = h_noise2.GetRMS();
	double rmsNoise3 = h_noise3.GetRMS();
	
	double offset1 = h_noise1.GetMean();
	double offset2 = h_noise2.GetMean();
	double offset3 = h_noise3.GetMean();
	
	double newOffset1 = off1+offset1;
	double newOffset2 = off2+offset2;
	double newOffset3 = off3+offset3;
	
	
	// print some results
	
	ofstream res("_results/" + prefix + dataSetID + "_results.txt");
	
	cout.precision(3);
	res.precision(4);
	
	cout << endl << endl;
	cout << "Input file: " << inputFileName << endl;
	res  << "Input file: " << inputFileName << endl;
	cout << nEvents << " events processed" << endl;
	res  << nEvents << " events processed" << endl;
	
	cout << "input charge: " << inputCharge << " fC" << endl;
	
			 
	cout << "offset 1: " << off1*1000. << " mV; residual: " << offset1*1000. << " mV"  << endl;	 
	res  << "offset 1: " << off1*1000. << " mV; residual: " << offset1*1000. << " mV"  << endl;	 
	cout << "offset 2: " << off2*1000. << " mV; residual: " << offset2*1000. << " mV"  << endl;	 
	res  << "offset 2: " << off2*1000. << " mV; residual: " << offset2*1000. << " mV"  << endl;	 
	cout << "offset 3: " << off3*1000. << " mV; residual: " << offset3*1000. << " mV"  << endl;	 
	res  << "offset 3: " << off3*1000. << " mV; residual: " << offset3*1000. << " mV"  << endl;	
	
	res << "new offset 1: " << newOffset1 << endl;
	res << "new offset 2: " << newOffset2 << endl;
	res << "new offset 3: " << newOffset3 << endl;		
			
	cout << "Threshold 1: " << thresh1*1000. << " mV" << endl;
	res  << "Threshold 1: " << thresh1*1000. << " mV" << endl;
	cout << "Threshold 2: " << thresh2*1000. << " mV" << endl;
	res  << "Threshold 2: " << thresh2*1000. << " mV" << endl;
	cout << "Threshold 3: " << thresh3*1000. << " mV" << endl;
	res  << "Threshold 3: " << thresh3*1000. << " mV" << endl;
	
	cout << "tMin 1: " << tMin1*1.e9 << " ns; tMax 1: " << tMax1*1.e9 << " ns" << endl;
	cout << "tMin 2: " << tMin2*1.e9 << " ns; tMax 2: " << tMax2*1.e9 << " ns" << endl;
	cout << "tMin 3: " << tMin3*1.e9 << " ns; tMax 3: " << tMax3*1.e9 << " ns" << endl;	
	res  << "tMin 1: " << tMin1*1.e9 << " ns; tMax 1: " << tMax1*1.e9 << " ns" << endl;
	res  << "tMin 2: " << tMin2*1.e9 << " ns; tMax 2: " << tMax2*1.e9 << " ns" << endl;
	res  << "tMin 3: " << tMin3*1.e9 << " ns; tMax 3: " << tMax3*1.e9 << " ns" << endl;
	
	cout << "Mean pulse height 1: " << meanPulseHeight1*1000 
			<< " +- " << meanPulseRMS1*1000 << " mV" << endl;
	res  << "Mean pulse height 1: " << meanPulseHeight1*1000 
			<< " +- " << meanPulseRMS1*1000 << " mV" << endl;
	cout << "Mean pulse height 2: " << meanPulseHeight2*1000 
			<< " +- " << meanPulseRMS2*1000 << " mV" << endl;
	res << "Mean pulse height 2: " << meanPulseHeight2*1000 
			<< " +- " << meanPulseRMS2*1000 << " mV" << endl;
	cout << "Mean pulse height 3: " << meanPulseHeight3*1000 
			<< " +- " << meanPulseRMS3*1000 << " mV" << endl;
	res  << "Mean pulse height 3: " << meanPulseHeight3*1000 
			<< " +- " << meanPulseRMS3*1000 << " mV" << endl;
	
	
				
	cout << "Risetime 1: " << 1.e9*riseTime1 << " ns" << endl;
	res  << "Risetime 1: " << 1.e9*riseTime1 << " ns" << endl;
	cout << "Risetime 2: " << 1.e9*riseTime2 << " ns" << endl;
	res  << "Risetime 2: " << 1.e9*riseTime2 << " ns" << endl;
	cout  << "Risetime 3: " << 1.e9*riseTime3 << " ns" << endl;
	res  << "Risetime 3: " << 1.e9*riseTime3 << " ns" << endl;


	
	cout << "RMS noise 1: " << rmsNoise1*1000. << " mV" 
		 << " signal/noise: " << meanPulseHeight1/rmsNoise1 << endl;
	res  << "RMS noise 1: " << rmsNoise1*1000. << " mV" 
		 << " signal/noise: " << meanPulseHeight1/rmsNoise1 << endl;
	cout << "RMS noise 2: " << rmsNoise2*1000. << " mV" 
		 << " signal/noise: " << meanPulseHeight2/rmsNoise2 << endl;
	res  << "RMS noise 2: " << rmsNoise2*1000. << " mV" 
		 << " signal/noise: " << meanPulseHeight2/rmsNoise2 << endl;
	cout << "RMS noise 3: " << rmsNoise3*1000. << " mV" 
		 << " signal/noise: " << meanPulseHeight3/rmsNoise3 << endl;
	res  << "RMS noise 3: " << rmsNoise3*1000. << " mV" 
		 << " signal/noise: " << meanPulseHeight3/rmsNoise3 << endl;

	
	cout << "Mean LE 1: " << meanLE1*1.e9
			<< " +- " << meanLERMS1*1.e9 << " ns" << endl;
	res  << "Mean LE 1: " << meanLE1*1.e9
			<< " +- " << meanLERMS1*1.e9 << " ns" << endl;
	cout << "Mean LE 2: " << meanLE2*1.e9 
			<< " +- " << meanLERMS2*1.e9 << " ns" << endl;
	res << "Mean LE 2: " << meanLE2*1.e9 
			<< " +- " << meanLERMS2*1.e9 << " ns" << endl;
	cout << "Mean LE 3: " << meanLE3*1.e9 
			<< " +- " << meanLERMS3*1.e9 << " ns" << endl;
	res << "Mean LE 3: " << meanLE3*1.e9 
			<< " +- " << meanLERMS3*1.e9 << " ns" << endl;
			
	cout << "Leading edge resolution: " << LEresolution*1.e12 << " ps" << endl;		
	res  << "Leading edge resolution: " << LEresolution*1.e12 << " ps" << endl;
	cout << "Leading edge: " << leadingEdge*1.e9 << " ns" << endl;
	res  << "Leading edge: " << leadingEdge*1.e9 << " ns" << endl;
			
	cout << "Trailing edge resolution: " << TEresolution*1.e12 << " ps" << endl;		
	res  << "Trailing edge resolution: " << TEresolution*1.e12 << " ps" << endl;
	cout << "Trailing edge: " << trailingEdge*1.e9 << " ns" << endl;
	res  << "Trailing edge: " << trailingEdge*1.e9 << " ns" << endl;
		 
	cout << "Ch1 1.2*Risetime/(S/N): " << riseTime1/meanPulseHeight1*rmsNoise1*1.e12 << " ps" << endl;
	res  << "Ch1 1.2*Risetime/(S/N): " << riseTime1/meanPulseHeight1*rmsNoise1*1.e12 << " ps" << endl;
	cout << "Ch2 1.2*Risetime/(S/N): " << riseTime2/meanPulseHeight2*rmsNoise2*1.e12 << " ps" << endl;
	res  << "Ch2 1.2*Risetime/(S/N): " << riseTime2/meanPulseHeight2*rmsNoise2*1.e12 << " ps" << endl;
	cout << "Ch3 1.2*Risetime/(S/N): " << riseTime3/meanPulseHeight3*rmsNoise3*1.e12 << " ps" << endl;
	res  << "Ch3 1.2*Risetime/(S/N): " << riseTime3/meanPulseHeight3*rmsNoise3*1.e12 << " ps" << endl;
		
	cout << endl;
	
	res.close();
	
	// add data to global plot files (append mode)
	
	gbf << inputCharge << " " << leadingEdge << " " << LEresolution << " " 
							  << trailingEdge << " " << TEresolution << endl;
	gbf.close();
	
	// create slices of pulse shapes in time windows
	histSlice(h_meanPulse1, h_meanPulse1_sliced, tMin1, tMax1);
	histSlice(h_meanPulse2, h_meanPulse2_sliced, tMin2, tMax2);
	histSlice(h_meanPulse3, h_meanPulse3_sliced, tMin3, tMax3);
	
	histFile->Write();
	
	return 0;

} // end of testCode4


