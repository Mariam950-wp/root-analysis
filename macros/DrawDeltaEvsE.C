
// m.abuladze@fz-juelich.de
//
//

// canvases
TCanvas *cLeft2D, *cRight2D, *cUp2D, *cDown2D;

//=============================================================================
void DrawLeft2D(){
  for(int i = 0; i <12; i++){
      cLeft2D->cd(i+1);
      hdEvsE[Ls+i]->SetFillColor(kCyan+2);
      hdEvsE[Ls+i]->Draw("colz");
  }
}

//=============================================================================
void DrawRight2D(){
  for(int i = 0; i <12; i++){
      cRight2D->cd(i+1);
      hdEvsE[Rs+i]->SetFillColor(kCyan+2);
      hdEvsE[Rs+i]->Draw("colz");
  }
}

//=============================================================================
void DrawUps2D(){
  for(int i = 0; i <12; i++){
      cUp2D->cd(i+1);
      hdEvsE[Us+i]->SetFillColor(kRed-3);
      hdEvsE[Us+i]->Draw("colz");
  }
}

//=============================================================================
void DrawDown2D(){
  for(int i = 0; i <12; i++){
      cDown2D->cd(i+1);
      hdEvsE[Ds+i]->SetFillColor(kRed-3);
      hdEvsE[Ds+i]->Draw("colz");
  }
}

//=============================================================================
//=============================================================================
void DrawDeltaEvsE() {

  // check if histos exist
  if( !hdEvsE[0] ) {
    cout <<"\n * * * Pleas run analysis * * * \n" << endl; 
    return;
    }

    // screen parameters
  Double_t MenuY = 56;
  Double_t MonX = 1680;
  Double_t MonY = 1080-MenuY;

  // initialisation of canvases
  cLeft2D = new TCanvas("cLeft2D", "Left",          0./11*MonX, 4./11*MonY, 4./11*MonX, 3./11*MonY);
  cLeft2D->Divide(4, 3, .001, .001);

  cRight2D = new TCanvas("cRight2D", "Right",       7./11*MonX, 4./11*MonY, 4./11*MonX, 3./11*MonY);
  cRight2D->Divide(4, 3, .001, .001);

  cDown2D = new TCanvas("cDown2D", "Down",          4./11*MonX, 7./11*MonY, 3./11*MonX, 4./11*MonY);
  cDown2D->Divide(3, 4, .001, .001);

  cUp2D = new TCanvas("cUp2D", "Up",                4./11*MonX, 0./11*MonX, 3./11*MonX, 4./11*MonY);
  cUp2D->Divide(3, 4, .001, .001);

  // drawing histograms of different sides (U, D, R, L, Corner)
  DrawLeft2D();
  DrawRight2D();
  DrawDown2D();
  DrawUps2D();
}