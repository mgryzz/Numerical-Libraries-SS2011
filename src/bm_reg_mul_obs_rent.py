#! /usr/bin/env python

import subprocess
import sys

iterations = 100
indVars = 6 # Anzahl unabhÅ‰ngiger Variablen
file = open("bm_reg_mul_obs_fair_rent.csv", "w")

file.write("Anzahl Beobachtungen\tGSL Method\tNAG Method\n")

for noObs in range(10,2500,10):
    if(noObs%100 == 0):
        print str(noObs) + " Beobachtungen werden getestet"
    
    gsl_process = subprocess.Popen(['test_gsl_reg_mul_fair', '-nv', '-i', str(iterations), '-foms', '-f', 'data/miete03.asc', '-xs', '13', '-ys', str(noObs), '-ip', str(indVars)],
                                   stdout=subprocess.PIPE)
    gsl_output = gsl_process.communicate()

    nag_process = subprocess.Popen(['test_reg_mul', '-nv', '-i', str(iterations), '-foms', '-f', 'data/miete03.asc', '-xs', '13', '-ys', str(noObs), '-ip', str(indVars)],
                                   stdout=subprocess.PIPE)
    nag_output = nag_process.communicate()

    if gsl_output[1] or nag_output[1]:
        print "There was an error!"
        sys.exit(1)

    file.write(str(noObs) + "\t" + gsl_output[0][:-1] + "\t" + nag_output[0][:-1] + "\n")
