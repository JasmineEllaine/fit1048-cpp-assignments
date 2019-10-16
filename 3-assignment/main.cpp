#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "hackamon.h"
#include "main.h"
#include "player.h"

void displayTextFromFile(std::string filename) {
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
            << std::endl << "either doesn't exist or is empty! :(" << std::endl;
        return;
    }

    // Display message.
    std::string textline;
    while (std::getline(file, textline)) {
        std::cout << textline << std::endl;
    }
    file.close();
}

std::string getStringInput(std::string prompt,
                           std::string errorMessage,
                           std::vector<std::string> choices) {
    /***************************************************************************
     * Asks user for a string input, with the valid responses being the items in
     * choices.
     * 
     * @param   prompt          Prompt to be displayed to the user.
     * @param   errorMessage    Error message prompt to be displayed if input is
     *                          is invalid. Pass "" if not needed.
     * @param   choices         Possible responses by the user. Pass null if not
     *                          needed. 
     * @return  userInput       Input selected by user from choices.
     **************************************************************************/
    std::cout << prompt;
    std::string userInput;
    bool notValid = true;
    while (notValid) {
        std::cin >> userInput;
        // Check if userInput is in the allowed choices.
        if (std::find(choices.begin(), choices.end(), userInput) != choices.end()
            || choices[0] == "") {
            // Value found.
            notValid = false;
        } else {
            std::cout << std::endl << errorMessage;
        }
    }
    
    return userInput;
}

int main() {
    // Display the intro screen.
    displayTextFromFile("hackamonStartDisplay.txt");
    std::vector<std::string> choices = {"NEW", "LOAD"};
    std::string prompt = "Write either [NEW] or [LOAD]: ";
    std::string invalidInputPrompt = "Invalid input. Please only write either \"NEW\" or \"LOAD\": ";
    std::string startGameType = getStringInput(prompt, invalidInputPrompt, choices);

    Hackamon *hackamon;
    hackamon->run(startGameType);

    return 0;
}