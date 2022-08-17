#include "CAnaElAsymm.hh"
#include "CFadcDataManager.hh"
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

ClassImp(CAnaElAsymm);

CAnaElAsymm::CAnaElAsymm(const char* name, const char* option, UInt_t ns, bool rawsampleson) : CAnadpelSelector(name,option,ns,rawsampleson)
{
  fPolIdx_old = 0;
  fOldTime = 0;
  fCOSYdata = 0x0;
  
  SetPolStates(1,2,15);
  SetTimeScale(30);
  SetUpdateTime(5);
  SetNumOfCRcycles(NStates*5);

  for (int k=0; k<NSides; k++) {
    fNThetaIdx[k] = 0;
    fThetaIdxMask[k] = 0x0;
    
    fNPhiIdx[k] = 0x0;
    fChannelId[k] = 0x0;
  }

  int i=0;
  char* opt = strtok(Form("%s",option)," ,.-");

  while (opt != NULL) {
    if (i < NSides) {
      fDetectorSides[i] = opt;
      fSubName += opt;
    }
    else break;
    
    opt = strtok(NULL," ,.-");
    i++;
  }

  cout << "Sides: " << fDetectorSides[0] << ", " << fDetectorSides[1] << ". Subname: " << fSubName << endl;
}

CAnaElAsymm::~CAnaElAsymm()
{
  ClearMasks();
}

bool CAnaElAsymm::Process(CEventBase* event)
{
  
  if (!CAnadpelSelector::Process(event)) return false;
  if (fFiredSide < 1 || fFiredSide > 2) return false;
  
  Int_t iSide = fFiredSide - 1; //fFiredSide = 1 or 2
  Int_t iPol = (fCOSYdata) ? GetPolIdx(fCOSYdata->GetPolState()) : -1;
  Int_t iTheta = GetThetaIdx(iSide);
  Int_t ith = iTheta+1;
  if (!iSide) ith *= -1;
  
  CAnadEvsE* ana;

  if (iPol>=0 && iTheta>=0) {
    if ((ana = GetAnalysis(iSide))) hPolAmplitude[iSide][iPol][iTheta]->Fill(ana->GetTotal_E());
    hTmpPolCounts[iSide]->Fill(iTheta);
    hPermPolCounts[iSide][iPol]->Fill(iTheta);
    hPolCounts[iPol]->Fill(ith);

    Int_t iPhi = GetPhiIdx(iSide, iTheta);
    if (iPhi>=0) {
      if (iSide == 1) iPhi = fNPhiIdx[iSide][iTheta] - iPhi - 1;
      hPolStats[iPhi]->Fill(ith);
    }
  }

  UpdateAsymmetries();

  if (IsNewPolState()) {
    UpdateCrossRatios(iPol);
    for (int k=0; k<fNPhiIdx[0][0]; k++) hPolStats[k]->Reset();
  }

  return true;
}


