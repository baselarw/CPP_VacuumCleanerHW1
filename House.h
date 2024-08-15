#ifndef HOUSE_H
#define HOUSE_H

#include <string>
#include <vector>
#include "VacuumCleaner.h"

class House
{
private:
  /*
  vector that contains the house_map
   */
  std::vector<std::vector<char>> house_map;

  /*
  pair of the docking station location
  */
  std::pair<int, int> docking_station;

  /*
   *this function split the line that we got from the file into strings (we will use for the first line)
   *@param &line: string that splitted by ','
   *return: vector of strings
   */
  std::vector<std::string> splitString(std::string line);

  /*
   *this function split the line that we got from the file into chars (we will use for the lines except of the first line)
   *@param &line: string that splitted by ','
   *return: vector of chars
   */
  std::vector<char> splitChar(std::string line);

  /*
   *this function called when we want to load the House from the text_file
   *@param &filename: the name of the text_file
   */
  void LoadHouse(const std::string &filename);

  /*
   *this function called for checking the validity of the input
   *@param vec: vector of chars
   *return: True if the input is valid, Flase if not valid
   */
  bool IsValidInput(std::vector<char> vec);

  /*
   *this function called to get the Docking station
   *return: pair of the docking station location
   */
  std::pair<int, int> getDockingStation() const;

public:
  /*
   *pointer to robot
   */
  VacuumCleaner *robot;

  /*
   *constructor of House class
   *@param &filename: the name of the text_file
   */
  House(const std::string &filename);

  /*
   *destructor of House class
   */
  ~House();


  /*
   *this function called for checking if the there is a wall
   *@param x: presents the x-axis location
   *@param y: presents the y-axis location
   *return: True if there is a wall at (x,y) location, Flase if not
   */
  bool IsWall(int x, int y) const;

  /*
   *this function called for checking if the house is tottaly clean
   *return: True if all of the house is clean, Flase if not
   */
  bool IsClean() const;

  /*
   *this function called to clean the dirt
   *@param x: presents the x-axis location
   *@param y: presents the y-axis location
   *return: reduces the dirt level at (x,y) location by 1
   */
  void cleanDirt(int x, int y);

  /*
   *this function called to get the Dirt level of the square
   *@param x: presents the x-axis location
   *@param y: presents the y-axis location
   *return: the dirt level of the square at (x,y) locaction
   */
  int getDirtLevel(int x, int y) const;

  /*
   *this function called to get the sum of the House Dirt
   *return: the sum of the House Dirt
   */
  int getHouseDirt() const;
};

#endif
