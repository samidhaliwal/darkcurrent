#include <string>
#include <math.h>
#include <stdio.h>

TCanvas* Plot_1D(TString titlecan, TString titleX, TString titleY, TString LegName, TH1F* hist, int col, int fillstyle, bool dofit, bool pattern, bool dolatex){
  TCanvas *c = new TCanvas(titlecan,titlecan,700,500);
  
  c->Draw();
  c->cd();
  
  float histmax;
  //Signal
  int coluse = col;
  int filluse = fillstyle;

  hist->SetLineWidth(1);
  hist->SetLineStyle(1);
  hist->SetLineColor(coluse);
  hist->SetFillStyle(filluse);
  hist->SetFillColor(coluse);
  
  TH1F *hist2 = (TH1F*)hist->Clone();
  if (pattern){
    hist->SetLineColor(1);
    hist2->SetLineColor(1);
    hist2->SetFillColor(1);
    hist2->SetFillStyle(3244);
    
  }
	    
  hist->GetXaxis()->SetTitle(titleX);
  hist->GetYaxis()->SetTitle(titleY);

  //  histSig->GetYaxis()->SetRangeUser(0.0000001, ymax);
  hist->Draw();

  if (pattern)
    hist2->Draw("sames");

  float Mean, RMS, Peak, HWHM, PeakErr, HWHMErr, chisquare, prob;
  int ndf;
  if (dofit){
    Mean = hist->GetMean();
    RMS = hist->GetRMS();
    TF1 *f = new TF1("f", "[0]*TMath::CauchyDist(x, [1], [2])", Mean-1.4*RMS, Mean+1.4*RMS);
    f->SetParameters(hist->Integral(),Mean,RMS);
    f->SetParName(0,"Constant");
    f->SetParName(1,"Peak");
    f->SetParName(2,"HWHM");
    hist->Fit("f", "RL");
    std::cout << std::fixed << std::setprecision(3) << Mean;
    Peak = f->GetParameter(1);
    HWHM = f->GetParameter(2);
    PeakErr = f->GetParError(1);
    HWHMErr = f->GetParError(2);
    chisquare = f->GetChisquare();
    ndf = f->GetNDF();
    prob = f->GetProb();

    // gStyle->SetOptTitle(0);
    //gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  }

  c->cd();
  
  int SEntries = hist->GetEntries();
  
  TLegend *L = new TLegend(0.18,0.33,0.38,0.75);
  L->SetBorderSize(0);
  L->SetFillStyle(0);
  L->SetTextFont(42);
  L->SetTextSize(0.035);
  if (!pattern)
    L->AddEntry(hist, LegName, "L");
  if (pattern)
    L->AddEntry(hist2, LegName, "L");
  
  L->Draw("sames");

  TLatex t;
  int Entries = hist->GetEntries();
  std::string sEntries = std::to_string(Entries);
  char sMean[50]; sprintf(sMean, "histogram mean: %.3f", Mean);
  char sRMS[50]; sprintf(sRMS, "histogram RMS: %.3f", RMS);
  char sPeak[50]; sprintf(sPeak, "fit peak: %.3f #pm %.3f", Peak, PeakErr);
  char sHWHM[50]; sprintf(sHWHM, "fit HWHM: %.3f #pm %.3f", HWHM, HWHMErr);
  char schisquare[50]; sprintf(schisquare, "fit #chi^{2}/NDF: %.2f/%.2d", chisquare, ndf);
  char sprob[50]; sprintf(sprob, "fit prob.: %.2f", prob);


  t.SetNDC(kTRUE);
  if (dolatex){
    t.SetTextFont(42);
    t.SetTextSize(0.04);    
    t.DrawLatexNDC(0.18,0.88,("Entries: "+sEntries).c_str());
    /*
    t.DrawLatexNDC(0.18,0.83,("histogram mean: "+sMean).c_str());
    t.DrawLatexNDC(0.18,0.78,("histogram RMS: "+sRMS).c_str());
    t.DrawLatexNDC(0.18,0.73,("fit peak: "+sPeak+" #pm "+sPeakErr).c_str()); d
    t.DrawLatexNDC(0.18,0.68,("fit HWHM: "+sHWHM+" #pm "+sHWHMErr).c_str());
    t.DrawLatexNDC(0.18,0.63,("fit #chi^{2}/NDF: "+schisquare+"/"+sndf).c_str());
    t.DrawLatexNDC(0.18,0.58,("fit prob.: "+sprob).c_str());
    */
    t.DrawLatexNDC(0.18,0.83,(sMean));
    t.DrawLatexNDC(0.18,0.78,(sRMS));
    t.DrawLatexNDC(0.18,0.73,(sPeak));
    t.DrawLatexNDC(0.18,0.68,(sHWHM));
    t.DrawLatexNDC(0.18,0.63,(schisquare));
    //    t.DrawLatexNDC(0.18,0.58,(sprob));
    
  }

  return c;
  
}


TCanvas* Plot_1D_Comp(TString titlecan, TString titleX, TString titleY, TString LegName, TH1F* hist, TH1F* histO, int col, int fillstyle, bool dofit, bool pattern, bool dolatex){
  TCanvas *c = new TCanvas(titlecan,titlecan,700,500);
  cout << "HERE 0 " << endl;
  c->Draw();
  c->cd();
  
  float histmax;
  //Signal
  int coluse = col;
  int filluse = fillstyle;

  hist->SetLineWidth(2);
  hist->SetLineStyle(1);
  hist->SetLineColor(1);
  hist->SetFillColor(1);
  hist->SetFillStyle(0);
    cout << "HERE 1 " << endl;

  TH1F *hist2 = (TH1F*)hist->Clone();
  if (pattern){
    hist->SetLineColor(1);
    hist2->SetLineColor(1);
    hist2->SetFillColor(1);
    hist2->SetFillStyle(3244);
        cout << "HERE 2 " << endl;

  }
      cout << "HERE 3 " << endl;

  hist->GetXaxis()->SetTitle(titleX);
  hist->GetYaxis()->SetTitle(titleY);

  //  histSig->GetYaxis()->SetRangeUser(0.0000001, ymax);
  hist->Draw();
      cout << "HERE 4 " << endl;

  histO->SetLineColor(38);
  histO->SetFillColor(38);
  histO->SetFillStyle(1001);
  histO->Draw("sames");
  hist->Draw("sames");
    cout << "HERE 5 " << endl;

  if (pattern)
    hist2->Draw("sames");
    cout << "HERE 6 " << endl;

  float Mean[2], RMS[2], Peak[2], HWHM[2], PeakErr[2], HWHMErr[2], chisquare[2], prob[2];
  int ndf[2];
  if (dofit){
        cout << "HERE 7 " << endl;

    Mean[0] = hist->GetMean();
    RMS[0] = hist->GetRMS();
    //TF1 *f = new TF1("f", "[0]*TMath::CauchyDist(x, [1], [2])", Mean[0]-5*RMS[0], Mean[0]+5*RMS[0]);
    TF1 *f = new TF1("f", "[0]*TMath::CauchyDist(x, [1], [2])",  -20., 20);
    f->SetParameters(hist->Integral(),Mean[0],RMS[0]);
    f->SetParName(0,"Constant");
    f->SetParName(1,"Peak");
    f->SetParName(2,"HWHM");
        cout << "HERE 8 " << endl;

    hist->Fit("f", "LR");
    std::cout << std::fixed << std::setprecision(3) << Mean;
    Peak[0] = f->GetParameter(1);
    HWHM[0] = f->GetParameter(2);
    PeakErr[0] = f->GetParError(1);
    HWHMErr[0] = f->GetParError(2);
    chisquare[0] = f->GetChisquare();
    ndf[0] = f->GetNDF();
    prob[0] = f->GetProb();
        cout << "HERE 9 " << endl;

    Mean[1] = histO->GetMean();
    RMS[1] = histO->GetRMS();
    //TF1 *g = new TF1("g", "[0]*TMath::CauchyDist(x, [1], [2])", Mean[1]-5*RMS[1], Mean[1]+5*RMS[1]);
    TF1 *g = new TF1("g", "[0]*TMath::CauchyDist(x, [1], [2])", -20., 20.);
    g->SetParameters(histO->Integral(),Mean[1],RMS[1]);
    g->SetParName(0,"Constant");
    g->SetParName(1,"Peak");
    g->SetParName(2,"HWHM");
    histO->Fit("g", "LR");
    std::cout << std::fixed << std::setprecision(3) << Mean;
    Peak[1] = g->GetParameter(1);
    HWHM[1] = g->GetParameter(2);
    PeakErr[1] = g->GetParError(1);
    HWHMErr[1] = g->GetParError(2);
    chisquare[1] = g->GetChisquare();
    ndf[1] = g->GetNDF();
    prob[1] = g->GetProb();    
        cout << "HERE 10 " << endl;

    // gStyle->SetOptTitle(0);
    //gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  }

  c->cd();
  
  int SEntries = hist->GetEntries();
  
  TLegend *L = new TLegend(0.18,0.33,0.38,0.45);
  L->SetBorderSize(0);
  L->SetFillStyle(0);
  L->SetTextFont(42);
  L->SetTextSize(0.035);
  if (!pattern)
    L->AddEntry(hist, "New ILines", "L");
  if (pattern)
    L->AddEntry(hist2, LegName, "L");
  L->AddEntry(histO, "Old ILines", "F");
  
  L->Draw("sames");

  TLatex t;
  int Entries = hist->GetEntries();
  std::string sEntries = std::to_string(Entries);
  char sMean[50]; sprintf(sMean, "histogram mean: %.3f", Mean[0]);
  char sRMS[50]; sprintf(sRMS, "histogram RMS: %.3f", RMS[0]);
  char sPeak[50]; sprintf(sPeak, "fit peak: %.3f #pm %.3f", Peak[0], PeakErr[0]);
  char sHWHM[50]; sprintf(sHWHM, "fit HWHM: %.3f #pm %.3f", HWHM[0], HWHMErr[0]);
  char schisquare[50]; sprintf(schisquare, "fit #chi^{2}/NDF: %.2f/%.2d", chisquare[0], ndf[0]);
  char sprob[50]; sprintf(sprob, "fit prob.: %.2f", prob[0]);

  int Entries2 = histO->GetEntries();
  std::string sEntries2 = std::to_string(Entries2);
  char sMean2[50]; sprintf(sMean2, "histogram mean: %.3f", Mean[1]);
  char sRMS2[50]; sprintf(sRMS2, "histogram RMS: %.3f", RMS[1]);
  char sPeak2[50]; sprintf(sPeak2, "fit peak: %.3f #pm %.3f", Peak[1], PeakErr[1]);
  char sHWHM2[50]; sprintf(sHWHM2, "fit HWHM: %.3f #pm %.3f", HWHM[1], HWHMErr[1]);
  char schisquare2[50]; sprintf(schisquare2, "fit #chi^{2}/NDF: %.2f/%.2d", chisquare[1], ndf[1]);
  char sprob2[50]; sprintf(sprob2, "fit prob.: %.2f", prob[1]);

  t.SetNDC(kTRUE);
  if (dolatex){
    t.SetTextFont(42);
    t.SetTextSize(0.04);    
    t.DrawLatexNDC(0.18,0.88,("New Entries: "+sEntries).c_str());
    /*
    t.DrawLatexNDC(0.18,0.83,("histogram mean: "+sMean).c_str());
    t.DrawLatexNDC(0.18,0.78,("histogram RMS: "+sRMS).c_str());
    t.DrawLatexNDC(0.18,0.73,("fit peak: "+sPeak+" #pm "+sPeakErr).c_str()); d
    t.DrawLatexNDC(0.18,0.68,("fit HWHM: "+sHWHM+" #pm "+sHWHMErr).c_str());
    t.DrawLatexNDC(0.18,0.63,("fit #chi^{2}/NDF: "+schisquare+"/"+sndf).c_str());
    t.DrawLatexNDC(0.18,0.58,("fit prob.: "+sprob).c_str());
    */
    t.DrawLatexNDC(0.18,0.83,(sMean));
    t.DrawLatexNDC(0.18,0.78,(sRMS));
    t.DrawLatexNDC(0.18,0.73,(sPeak));
    t.DrawLatexNDC(0.18,0.68,(sHWHM));
    t.DrawLatexNDC(0.18,0.63,(schisquare));
    t.DrawLatexNDC(0.18,0.58,(sprob));

    
    t.DrawLatexNDC(0.65,0.88,("Old Entries: "+sEntries2).c_str());
    /*
    t.DrawLatexNDC(0.18,0.83,("histogram mean: "+sMean).c_str());
    t.DrawLatexNDC(0.18,0.78,("histogram RMS: "+sRMS).c_str());
    t.DrawLatexNDC(0.18,0.73,("fit peak: "+sPeak+" #pm "+sPeakErr).c_str()); d
    t.DrawLatexNDC(0.18,0.68,("fit HWHM: "+sHWHM+" #pm "+sHWHMErr).c_str());
    t.DrawLatexNDC(0.18,0.63,("fit #chi^{2}/NDF: "+schisquare+"/"+sndf).c_str());
    t.DrawLatexNDC(0.18,0.58,("fit prob.: "+sprob).c_str());
    */
    t.DrawLatexNDC(0.65,0.83,(sMean2));
    t.DrawLatexNDC(0.65,0.78,(sRMS2));
    t.DrawLatexNDC(0.65,0.73,(sPeak2));
    t.DrawLatexNDC(0.65,0.68,(sHWHM2));
    t.DrawLatexNDC(0.65,0.63,(schisquare2));
    t.DrawLatexNDC(0.65,0.58,(sprob2));
        
    
  }

  return c;
  
}



TCanvas* Plot_Multi_SameSamp_DiffCut_1D(TString titlecan,
					TString titleX, TString titleY,
					int Ncut,
					TString* LegName[Ncut], TH1D* hist[Ncut],
					int col[Ncut], int fillstyle[Ncut], float fillalpha[Ncut], int rebin, bool logy, bool drawratio){
  
  int cxrange = 700;
  int cyrange = 500;

  if ( drawratio ){
    cyrange = 570;
  }

  TCanvas *c = new TCanvas(titlecan,titlecan,cxrange,cyrange);
  c->Draw();
  c->cd();
  
  // Upper plot will be in pad1
//  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0.1); // Upper and lower plot are joined
  pad1->SetGridx();         // Vertical grid
  
  if (drawratio){
    pad1->Draw();             // Draw the upper pad: pad1
    pad1->cd();               // pad1 becomes the current pad
  }

	//TLegend *L = new TLegend(0.5,0.45,0.78,0.9);//7 entries
	//TLegend *L = new TLegend(0.5,0.45,0.75,0.50);//1 entry
	TLegend *L = new TLegend(0.5,0.45,0.75,0.60);//2 entries

	//		TLegend *L = new TLegend(0.5,0.65,0.78,0.9);
  float ymax = -1.;
  for (int i = 0; i < Ncut; i++){
    float ymax_temp = hist[i]->GetMaximum()*1.1;
    if (ymax_temp > ymax)
      ymax = ymax_temp;
  } 
  

  int Entry0 = 0;
  TString SEntry0 = "";
  
  TGaxis *axis = new TGaxis( -5, 20, -5, 220, 20,220,510,"");
  //axis->SetLabelFont(62); // Absolute font size in pixel (precision 3)
       
  for (int i = 0; i < Ncut; i++){
    int thiscol = col[i];
    int thefill = fillstyle[i];
    float thefillalpha = fillalpha[i];
    
    hist[i]->SetLineColor(thiscol);
    hist[i]->SetLineWidth(1); //specific
		hist[i]->SetLineStyle(1);
		if (i == 2 || i == 3 || i == 4 || i == 5)
			hist[i]->SetLineStyle(i);
    hist[i]->SetFillStyle(thefill);
    hist[i]->SetFillColorAlpha(thiscol,thefillalpha);
    int Entries = hist[i]->GetEntries();
    TString SEntries = std::to_string(Entries);

    if (rebin > 1)
      hist[i]->Rebin(rebin);
    
    TString name = "";

    if (i == 0){
      Entry0 = hist[i]->GetEntries();
      SEntry0 = std::to_string(Entry0);
      hist[i]->GetXaxis()->SetTitle(titleX);
      hist[i]->GetYaxis()->SetTitle(titleY);
      if (drawratio)
        hist[i]->GetXaxis()->SetNdivisions(15.);

      hist[i]->Draw();
      hist[i]->GetYaxis()->SetRangeUser(0.0001,ymax);

   name = (*(LegName[i])); //+" ("+SEntries+")";
    } else {
      float rel = 100.*float(Entries)/float(Entry0);
      stringstream stream;
      stream << fixed << setprecision(1) << rel;
      string s = stream.str();
      TString Srel = std::to_string(rel);
      name = (*(LegName[i]));// +" ("+SEntries+", "+s+"%)";
    }

    hist[i]->Draw("sames");
    //    int SEntries = hist->GetEntries();
    L->SetBorderSize(0);
    L->SetFillStyle(0);
    L->SetTextFont(42);
    L->SetTextSize(0.04);
    //L->AddEntry(hist[i], (*(LegName[i])), "L");
		/*
    if (i < Ncut - 3)//if (i != Ncut - 1)
      L->AddEntry(hist[i], name, "F");
    if (i >= Ncut - 3)//if (i == Ncut - 2)
      L->AddEntry(hist[i], name, "L");
		 */

		if (i == 2 || i == 3 || i == 4 || i == 5)
			L->AddEntry(hist[i], name, "L");
		else
			L->AddEntry(hist[i], name, "L"); //F


  }
  //  hist[1]->Draw("sames"); //specific
  hist[0]->Draw("sames");
  if (!drawratio){
  c->cd();
  L->Draw();
}
  if (drawratio){
    
    // lower plot will be in pad
    c->cd();          // Go back to the main canvas before defining pad2
    pad1->cd();
    L->Draw();
    c->cd();

    
    
    //TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
        TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.29); 
    pad2->SetTopMargin(0.05);
    pad2->SetBottomMargin(0.2);
    pad2->SetGridx(); // vertical grid
    pad2->SetGridy(); // vertical grid

      pad2->Draw();
      pad2->cd();       // pad2 becomes the current pad  
 

 

    TH1D *h2 = (TH1D*) hist[1]->Clone();
//    TH1D *h2 = (TH1D*) hist[2]->Clone();
    TH1D *h = (TH1D*) hist[0]->Clone();
  /*
    // Define the ratio plot
    h1->SetMinimum(0.0);
    h1->SetMaximum(2.);
    h1->Sumw2();  
    h1->Divide(h);
    h1->SetMarkerStyle(21);
    h1->Draw("ep");
    */

    h2->SetMinimum(0.7);
    h2->SetMaximum(1.1);
    h2->Sumw2();  
    h2->Divide(h);
    h2->SetMarkerStyle(8);
  //    h2->Draw("eb");
    h2->GetXaxis()->SetLabelSize(0.12);
    h2->GetXaxis()->SetNdivisions(15.);
    h2->GetXaxis()->SetLabelOffset(0.04);    
    h2->GetYaxis()->SetNdivisions(5.);
    h2->GetYaxis()->SetLabelSize(0.12);   
//    h2->GetXaxis()->SetTitle(titleX);
  //  h2->GetXaxis()->SetTitleSize(0.08);
//        h2->GetXaxis()->SetTitleOffset(1.3); 


    h2->Draw();
    
    
    // axis->SetLabelSize(0.14);
    // axis->Draw();
  }

    if (logy)
      c->SetLogy();
      
    if (logy && drawratio){
      c->cd();
      pad1->cd();
      pad1->SetLogy();
    }
    
  
  return c;
}



TCanvas* Plot_Multi_DiffSamp_SameCut_1D(TString titlecan,
					TString titleX, TString titleY,
					int Nsamp,
					TString* LegName[Nsamp], TH1D* hist[Nsamp],
					int col[Nsamp], int fillstyle[Nsamp]){
  
  TCanvas *c = new TCanvas(titlecan,titlecan,700,500);
  cout << "inside 0 " << endl;
  c->Draw();
  c->cd();
    TLegend *L = new TLegend(0.65,0.50,0.92,0.8);
	//  TLegend *L = new TLegend(0.15,0.20,0.92,0.95, "" ,brNDC);
  cout << "inside 1 " << endl;
  vector<float> vEntries;
  float ymax = -1.;
  for (int i = 0; i < Nsamp; i++){
    cout << "i is: " << i << endl;
    float tempY = hist[i]->GetMaximum();
    vEntries.push_back(tempY);
    cout << "ymax is: " << ymax << endl;
    if (ymax < tempY)
      ymax = tempY;
    ymax = ymax*1.1;
  }
  
    cout << "inside 2 " << endl;

  for (int i = 0; i < Nsamp; i++){
      cout << "inside 3 " << endl;

    float histmax;
    int thiscol = col[i];
    cout << "Colour is: " << thiscol << endl;
    int thefill = fillstyle[i];
    cout << "Fill is: " << thefill << endl;

    int iEntries = hist[i]->GetEntries();
    if (iEntries < 1000.)
      continue;
    //    hist[i]->Rebin(10);
    TString sEntries = std::to_string(iEntries);
    hist[i]->SetLineColor(thiscol);
    hist[i]->SetLineWidth(3);
    hist[i]->SetLineStyle(1);
    hist[i]->SetFillStyle(thefill);
    hist[i]->SetFillColor(thiscol);
   
    if (i == 0){
      hist[i]->GetYaxis()->SetRangeUser(0., 1.1);
      hist[i]->GetXaxis()->SetTitle(titleX);
      hist[i]->GetYaxis()->SetTitle(titleY);
      hist[i]->Scale(1./hist[i]->Integral());
      hist[i]->Draw();
    }

    int num = hist[i]->GetEntries();
    cout << "Entries: " << num << endl;
    hist[i]->Scale(1./hist[i]->Integral());
    hist[i]->Draw("sames");
    hist[0]->Draw("sames");
    //    int SEntries = hist->GetEntries();
    
    L->SetBorderSize(0);
    L->SetFillStyle(0);
    L->SetTextFont(42);
    L->SetTextSize(0.04);
    if (thefill == 1 || thefill == 0)
      L->AddEntry(hist[i],  (*(LegName[i])), "L"); //+" ("+sEntries+")", "L");
    if (thefill == 1001 || thefill == 3001)
      L->AddEntry(hist[i], (*(LegName[i])), "F");     
  }
  c->cd();
  L->Draw();
  
  return c;
}



TCanvas* Plot_Multi_DiffSamp_SameCut_1D_vec(TString titlecan,
					    TString titleX, TString titleY,
					    int Nsamp,
					    vector<TString*> LegName, vector<TH1D*> hist,
					    vector<int> col, vector<int> fillstyle){
  
  TCanvas *c = new TCanvas(titlecan,titlecan,700,500);
  
  c->Draw();
  c->cd();
  TLegend *L = new TLegend(0.6,0.65,0.88,0.85);

  float ymax = -1.;
  for (int i = 0; i < Nsamp; i++){
    float tempY = hist[i]->GetMaximum();
    if (ymax < tempY)
      ymax = tempY;
    ymax = ymax*1.1;
  }
  
  for (int i = 0; i < Nsamp; i++){
    float histmax;
    int thiscol = col[i];
    cout << "Colour is: " << thiscol << endl;
    int thefill = fillstyle[i];
    cout << "Fill is: " << thefill << endl;
    int iEntries = hist[i]->GetEntries();
    TString sEntries = std::to_string(iEntries);
    hist[i]->SetLineColor(thiscol);
    hist[i]->SetLineWidth(3);
    hist[i]->SetLineStyle(1);
    hist[i]->SetFillStyle(thefill);
    hist[i]->SetFillColor(thiscol);
   
    if (i == 0){
      hist[i]->GetYaxis()->SetRangeUser(0.0000001, ymax);
      hist[i]->GetXaxis()->SetTitle(titleX);
      hist[i]->GetYaxis()->SetTitle(titleY);
      hist[i]->Draw();
    }

    hist[i]->Draw("sames");
    //    int SEntries = hist->GetEntries();
    
    L->SetBorderSize(0);
    L->SetFillStyle(0);
    L->SetTextFont(42);
    L->SetTextSize(0.04);
    if (thefill == 1 || thefill == 0)
      L->AddEntry(hist[i], (*(LegName[i])), "L"); //+" ("+sEntries+")", "L");
    if (thefill == 1001 || thefill == 3001)
      L->AddEntry(hist[i], (*(LegName[i])), "F");     
  }
  c->cd();
  L->Draw();
  
  return c;
}

//HERE
void Plot_Multi_DiffSamp_SameCut_1D_sag(TString titlecan,
					TString titleX, TString titleY,
					int Nsamp,
					TString* LegName[Nsamp][5][3][17], TH1D* hist[Nsamp][5][3][17], int col[Nsamp], int fillstyle[Nsamp]){

  	  float Mean, RMS, Peak, HWHM, PeakErr, HWHMErr, chisquare, prob;
	  int nEntries, ndf;
	  bool dofit = true;

  TCanvas *c[5][3][17];
  Float_t fPeak[5][3][17];
  Float_t fHWHM[5][3][17];
  Float_t fPeakErr[5][3][17];
  Float_t fHWHMErr[5][3][17];
  TF1 *fit[5][3][17];
    
  TCanvas *cG[5][3];
  TGraphErrors *gr[5][3];

  std::cout << "Here now 0 " << std::endl;
  for (int combs = 0; combs < 5; combs++){
    for (int sides = 0; sides < 3; sides++){
      for (int sec = 0; sec < 17; sec++){
	TString can_name = titlecan+"_"+std::to_string(combs)+"_"+std::to_string(sides)+"_"+std::to_string(sec);
	c[combs][sides][sec] = new TCanvas(can_name, can_name,700,500);
    std::cout << "Here now 1 " << std::endl;

	c[combs][sides][sec]->Draw();
	c[combs][sides][sec]->cd();
	TLegend *L = new TLegend(0.57,0.80,0.85,0.85);
  std::cout << "Here now 2 " << std::endl;

	float ymax = -1.;
	for (int i = 0; i < Nsamp; i++){
	  float tempY = hist[i][combs][sides][sec]->GetMaximum();
	  if (ymax < tempY)
	    ymax = tempY;
	  ymax = ymax*1.1;
	}
	  std::cout << "Here now 3 " << std::endl;

	for (int i = 0; i < Nsamp; i++){
	  float histmax;
	  int thiscol = col[i];
	  int thefill = fillstyle[i];
	  //int iEntries = hist[i]->GetEntries();
	  //TString sEntries = std::to_string(iEntries);
	  hist[i][combs][sides][sec]->SetLineColor(1);
	  hist[i][combs][sides][sec]->SetLineWidth(1);
	  hist[i][combs][sides][sec]->SetLineStyle(1);
	  hist[i][combs][sides][sec]->SetFillStyle(thefill);
	  hist[i][combs][sides][sec]->SetFillColor(thiscol);

	  if (dofit){
	    Mean = hist[i][combs][sides][sec]->GetMean();
	    RMS = hist[i][combs][sides][sec]->GetRMS();
	    nEntries = hist[i][combs][sides][sec]->GetEntries();
	    TF1 *f = new TF1("f", "[0]*TMath::CauchyDist(x, [1], [2])", Mean-1.7*RMS, Mean+1.7*RMS);
	    f->SetParameters(hist[i][combs][sides][sec]->Integral(),Mean,RMS);
	    f->SetParName(0,"Constant");
	    f->SetParName(1,"Peak");
	    f->SetParName(2,"HWHM");
	    hist[i][combs][sides][sec]->Fit("f", "RL");
	    std::cout << std::fixed << std::setprecision(3) << Mean;
	    Peak = f->GetParameter(1);
	    HWHM = f->GetParameter(2);
	    PeakErr = f->GetParError(1);
	    HWHMErr = f->GetParError(2);
	    chisquare = f->GetChisquare();
	    ndf = f->GetNDF();
	    prob = f->GetProb();

	    fPeak[combs][sides][sec] = Peak;
	    fHWHM[combs][sides][sec] = HWHM;
	    fPeakErr[combs][sides][sec] = PeakErr;
	    fHWHMErr[combs][sides][sec] = HWHMErr;
	    fit[combs][sides][sec] = f;
  
	    // gStyle->SetOptTitle(0);
	    //gStyle->SetOptStat(0);
	    gStyle->SetOptFit(0);
	  }
	  
	  std::cout << "Here now 4 " << std::endl;
	  
	  if (i == 0){
	    std::cout << "Here now 4A " << std::endl;
	    
	    hist[i][combs][sides][sec]->GetYaxis()->SetRangeUser(0.0000001, ymax);
	    hist[i][combs][sides][sec]->GetXaxis()->SetTitle(titleX);
	    hist[i][combs][sides][sec]->GetYaxis()->SetTitle(titleY);
	    hist[i][combs][sides][sec]->Draw();
	  }
	    std::cout << "Here now 5 " << std::endl;

	  hist[i][combs][sides][sec]->Draw("sames");
	  //    int SEntries = hist->GetEntries();
	    std::cout << "Here now 5A " << std::endl;

	  
	  L->SetBorderSize(0);
	  L->SetFillStyle(0);
	  L->SetTextFont(42);
	  L->SetTextSize(0.04);
	    std::cout << "Here now 5B " << std::endl;
	  
	  L->AddEntry(hist[i][combs][sides][sec], (*(LegName[i][combs][sides][sec])), "F");
  std::cout << "Here now 6 " << std::endl;

	}
	c[combs][sides][sec]->cd();
	  std::cout << "Here now 7 " << std::endl;

	L->Draw();

	
  TLatex t;
  std::string sEntries = std::to_string(nEntries);
  char sMean[50]; sprintf(sMean, "histogram mean: %.3f", Mean);
  char sRMS[50]; sprintf(sRMS, "histogram RMS: %.3f", RMS);
  char sPeak[50]; sprintf(sPeak, "fit peak: %.3f #pm %.3f", Peak, PeakErr);
  char sHWHM[50]; sprintf(sHWHM, "fit HWHM: %.3f #pm %.3f", HWHM, HWHMErr);
  char schisquare[50]; sprintf(schisquare, "fit #chi^{2}/NDF: %.2f/%.2d", chisquare, ndf);
  char sprob[50]; sprintf(sprob, "fit prob.: %.2f", prob);


  t.SetNDC(kTRUE);
  if (dofit){
    t.SetTextFont(42);
    t.SetTextSize(0.04);    
    t.DrawLatexNDC(0.18,0.88,("Entries: "+sEntries).c_str());
    /*
    t.DrawLatexNDC(0.18,0.83,("histogram mean: "+sMean).c_str());
    t.DrawLatexNDC(0.18,0.78,("histogram RMS: "+sRMS).c_str());
    t.DrawLatexNDC(0.18,0.73,("fit peak: "+sPeak+" #pm "+sPeakErr).c_str()); d
    t.DrawLatexNDC(0.18,0.68,("fit HWHM: "+sHWHM+" #pm "+sHWHMErr).c_str());
    t.DrawLatexNDC(0.18,0.63,("fit #chi^{2}/NDF: "+schisquare+"/"+sndf).c_str());
    t.DrawLatexNDC(0.18,0.58,("fit prob.: "+sprob).c_str());
    */
    t.DrawLatexNDC(0.18,0.83,(sMean));
    t.DrawLatexNDC(0.18,0.78,(sRMS));
    t.DrawLatexNDC(0.18,0.73,(sPeak));
    t.DrawLatexNDC(0.18,0.68,(sHWHM));
    t.DrawLatexNDC(0.18,0.63,(schisquare));
    //    t.DrawLatexNDC(0.18,0.58,(sprob));
    
	  std::cout << "Here now 8 " << std::endl;

  }
  c[combs][sides][sec]->SaveAs(can_name+".pdf");

      }
      //after sector loop, make graphs
double band_y[16];
 double band_x[16];
  double band_y_err[2][16];
  TGraphErrors* gr_band[2];
  for(int i = 0; i < 16; i++){
    band_y[i] = 0.;
    band_x[i] = i*100; (double(i)-1.)*100.;
    for(int j = 0; j < 2; j++){
      if(j == 0)
        band_y_err[j][i] = 0.04;
      if(j == 1)
        band_y_err[j][i] = 0.1;
    }
  }
  for(int i = 0; i < 2; i++)
    gr_band[i] = (TGraphErrors*) new TGraphErrors(2,band_x,band_y,band_y,band_y_err[i]);
  gr_band[0]->SetFillColor(5);
  gr_band[0]->SetFillStyle(3001);
  gr_band[0]->SetLineColor(0);
  gr_band[1]->SetFillColor(5);
  gr_band[1]->SetFillStyle(3003);
  gr_band[1]->SetLineColor(0);

  TString canner_name = titlecan+"_"+std::to_string(combs)+"_"+std::to_string(sides)+"_graph";

  cG[combs][sides] = new TCanvas(canner_name,"",200,10,700,500);

  cG[combs][sides]->SetGrid();
  cG[combs][sides]->GetFrame()->SetFillColor(21);
  cG[combs][sides]->GetFrame()->SetBorderSize(12);
  
  const Int_t n = 16;
  Float_t x[n]  = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
  Float_t ex[n] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  Float_t y[n];
  Float_t ey[n];
  for (int i = 0; i < n; i++)
    {
      y[i] = fPeak[combs][sides][i+1];
      //                      ey[i] = fHWHM_scg[s][tw][i+1];
      ey[i] = fPeakErr[combs][sides][i+1];
      
    }

  gr[combs][sides] = new TGraphErrors(n,x,y,ex,ey);
  gr[combs][sides]->SetTitle("comb");
  gr[combs][sides]->SetMarkerColor(1);
  gr[combs][sides]->SetMarkerStyle(20);
  gr[combs][sides]->Draw("AP");
  gr[combs][sides]->GetYaxis()->SetRangeUser(-0.4, 0.4);
  gr[combs][sides]->GetYaxis()->SetTitle("mean sagitta [mm]");
  gr[combs][sides]->GetXaxis()->SetTitle("sector");
  
  
  for(int i = 0; i < 2; i++)
    gr_band[i]->Draw("C3");
  
  gr[combs][sides]->Draw("P");
  cG[combs][sides]->Update();
  cG[combs][sides]->SaveAs(canner_name+".pdf");
  
    }
  }





  return;// c; //[combs][sides][sec];
}



TCanvas* Plot_Multi_DiffSamp_SameCut_wRatio_1D(TString titlecan,
					TString titleX, TString titleY,
					int Nsamp,
					TString* LegName[Nsamp], TH1D* hist[Nsamp],
					int col[Nsamp], int fillstyle[Nsamp]){

  TCanvas *c = new TCanvas(titlecan,titlecan,800,800);
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
   pad1->SetBottomMargin(0); // Upper and lower plot are joined
   pad1->SetGridx();         // Vertical grid
   pad1->Draw();             // Draw the upper pad: pad1
   pad1->cd();               // pad1 becomes the current pad     

 TLegend *L = new TLegend(0.6,0.65,0.88,0.85);
//  TLegend *L = new TLegend(0.6,0.15,0.88,0.35); 

  float ymax = -1.;
  for (int i = 0; i < Nsamp; i++){
    float tempY = hist[i]->GetMaximum();
    if (ymax < tempY)
      ymax = tempY;
    ymax = ymax*1.1;
  }
  
  for (int i = 0; i < Nsamp; i++){
    pad1->cd();               // pad1 becomes the current pad     

    float histmax;
    int thiscol = col[i];
    int thefill = fillstyle[i];
    hist[i]->SetLineColor(thiscol);
    hist[i]->SetLineWidth(3);
    hist[i]->SetLineStyle(1);
    hist[i]->SetFillStyle(thefill);
    hist[i]->SetFillColor(thiscol);

       TH1F *h3 = (TH1F*)hist[0]->Clone("h3");
       TH1F *h2 = (TH1F*)hist[i]->Clone("h2");
       h3->Sumw2();
       h2->Sumw2();
    
    bool scale = false;
    if (scale){
      hist[i]->Scale(1/hist[i]->Integral());
    }


    if (i == 0){
      if (scale){
	hist[i]->GetYaxis()->SetRangeUser(0.0000001, 1);
      } else {
	hist[i]->GetYaxis()->SetRangeUser(0.0000001, ymax);
      }
      hist[i]->GetXaxis()->SetTitle(titleX);

      hist[i]->GetYaxis()->SetTitle(titleY);
         // Do not draw the Y axis label on the upper plot and redraw a small
   // axis instead, in order to avoid the first label (0) to be clipped.
      //hist[i]->GetYaxis()->SetLabelSize(0.);
      hist[i]->Draw();
    }

    hist[i]->Draw("sames");
    //    int SEntries = hist->GetEntries();
    
    L->SetBorderSize(0);
    L->SetFillStyle(0);
    L->SetTextFont(42);
    L->SetTextSize(0.04);
    L->AddEntry(hist[i], (*(LegName[i])), "L");


   TGaxis *axis = new TGaxis( -5, 20, -5, 220, 20,220,510,"");
   axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   axis->SetLabelSize(15);
   //axis->Draw();

   // lower plot will be in pad
   c->cd();          // Go back to the main canvas before defining pad2
   TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
   pad2->SetTopMargin(0);
   pad2->SetBottomMargin(0.3);
   pad2->SetGridx(); // vertical grid
   pad2->Draw();
   pad2->cd();       // pad2 becomes the current pad

   // Define the ratio plot
   h3->SetLineColor(col[0]);
  
   h3->SetMinimum(0.);  // Define Y ..
   h3->SetMaximum(1.); // .. range
   h3->Sumw2();
   h2->Sumw2();
      
   h3->SetStats(0);      // No statistics on lower plot
   //   hist[i]->Sumw2();
   h3->Divide(h2);
   h3->Sumw2();
   h2->Sumw2();
   
   h3->SetMarkerStyle(21);
   h3->Draw("ep");       // Draw the ratio plot

   // Y axis ratio plot settings
   h3->GetYaxis()->SetTitle("25ns/50ns ");
   
   h3->GetYaxis()->SetNdivisions(505);
   h3->GetYaxis()->SetTitleSize(20);
   h3->GetYaxis()->SetTitleFont(43);
   h3->GetYaxis()->SetTitleOffset(1.55);
   h3->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   h3->GetYaxis()->SetLabelSize(15);

   // X axis ratio plot settings
   h3->GetXaxis()->SetTitleSize(20);
   h3->GetXaxis()->SetTitleFont(43);
   h3->GetXaxis()->SetTitleOffset(4.);
   h3->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   h3->GetXaxis()->SetLabelSize(15);
       
    
  }
  c->cd();
  pad1->cd();
  L->Draw();
  return c;
}



TCanvas* Plot_Multi_DiffSamp_SameCut_1D_temp(TString titlecan,
					TString titleX, TString titleY,
					int Nsamp,
					TString* LegName[Nsamp], TH1D* hist[Nsamp],
					     int col[Nsamp], int fillstyle[Nsamp], bool setlog, bool drawleg){
  
  TCanvas *c = new TCanvas(titlecan,titlecan,700,500);
  cout << "inside 0 " << endl;
  c->Draw();
  c->cd();
 // TLegend *L = new TLegend(0.65,0.50,0.92,0.8);
  TLegend *L = new TLegend(0.65,0.40,0.22,0.55);
  cout << "inside 1 " << endl;
  vector<float> vEntries;
  float ymax = -1.;
  for (int i = 0; i < Nsamp; i++){
    cout << "i is: " << i << endl;
    float tempY = hist[i]->GetMaximum();
    vEntries.push_back(tempY);
    cout << "ymax is: " << ymax << endl;
    if (ymax < tempY)
      ymax = tempY;
    ymax = ymax*1.1;
  }
  
    cout << "inside 2 " << endl;

    int Entries;
    float Mean;
    float RMS;

    
  for (int i = 0; i < Nsamp; i++){
      cout << "inside 3 " << endl;

      Entries = hist[i]->GetEntries();
      Mean = hist[i]->GetMean();
      RMS = hist[i]->GetRMS();

      
    float histmax;
    int thiscol = col[i];
    cout << "Colour is: " << thiscol << endl;
    int thefill = fillstyle[i];
        cout << "Fill is: " << thefill << endl;

    int iEntries = hist[i]->GetEntries();
    // if (iEntries < 1000.)
    // continue;
    //    hist[i]->Rebin(10);
    TString sEntries = std::to_string(iEntries);
    hist[i]->SetLineColor(thiscol);
    hist[i]->SetLineWidth(1);
    hist[i]->SetLineStyle(1);
    hist[i]->SetFillStyle(thefill);
    hist[i]->SetFillColor(thiscol);
   
    if (i == 0){
      //      hist[i]->GetYaxis()->SetRangeUser(0., 1.1);
      hist[i]->GetXaxis()->SetTitle(titleX);
      hist[i]->GetYaxis()->SetTitle(titleY);
      //hist[i]->Scale(1./hist[i]->Integral());
      hist[i]->Draw();

    }

    int num = hist[i]->GetEntries();
    cout << "Entries: " << num << endl;
    //    hist[i]->Scale(1./hist[i]->Integral());
    hist[i]->Draw("sames");
    hist[0]->Draw("sames");
    //    int SEntries = hist->GetEntries();
    
    L->SetBorderSize(0);
    L->SetFillStyle(0);
    L->SetTextFont(42);
    L->SetTextSize(0.04);
    if (thefill == 1 || thefill == 0)
      L->AddEntry(hist[i],  (*(LegName[i])), "L"); //+" ("+sEntries+")", "L");
    if (thefill == 1001 || thefill == 3001)
      L->AddEntry(hist[i], (*(LegName[i])), "F");     
  }
  c->cd();
  if (setlog)
    gPad->SetLogy();
  if (drawleg)
    L->Draw();


  TLatex t;
  std::string sEntries = std::to_string(Entries);
  char sMean[50]; sprintf(sMean, "Mean: %.3f", Mean);
  char sRMS[50]; sprintf(sRMS, "RMS: %.3f", RMS);


  t.SetNDC(kTRUE);
    t.SetTextFont(42);
    t.SetTextSize(0.04);    
    t.DrawLatexNDC(0.18,0.88,("Entries: "+sEntries).c_str());
    /*
    t.DrawLatexNDC(0.18,0.83,("histogram mean: "+sMean).c_str());
    t.DrawLatexNDC(0.18,0.78,("histogram RMS: "+sRMS).c_str());
    t.DrawLatexNDC(0.18,0.73,("fit peak: "+sPeak+" #pm "+sPeakErr).c_str()); d
    t.DrawLatexNDC(0.18,0.68,("fit HWHM: "+sHWHM+" #pm "+sHWHMErr).c_str());
    t.DrawLatexNDC(0.18,0.63,("fit #chi^{2}/NDF: "+schisquare+"/"+sndf).c_str());
    t.DrawLatexNDC(0.18,0.58,("fit prob.: "+sprob).c_str());
    */
    t.DrawLatexNDC(0.18,0.83,(sMean));
    t.DrawLatexNDC(0.18,0.78,(sRMS));

  
  return c;
}




TCanvas* Plot_Multi_d0Check_1D(TString titlecan,
					TString titleX, TString titleY,
					int Ncut,
					TString* LegName[Ncut], TH1D* hist[Ncut],
					int col[Ncut], int fillstyle[Ncut], int rebin, bool logy, bool drawratio){
  
  int cxrange = 700;
  int cyrange = 500;

  if ( drawratio ){
    cyrange = 570;
  }

  TCanvas *c = new TCanvas(titlecan,titlecan,cxrange,cyrange);
  c->Draw();
  c->cd();
  
  // Upper plot will be in pad1
//  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0.1); // Upper and lower plot are joined
  pad1->SetGridx();         // Vertical grid
  
  if (drawratio){
    pad1->Draw();             // Draw the upper pad: pad1
    pad1->cd();               // pad1 becomes the current pad
  }

  //TLegend *L = new TLegend(0.35,0.13,0.62,0.35); //
  TLegend *L = new TLegend(0.5,0.65,0.78,0.85);//(0.45,0.63,0.72,0.85); //(0.6,0.65,0.88,0.85);
  float ymax = -1.;
  for (int i = 0; i < Ncut; i++){
    float ymax_temp = hist[i]->GetMaximum()*1.1;
    if (ymax_temp > ymax)
      ymax = ymax_temp;
  } 
  

  int Entry0 = 0;
  TString SEntry0 = "";
  
  TGaxis *axis = new TGaxis( -5, 20, -5, 220, 20,220,510,"");
  //axis->SetLabelFont(62); // Absolute font size in pixel (precision 3)
       
  for (int i = 0; i < Ncut; i++){
    int thiscol = col[i];
    int thefill = fillstyle[i];
      
    hist[i]->SetLineColor(thiscol);
    hist[i]->SetLineWidth(2);
    hist[i]->SetLineStyle(1);
    hist[i]->SetFillStyle(thefill);
    hist[i]->SetFillColor(thiscol);
    int Entries = hist[i]->GetEntries();
    TString SEntries = std::to_string(Entries);

    if (rebin > 1)
      hist[i]->Rebin(rebin);
    
    TString name = "";

    if (i == 0){
      Entry0 = hist[i]->GetEntries();
      SEntry0 = std::to_string(Entry0);
      hist[i]->GetXaxis()->SetTitle(titleX);
      hist[i]->GetYaxis()->SetTitle(titleY);
      if (drawratio)
        hist[i]->GetXaxis()->SetNdivisions(15.);

   hist[i]->Draw();


   name = (*(LegName[i])); //+" ("+SEntries+")";
    } else {
      float rel = 100.*float(Entries)/float(Entry0);
      stringstream stream;
      stream << fixed << setprecision(1) << rel;
      string s = stream.str();
      TString Srel = std::to_string(rel);
      name = (*(LegName[i]));// +" ("+SEntries+", "+s+"%)";
    }

    hist[i]->Draw("sames");
    //    int SEntries = hist->GetEntries();
    L->SetBorderSize(0);
    L->SetFillStyle(0);
    L->SetTextFont(42);
    L->SetTextSize(0.04);
    //L->AddEntry(hist[i], (*(LegName[i])), "L");
    L->AddEntry(hist[i], name, "L");
  }
  
  if (!drawratio){
  c->cd();
  L->Draw();
}
  if (drawratio){
    
    // lower plot will be in pad
    c->cd();          // Go back to the main canvas before defining pad2
    pad1->cd();
    L->Draw();
    c->cd();

    
    
    //TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
        TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.29); 
    pad2->SetTopMargin(0.05);
    pad2->SetBottomMargin(0.2);
    pad2->SetGridx(); // vertical grid
    pad2->SetGridy(); // vertical grid

      pad2->Draw();
      pad2->cd();       // pad2 becomes the current pad  
 

 

    TH1D *h2 = (TH1D*) hist[1]->Clone();
//    TH1D *h2 = (TH1D*) hist[2]->Clone();
    TH1D *h = (TH1D*) hist[0]->Clone();

    TH1D *h2a = (TH1D*) hist[2]->Clone();
    TH1D *ha = (TH1D*) hist[0]->Clone();

    
    TH1D *h2b = (TH1D*) hist[3]->Clone();
    TH1D *hb = (TH1D*) hist[0]->Clone();
   
    TH1D *h2c = (TH1D*) hist[4]->Clone();
    TH1D *hc = (TH1D*) hist[0]->Clone();
   
   
  /*
    // Define the ratio plot
    h1->SetMinimum(0.0);
    h1->SetMaximum(2.);
    h1->Sumw2();  
    h1->Divide(h);
    h1->SetMarkerStyle(21);
    h1->Draw("ep");
    */
    h2->SetMinimum(0.3);
    h2->SetMaximum(1.9);
    h2->Sumw2();  
    h2->Divide(h);
    h2->SetMarkerStyle(20);//8
    h2->SetMarkerSize(0.5);//8
  //    h2->Draw("eb");
    h2->GetXaxis()->SetLabelSize(0.12);
    h2->GetXaxis()->SetNdivisions(15.);
    h2->GetXaxis()->SetLabelOffset(0.04);    
    h2->GetYaxis()->SetNdivisions(5.);
    h2->GetYaxis()->SetLabelSize(0.12);   
//    h2->GetXaxis()->SetTitle(titleX);
  //  h2->GetXaxis()->SetTitleSize(0.08);
//        h2->GetXaxis()->SetTitleOffset(1.3); 


    h2a->SetMarkerStyle(21);
    h2b->SetMarkerStyle(22);
    h2c->SetMarkerStyle(23);

    h2a->SetMarkerSize(0.5);
    h2b->SetMarkerSize(0.5); 
    h2c->SetMarkerSize(0.5); 
    
    int col1 = int(col[1]);
    int col2 = int(col[2]);
    int col3 = int(col[3]);
    int col4 = int(col[4]);


    h2->SetMarkerColorAlpha(col1, 0.9);
    h2->SetLineColor(col1);
    h2->SetFillColor(col1);

    h2a->SetMarkerColorAlpha(col2, 0.9);
    h2a->SetLineColor(col2);
    h2a->SetFillColor(col2);
    ha->SetMarkerColorAlpha(col2, 0.9);
    ha->SetLineColor(col2);
    ha->SetFillColor(col2);
    
    h2b->SetMarkerColorAlpha(col3, 0.9);
    h2b->SetLineColor(col3);
    h2b->SetFillColor(col3);
    hb->SetMarkerColorAlpha(col3, 0.9);
    hb->SetLineColor(col3);
    hb->SetFillColor(col3);    

    h2c->SetMarkerColorAlpha(col4, 0.9);
    h2c->SetLineColor(col4);
    h2c->SetFillColor(col4);
    hc->SetMarkerColorAlpha(col4, 0.9);
    hc->SetLineColor(col4);
    hc->SetFillColor(col4);    
    
    h2a->Sumw2();  
    h2a->Divide(ha);

    h2b->Sumw2();  
    h2b->Divide(hb);
 
    h2c->Sumw2();  
    h2c->Divide(hc);   
    
    h2->Draw("hist p");
    h2a->Draw("hist p sames");
    h2b->Draw("hist p sames");
    h2c->Draw("hist p sames");
    
    
    // axis->SetLabelSize(0.14);
    // axis->Draw();
  }


    if (logy)
      c->SetLogy();
      
    if (logy && drawratio){
      c->cd();
      pad1->cd();
      pad1->SetLogy();
    }
    
  
  return c;
}