bool CAnaElAsymm::Begin(TFile* file)
{
  bool IsOK = CAnadpelSelector::Begin(file);
  
  if (fManager) fCOSYdata = fManager->GetCosyData();

  TString name;
  Int_t NTimeBins = fTimeScaleSec/fTimeUpdateSec;
  if (fTimeScaleSec%fTimeUpdateSec) NTimeBins++;

  Int_t Ntheta = fNThetaIdx[0];
  if (fNThetaIdx[1] < fNThetaIdx[0]) Ntheta = fNThetaIdx[1];
  
  if (Ntheta <= 0) return false;

  for (int ipol=0; ipol<NStates; ipol++) {
    for (int k=0; k<NSides; k++) {
      hPolAmplitude[k][ipol] = new TH1F* [fNThetaIdx[k]];

      for (int ith=0; ith<fNThetaIdx[k]; ith++) {
	name.Form("hPolAmplitude_%s%i_%02i",fDetectorSides[k].Data(),ith+1,fPolStates[ipol]);
	hPolAmplitude[k][ipol][ith] = new TH1F(name,";E [MeV] ;",1000,0,400);
	AddHistogram(hPolAmplitude[k][ipol][ith],"PolCounts");
      }

      name.Form("hPermPolCounts_%s%02i",fDetectorSides[k].Data(),fPolStates[ipol]);
      hPermPolCounts[k][ipol] = new TH1F(name,";Theta Index ;", Ntheta, 0, Ntheta);
      AddHistogram(hPermPolCounts[k][ipol],"PolCounts");
    }

    name.Form("hPolCounts%s_%02i",fSubName.Data(),fPolStates[ipol]);
    hPolCounts[ipol] = new TH1F(name,";Theta Index ;", 
				  fNThetaIdx[0]+fNThetaIdx[1]+3, -1*fNThetaIdx[0]-1.5, fNThetaIdx[1]+1.5);
    AddHistogram(hPolCounts[ipol],"PolCounts");
  }
  
  hTimeAsymm = new TH1F* [Ntheta+1]; //last one is an empty histogram for zero line
  
  TString title;
  title.Form(";Time [sec] ;(%s-%s)/(%s+%s)",fDetectorSides[0].Data(),fDetectorSides[1].Data(),
	     fDetectorSides[0].Data(),fDetectorSides[1].Data());

  for (int k=0; k<NSides; k++) {
    name.Form("hTmpPolCounts_%s",fDetectorSides[k].Data());
    hTmpPolCounts[k] = new TH1F(name,";Theta Index ;", Ntheta, 0, Ntheta);
    AddHistogram(hTmpPolCounts[k],"PolCounts");
  
    for (int ith=0; ith<Ntheta; ith++) {
      if (k==NSides-1) {
	name.Form("hTimeAsymm%s%i",fSubName.Data(),ith+1);
	hTimeAsymm[ith] = new TH1F(name,title,NTimeBins,0,NTimeBins*fTimeUpdateSec);
	AddHistogram(hTimeAsymm[ith],"Asymmetries");
      }
    }
  }

  hTimeAsymm[Ntheta] = new TH1F(Form("hTimeAsymm%s_dummy",fSubName.Data()),title,NTimeBins,0,NTimeBins*fTimeUpdateSec);
  AddHistogram(hTimeAsymm[Ntheta],"Asymmetries");

  //Create histograms for the statistics
  Int_t Nstat = 3;
  hPolStats = new TH1F* [3];
  
  // Double_t min = -1*fNThetaIdx[0]-1.5;
  // Double_t max = fNThetaIdx[1]+1.5;

  for (int k=0; k<Nstat; k++) {
    name.Form("hPolStats%i",k+1);
    hPolStats[k] = new TH1F(name,";Theta Index ;", 
			    fNThetaIdx[0]+fNThetaIdx[1]+3, -1*fNThetaIdx[0]-1.5, fNThetaIdx[1]+1.5);
    AddHistogram(hPolStats[k],"PolCounts");
  }

  //Create Cross ratio histograms
  hCrossRatio = new TH1F("hCrossRatio",";Theta Index ;Cross Ratio",Ntheta+2, 0.5, Ntheta+2.5);
  AddHistogram(hCrossRatio,"CrossRatios");

  hTimeCR = new TH1F* [Ntheta];

  for (int ipol=0; ipol<NStates-1; ipol++) {
    hTimeHCR[ipol] = new TH1F* [Ntheta];
    name.Form("hHalfCrossRatio_%02i",fPolStates[NStates-2-ipol]);
    hHalfCrossRatio[ipol] = new TH1F(name,";Theta Index ;Cross Ratio",Ntheta+2, 0.5, Ntheta+2.5);
    AddHistogram(hHalfCrossRatio[ipol],"CrossRatios");
  }

  hHalfCrossRatio[NStates-1] = new TH1F("hHalfCrossRatio_dummy",";Theta Index ;Cross Ratio",Ntheta+2, 0.5, Ntheta+2.5);
  AddHistogram(hHalfCrossRatio[NStates-1],"CrossRatios");

  for (int ith=0; ith<Ntheta; ith++) {
    name.Form("hTimeCR%i",ith+1);
    hTimeCR[ith] = new TH1F(name,";Last pol. cycles ;CR",fNLastCRcycles,0,fNLastCRcycles);
    AddHistogram(hTimeCR[ith],"CrossRatios");    

    for (int ipol=0; ipol<NStates-1; ipol++) {
      //if (ith == 0) hTimeHCR[ipol] = new TH1F* [Ntheta];
      name.Form("hTimeHCR%i_%02i",ith+1,fPolStates[NStates-2-ipol]);
      hTimeHCR[ipol][ith] = new TH1F(name,";Last pol. cycles ;HalfCR",fNLastCRcycles,0,fNLastCRcycles);
      AddHistogram(hTimeHCR[ipol][ith],"CrossRatios");
    }
  }

  fUpdateTimer.Start();

  return IsOK;
}

