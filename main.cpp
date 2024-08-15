#include "House.h"
#include "VacuumCleaner.h"
#include "Algorithm.h"
#include "Sensor.h"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{
    try
    {
        if (argc < 2)
        {
            std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
            return 1;
        }

        std::string filename = argv[1];
        House house (std::filesystem::absolute(filename));
        VacuumCleaner *vacuum = house.robot;

        if ((*vacuum).getPosition().first == -1 && (*vacuum).getPosition().second == -1 && (*vacuum).getMaxBattery() == -1 && (*vacuum).getMaxSteps() == -1) ///check validity of file
        {
            throw std::runtime_error("An error occurred");
        }

        Algorithm algorithm;
        Sensor sensor(house, *vacuum);
        std::ofstream outputFile("output_" + filename);
        bool first_step = true;
        while (!(*vacuum).isOutOfBattery() && !(*vacuum).IsOutOfSteps()) ////checking If it's legal to for the robot to move
        {
            int dirtLevel = sensor.detectDirt();
            int batteryLevel = sensor.detectBattery();
            bool northWall = sensor.detectWall('N');
            bool eastWall = sensor.detectWall('E');
            bool southWall = sensor.detectWall('S');
            bool westWall = sensor.detectWall('W');


            char nextMove = algorithm.nextStep(northWall, eastWall, southWall, westWall, dirtLevel, batteryLevel, (*vacuum).getBack_stepsSize(), true); //choosing the next step
            if (first_step)
            {
                if (nextMove == 'T')   // in this situation the vacuum surrounded with walls and in the docking station.
                {
                    break;
                }

                first_step = false;
            }

            if (nextMove == 'D')  //the vacuum in docking station
            {
                if ((*vacuum).getMaxSteps() < ((*vacuum).getTotalSteps() + (*vacuum).getBack_stepsSize())) /// can not return to the docking station cause if return he will pass the legal number of max_steps
                {
                    nextMove = algorithm.nextStep(northWall, eastWall, southWall, westWall, dirtLevel, batteryLevel, (*vacuum).getBack_stepsSize(), false);
                }
                else
                {
                    (*vacuum).setPostionToDockingStation();
                    int cnt1 = 1;
                    while ((*vacuum).getTotalSteps() < (*vacuum).getMaxSteps() && (*vacuum).getBatteryLevel() < (*vacuum).getMaxBattery()) //if can charge more then charge
                    {
                        (*vacuum).charge();
                        cnt1 += 1;
                    }
                    algorithm.setGoingBackToDocking();
                }
            }
            if (nextMove == 'T') //the vacuum stays in place for cleaning
            {
                (*vacuum).clean();
                house.cleanDirt((*vacuum).getPosition().first, (*vacuum).getPosition().second);
            }

            else if (nextMove != 'D' && nextMove != 'T')
            {
                (*vacuum).move(nextMove);
            }
        }

        if (house.IsClean() && (*vacuum).getMaxSteps() >= ((*vacuum).getTotalSteps() + (*vacuum).getBack_stepsSize())) ///check if the house is clean and if the vacuum can return to docking station
        {
            (*vacuum).setPostionToDockingStation();
            algorithm.setGoingBackToDocking();
        }


        ///////////////////////////////////
        ////writing in the output file/////
        ///////////////////////////////////
        try
        {
            if (outputFile.is_open())
            {
                outputFile << "all the steps performed by the vacuum cleaner: ";
                std::vector<std::pair<int, int>> all_steps = (*vacuum).getAll_steps();
                for (int i = 0; i < (*vacuum).getAll_stepsSize() - 1; i++)
                {
                    outputFile << '(' << all_steps[i].first << ',' << all_steps[i].second << ')' << ", ";
                }

                if (all_steps.size() == 0)
                {
                    outputFile << std::endl;
                }
                else
                {
                    outputFile << '(' << all_steps[all_steps.size() - 1].first << ',' << all_steps[all_steps.size() - 1].second << ')' << std::endl;
                }

                outputFile << "the total number of steps performed: " << (*vacuum).getTotalSteps() << std::endl;

                outputFile << "a result of the amount of dirt left in house: " << house.getHouseDirt() << std::endl;

                outputFile << "an indication of whether the vacuum cleaner is dead: " << (*vacuum).isOutOfBattery() << std::endl;

                if (house.IsClean() && (*vacuum).isInDockingStation())
                {
                    outputFile << "an indication of whether mission is succeeded: " << true << std::endl;
                }
                else
                {
                    outputFile << "an indication of whether mission is succeeded: " << false << std::endl;
                }

                outputFile.close();
            }
            else
            {
                std::cerr << "Error opening file for writing!" << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "--> Standard exception: " << e.what() << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "--> Standard exception: " << e.what() << std::endl;
    }

    return 0;
}
