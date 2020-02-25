#include "MCTask.h"

ClassImp(MCTask);

MCTask::MCTask(const char *name,  float trigPtLow, float trigPtHigh)
: AliAnalysisTaskSE(name),
inputAOD(0),
outputList(0)
{
    DefineInput(0, TChain::Class());
    DefineOutput(1, TList::Class());
    triggerPtLow = trigPtLow;
    triggerPtHigh = trigPtHigh;
}

void MCTask::UserCreateOutputObjects(){

    // Define bin arrays for THnSparses
    int bin_array[4]        = {120, 120, 32, 32};
    double low_array[4]     = {0, 0, -pi/2, -4};
    double high_array[4]    = {12, 12, 3*pi/2, 4};

    int triple_cor_bin_array[6] = {12, 120, 16, 120, 32, 32};
    double triple_cor_low_array[6] = {0, 0, -pi/2, 0, -pi/2, -4};
    double triple_cor_high_array[6] = {12, 12, 3*pi/2, 12, 3*pi/2, 4};

    // Initialize correlation histograms
    hh_Cor            = new THnSparseF("hh_Cor", "hh_Cor", 4, bin_array, low_array, high_array);
    hl_Cor            = new THnSparseF("hl_Cor", "hl_Cor", 4, bin_array, low_array, high_array);
    he_Cor            = new THnSparseF("he_Cor", "he_Cor", 4, bin_array, low_array, high_array);
    hp_Cor            = new THnSparseF("hp_Cor", "hp_Cor", 4, bin_array, low_array, high_array);
    hproton_Cor       = new THnSparseF("hproton_Cor", "hproton_Cor", 4, bin_array, low_array, high_array);
    hantiProton_Cor   = new THnSparseF("hantiProton_Cor", "hantiProton_Cor", 4, bin_array, low_array, high_array);
    hkPlus_Cor        = new THnSparseF("hkPlus_Cor", "hkPlus_Cor", 4, bin_array, low_array, high_array);
    hkMinus_Cor       = new THnSparseF("hkMinus_Cor", "hkMinus_Cor", 4, bin_array, low_array, high_array);
    hpiPlus_Cor       = new THnSparseF("hpiPlus_Cor", "hpiPlus_Cor", 4, bin_array, low_array, high_array);
    hpiMinus_Cor      = new THnSparseF("hpiMinus_Cor", "hpiMinus_Cor", 4, bin_array, low_array, high_array);
    lk_inJet_Cor      = new THnSparseF("lk_inJet_Cor", "Lambda-Kaon from Jet Correlation", 4, bin_array, low_array, high_array);
    lk_outJet_Cor     = new THnSparseF("lk_outJet_Cor", "Lambda-Kaon out of Jet Correlation", 4, bin_array, low_array, high_array);
    lk_Rand_Cor       = new THnSparseF("lk_Rand_Cor", "Random Lambda-Kaon Correlation", 4, bin_array, low_array, high_array);
    lh_inJet_Cor      = new THnSparseF("lh_inJet_Cor", "inJet Lambda-Hadron Correlation", 4, bin_array, low_array, high_array);
    lh_outJet_Cor     = new THnSparseF("lh_outJet_Cor", "outJet Lambda-Hadron Correlation", 4, bin_array, low_array, high_array);
    lh_Rand_Cor       = new THnSparseF("lh_Rand_Cor", "Random Lambda-Hadron Correlation", 4, bin_array, low_array, high_array);
    kk_inJet_Cor      = new THnSparseF("kk_inJet_Cor", "Kaon-Kaon from Jet Correlation", 4, bin_array, low_array, high_array);
    kk_outJet_Cor     = new THnSparseF("kk_outJet_Cor", "Kaon-Kaon out of Jet Correlation", 4, bin_array, low_array, high_array);
    kk_Rand_Cor       = new THnSparseF("kk_Rand_Cor", "Random Kaon-Kaon Correlation", 4, bin_array, low_array, high_array);
    trig_Cor          = new THnSparseF("trig_Cor", "Trigger-trigger correlation", 4, bin_array, low_array, high_array);
    triple_Cor        = new THnSparseF("triple_Cor", "Triple correlation", 4, triple_cor_bin_array, triple_cor_low_array, triple_cor_high_array);
    fixedTriple_Cor   = new THnSparseF("fixedTriple_Cor", "Fixed trigger triple correlation", 4, triple_cor_bin_array, triple_cor_low_array, triple_cor_high_array);

    // Particle per event distributions
    lambdaEvent               = new TH1I("lambdaEvent", "Lambdas in Event", 10, 0, 10);
    lambdaEvent_withTrigger   = new TH1I("lambdaEvent_withTrigger", "Lambdas in Event with Trigger", 10, 0, 10);
    kMinusEvent               = new TH1I("kMinusEvent", "K^{-} in Event", 10, 0, 10);
    kMinusEvent_withTrigger   = new TH1I("kMinusEvent_withTrigger", "K^{-} in Event with Trigger", 10, 0, 10);
    protonEvent               = new TH1I("protonEvent", "p in Event", 10, 0, 10);
    protonEvent_withTrigger   = new TH1I("protonEvent_withTrigger", "p in Event with Trigger", 10, 0, 10);
    electronEvent             = new TH1I("electronEvent", "e in Event", 20, 0, 20);
    electronEvent_withTrigger = new TH1I("electronEvent_withTrigger", "e in Event with Trigger", 20, 0, 20);
    pionEvent                 = new TH1I("pionEvent", "#pi^{+} in Event", 20, 0, 20);
    pionEvent_withTrigger     = new TH1I("pionEvent_withTrigger", "#pi^{+} in Event with Trigger", 20, 0, 20);
    triggerEvent              = new TH1I("triggerEvent", "Triggers in Event", 10, 0, 10);

    //Add to output list
    outputList = new TList();
    outputList->SetOwner();
    outputList->Add(hh_Cor);
    outputList->Add(hl_Cor); 
    outputList->Add(he_Cor); 
    outputList->Add(hp_Cor); 
    outputList->Add(hproton_Cor);
    outputList->Add(hantiProton_Cor);
    outputList->Add(hkPlus_Cor);
    outputList->Add(hkMinus_Cor);
    outputList->Add(hpiPlus_Cor);
    outputList->Add(hpiMinus_Cor);
    outputList->Add(lk_inJet_Cor);
    outputList->Add(lk_outJet_Cor);
    outputList->Add(lk_Rand_Cor);
    outputList->Add(lh_inJet_Cor);
    outputList->Add(lh_outJet_Cor);
    outputList->Add(lh_Rand_Cor);
    outputList->Add(kk_inJet_Cor);
    outputList->Add(kk_outJet_Cor);
    outputList->Add(kk_Rand_Cor);
    outputList->Add(trig_Cor);
    outputList->Add(triple_Cor);
    outputList->Add(fixedTriple_Cor);
    outputList->Add(lambdaEvent);
    outputList->Add(lambdaEvent_withTrigger);
    outputList->Add(kMinusEvent);
    outputList->Add(kMinusEvent_withTrigger);
    outputList->Add(pionEvent);
    outputList->Add(pionEvent_withTrigger);
    outputList->Add(protonEvent);
    outputList->Add(protonEvent_withTrigger);
    outputList->Add(electronEvent);
    outputList->Add(electronEvent_withTrigger);
    outputList->Add(triggerEvent);

    PostData(1, outputList);
}