void CAnaElAsymm::Clear()
{
  CAnadpelSelector::Clear();
}

void CAnaElAsymm::ClearHisto(Option_t* o)
{
  CAnadpelSelector::ClearHisto(o);
  fOldTime = fTimeUpdateSec;
  fUpdateTimer.Start();
}

void CAnaElAsymm::ClearMasks()
{
  for (int k=0; k<NSides; k++) {
    if (fChannelId[k]) {
      for (int ith=0; ith<fNThetaIdx[k]; ith++) {
	if (fChannelId[k][ith]) delete [] fChannelId[k][ith];
      }
      
      delete [] fChannelId[k];
      fChannelId[k] = 0x0;
    }

    if (fNPhiIdx[k]) {
      delete [] fNPhiIdx[k];
      fNPhiIdx[k] = 0x0;
    }

    if (fThetaIdxMask[k]) {
      delete [] fThetaIdxMask[k];
      fThetaIdxMask[k] = 0x0;
    }

    fNThetaIdx[k] = 0;
  }
}

Int_t CAnaElAsymm::GetThetaIdx(Int_t side) //indexing from 0
{
  if (side < 0 && side >= NSides) return -1;
  
  CAnadEvsE* ana = GetAnalysis(side);
  const CDaqConfig* allchannels = (ana) ? ana->GetFiredChannels() : 0;
  Int_t ThetaIdx = -1;

  for (int ith=0; ith<fNThetaIdx[side]; ith++) {
    if (fThetaIdxMask[side][ith].IsIncluded(allchannels)) {ThetaIdx = ith; break;}
  }
  
  return ThetaIdx;
}

Int_t CAnaElAsymm::GetPhiIdx(Int_t side, Int_t theta_idx)
{
  if (side < 0 && side >= NSides) return -1;
  if (theta_idx < 0 || theta_idx >= fNThetaIdx[side]) return -1;

  CAnadEvsE* ana = GetAnalysis(side);
  const CDaqConfig* allchannels = (ana) ? ana->GetFiredChannels() : 0;
  Int_t PhiIdx = -1;

  for (int k=0; k<fNPhiIdx[side][theta_idx]; k++) {
    if (allchannels->IsAccChannel(fChannelId[side][theta_idx][k])) {PhiIdx = k; break;}
  }

  return PhiIdx;
}

Int_t CAnaElAsymm::GetPolIdx(Int_t state)
{
  Int_t idx = -1;

  for (int k=0; k<NStates; k++) {
    if (state == fPolStates[k]) {idx = k; break;}
  }

  return idx;
}

bool CAnaElAsymm::IsNewPolState()
{
  bool newstate = false;
  Int_t PolIdx = (fCOSYdata) ? fCOSYdata->GetPolState() : -1;
  
  for (int k=0; k<NStates; k++) {
    if (PolIdx == fPolStates[k]) {
      if (PolIdx != fPolIdx_old) {newstate = true; fPolIdx_old = PolIdx;}
      break;
    }
  }
  
  return newstate;
}

void CAnaElAsymm::ScanThetaIdx(const char* s)
{  
  if (strlen(s) != 6) return;
  
  TString name = s;
  int idx;

  for (int k=0; k<NSides; k++) {
    if (name.BeginsWith(fDetectorSides[k])) {
      idx = atoi(&s[fDetectorSides[k].Length()]);
      if (idx > fNThetaIdx[k]) {fNThetaIdx[k] = idx; break;}
    }
  }
}

