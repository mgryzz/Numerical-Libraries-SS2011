#! /usr/bin/env python

import subprocess
import sys

iterations = 100
obs = 2500 # Anzahl unabhängiger Variablen
file = open("bm_reg_mul_vars_fair.csv", "w")

file.write("Anzahl Variablen\tGSL Method\tNAG Method\n")

for vars in range(1,13):
    #if(noObs%100 == 0):
    print str(vars) + " Variablen werden getestet"
    
    gsl_process = subprocess.Popen(['test_gsl_reg_mul_fair', '-nv', '-i', str(iterations), '-foms', '-f', 'data/miete03.asc', '-xs', '50', '-ys', str(obs), '-ip', str(vars)],
                                   stdout=subprocess.PIPE)
    gsl_output = gsl_process.communicate()

    nag_process = subprocess.Popen(['test_reg_mul', '-nv', '-i', str(iterations), '-foms', '-f', 'data/miete03.asc', '-xs', '50', '-ys', str(obs), '-ip', str(vars)],
                                   stdout=subprocess.PIPE)
    nag_output = nag_process.communicate()

    if gsl_output[1] or nag_output[1]:
        print "There was an error!"
        sys.exit(1)

    file.write(str(vars) + "\t" + gsl_output[0][:-1] + "\t" + nag_output[0][:-1] + "\n")
