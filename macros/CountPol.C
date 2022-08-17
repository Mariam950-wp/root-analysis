//
// 
//

Double_t IntegLeft[NofCryInArms];
Double_t IntegRight[NofCryInArms];
Double_t IntegUp[NofCryInArms];
Double_t IntegDown[NofCryInArms];

TH1D    *h_FirstRow; 
TH1D    *h_SecondRow;
TH1D    *h_ThirdRow;

TH1D    *h_FirstColumn;
TH1D    *h_SecondColumn;
TH1D    *h_ThirdColumn;

TH1D    *h_AsymmetryLR;
TH1D    *h_AsymmetryUD;

TCanvas* Asymetry;

// thresholds
Double_t low = 200;
Double_t high = 300;

//-----------------------------------------------------------------------------
void InitHistos() {
    // histograms to store infromation about right and left crystals
    h_FirstRow = new  TH1D( "h_FirstRow", "", 11, -5, 5);   // 8 crystals: 4 from first row of left and 4 of rignt
    h_SecondRow = new TH1D("h_SecondRow", "", 11, -5, 5);   // 8 crystals: 4 from second row of left and 4 rignt
    h_ThirdRow = new  TH1D( "h_ThirdRow", "", 11, -5, 5);   // 8 crystals: 4 from third row of left and 4 of rignt

    // histograms to store information about Up and Down crystals
    h_FirstColumn = new  TH1D("h_FirstColumn",  "", 11, -5, 5); // 8 crystals: 4 from first column of up and 4 of down
    h_SecondColumn = new TH1D("h_SecondColumn", "", 11, -5, 5); // 8 crystals: 4 from first column of up and 4 of down
    h_ThirdColumn = new  TH1D("h_ThirdColumn",  "", 11, -5, 5); // 8 crystals: 4 from first column of up and 4 of down

    // histograms which will contain information about asymmetry between left-right and up-down crystals
    h_AsymmetryLR = new  TH1D("h_AsymmetryLR",  "(L - R)/(L + R)", 6, -0.5, 5.5);
    h_AsymmetryUD = new  TH1D("h_AsymmetryUD",  "(U - D)/(U + D)", 6, -0.5, 5.5);
}

//-----------------------------------------------------------------------------
void SetThresholds(Double_t thr1, Double_t thr2) {
    low  = thr1;
    high = thr2;
}

//-----------------------------------------------------------------------------
void CountIntegrals(){
    for(int i = 0; i < NofCryInArms; i++){
        IntegLeft[i] = hLYSO[Ls+i]->Integral(low, high);
        IntegRight[i] = hLYSO[Rs+i]->Integral(low, high);
        IntegUp[i] = hLYSO[Us+i]->Integral(low, high);
        IntegDown[i] = hLYSO[Ds+i]->Integral(low, high);
    }
}

//-----------------------------------------------------------------------------
Double_t GetAsymmetry(Double_t DetOne, Double_t DetTwo){
    return (DetOne - DetTwo)/(DetOne + DetTwo);
}

//-----------------------------------------------------------------------------
//  method to count error asymmetry in counting asymmetry of energy deposition
Double_t GetAsymmetryError(Double_t DetOne, Double_t DetTwo){
    if (DetOne < 1 || DetTwo < 1) 
        return 0;
    else 
        return 2.*DetOne*DetTwo/((DetOne + DetTwo) * (DetOne + DetTwo)) * sqrt(1./DetOne + 1./DetTwo);
}

