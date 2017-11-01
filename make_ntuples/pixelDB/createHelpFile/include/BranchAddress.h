//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu May 25 13:50:46 2017 by ROOT version 6.06/08
// from TChain T/
//////////////////////////////////////////////////////////

#ifndef BranchAddress_h
#define BranchAddress_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "string"
using namespace std;

class BranchAddress {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
	TTree          *fChain_ccd;   //!pointer to the analyzed TTree or TChain
	Int_t           fCurrent_ccd; //!current Tree number in a TChain
	

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   string          *imageName;
   string          *aramysName;
   Float_t         x;
   Float_t         y;
   Float_t         z;
   Float_t         r;
   Int_t           may16_avgIntensity;
   Int_t           jun16_avgIntensity;
   Int_t           aug16_avgIntensity;
   Int_t           sep16_avgIntensity;
   Int_t           oct16_avgIntensity;
   Int_t           nov16_avgIntensity;
   Int_t           jan17_avgIntensity;
   Int_t           mar17_avgIntensity;
   Int_t           may17_avgIntensity;
	 Int_t           jun17a_avgIntensity;
	 Int_t           jun17b_avgIntensity;
   string          *fullName;
   Int_t           row_num;
   Int_t           col_num;
   Int_t           may16_intensity;
   Int_t           may16_diffFromAvg;
   Int_t           jun16_intensity;
   Int_t           jun16_diffFromAvg;
   Int_t           aug16_intensity;
   Int_t           aug16_diffFromAvg;
   Int_t           sep16_intensity;
   Int_t           sep16_diffFromAvg;
   Int_t           oct16_intensity;
   Int_t           oct16_diffFromAvg;
   Int_t           nov16_intensity;
   Int_t           nov16_diffFromAvg;
   Int_t           jan17_intensity;
   Int_t           jan17_diffFromAvg;
   Int_t           mar17_intensity;
   Int_t           mar17_diffFromAvg;
   Int_t           may17_intensity;
   Int_t           may17_diffFromAvg;
	 Int_t           jun17a_intensity;
	 Int_t           jun17a_diffFromAvg;
	 Int_t           jun17b_intensity;
	 Int_t           jun17b_diffFromAvg;
   Int_t           high_avgIntensity;
   Int_t           low_avgIntensity;
   Int_t           high_avgIntensity_index;
   Int_t           low_avgIntensity_index;
   Int_t           high_diffFromAvg;
   Int_t           low_diffFromAvg;
   Int_t           high_diffFromAvg_index;
   Int_t           low_diffFromAvg_index;
	
	// Declaration of leaf types
	Float_t         x_ccd;
	Float_t         y_ccd;
	Float_t         z_ccd;
	Float_t         r_ccd;
	Int_t           may16_ccd_avgIntensity;
	Int_t           jun16_ccd_avgIntensity;
	Int_t           aug16_ccd_avgIntensity;
	Int_t           sep16_ccd_avgIntensity;
	Int_t           oct16_ccd_avgIntensity;
	Int_t           nov16_ccd_avgIntensity;
	Int_t           jan17_ccd_avgIntensity;

   // List of branches
   TBranch        *b_imageName;   //!
   TBranch        *b_aramysName;   //!
   TBranch        *b_x;   //!
   TBranch        *b_y;   //!
   TBranch        *b_z;   //!
   TBranch        *b_r;   //!
   TBranch        *b_may16_avgIntensity;   //!
   TBranch        *b_jun16_avgIntensity;   //!
   TBranch        *b_aug16_avgIntensity;   //!
   TBranch        *b_sep16_avgIntensity;   //!
   TBranch        *b_oct16_avgIntensity;   //!
   TBranch        *b_nov16_avgIntensity;   //!
   TBranch        *b_jan17_avgIntensity;   //!
   TBranch        *b_mar17_avgIntensity;   //!
   TBranch        *b_may17_avgIntensity;   //!
   TBranch        *b_fullName;   //!
   TBranch        *b_row_num;   //!
   TBranch        *b_col_num;   //!
   TBranch        *b_may16_intensity;   //!
   TBranch        *b_may16_diffFromAvg;   //!
   TBranch        *b_jun16_intensity;   //!
   TBranch        *b_jun16_diffFromAvg;   //!
   TBranch        *b_aug16_intensity;   //!
   TBranch        *b_aug16_diffFromAvg;   //!
   TBranch        *b_sep16_intensity;   //!
   TBranch        *b_sep16_diffFromAvg;   //!
   TBranch        *b_oct16_intensity;   //!
   TBranch        *b_oct16_diffFromAvg;   //!
   TBranch        *b_nov16_intensity;   //!
   TBranch        *b_nov16_diffFromAvg;   //!
   TBranch        *b_jan17_intensity;   //!
   TBranch        *b_jan17_diffFromAvg;   //!
   TBranch        *b_mar17_intensity;   //!
   TBranch        *b_mar17_diffFromAvg;   //!
   TBranch        *b_may17_intensity;   //!
   TBranch        *b_may17_diffFromAvg;   //!
   TBranch        *b_high_avgIntensity;   //!
   TBranch        *b_low_avgIntensity;   //!
   TBranch        *b_high_avgIntensity_index;   //!
   TBranch        *b_low_avgIntensity_index;   //!
   TBranch        *b_high_diffFromAvg;   //!
   TBranch        *b_low_diffFromAvg;   //!
   TBranch        *b_high_diffFromAvg_index;   //!
   TBranch        *b_low_diffFromAvg_index;   //!

