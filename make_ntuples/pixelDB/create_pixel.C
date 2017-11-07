#include "Riostream.h"
#include <iostream>

bool pairCompare(const std::pair<int, int>& firstElem, const std::pair<int, int>& secondElem) {
  return firstElem.first < secondElem.first;
}

void create_pixel() {
  TString dir = gSystem->UnixPathName(__FILE__);
  dir.ReplaceAll("create_pixel.C","");
  dir.ReplaceAll("/./","/");
  ifstream in;
  in.open(Form("%spixel.txt",dir.Data()));

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
	
  std::string fullName;
  int row_num;
  int col_num;
  std::string imageName_again;
  int may16_intensity;
  int may16_diffFromAvg;
  int jun16_intensity;
  int jun16_diffFromAvg;
  int aug16_intensity;
  int aug16_diffFromAvg;
  int sep16_intensity;
  int sep16_diffFromAvg;
  int oct16_intensity;
  int oct16_diffFromAvg;
  int nov16_intensity;
  int nov16_diffFromAvg;
  int jan17_intensity;
  int jan17_diffFromAvg;
  int mar17_intensity;
  int mar17_diffFromAvg;
  int may17_intensity;
  int may17_diffFromAvg;
  int jun17a_intensity;
  int jun17a_diffFromAvg;
  int jun17b_intensity;
  int jun17b_diffFromAvg;
  int jul17_intensity;
  int jul17_diffFromAvg;
	
  int high_avgIntensity;
  int low_avgIntensity;
  int high_avgIntensity_index;   
  int low_avgIntensity_index;
  int high_diffFromAvg;
  int low_diffFromAvg;
  int high_diffFromAvg_index;
  int low_diffFromAvg_index;

   
  Int_t nlines = 0;
  TFile *f = new TFile("pixel.root","RECREATE");
  TTree T("T", "tree");

  T.Branch("imageName", &imageName);
  T.Branch("aramysName", &aramysName);
  T.Branch("x", &x);
  T.Branch("y", &y);
  T.Branch("z", &z);
  T.Branch("r", &r);
  T.Branch("may16_avgIntensity", &may16_avgIntensity);
  T.Branch("jun16_avgIntensity", &jun16_avgIntensity);
  T.Branch("aug16_avgIntensity", &aug16_avgIntensity);
  T.Branch("sep16_avgIntensity", &sep16_avgIntensity);
  T.Branch("oct16_avgIntensity", &oct16_avgIntensity);
  T.Branch("nov16_avgIntensity", &nov16_avgIntensity);
  T.Branch("jan17_avgIntensity", &jan17_avgIntensity);
  T.Branch("mar17_avgIntensity", &mar17_avgIntensity);
  T.Branch("may17_avgIntensity", &may17_avgIntensity);
  T.Branch("jun17a_avgIntensity", &jun17a_avgIntensity);
  T.Branch("jun17b_avgIntensity", &jun17b_avgIntensity);
  T.Branch("jul17_avgIntensity", &jul17_avgIntensity);
	
  T.Branch("fullName", &fullName);
  T.Branch("row_num", &row_num);
  T.Branch("col_num", &col_num);
  T.Branch("imageName", &imageName_again);
  T.Branch("may16_intensity", &may16_intensity);
  T.Branch("may16_diffFromAvg", &may16_diffFromAvg);
  T.Branch("jun16_intensity", &jun16_intensity);
  T.Branch("jun16_diffFromAvg", &jun16_diffFromAvg);
  T.Branch("aug16_intensity", &aug16_intensity);
  T.Branch("aug16_diffFromAvg", &aug16_diffFromAvg);
  T.Branch("sep16_intensity", &sep16_intensity);
  T.Branch("sep16_diffFromAvg", &sep16_diffFromAvg);
  T.Branch("oct16_intensity", &oct16_intensity);
  T.Branch("oct16_diffFromAvg", &oct16_diffFromAvg);
  T.Branch("nov16_intensity", &nov16_intensity);
  T.Branch("nov16_diffFromAvg", &nov16_diffFromAvg);
  T.Branch("jan17_intensity", &jan17_intensity);
  T.Branch("jan17_diffFromAvg", &jan17_diffFromAvg);
  T.Branch("mar17_intensity", &mar17_intensity);
  T.Branch("mar17_diffFromAvg", &mar17_diffFromAvg);
  T.Branch("may17_intensity", &may17_intensity);
  T.Branch("may17_diffFromAvg", &may17_diffFromAvg);
  T.Branch("jun17a_intensity", &jun17a_intensity);
  T.Branch("jun17a_diffFromAvg", &jun17a_diffFromAvg);
  T.Branch("jun17b_intensity", &jun17b_intensity);
  T.Branch("jun17b_diffFromAvg", &jun17b_diffFromAvg);	
  T.Branch("jul17_intensity", &jul17_intensity);
  T.Branch("jul17_diffFromAvg", &jul17_diffFromAvg);
	
  T.Branch("high_avgIntensity", &high_avgIntensity);
  T.Branch("low_avgIntensity", &low_avgIntensity);
  T.Branch("high_avgIntensity_index", &high_avgIntensity_index);
  T.Branch("low_avgIntensity_index", &low_avgIntensity_index);
  T.Branch("high_diffFromAvg", &high_diffFromAvg);
  T.Branch("low_diffFromAvg", &low_diffFromAvg);
  T.Branch("high_diffFromAvg_index", &high_diffFromAvg_index);
  T.Branch("low_diffFromAvg_index", &low_diffFromAvg_index);

  std::vector< std::pair< int, int > > v_avgIntensity;
  std::vector< std::pair< int, int > > v_diffFromAvg;
     
  while (1) {

    in >> imageName >> aramysName >> x >> y >> z >> r >> may16_avgIntensity >> jun16_avgIntensity >> aug16_avgIntensity >> sep16_avgIntensity >> oct16_avgIntensity  >> nov16_avgIntensity >> jan17_avgIntensity >> mar17_avgIntensity >> may17_avgIntensity >> jun17a_avgIntensity >> jun17b_avgIntensity >> jul17_avgIntensity >> fullName >> row_num >> col_num >> imageName_again >> may16_intensity >> may16_diffFromAvg >> jun16_intensity >> jun16_diffFromAvg >> aug16_intensity >> aug16_diffFromAvg >> sep16_intensity >> sep16_diffFromAvg >> oct16_intensity >> oct16_diffFromAvg >> nov16_intensity >> nov16_diffFromAvg >> jan17_intensity >> jan17_diffFromAvg >> mar17_intensity >> mar17_diffFromAvg >> may17_intensity >> may17_diffFromAvg >> jun17a_intensity >> jun17a_diffFromAvg >> jun17b_intensity >> jun17b_diffFromAvg >> jul17_intensity >> jul17_diffFromAvg;
		 
    bool isgood = true;
    if ((may16_avgIntensity == -999 || may16_intensity == -999 || may16_diffFromAvg == -999) ||
				(jun16_avgIntensity == -999 || jun16_intensity == -999 || jun16_diffFromAvg == -999) ||
				(aug16_avgIntensity == -999 || aug16_intensity == -999 || aug16_diffFromAvg == -999) ||
				(sep16_avgIntensity == -999 || sep16_intensity == -999 || sep16_diffFromAvg == -999) ||
				(nov16_avgIntensity == -999 || nov16_intensity == -999 || nov16_diffFromAvg == -999) ||
				(oct16_avgIntensity == -999 || oct16_intensity == -999 || oct16_diffFromAvg == -999) ||
				(nov16_avgIntensity == -999 || nov16_intensity == -999 || nov16_diffFromAvg == -999) ||
				(jan17_avgIntensity == -999 || jan17_intensity == -999 || jan17_diffFromAvg == -999) ||
				(mar17_avgIntensity == -999 || mar17_intensity == -999 || mar17_diffFromAvg == -999) ||
				(may17_avgIntensity == -999 || may17_intensity == -999 || may17_diffFromAvg == -999) ||
				(jun17a_avgIntensity == -999 || jun17a_intensity == -999 || jun17a_diffFromAvg == -999) ||
				(jun17b_avgIntensity == -999 || jun17b_intensity == -999 || jun17b_diffFromAvg == -999) ||
				(jul17_avgIntensity == -999 || jul17_intensity == -999 || jul17_diffFromAvg == -999))
      isgood = false;
		 
		 
    if (isgood){
      high_avgIntensity = -999;
      low_avgIntensity = -999;
      high_avgIntensity_index = -999;   
      low_avgIntensity_index = -999; 
     
      high_diffFromAvg = -999;   
      low_diffFromAvg = -999;   
      high_diffFromAvg_index = -999;   
      low_diffFromAvg_index = -999;
     
      v_avgIntensity.clear();
      v_diffFromAvg.clear();

      int ind = 1;
      v_avgIntensity.push_back(std::make_pair(may16_avgIntensity, ind)); ind++; //index for may16 = 1
      v_avgIntensity.push_back(std::make_pair(jun16_avgIntensity, ind)); ind++;
      v_avgIntensity.push_back(std::make_pair(aug16_avgIntensity, ind)); ind++;
      v_avgIntensity.push_back(std::make_pair(sep16_avgIntensity, ind)); ind++;
      v_avgIntensity.push_back(std::make_pair(oct16_avgIntensity, ind)); ind++;
      v_avgIntensity.push_back(std::make_pair(nov16_avgIntensity, ind)); ind++;
      v_avgIntensity.push_back(std::make_pair(jan17_avgIntensity, ind)); ind++;
      v_avgIntensity.push_back(std::make_pair(mar17_avgIntensity, ind)); ind++;
      v_avgIntensity.push_back(std::make_pair(may17_avgIntensity, ind)); ind++;
      v_avgIntensity.push_back(std::make_pair(jun17a_avgIntensity, ind)); ind++;
      v_avgIntensity.push_back(std::make_pair(jun17b_avgIntensity, ind)); ind++;
      v_avgIntensity.push_back(std::make_pair(jul17_avgIntensity, ind)); //index for jul17 = 12
			
      ind = 1;
      v_diffFromAvg.push_back(std::make_pair(may16_diffFromAvg, ind)); ind++; //index for may16 = 1
      v_diffFromAvg.push_back(std::make_pair(jun16_diffFromAvg, ind)); ind++;
      v_diffFromAvg.push_back(std::make_pair(aug16_diffFromAvg, ind)); ind++;
      v_diffFromAvg.push_back(std::make_pair(sep16_diffFromAvg, ind)); ind++;
      v_diffFromAvg.push_back(std::make_pair(oct16_diffFromAvg, ind)); ind++;
      v_diffFromAvg.push_back(std::make_pair(nov16_diffFromAvg, ind)); ind++;
      v_diffFromAvg.push_back(std::make_pair(jan17_diffFromAvg, ind)); ind++;
      v_diffFromAvg.push_back(std::make_pair(mar17_diffFromAvg, ind)); ind++;
      v_diffFromAvg.push_back(std::make_pair(may17_diffFromAvg, ind)); ind++;
      v_diffFromAvg.push_back(std::make_pair(jun17a_diffFromAvg, ind)); ind++;
      v_diffFromAvg.push_back(std::make_pair(jun17b_diffFromAvg, ind)); ind++;
      v_diffFromAvg.push_back(std::make_pair(jul17_diffFromAvg, ind)); //index for jul17 = 12
		 
      std::stable_sort(v_avgIntensity.begin(), v_avgIntensity.end(), pairCompare);
      std::stable_sort(v_diffFromAvg.begin(), v_diffFromAvg.end(), pairCompare);

      high_avgIntensity = v_avgIntensity[ind-1].first; //last entry after sort
      high_avgIntensity_index = v_avgIntensity[ind-1].second;
      low_avgIntensity = v_avgIntensity[0].first; // first entry after sort
      low_avgIntensity_index = v_avgIntensity[0].second;

      high_diffFromAvg = v_diffFromAvg[ind-1].first;
      high_diffFromAvg_index = v_diffFromAvg[ind-1].second;
      low_diffFromAvg = v_diffFromAvg[0].first;
      low_diffFromAvg_index = v_diffFromAvg[0].second;
    }
     
    if (!in.good()) break;
    if (nlines < 5)
      std::cout << "ImageName: " << imageName << std::endl;
		
    T.Fill();
    nlines++;
  }

  in.close();
  f->Write();
}