//-----------------------------------------------------------------------------
void FillHistos(){
    h_AsymmetryLR->Reset();
    h_AsymmetryUD->Reset();

    for(int i = 0; i < 4; i++){
        // left's
        h_FirstRow->SetBinContent(i + 2, IntegLeft[i]);
        h_SecondRow->SetBinContent(i + 2, IntegLeft[4 + i]);
        h_ThirdRow->SetBinContent(i + 2, IntegLeft[8 + i]);

        // right's
        h_FirstRow->SetBinContent(7 + i, IntegRight[i]);       
        h_SecondRow->SetBinContent(7 + i, IntegRight[4 + i]);
        h_ThirdRow->SetBinContent(7 + i, IntegRight[8 + i]);

        // fill histogram which shows asymmetry between left and right crystals
        h_AsymmetryLR->AddBinContent(5 - i, GetAsymmetry(IntegLeft[0 + i], IntegRight[3 - i]));
        h_AsymmetryLR->AddBinContent(5 - i, GetAsymmetry(IntegLeft[4 + i], IntegRight[7 - i]));
        h_AsymmetryLR->AddBinContent(5 - i, GetAsymmetry(IntegLeft[8 + i], IntegRight[11 - i]));

        // setting errors to each asymmetry between left and right crystals
        Double_t error = 0;
        for(int k = 0; k < 3; k++){
            error += GetAsymmetryError(IntegLeft[4 * k + i],IntegRight[4 * k + 3 - i]);
        } 
        h_AsymmetryLR->SetBinError(i + 2, error);
    }

    for(int j = 0; j < 4; j++){
        // up's
        h_FirstColumn->SetBinContent( 10 - j,IntegUp[j * 3 + 0]);
        h_SecondColumn->SetBinContent(10 - j,IntegUp[j * 3 + 1]);
        h_ThirdColumn->SetBinContent( 10 - j,IntegUp[j * 3 + 2]);

        // down's
        h_FirstColumn->SetBinContent( 5 - j,IntegDown[j * 3 + 0]);
        h_SecondColumn->SetBinContent(5 - j,IntegDown[j * 3 + 1]);
        h_ThirdColumn->SetBinContent( 5 - j,IntegDown[j * 3 + 2]);

        // fill histogram which shows asymmetry between up and down crystals
        h_AsymmetryUD->AddBinContent(5 - j, GetAsymmetry(IntegUp[j * 3 + 0], IntegDown[(3 - j) * 3 + 0]));
        h_AsymmetryUD->AddBinContent(5 - j, GetAsymmetry(IntegUp[j * 3 + 1], IntegDown[(3 - j) * 3 + 1]));
        h_AsymmetryUD->AddBinContent(5 - j, GetAsymmetry(IntegUp[j * 3 + 2], IntegDown[(3 - j) * 3 + 2]));
    
        // setting errors to each asymmetry between up and down crystals
        Double_t error = 0;
        for(int k = 0; k < 3; k++){
            error += GetAsymmetryError(IntegUp[j * 3 + k],IntegDown[(3 - j) * 3 + k]);
        } 
        h_AsymmetryUD->SetBinError(j + 2, error);
    }
}

//-----------------------------------------------------------------------------
// Drawing all histograms in one canvas
void DrawResults(){
    THStack* hAsymLR = new THStack("hAsymLR", ";Laft - Right;");
    THStack* hAsymUD = new THStack("hAsymUD", ";Up - Down;"); //???

    THStack* hNorAsymLR = new THStack("hNorAsymLR", ";Left - Right;");
    THStack* hNorAsymUD = new THStack("hNorAsymUD", ";   Up - Down;");

    h_FirstRow->SetFillColor(kRed);
    h_SecondRow->SetFillColor(kBlue);
    h_ThirdRow->SetFillColor(kGreen);

    h_FirstColumn->SetFillColor(kRed);
    h_SecondColumn->SetFillColor(kBlue);
    h_ThirdColumn->SetFillColor(kGreen);

    h_AsymmetryLR->SetFillColor(kBlue);
    h_AsymmetryUD->SetFillColor(kBlue);
    
    hAsymLR->Add(h_FirstRow);
    hAsymLR->Add(h_SecondRow);
    hAsymLR->Add(h_ThirdRow);

    hAsymUD->Add(h_FirstColumn);
    hAsymUD->Add(h_SecondColumn);
    hAsymUD->Add(h_ThirdColumn);
    
    Asymetry = new TCanvas("cAsymmetry","stacked hists", 700, 900);
    Asymetry->Divide(2, 2);

    Asymetry->cd(1);
    hAsymLR->Draw();

    Asymetry->cd(2);
    h_AsymmetryLR->GetYaxis()->SetRangeUser(-1, 1);
    h_AsymmetryLR->Draw("E1");

    Asymetry->cd(3);
    hAsymUD->Draw();

    Asymetry->cd(4);
    h_AsymmetryUD->GetYaxis()->SetRangeUser(-1, 1);
    h_AsymmetryUD->Draw("E1");
}

//=============================================================================
void CountPol(){
    InitHistos();       // innitialization of histograms whete asymmetric information will be stored
    CountIntegrals();   // counting energy deposition in each crystal
    FillHistos();       // filling inntialized histograms with the information generated by CountIntegrals method
    DrawResults();      // Drawing results and dysplaying asymmetry in energy deposition
}