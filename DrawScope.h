
void DrawScope(vector<double>& time, vector<double>& voltage, string pictName = "scope"){
   
   TCanvas * scopeCanvas = new TCanvas("scopeCanvas","scopeCanvas",50,50,100,100);
   TH1D scope("scope","scope",100,time.front(),time.back());  
   
   	auto itMax = max_element(std::begin(voltage), std::end(voltage)); 
	auto itMin = min_element(std::begin(voltage), std::end(voltage)); 
	
	double maxV = *itMax;
	double minV = *itMin;
	double span = maxV - minV;
 
 	scope.SetMaximum(maxV + 0.1*span);
 	scope.SetMinimum(minV - 0.1*span);
 	scope.SetStats(false);
 	
 	int nSamples = time.size();
 	
 	
 	double t[nSamples];
 	double v[nSamples];
 	
 	for(int iS = 0; iS != nSamples; ++iS) {
 		t[iS] = time[iS];
 		v[iS] = voltage[iS];
 	}
 
    TGraph * scopeTrace = new TGraph(nSamples, t, v);
    
    scopeTrace->SetMarkerStyle(20);
	scopeTrace->SetMarkerSize(0.05);
	scopeTrace->SetMarkerColor(4);
	scopeTrace->SetLineColor(2);
	
    scopeCanvas->cd();  
    scope.Draw();
    scopeTrace->Draw("pLSAME");
    string fullFileName = pictName + ".pdf";
    scopeCanvas->SaveAs(fullFileName.c_str()); 

    delete scopeCanvas;
    
    return;
    
}; // end DrawScope

void SaveScope(vector<double>& time, vector<double>& voltage, string pictName = "scope"){

	//TCanvas * scopeCanvas = new TCanvas("scopeCanvas","scopeCanvas",1200,800);
	TH1D scope("scope","scope",100,time.front(),time.back());  
   
   	auto itMax = max_element(std::begin(voltage), std::end(voltage)); 
	auto itMin = min_element(std::begin(voltage), std::end(voltage)); 
	
	double maxV = *itMax;
	double minV = *itMin;
	double span = maxV - minV;
 
 	scope.SetMaximum(maxV + 0.1*span);
 	scope.SetMinimum(minV - 0.1*span);
 	scope.SetStats(false);
 	
 	int nSamples = time.size();
 	
 	double t[nSamples];
 	double v[nSamples];
 	
 	for(int iS = 0; iS != nSamples; ++iS) {
 		t[iS] = time[iS];
 		v[iS] = voltage[iS];
 	}
 
    TGraph * scopeTrace = new TGraph(nSamples, t, v);
    scopeTrace->SetMarkerStyle(20);
	scopeTrace->SetMarkerSize(0.05);
	scopeTrace->SetMarkerColor(4);
	scopeTrace->SetLineColor(2);

    TString fullFileName = pictName + ".root";
	TFile *output = new TFile(fullFileName, "RECREATE");
	scopeTrace->Write();

    //scopeCanvas->cd();  
    //scope.Draw();
    //scopeTrace->Draw("pLSAME");
    //string fullFileName = pictName + ".root";
    //scopeCanvas->SaveAs(fullFileName.c_str()); 

    //delete scopeCanvas;
    
    return;
    
}; // end DrawScope

void DrawScope3(vector<double>& time, vector<double>& v1,vector<double>& v2,vector<double>& v3,
					string pictName = "scope"){
   
   //TCanvas * scopeCanvas = new TCanvas("scopeCanvas","scopeCanvas",50,50,100,100);
   TCanvas * scopeCanvas = new TCanvas("scopeCanvas","scopeCanvas",1200,800);
   TH1D scope("scope","scope",100,time.front(),time.back());  
   
   	auto itMax1 = max_element(std::begin(v1), std::end(v1)); 
	auto itMin1 = min_element(std::begin(v1), std::end(v1)); 	
	double maxV1 = *itMax1;
	double minV1 = *itMin1;
	
	auto itMax2 = max_element(std::begin(v2), std::end(v2)); 
	auto itMin2 = min_element(std::begin(v2), std::end(v2)); 	
	double maxV2 = *itMax2;
	double minV2 = *itMin2;
	
	auto itMax3 = max_element(std::begin(v3), std::end(v3)); 
	auto itMin3 = min_element(std::begin(v3), std::end(v3)); 	
	double maxV3 = *itMax3;
	double minV3 = *itMin3;
	
	double maxV = max(maxV1, maxV2);
	maxV = max(maxV,maxV3);
	double minV = min(minV1, minV2);
	minV = min(minV,minV3);
	
	
	
	double span = maxV - minV;
 
 	scope.SetMaximum(maxV + 0.1*span);
 	scope.SetMinimum(minV - 0.1*span);
 	scope.SetStats(false);
 	
 	int nSamples = time.size();
 	
 	
 	double t[nSamples];
 	double vp1[nSamples];
 	double vp2[nSamples];	
 	double vp3[nSamples];
 	
 	for(int iS = 0; iS != nSamples; ++iS) {
 		t[iS] = time[iS];
 		vp1[iS] = v1[iS];
 		vp2[iS] = v2[iS];
 		vp3[iS] = v3[iS];
 	}
 
    TGraph * scopeTrace1 = new TGraph(nSamples, t, vp1);
    TGraph * scopeTrace2 = new TGraph(nSamples, t, vp2);
    TGraph * scopeTrace3 = new TGraph(nSamples, t, vp3);
    
    scopeTrace1->SetMarkerStyle(20);
	scopeTrace1->SetMarkerSize(0.05);
	scopeTrace1->SetMarkerColor(4);
	scopeTrace1->SetLineColor(2);
	
	scopeTrace2->SetMarkerStyle(20);
	scopeTrace2->SetMarkerSize(0.05);
	scopeTrace2->SetMarkerColor(4);
	scopeTrace2->SetLineColor(4);
	
	scopeTrace3->SetMarkerStyle(20);
	scopeTrace3->SetMarkerSize(0.05);
	scopeTrace3->SetMarkerColor(4);
	scopeTrace3->SetLineColor(1);
	
		
    scopeCanvas->cd();  
    scope.Draw();
    scopeCanvas->SetGrid();
    scopeTrace1->Draw("LSAME");
    scopeTrace2->Draw("LSAME");
    scopeTrace3->Draw("LSAME");
    
      
    //string fullFileName = pictName + ".pdf";
    string fullFileName = pictName + ".png";
    scopeCanvas->SaveAs(fullFileName.c_str()); 

    delete scopeCanvas;
    
    return;
    
}; // end DrawScope

