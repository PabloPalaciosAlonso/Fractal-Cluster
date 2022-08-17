import utils as u
import matplotlib.pyplot as plt
import numpy as np
import sys
import os

def computeCM(pos):
    cm = np.zeros(3)
    for posi in pos:
        cm+=posi
    return cm/len(pos)

def computeGyrationRadius(pos, radius2):
    cm = computeCM(pos)
    rg2 = 0
    for posi in pos:
        posi_cm = posi-cm
        rg2+=np.dot(posi_cm,posi_cm)/len(pos)
    return np.sqrt(rg2+radius2)

def printResults(nParticlesList, rgList, Df, kf):
    fit = u.least_squares(nParticlesList, np.array(rgList), xscale = "log", yscale = "log")
    print("Expected Df = "+str(Df)+"; Obtained Df = " + str(1/fit[0]))
    print("Expected kf = "+str(kf)+"; Obtained kf = " + str(pow(radius/np.exp(fit[1]),Df)))
def plotResults(nParticlesList, rgList, Df, kf, radius):
    plt.rcParams['font.size'] = 20
    plt.rcParams['figure.constrained_layout.use'] = True
    plt.rcParams['axes.linewidth'] = 2
    fig = plt.figure()
    ax = plt.subplot(111)
    ax.xaxis.set_tick_params(which='major', size=10, width=2, direction='in', top='on')
    ax.xaxis.set_tick_params(which='minor', size=7, width=2, direction='in', top='on')
    ax.yaxis.set_tick_params(which='major', size=10, width=2, direction='in', right='on')
    ax.yaxis.set_tick_params(which='minor', size=7, width=2, direction='in', right='on')
    ax.plot(nParticlesList, np.array(rgList)/radius, ".", label = "Obtained", markersize = 15)
    ax.plot(nParticlesList, (nParticlesList/kf)**(1/Df), label = "Expected", linewidth = 2)
    ax.set_xlabel("Number of particles")
    ax.set_ylabel("$R_g$/a")
    ax.set_xscale("log")
    ax.set_yscale("log")
    ax.legend()
    plt.show()

    
Df = float(sys.argv[1])
kf = float(sys.argv[2])
radius = float(sys.argv[3])
rgList = []
nParticlesList = []
files = os.listdir()
for filename in files:
    if "FC" in filename and ".out" in filename and "~" not in filename:
        nParticles = int(filename.replace("FC","").replace(".out",""))
        pos = u.readMatrix(filename)[:,0:3]
        rgList+=[computeGyrationRadius(pos, radius*radius)]
        nParticlesList+=[nParticles]
nParticlesList = np.array(nParticlesList)
printResults(nParticlesList, rgList, Df, kf)
plotResults(nParticlesList, rgList, Df, kf, radius)
