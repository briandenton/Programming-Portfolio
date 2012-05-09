# Brian Denton
# CS 190C Introduction to Computational Thinking
# Project 3

# Tools for randomness
# randint - pick a random integer in the given closed interval
# uniform - generate a (floating point) random number from the given interval
from random import randint, uniform
from math import sqrt, floor
import matplotlib.pyplot as pylab
#import pylab
#import visual
#pylab.ion()

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
    
    moleculeEnergy = []
    moleculeVelocity = []

    demonStepMatrix = []
    demonEnergyMatrix = []

    if state == 1:
        """give each molecule the same energy and velocity. Since the energies given the velocities must
           sum up to totalEnergy (our demon initially has no energy), this means that each
           molecule starts with a velocity of sqrt(2*totalEnergy/N) and energy of totalEnergy/N."""
        demonEnergy = 0
        
        for i in range(N):
            moleculeEnergy.append( 1.0 * totalEnergy/N )
            moleculeVelocity.append( sqrt( 2.0 * totalEnergy/N ) )

    elif state == 2:
        """set all molecule velocities to zero and give the demon all of the energy"""
        demonEnergy = totalEnergy
                                     
        for i in range(N):
            moleculeEnergy.append( 0.0 )
            moleculeVelocity.append( 0.0 )

    # Run the following loop 'steps' times
    
    for i in range( steps ):

        acceleratedMoleculeIndex = randint( 0, N - 1 )

        Dv = uniform( -sqrt( 2 * (totalEnergy/10.0)/N ), sqrt( 2*(totalEnergy/10.0)/N ) )

        # Energy = v^2/2
        # v = sqrt(2 * Energy)

        oldVelocity = sqrt( 2 * moleculeEnergy[ acceleratedMoleculeIndex ] )
        newVelocity = oldVelocity + Dv

        deltaEnergy = newVelocity**2/2.0 - oldVelocity**2/2.0
        
        if demonEnergy - deltaEnergy > 0 and demonEnergy - deltaEnergy <= totalEnergy:
            demonEnergy = demonEnergy - deltaEnergy
            demonEnergyMatrix.append( demonEnergy )
            demonStepMatrix.append(i)
            moleculeEnergy[ acceleratedMoleculeIndex ] = moleculeEnergy[ acceleratedMoleculeIndex ] + deltaEnergy
            moleculeVelocity[ acceleratedMoleculeIndex ] = newVelocity



    if visuals == True:
        pylab.figure()
        pylab.hist( moleculeVelocity, 11 )
        pylab.title('Final particle velocity distribution\nState = ' + str(state) + ', Steps = ' + str(steps))
        pylab.ylabel('Frequency')
        pylab.xlabel('Velocity')
        pylab.savefig( 'Final_Molecule_Velocity_State_' + str(state) + '_Steps_' + str(steps) )
        pylab.close()

        pylab.figure()
        pylab.hist( demonEnergyMatrix, 11 )
        pylab.title('Final demon energy distribution\nState = ' + str(state) + ', Steps = ' + str(steps))
        pylab.ylabel('Frequency')
        pylab.xlabel('Energy')
        pylab.savefig( 'Demon_Energy_State_' + str(state) + '_Steps_' + str(steps)  )
        pylab.close()

        pylab.figure()
        pylab.plot( demonStepMatrix, demonEnergyMatrix, 'b-', label = 'Demon Energy' )
        pylab.title('Demon Energy vs. Step\nState = ' + str(state) + ', Steps = ' + str(steps) )
        pylab.ylabel('Energy')
        pylab.xlabel('Step')
        pylab.savefig( 'Demon_Energy_Time_State_' + str(state) + '_Steps_' + str(steps) )
        pylab.close()

    
    systemEnergy = 0

    for i in range( N ):
        systemEnergy = systemEnergy + moleculeEnergy[i]

    return systemEnergy

if __name__ == "__main__":
    totalEnergy = 500
    for state in [1, 2]:
        for steps in [ 3000, 10000, 100000, 1000000 ]:
            systemEnergyMatrix = []
            totalEnergyMatrix = []
            NMatrix = []
            for N in range(50,501,50):
                systemEnergy = ideal_gas(N, totalEnergy, steps, state, N==500)
                systemEnergyMatrix.append( systemEnergy )
                totalEnergyMatrix.append( totalEnergy )
                NMatrix.append( N )

            yRange = totalEnergy - min( systemEnergyMatrix )

            pylab.figure()
            pylab.plot( NMatrix, systemEnergyMatrix, 'go-', label = 'System Energy' )
            pylab.plot( NMatrix, totalEnergyMatrix, 'bo-', label = 'Total Energy')
            pylab.legend( loc = 'best')
            pylab.title('System Energy vs. N\nState = ' + str(state) + ', Steps = ' + str(steps) )
            pylab.ylabel('Energy')
            pylab.xlabel('N')
            pylab.xlim( min( NMatrix ), max( NMatrix ) )
            pylab.ylim( floor( min( systemEnergyMatrix ) - 0.01 * yRange ), floor( totalEnergy + 0.1 * yRange ) )
            pylab.savefig( 'System_Energy_State_' + str(state) + '_Steps_' + str(steps) )
            pylab.close()

#END OF PROGRAM
