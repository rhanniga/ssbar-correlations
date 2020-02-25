#include "THnSparse.h"

float pi = TMath::Pi();

//list of pdg codes of charged hadrons
int charged_pdg_list[8] = {211, -211, 2212, -2212, 321, -321, 11, -11};

//bin arrangement for usual thnsparse
int bin_array[4] = {12, 12, 32, 32};
double low_array[4] = {0, 0, -pi/2, -4};
double high_array[4] = {12, 12, 3*pi/2, 4};

//thnsparse initializations
THnSparseF *hh_Cor = new THnSparseF("hh_Cor", "hh_Cor", 4, bin_array, low_array, high_array);
THnSparseF *hl_Cor = new THnSparseF("hl_Cor", "hl_Cor", 4, bin_array, low_array, high_array);
THnSparseF *he_Cor = new THnSparseF("he_Cor", "he_Cor", 4, bin_array, low_array, high_array);
THnSparseF *hp_Cor = new THnSparseF("hp_Cor", "hp_Cor", 4, bin_array, low_array, high_array);
THnSparseF *hproton_Cor = new THnSparseF("hproton_Cor", "hproton_Cor", 4, bin_array, low_array, high_array);
THnSparseF *hantiProton_Cor = new THnSparseF("hantiProton_Cor", "hantiProton_Cor", 4, bin_array, low_array, high_array);
THnSparseF *hkPlus_Cor = new THnSparseF("hkPlus_Cor", "hkPlus_Cor", 4, bin_array, low_array, high_array);
THnSparseF *hkMinus_Cor = new THnSparseF("hkMinus_Cor", "hkMinus_Cor", 4, bin_array, low_array, high_array);
THnSparseF *hpiPlus_Cor = new THnSparseF("hpiPlus_Cor", "hpiPlus_Cor", 4, bin_array, low_array, high_array);
THnSparseF *hpiMinus_Cor = new THnSparseF("hpiMinus_Cor", "hpiMinus_Cor", 4, bin_array, low_array, high_array);
THnSparseF *lk_inJet_Cor = new THnSparseF("lk_inJet_Cor", "Lambda-Kaon from Jet Correlation", 4, bin_array, low_array, high_array);
THnSparseF *lk_outJet_Cor = new THnSparseF("lk_outJet_Cor", "Lambda-Kaon out of Jet Correlation", 4, bin_array, low_array, high_array);
THnSparseF *lk_Rand_Cor = new THnSparseF("lk_Rand_Cor", "Random Lambda-Kaon Correlation", 4, bin_array, low_array, high_array);
THnSparseF *lh_Rand_Cor = new THnSparseF("lh_Rand_Cor", "Random Lambda-Hadron Correlation", 4, bin_array, low_array, high_array);
THnSparseF *kk_inJet_Cor = new THnSparseF("kk_inJet_Cor", "Kaon-Kaon from Jet Correlation", 4, bin_array, low_array, high_array);
THnSparseF *kk_outJet_Cor = new THnSparseF("kk_outJet_Cor", "Kaon-Kaon out of Jet Correlation", 4, bin_array, low_array, high_array);
THnSparseF *kk_Rand_Cor = new THnSparseF("kk_Rand_Cor", "Random Kaon-Kaon Correlation", 4, bin_array, low_array, high_array);

//th1d initializations
TH1I *lambdaEvent = new TH1I("lambdaEvent", "Lambdas in Event", 10, 0, 10);
TH1I *lambdaEvent_withTrigger = new TH1I("lambdaEvent_withTrigger", "Lambdas in Event with Trigger", 10, 0, 10);
TH1I *kMinusEvent = new TH1I("kMinusEvent", "K^{-} in Event", 10, 0, 10);
TH1I *kMinusEvent_withTrigger = new TH1I("kMinusEvent_withTrigger", "K^{-} in Event with Trigger", 10, 0, 10);
TH1I *kMinusEvent_withNonKMinusTrigger = new TH1I("kMinusEvent_withNonKMinusTrigger", "K^{-} in Event with Trigger", 10, 0, 10);
TH1I *triggerEvent = new TH1I("triggerEvent", "Triggers in Event", 10, 0, 10);