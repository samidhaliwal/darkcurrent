

TCanvas* Plot_Me_2D(TString titlecan, TH2D* histo, TString titleX, TString titleY){
  TCanvas *c1 = new TCanvas(titlecan,titlecan,700,500);
  c1->Draw();
  //  histo->Scale(1./histo->Integral());
  histo->GetXaxis()->SetTitle(titleX);
  histo->GetYaxis()->SetTitle(titleY);
  //histo->GetXaxis()->CenterTitle();
  //histo->GetYaxis()->CenterTitle();
  histo->Draw("COLZ");

  gPad->Update();
   TPaletteAxis *palette = (TPaletteAxis*)histo->GetListOfFunctions()->FindObject("palette");

// the following lines moe the paletter. Choose the values you need for the position.
   /*
   palette->SetX1NDC(0.01);
   palette->SetX2NDC(0.05);
   palette->SetY1NDC(0.15);
   palette->SetY2NDC(0.94);
   gPad->Modified();
   gPad->Update();
   */
/*
   palette->SetX1NDC(0.01);
   palette->SetX2NDC(0.05);
   palette->SetY1NDC(0.15);
   palette->SetY2NDC(0.94);
   gPad->Update();

   // gPad->SetLogz(1);

   
   gPad->Modified();
   gPad->Update();
   
*/
  return c1;
}



TCanvas* Plot_Me_2D_weight(TString titlecan, TH2D* histo, TString titleX, TString titleY){
  TCanvas *c1 = new TCanvas(titlecan,titlecan,700,500);
  c1->Draw();
  histo->Scale(1./histo->Integral());
  histo->GetXaxis()->SetTitle(titleX);
  histo->GetYaxis()->SetTitle(titleY);
  //histo->GetXaxis()->CenterTitle();
  //histo->GetYaxis()->CenterTitle();
  histo->Draw("COL text");

  return c1;
}






TCanvas* Plot_Me_2D_profile(TString titlecan, TH2D* histo, TProfile* prof, TString titleX, TString titleY){
  TCanvas *c1 = new TCanvas(titlecan,titlecan,700,500);
  c1->Draw();
  histo->Scale(1./histo->Integral());
  histo->GetXaxis()->SetTitle(titleX);
  histo->GetYaxis()->SetTitle(titleY);
  //	histo->GetXaxis()->CenterTitle();
  //	histo->GetYaxis()->CenterTitle();
  histo->Draw("COLZ");
  prof = histo->ProfileX("", 1, -1, "");
  prof->Draw("sames");


  return c1;

}



TCanvas* Plot_profiles(TString titlecan, TProfile *pS, TProfile *pMC, TProfile *pD, TString titleX, TString titleY){
  TCanvas *c1 = new TCanvas(titlecan,titlecan,700,500);
  c1->Draw();
  pS->GetXaxis()->SetTitle(titleX);
  pS->GetYaxis()->SetTitle(titleY);
  //	histo->GetXaxis()->CenterTitle();
  //	histo->GetYaxis()->CenterTitle();
  //histo->Draw("COLZ");

  pS->SetLineColor(9);
  pS->SetMarkerColor(9);
  pMC->SetLineColor(8);
  pMC->SetMarkerColor(8);
  pD->SetLineColor(1);
  pD->SetMarkerColor(1);
  
  vector<float> ymax;
  ymax.push_back(pS->GetMaximum());
  ymax.push_back(pMC->GetMaximum());
  ymax.push_back(pD->GetMaximum());
  
  float ymaxUse = -1.;
  for (int i = 0; i < ymax.size(); i++)
    if (ymax[i] > ymaxUse)
      ymaxUse = ymax[i];


  pS->GetYaxis()->SetRangeUser(0.0000001, ymaxUse*1.1);
  pS->Draw("E");
  pMC->Draw("samesE");
  pD->Draw("samesE");
  

  return c1;

}