	// List of branches

	TBranch        *b_x_ccd;   //!
	TBranch        *b_y_ccd;   //!
	TBranch        *b_z_ccd;   //!
	TBranch        *b_r_ccd;   //!
	TBranch        *b_may16_ccd_avgIntensity;   //!
	TBranch        *b_jun16_ccd_avgIntensity;   //!
	TBranch        *b_aug16_ccd_avgIntensity;   //!
	TBranch        *b_sep16_ccd_avgIntensity;   //!
	TBranch        *b_oct16_ccd_avgIntensity;   //!
	TBranch        *b_nov16_ccd_avgIntensity;   //!
	TBranch        *b_jan17_ccd_avgIntensity;   //!
	
   BranchAddress(TTree *tree=0, TTree *tree_ccd=0);
   virtual ~BranchAddress();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
	 virtual Long64_t LoadTree_ccd(Long64_t entry);
   virtual void     Init(TTree *tree, TTree *tree_ccd);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef BranchAddress_cxx
BranchAddress::BranchAddress(TTree *tree, TTree *tree_ccd) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("T",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("T","");
      chain->Add("../Analysis20170525_ccd_vND_loose.root/T");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree, tree_ccd);
}

BranchAddress::~BranchAddress()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
	
	if (!fChain_ccd) return;
	delete fChain_ccd->GetCurrentFile();
}

Int_t BranchAddress::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t BranchAddress::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

Long64_t BranchAddress::LoadTree_ccd(Long64_t entry)
{
	// Set the environment to read one entry
	if (!fChain_ccd) return -5;
	Long64_t centry = fChain_ccd->LoadTree(entry);
	if (centry < 0) return centry;
	if (fChain_ccd->GetTreeNumber() != fCurrent) {
		fCurrent_ccd = fChain_ccd->GetTreeNumber();
		Notify();
	}
	return centry;
}


void BranchAddress::Init(TTree *tree, TTree *tree_ccd)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   imageName = 0;
   aramysName = 0;
   fullName = 0;
   imageName = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);
	
	if (!tree_ccd) return;
	fChain_ccd = tree_ccd;
	fCurrent_ccd = -1;
	fChain_ccd->SetMakeClass(1);

   fChain->SetBranchAddress("imageName", &imageName, &b_imageName);
   fChain->SetBranchAddress("aramysName", &aramysName, &b_aramysName);
   fChain->SetBranchAddress("x", &x, &b_x);
   fChain->SetBranchAddress("y", &y, &b_y);
   fChain->SetBranchAddress("z", &z, &b_z);
   fChain->SetBranchAddress("r", &r, &b_r);
   fChain->SetBranchAddress("may16_avgIntensity", &may16_avgIntensity, &b_may16_avgIntensity);
   fChain->SetBranchAddress("jun16_avgIntensity", &jun16_avgIntensity, &b_jun16_avgIntensity);
   fChain->SetBranchAddress("aug16_avgIntensity", &aug16_avgIntensity, &b_aug16_avgIntensity);
   fChain->SetBranchAddress("sep16_avgIntensity", &sep16_avgIntensity, &b_sep16_avgIntensity);
   fChain->SetBranchAddress("oct16_avgIntensity", &oct16_avgIntensity, &b_oct16_avgIntensity);
   fChain->SetBranchAddress("nov16_avgIntensity", &nov16_avgIntensity, &b_nov16_avgIntensity);
   fChain->SetBranchAddress("jan17_avgIntensity", &jan17_avgIntensity, &b_jan17_avgIntensity);
   fChain->SetBranchAddress("mar17_avgIntensity", &mar17_avgIntensity, &b_mar17_avgIntensity);
   fChain->SetBranchAddress("may17_avgIntensity", &may17_avgIntensity, &b_may17_avgIntensity);
   fChain->SetBranchAddress("fullName", &fullName, &b_fullName);
   fChain->SetBranchAddress("row_num", &row_num, &b_row_num);
   fChain->SetBranchAddress("col_num", &col_num, &b_col_num);
