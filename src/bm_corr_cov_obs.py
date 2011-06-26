#! /usr/bin/env python

import subprocess
import sys

iterations = 1000
file = open("bm_corr_cov_obs.csv", "w")

file.write("Beobachtungen\tNAG-Funktion\tGSL-Funktion\n")

for noObs in range(10,10000,10):
	if(noObs%100 == 0):
		print "Beobachtungen: " + str(noObs) 
	
	nag_process = subprocess.Popen(['test_corr_cov', '-nv', '-i', str(iterations), '-foms', '-xs', '2', '-ys', str(noObs)], stdout=subprocess.PIPE)
	nag_output = nag_process.communicate()
	
	gsl_process = subprocess.Popen(['test_gsl_corr_cov', '-nv', '-i', str(iterations), '-foms', '-xs', '2', '-ys', str(noObs)], stdout=subprocess.PIPE)
	gsl_output = gsl_process.communicate()
	
	if gsl_output[1] or nag_output[1]:
		print "Fehler!"
		sys.exit(1)
	
	file.write(str(noObs) + "\t" + nag_output[0][:-1] + "\t" + gsl_output[0][:-1] + "\n")
