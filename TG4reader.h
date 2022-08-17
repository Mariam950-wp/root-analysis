//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Mar 29 14:13:54 2019 by ROOT version 6.16/00
// from TTree hits/eDep
// found on file: pol.root
//////////////////////////////////////////////////////////

#ifndef TG4reader_h
#define TG4reader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class TG4reader {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           eventID;
   Double_t        Particle;
   Double_t        Kinetic_Energy;
   Double_t        theta_lab;
   Double_t        phi_lab;
   Double_t        U4_3_7;
   Double_t        U4_4_7;
   Double_t        U4_5_7;
   Double_t        U3_3_7;
   Double_t        U3_4_7;
   Double_t        U3_5_7;
   Double_t        U2_2_5;
   Double_t        U2_3_5;
   Double_t        U2_4_5;
   Double_t        C1_1_4;
   Double_t        U1_1_3;
   Double_t        U1_2_3;
   Double_t        U1_3_3;
   Double_t        C1_2_4;
   Double_t        L4_5_7;
   Double_t        L3_5_7;
   Double_t        L2_4_5;
   Double_t        L1_3_3;
   Double_t        R1_1_3;
   Double_t        R2_2_5;
   Double_t        R3_3_7;
   Double_t        R4_3_7;
   Double_t        L4_4_7;
   Double_t        L3_4_7;
   Double_t        L2_3_5;
   Double_t        L1_2_3;
   Double_t        R1_2_3;
   Double_t        R2_3_5;
   Double_t        R3_4_7;
   Double_t        R4_4_7;
   Double_t        L4_3_7;
   Double_t        L3_3_7;
   Double_t        L2_2_5;
   Double_t        L1_1_3;
   Double_t        R1_3_3;
   Double_t        R2_4_5;
   Double_t        R3_5_7;
   Double_t        R4_5_7;
   Double_t        C1_4_4;
   Double_t        D1_3_3;
   Double_t        D1_2_3;
   Double_t        D1_1_3;
   Double_t        C1_3_4;
   Double_t        D2_4_5;
   Double_t        D2_3_5;
   Double_t        D2_2_5;
   Double_t        D3_5_7;
   Double_t        D3_4_7;
   Double_t        D3_3_7;
   Double_t        D4_5_7;
   Double_t        D4_4_7;
   Double_t        D4_3_7;
   Double_t        kE_dE_R;
   Double_t        kE_dE_L;
   Double_t        kE_dE_U;
   Double_t        kE_dE_D;

   // List of branches
   TBranch        *b_eventID;   //!
   TBranch        *b_Particle;   //!
   TBranch        *b_Kinetic_Energy;   //!
   TBranch        *b_theta_lab;   //!
   TBranch        *b_phi_lab;   //!
   TBranch        *b_U4_3_7;   //!
   TBranch        *b_U4_4_7;   //!
   TBranch        *b_U4_5_7;   //!
   TBranch        *b_U3_3_7;   //!
   TBranch        *b_U3_4_7;   //!
   TBranch        *b_U3_5_7;   //!
   TBranch        *b_U2_2_5;   //!
   TBranch        *b_U2_3_5;   //!
   TBranch        *b_U2_4_5;   //!
   TBranch        *b_C1_1_4;   //!
   TBranch        *b_U1_1_3;   //!
   TBranch        *b_U1_2_3;   //!
   TBranch        *b_U1_3_3;   //!
   TBranch        *b_C1_2_4;   //!
   TBranch        *b_L4_5_7;   //!
   TBranch        *b_L3_5_7;   //!
   TBranch        *b_L2_4_5;   //!
   TBranch        *b_L1_3_3;   //!
   TBranch        *b_R1_1_3;   //!
   TBranch        *b_R2_2_5;   //!
   TBranch        *b_R3_3_7;   //!
   TBranch        *b_R4_3_7;   //!
   TBranch        *b_L4_4_7;   //!
   TBranch        *b_L3_4_7;   //!
   TBranch        *b_L2_3_5;   //!
   TBranch        *b_L1_2_3;   //!
   TBranch        *b_R1_2_3;   //!
   TBranch        *b_R2_3_5;   //!
   TBranch        *b_R3_4_7;   //!
   TBranch        *b_R4_4_7;   //!
   TBranch        *b_L4_3_7;   //!
   TBranch        *b_L3_3_7;   //!
   TBranch        *b_L2_2_5;   //!
   TBranch        *b_L1_1_3;   //!
   TBranch        *b_R1_3_3;   //!
   TBranch        *b_R2_4_5;   //!
   TBranch        *b_R3_5_7;   //!
   TBranch        *b_R4_5_7;   //!
   TBranch        *b_C1_4_4;   //!
   TBranch        *b_D1_3_3;   //!
   TBranch        *b_D1_2_3;   //!
   TBranch        *b_D1_1_3;   //!
   TBranch        *b_C1_3_4;   //!
   TBranch        *b_D2_4_5;   //!
   TBranch        *b_D2_3_5;   //!
   TBranch        *b_D2_2_5;   //!
   TBranch        *b_D3_5_7;   //!
   TBranch        *b_D3_4_7;   //!
   TBranch        *b_D3_3_7;   //!
   TBranch        *b_D4_5_7;   //!
   TBranch        *b_D4_4_7;   //!
   TBranch        *b_D4_3_7;   //!
   TBranch        *b_kE_dE_R;   //!
   TBranch        *b_kE_dE_L;   //!
   TBranch        *b_kE_dE_U;   //!
   TBranch        *b_kE_dE_D;   //!

   TG4reader(TTree *tree=0);
   virtual ~TG4reader();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TG4reader_cxx
