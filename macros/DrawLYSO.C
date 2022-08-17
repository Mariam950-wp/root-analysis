
// m.abuladze@fz-juelich.de
//
//

// canvases
TCanvas *cLeft, *cRight, *cUp, *cDown, *cCorners;

// ----------------------------------------------------------------------------
void DrawLeft(){
  for(int i = 0; i <12; i++){
      cLeft->cd(i+1);
      cLeft->GetPad(i+1)->SetLogy();
      hLYSO[Ls+i]->SetFillColor(kCyan+2);
      hLYSO[Ls+i]->Draw();

      
    /*  fFitFun[Ls+i]->Draw("same");
      fPol0[Ls+i]->Draw("same");
      fGaus[Ls+i]->Draw("same");
    */
  }
}

// ----------------------------------------------------------------------------
void DrawRight(){
  for(int i = 0; i <12; i++){
      cRight->cd(i+1);
      cRight->GetPad(i+1)->SetLogy();
      hLYSO[Rs+i]->SetFillColor(kCyan+2); 
      hLYSO[Rs+i]->Draw();
  }
}

// ----------------------------------------------------------------------------
void DrawUps(){
  for(int i = 0; i <12; i++){
      cUp->cd(i+1);
      cUp->GetPad(i+1)->SetLogy();
      hLYSO[Us+i]->SetFillColor(kRed-3);
      hLYSO[Us+i]->Draw();
  }
}

// ----------------------------------------------------------------------------
void DrawDown(){
  for(int i = 0; i <12; i++){
      cDown->cd(i+1);
      cDown->GetPad(i+1)->SetLogy();
      hLYSO[Ds+i]->SetFillColor(kRed-3);
      hLYSO[Ds+i]->Draw();
  }
}

// ----------------------------------------------------------------------------
void DrawCorners(){
  for(int i = 0; i <4; i++){
      cCorners->cd(i+1);
      cCorners->GetPad(i+1)->SetLogy();
      hLYSO[Crns+i]->SetFillColor(kGreen+3);
      hLYSO[Crns+i]->Draw();
  }
}

// ----------------------------------------------------------------------------
void DrawLYSO() {

  // check if histos exist
  if( !hLYSO[0] ) {
      cout <<"\n * * * Pleas run analysis * * * \n" << endl; 
      return;
      }

  // screen parameters
  Double_t MenuY = 56;
  Double_t MonX = 1680;
  Double_t MonY = 1080-MenuY;

  // initialisation of canvases
  cLeft = new TCanvas("cLeft", "Left",          0./11*MonX, 4./11*MonY, 4./11*MonX, 3./11*MonY);
  cLeft->Divide(4, 3, .001, .001);
  cRight = new TCanvas("cRight", "Right",       7./11*MonX, 4./11*MonY, 4./11*MonX, 3./11*MonY);
  cRight->Divide(4, 3, .001, .001);

  cDown = new TCanvas("cDown", "Down",          4./11*MonX, 7./11*MonY, 3./11*MonX, 4./11*MonY);
  cDown->Divide(3, 4, .001, .001);
  cCorners = new TCanvas("cCorners", "Corners", 4./11*MonX, 4./11*MonY, 3./11*MonX, 3./11*MonY);
  cCorners->Divide(2, 2, .001, .001);
  cUp = new TCanvas("cUp", "Up",                4./11*MonX, 0./11*MonX, 3./11*MonX, 4./11*MonY);
  cUp->Divide(3, 4, .001, .001);

  // drawing histograms of different sides (U, D, R, L, Corner)
  DrawLeft();
  DrawRight();
  DrawDown();
  DrawCorners();
  DrawUps();
}
