#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TMath.h"
#include "../PlottingStyle/style.C"
#include "../PlottingStyle/quickBinning.C"
#include "../PlottingStyle/quick2DPlot.C"

void MakePlot2D_regions()
{

  setstyle();
  gStyle->SetPadRightMargin(0.2);

  TChain *S = new TChain("tree_region_avg");
	S->Add("createHelpFile/pixel_helperfile.root"); //comment if you do not want to use anything from helper file

  TString ToDraw = "(rr/1000.):(rz/1000.)";
  TString axisx = "z [m]";
  TString axisy = "r [m]";
  TString CanvasName = "temp";

	TString cut = "(rregion_avg_jun_diffFromAvg > 0.)"; //cutz;
  
  float startx = 0.;
  float endx = 20.;
  float Binningx = 0.5;
  float starty = 0.;
  float endy = 12.;
  float Binningy = 0.5;

  int NBx = NBins(startx,endx,Binningx);
  int NBy = NBins(starty,endy,Binningy);
    
  TCanvas *cTEMP = new TCanvas("cTEMP", "cTEMP",600,500);
  TH2D *histS = new TH2D("histSig","histSigTitle",NBx,startx,endx,NBy,starty,endy);
  

  S->Draw(ToDraw+" >> histSig", cut, "");
  cout << "Num Entries: " << histS->GetEntries() << endl;
  
  TCanvas *cS = Plot_Me_2D(CanvasName, histS, axisx, axisy);
  cS->SaveAs(CanvasName+".pdf");
  
}
