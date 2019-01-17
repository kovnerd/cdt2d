# -*- coding: utf-8 -*-
"""
Created on Fri Jun 23 12:55:40 2017

@author: kovnerd
"""

import stats
import plot_data as pltd
import pandas as pd 
pd.set_option('display.mpl_style', 'default') # Make the graphs a bit prettier
import numpy as np
import os, errno

sim_type = "gb"
ext = ".txt"

dir = os.path.dirname(__file__)
data_path = os.path.join(os.path.join(dir, '../'), 'data_files')
out_path = os.path.join(os.path.join(dir, '../'), 'plots/' + sim_type)
try:
    os.makedirs(out_path)
except OSError as e:
    if e.errno != errno.EEXIST:
        raise


sigmas = []
n_bootstrap = 100
info = pd.read_table(os.path.join(os.path.join(data_path,"sim_details_" + sim_type + ext)), sep = ' ', header = None, lineterminator = '\n')
cosmo = float(info[1][0])
N_fix = int(info[1][1])
TIME = int(info[1][2])
num_cor = int(info[1][3])
num_config = int(info[1][4])
sigma_min = int(info[1][5])
sigma_max = int(info[1][6])
num_points = int(info[1][7])
inc = int((sigma_max - sigma_min)/num_points)


for sigma in range(sigma_min, sigma_max, inc):
    sigmas.append(float(sigma));
sigmas = np.asarray(sigmas)

print "SIGMAS:"
print sigmas
print "\n"

def spec_dim(return_probs):
    derv = stats.deriv(return_probs, sigmas)
    div = np.divide(sigmas, return_probs)
    spec_dims = -2 * np.append(derv, 0.) * div
    
    #too big
    #spec_dims = -2 * sigmas * np.append(stats.deriv(np.log(return_probs), np.log(sigmas)), 0)
    
    #also too big
    #spec_dims = -2*sigmas*(np.subtract(np.append(np.divide(return_probs[1:], return_probs[:-1]), 0) , 1))
   
    return spec_dims

def vol_dist():
    #parse epsilon_check_2d.txt
   
    N_2s = pd.read_table(os.path.join(os.path.join(data_path,"vol_dist_" + sim_type + ext)), sep = ' ', header = None, lineterminator = '\n')
    #calculate stdev and mean of dist
    #print "N_2s IN ENSEMBLE AS AN ARRAY:\n"
    #print N_2s.values
    avN_2 = stats.avg(N_2s.values)
    stdN_2 = stats.sdev(N_2s.values)
    N_2array = N_2s.values.flatten()
    print "AVERAGE N_2 OVER ENSEMBLE: " + str(avN_2[0])
    print "STDEV OVER ENSEMBLE: " + str(stdN_2[0])
    print "\n"
    #plot distribution
    epsilon_fig = pltd.make_plot(N_2s.values, r'Binned Histogram of $N_2s$ from $\epsilon = 0.02$', r'$N_2$', r'counts') 
    pltd.save_plot(epsilon_fig, 'vol_dist_' + sim_type + '.pdf', out_path)

def slice_dist(): #fix parsing
    slices = pd.read_table(os.path.join(os.path.join(data_path,"slice_dist_" + sim_size + ext)), sep = ' ', header = None, lineterminator = '\n')
    slices.drop(slices.columns[-1], axis = 1, inplace = True)#last columns is just " "
    avSlices = stats.avg(slices.values)
    stdSlices = stats.sdev(slices.values)
    print "AVERAGE DISTRIBUTION OF N_2s: " + str(avSlices)
    print "STDEV DISTRIBUTION OF N_2s: " + str(stdSlices)
    print "\n"

def parse_spec_dim():
    #parse return_probs_2d.txt
    ret_prob = pd.read_table(os.path.join(os.path.join(data_path,"return_probs_" + sim_type + ext)), sep = ' ', header = None, lineterminator = '\n')
    ret_prob.drop(ret_prob.columns[-1], axis = 1, inplace = True)
    #print "TEXT FILE AS A MATRIX:\n" + str(ret_prob.values) 
    #print "\n\n"
    #use definition of spectral dimension get list of spectral dimensions 
    av_prob = stats.avg(ret_prob.values)
    #std_spec_dim = sdev(ret_prob.values) 
    print "AV RETURN PROBABILITIES AS A FUNCTION OF SIGMA:\n"
    print av_prob
    #plot return prob
    print "SPECTRAL DIMENSION AS A FUNCTION OF SIGMA:\n"
    sp_dim =  spec_dim(av_prob)
    print sp_dim
    print "\n"
    #calculate errors via bootstrap
    #calculate_errors(av_prob, spec_dim)
    prob_plot = pltd.make_plot(sigmas, r'Average Return Probability vs Diffusion Time', r'$\sigma$', r'$\langle P_g(\sigma)\rangle$', av_prob)
    spdim_plot = pltd.make_plot(sigmas[:-1], r'Average Spectral Dimension vs Diffusion Time', r'$\sigma$', r'$\langle D_s(\sigma)\rangle$', sp_dim[:-1])
    pltd.save_plot(prob_plot, 'return_probs_' + sim_type + '.pdf', out_path)
    pltd.save_plot(spdim_plot, 'spec_dim_' + sim_type + '.pdf', out_path)


vol_dist()
parse_spec_dim()
#slice_dist()
