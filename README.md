# Covid 19 transmission Simulation Program

## Welcome 

This program simulates the behavior of Covid 19 virus inside a building occupied by people, and let the user monitor the progress of the infection.
This project is based on the Siafu Simulator : https://github.com/miquelmartin/Siafu and the work of Thiago Goldoni for the Model classes (Agent & World Models).

## Utilization of the program

In order to launch the program, you need to compile the project using the command :

#### make simulator

You can then run it using the command :

#### ./bin/Simulation

Besides, you can use the launching options :

#### --days <number> or -d <number>
Specifies the amount of days for the simulation

#### --stop or -s 
After the creation or recovery of Gradients, the program will ask the user to press a key before launching the simulation 

#### --grad or -g
After the creation or recovery of Gradients, the program will shut down


The script performance.sh can be used to launch the simulation multiple times :

#### bash performance.sh <loop> <d>
Launches the simulation loop times, with d amount of days for the simulation. This script can be used to facilitate the performance analysis process, for instance you can combine it with the time command on unbuntu to measure the execution time of the program.





