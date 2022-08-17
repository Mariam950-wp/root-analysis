
//
//
//

Double_t peak = 254.; // MeV
Double_t sigma = 0.5;
Double_t bkg = 10;

Double_t LowPer = 0.55;
Double_t UpperPer = 0.75;
Double_t InnUpperLimit[NofCrystals];

Double_t IntRange = 10; // peak - IntRange %
Double_t xmin[NofCrystals];
Double_t xmax[NofCrystals];

TF1 *fFitFun[NofCrystals];
TF1 *fPol0[NofCrystals];
TF1 *fGaus[NofCrystals];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Double_t MeanBackg(Int_t index){
    // find maximum bin in the left part of kistogram
    hLYSO[index]->SetAxisRange(0, InnUpperLimit[index]/2);
    Int_t Left = hLYSO[index]->GetMaximumBin();

    // find maximum bin in the right part of histogram
    hLYSO[index]->SetAxisRange(InnUpperLimit[index]/2, InnUpperLimit[index]);
    Int_t Right = hLYSO[index]->GetMaximumBin();

    // count average background between these maximums
    Int_t bins = Right - Left;
    int summ = hLYSO[index]->Integral((Int_t)bins*LowPer+Left,(Int_t)bins*UpperPer+Left); 
    return summ/(bins*UpperPer-bins*LowPer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Int_t FindLeftLimit(Int_t index, Double_t background){
    if(index>NofCrystals)return -1;

    // Search in second half of histogram
    hLYSO[index]->SetAxisRange(InnUpperLimit[index]/2 , InnUpperLimit[index]);

    // find lower limit to consider
    Int_t bintoConsider = hLYSO[index]->GetMaximumBin();
    while(hLYSO[index]->GetBinContent(bintoConsider)>background && bintoConsider > -1)
        bintoConsider -= 1;
    return hLYSO[index]->GetBinCenter(bintoConsider);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Double_t FindUpperLimits(int index){
    return hLYSO[index]->GetBinCenter(hLYSO[index]->GetNbinsX());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FitAll(){

    if( !hLYSO[0] ) {
        cout <<"\n * * * Please analyse file first * * * \n" << endl; 
        return;
        }

    Double_t meanbackg[NofCrystals];

    Double_t fitmin = 200;
    Double_t fitmax = 260;

    for(int i = 0; i < NofCrystals ; i++){

        fFitFun[i] = new TF1(Form("fFitFun_%i", i), "gaus + pol2(3)", fitmin, fitmax);
        fPol0[i] = new TF1(Form("fPol2_%i", i), "pol2", fitmin, fitmax);
        fGaus[i] = new TF1(Form("fGaus_%i", i), "gaus", fitmin, fitmax);

        hLYSO[i]->GetXaxis()->SetRangeUser(100., 300.);
        
        Int_t maxBin = hLYSO[i]->GetMaximumBin();
        peak = hLYSO[i]->GetBinCenter( maxBin );
        bkg =  hLYSO[i]->Integral(100, 110)/10.;

        fFitFun[i]->SetParLimits(1, peak-3.*sigma, peak+3.*sigma);
        fFitFun[i]->SetParLimits(2, 0.5*sigma, 2.*sigma);
        fFitFun[i]->SetParLimits(4, 0, -1000.);
        fFitFun[i]->SetParLimits(5, 0, -1000.);
        
        fFitFun[i]->SetParameters(10., peak, sigma, bkg, -1.);
        hLYSO[i]->Fit(fFitFun[i], "+R0");

        Double_t pars[6];





        // maximumvalue on X axis
        //InnUpperLimit[i] = FindUpperLimits(i);

        // average background for each histogram
        //meanbackg[i] = MeanBackg(i);

        // find limits to consider
        //upperlimit[i] = hLYSO[i]->GetBinCenter(hLYSO[i]->GetNbinsX());
        //lowlimit[i] = FindLeftLimit(i,meanbackg[i]);

        // cut backgrounds
        //hLYSO[i]->SetAxisRange(lowlimit[i],upperlimit[i]);
        //hLYSO[i]->Fit("gaus");
        
    }

}