void CAnaElAsymm::ScanPhiIdx(Int_t Id, const char* s)
{ 
  if (strlen(s) != 6) return;

  TString name = s;
  TString tmp;
  bool done = false;
  
  for (int k=0; k<NSides; k++) {
    if (done) break;

    for (int i=0; i<fNThetaIdx[k]; i++) {
      tmp = fDetectorSides[k];
      tmp += (i+1);
      tmp += "_";
      
      if (name.BeginsWith(tmp)) {
  	fThetaIdxMask[k][i].SetChannel(Id);
  	fNPhiIdx[k][i] = atoi(&s[fDetectorSides[k].Length() + 4]);
  	fChannelId[k][i] = new Int_t [fNPhiIdx[k][i]];

  	for (int iphi=0; iphi<fNPhiIdx[k][i]; iphi++) fChannelId[k][i][iphi] = 0;

  	done = true;
  	break;
      }
    }
  }
}

void CAnaElAsymm::ScanChannelIds(Int_t Id, const char* s)
{
  if (strlen(s) != 6) return;

  TString name = s;
  TString tmp;
  bool done = false;

  for (int k=0; k<NSides; k++) {
    if (done) break;

    for (int i=0; i<fNThetaIdx[k]; i++) {
      tmp = fDetectorSides[k];
      tmp += (i+1);
      tmp += "_";

      if (name.BeginsWith(tmp)) {
	name.Remove(0,3);
	name.Remove(1,2);
	int iphi = name.Atoi();
	fChannelId[k][i][iphi-1] = Id;
	done = true;
	break;
      }
    }
  }

}

void CAnaElAsymm::SetPolStates(Int_t Up_idx, Int_t Down_idx, Int_t Unpol_idx)
{
  fPolStates[0] = Up_idx; fPolStates[1] = Down_idx; fPolStates[2] = Unpol_idx;

  int mask = 0;
  
  for (int k=0; k<NStates; k++) mask |= 1<<(fPolStates[k]-1);
  
  SetPolMask(mask);
}

Double_t CAnaElAsymm::GetAsymmetry(Double_t Nleft, Double_t Nright)
{
  if (Nleft < 1e-6 || Nright < 1e-6) return 0;
  else return (Nleft - Nright)/(Nleft + Nright);
}

Double_t CAnaElAsymm::GetAsymmetryError(Double_t Nleft, Double_t Nright)
{
  if (Nleft < 1e-6 || Nright < 1e-6) return 0;
  else return 2.*Nleft*Nright/((Nleft+Nright)*(Nleft+Nright))*sqrt(1./Nleft + 1./Nright);
} 


Double_t CAnaElAsymm::GetCrossRatio(Double_t Nleft_up, Double_t Nleft_down, Double_t Nright_up, Double_t Nright_down, Bool_t HalfCS) {
  if (Nright_up*Nleft_down < 1e-6) return 1;

  Double_t r = (Nleft_up*Nright_down)/(Nright_up*Nleft_down);
  
  if (!HalfCS) r = sqrt(r);
  
  return r;
}

Double_t CAnaElAsymm::GetCrossRatioError(Double_t r, Double_t Nleft_up, Double_t Nleft_down, Double_t Nright_up, Double_t Nright_down, Bool_t HalfCS) {
  if (Nleft_up < 1e-6 || Nleft_down < 1e-6 || Nright_up < 1e-6 || Nright_down < 1e-6) return 0;

  Double_t err = sqrt(1./Nleft_up + 1./Nleft_down + 1./Nright_up + 1./Nright_down);
  
  if (HalfCS) err *= 2;
  
  return (r*err)/((r+1)*(r+1));
}

