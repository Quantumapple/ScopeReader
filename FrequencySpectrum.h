
void FrequencySpectrum(double deltaT, vector<double>& voltage, TH1 *transform){
	
	unsigned nSamples = voltage.size();
	double fCut = 0.5/deltaT; // cut frequency = 0.5 * sampling frequency
	int iSmin = 0; // first sample to use
	int iSmax = nSamples-1; // last sample to use
	int iS0 = (iSmin + iSmax)/2;
	
	int nBins = transform->GetNbinsX();
	double f1 = transform->GetXaxis()->GetXmin();
	double f2 = transform->GetXaxis()->GetXmax();
		
	for(int iBin = 1; iBin <= nBins; ++iBin){
		double freq = (transform->GetXaxis()->GetBinLowEdge(iBin) + transform->GetXaxis()->GetBinUpEdge(iBin))/2.;
		
		TComplex s(0.,0.); // Fourier transform at freq
		TComplex I(0.,1.); // i
		
		for(int iS = iSmin; iS <= iSmax; ++iS){
			s += (double)voltage[iS]*TComplex::Exp(-I*((iS-iS0)*TMath::Pi()*freq/fCut));
		}
		
		double content = transform->GetBinContent(iBin) + s.Rho2();
		transform->SetBinContent(iBin,content);
		transform->SetBinError(iBin,0.);
	}
	
}	

void FrequencySpectrum(TH1 *hist, TH1 *transform){
	
	unsigned nSamples = hist->GetNbinsX();
	double deltaT = hist->GetBinWidth(1); // sampling time interval
	double fCut = 0.5/deltaT; // cut frequency = 0.5 * sampling frequency

	vector<double> voltage;

	for(unsigned iBin = 1; iBin <= nSamples; ++iBin) {
		voltage.push_back(hist->GetBinContent(iBin));
	}

	FrequencySpectrum(deltaT,voltage, transform);
}


void FrequencySpectrum(double t1, double t2, vector<double>& time, vector<double>& voltage, TH1 *transform){
	
	unsigned nSamples = time.size();
	double deltaT = time[1] - time[0]; // sampling time interval
	double fCut = 0.5/deltaT; // cut frequency = 0.5 * sampling frequency

	vector<double> v;

	for(unsigned iS = 0; iS != nSamples; ++iS) {
		if(time[iS] >= t1)
			v.push_back(voltage[iS]);
		if(time[iS] > t2) break;
	}

	FrequencySpectrum(deltaT,v, transform);
}

	
