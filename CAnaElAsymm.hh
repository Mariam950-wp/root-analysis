#ifndef _CANAELASYMM_HH_
#define _CANAELASYMM_HH_

#include "CAnadpelSelector.hh"
#include "CAnaCOSY.hh"
#include <TStopwatch.h>

class CAnaElAsymm : public CAnadpelSelector
{
protected:
  static const Int_t    NSides = 2;
  static const Int_t    NStates = 3;

  Int_t                 fPolStates[NStates]; //Last one is always unpol state.
  Int_t                 fPolIdx_old;
  Int_t                 fTimeScaleSec;
  Int_t                 fTimeUpdateSec;
  Int_t                 fNThetaIdx[NSides];
  Int_t*                fNPhiIdx[NSides];
  Int_t                 fNLastCRcycles;
  Int_t**               fChannelId[NSides]; //Containes channels Ids for each theta idx. ([side][iTheta]) 
  Double_t              fOldTime;
  TString               fSubName;
  TString               fDetectorSides[NSides];

  CDaqConfig*           fThetaIdxMask[NSides]; //Containes channels Ids for each theta idx. ([side][iTheta]) 
  
  TH1F**                hPolAmplitude[NSides][NStates];
  TH1F*                 hTmpPolCounts[NSides];
  TH1F*                 hPermPolCounts[NSides][NStates];
  TH1F*                 hPolCounts[NStates];
  TH1F*                 hCrossRatio;
  TH1F*                 hHalfCrossRatio[NStates];
  TH1F**                hPolStats;
  TH1F**                hTimeAsymm;
  TH1F**                hTimeCR;
  TH1F**                hTimeHCR[NStates-1];

  CAnaCOSY*             fCOSYdata;
  TStopwatch            fUpdateTimer;

  void                  ClearMasks();
  Double_t              GetCrossRatio(Double_t, Double_t, Double_t, Double_t, Bool_t HalfCS = false);
  Double_t              GetCrossRatioError(Double_t, Double_t, Double_t, Double_t, Double_t, Bool_t HalfCS = false);
  Double_t              GetAsymmetry(Double_t, Double_t); //Left-Right
  Double_t              GetAsymmetryError(Double_t, Double_t);  
  Int_t                 GetThetaIdx(Int_t);
  Int_t                 GetPhiIdx(Int_t, Int_t);
  Int_t                 GetPolIdx(Int_t);
  bool                  IsNewPolState();
  void                  ScanThetaIdx(const char*);
  void                  ScanPhiIdx(Int_t, const char*);
  void                  ScanChannelIds(Int_t, const char*);
  void                  SetNumOfCRcycles(Int_t nc) { fNLastCRcycles = nc; }
  void                  ShiftDataLeft(TH1* h, Int_t nbins = 1);
  bool                  UpdateAsymmetries();
  bool                  UpdateCrossRatios(Int_t);

public:

  CAnaElAsymm(const char*, const char*, UInt_t, bool);
  virtual ~CAnaElAsymm();

  virtual bool          Begin(TFile*);
  virtual bool          Process(CEventBase* event = 0);
  virtual void          Clear();
  virtual void          ClearHisto(Option_t *o = "");
  virtual int           GetAnalysisType() { return CAnaBase::ElAsymm; }
  virtual const char*   GetAnalysisName() const { return "CAnaElAsymm"; }
  virtual bool          ReadConfig();
  virtual void          PrintChannelIds();

  void                  SetPolStates(Int_t Up_idx, Int_t Down_idx, Int_t Unpol_idx);
  void                  SetTimeScale(Int_t nsec) { fTimeScaleSec = nsec; }
  void                  SetUpdateTime(Int_t nsec) { fTimeUpdateSec = nsec; fOldTime = fTimeUpdateSec; }


  ClassDef(CAnaElAsymm, 0);
};

#endif
