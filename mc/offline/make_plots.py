from ROOT import TFile, TCanvas
from sys import argv

input_file = TFile(argv[1])

canvas_name_list = ["hh_canvas", "he_canvas", "hp_canvas", "hproton_canvas", "hanti-proton_canvas", "hkplus_canvas", "hkminus_canvas", "hpiplus_canvas", "hpiminus_canvas"]
canvas_list = []
for index, canvas_name in enumerate(canvas_name_list):
    canvas = TCanvas(canvas_name, canvas_name, 10*index, 10*index, 1024, 768)
    canvas_list.append(canvas)


kk_canvas = TCanvas("kk_canvas", "K^{-}-K^{+} canvas", 0, 10, 1920, 1080)
lk_canvas = TCanvas("lk_canvas", "#Lambda^{0}-K^{+} canvas", 0, 10, 1920, 1080)
kk_canvas.Divide(3, 1)
lk_canvas.Divide(3, 1)

hh_dist = input_file.Get("hh_Cor")
he_dist = input_file.Get("he_Cor")
hp_dist = input_file.Get("hp_Cor")
hproton_dist = input_file.Get("hproton_Cor")
hantiproton_dist = input_file.Get("hantiProton_Cor")
hkplus_dist = input_file.Get("hkPlus_Cor")
hkminus_dist = input_file.Get("hkMinus_Cor")
hpiplus_dist = input_file.Get("hpiPlus_Cor")
hpiminus_dist = input_file.Get("hpiMinus_Cor")

hh_dist.GetAxis(1).SetRangeUser(0, 4)
he_dist.GetAxis(1).SetRangeUser(0, 4)
hp_dist.GetAxis(1).SetRangeUser(0, 4)
hproton_dist.GetAxis(1).SetRangeUser(0, 4)
hantiproton_dist.GetAxis(1).SetRangeUser(0, 4)
hkplus_dist.GetAxis(1).SetRangeUser(0, 4)
hkminus_dist.GetAxis(1).SetRangeUser(0, 4)
hpiplus_dist.GetAxis(1).SetRangeUser(0, 4)
hpiminus_dist.GetAxis(1).SetRangeUser(0, 4)

canvas_list[0].cd()
hh_dist.Projection(2).Draw()
canvas_list[1].cd()
he_dist.Projection(2).Draw()
canvas_list[2].cd()
hp_dist.Projection(2).Draw()
canvas_list[3].cd()
hproton_dist.Projection(2).Draw()
canvas_list[4].cd()
hantiproton_dist.Projection(2).Draw()
canvas_list[5].cd()
hkplus_dist.Projection(2).Draw()
canvas_list[6].cd()
hkminus_dist.Projection(2).Draw()
canvas_list[7].cd()
hpiplus_dist.Projection(2).Draw()
canvas_list[8].cd()
hpiminus_dist.Projection(2).Draw()

kk_random_dist = input_file.Get("kk_Rand_Cor")
kk_injet_dist = input_file.Get("kk_inJet_Cor")
kk_outjet_dist = input_file.Get("kk_outJet_Cor")

lk_random_dist = input_file.Get("lk_Rand_Cor")
lk_injet_dist = input_file.Get("lk_inJet_Cor")
lk_outjet_dist = input_file.Get("lk_outJet_Cor")

kk_rand_dphi = kk_random_dist.Projection(2, 3)
kk_injet_dphi = kk_injet_dist.Projection(2, 3)
kk_outjet_dphi = kk_outjet_dist.Projection(2, 3)
lk_rand_dphi = lk_random_dist.Projection(2, 3)
lk_injet_dphi = lk_injet_dist.Projection(2, 3)
lk_outjet_dphi = lk_outjet_dist.Projection(2, 3)

# kk_canvas.cd(1)
# kk_rand_dphi.Draw("SURF1")
# kk_canvas.cd(2)
# kk_injet_dphi.Draw("SURF1")
# kk_canvas.cd(3)
# kk_outjet_dphi.Draw("SURF1")

# lk_canvas.cd(1)
# lk_rand_dphi.Draw("SURF1")
# lk_canvas.cd(2)
# lk_injet_dphi.Draw("SURF1")
# lk_canvas.cd(3)
# lk_outjet_dphi.Draw("SURF1")