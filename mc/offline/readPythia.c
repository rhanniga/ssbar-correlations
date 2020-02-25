#include "readPythia.h"

std::vector<TParticle*> jetFilter(std::vector<TParticle*> tList, std::vector<TParticle*> aList, float coneWidth = pi/6, bool inJet = true) {
    std::vector<TParticle*> filteredList;
    for(int i = 0; i < tList.size(); i++) {
        TParticle *trigger = tList[i];
        for(int j = 0; j < aList.size(); j++) {
            TParticle *associated = aList[j];
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

void makeCor(std::vector<TParticle*> tList, std::vector<TParticle*> aList, THnSparse *sparse){ 


    double data_array[4];
    for(int i = 0; i < tList.size(); i++) {
        TParticle *trigger = tList[i];
        for(int j = 0; j < aList.size(); j++){
            TParticle *associated = aList[j];

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

void writeOut(TString outputFile) {

    TFile *outFile = new TFile(outputFile, "NEW");
    lh_Rand_Cor->Write("lh_Rand_Cor");
    lk_Rand_Cor->Write("lk_Rand_Cor");
    lk_inJet_Cor->Write("lk_inJet_Cor");
    lk_outJet_Cor->Write("lk_outJet_Cor");
    kk_Rand_Cor->Write("kk_Rand_Cor");
    kk_inJet_Cor->Write("kk_inJet_Cor");
    kk_outJet_Cor->Write("kk_outJet_Cor");
    hh_Cor->Write("hh_Cor");
    hl_Cor->Write("hl_Cor");
    hproton_Cor->Write("hproton_Cor");
    hantiProton_Cor->Write("hantiProton_Cor");
    he_Cor->Write("he_Cor");
    hp_Cor->Write("hp_Cor");
    hkPlus_Cor->Write("hkPlus_Cor");
    hkMinus_Cor->Write("hkMinus_Cor");
    hpiPlus_Cor->Write("hpiPlus_Cor");
    hpiMinus_Cor->Write("hpiMinus_Cor");
    triggerEvent->Write("triggerEvent");
    lambdaEvent->Write("lambdaEvent");
    kMinusEvent->Write("kMinusEvent");
    lambdaEvent_withTrigger->Write("lambdaEvent_withTrigger");
    kMinusEvent_withTrigger->Write("kMinusEvent_withTrigger");
    kMinusEvent_withNonKMinusTrigger->Write("kMinusEvent_withNonKMinusTrigger");
    outFile->Close();

}
 
void readPythia(TString inputFile, TString outputFile) {

    //Loading everything
    AliRunLoader* inputRun = AliRunLoader::Open(inputFile);
    int numEvents = inputRun->GetNumberOfEvents();
    inputRun->LoadKinematics();
    inputRun->LoadHeader();

    //Loop through all of the events in the run
    for(int event = 0;  event < numEvents; event++) {

        //Load the stack (contains all of the particles in the event)
        inputRun->GetEvent(event);
        AliStack *theStack = inputRun->Stack();
        int numPrimary = theStack->GetNprimary();

        //Generate particle arrays
        std::vector<TParticle*> lambdaList;
        std::vector<TParticle*> hadronList;
        std::vector<TParticle*> hadronListNoKaon;
        std::vector<TParticle*> assocHadronList;
        std::vector<TParticle*> kPlusList;
        std::vector<TParticle*> kMinusList;
        std::vector<TParticle*> piPlusList;
        std::vector<TParticle*> piMinusList;
        std::vector<TParticle*> protonList;
        std::vector<TParticle*> antiProtonList;
        std::vector<TParticle*> electronList;
        std::vector<TParticle*> positronList;

        for(int part = 0; part < numPrimary; part++) {

            //Load the particle and do something with it
            TParticle *particle = theStack->Particle(part);
            if(std::find(std::begin(charged_pdg_list), std::end(charged_pdg_list), particle->GetPdgCode()) != std::end(charged_pdg_list) && particle->Pt() > 4 && particle->Pt() < 8) {
                hadronList.push_back(particle);
                if(particle->GetPdgCode() != -321) {
                    hadronListNoKaon.push_back(particle);
                }
            }
            if(std::find(std::begin(charged_pdg_list), std::end(charged_pdg_list), particle->GetPdgCode()) != std::end(charged_pdg_list)) {
                assocHadronList.push_back(particle);
            }

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

        //filtering lists for in jet and out of jet comp
        std::vector<TParticle*> inJetLambdaList = jetFilter(hadronList, lambdaList, pi/4, true);
        std::vector<TParticle*> outJetLambdaList = jetFilter(hadronList, lambdaList, pi/4, false);
        std::vector<TParticle*> inJetKaonList = jetFilter(hadronList, kMinusList, pi/4, true);
        std::vector<TParticle*> outJetKaonList = jetFilter(hadronList, kMinusList, pi/4, false);

        //filling correlation distributions
        makeCor(lambdaList, assocHadronList, lh_Rand_Cor);
        makeCor(lambdaList, kPlusList, lk_Rand_Cor);
        makeCor(inJetKaonList, kPlusList, kk_inJet_Cor);
        makeCor(outJetKaonList, kPlusList, kk_outJet_Cor);
        makeCor(kMinusList, kPlusList, kk_Rand_Cor);
        makeCor(inJetLambdaList, kPlusList, lk_inJet_Cor);
        makeCor(outJetLambdaList, kPlusList, lk_outJet_Cor);
        makeCor(hadronList, assocHadronList, hh_Cor);
        makeCor(hadronList, lambdaList, hl_Cor);
        makeCor(hadronList, protonList, hproton_Cor);
        makeCor(hadronList, antiProtonList, hantiProton_Cor);
        makeCor(hadronList, piPlusList, hpiPlus_Cor);
        makeCor(hadronList, piMinusList, hpiMinus_Cor);
        makeCor(hadronList, kPlusList, hkPlus_Cor);
        makeCor(hadronList, kMinusList, hkMinus_Cor);
        makeCor(hadronList, electronList, he_Cor);
        makeCor(hadronList, positronList, hp_Cor);


        //counting number of certain particles in event
        lambdaEvent->Fill(lambdaList.size());
        kMinusEvent->Fill(kMinusList.size());
        triggerEvent->Fill(hadronList.size());

        if(hadronList.size() > 0) {
            kMinusEvent_withTrigger->Fill(kMinusList.size());
            lambdaEvent_withTrigger->Fill(lambdaList.size());
        }
        if(hadronListNoKaon.size() > 0) {
            kMinusEvent_withNonKMinusTrigger->Fill(kMinusList.size());
        }
    }

    writeOut(outputFile);

}