TCanvas* Plot_Multi_d0Check_1D_4(TString titlecan,
          TString titleX, TString titleY,
          int Ncut,
          TString* LegName[Ncut], TH1D* hist[Ncut],
          int col[Ncut], int fillstyle[Ncut], int rebin, bool logy, bool drawratio){

  int cxrange = 700;
  int cyrange = 500;

  if ( drawratio ){
    cyrange = 570;
  }

  TCanvas *c = new TCanvas(titlecan,titlecan,cxrange,cyrange);
  c->Draw();
  c->cd();

  // Upper plot will be in pad1
//  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0.1); // Upper and lower plot are joined
  pad1->SetGridx();         // Vertical grid

  if (drawratio){
    pad1->Draw();             // Draw the upper pad: pad1
    pad1->cd();               // pad1 becomes the current pad
  }

  //TLegend *L = new TLegend(0.35,0.13,0.62,0.35); //
  TLegend *L = new TLegend(0.5,0.65,0.78,0.85);//(0.45,0.63,0.72,0.85); //(0.6,0.65,0.88,0.85);
  float ymax = -1.;
  for (int i = 0; i < Ncut; i++){
    float ymax_temp = hist[i]->GetMaximum()*1.1;
    if (ymax_temp > ymax)
      ymax = ymax_temp;
  } 


  int Entry0 = 0;
  TString SEntry0 = "";

  TGaxis *axis = new TGaxis( -5, 20, -5, 220, 20,220,510,"");
  //axis->SetLabelFont(62); // Absolute font size in pixel (precision 3)

  for (int i = 0; i < Ncut; i++){
    int thiscol = col[i];
    int thefill = fillstyle[i];

    hist[i]->SetLineColor(thiscol);
    hist[i]->SetLineWidth(2);
    hist[i]->SetLineStyle(1);
    hist[i]->SetFillStyle(thefill);
    hist[i]->SetFillColor(thiscol);
    int Entries = hist[i]->GetEntries();
    TString SEntries = std::to_string(Entries);

    if (rebin > 1)
      hist[i]->Rebin(rebin);

    TString name = "";

    if (i == 0){
      Entry0 = hist[i]->GetEntries();
      SEntry0 = std::to_string(Entry0);
      hist[i]->GetXaxis()->SetTitle(titleX);
      hist[i]->GetYaxis()->SetTitle(titleY);
      if (drawratio)
        hist[i]->GetXaxis()->SetNdivisions(15.);

   hist[i]->Draw();


   name = (*(LegName[i])); //+" ("+SEntries+")";
    } else {
      float rel = 100.*float(Entries)/float(Entry0);
      stringstream stream;
      stream << fixed << setprecision(1) << rel;
      string s = stream.str();
      TString Srel = std::to_string(rel);
      name = (*(LegName[i]));// +" ("+SEntries+", "+s+"%)";
    }

    hist[i]->Draw("sames");
    //    int SEntries = hist->GetEntries();
    L->SetBorderSize(0);
    L->SetFillStyle(0);
    L->SetTextFont(42);
    L->SetTextSize(0.04);
    //L->AddEntry(hist[i], (*(LegName[i])), "L");
    L->AddEntry(hist[i], name, "L");
  }

  if (!drawratio){
  c->cd();
  L->Draw();
}
  if (drawratio){

    // lower plot will be in pad
    c->cd();          // Go back to the main canvas before defining pad2
    pad1->cd();
    L->Draw();
    c->cd();



    //TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
        TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.29); 
    pad2->SetTopMargin(0.05);
    pad2->SetBottomMargin(0.2);
    pad2->SetGridx(); // vertical grid
    pad2->SetGridy(); // vertical grid

      pad2->Draw();
      pad2->cd();       // pad2 becomes the current pad  




    TH1D *h2 = (TH1D*) hist[1]->Clone();
//    TH1D *h2 = (TH1D*) hist[2]->Clone();
    TH1D *h = (TH1D*) hist[0]->Clone();

    TH1D *h2a = (TH1D*) hist[2]->Clone();
    TH1D *ha = (TH1D*) hist[0]->Clone();


    TH1D *h2b = (TH1D*) hist[3]->Clone();
    TH1D *hb = (TH1D*) hist[0]->Clone();

    TH1D *h2c = (TH1D*) hist[4]->Clone();
    TH1D *hc = (TH1D*) hist[0]->Clone();

  /*
    // Define the ratio plot
    h1->SetMinimum(0.0);
    h1->SetMaximum(2.);
    h1->Sumw2();  
    h1->Divide(h);
    h1->SetMarkerStyle(21);
    h1->Draw("ep");
    */
    h2->SetMinimum(0.3);
    h2->SetMaximum(1.9);
    h2->Sumw2();  
    h2->Divide(h);
    h2->SetMarkerStyle(20);//8
    h2->SetMarkerSize(0.5);//8
  //    h2->Draw("eb");
    h2->GetXaxis()->SetLabelSize(0.12);
    h2->GetXaxis()->SetNdivisions(15.);
    h2->GetXaxis()->SetLabelOffset(0.04);    
    h2->GetYaxis()->SetNdivisions(5.);
    h2->GetYaxis()->SetLabelSize(0.12);   
//    h2->GetXaxis()->SetTitle(titleX);
  //  h2->GetXaxis()->SetTitleSize(0.08);
//        h2->GetXaxis()->SetTitleOffset(1.3); 


    h2a->SetMarkerStyle(21);
    h2b->SetMarkerStyle(22);
    h2c->SetMarkerStyle(23);

    h2a->SetMarkerSize(0.5);
    h2b->SetMarkerSize(0.5); 
    h2c->SetMarkerSize(0.5); 

    int col1 = int(col[1]);
    int col2 = int(col[2]);
    int col3 = int(col[3]);
    int col4 = int(col[4]);



    h2->SetMarkerColorAlpha(col1, 0.9);
    h2->SetLineColor(col1);
    h2->SetFillColor(col1);

    h2a->SetMarkerColorAlpha(col2, 0.9);
    h2a->SetLineColor(col2);
    h2a->SetFillColor(col2);
    ha->SetMarkerColorAlpha(col2, 0.9);
    ha->SetLineColor(col2);
    ha->SetFillColor(col2);

    h2b->SetMarkerColorAlpha(col3, 0.9);
    h2b->SetLineColor(col3);
    h2b->SetFillColor(col3);
    hb->SetMarkerColorAlpha(col3, 0.9);
    hb->SetLineColor(col3);
    hb->SetFillColor(col3);    
    
    h2c->SetMarkerColorAlpha(col4, 0.9);
    h2c->SetLineColor(col4);
    h2c->SetFillColor(col4);
    hc->SetMarkerColorAlpha(col4, 0.9);
    hc->SetLineColor(col4);
    hc->SetFillColor(col4);    

    h2a->Sumw2();  
    h2a->Divide(ha);

    h2b->Sumw2();  
    h2b->Divide(hb);
    
    h2c->Sumw2();  
    h2c->Divide(hc);

    h2->Draw("hist p");
    h2a->Draw("hist p sames");
    h2b->Draw("hist p sames");
    h2c->Draw("hist p sames");


    // axis->SetLabelSize(0.14);
    // axis->Draw();
  }


    if (logy)
      c->SetLogy();

    if (logy && drawratio){
      c->cd();
      pad1->cd();
      pad1->SetLogy();
    }


  return c;
}



