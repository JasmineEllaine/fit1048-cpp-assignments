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
std::string lastGeneratedTable = "";

void displayMenu() {
    /***************************************************************************
     * Displays a text menu in the console.
     **************************************************************************/
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

void displayText(std::string filename) {
    /***************************************************************************
     * Prints out contents of a file into the console exactly the way it was
     * formatted.
     * 
     * @param   filename    Name of the text file to be displayed.
     **************************************************************************/
    std::cout << std::endl;
    std::fstream file;

    file.open(filename);
    // Print error message if about file is not found or empty.
    if (file.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "Sorry, it seems like the file you're reading"
            << std::endl << "either doesn't exist is is empty! :(" << std::endl;
        return;
    }

    // Display message.
    std::string textline;
    while (std::getline(file, textline)) {
        std::cout << textline << std::endl;
    }
    file.close();
}

std::vector<std::string> createLists(std::string filename) {
    /***************************************************************************
     * Loads data from a file and returns this data as a vector.
     * 
     * @param   filename    Name of the text file to be displayed.
     * @return  tallyData   String vector containing data from each line of
     *                      file. Empty if file does not exist or is empty.
     **************************************************************************/
    // Initialise empty vector.
    std::vector<std::string> tallyData;

    // Open file.
    std::ifstream data;
    data.open(filename);

    // Return empty vector if file not found/empty.
    if (data.peek() == std::ifstream::traits_type::eof()) {
        return tallyData;
    }

    // Read file into vector if not empty.
    std::string currData;
    while (std::getline(data, currData)) {
        tallyData.push_back(currData);
    }

    return tallyData;
}

int getIntInput(std::string prompt, int lo, int hi) {
    /***************************************************************************
     * Asks user for valid integer input.
     * 
     * @param   prompt  Prompt to be displayed to the user. Displayed as is.
     * @param   lo      Lowest integer user can input.
     * @param   hi      Highest integer user can input.
     * @return  input   User's input.
     **************************************************************************/
    std::cout << prompt;

	// Initialise user input to be lower than allowed range.
	int input = lo - 1;
	std::cin >> input;
	// Keep asking for input until it is within range specified.
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
    /***************************************************************************
     * Converts a vector into a string where each element of a vector is
     * separated by a space. E.g. {1, 2, 3} -> "1 2 3".
     * 
     * @param   vector  Vector to be stringified.
     * @return  output  Stringified vector.
     * 
     * Preconditions:
     * - vector must not be empty.
     **************************************************************************/
    // Initialise output string using the first elem of vector.
    std::string output = std::to_string(vector[0]);
    for (int i = 1; i < vector.size(); i++) {
        output += " " + std::to_string(vector[i]);
    }
    return output;
}

std::vector<int> stringToVector(std::string string) {
    /***************************************************************************
     * Splits a string into a vector<int>delimited by a " ".
     * E.g. "1 2 3" -> {1, 2, 3}.
     * 
     * @param   string  String to be split.
     * @return  output  Vector containing integers split using a delimiter.
     * 
     * Preconditions:
     * - vector must not be empty.
     **************************************************************************/
    // Initialise output vector.
    std::vector<int> output;
    std::istringstream is(string);
    int currValue;
    while (is >> currValue) {
        output.push_back(currValue);
    }
    return output;
}

std::string generateTable(int diceUsed, int diceRolls) {
    /***************************************************************************
     * Generates a table with resuls of dice rolls specified by user.
     * 
     * @param   diceUsed        The number of dice used.
     * @param   diceRolls       The number of times dice is rolled divided by
     *                          10.
     * @return  tallyResults    String holding information about this run.
     *                          First number in string holds the number of dice
     *                          used, second number in the string holds the
     *                          number of times dice was rolled, and the
     *                          remaining rerpresents the number of times a
     *                          certain number was obtained. E.g.
     *                          "1 3 5 6 7 1 2 4 0 0 0 0 0 0"
     *                          1 = dice used
     *                          3 = times dice rolled
     *                          5 = number of times "1" was rolled
     *                          6 = number of times "2" was rolled
     *                          7 = number of times "3" was rolled etc...
     * 
     * Postcondition:
     * - tallyResults has 14 substrings all separeted by a space.
     **************************************************************************/
    // Initialise a vector of size 14 each containing 0.
    std::vector<int> tallyResults(14, 0);
    tallyResults[0] = diceUsed;
    tallyResults[1] = diceRolls;

    // Roll dice diceRolls*10 amount of times.
    for (int i = 0; i < diceRolls*10; i++) {
        int diceResultTotal = 0;
        // Rolls dice either once or twice.
        for (int j = 0; j < diceUsed; j++) {
            int dieResult = std::rand() % 6 + 1;
            // Adds current dice roll to total.
            // Significant if there is more than 1 die used.
            diceResultTotal += dieResult;
        }

        // First two items in vector reserved for dice used and rolls.
        // Hence, an "n" dice roll will be the n+1 element of the vector.
        tallyResults[diceResultTotal+1]++;
    }

    return vectorToString(tallyResults);
}

void printTableFromVector(std::vector<int> tableData) {
    /***************************************************************************
     * Prints a result table using data from a vector.
     * 
     * @param   tableData   14-element vector containing results and info from
     *                      die rolling experiment.
     * 
     * Precondition:
     * - tableData follows a similar format to tallyResults above. I.E. first
     *   two elements are information on how many dice used and how many times
     *   it was rolled, and then the rest are information on how many times each
     *   number was rolled.
     **************************************************************************/
    std::cout << std::endl;
    std::cout << "You rolled " << tableData[0] << " dice " << tableData[1]
        << "0 times." << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    
    // Range of dice rolls. Used to display 1-6 only for experiments where only
    // one die is used, and display 2-12 is 2 were used.
    int lo = tableData[0] < 2 ? 1 : 2;
    int hi = lo == 1 ? 6 : 12;
    for (lo; lo <= hi; lo++) {
        // Formatting: Add extra space before number if single digit.
        if (lo < 10) {
            std::cout << " ";
        }
        std::cout << lo << ": " << std::string(tableData[lo+1], '*')
            << std::endl;
    }
}

void appendToFile(std::string filename, std::string lineToWrite) {
    /***************************************************************************
     * Appends a single line of text into a file.
     * 
     * @param   filename    Name of the file to be edited.
     * @param   lineToWrite String to be appended on to file.
     * 
     * Precondition:
     * - lineToWrite cannot be empty.
     **************************************************************************/
    std::ofstream savedFile;
    savedFile.open(filename, std::ios_base::app);
    savedFile << lineToWrite << "\n";
    savedFile.close();
}

void displayAllDataFromFile(std::string filename) {
    /***************************************************************************
     * Displays dice data stored in a file where each line is a stringified
     * format of tallyResults in the function generateTable.
     * 
     * @param   filename    Name of the file containing data.
     * 
     * Precondition:
     * - File must be in the format specified above.
     **************************************************************************/
    // Load data.
    std::vector<std::string> tallyData = createLists(filename);
    
    // Handle empty/non-existent file.
    if (tallyData.empty()) {
        std::cout << std::endl << "Error: Data can't be loaded as no tables"
            << std::endl << "have been saved yet." << std::endl;
            return;
    }
    
    // Print each table.
    for (int i = 0; i < tallyData.size(); i++) {
        printTableFromVector(stringToVector(tallyData[i]));
    }
}

bool processChoice (int userChoice) {
    /***************************************************************************
     * Processes user input to show correct functionality.
     * 
     * @param   userChoice  User's choice.
     * @return  bool        false if user wishes to exit program,
     *                      true otherwise.
     * 
     * Precondition:
     * - userChoice must be from 0-5.
     **************************************************************************/
    // Switch statement has the precondition that the numbers are from 0-5
    switch (userChoice) {
        case 1: // Case 1: Displays information about the program.
                displayText("TallyAbout.txt");
                system("pause");
                break;
        case 2: {
                // Case 2: Loads and stores data from a file.
                std::vector<std::string> tallyData = 
                    createLists("savedTallyData.txt");
                // Handle empty/non-existent file.
                if (tallyData.empty()) {
                    std::cout << std::endl
                        << "Error: Data can't be loaded as no tables"
                        << std::endl << "have been saved yet." << std::endl;
                } else {
                    // Latest item in the file is loaded into last generated
                    // table as per Gavin's response in the forum.
                    lastGeneratedTable = tallyData.back();
                }
                system("pause");
                break;
            }
        case 3: {
                // Case 3: Generates a table of results from the experiment
                // based on user's specified conditions.
                std::cout << std::endl;
                int diceUsed = getIntInput("How many dice to roll (1-2): ",
                                           1,
                                           2);
                int diceRolls = getIntInput("How many times to roll (1-10): ",
                                           1,
                                           10);
                lastGeneratedTable = generateTable(diceUsed, diceRolls);
                // Converts stringified table results to vector first before
                // printing because printing from a vector was more efficient
                // than printing from a string.
                printTableFromVector(stringToVector(lastGeneratedTable));
                system("pause");
                break;
        }
        case 4: {
                // Case 4: Save last generated table to a file.
                // Checks first if a table has been generated. Prints a message
                // if not.
                if (lastGeneratedTable == "") {
                    std::cout << std::endl << "Generate a table first before"
                        << "saving to a file." <<std::endl;
                } else {
                    // Prints last generated table.
                    printTableFromVector(stringToVector(lastGeneratedTable));
                    // Prompts user if they want to save the last generated
                    // table.
                    std::cout << std::endl
                        << "Do you want to save this data - (y/n): ";
                    std::string userChoice;
                    std::cin >> userChoice;
                    // Handles user choice.
                    if (userChoice == "y") {
                        appendToFile("savedTallyData.txt", lastGeneratedTable);
                        std::cout << std::endl
                            << "These statistics are now saved." << std::endl;
                    }
                }
                system("pause");
                break;
        }
        case 5: // Case 5: Displays all experiment date stored in file.
                displayAllDataFromFile("savedTallyData.txt");
                system("pause");
                break;
    }

    // Return true or false to determine if program should exit.
    return userChoice > 0 ? true : false;
}

int main() {
    // Initialise program to run.
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