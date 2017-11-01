#define Analysis_cxx
#include "Analysis.h"

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <cmath>
#include <vector>

void Analysis::Loop()
{
	bool runFits = false;
	
  if (BranchAddress::fChain == 0) return;

  Long64_t nentries = fChain->GetEntries();
  Long64_t nbytes = 0, nb = 0;
  Long64_t nbytes1 = 0, nb1 = 0;
  Long64_t nentries_ccd = fChain_ccd->GetEntries();
  Long64_t nbytes_ccd = 0, nb_ccd = 0;
  Long64_t nbytes_ccd2 = 0, nb_ccd2 = 0;

  const float GeV = 0.001;
	int count_total = 0;
  int count_nonNull = 0;

  int count_total_cut = 0;
	int count_nonNull_cut = 0;
	
	float sum_total_cut_jun_aboveavg = 0.;
	float sum_nonNull_cut_jun_aboveavg = 0.;

	//if (runFits){
		int count_withinResolution = 0;
		int count_withinResolution_cut = 0;
		float sum_withinResolution_cut_jun_aboveavg = 0.;
	//}

  TFile *out = new TFile("pixel_helperfile.root","RECREATE");
  TTree *tree = new TTree("treeF", "treeF");
  tree->Branch("hasNullEntry", &hasNullEntry);
	
	if (runFits){
	tree->Branch("isWithinResolution", &isWithinResolution);
	tree->Branch("junPredict", &junPredict);
  tree->Branch("janPredict", &novPredict);
  tree->Branch("slope", &slope);
  tree->Branch("slopeerr", &slopeerr);
  tree->Branch("intercept", &intercept);
  tree->Branch("intercepterr", &intercepterr);
	}

  TTree *tree_region = new TTree("tree_region_avg", "treeF_region_avg");
  tree_region->Branch("rregion_count_ccd", &rregion_count_ccd);
  tree_region->Branch("rregion_sum_jun_diffFromAvg", &rregion_sum_jun_diffFromAvg);
  tree_region->Branch("rregion_avg_jun_diffFromAvg", &rregion_avg_jun_diffFromAvg);
  tree_region->Branch("rz", &rz);
  tree_region->Branch("rr", &rr);

	if (runFits){
		res = new TH1F("res", "res", 1100, 10, 100);
		predictplot = new TH1F ("predictplot", "predictplot", 2000, -10., 10.);
		junVal = new TH1F("junVal", "junVal", 1100, 10, 100);
		
		mgr_norm = new TMultiGraph();
		mgr_norm->SetTitle("mgr_norm; day; pixel intensity/ccd avg pixel intensity");
		mgr_diffAvg = new TMultiGraph();
		mgr_diffAvg->SetTitle("mgr_diffAvg; day; pixel intensity difference from avg");
		mgr_FitEnd = new TMultiGraph();
		mgr_diffAvg->SetTitle("mgr_FitEnd; day; pixel intensity difference from avg");
	}
	
  ///----------------------------------------------------------
  ///---------------  F I R S T  L O O P  ---------------------
  ///----------------------------------------------------------
  ///Define regions within which to calculate the average number
  ///pixels. 7 regions divided in z (for particular wheels) and
  ///every 100 mm radial seperation -> this may need to be
  ///increased. radial range is then filled into a vector.
	
  float z_range[7] = {6000., 8000., 10500., 12000., 17000., 20000., 25000.};
  float r_start = 2000.;
  float r_end =  12000.;
  float rincr = 100.;
  std::vector< float > r_range;
  for (float rval = r_start; rval < r_end; rval+=rincr){
    float val = rval;
    r_range.push_back(val);
  }
	
  ///---------------  I N I T  L O O P  ---------------------
  ///Define counter for number of ccds in particular z/r range
  std::vector< std::vector< float > > ccdcount_zr;
  ccdcount_zr.resize(7); //this resize value comes from entries in z_range
  ///Define counter for sum of pixels in particular z/r range	
  std::vector< std::vector< float > > sum_jun_zr;
  sum_jun_zr.resize(7); //this resize value comes from entries in z_range
  ///Define counter for number of average of pixel values
  ///in particular z/r range	
  std::vector< std::vector< float > > avg_zr;
  avg_zr.resize(7);
  for (int z_ind = 0; z_ind < 7; z_ind++){
    ccdcount_zr[z_ind].resize(int(r_range.size()));
    sum_jun_zr[z_ind].resize(int(r_range.size()));
    avg_zr[z_ind].resize(int(r_range.size()));
  }
  
  ///Initialize all counters to 0
  for (int z_ind = 0; z_ind < 7; z_ind++){
    for (int r_ind = 0; r_ind < r_range.size(); r_ind++){

      ccdcount_zr[z_ind][r_ind] = 0.;
      sum_jun_zr[z_ind][r_ind] = 0.;
      avg_zr[z_ind][r_ind] = 0.;
	
    }
  }

  ///---------------  C C D  L O O P  ---------------------
  ///Store count for *number of ccds* in particular z/r range
  ///Loop through ccds, and add count
  for (Long64_t jentry=0; jentry<nentries_ccd;jentry++) {
    Long64_t ientry = LoadTree_ccd(jentry);

    if (ientry < 0) break;
    nb_ccd = fChain_ccd->GetEntry(jentry);
    nbytes_ccd += nb_ccd;
    
    for (int z_ind = 0; z_ind < 6; z_ind++){
      //sum_jun_zr[z_ind].resize(int(r_range.size()));
      for (int r_ind = 0; r_ind < r_range.size()-1; r_ind++){
				if (r_ccd > r_range[r_ind] && r_ccd <= r_range[r_ind+1]
						&& abs(z_ccd) > z_range[z_ind] && abs(z_ccd) <= z_range[z_ind+1]){
					ccdcount_zr[z_ind][r_ind]+=1.;
				}
      }
    }
  }

  //sum_jun_zr.resize(7);
  ///---------------  P I X E L  L O O P  ---------------------
  ///Looping over the *number of pixels*, and
  /// store the total 'diffence from avg' in particular z/r range
  ///count for June -> May want to change this, or add additional
  ///array for each month (line 163 below)
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
		
    if (ientry < 0) break;
    nb1 = fChain->GetEntry(jentry);		nbytes1 += nb1;
		
    for (int z_ind = 0; z_ind < 6; z_ind++){
      for (int r_ind = 0; r_ind < r_range.size()-1; r_ind++){
				if (r > r_range[r_ind] && r <= r_range[r_ind+1]
						&& abs(z) > z_range[z_ind] && abs(z) <= z_range[z_ind+1]){
					sum_jun_zr[z_ind][r_ind] += float(jun16_diffFromAvg);
				}
      }
    }	
  }
	
  ///---------------  CALC AVG  L O O P  ---------------------
  ///Store average values for particular r/z ranges
  rregion_count_ccd = 0.;
  rregion_sum_jun_diffFromAvg = 0.;
  rregion_avg_jun_diffFromAvg = 0.;
  for (int z_ind = 0; z_ind < 6; z_ind++){
    for (int r_ind = 0; r_ind < r_range.size()-1; r_ind++){
			
      if (ccdcount_zr[z_ind][r_ind] != 0){
				avg_zr[z_ind][r_ind] = sum_jun_zr[z_ind][r_ind]/(ccdcount_zr[z_ind][r_ind]*324*323);
      }else{
				avg_zr[z_ind][r_ind] = 0.;
      }
      //std::cout << "avg: " << avg_zr[z_ind][r_ind] << std::endl;
      rregion_count_ccd = ccdcount_zr[z_ind][r_ind];
      rregion_sum_jun_diffFromAvg = sum_jun_zr[z_ind][r_ind];
      rregion_avg_jun_diffFromAvg = avg_zr[z_ind][r_ind];
      rr = r_range[r_ind] + rincr/2.; //center value
      float rztempadd = z_range[z_ind+1] - z_range[z_ind];
      rz = z_range[z_ind]+rztempadd;
      tree_region->Fill();

    }
  }

  ///----------------------------------------------------------
  ///----------  S E C O N D  P I X E L  L O O P  -------------
  ///----------------------------------------------------------
  ///Looping over pixels
	
	//if (runFits){ //barfs if this is within restriction
		const int nmonths = 11;
		float y_FitEnd[11];
		float y_diffAvg[11];
		float y_norm[11];
		float x_month[11] = {0, 42, 74, 117, 146, 179, 253, 306, 348, 390, 391};
	//}
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);

    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;

    count_total++;

    ///Null entries in months
    hasNullEntry = false;
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
				(jun17b_avgIntensity == -999 || jun17b_intensity == -999 || jun17b_diffFromAvg == -999))
				//(jul17_avgIntensity == -999 || jul17_intensity == -999 || jul17_diffFromAvg == -999))
      hasNullEntry = true;
		
    if (!hasNullEntry)
      count_nonNull++;
		
		if (runFits){
			float month_intensity[nmonths] = {float(may16_intensity),
						float(jun16_intensity),
						float(aug16_intensity),
						float(sep16_intensity),
						float(oct16_intensity),
						float(nov16_intensity),
						float(jan17_intensity),
						float(mar17_intensity),
						float(may17_intensity),
						float(jun17a_intensity),
						float(jun17b_intensity)
			};
			
			float month_diffFromAvg[nmonths] = {float(may16_diffFromAvg),
						float(jun16_diffFromAvg),
						float(aug16_diffFromAvg),
						float(sep16_diffFromAvg),
						float(oct16_diffFromAvg),
						float(nov16_diffFromAvg),
						float(jan17_diffFromAvg),
						float(mar17_diffFromAvg),
						float(may17_diffFromAvg),
						float(jun17a_diffFromAvg),
						float(jun17b_diffFromAvg)
			};
			
			float month_avgIntensity[nmonths] = {float(may16_avgIntensity),
						 float(jun16_avgIntensity),
						 float(aug16_avgIntensity),
						 float(sep16_avgIntensity),
						 float(oct16_avgIntensity),
						 float(nov16_avgIntensity),
						 float(jan17_avgIntensity),
						 float(mar17_avgIntensity),
						 float(may17_avgIntensity),
						 float(jun17a_avgIntensity),
						 float(jun17b_avgIntensity)
			};
			
			for (int i = 0; i < nmonths; i++)
				{
					y_norm[i] = month_intensity[i]/month_avgIntensity[i];
					y_diffAvg[i] = month_diffFromAvg[i];
					y_FitEnd[i] =  month_diffFromAvg[i];
				}

			gr_FitEnd[jentry] = new TGraph (11, x_month, y_FitEnd);
			TF1 *ffit = new TF1("ffit", "[0]*x + [1]", 50, 200);
			gr_FitEnd[jentry]->Fit("ffit", "F", "",  50, 200);
			mgr_FitEnd->Add(gr_FitEnd[jentry], "AL*");
			
			double resval = ffit->Eval(42,0,0);
			junPredict = resval;
			novPredict = ffit->Eval(252,0,0);
			slope = ffit->GetParameter(0);
			slopeerr = ffit->GetParError(0);
			intercept = ffit->GetParameter(1);
			intercepterr = ffit->GetParError(1);
			res->Fill(resval);
			junVal->Fill(jun16_diffFromAvg);
			std::cout << "resval: " << resval << " and Junval: " << jun16_diffFromAvg << std::endl;
			predictplot->Fill(resval/jun16_diffFromAvg);
			
			isWithinResolution = true;
			if (resval < 0.8*jun16_diffFromAvg || resval > 1.2*jun16_diffFromAvg ){
				isWithinResolution = false;

			}
			
			if (isWithinResolution)
				count_withinResolution++;
		}// end if (runFits)

		
    //Only looking at ccds closes to IP here   
    if (abs(z) < 8000 && abs(r) < 3000){
      count_total_cut++;
      sum_total_cut_jun_aboveavg += float(jun16_diffFromAvg);
			
			if (!hasNullEntry){
				count_nonNull_cut++;
				sum_nonNull_cut_jun_aboveavg += float(jun16_diffFromAvg);
			}
			
			if (runFits){
				if (isWithinResolution){
					count_withinResolution_cut++;
					sum_withinResolution_cut_jun_aboveavg += float(jun16_diffFromAvg);
				}
			}
			
    }

		if (runFits){
			gr_norm[jentry] = new TGraph (11, x_month, y_norm);
			mgr_norm->Add(gr_norm[jentry], "AL*");
			gr_diffAvg[jentry] = new TGraph (11, x_month, y_diffAvg);
			mgr_diffAvg->Add(gr_diffAvg[jentry], "AL*");
		}
    tree->Fill();
		
		
  }//End entry Loop
