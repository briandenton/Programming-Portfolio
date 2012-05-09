# Tools for randomness
# randint - pick a random integer in the given closed interval
# uniform - generate a (floating point) random number from the given interval
from random import randint, uniform
from math import sqrt
import pylab

def setupGraph(title, xlabel, ylabel, hold=False):
    pylab.title(title)
    pylab.xlabel(xlabel)
    pylab.ylabel(ylabel)
    pylab.grid(True)
    pylab.hold(hold)
    
def ideal_gas(
        N,                              # Number of particles
        totalEnergy,                    # total of demon and system energy
        steps,                          # number of simulation steps
        state=1,                        # Initial state
        visuals=True                    # plot histogram?
    ):

    return 0

if __name__ == "__main__":
    state = 1
    totalEnergy = 500
    for N in range(50,501,50):
        systemEnergy = ideal_gas(N, totalEnergy, 3000, state, N==500)