bool CAnaElAsymm::UpdateAsymmetries()
{
  Double_t time = fUpdateTimer.RealTime();
  
  if (time < fOldTime) {
    fUpdateTimer.Continue();
    return false;
  }
  
  if (time > fTimeScaleSec) {//time overflow
    fOldTime = fTimeUpdateSec;
    fUpdateTimer.Start();
  }
  else fUpdateTimer.Continue();

  Int_t timebin = fOldTime/fTimeUpdateSec;
  fOldTime += fTimeUpdateSec;

  //------- Fill asymmetry histograms ---------
  Int_t Ntheta = fNThetaIdx[0];
  if (fNThetaIdx[1] < fNThetaIdx[0]) Ntheta = fNThetaIdx[1];
  
  Double_t asymm, err;

  for (int ith=0; ith<Ntheta; ith++) {
    asymm = GetAsymmetry(hTmpPolCounts[0]->GetBinContent(ith+1),hTmpPolCounts[1]->GetBinContent(ith+1));
    err = GetAsymmetryError(hTmpPolCounts[0]->GetBinContent(ith+1),hTmpPolCounts[1]->GetBinContent(ith+1));
    //cout << ith << ": " << asymm << " " << err << endl;
    hTimeAsymm[ith]->SetBinContent(timebin,asymm);
    hTimeAsymm[ith]->SetBinError(timebin,err);
  }

  //-------- Clear count accumulators ---------
  for (int k=0; k<NSides; k++) hTmpPolCounts[k]->Reset();

  return true;
}

bool CAnaElAsymm::UpdateCrossRatios(Int_t PolIdx)
{
  static Int_t PolIdx_old = -1;
  static Int_t PolIdx_shifter = -1*NStates;
  Double_t cr, cr_err, LU, LD, RU, RD;
  Int_t ibinL, ibinR;
  Int_t Ntheta = fNThetaIdx[0];
  if (fNThetaIdx[1] < fNThetaIdx[0]) Ntheta = fNThetaIdx[1];
  
  //Find two states which will be used for CR calculation.
  //in case of two polarised and one unpolarised states these 
  //two are the previous and next (pre-previous) states.
  if (PolIdx_old) {
    if (PolIdx>0) PolIdx_old = PolIdx - 1;
    else PolIdx_old = NStates - 1;
  }
  
  Int_t PolIdx_preold = (PolIdx + 1)%NStates;
  bool IsHCR = (PolIdx != NStates-1); //If unpolarised then IsHCR is false
  Int_t c_flip = (IsHCR && PolIdx==0) ? -1 : 1; //Flip coefficient. Needed for flipping one of the HCRs
  TH1* h;

  //cout << "Calculating CR between states " << fPolStates[PolIdx_old] << " and " << fPolStates[PolIdx_preold] << endl;

  if (PolIdx_shifter < -1) PolIdx_shifter++;
  else if (PolIdx_shifter < 0) {
    PolIdx_shifter = PolIdx; //In every occurance of this state time histograms will be shifted.
    //cout << "Shift will be done on state change to " << fPolStates[PolIdx] << endl;
  }

  for (int ith=0; ith<Ntheta; ith++) {
    ibinL = hPolCounts[PolIdx_old]->FindBin((ith+1)*(-1));
    ibinR = hPolCounts[PolIdx_old]->FindBin(ith+1);
    LU = hPolCounts[PolIdx_old]->GetBinContent(ibinL);
    LD = hPolCounts[PolIdx_preold]->GetBinContent(ibinL);
    RU = hPolCounts[PolIdx_old]->GetBinContent(ibinR);
    RD = hPolCounts[PolIdx_preold]->GetBinContent(ibinR);
    cr = GetCrossRatio(LU,LD,RU,RD,IsHCR);
    cr_err = GetCrossRatioError(cr,LU,LD,RU,RD,IsHCR);

    if (PolIdx_shifter >= 0 && PolIdx == PolIdx_shifter) {
      ShiftDataLeft(hTimeCR[ith],3);
      for (int k=0; k<NStates-1; k++) ShiftDataLeft(hTimeHCR[k][ith],3);
    }

    h = (IsHCR) ? hTimeHCR[PolIdx][ith] : hTimeCR[ith];
    //ShiftDataLeft(h,3);
    h->SetBinContent(fNLastCRcycles-NStates+PolIdx+1,(cr-1)/(cr+1)*c_flip);
    h->SetBinError(fNLastCRcycles-NStates+PolIdx+1,cr_err);
  }


  //Clear pre-previous state
  hPolCounts[PolIdx_preold]->Reset();
  //cout << "CR: Cleared state " << fPolStates[PolIdx_preold] << endl;

  //------- Rebuild average cross ratio histograms --------
  for (int ith=0; ith<Ntheta; ith++) {
    LU = hPermPolCounts[0][PolIdx_old]->GetBinContent(ith+1);
    LD = hPermPolCounts[0][PolIdx_preold]->GetBinContent(ith+1);
    RU = hPermPolCounts[1][PolIdx_old]->GetBinContent(ith+1);
    RD = hPermPolCounts[1][PolIdx_preold]->GetBinContent(ith+1);
    cr = GetCrossRatio(LU,LD,RU,RD,IsHCR);
    cr_err = GetCrossRatioError(cr,LU,LD,RU,RD,IsHCR);
    
    h = (IsHCR) ? hHalfCrossRatio[PolIdx] : hCrossRatio;
    h->SetBinContent(ith+1,fabs((cr-1)/(cr+1)));
    h->SetBinError(ith+1,cr_err);
  }
  //-----------------------------------------------------

  PolIdx_old = PolIdx;

  return true;
}

