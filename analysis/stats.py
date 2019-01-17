import numpy as np 
from math import * 
from random import uniform 

def deriv(f, x):
    fprime = np.diff(f)/np.diff(x)
    return fprime
    
def avg(matrix):
    return np.sum(matrix, axis = 0)/len(matrix)
    
def sdev(matrix):        # std dev of G 
    lst = np.asarray(matrix) 
    return np.absolute(avg(lst**2)-avg(lst)**2)**0.5
    
def bootstrap(ensemble):
    N_cf = len(ensemble)
    ensemble_bootstrap = []
    for n in range(0, N_cf):
        alpha = int(uniform(0, N_cf))
        ensemble_bootstrap.append(ensemble[alpha])
    return ensemble_bootstrap

def bin(ensemble, binsize):
    binned_ensemble = []
    for i in range(0, len(ensemble), binsize):
        binval = 0;
        for j in range (0, binsize):
            binval += ensemble[i + j]
        binned_ensemble.append(binval)
    return binned_ensemble

def calculate_errors(data, f):#, original #uses bootstrap error analysis to calculate the errors in f(data)
    bootstrap_dim = []
    for i in range(0, n_bootstrap):
        data_bootstrap = bootstrap(data)
        bootstrap_ensemble.append(lambda data : f(data))#not sure if need f(data)
    bootstrap_ensemble = Numeric.array(bootstrap_ensemble)
    bootstrap_errors = sdev(bootstrap_ensemble) #error as standard deviation
    #bootstrap_errors = sdev(bootstrp_ensemble/original) #error as standard deviation of the mean
    return bootstrap_errors

