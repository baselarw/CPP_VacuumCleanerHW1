#include "Algorithm.h"
#include <random>

/*
 *constructor of Sensor class
 *goingBackToDocking =false as default.
 */
Algorithm::Algorithm() : goingBackToDocking(false) {}

/*
 *this function called to generate the next step
 *@param north_wall: true if there a north wall, else false.
 *@param east_wall: true if there a east wall, else false.
 *@param south_wall: true if there a south wall, else false.
 *@param west_wall: true if there a west wall, else false.
 *@param dirtLevel: the dirt level of the current location of the vacuum.
 *@param batteryLevel: the current battery level of the vacuum.
 *@param backSteps_len: the total steps to get back to the docking station from the current location.
 *@param canBack: true if can back, else false.
 *return: the next direction to move on.
 */
char Algorithm::nextStep(bool north_wall, bool east_wall, bool south_wall, bool west_wall, int dirtLevel, int batteryLevel, int backSteps_len, bool canBack)
{

    if ((canBack && (batteryLevel == backSteps_len || batteryLevel == (backSteps_len +1)))) // going back to the docking station to charge the battery
    {
        if(dirtLevel>0 && batteryLevel==(backSteps_len+1)){
            return 'T';  //clean
        }
        goingBackToDocking = true;   // there are no dirt
        return 'D'; 
    }


    if (dirtLevel > 0)
    {
        return 'T'; // clean
    }

    if (north_wall && east_wall && south_wall && west_wall) // blocked from tall of the directions
    {
        return 'T';
    }

    // Simple random move
    while (true)
    {
        // Seed with a real random value, if available
        std::random_device rd;

        // Initialize the random number generator with the seed
        std::default_random_engine generator(rd());

        // Define the range of the random numbers (1 to 4)
        std::uniform_int_distribution<int> distribution(1, 4);

        // Generate a random number
        int random_number = distribution(generator);
        //int random_number = rand() % 4 + 1;

        if (!north_wall && random_number == 1)
            return 'N';
        if (!east_wall && random_number == 2)
            return 'E';
        if (!south_wall && random_number == 3)
            return 'S';
        if (!west_wall && random_number == 4)
            return 'W';
    }

    return 'T'; // stay if all directions are walls
}


/*
 *this function called for set GoingBackToDocking field
 *True if can going back to the docking station, Flase if not.
 */
void Algorithm::setGoingBackToDocking()
{
    goingBackToDocking = false;
}