void CAnaElAsymm::ShiftDataLeft(TH1* h, Int_t nbins)
{
  Int_t Nbins = h->GetNbinsX();
  Double_t val, err;

  for (int k=0; k<Nbins; k++) {
    if (k+1+nbins <= Nbins) {
      val = h->GetBinContent(k+1+nbins);
      err = h->GetBinError(k+1+nbins);
    }
    else val = err = 0;
    
    h->SetBinContent(k+1,val);
    h->SetBinError(k+1,err);
  }
}

void CAnaElAsymm::PrintChannelIds()
{
  CAnadpelSelector::PrintChannelIds();

  TString name;

  for (int k=0; k<NSides; k++) {
    if (fChannelId[k]) {
      cout << "Side " << fDetectorSides[k] << ": " << endl;
      
      for (int ith=0; ith<fNThetaIdx[k]; ith++) {
	for (int iphi=0; iphi<fNPhiIdx[k][ith]; iphi++) {
	  name.Form("%s%i_%i_%i",fDetectorSides[k].Data(),ith+1,iphi+1,fNPhiIdx[k][ith]);
	  cout << "Module " << name << " at ch. " << fChannelId[k][ith][iphi] << endl;
	}
      }
    }
  }
}

bool CAnaElAsymm::ReadConfig()
{
  if (!CAnadpelSelector::ReadConfig()) return false; //Fills masks, ensures that Nmodules will not be 0!
  
  EdmPolarimeterConfiguration* cfg = EdmPolarimeterConfiguration::get();
  int Nmodules = cfg->getNumOfModules();
  EdmModule* m;

  ClearMasks();

  //Find the number of theta indexes for each side  
  for (int k=0; k<Nmodules; k++) {
    m = cfg->getModuleByIndex(k);
    ScanThetaIdx(m->getName());
  }
  
  cout << fName << ": Number of configured channels = " << Nmodules
       << ". Left " << fNThetaIdx[0] << ", Right " << fNThetaIdx[1] << endl;

  //Reread and save the channel configuration
  for (int k=0; k<NSides; k++) {
    fThetaIdxMask[k] = new CDaqConfig [fNThetaIdx[k]];
    fNPhiIdx[k] = new Int_t [fNThetaIdx[k]];
    fChannelId[k] = new Int_t* [fNThetaIdx[k]];
    
    for (int i=0; i<fNThetaIdx[k]; i++) fChannelId[k][i] = 0x0;
  }
  
  //Fill Phi masks
  int ich;

  for (int k=0; k<Nmodules; k++) {
    m = cfg->getModuleByIndex(k);
    ich = fDAQ.GetGlobalChID(m);
    ScanPhiIdx(ich, m->getName());
  }
  
  //Fill general masks
  for (int k=0; k<Nmodules; k++) {
    m = cfg->getModuleByIndex(k);
    ich = fDAQ.GetGlobalChID(m);
    ScanChannelIds(ich, m->getName());
  }
  
  return true;
}
