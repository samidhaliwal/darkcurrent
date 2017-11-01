
void setstyle() {

  // For the canvas:
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetCanvasDefH(300); //Height of canvas
  gStyle->SetCanvasDefW(600); //Width of canvas
  gStyle->SetCanvasDefX(0);   //POsition on screen
  gStyle->SetCanvasDefY(0);

  // For the Pad:
  gStyle->SetPadBorderMode(0);
  // gStyle->SetPadBorderSize(Width_t size = 1);
  gStyle->SetPadColor(kWhite);
  gStyle->SetPadGridX(false);
  gStyle->SetPadGridY(false);
  gStyle->SetGridColor(0);
  gStyle->SetGridStyle(3);
  gStyle->SetGridWidth(1);

  // For the frame:
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameBorderSize(1);
  gStyle->SetFrameFillColor(0);
  gStyle->SetFrameFillStyle(0);
  gStyle->SetFrameLineColor(1);
  gStyle->SetFrameLineStyle(1);
  gStyle->SetFrameLineWidth(1);

  // set the paper & margin sizes
  gStyle->SetPaperSize(20,26);
  gStyle->SetPadTopMargin(0.065);
  gStyle->SetPadRightMargin(0.065);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);

  // use large Times-Roman fonts
  gStyle->SetTitleFont(42,"xyz");  // set the all 3 axes title font
  gStyle->SetTitleFont(42," ");    // set the pad title font
  gStyle->SetTitleSize(0.05,"xyz"); // set the 3 axes title size
  gStyle->SetTitleSize(0.05," ");   // set the pad title size
  gStyle->SetLabelFont(42,"xyz");
  gStyle->SetLabelSize(0.04,"xyz");
  gStyle->SetLabelColor(1,"xyz");
  gStyle->SetTextFont(42);
  gStyle->SetTextSize(0.05);
  gStyle->SetStatFont(42);

  // use bold lines and markers
  gStyle->SetMarkerStyle(8);
  gStyle->SetHistLineWidth(1.85);
  gStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  //..Get rid of X error bars
  gStyle->SetErrorX(0.001);

  // do not display any of the standard histogram decorations
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(11111111);

  // put tick marks on top and RHS of plots
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(0);


 
  /*
  const Int_t NRGBs = 5;
  const Int_t NCont = 100;
  Double_t stops[NRGBs] = { 0.00, 0.54, 1.00, 1.00, 1.00 };
  Double_t red[NRGBs]   = { 0.71, 0.70, 0.17, 1.00, 1.00 };
  Double_t green[NRGBs] = { 0.70, 0.81, 0.10, 0.20, 1.00 };
  Double_t blue[NRGBs]  = { 0.80, 1.00, 0.12, 0.00, 0.90 };

  double mr[NRGBs],mg[NRGBs],mb[NRGBs];
  for(int i = 0; i < NRGBs; i++){
    mr[i] = red[NRGBs-1-i];
    mg[i] = green[NRGBs-1-i];
    mb[i] = blue[NRGBs-1-i];
  }
  TColor::CreateGradientColorTable(NRGBs, stops, mr, mg, mb, NCont);
 //gStyle->SetNumberContours(NCont);
 */
  
/*
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  //Double_t stops[NRGBs] = { 0.5, 0.65, 0.7, 0.85, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);
*/
	/*
	const Int_t NRGBs = 5;
	const Int_t NCont = 255;
	Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
	//Double_t stops[NRGBs] = { 0.5, 0.65, 0.7, 0.85, 1.00 };
	Double_t red[NRGBs]   = { 1.0, 1.0, 0.37, 0.12, 0.098 };
	Double_t green[NRGBs] = { 1.0, 0.84, 0.62, 0.56, 0.098 };
	Double_t blue[NRGBs]  = { 0.88, 0.0, 0.63, 1.00, 0.439 };
	 */
/*
	Double_t red[NRGBs]   = { 0.51, 1.00, 0.87, 0.00, 0.01 };
	Double_t green[NRGBs] = { 0.00, 0.20, 1.00, 0.81, 0.00 };
	Double_t blue[NRGBs]  = { 0.00, 0.00, 0.12, 1.00, 0.51 };
 */
	/*
	TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
	gStyle->SetNumberContours(NCont);
*/
	

    /*
  const Int_t NRGBs = 11;
  const Int_t NCont = 255;
  
  Double_t stops[NRGBs] = { 0.00, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
  Double_t red[5]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[5] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[5]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);
  */

/*
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  
  // Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t stops[NRGBs] = { 0.5, 0.65, 0.7, 0.85, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.25, 0.5, 0.75, 1.00 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 1.00, 1.00, 1.00, 1.00, 1.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);
*/

  gStyle->SetNumberContours(255);
  //  gStyle->SetPalette(56);
  gStyle->SetPalette(kRainBow);


  gStyle->cd();

}

