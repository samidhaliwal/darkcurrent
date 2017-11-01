#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TMath.h"
#include "../PlottingStyle/style.C"
#include "../PlottingStyle/quickBinning.C"
#include "../PlottingStyle/quick2DPlot.C"

void MakePlot2D_ccd()
{
  setstyle();
  gStyle->SetPadRightMargin(0.2);

  TChain *S = new TChain("T_ccd");
  S->Add("ccd.root");

  TString ToDraw = "x_ccd:y_ccd";
  TString axisx = "#sqrt{x^{2}+y^{2}+z^{2}} (mm from IP)";
  TString axisy = "shared pixel count/500 mm (threshold 5)";
  TString CanvasName = "temp";
  TString cut = "(abs(z_ccd) < 8000 && (abs(r_ccd) < 3000) && sep16_ccd_avgIntensity != -999)";
  //TString cut = "(abs(z) > 8000 && abs(z) < 13000)";
  //TString cut = "(abs(z) > 13000 && abs(z) < 20000)";
  //TString cut = "(abs(z) > 20000)";
	
  float startx = -10000.;
  float endx = 10000.;
  float Binningx = 500;
  float starty = -10000.;
  float endy = 10000.;
  float Binningy = 500;

  int NBx = NBins(startx,endx,Binningx);
  int NBy = NBins(starty,endy,Binningy);
    
  TCanvas *cTEMP = new TCanvas("cTEMP", "cTEMP",600,500);
  TH2D *histS = new TH2D("histSig","histSigTitle",NBx,startx,endx,NBy,starty,endy);

  S->Draw(ToDraw+" >> histSig", cut, "");
  cout << "Num of ccds: " << histS->GetEntries() << endl;
	
  TCanvas *cS = Plot_Me_2D(CanvasName, histS, axisx, axisy);
  cS->SaveAs(CanvasName+".pdf");
  
}

