#ifndef SENSOR_H
#define SENSOR_H

#include "House.h"
#include "VacuumCleaner.h"

class Sensor
{
private:
    /*
    instance of House
     */
    const House &house;

    /*
    instance of VacuumCleaner
    */
    const VacuumCleaner &vacuum;

public:
    /*
     *constructor of Sensor class
     *@param &house: input of house type
     *@param &vacuum: input of vacuum type
     */
    Sensor(const House &house, const VacuumCleaner &vacuum);

    /*
     *this function called for detecting walls
     *@param direction: the direction that the vacuum sensor wants to check
     *return: True if there is a wall in direction, Flase if not
     */
    bool detectWall(char direction) const;

    /*
     *this function called for detecting dirt
     *return: level of dirt at the vacuum current position
     */
    int detectDirt() const;

    /*
     *this function called for detecting Battery level
     *return: current battery level of the vacuum cleaner
     */
    int detectBattery() const;
};

#endif
