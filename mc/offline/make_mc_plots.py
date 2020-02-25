from ROOT import TFile, TCanvas, TList
from sys import argv

input_file = TFile(argv[1])

input_dist_list = ["lk_inJet_Cor",
                    # "lk_outJet_Cor",
                    "lk_Rand_Cor", 
                    # "lh_inJet_Cor",
                    # "lh_outJet_Cor",
                    "lh_Rand_Cor", 
                    # "kk_inJet_Cor",
                    # "kk_outJet_Cor",
                    "kk_Rand_Cor",
                    # "lambdaEvent",
                    # "lambdaEvent_withTrigger",
                    # "kMinusEvent",
                    # "kMinusEvent_withTrigger",
                    # "protonEvent",
                    # "protonEvent_withTrigger",
                    # "pionEvent",
                    # "pionEvent_withTrigger",
                    # "electronEvent",
                    # "electronEvent_withTrigger",
                    # "triggerEvent",
                    "hl_Cor"]

canvas_dict = {}
hist_dict = {}
tlist = input_file.Get("strangeMC")
for index, dist in enumerate(input_dist_list):
    canvas = TCanvas(dist, dist, 10*index, 10*index, 1920, 1080)
    canvas_dict[dist] = canvas
    hist_dict[dist] = tlist.FindObject(dist)


hist_dict["hl_Cor"].GetAxis(0).SetRangeUser(4, 8)
hl_cor_dphi = hist_dict["hl_Cor"].Projection(2).Clone("hl_cor_dphi")
hl_cor_dphi.SetLineColor(1)
hl_cor_dphi.SetTitle("h-#Lambda^{0} #Delta#varphi")
hl_cor_dphi.GetYaxis().SetTitle("d#it{N}_{pairs}/d#it{#Delta#varphi}")
hl_cor_dphi.GetXaxis().SetTitle("#Delta#varphi")
canvas_dict["hl_Cor"].cd()
hl_cor_dphi.Sumw2()
hl_cor_dphi.Draw()

pt_list = [0.15, 0.5, 1, 2, 4, 8, 16]

canvas_dict["lk_Rand_Cor"].Divide(3, 2)
lk_hist_list = [None]*6

for index in range(len(pt_list) - 1):
    hist_dict["lk_Rand_Cor"].GetAxis(0).SetRangeUser(pt_list[index], pt_list[index+1])
    lk_hist_list[index] = hist_dict["lk_Rand_Cor"].Projection(2).Clone(f"hist_list[index]_{index}")
    lk_hist_list[index].SetLineColor(1)
    lk_hist_list[index].SetTitle(f"#Lambda^{{0}} - K^{{+}} #Delta#varphi  ({pt_list[index]} < p_{{T}}(#Lambda)  < {pt_list[index+1]})")
    lk_hist_list[index].GetYaxis().SetTitle("d#it{N}_{pairs}/d#it{#Delta#varphi}")
    lk_hist_list[index].GetXaxis().SetTitle("#Delta#varphi")
    canvas_dict["lk_Rand_Cor"].cd(index+1)
    lk_hist_list[index].Sumw2()
    lk_hist_list[index].Draw()

canvas_dict["kk_Rand_Cor"].Divide(3, 2)
kk_hist_list = [None]*6

for index in range(len(pt_list) - 1):
    hist_dict["kk_Rand_Cor"].GetAxis(0).SetRangeUser(pt_list[index], pt_list[index+1])
    kk_hist_list[index] = hist_dict["kk_Rand_Cor"].Projection(2).Clone(f"hist_list[index]_{index}")
    kk_hist_list[index].SetLineColor(1)
    kk_hist_list[index].SetTitle(f"K^{{-}} - K^{{+}} #Delta#varphi  ({pt_list[index]} < p_{{T}}(K^{{-}})  < {pt_list[index+1]})")
    kk_hist_list[index].GetYaxis().SetTitle("d#it{N}_{pairs}/d#it{#Delta#varphi}")
    kk_hist_list[index].GetXaxis().SetTitle("#Delta#varphi")
    canvas_dict["kk_Rand_Cor"].cd(index+1)
    kk_hist_list[index].Sumw2()
    kk_hist_list[index].Draw()

canvas_dict["lh_Rand_Cor"].Divide(3, 2)
lh_hist_list = [None]*6

for index in range(len(pt_list) - 1):
    hist_dict["lh_Rand_Cor"].GetAxis(0).SetRangeUser(pt_list[index], pt_list[index+1])
    lh_hist_list[index] = hist_dict["lh_Rand_Cor"].Projection(2).Clone(f"hist_list[index]_{index}")
    lh_hist_list[index].SetLineColor(1)
    lh_hist_list[index].SetTitle(f"K^{{-}} - K^{{+}} #Delta#varphi  ({pt_list[index]} < p_{{T}}(K^{{-}})  < {pt_list[index+1]})")
    lh_hist_list[index].GetYaxis().SetTitle("d#it{N}_{pairs}/d#it{#Delta#varphi}")
    lh_hist_list[index].GetXaxis().SetTitle("#Delta#varphi")
    canvas_dict["lh_Rand_Cor"].cd(index+1)
    lh_hist_list[index].Sumw2()
    lh_hist_list[index].Draw()

# kk_rand_cor = hist_dict["lh_Rand_Cor"].Projection(2, 3).Clone("kk_rand_cor")
# kk_rand_cor.SetTitle("h-#Lambda^{0} #Delta#varphi #Delta#eta")
# canvas_dict["kk_Rand_Cor"].cd()
# kk_rand_cor.Sumw2()
# kk_rand_cor.Draw("SURF1")

hist_dict["hl_Cor"].GetAxis(0).SetRangeUser(4, 8)
hl_cor_dphi = hist_dict["hl_Cor"].Projection(2).Clone("hl_cor_dphi")
hl_cor_dphi.SetLineColor(1)
hl_cor_dphi.Rebin(2)
hl_cor_dphi.SetTitle("h-#Lambda^{0} #Delta#varphi")
hl_cor_dphi.GetYaxis().SetTitle("d#it{N}_{pairs}/d#it{#Delta#varphi}")
hl_cor_dphi.GetXaxis().SetTitle("#Delta#varphi")
canvas_dict["hl_Cor"].cd()
hl_cor_dphi.Sumw2()
hl_cor_dphi.Draw()
