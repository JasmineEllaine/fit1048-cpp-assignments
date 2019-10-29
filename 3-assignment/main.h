#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <vector>

// @brief: Prints out contents of file exactly as formatted.
void displayTextFromFile(std::string filename);

// @brief: Pauses program until ENTER is pressed.
void pause();

// @brief: Asks user for string input.
// @param: prompt - input prompt.
// @param: errorMessage - message if input is invalid.
// @param: choices - allowed inputs from user.
// @return: Input selected by user from choices.
std::string getStringInput(std::string prompt, std::string errorMessage,
                          std::vector<std::string> choices);

// @brief: Gets an integer input from user between lo-hi.
int getIntInput(std::string prompt, int lo, int hi);

// @brief: Display text line by line.
void displayTextLineByLine(std::string filename);

// @brief: Application file.
int main();

#endif