//  delete V;

	if (runFits){
		mgr_norm->Write();
		mgr_diffAvg->Write();
		mgr_FitEnd->Write();
		res->Write();
		predictplot->Write();
		junVal->Write();
	}
	
  tree->Write();
  tree_region->Write();
  out->Close();
	
  std::cout << "Total pixel count (including null entries): " << count_total << std::endl;
  std::cout << "non-Null pixel count: " << count_nonNull << std::endl;
	if (runFits)
			std::cout << "Within resolution pixel count: " << count_withinResolution << std::endl;
	std::cout << "Total pixel count (including null entries) with cuts: " << count_total_cut << std::endl;
	std::cout << "non-Null pixel count with cuts: " << count_nonNull_cut << std::endl;
	if (runFits)
		std::cout << "Within resolution pixel count with cuts: " << count_withinResolution_cut << std::endl;
  std::cout << "Sum of total pixels above avg in June: " << sum_total_cut_jun_aboveavg << std::endl;
  std::cout << "non-Null sum of total pixels above avg in June: " << sum_nonNull_cut_jun_aboveavg << std::endl;
	if (runFits)
			std::cout << "Within resolution and nonNull sum of total pixels above avg in June: " << sum_withinResolution_cut_jun_aboveavg << std::endl;

	
}//End Loop function