//    fChain->SetBranchAddress("imageName", &imageName, &b_imageName);
   fChain->SetBranchAddress("may16_intensity", &may16_intensity, &b_may16_intensity);
   fChain->SetBranchAddress("may16_diffFromAvg", &may16_diffFromAvg, &b_may16_diffFromAvg);
   fChain->SetBranchAddress("jun16_intensity", &jun16_intensity, &b_jun16_intensity);
   fChain->SetBranchAddress("jun16_diffFromAvg", &jun16_diffFromAvg, &b_jun16_diffFromAvg);
   fChain->SetBranchAddress("aug16_intensity", &aug16_intensity, &b_aug16_intensity);
   fChain->SetBranchAddress("aug16_diffFromAvg", &aug16_diffFromAvg, &b_aug16_diffFromAvg);
   fChain->SetBranchAddress("sep16_intensity", &sep16_intensity, &b_sep16_intensity);
   fChain->SetBranchAddress("sep16_diffFromAvg", &sep16_diffFromAvg, &b_sep16_diffFromAvg);
   fChain->SetBranchAddress("oct16_intensity", &oct16_intensity, &b_oct16_intensity);
   fChain->SetBranchAddress("oct16_diffFromAvg", &oct16_diffFromAvg, &b_oct16_diffFromAvg);
   fChain->SetBranchAddress("nov16_intensity", &nov16_intensity, &b_nov16_intensity);
   fChain->SetBranchAddress("nov16_diffFromAvg", &nov16_diffFromAvg, &b_nov16_diffFromAvg);
   fChain->SetBranchAddress("jan17_intensity", &jan17_intensity, &b_jan17_intensity);
   fChain->SetBranchAddress("jan17_diffFromAvg", &jan17_diffFromAvg, &b_jan17_diffFromAvg);
   fChain->SetBranchAddress("mar17_intensity", &mar17_intensity, &b_mar17_intensity);
   fChain->SetBranchAddress("mar17_diffFromAvg", &mar17_diffFromAvg, &b_mar17_diffFromAvg);
   fChain->SetBranchAddress("may17_intensity", &may17_intensity, &b_may17_intensity);
   fChain->SetBranchAddress("may17_diffFromAvg", &may17_diffFromAvg, &b_may17_diffFromAvg);
   fChain->SetBranchAddress("high_avgIntensity", &high_avgIntensity, &b_high_avgIntensity);
   fChain->SetBranchAddress("low_avgIntensity", &low_avgIntensity, &b_low_avgIntensity);
   fChain->SetBranchAddress("high_avgIntensity_index", &high_avgIntensity_index, &b_high_avgIntensity_index);
   fChain->SetBranchAddress("low_avgIntensity_index", &low_avgIntensity_index, &b_low_avgIntensity_index);
   fChain->SetBranchAddress("high_diffFromAvg", &high_diffFromAvg, &b_high_diffFromAvg);
   fChain->SetBranchAddress("low_diffFromAvg", &low_diffFromAvg, &b_low_diffFromAvg);
   fChain->SetBranchAddress("high_diffFromAvg_index", &high_diffFromAvg_index, &b_high_diffFromAvg_index);
   fChain->SetBranchAddress("low_diffFromAvg_index", &low_diffFromAvg_index, &b_low_diffFromAvg_index);
	

	fChain_ccd->SetBranchAddress("x_ccd", &x_ccd, &b_x_ccd);
	fChain_ccd->SetBranchAddress("y_ccd", &y_ccd, &b_y_ccd);
	fChain_ccd->SetBranchAddress("z_ccd", &z_ccd, &b_z_ccd);
	fChain_ccd->SetBranchAddress("r_ccd", &r_ccd, &b_r_ccd);
	fChain_ccd->SetBranchAddress("may16_ccd_avgIntensity", &may16_ccd_avgIntensity, &b_may16_ccd_avgIntensity);
	fChain_ccd->SetBranchAddress("jun16_ccd_avgIntensity", &jun16_ccd_avgIntensity, &b_jun16_ccd_avgIntensity);
	fChain_ccd->SetBranchAddress("aug16_ccd_avgIntensity", &aug16_ccd_avgIntensity, &b_aug16_ccd_avgIntensity);
	fChain_ccd->SetBranchAddress("sep16_ccd_avgIntensity", &sep16_ccd_avgIntensity, &b_sep16_ccd_avgIntensity);
	fChain_ccd->SetBranchAddress("oct16_ccd_avgIntensity", &oct16_ccd_avgIntensity, &b_oct16_ccd_avgIntensity);
	fChain_ccd->SetBranchAddress("nov16_ccd_avgIntensity", &nov16_ccd_avgIntensity, &b_nov16_ccd_avgIntensity);
	fChain_ccd->SetBranchAddress("jan17_ccd_avgIntensity", &jan17_ccd_avgIntensity, &b_jan17_ccd_avgIntensity);
	
   Notify();
}

Bool_t BranchAddress::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void BranchAddress::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t BranchAddress::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef BranchAddress_cxx
