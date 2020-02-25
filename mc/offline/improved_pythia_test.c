#include <tgmath.h>

#define PI 3.14159

//Declaring histograms...
TH1F *pt_dist;
TH1F *phi_dist;
TH1F *eta_dist;
TH1F *delta_phi_dist;
TH1F *delta_eta_dist;
TH2D *dphi_deta_dist;

//Declaring canvases
TCanvas *pt_phi_eta;
TCanvas *delta;
TCanvas *two_dee;

//List of PDG codes to include...(Protons, kaons, pions, electrons)
int include_pdg_list[8] = {211, -211, 2212, -2212, 321, -321, 11, -11};

//Making a particle struct for ease of use...
struct Particle {
    int pdg_code;
    float pt;
    float phi;
    float eta;
};

void setup_histos() {
    pt_dist = new TH1F("pt_dist", "$p_{t}$ distribution", 32, 0, 10);
    phi_dist = new TH1F("phi_dist", "Phi distribution",  32, -PI, PI);
    eta_dist = new TH1F("eta_dist", "Eta distribution", 32, -10, 10);
    delta_phi_dist = new TH1F("delta_phi_dist", "Delta phi distribution", 32, -PI/2, 3*PI/2);
    delta_eta_dist = new TH1F("delta_eta_dist", "Delta eta distribution", 32, -10, 10);
    dphi_deta_dist = new TH2D("dphi_deta_dist", "2-d Delta phi delta eta distribution", 32, -PI/2, 3*PI/2, 32, -10, 10);
}

void setup_canvases() {
    pt_phi_eta = new TCanvas("pt_phi_eta", "Pt, Phi, Eta", 0, 10, 1920, 1080);
    pt_phi_eta->Divide(3, 1);
    delta = new TCanvas("delta", "Two Particle Correlations", 0, 10, 1920, 1080);
    delta->Divide(2, 1);
    two_dee = new TCanvas("two_dee", "2-D Angular Correlations", 0, 10, 1920, 1080);
}

void fill_histograms(std::vector<Particle> particle_list) {
    std::vector<Particle> low_pt_list;
    std::vector<Particle> high_pt_list;
    for(uint i = 0; i < particle_list.size(); i++) {
        Particle part = particle_list[i];
        pt_dist->Fill(part.pt);
        phi_dist->Fill(part.phi);
        eta_dist->Fill(part.eta);
        if(part.pt > 4) high_pt_list.push_back(part);
        if(part.pt > 1 && part.pt < 4) low_pt_list.push_back(part);
    }
    for(uint j = 0; j < high_pt_list.size(); j++){
        Particle high = high_pt_list[j];
        for(uint i = 0; i < low_pt_list.size(); i++) {
            Particle low = low_pt_list[i];
            float delta_eta = high.eta - low.eta;
            float delta_phi = high.phi - low.phi;
            if(delta_phi < -PI/2) delta_phi += 2*PI;
            if(delta_phi > 3*PI/2) delta_phi -= 2*PI;
            delta_phi_dist->Fill(delta_phi);
            delta_eta_dist->Fill(delta_eta);
            delta_eta_dist->Fill(delta_eta);
            dphi_deta_dist->Fill(delta_phi, delta_eta);
        }
    }
}

int improved_pythia_test() {
    
    setup_histos();
    setup_canvases();
    float no, status, mothers, mothers2, daughters2, daughters, colours, colours2, x, y, z, e, m;
    std::string name;
    int id;
    std::vector<Particle> particle_list;

    std::ifstream input_file;
    input_file.open("pythia_out30.txt");

    std::string event_start = "(system)";
    std::string event_end = "Charge sum:";

    bool in_event = false;
    std::string line;

    while (input_file) {

        std::getline(input_file, line);
        if(line.find(event_start) != std::string::npos) in_event = true;
        if(line.find(event_end) != std::string::npos && in_event == true) {
            in_event = false;
            fill_histograms(particle_list);
            particle_list.clear();
        }

        if(in_event) {
            Particle part;
            std::istringstream streamer(line);
            streamer >> no >> id >> name >> status >> mothers >> mothers2 >> daughters >> daughters2 >> colours >> colours2 >> x >> y >> z >> e >> m;
            float pt = sqrt(x*x + y*y);
            float phi = atan2(y, x);
            float p = sqrt(x*x + y*y + z*z);
            float eta = log((p-z)/(p+z))*(-1.0/2.0);
            std::cout << eta << " " << phi << " " << pt << std::endl;
            part.pdg_code = id;
            part.pt = pt;
            part.phi = phi;
            part.eta = eta;
            if(std::find(std::begin(include_pdg_list), std::end(include_pdg_list), part.pdg_code) != std::end(include_pdg_list)) {
                particle_list.push_back(part);
            }
        }
    }

    pt_phi_eta->cd(1);
    pt_dist->Draw();
    pt_phi_eta->cd(2);
    phi_dist->Draw();
    pt_phi_eta->cd(3);
    eta_dist->Draw();
    
    delta->cd(1);
    delta_phi_dist->Draw();
    delta->cd(2);
    delta_eta_dist->Draw();

    two_dee->cd();
    dphi_deta_dist->Draw("surf1");
    
    return 0;
}