std::vector<AliAODMCParticle*> MCTask::JetFilter(std::vector<AliAODMCParticle*> tList, std::vector<AliAODMCParticle*> aList, float coneWidth, bool inJet) {
    std::vector<AliAODMCParticle*> filteredList;
    for(uint i = 0; i < tList.size(); i++) {
        AliAODMCParticle *trigger = tList[i];
        for(uint j = 0; j < aList.size(); j++) {
            AliAODMCParticle *associated = aList[j];
            float deltaPhi = trigger->Phi() - associated->Phi();
            if(deltaPhi < -pi) deltaPhi += 2*pi;
            else if(deltaPhi > pi) deltaPhi -= 2*pi;
            if(inJet) {
                if(TMath::Abs(deltaPhi) < coneWidth) filteredList.push_back(associated);
            }
            else {
                if((TMath::Abs(deltaPhi) > coneWidth) && (TMath::Abs(deltaPhi) < pi-coneWidth)) filteredList.push_back(associated);
            }
        }
    }
    return filteredList;
}

void MCTask::MakeTripleCor(std::vector<AliAODMCParticle*> tList, std::vector<AliAODMCParticle*> lList, std::vector<AliAODMCParticle*> kList, THnSparse *sparse){ 

    double data_array[6];

    for(uint i = 0; i < tList.size(); i++) {

        AliAODMCParticle *trigger = tList[i];

        data_array[0] = trigger->Pt();

        for(uint j = 0; j < lList.size(); j++){

            AliAODMCParticle *lambda = lList[j];

            data_array[1] = lambda->Pt();

            data_array[2] = trigger->Phi() - lambda->Phi();
            if(data_array[2] < -pi/2) data_array[2] += 2*pi;
            else if(data_array[2] > 3*pi/2) data_array[2] -= 2*pi;

            for(uint k = 0; k < kList.size(); k++){

                AliAODMCParticle *kaon = kList[k];

                data_array[3] = kaon->Pt();

                data_array[4] = lambda->Phi() - kaon->Phi();
                if(data_array[4] < -pi/2) data_array[4] += 2*pi;
                else if(data_array[4] > 3*pi/2) data_array[4] -= 2*pi;

                data_array[5] = lambda->Eta() - kaon->Eta();

                sparse->Fill(data_array);
            }
        }
    }
}

