#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TGaxis.h"
#include "../PlottingStyle/style.C"
#include "../PlottingStyle/quickBinning.C"
#include "../PlottingStyle/quick1DPlot.C"

#include <iomanip> // setprecision
#include <sstream> // stringstream

void MakePlot1DCuts_diffMon()
{
  setstyle();
  

  TChain *S = new TChain("T");
  TChain *SF = new TChain("treeF");
	S->Add("pixel.root");
	SF->Add("createHelpFile/pixel_helperfile.root"); //comment if you do not want to use anything from helper file
	
	S->AddFriend(SF); //comment if you do not want to use anything from helper file
	
	TString ToDraw = "(may16_diffFromAvg)";
	TString ToDrawJ = "(jun16_diffFromAvg)";
	TString ToDrawA = "(aug16_diffFromAvg)";
	TString ToDrawS = "(sep16_diffFromAvg)";
	TString ToDrawO = "(oct16_diffFromAvg)";
	TString ToDrawN = "(nov16_diffFromAvg)";
	TString ToDrawJa = "(jan17_diffFromAvg)";
	TString cutz = "(abs(z) < 8000)";

	// TString cutz = "(abs(z) < 8000 && r < 3000)";
	//TString cut1 = "(low16_diffFromAvg != -999)";// && low_avgIntensity != -999 && low16_diffFromAvg > 5 && low16_diffFromAvg_index == 1 && high16_diffFromAvg_index == 3)";

  TString cutlow = "(nov16_diffFromAvg < 0.5*jun16_diffFromAvg)";
  TString cuthigh = "(nov16_diffFromAvg >= 0.5*jun16_diffFromAvg)";

	TString cut_2month = "(may16_diffFromAvg < 5 && jun16_diffFromAvg > 5 && (aug16_diffFromAvg >= jun16_diffFromAvg*0.5) && (aug16_diffFromAvg < jun16_diffFromAvg*1.1) && (sep16_diffFromAvg >= jun16_diffFromAvg*0.5) && (sep16_diffFromAvg < jun16_diffFromAvg*1.1))";
	
	TString cutJuneGT20 = "(jun16_diffFromAvg > 20)";
	
	TString cut = cut_2month;
	
  TString axis = "Net intensity";
  TString axisy = "Entries";
  TString CanvasName = "temp";
  TString NameMe = "temp";
  int NCuts = 7;

  float start =  0;
  float end = 50;
  float Binning = 1;
  int NB = NBins(start,end,Binning);  
  
  int col[7] = {38, 46, 1, 1, 1, 1, kGreen+3};//, 9, 46};
  int fill[7] = {1001, 1001, 0, 0, 0, 0, 1001};//, 1001, 1001};
  float fillalpha[7] = {0.4
		, 0.4, 0.4, 0.5, 0.4, 0.3, 0.3};//,  0.3, 0.3};

  TString AND = " && ";

  TCanvas *cTEMP = new TCanvas("cTEMP", "cTEMP", 600, 500);
  TH1D *hist[7];
  TString *thishist[7];

  for (int i = 0; i < NCuts; i++){
    thishist[i] = new TString("hist_"+std::to_string(i));
    hist[i] = new TH1D((*thishist[i]),"histTitle", NB, start, end);
  }
 
  S->Draw(ToDraw+" >> "+(*thishist[0]), cut, "");
	S->Draw(ToDrawJ+" >> "+(*thishist[1]), cut, "");
	S->Draw(ToDrawA+" >> "+(*thishist[2]), cut, "");
	S->Draw(ToDrawS+" >> "+(*thishist[3]), cut, "");
	S->Draw(ToDrawO+" >> "+(*thishist[4]), cut, "");
	S->Draw(ToDrawN+" >> "+(*thishist[5]), cut, "");
	S->Draw(ToDrawJa+" >> "+(*thishist[6]), cut, "");

	TString *leg[7];

	float val = hist[0]->GetMean();
	stringstream stream;
	stream << fixed << setprecision(0) << val;
	string s = stream.str();
	
	
	leg[0] = {new TString("May, mean: "+s)};
	val = hist[1]->GetMean();
	stream.str("");
	stream.clear();
	stream << fixed << setprecision(0) << val;
	s = stream.str();
	leg[1] = {new TString("Jun, mean: "+s)};

	val = hist[2]->GetMean();
	stream.str("");
	stream.clear();
	stream << fixed << setprecision(0) << val;
	s = stream.str();
	leg[2] = {new TString("Aug, mean: "+s)};
	
	val = hist[3]->GetMean();
	stream.str("");
	stream.clear();
	stream << fixed << setprecision(0) << val;
	s = stream.str();
	leg[3] = {new TString("Sep, mean: "+s)};

	val = hist[4]->GetMean();
	stream.str("");
	stream.clear();
	stream << fixed << setprecision(0) << val;
	s = stream.str();
	leg[4] = {new TString("Oct, mean: "+s)};

	val = hist[5]->GetMean();
	stream.str("");
	stream.clear();
	stream << fixed << setprecision(0) << val;
	s = stream.str();
	leg[5] = {new TString("Nov, mean: "+s)};

	val = hist[6]->GetMean();
	stream.str("");
	stream.clear();
	stream << fixed << setprecision(0) << val;
	s = stream.str();
	leg[6] = {new TString("Jan, mean: "+s)};
	
	hist[0]->GetEntries();
	
   TCanvas *c2 = Plot_Multi_SameSamp_DiffCut_1D(CanvasName, axis, axisy, NCuts, leg, hist, col, fill, fillalpha, 1, false, false);





}

