#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <vector>

// @brief: Prints out contents of file exactly as formatted.
// @param: filename - name of file.
void displayTextFromFile(std::string filename);

// @brief: Asks user for string input.
// @param: prompt - input prompt.
// @param: errorMessage - message if input is invalid.
// @param: choices - allowed inputs from user.
// @return: Input selected by user from choices.
std::string getStringInput(std::string prompt, std::string errorMessage,
                          std::vector<std::string> choices);

// @brief: Application file.
int main();

#endif