//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Sep 11 16:10:51 2013 by ROOT version 5.30/06
// from TChain physics/
//////////////////////////////////////////////////////////

#ifndef Analysis_h
#define Analysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include "BranchAddress.h"
#include <TH1.h>
#include <TH2.h>
#include <TLorentzVector.h>
#include <TGraph.h>
#include <TMultiGraph.h>


using namespace std;

class Analysis : virtual public BranchAddress {
  
private :

	TGraph *gr_norm[100000];
	TMultiGraph *mgr_norm;
	TGraph *gr_diffAvg[100000];
	TMultiGraph *mgr_diffAvg;
	TGraph *gr_FitEnd[100000];
	TMultiGraph *mgr_FitEnd;

	TH1F *res;
	TH1F *predictplot;
	TH1F *junVal;
	bool isWithinResolution;
	bool hasNullEntry;
	float junPredict;
	float novPredict;
	float slope;
	float slopeerr;
	float intercept;
	float intercepterr;

	float rregion_count_ccd;
	float rregion_sum_jun_diffFromAvg;
	float rregion_avg_jun_diffFromAvg;
	float rx;
	float ry;
	float rz;
	float rr;

	
public :

   Analysis(TTree *tree=0, TTree *tree_ccd=0);
   virtual ~Analysis();
   virtual void     Loop();

   
};

#endif // 
#ifdef Analysis_cxx
Analysis::Analysis(TTree *tree, TTree *tree_ccd):
BranchAddress(tree, tree_ccd)
{
}

Analysis::~Analysis()
{
}

#endif // #ifdef Analysis_h
