//Homework Problem #3


//#include <iostream>
#include <TMath.h>
#include <stdio.h>
//#include <ifstream.h>
#include <Riostream.h>
#include <iostream>
#include <sstream>

#include <tgmath.h>
#include "TLegend.h"

#include "string"

#define PI 3.14159
int pythia_test(){
    
    // 1) Calculate and plot pt distribution of all pions
    // 2) Calculate and plot phi angle in pt plane of all pions
    // 3)Calculate and plot phi angle difference between high trigger pt particle
    //pt> 4 GeV/c and low pt associated particle 1<pt<4 GeV/c
    // 4) How many particles are in a jet? (jet identification is one particle with pt>4 GeV/c)
    //https://www-cdf.fnal.gov/physics/new/qcd/ue_escan/etaphi.html
    THStack *hs = new THStack("hs","");
    gStyle->SetOptFit(1);
    gStyle->SetOptTitle(1);
    gStyle->SetOptStat(1);
    
    
   
    //create histograms
    
    TH1F *h1 = new TH1F("h1","Pt distribution;x;y",300,-1,10);
    hs->Add(h1);
    
    TH1F *h2 = new TH1F("h2","Phi distribution",300,-3.14,3.14);
    hs->Add(h2);
    
    TH1F *h3 = new TH1F("h3","Delta Phi distribution",200,-PI/2,3*PI/2);
    hs->Add(h3);
    
    TH1F *h4 = new TH1F("h4","Eta distribution",300,-10,10);
    hs->Add(h4);
    
    TH1F *h5 = new TH1F("h5","Delta Eta distribution",200,-10,10);
    hs->Add(h5);
    
    TH1F *h6 = new TH1F("h6","Delta Eta distribution:Version 2",200,-10,10);
    hs->Add(h6);
 
    TH2F *h7 = new TH2F("h7","2d histogram",200,-PI/2,3*PI/2,200,-10,10);
    hs->Add(h7);
    
    //read in file
    ifstream in;
    in.open("pythia_out30.txt");
    
    string name ;
    Double_t no,id , status, mothers , mothers2, daughters2,daughters ,colours,colours2,x ,y ,z ,e, m;//200 total events
    Int_t nlines = 0;
    
    
    //  std::string event_start="PYTHIA Event Listing  (complete event)";
    std::string event_start="no         id  name            status     mothers   daughters     colours      p_x        p_y        p_z         e          m";
    
    //find line with PYTHIA Event Listing  (complete event)
    std::string event_end="Charge sum";
    std:: string file_end="End PYTHIA Error and Warning Messages Statistics";
    string line;

    int event_count = 0;

    while (in)//while the line is NOT the end of file line
    {

        int num_HEP=0;
        int event_num=1;
        int eta_counter=0;
        int phi_counter=0;
        
        
        //Create Arrays for Data
        float_t array_dphi[3000];//delta phi array
        int dphi_count=0;
        
        float_t array_eta[3000];//eta array
        float_t array_phi[3000];//phi array
       
        int h=0;//high energy counter
        float_t array_h[3000];//high energy array
        
        int l=0;//low energy counter
        float_t array_l[3000];//low energy array
        
        float_t arrayl_eta[3000];
        int l_eta=0;//low energy counter
        
        float_t arrayh_eta[3000];
        int h_eta=0 ;//high energy counter

        while(line.find(event_start,0) == std::string::npos && in)//while the line is NOT the start of a Pythia Event
        {
            getline(in, line);
        }
        //now we are at the beginning of a pythia event

        event_count++;
        
        while (line.find(event_end) == std::string::npos && in)
        {//while line does not contain "End PYTHIA Event Listing", the end of the pythia event
            getline(in, line);
            cout << line << endl;
            std::istringstream test(line);
            test >> no >> id >> name >> status >> mothers >> mothers2 >> daughters >> daughters2 >> colours >> colours2 >> x >> y >> z >> e >> m;
            //toss data into arrays
            
            if(name=="pi+" || name=="pi-"|| name=="K*+"|| name=="K*-"|| name=="p+"|| name=="p-"|| name=="(p+)"|| name=="(p-)"||name=="(e+)"|| name=="(e-)")//k+ K- pi+ pi- protons antiprotons electrons positrons.....
            {
                float px=x;
                float py=y;
                float pz=z;
                float Pt=sqrt((px*px)+(py*py));
                float P_tot=sqrt((px*px)+(py*py)+(pz*pz));
                float phi=atan2(py,px);//https://www-cdf.fnal.gov/physics/new/qcd/ue_escan/etaphi.html
                
                float eta=log((P_tot-pz)/(P_tot+pz))*(-1.0/2.0);
                
                array_eta[eta_counter]=eta;
                eta_counter++;
                
                array_phi[phi_counter]=phi;
                phi_counter++;
                
                h1->Fill(Pt);
                h2->Fill(phi);
                h4->Fill(eta);
                
                
                //sort into arrays
                if(Pt>4)
                {//pt> 4 GeV/c
                    array_h[h]=atan2(py,px);//have to do px and py, not pt
                    h++;
                    
                    arrayh_eta[h_eta]=eta;
                    h_eta++;
                    
                    num_HEP++;
                }
                if(Pt<4 && Pt>1)
                {//low pt associated particle 1<pt<4 GeV/c
                    array_l[l]=atan2(py,px);
                    
                    arrayl_eta[l_eta]=eta;
                    l_eta++;
                    
                    l++;
                }
                
            }//end if name statement
            
        }//end while loop, meaning it is the end of the event
        
        
        //loop through eta array
        int k=0;
        
        for(int i=0;i<eta_counter;i++)
        {
            for(int j=0;j<eta_counter;j++)
            {
                float delta_eta=array_eta[i]-array_eta[j];
                h5->Fill(delta_eta);
            }
        }
        
        for(int i=0;i<h;i++)
        {
            for(int j=0;j<l;j++)
            {
                float delta_phi=array_h[i]-array_l[j];
                
                float delta_eta=(arrayh_eta[i]-arrayl_eta[j]);
                h6->Fill(delta_eta);
                
                if(delta_phi<(-PI/2))
                {
                    delta_phi+=2*PI;
                }
                if (delta_phi>(3*(PI/2)))
                {
                    delta_phi=delta_phi-(2*PI);
                }
                
                
                h3->Fill(delta_phi);
                h7->Fill(delta_phi,delta_eta);
            }
        }
    }//end while loop that goes through all the events
    
    
    //       h3->Rebin(20);
    //       h7->Rebin(20);
    //       h4->Rebin(20);
    //       h6->Rebin2D(2,2);
    //find number of particles in jet
    //    int maxbin = h3->GetMaximumBin();
    //    double histerror;
    //    double integral=h3->IntegralAndError(maxbin,maxbin, histerror);
    //    cout<<"Integral Error "<<histerror<<endl;
    //    float num_particles=num_HEP+integral;
    //    float num_particles_err=sqrt(((histerror)*(histerror))+(num_particles));
    //    cout<<"Num HEP Error "<<sqrt(num_particles)<<endl;
    // cout<< "Number of Particles in the Jet: "<<num_particles<< "+/-"<< num_particles_err<<endl;
    // cout << "Estimated Error of Integral"<<fIntegrator->Error();
    

    TCanvas *c2 = new TCanvas("c2", "c2",0,0,400,400);
    c2->SetFillColor(10);
    c2->SetBorderMode(0);
    
    
    c2->cd(1);
    gPad->SetLogz();
    h7->SetYTitle ("Delta Eta");
    h7->SetXTitle ("Delta Phi");
    h7->Draw("surf1");
 
    
    //NEW CANVAS
    TCanvas *c3 = new TCanvas("c3", "c3",0,0,400,400);
    c3->SetFillColor(10);
    c3->SetBorderMode(0);
    c3->Divide(6,1);

    c3->cd(1);
    h1->SetLineColor(2);
    h1->Draw();
    auto legend = new TLegend(0.1,0.8,0.4,0.9);
    legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
    legend->AddEntry(h1,"Pt");
    legend->Draw();
    
    c3->cd(2);
    h2->Draw();
    auto legend2 = new TLegend(0.1,0.8,0.4,0.9);
    legend2->SetHeader("The Legend Title","C"); // option "C" allows to center the header
    legend2->AddEntry(h1,"Pt");
    legend2->Draw();
    //        myfit->Draw("SAME");
    c3->cd(3);
    h3->Draw();
    
    auto legend3 = new TLegend(0.1,0.8,0.4,0.9);
    legend3->SetHeader("The Legend Title","C"); // option "C" allows to center the header
    legend3->AddEntry(h1,"Pt");
    
    legend3->Draw();
    
    c3->cd(4);
    h4->Draw();
    
    c3->cd(5);
    h5->Draw();
    
    
    c3->cd(6);
    h6->Draw();
    
    std::cout << event_count << " is the event count\n";
    return 0;
}
