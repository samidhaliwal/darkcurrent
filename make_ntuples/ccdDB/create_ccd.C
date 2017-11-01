#include "Riostream.h"
#include <iostream>
void create_ccd() {

  // read file $ROOTSYS/tutorials/tree/basic.dat
  // this file has 3 columns of float data
  TString dir = gSystem->UnixPathName(__FILE__);
  dir.ReplaceAll("create_ccd.C","");
  dir.ReplaceAll("/./","/");
  ifstream in;
  in.open(Form("%sccd.txt",dir.Data()));

  std::string imageName;
  std::string aramysName;
  float x;
  float y;
  float z;
  float r;
  int may16_avgIntensity;
  int jun16_avgIntensity;
  int aug16_avgIntensity;
  int sep16_avgIntensity;
  int oct16_avgIntensity;
  int nov16_avgIntensity;
  int jan17_avgIntensity;
  int mar17_avgIntensity;
  int may17_avgIntensity;
  int jun17a_avgIntensity;
  int jun17b_avgIntensity;
  int jul17_avgIntensity;
  int aug17_avgIntensity;
	
  Int_t nlines = 0;
  int goodcount = 0;

  TFile *f = new TFile("ccd.root","RECREATE");
  TTree T("T_ccd", "tree");

  T.Branch("imageName_ccd", &imageName);
  T.Branch("aramysName_ccd", &aramysName);
  T.Branch("x_ccd", &x);
  T.Branch("y_ccd", &y);
  T.Branch("z_ccd", &z);
  T.Branch("r_ccd", &r);
  T.Branch("may16_ccd_avgIntensity", &may16_avgIntensity);
  T.Branch("jun16_ccd_avgIntensity", &jun16_avgIntensity);
  T.Branch("aug16_ccd_avgIntensity", &aug16_avgIntensity);
  T.Branch("sep16_ccd_avgIntensity", &sep16_avgIntensity);
  T.Branch("oct16_ccd_avgIntensity", &oct16_avgIntensity);
  T.Branch("nov16_ccd_avgIntensity", &nov16_avgIntensity);
  T.Branch("jan17_ccd_avgIntensity", &jan17_avgIntensity);
  T.Branch("mar17_ccd_avgIntensity", &mar17_avgIntensity);
  T.Branch("may17_ccd_avgIntensity", &may17_avgIntensity);
  T.Branch("jun17a_ccd_avgIntensity", &jun17a_avgIntensity);
  T.Branch("jun17b_ccd_avgIntensity", &jun17b_avgIntensity);
  T.Branch("jul17_ccd_avgIntensity", &jul17_avgIntensity);
  T.Branch("aug17_ccd_avgIntensity", &aug17_avgIntensity);

  while (1) {

    in >> imageName >> aramysName >> x >> y >> z >> r >> may16_avgIntensity >> jun16_avgIntensity >> aug16_avgIntensity >> sep16_avgIntensity >> oct16_avgIntensity >> nov16_avgIntensity >> jan17_avgIntensity >> mar17_avgIntensity >> may17_avgIntensity >> jun17a_avgIntensity >> jun17b_avgIntensity >> jul17_avgIntensity >> aug17_avgIntensity;

    std::cout << " " << imageName <<  " " <<aramysName <<  " " <<x <<  " " <<y <<  " " <<z <<  " " <<r << std::endl;		 
     
    if (!in.good()) break;
    T.Fill();
		 
    if (sep16_avgIntensity != -999) //Keeping track of all those NULLs
      goodcount++;
		 
    nlines++;

  }

  std::cout << "num total: " << nlines << std::endl;
  std::cout << "good total: " << goodcount << std::endl;
	
  in.close();

  f->Write();
}