void MCTask::MakeFixedTripleCor(AliAODMCParticle* trigger, std::vector<AliAODMCParticle*> lList, std::vector<AliAODMCParticle*> kList, THnSparse *sparse){ 

    double data_array[6];

    data_array[0] = trigger->Pt();

    for(uint j = 0; j < lList.size(); j++){

        AliAODMCParticle *lambda = lList[j];

        data_array[1] = lambda->Pt();

        data_array[2] = trigger->Phi() - lambda->Phi();
        if(data_array[2] < -pi/2) data_array[2] += 2*pi;
        else if(data_array[2] > 3*pi/2) data_array[2] -= 2*pi;

        for(uint k = 0; k < kList.size(); k++){

            AliAODMCParticle *kaon = kList[k];

            data_array[3] = kaon->Pt();

            data_array[4] = lambda->Phi() - kaon->Phi();
            if(data_array[4] < -pi/2) data_array[4] += 2*pi;
            else if(data_array[4] > 3*pi/2) data_array[4] -= 2*pi;

            data_array[5] = lambda->Eta() - kaon->Eta();

            sparse->Fill(data_array);
        }
    }
}

void MCTask::MakeCor(std::vector<AliAODMCParticle*> tList, std::vector<AliAODMCParticle*> aList, THnSparse *sparse){ 
    double data_array[4];
    for(uint i = 0; i < tList.size(); i++) {
        AliAODMCParticle *trigger = tList[i];
        for(uint j = 0; j < aList.size(); j++){
            AliAODMCParticle *associated = aList[j];

            data_array[0] = trigger->Pt();
            data_array[1] = associated->Pt();

            data_array[2] = trigger->Phi() - associated->Phi();
            if(data_array[2] < -pi/2) data_array[2] += 2*pi;
            else if(data_array[2] > 3*pi/2) data_array[2] -= 2*pi;

            data_array[3] = trigger->Eta() - associated->Eta();

            sparse->Fill(data_array);
        }
    }
}

void MCTask::MakeTrigCor(std::vector<AliAODMCParticle*> tList, THnSparse *sparse){ 
    double data_array[4];
    for(uint i = 0; i < tList.size(); i++) {
        AliAODMCParticle *trigger1 = tList[i];
        for(uint j = i+1; j < tList.size(); j++){
            AliAODMCParticle *trigger2 = tList[j];

            data_array[0] = trigger1->Pt();
            data_array[1] = trigger2->Pt();

            data_array[2] = trigger1->Phi() - trigger2->Phi();
            if(data_array[2] < -pi/2) data_array[2] += 2*pi;
            else if(data_array[2] > 3*pi/2) data_array[2] -= 2*pi;

            data_array[3] = trigger1->Eta() - trigger2->Eta();

            sparse->Fill(data_array);
        }
    }
}

