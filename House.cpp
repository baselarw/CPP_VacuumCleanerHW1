#include "House.h"
#include <fstream>
#include <iostream>
#include <exception>

/*
 *constructor of House class
 *@param &filename: the name of the text_file
 */
House::House(const std::string &fileName)
{
    LoadHouse(fileName);
}

/*
 *destructor of House class
 */
House::~House()
{
    delete robot; // Free the memory allocated for the VacuumCleaner object
}

/*
 *this function called when we want to load the House from the text_file
 *@param &filename: the name of the text_file
 */
void House::LoadHouse(const std::string &fileName)
{
    std::string line;
    try
    {
        int row = 0;
        std::ifstream file(fileName);
        if (file.is_open())
        {
            std::vector<std::string> first_line_vector;
            bool first_line = true;
            bool find_D = true;
            while (std::getline(file, line)) /// reading from the text_file
            {

                if (first_line) // first line
                {
                    first_line_vector = splitString(line);
                    first_line = false;
                }
                else /// 2nd line and above
                {
                    std::vector<char> line_vector = splitChar(line); // split the line by "," and get line_vector
                    if (!IsValidInput(line_vector))                  // checking the validity of the line_vector
                    {
                        throw std::runtime_error("An error occurred");
                    }
                    if (find_D) // finding the location of the docking_station
                    {
                        for (int i = 0; i < line_vector.size(); i++)
                        {
                            if (line_vector[i] == 'D')
                            {
                                docking_station = std::make_pair(row, i);
                                find_D = false;
                            }
                        }
                    }
                    house_map.push_back(line_vector);
                    row++;
                }
            }
            robot = new VacuumCleaner(docking_station.first, docking_station.second, std::stoi(first_line_vector[0]), std::stoi(first_line_vector[1])); // setting the robot informations
        }
        else
        {
            std::cout << "--> Unable to open the file";
        }
    }

    catch (const std::exception &e)
    {
        robot = new VacuumCleaner(-1, -1, -1,-1); // setting the robot informations for unvalid file!
    }
}

/*
 *this function split the line that we got from the file into chars (we will use for the lines except of the first line)
 *@param &line: string that splitted by ','
 *return: vector of chars
 */
std::vector<char> House::splitChar(std::string str)
{
    bool current_char = false;   // this is flag to decet if there are two ',' one after the another
    std::vector<char> result;
    for (char ch : str)
    {
        if (ch != ',')
        {
            result.push_back(ch);
            current_char=false;
        } 
        else{
            if(current_char){
                result.push_back('-');
            }
            else{
                current_char=true;
            }
        }

    }
    return result;
}

/*
 *this function split the line that we got from the file into strings (we will use for the first line)
 *@param &line: string that splitted by ','
 *return: vector of strings
 */
std::vector<std::string> House::splitString(std::string str)
{
    std::vector<std::string> result;
    std::string item;
    for (char ch : str)
    {
        if (ch == ',')
        {
            result.push_back(item); // Add the current item to the result vector
            item.clear();           // Clear the current item for the next substring
        }
        else
        {
            item += ch; // Add the character to the current item
        }
    }
    result.push_back(item); // Add the last item to the result vector
    return result;
}

/*
 *this function called to get the Dirt level of the square
 *@param x: presents the x-axis location
 *@param y: presents the y-axis location
 *return: the dirt level of the square at (x,y) locaction
 */
int House::getDirtLevel(int x, int y) const
{
    if (x >= 0 && x < house_map.size() && y >= 0 && y < house_map[x].size())
    {
        char curr_location = house_map[x][y];
        if ((curr_location == 'w') || (curr_location == 'D'))
        {
            return -1;
        }
        if (curr_location == ' ')
        {
            return 0;
        }
        return curr_location - '0';
    }
    return -1;
}

/*
 *this function called for checking if the there is a wall
 *@param x: presents the x-axis location
 *@param y: presents the y-axis location
 *return: True if there is a wall at (x,y) location, Flase if not
 */
bool House::IsWall(int x, int y) const
{
    if (x >= 0 && x < house_map.size() && y >= 0 && y < house_map[x].size())
    {
        return house_map[x][y] == 'w';
    }
    return true;
}

/*
 *this function called to get the Docking station
 *return: pair of the docking station location
 */
std::pair<int, int> House::getDockingStation() const
{
    return docking_station;
}

/*
 *this function called for checking if the house is tottaly clean
 *return: True if all of the house is clean, Flase if not
 */
bool House::IsClean() const
{
    for (int i = 0; i < house_map.size(); ++i)
    {
        for (int j = 0; j < house_map[i].size(); ++j)
        {
            if (getDirtLevel(i, j) > 0)
            {
                return false;
            }
        }
    }
    return true;
}

/*
 *this function called to clean the dirt
 *@param x: presents the x-axis location
 *@param y: presents the y-axis location
 *return: reduces the dirt level at (x,y) location by 1
 */
void House::cleanDirt(int x, int y)
{
    if (x >= 0 && x < house_map.size() && y >= 0 && y < house_map[x].size())
    {
        if (house_map[x][y] > '0' && house_map[x][y] <= '9')
        {
            house_map[x][y]--;
        }
    }
}

/*
 *this function called for checking the validity of the input
 *@param vec: vector of chars
 *return: True if the input is valid, Flase if not valid
 */
bool House::IsValidInput(std::vector<char> vec)
{
    for (char ch : vec)
    {
        if (ch != 'D' && ch != ' ' && ch != 'w' && !(ch >= '1' && ch <= '9'))
        {
            return false;
        }
    }
    return true;
}

/*
 *this function called to get the sum of the House Dirt
 *return: the sum of the House Dirt
 */
int House::getHouseDirt() const
{
    int cnt = 0;
    for (int i = 0; i < house_map.size(); ++i)
    {
        for (int j = 0; j < house_map[i].size(); ++j)
        {
            if (getDirtLevel(i, j) != -1)
            {
                cnt += getDirtLevel(i, j);
            }
        }
    }
    return cnt;
}
