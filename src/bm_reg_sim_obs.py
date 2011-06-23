#! /usr/bin/env python

import subprocess

iterations = 100000
file = open("bm_reg_sim_obs.csv", "w")

file.write("Anzahl Beobachtungen\tGSL Method\tNAG Mathod\n")

for noObs in range(1,10000):
    file.write(str(noObs) + ",\t")
    subprocess.Popen([./test_gsl_reg_sim, -nv, -i, iterations, -foms, -xs, 2, -ys, noObs],
                     stdout=subprocess.PIPE)
    file.write(subprocess.communicate() + "\t")
    subprocess.Popen([./test_nag_reg_sim, -nv, -i, iterations, -foms, -xs, 2, -ys, noObs],
                     stdout=subprocess.PIPE)
    file.write(subprocess.communicate() + "\n")