void MCTask::UserExec(Option_t *){
    inputAOD = dynamic_cast<AliAODEvent*>(InputEvent());

    // Counter of particles within acceptance, reject event if it's less than 2
    int acceptedParticleCount = 0;

    // Lists of relevant particles to be used for various things
    std::vector<AliAODMCParticle*> triggerList;
    std::vector<AliAODMCParticle*> assocHadronList;
    std::vector<AliAODMCParticle*> kPlusList;
    std::vector<AliAODMCParticle*> kMinusList;
    std::vector<AliAODMCParticle*> piPlusList;
    std::vector<AliAODMCParticle*> piMinusList;
    std::vector<AliAODMCParticle*> protonList;
    std::vector<AliAODMCParticle*> antiProtonList;
    std::vector<AliAODMCParticle*> electronList;
    std::vector<AliAODMCParticle*> positronList;
    std::vector<AliAODMCParticle*> lambdaList;

    TClonesArray* stack = dynamic_cast<TClonesArray*>(inputAOD->FindListObject(AliAODMCParticle::StdBranchName()));
    for(int ipart=0; ipart< stack->GetEntries(); ipart++){
                AliAODMCParticle *particle = (AliAODMCParticle*)stack->At(ipart);
                if(!particle->IsPhysicalPrimary()) continue;
                if(particle->Pt() < 0.15) continue;
                if(TMath::Abs(particle->Eta()) > 1) continue;
                int pdgCode = particle->GetPdgCode();
                acceptedParticleCount++;
                
                bool isChargedHadron = std::find(std::begin(charged_pdg_list), std::end(charged_pdg_list), particle->GetPdgCode()) != std::end(charged_pdg_list);
                bool isTriggerPt = particle->Pt() > triggerPtLow && particle->Pt() < triggerPtHigh;

                if(isChargedHadron && isTriggerPt) triggerList.push_back(particle);
                if(isChargedHadron) assocHadronList.push_back(particle);
            
                switch(particle->GetPdgCode()) {
                    case 211: piPlusList.push_back(particle);
                        break;
                    case -211: piMinusList.push_back(particle);
                        break;
                    case 321: kPlusList.push_back(particle);
                        break;
                    case -321: kMinusList.push_back(particle);
                        break;
                    case 11: electronList.push_back(particle);
                        break;
                    case -11: positronList.push_back(particle);
                        break;
                    case 2212: protonList.push_back(particle);
                        break;
                    case -2212: antiProtonList.push_back(particle);
                        break;
                    case 3122: lambdaList.push_back(particle);
                        break;
                }
    }

    // Do nothing if less than two particles in acceptence
    if(acceptedParticleCount < 2) return;

    // Filter lambdas/kaons that lie within certain dphi of trigger
    std::vector<AliAODMCParticle*> inJetLambdaList = JetFilter(triggerList, lambdaList, pi/4, true);
    std::vector<AliAODMCParticle*> outJetLambdaList = JetFilter(triggerList, lambdaList, pi/4, false);
    std::vector<AliAODMCParticle*> inJetKaonList = JetFilter(triggerList, kMinusList, pi/4, true);
    std::vector<AliAODMCParticle*> outJetKaonList = JetFilter(triggerList, kMinusList, pi/4, false);

    // Make correlations
    MakeCor(lambdaList, assocHadronList, lh_Rand_Cor);
    MakeCor(inJetLambdaList, assocHadronList, lh_inJet_Cor);
    MakeCor(outJetLambdaList, assocHadronList, lh_outJet_Cor);
    MakeCor(inJetKaonList, kPlusList, kk_inJet_Cor);
    MakeCor(outJetKaonList, kPlusList, kk_outJet_Cor);
    MakeCor(kMinusList, kPlusList, kk_Rand_Cor);
    MakeCor(inJetLambdaList, kPlusList, lk_inJet_Cor);
    MakeCor(outJetLambdaList, kPlusList, lk_outJet_Cor);
    MakeCor(lambdaList, kPlusList, lk_Rand_Cor);
    MakeCor(triggerList, assocHadronList, hh_Cor);
    MakeCor(triggerList, lambdaList, hl_Cor);
    MakeCor(triggerList, protonList, hproton_Cor);
    MakeCor(triggerList, antiProtonList, hantiProton_Cor);
    MakeCor(triggerList, piPlusList, hpiPlus_Cor);
    MakeCor(triggerList, piMinusList, hpiMinus_Cor);
    MakeCor(triggerList, kPlusList, hkPlus_Cor);
    MakeCor(triggerList, kMinusList, hkMinus_Cor);
    MakeCor(triggerList, electronList, he_Cor);
    MakeCor(triggerList, positronList, hp_Cor);
    MakeTrigCor(triggerList, trig_Cor);

    MakeTripleCor(triggerList, lambdaList, kPlusList, triple_Cor);
    if(triggerList.size() == 1) {
        MakeFixedTripleCor(triggerList[0], lambdaList, kPlusList, triple_Cor);
    }

    // Count number of triggers/lambdas/kaons in event
    lambdaEvent->Fill(lambdaList.size());
    kMinusEvent->Fill(kMinusList.size());
    triggerEvent->Fill(triggerList.size());
    protonEvent->Fill(protonList.size());
    pionEvent->Fill(piPlusList.size());
    electronEvent->Fill(electronList.size());

    if(triggerList.size() > 0) {
        kMinusEvent_withTrigger->Fill(kMinusList.size());
        lambdaEvent_withTrigger->Fill(lambdaList.size());
        protonEvent_withTrigger->Fill(protonList.size());
        pionEvent_withTrigger->Fill(piPlusList.size());
        electronEvent_withTrigger->Fill(electronList.size());
    }
}

void MCTask::Terminate(Option_t *) 
{
    printf("terminating task... \n");
    outputList = dynamic_cast<TList*> (GetOutputData(1));
    if (!outputList) {
        printf("ERROR: Output list not available\n");
        return;
    }    
}