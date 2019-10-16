#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <vector>

void displayTextFromFile(std::string filename);
std::string getStringInput(std::string prompt, std::string errorMessage,
                            std::vector<std::string> choices);
int main();

#endif