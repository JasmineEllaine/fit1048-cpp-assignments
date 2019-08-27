/*
 * Author: Jasmine Banares
 * Student ID: 2973 8660
 * Project: Assignment 1 – The Tally Ho Probability Generator
 * 
 * This simple program enables a user to experiment with probability using dice
 * rolls. A user is able specify how many dice to roll, how many times to roll
 * it, and how many times to repeat the experiment. Data can be be imported and
 * exported.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <random>
#include <sstream>

// Global variable declarations.
std::string lastGeneratedTable;

void displayMenu() {
	// Display menu header.
	std::cout << std::endl
        << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl
		<< "    The Tally Ho Probability Generator" << std::endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	// Display menu options.
	std::cout << "[0] End Testing the Program" << std::endl
		<< "[1] Display \"About\" Information" << std::endl
		<< "[2] Read and store data from files" << std::endl
		<< "[3] Generate a Dice Tally Table" << std::endl
		<< "[4] Save Tally Statistics to a File" << std::endl
		<< "[5] Load Tally Statistics from a File" << std::endl;
	// Display prompt.
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl
		<< "Select one of the options above (0-5): ";
}

int getValidInput() {
	// Initialise user input.
	int userChoice = -1;
	std::cin >> userChoice;
	// Keep asking for input until it is an integer from 0-5.
	while (userChoice < 0 || userChoice > 5 || std::cin.fail()) {
		std::cout << "Error: Input only integers from 0-5: ";
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> userChoice;
	}
	return userChoice;
}

void displayText(std::string filename) {
    // Add checks if file does not exist
    // http://www.fredosaurus.com/notes-cpp/io/readtextfile.html
    std::cout << std::endl;
    std::fstream file;
    file.open(filename);
    std::string textline;
    while (std::getline(file, textline)) {
        std::cout << textline << std::endl;
    }
    file.close();
}

std::vector<std::string> createLists(std::string filename) {
    // Check if file exists.
    std::ifstream data;
    data.open(filename);
    while (!data) {
        std::cout << filename << " does not exist." << std::endl
        << "Enter a different filename: ";
        std::cin >> filename;
    }

    // Initialise vector of data
    // std::vector<int> tallyLineData(14, 0);

    // std::cout << data.eof();
    // // Return 0 vector if file is empty.
    // if (!data.eof()) {
    //     // std::cout << "Empty File" << std::endl;
    //     return tallyLineData;
    // }

    // std::string currentData;
    // std::string delimiter = " ";
    // // If not empty read data into vector
    // while (getline(data, currentData)) {
    //     int strPos = 0;
    //     int vectorPos = 0;
    //     std::string currValue;
    //     // Get each value demlimited by a space.
    //     while ((strPos = currentData.find(delimiter)) != std::string::npos) {
    //         currValue = currentData.substr(0, strPos);
    //         // Insert each value into vector.
    //         tallyLineData[vectorPos++] = std::stoi(currValue);
    //         currentData.erase(0, strPos + delimiter.length());
    //     }
    //     tallyLineData[vectorPos++] = std::stoi(currentData);

    // }

    std::vector<std::string> tallyData;
    std::string currData;
    while (std::getline(data, currData)) {
        tallyData.push_back(currData);
    }

    return tallyData;
}

int getIntInput(std::string prompt, int lo, int hi) {
    std::cout << prompt;

	// Initialise user input.
	int input = lo - 1;
	std::cin >> input;
	// Keep asking for input until it is an integer from 0-5.
	while (input < lo || input > hi || std::cin.fail()) {
		std::cout << "Error: Input only integers from " << lo << "-"
            << hi << ": ";
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> input;
	}
	return input;
}

std::string vectorToString(std::vector<int> vector) {
    std::string output = std::to_string(vector[0]);
    for (int i = 1; i < vector.size(); i++) {
        output += " " + std::to_string(vector[i]);
    }
    return output;
}

std::vector<int> stringToVector(std::string string, std::string delimiter) {
    // int strPos = 0;
    // int vectorPos = 0;
    // std::string currValue;
    // // Get each value demlimited by a space.
    // while ((strPos = string.find(delimiter)) != std::string::npos) {
    //     currValue = string.substr(0, strPos);
    //     // Insert each value into vector.
    //     output[vectorPos++] = std::stoi(currValue);
    //     string.erase(0, strPos + delimiter.length());
    // }
    // output[vectorPos++] = std::stoi(string);
    std::vector<int> output(14, 0);
    std::istringstream is(string);
    int currValue;
    int counter = 0;
    while (is >> currValue) {
        output[counter++] = currValue;
    }
    return output;
}

std::string generateTable(int diceUsed, int diceRolls) {
    std::vector<int> tallyResults(14, 0);
    tallyResults[0] = diceUsed;
    tallyResults[1] = diceRolls;

    for (int i = 0; i < diceRolls*10; i++) {
        int diceResultTotal = 0;
        for (int j = 0; j < diceUsed; j++) {
            // Roll a die.
            int dieResult = std::rand() % 6 + 1;
            diceResultTotal += dieResult;
        }
        // Minus one because indices start at 0.
        // First two items in vector reserved for dice used and rolls.
        tallyResults[diceResultTotal+1]++;
    }

    // for (int i = 0; i < tallyResults.size(); i++){
    //     std::cout << tallyResults[i] << std::endl;
    // }

    tallyResults[0] = diceUsed;
    tallyResults[1] = diceRolls;

    return vectorToString(tallyResults);
}

void printTableFromVector(std::vector<int> tableData) {
    std::cout << std::endl;
    std::cout << "You rolled " << tableData[0] << " dice " << tableData[1]
        << "0 times." << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    
    // Range of dice rolls.
    int lo = tableData[0] < 2 ? 1 : 2;
    int hi = lo == 1 ? 6 : 12;
    for (lo; lo <= hi; lo++) { 
        if (lo < 10) {
            std::cout << " ";
        }
        std::cout << lo << ": " << std::string(tableData[lo+1], '*')
            << std::endl;
    }
}

void saveToFile(std::string filename, std::string lineToWrite) {
    std::ofstream savedFile;
    savedFile.open(filename, std::ios_base::app);
    savedFile << lineToWrite << "\n";
    savedFile.close();
}

void displayAllDataFromFile(std::string filename) {
    std::vector<std::string> tallyData = createLists(filename);
    for (int i = 0; i < tallyData.size(); i++) {
        // std::cout << tallyData[i];
        // std::cin >> i;
        printTableFromVector(stringToVector(tallyData[i], " "));
    }
}

bool processChoice (int userChoice) {
    // Switch statement has the precondition that the numbers are from 0-5
    switch (userChoice) {
        case 1: displayText("TallyAbout.txt");
                system("pause");
                break;
        case 2: {
                std::vector<std::string> tallyData = 
                    createLists("savedTallyData.txt");
                system("pause");
                break;
            }
        case 3: {
                int diceUsed = getIntInput("How many dice to roll (1-2): ",
                                           1,
                                           2);
                int diceRolls = getIntInput("How many times to roll (1-10): ",
                                           1,
                                           10);
                lastGeneratedTable = generateTable(diceUsed, diceRolls);
                printTableFromVector(stringToVector(lastGeneratedTable, " "));
                system("pause");
                break;
        }
        case 4: {
                printTableFromVector(stringToVector(lastGeneratedTable, " "));
                std::cout << std::endl
                    << "Do you want to save this data - (y/n): ";
                std::string userChoice;
                std::cin >> userChoice;
                if (userChoice == "y") {
                    saveToFile("savedTallyData.txt", lastGeneratedTable);
                    std::cout << std::endl
                        << "These statistics are now saved." << std::endl;
                }
                system("pause");
                break;
        }
        case 5: displayAllDataFromFile("savedTallyData.txt");
                system("pause");
                break;
    }

    // Return true or false to determine if program should exit.
    return userChoice > 0 ? true : false;
}

int main() {
    bool runProgram = true;
    while (runProgram) {
        displayMenu();
        // Prompt user for input.
        int userChoice = getIntInput("", 0, 5);
        runProgram = processChoice(userChoice);
    }

    std::cout << "Thank you for testing this application." << std::endl;
    system("pause");

	return 0;
}