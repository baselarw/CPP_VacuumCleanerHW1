#include "Sensor.h"
#include <iostream>

/*
 *constructor of Sensor class
 *@param &house: input of house type
 *@param &vacuum: input of vacuum type
 */
Sensor::Sensor(const House &house, const VacuumCleaner &vacuum) : house(house), vacuum(vacuum) {}

/*
 *this function called for detecting walls
 *@param direction: the direction that the vacuum sensor wants to check
 *return: True if there is a wall in direction, Flase if not
 */
bool Sensor::detectWall(char direction) const
{
    int x = vacuum.getPosition().first;
    int y = vacuum.getPosition().second;
    switch (direction)
    {
    case 'N':
        return house.IsWall(x - 1, y);
    case 'E':
        return house.IsWall(x, y + 1);
    case 'S':
        return house.IsWall(x + 1, y);
    case 'W':
        return house.IsWall(x, y - 1);
    }
    return true;
}

/*
 *this function called for detecting dirt
 *return: level of dirt at the vacuum current position
 */
int Sensor::detectDirt() const
{
    int x = vacuum.getPosition().first;
    int y = vacuum.getPosition().second;
    return house.getDirtLevel(x, y);
}

/*
 *this function called for detecting Battery level
 *return: current battery level of the vacuum cleaner
 */
int Sensor::detectBattery() const
{
    return vacuum.getBatteryLevel();
}
