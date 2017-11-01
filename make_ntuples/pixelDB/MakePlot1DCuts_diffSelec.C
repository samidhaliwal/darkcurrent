#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TGaxis.h"
#include "../PlottingStyle/style.C"
#include "../PlottingStyle/quickBinning.C"
#include "../PlottingStyle/quick1DPlot.C"
	
void MakePlot1DCuts()
{
  setstyle();
  
	TChain *S = new TChain("T");
	TChain *SF = new TChain("treeF");
	S->Add("pixel.root");
	SF->Add("createHelpFile/pixel_helperfile.root"); //comment if you do not want to use anything from helper file
	
	S->AddFriend(SF); //comment if you do not want to use anything from helper file
	
	TString ToDraw = "(jun16_diffFromAvg)";

	TString AND = " && ";
	TString cutz = "(abs(z) < 8000)";

  TString cutlow = "(nov16_diffFromAvg < 0.5*jun16_diffFromAvg)";
  TString cuthigh = "(nov16_diffFromAvg >= 0.5*jun16_diffFromAvg)";
	
	//vND_relax Jan
	TString cutJRelax = "(may16_diffFromAvg < 5 && jun16_diffFromAvg > 10 && (aug16_diffFromAvg >= jun16_diffFromAvg*0.5) && (aug16_diffFromAvg < jun16_diffFromAvg*1.1) && (sep16_diffFromAvg >= jun16_diffFromAvg*0.5) && (sep16_diffFromAvg < jun16_diffFromAvg*1.1) && (oct16_diffFromAvg >= jun16_diffFromAvg*0.5) && (oct16_diffFromAvg < jun16_diffFromAvg*1.1) && (nov16_diffFromAvg >= jun16_diffFromAvg*0.5) && (nov16_diffFromAvg < jun16_diffFromAvg*1.1) && (jan17_diffFromAvg >= jun16_diffFromAvg*0.3) && (jan17_diffFromAvg < jun16_diffFromAvg*1.1))";
	
	//vND_regular Jan
	TString cutJRegular = "(may16_diffFromAvg < 5 && jun16_diffFromAvg > 10 && (aug16_diffFromAvg >= jun16_diffFromAvg*0.5) && (aug16_diffFromAvg < jun16_diffFromAvg*1.1) && (sep16_diffFromAvg >= jun16_diffFromAvg*0.5) && (sep16_diffFromAvg < jun16_diffFromAvg*1.1) && (oct16_diffFromAvg >= jun16_diffFromAvg*0.5) && (oct16_diffFromAvg < jun16_diffFromAvg*1.1) && (nov16_diffFromAvg >= jun16_diffFromAvg*0.5) && (nov16_diffFromAvg < jun16_diffFromAvg*1.1) && (jan17_diffFromAvg >= jun16_diffFromAvg*0.5) && (jan17_diffFromAvg < jun16_diffFromAvg*1.1))";
	
	//vND_loose Jan
	TString cutJLoose = "(may16_diffFromAvg < 5 && jun16_diffFromAvg > 10 && (aug16_diffFromAvg >= jun16_diffFromAvg*0.5) && (aug16_diffFromAvg < jun16_diffFromAvg*1.1) && (sep16_diffFromAvg >= jun16_diffFromAvg*0.5) && (sep16_diffFromAvg < jun16_diffFromAvg*1.1) && (oct16_diffFromAvg >= jun16_diffFromAvg*0.5) && (oct16_diffFromAvg < jun16_diffFromAvg*1.1) && (nov16_diffFromAvg >= jun16_diffFromAvg*0.5) && (nov16_diffFromAvg < jun16_diffFromAvg*1.1))";
	
	TString cutbigOR = "(aug16_diffFromAvg > jun16_diffFromAvg || sep16_diffFromAvg > jun16_diffFromAvg || oct16_diffFromAvg > jun16_diffFromAvg || nov16_diffFromAvg > jun16_diffFromAvg || jan17_diffFromAvg > jun16_diffFromAvg)";
	
	TString cut2bigOR = "((aug16_diffFromAvg > jun16_diffFromAvg && sep16_diffFromAvg > jun16_diffFromAvg) || (aug16_diffFromAvg > jun16_diffFromAvg && oct16_diffFromAvg > jun16_diffFromAvg) || (aug16_diffFromAvg > jun16_diffFromAvg && nov16_diffFromAvg > jun16_diffFromAvg) || (aug16_diffFromAvg > jun16_diffFromAvg && jan17_diffFromAvg > jun16_diffFromAvg) || (sep16_diffFromAvg > jun16_diffFromAvg && oct16_diffFromAvg > jun16_diffFromAvg) || (sep16_diffFromAvg > jun16_diffFromAvg && nov16_diffFromAvg > jun16_diffFromAvg) || (sep16_diffFromAvg > jun16_diffFromAvg && jan17_diffFromAvg > jun16_diffFromAvg) || (oct16_diffFromAvg > jun16_diffFromAvg && nov16_diffFromAvg > jun16_diffFromAvg) || (oct16_diffFromAvg > jun16_diffFromAvg && jan17_diffFromAvg > jun16_diffFromAvg) || (nov16_diffFromAvg > jun16_diffFromAvg && jan17_diffFromAvg > jun16_diffFromAvg))";

	TString cut_2month = "(may16_diffFromAvg < 5 && jun16_diffFromAvg > 5 && (aug16_diffFromAvg >= jun16_diffFromAvg*0.5) && (aug16_diffFromAvg < jun16_diffFromAvg*1.1) && (sep16_diffFromAvg >= jun16_diffFromAvg*0.5) && (sep16_diffFromAvg < jun16_diffFromAvg*1.1))";
	
	TString cutJuneGT20 = "(jun16_diffFromAvg > 20)";

	TString cut = cut_2month;
	
  TString axis = "June net intensity";
  TString axisy = "Entries";
  TString CanvasName = "temp";
  TString NameMe = "temp";
  int NCuts = 2;

  float start =  -10;
  float end = 50;
  float Binning = 1;
  int NB = NBins(start,end,Binning);  
	
	int col[7] = {46, 34, 1, 2, 3, 4, kGreen+3};//, 9, 46};
	int fill[7] = {1001, 1001, 0, 0, 0, 0, 1001};//, 1001, 1001};
	float fillalpha[7] = {0.05
		, 0.7, 0.4, 0.5, 0.4, 0.3, 0.3};//,  0.3, 0.3};

  TString *leg[7];

	leg[0] = {new TString("Neutron selection, sustained for Aug/Sep")};
	leg[1] = {new TString("All months selected, Jan relaxed")};
  //leg[1] = {new TString("Nov < 0.5*June net intensity")};
  //leg[2] = {new TString("Nov >= 0.5*June net intensity")};

  TCanvas *cTEMP = new TCanvas("cTEMP", "cTEMP", 600, 500);
  TH1D *hist[3];
  TString *thishist[3];

  for (int i = 0; i < NCuts; i++){
    thishist[i] = new TString("hist_"+std::to_string(i));
    hist[i] = new TH1D((*thishist[i]),"histTitle", NB, start, end);
  }
 
	//	S->Draw(ToDraw+" >> "+(*thishist[0]), cut, "");
	S->Draw(ToDraw+" >> "+(*thishist[0]), cut_2month, "");
	S->Draw(ToDraw+" >> "+(*thishist[1]), cutJLoose, "");
	
	//S->Draw(ToDraw+" >> "+(*thishist[1]), cutJRelax, "");
	//S->Draw(ToDraw+" >> "+(*thishist[2]), cutJLoose, "");

	int entries = hist[0]->GetEntries();
	//	int entries2 = hist[1]->GetEntries();
	//int JRegularentries = hist[0]->GetEntries();
	//int JRelaxentries = hist[1]->GetEntries();
	//int JLooseentries = hist[2]->GetEntries();
	std::cout << "Number of entries: " << entries << std::endl;
	//	std::cout << "Number of entries2: " << entries2 << std::endl;
	//std::cout << "Number of JRegular: " << JRegularentries << std::endl;
	//std::cout << "Number of JRelax: " << JRelaxentries << std::endl;
	//std::cout << "Number of JLoose: " << JLooseentries << std::endl;
	
   TCanvas *c2 = Plot_Multi_SameSamp_DiffCut_1D(CanvasName, axis, axisy, NCuts, leg, hist, col, fill, fillalpha, 1, false, true);





}

