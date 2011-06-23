#! /usr/bin/env python

import subprocess
import sys

iterations = 1000
file = open("bm_reg_sim_obs.csv", "w")

file.write("Anzahl Beobachtungen\tGSL Method\tNAG Method\n")

for noObs in range(10,10000,10):
    if(noObs%100 == 0):
        print str(noObs) + " Beobachtungen werden getestet"
    
    gsl_process = subprocess.Popen(['test_gsl_reg_sim', '-nv', '-i', str(iterations), '-foms', '-xs', '2', '-ys', str(noObs)],
                               stdout=subprocess.PIPE)
    gsl_output = gsl_process.communicate()

    nag_process = subprocess.Popen(['test_reg_sim', '-nv', '-i', str(iterations), '-foms', '-xs', '2', '-ys', str(noObs)],
                               stdout=subprocess.PIPE)
    nag_output = nag_process.communicate()

    if gsl_output[1] or nag_output[1]:
        print "There was an error!"
        sys.exit(1)

    file.write(str(noObs) + "\t" + gsl_output[0][:-1] + "\t" + nag_output[0][:-1] + "\n")
