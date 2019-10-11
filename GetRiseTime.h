

double GetRiseTime(TH1 * hist){

	double lowFraction = 0.10;
	double highFraction = 0.90;
		
	int nBins = hist->GetNbinsX();

	// find maximum
	double maxCont = -1000.;
	double tBin = hist->GetBinWidth(1);
	for(int iBin = 1; iBin <= nBins; ++iBin){
		double v = hist->GetBinContent(iBin);
		if(v > maxCont) maxCont = v;			
	}
	
	//cout << "maxCont: " << maxCont << endl;
	
	// establish thresholds for risetime
	double lowThresh = maxCont*lowFraction;
	double highThresh = maxCont*highFraction;
	
	
	// find low threshold crossing
	double tLow = 0.;
	unsigned iBinStart = 0;	
	for(int iBin = 1; iBin <= nBins; ++iBin){
		//double t2 = hist->GetXaxis()->GetBinLowEdge(iBin) + halfBin;
		double v2 = hist->GetBinContent(iBin);
		if(v2 >= lowThresh){
			iBinStart = iBin;
			double t1 = hist->GetXaxis()->GetBinLowEdge(iBinStart -1);
			double v1 = hist->GetBinContent(iBinStart -1);			
			tLow = t1 + tBin*(lowThresh-v1)/(v2 - v1);
			//cout << "tLow: " << tLow << endl;
			break;
		}
	}
	
	
	// find high threshold crossing
	double tHigh = 0.;
	unsigned iBinStop = 0;	
	for(int iBin = iBinStart; iBin <= nBins; ++iBin){
		//double t2 = hist->GetXaxis()->GetBinLowEdge(iBin) + halfBin;
		double v2 = hist->GetBinContent(iBin);
		if(v2 >= highThresh){
			iBinStop = iBin;
			double t1 = hist->GetXaxis()->GetBinLowEdge(iBinStop -1);
			double v1 = hist->GetBinContent(iBinStop -1);			
			tHigh = t1 + tBin*(highThresh-v1)/(v2 - v1);			
			//cout << "tHigh: " << tHigh << endl;
			break;
		}
	}
	
	return tHigh - tLow;
}

double GetFallTime(TH1 * myHist){
int nBins = myHist->GetNbinsX();

	for(int iBin = 1; iBin <= nBins; ++iBin){
		double v = myHist->GetBinContent(iBin);
		myHist->SetBinContent(iBin, -v);
	}
	return GetRiseTime(myHist);
}