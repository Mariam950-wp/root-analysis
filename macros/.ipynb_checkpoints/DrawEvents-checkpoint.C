
void DrawEvents(){

    TCanvas *cThetaVSPhi = new TCanvas("cDeltaE", "cDeltaE", 0, 0, 1000, 1000);     
    hThetaVSPhi->SetXTitle("theta_lab");
    hThetaVSPhi->SetYTitle("phi_lab");
    hThetaVSPhi->SetFillColor(kBlue);
    hThetaVSPhi->Draw("colz");


}