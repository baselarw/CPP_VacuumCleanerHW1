#ifndef ALGORITHM_H
#define ALGORITHM_H

class Algorithm
{

private:
    /*
    if True then go back to the docking station. if False don't
     */
    bool goingBackToDocking;

public:
    /*
     *constructor of Sensor class
     */
    Algorithm();

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
    char nextStep(bool north_wall, bool east_wall, bool south_wall, bool west_wall, int dirtLevel, int batteryLevel, int backSteps_len, bool canBack);

    // /*
    //  *this function called for going back to the docking station.
    //  *return: True if can going back to the docking station, Flase if not.
    //  */
    // bool getGoingBackToDocking() const;

    /*
     *this function called for set GoingBackToDocking field
     *True if can going back to the docking station, Flase if not.
     */
    void setGoingBackToDocking();
};




#endif
