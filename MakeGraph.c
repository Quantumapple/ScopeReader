
#include <iostream>
int MakeGraph(){

  using namespace std;
  
  const int n = 100;
  Double_t x1[n], y1[n], errxl1[n], errxh1[n], erryl1[n], erryh1[n];
  Double_t x2[n], y2[n], errxl2[n], errxh2[n], erryl2[n], erryh2[n];

 TCanvas *c1 = new TCanvas("c1","Canvas",200,10,700,500);
 	c1->SetGridx();
	c1->SetGridy();

  Double_t x0[2],y0[2];
  	x0[0] = 0.;    y0[0] = 5900.;
  	x0[1] = 20.; y0[1] = 6400.;
  	
  TGraph *gr0 = new TGraph(2,x0,y0);  
  
	  gr0->SetTitle("Time walk");
	  gr0->GetXaxis()->SetTitle("input charge (fC)");
	  gr0->GetYaxis()->SetTitle("delay (ps)");
	  gr0->Draw("AP"); 
  
	int i = -1;
	
	x1[++i] =  4.; y1[i] = 6359; errxl1[i] = 0.; errxh1[i] = 0.; erryl1[i] = 27.1; erryh1[i] = 27.1;
	x1[++i] =  6.; y1[i] = 6193; errxl1[i] = 0.; errxh1[i] = 0.; erryl1[i] = 17.7; erryh1[i] = 17.7;
	x1[++i] =  8.; y1[i] = 6114; errxl1[i] = 0.; errxh1[i] = 0.; erryl1[i] = 14.21; erryh1[i] = 14.21;
	x1[++i] =  10.; y1[i] = 6062; errxl1[i] = 0.; errxh1[i] = 0.; erryl1[i] = 12.49; erryh1[i] = 12.49;
	x1[++i] =  12.; y1[i] = 6028; errxl1[i] = 0.; errxh1[i] = 0.; erryl1[i] = 11.04; erryh1[i] = 11.04;
	x1[++i] =  15.; y1[i] = 5994; errxl1[i] = 0.; errxh1[i] = 0.; erryl1[i] = 9.419; erryh1[i] = 9.419;
	x1[++i] =  20.; y1[i] = 5958; errxl1[i] = 0.; errxh1[i] = 0.; erryl1[i] = 8.576; erryh1[i] = 8.576;
	
    TGraph *gr1 = new TGraphAsymmErrors(i+1, x1, y1, errxl1, errxh1, erryl1, erryh1);   
  
	i = -1;
  	
	x2[++i] =  4.; y2[i] = 27.1; errxl2[i] = 0.; errxh2[i] = 0.; erryl2[i] = 0.; erryh2[i] = 0.;
	x2[++i] =  6.; y2[i] = 17.7; errxl2[i] = 0.; errxh2[i] = 0.; erryl2[i] = 0.; erryh2[i] = 0.;
	x2[++i] =  8.; y2[i] = 14.21; errxl2[i] = 0.; errxh2[i] = 0.; erryl2[i] = 0.; erryh2[i] = 0.;
	x2[++i] =  10.; y2[i] = 12.49; errxl2[i] = 0.; errxh2[i] = 0.; erryl2[i] = 0.; erryh2[i] = 0.;
	x2[++i] =  12.; y2[i] = 11.04; errxl2[i] = 0.; errxh2[i] = 0.; erryl2[i] = 0.; erryh2[i] = 0.;
	x2[++i] =  15.; y2[i] = 9.419; errxl2[i] = 0.; errxh2[i] = 0.; erryl2[i] = 0.; erryh2[i] = 0.;
	x2[++i] =  20.; y2[i] = 8.576; errxl2[i] = 0.; errxh2[i] = 0.; erryl2[i] = 0.; erryh2[i] = 0.;
	
  	TGraph *gr2 = new TGraphAsymmErrors(i+1, x2, y2, errxl2, errxh2, erryl2, erryh2);
  	
 
	gr1->SetMarkerColor(4);
	gr1->SetLineColor(4);
	gr1->SetMarkerStyle(21);  
	gr1->SetMarkerSize(0.5);
	gr1->Draw("PL");  
	
	  //gr2->SetMarkerColor(2);
	  //gr2->SetMarkerStyle(21);

	
		//gr2->Draw("P");
	  
	TCanvas *c2 = new TCanvas("c2","Canvas",200,10,700,500);
 	c2->SetGridx();
	c2->SetGridy();

  	//Double_t x0[2],y0[2];
  	x0[0] = 0.;  y0[0] = 0.;
  	x0[1] = 20.; y0[1] = 30.;
  	
    gr0 = new TGraph(2,x0,y0);  
  
	gr0->SetTitle("Time resolution");
	gr0->GetXaxis()->SetTitle("input charge (fC)");
	gr0->GetYaxis()->SetTitle("time resolution (ps)");
	gr0->Draw("AP"); 
	    
	  
	gr2->SetMarkerColor(4);
	gr2->SetLineColor(4);
	gr2->SetMarkerStyle(21);  
	gr2->SetMarkerSize(1.);
	gr2->Draw("PL");  
	
	  
/*  
	  TLegend *leg = new TLegend(0.75,0.15,0.83,0.30);
	  leg->AddEntry(gr1," Eff 95%","P");
	  leg->AddEntry(gr2," Eff 90%","P");	
	  leg->Draw(); 
	  
*/

c1->SaveAs("timeWalk.pdf"); 
c2->SaveAs("timeResolution.pdf"); 
  
  return 0;
}