TCanvas* Plot_1D_simple(TString titlecan, TString titleX, TString titleY, TH1D* hist, int col, int fillstyle, bool dology, bool dolatex){
  TCanvas *c = new TCanvas(titlecan,titlecan,700,500);

  c->Draw();
  c->cd();

  float histmax;
  //Signal
  int coluse = col;
  int filluse = fillstyle;

  hist->SetLineWidth(2);
  hist->SetLineStyle(1);
  hist->SetLineColor(coluse);
  hist->SetFillStyle(filluse);
  hist->SetFillColor(coluse);

  hist->GetXaxis()->SetTitle(titleX);
  hist->GetYaxis()->SetTitle(titleY);

  /// float ymax = hist->GetMaximum()*1.3;

  //  hist->GetYaxis()->SetRangeUser(0.8, ymax);
  hist->Draw();

  c->cd();

/*
  TLegend *L = new TLegend(0.18,0.33,0.38,0.75);
  L->SetBorderSize(0);
  L->SetFillStyle(0);
  L->SetTextFont(42);
  L->SetTextSize(0.035);
  L->AddEntry(hist, LegName, "L");
  
  L->Draw("sames");
*/
  TLatex t;
  int Entries = hist->GetEntries();
  float Mean = hist->GetMean();
  float RMS = hist->GetRMS();
  
  std::string sEntries = std::to_string(Entries);
  char sMean[50]; sprintf(sMean, "histogram mean: %.3f", Mean);
  char sRMS[50]; sprintf(sRMS, "histogram RMS: %.3f", RMS);

  t.SetNDC(kTRUE);
  if (dolatex){
    t.SetTextFont(42);
    t.SetTextSize(0.04);  
    t.DrawLatexNDC(0.18,0.88, titlecan); 
    t.DrawLatexNDC(0.18,0.83,("Entries: "+sEntries).c_str());
    t.DrawLatexNDC(0.18,0.78,(sMean));
    t.DrawLatexNDC(0.18,0.73,(sRMS));


  }

  if (dology)
    c->SetLogy();

  return c;

}


