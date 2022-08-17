
// m.abuladze@fz-juelich.de
//
//

TCanvas *cDeltaE;

void DrawDeltaE() {

    // check if histos exist
    if( !hDESC[0] ) {
        cout <<"\n * * * Please analyse file first * * * \n" << endl; 
        return;
        }

    cDeltaE = new TCanvas("cDeltaE", "cDeltaE", 0, 0, 1000, 1000);
    
    cDeltaE->Divide(3, 3);

    cDeltaE->cd(2); // up
    cDeltaE->GetPad(2)->SetLogy();
    hDESC[2]->GetXaxis()->SetRangeUser(-10, 200);
    hDESC[2]->SetFillColor(kBlue);
    hDESC[2]->Draw();

    cDeltaE->cd(4); // right
    cDeltaE->GetPad(4)->SetLogy();
    hDESC[1]->GetXaxis()->SetRangeUser(-10, 200);
    hDESC[1]->SetFillColor(kBlue);
    hDESC[1]->Draw();

    cDeltaE->cd(6); // left
    cDeltaE->GetPad(6)->SetLogy();
    hDESC[0]->GetXaxis()->SetRangeUser(-10, 200);
    hDESC[0]->SetFillColor(kBlue);
    hDESC[0]->Draw();

    cDeltaE->cd(8); // down
    cDeltaE->GetPad(8)->SetLogy();
    hDESC[3]->GetXaxis()->SetRangeUser(-10, 200);
    hDESC[3]->SetFillColor(kBlue);
    hDESC[3]->Draw();
}