TG4reader::TG4reader(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("pol.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("pol.root");
      }
      f->GetObject("hits",tree);

   }
   Init(tree);
}

TG4reader::~TG4reader()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TG4reader::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TG4reader::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void TG4reader::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("eventID", &eventID, &b_eventID);
   fChain->SetBranchAddress("Particle", &Particle, &b_Particle);
   fChain->SetBranchAddress("Kinetic_Energy", &Kinetic_Energy, &b_Kinetic_Energy);
   fChain->SetBranchAddress("theta_lab", &theta_lab, &b_theta_lab);
   fChain->SetBranchAddress("phi_lab", &phi_lab, &b_phi_lab);
   fChain->SetBranchAddress("U4_3_7", &U4_3_7, &b_U4_3_7);
   fChain->SetBranchAddress("U4_4_7", &U4_4_7, &b_U4_4_7);
   fChain->SetBranchAddress("U4_5_7", &U4_5_7, &b_U4_5_7);
   fChain->SetBranchAddress("U3_3_7", &U3_3_7, &b_U3_3_7);
   fChain->SetBranchAddress("U3_4_7", &U3_4_7, &b_U3_4_7);
   fChain->SetBranchAddress("U3_5_7", &U3_5_7, &b_U3_5_7);
   fChain->SetBranchAddress("U2_2_5", &U2_2_5, &b_U2_2_5);
   fChain->SetBranchAddress("U2_3_5", &U2_3_5, &b_U2_3_5);
   fChain->SetBranchAddress("U2_4_5", &U2_4_5, &b_U2_4_5);
   fChain->SetBranchAddress("C1_1_4", &C1_1_4, &b_C1_1_4);
   fChain->SetBranchAddress("U1_1_3", &U1_1_3, &b_U1_1_3);
   fChain->SetBranchAddress("U1_2_3", &U1_2_3, &b_U1_2_3);
   fChain->SetBranchAddress("U1_3_3", &U1_3_3, &b_U1_3_3);
   fChain->SetBranchAddress("C1_2_4", &C1_2_4, &b_C1_2_4);
   fChain->SetBranchAddress("L4_5_7", &L4_5_7, &b_L4_5_7);
   fChain->SetBranchAddress("L3_5_7", &L3_5_7, &b_L3_5_7);
   fChain->SetBranchAddress("L2_4_5", &L2_4_5, &b_L2_4_5);
   fChain->SetBranchAddress("L1_3_3", &L1_3_3, &b_L1_3_3);
   fChain->SetBranchAddress("R1_1_3", &R1_1_3, &b_R1_1_3);
   fChain->SetBranchAddress("R2_2_5", &R2_2_5, &b_R2_2_5);
   fChain->SetBranchAddress("R3_3_7", &R3_3_7, &b_R3_3_7);
   fChain->SetBranchAddress("R4_3_7", &R4_3_7, &b_R4_3_7);
   fChain->SetBranchAddress("L4_4_7", &L4_4_7, &b_L4_4_7);
   fChain->SetBranchAddress("L3_4_7", &L3_4_7, &b_L3_4_7);
   fChain->SetBranchAddress("L2_3_5", &L2_3_5, &b_L2_3_5);
   fChain->SetBranchAddress("L1_2_3", &L1_2_3, &b_L1_2_3);
   fChain->SetBranchAddress("R1_2_3", &R1_2_3, &b_R1_2_3);
   fChain->SetBranchAddress("R2_3_5", &R2_3_5, &b_R2_3_5);
   fChain->SetBranchAddress("R3_4_7", &R3_4_7, &b_R3_4_7);
   fChain->SetBranchAddress("R4_4_7", &R4_4_7, &b_R4_4_7);
   fChain->SetBranchAddress("L4_3_7", &L4_3_7, &b_L4_3_7);
   fChain->SetBranchAddress("L3_3_7", &L3_3_7, &b_L3_3_7);
   fChain->SetBranchAddress("L2_2_5", &L2_2_5, &b_L2_2_5);
   fChain->SetBranchAddress("L1_1_3", &L1_1_3, &b_L1_1_3);
   fChain->SetBranchAddress("R1_3_3", &R1_3_3, &b_R1_3_3);
   fChain->SetBranchAddress("R2_4_5", &R2_4_5, &b_R2_4_5);
   fChain->SetBranchAddress("R3_5_7", &R3_5_7, &b_R3_5_7);
   fChain->SetBranchAddress("R4_5_7", &R4_5_7, &b_R4_5_7);
   fChain->SetBranchAddress("C1_4_4", &C1_4_4, &b_C1_4_4);
   fChain->SetBranchAddress("D1_3_3", &D1_3_3, &b_D1_3_3);
   fChain->SetBranchAddress("D1_2_3", &D1_2_3, &b_D1_2_3);
   fChain->SetBranchAddress("D1_1_3", &D1_1_3, &b_D1_1_3);
   fChain->SetBranchAddress("C1_3_4", &C1_3_4, &b_C1_3_4);
   fChain->SetBranchAddress("D2_4_5", &D2_4_5, &b_D2_4_5);
   fChain->SetBranchAddress("D2_3_5", &D2_3_5, &b_D2_3_5);
   fChain->SetBranchAddress("D2_2_5", &D2_2_5, &b_D2_2_5);
   fChain->SetBranchAddress("D3_5_7", &D3_5_7, &b_D3_5_7);
   fChain->SetBranchAddress("D3_4_7", &D3_4_7, &b_D3_4_7);
   fChain->SetBranchAddress("D3_3_7", &D3_3_7, &b_D3_3_7);
   fChain->SetBranchAddress("D4_5_7", &D4_5_7, &b_D4_5_7);
   fChain->SetBranchAddress("D4_4_7", &D4_4_7, &b_D4_4_7);
   fChain->SetBranchAddress("D4_3_7", &D4_3_7, &b_D4_3_7);
   fChain->SetBranchAddress("kE_dE_R", &kE_dE_R, &b_kE_dE_R);
   fChain->SetBranchAddress("kE_dE_L", &kE_dE_L, &b_kE_dE_L);
   fChain->SetBranchAddress("kE_dE_U", &kE_dE_U, &b_kE_dE_U);
   fChain->SetBranchAddress("kE_dE_D", &kE_dE_D, &b_kE_dE_D);
   Notify();
}

Bool_t TG4reader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TG4reader::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TG4reader::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TG4reader_cxx
