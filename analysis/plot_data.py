import numpy as np
import os
import matplotlib
matplotlib.use('Agg')
from matplotlib.backends.backend_pdf import PdfPages
import matplotlib.pyplot as plt
plt.rc('text', usetex=True)
plt.rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})


#write code to plot data to pdf
def make_plot(xs, fig_title, x_label, y_label, ys = None):#add errorbars parameter?
    fig = plt.figure()
    fig1 = fig.add_subplot(111)
    if ys is None:
        fig1.hist(xs)
    else:
        fig1.plot(xs, ys)
    #plotting info
    #not sure if making latex titles right
    fig1.set_title(fig_title, fontsize = 16)
    fig1.set_xlabel(x_label)
    fig1.set_ylabel(y_label)  
    return fig 

def save_plot(plot, filename, path):
    pp = PdfPages(os.path.join(os.path.join(path, filename)))
    pp.savefig(plot)
    pp.close()

