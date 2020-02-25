from ROOT import TFile, TCanvas
from sys import argv
import os
import imageio


input_file = TFile(argv[1])

spinning_canvas = TCanvas("spinning_canvas", "You Spin Me Right Round", 10, 10, 1024, 768)
distro = input_file.Get(argv[2])


h2d = distro.Projection(2, 3)
h2d.SetTitle("#Delta#varphi #Delta#eta distribution")
h2d.GetYaxis().SetTitle("#Delta#varphi")
h2d.GetXaxis().SetTitle("#Delta#eta")
h2d.Draw("SURF1")

image_list = []

os.system('mkdir spinning_canvas')
for angle in range(180):
    spinning_canvas.SetPhi(2*angle)
    spinning_canvas.SaveAs(f"spinning_canvas/spinning_canvas_{angle}.png")
    image_list.append(imageio.imread(f"spinning_canvas/spinning_canvas_{angle}.png"))

os.system('rm -rf spinning_canvas')
imageio.mimsave("spinning_histo.gif", image_list)