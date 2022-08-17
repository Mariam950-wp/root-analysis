void SaveAll(){
    // check if histos exist
    if( !cLeft ) {
        cout <<"\n * * * Please draw results first * * * \n" << endl; 
        return;
        }

    // Create directory to save results
    TDatime datime;
    //TString dirName = Form("/home/mariam/simulation/ROOToutput/beamtarYpos/%i_%i", datime.GetDate(), datime.GetTime());
    TString dirName = "/home/mariam/simulation/ROOToutput/beamYpos/beam_10";
    gSystem->Exec("mkdir -p " + dirName);

    // Save crystal information
    cLeft->SaveAs(dirName + "/Left_Crystals.pdf");
    cRight->SaveAs(dirName + "/Right_Crystals.pdf");
    cDown->SaveAs(dirName + "/Down_Crystals.pdf");
    cUp->SaveAs(dirName + "/Up_Crystals.pdf");
    cCorners->SaveAs(dirName + "/Corners_Crystals.pdf");

    // root files
    cLeft->SaveAs(dirName + "/Left_Crystals.root");
    cRight->SaveAs(dirName + "/Right_Crystals.root");
    cDown->SaveAs(dirName + "/Down_Crystals.root");
    cUp->SaveAs(dirName + "/Up_Crystals.root");
    cCorners->SaveAs(dirName + "/Corners_Crystals.root");

    //Save Scintillator information
    cDeltaE->SaveAs(dirName + "/DeltaE.pdf");

    // root files
    cDeltaE->SaveAs(dirName + "/DeltaE.root");

    //Save crystal information VC Scintillator information
    cLeft2D->SaveAs(dirName + "/DeltaE_VC_Laft_Crystals.pdf");
    cRight2D->SaveAs(dirName + "/DeltaE_VC_Right_Crystals.pdf");
    cUp2D->SaveAs(dirName + "/DeltaE_VC_Down_Crystals.pdf");
    cDown2D->SaveAs(dirName + "/DeltaE_VC_Up_Crystals.pdf");

    // root files
    cLeft2D->SaveAs(dirName + "/DeltaE_VC_Laft_Crystals.root");
    cRight2D->SaveAs(dirName + "/DeltaE_VC_Right_Crystals.root");
    cUp2D->SaveAs(dirName + "/DeltaE_VC_Down_Crystals.root");
    cDown2D->SaveAs(dirName + "/DeltaE_VC_Up_Crystals.root");

    // Save information about asymmetry
    Asymetry->SaveAs(dirName + "/Asymmetry_In_Energy_Deposition.pdf");

    // root file
    Asymetry->SaveAs(dirName + "/Asymmetry_In_Energy_Deposition.root");

    // altogether file
    
}