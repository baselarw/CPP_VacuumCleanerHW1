-------------------------------------------------------------------------------
Description of the solutaion and and the format of the inputs and outputs:
-------------------------------------------------------------------------------

**Overview:**
This project simulates the operation of an autonomous vacuum cleaner within a house environment. The vacuum cleaner navigates through the house, detecting walls, dirt levels, and battery status to determine its next move. The goal is to clean the house efficiently while managing battery usage and ensuring the vacuum can return to its docking station for recharging.

**Approach:**
The solution is implemented using object-oriented programming principles in C++. The main components of the system are:

House: Represents the environment where the vacuum cleaner operates. It stores the layout of the house, including the position of walls and dirt levels.

VacuumCleaner: Represents the vacuum cleaner with attributes such as position, battery level, and movement history. It provides methods for movement, cleaning, charging, and tracking steps.

Sensor: Simulates the sensors on the vacuum cleaner, allowing it to detect walls, dirt levels, and battery status.

Algorithm: Implements the decision-making logic for the vacuum cleaner. It determines the next step based on sensor inputs, current state, and the need to return to the docking station.

Main Program: Orchestrates the simulation, initializing the house and vacuum cleaner, running the cleaning algorithm, and producing output results.

**Input Format**
The input to the program is a file that describes the layout of the house. The file should contain:

The first line: Contains two elements, the first one is the number of max battery steps ,and the second element isthe maximum number of steps they are separated by ','.
The other lines: between every two elemens there is: ','. and every element could be: 
 - 'D' = docking station (there is only 1, and from here the vacuum cleaner starts)
 - 'w' = wall
 - ' ' = clean square
 - 1-9 = number from 1 to 9, this is the dirtlevel of square

There are 3 inputs files:
- input_a.txt:
    in this file the vacuum cleaner surrounded with 4 walls.
- input_b.txt:
    in this file there is no docking station, that's mean that there is no vacuum. 
- input_c.txt:
    legal file with legal output. no case edges.

**Output Format**
The program produces an output file that records the vacuum cleaner's activity throughout the simulation. The output includes:

- A list of all the steps performed by the vacuum cleaner.
- The total number of steps taken.
- The amount of dirt left in the house.
- An indication of whether the vacuum cleaner is dead (battery exhausted).
- An indication of whether the cleaning mission was successful.

There are 3 outputs files:
- output_input_a.txt:
    in this output file, the vacuum cleaner will do any move, cause he is surrounded with 4 walls. He stays on place and don't move nor charge.
- output_input_b.txt:
    in this output file, there is no steps performed, and we supposed that number of steps,indicaton of whether the vacuum cleaner is dead or whether mission is succeeded are all 0.
- output_input_c.txt:
    legal output with succeeded mission. no case edges.

