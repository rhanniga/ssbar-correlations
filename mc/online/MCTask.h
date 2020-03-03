#ifndef MCTask_h
#define MCTask_h

#include <iostream>

#include "AliAnalysisTaskSE.h"
#include "TChain.h"
#include "AliAODEvent.h"
#include "AliAODMCParticle.h"
#include "THnSparse.h"
#include "TString.h"

static float pi = TMath::Pi();
static TString defaultName = "MCTask";

class MCTask : public AliAnalysisTaskSE {
public:

    MCTask(const char *name = defaultName.Data(), float trigPtLow = 4, float trigPtHigh = 8);
    virtual void   UserCreateOutputObjects();
    virtual void   UserExec(Option_t *option);
    virtual void   Terminate(Option_t *);

private:

    int charged_pdg_list[8] = {211, -211, 2212, -2212, 321, -321, 11, -11};

    float triggerPtLow; 
    float triggerPtHigh; 

    AliAODEvent* inputAOD; //! input file
    TList*       outputList; //! output list

    // USER FUNCTION SECTION //
    std::vector<AliAODMCParticle*> JetFilter(std::vector<AliAODMCParticle*> tList, std::vector<AliAODMCParticle*> aList, float coneWidth = pi/4, bool inJet = true);
    void MakeCor(std::vector<AliAODMCParticle*> tList, std::vector<AliAODMCParticle*> aList, THnSparse *sparse);
    void MakeTrigCor(std::vector<AliAODMCParticle*> tList, THnSparse *sparse);
    void MakeTripleCor(std::vector<AliAODMCParticle*> tList, std::vector<AliAODMCParticle*> lList, std::vector<AliAODMCParticle*> kList, THnSparse *sparse);
    void MakeFixedTripleCor(AliAODMCParticle* trigger, std::vector<AliAODMCParticle*> lList, std::vector<AliAODMCParticle*> kList, THnSparse *sparse);

    // CORRELATION HISTOGRAMS //
    THnSparseF *hh_Cor; //! dihadron 
    THnSparseF *hl_Cor; //! hadron lambda
    THnSparseF *he_Cor; //! hadron electron
    THnSparseF *hp_Cor; //! hadron positron
    THnSparseF *hproton_Cor; //! hadron proton
    THnSparseF *hantiProton_Cor; //! hadron aproton
    THnSparseF *hkPlus_Cor; //! hadron kplus
    THnSparseF *hkMinus_Cor; //! hadron kminus
    THnSparseF *hpiPlus_Cor; //! hadron piplus
    THnSparseF *hpiMinus_Cor; //! hadron piminus
    THnSparseF *lk_inJet_Cor; //! lambda-kplus in jet
    THnSparseF *lk_outJet_Cor; //! lambda-kplus out of jet
    THnSparseF *lk_Rand_Cor; //! random lambda-kplus
    THnSparseF *lh_Rand_Cor; //! random lambda-hadron 
    THnSparseF *lh_inJet_Cor; //! in-jet lambda-hadron
    THnSparseF *lh_outJet_Cor; //! out-jet lambda-hadron
    THnSparseF *kk_inJet_Cor; //! kmin-kplus in jet
    THnSparseF *kk_outJet_Cor; //! kmin-kplus out of jet
    THnSparseF *kk_Rand_Cor; //! random kmin-kplus
    THnSparseF *trig_Cor; //! trig-trig correlations
    THnSparseF *triple_Cor; //! trig-trig correlations
    THnSparseF *fixedTriple_Cor; //! trig-trig correlations

    // PARTICLE PER EVENT HISTOGRAMS // 
    TH1I *lambdaEvent; //! counting lambdas per event
    TH1I *lambdaEvent_withTrigger; //! counting lambdas per event w trigger
    TH1I *kMinusEvent; //! counting kminus per event
    TH1I *kMinusEvent_withTrigger; //!counting kminus per event w trigger
    TH1I *protonEvent; //! counting proton per event
    TH1I *protonEvent_withTrigger; //!counting proton per event w trigger
    TH1I *pionEvent; //! counting pion per event
    TH1I *pionEvent_withTrigger; //!counting pion per event w trigger
    TH1I *electronEvent; //! counting e per event
    TH1I *electronEvent_withTrigger; //!counting e per event w trigger
    TH1I *triggerEvent; //! counting trigger per event
   
    ClassDef(MCTask, 3); // example of analysis
};

#endif
