/*
 * Author: Jasmine Banares
 * Student ID: 2973 8660
 * Project: Assignment 3: Custom Mastermind Game (Hackamon!)
 * 
 * This application enables the player to start a single player game of
 * Hackamon! – a themed game of mastermind where instead of cracking a colour
 * code, you crack passwords to a computer.
 * 
 * IMPORTANT NOTE TO MARKER: Please disable "srand(time(0))" from main() to get
 * a more predictable passcode to crack during the game. The first passcode will
 * always be "3112" if disabled.
 */

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

void pause() {
    /***************************************************************************
     * Pauses the program until the user presses ENTER. Alternative to
     * system("pause") because I use a MAC.
     **************************************************************************/
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
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

void displayTextLineByLine(std::string filename) {
    /***************************************************************************
     * Prints out contents of a file into the console line by line. The next
     * line of text can be shown by pressing ENTER on the keyboard.
     * 
     * @param   filename    Name of the text file to be displayed.
     * @precondition        The different lines should be delimited by an empty
     *                      line. E.g. if the file given is as below
     * 
     *                      1  "Hello.
     *                      2  I am Jasmine.
     *                      3
     *                      4  What is your name?""
     * 
     *                      Lines 1 and 2 will be shown in the terminal at the
     *                      same time. The user will then have to press enter to
     *                      see line 4.
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

    // Display message line by line. 
    std::string textline;
    while (std::getline(file, textline)) {
        // Waits for user to press ENTER before displaying next line.
        if (textline == "") {
            std::cin.get();
        } else {
            std::cout << textline << std::endl;
        }
    }
    file.close();
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

int main() {
    // Randomises passcode generated every time application starts. Disable if 
    // you need the passcodes to be the same every run.
    srand(time(0));

    // Display the home screen.
    displayTextFromFile("hackamonStartDisplay.txt");
    std::vector<std::string> choices = {"NEW", "LOAD"};
    std::string prompt = "Write either [NEW] or [LOAD]: ";
    std::string invalidInputPrompt = "Invalid input. Please only write either \"NEW\" or \"LOAD\": ";
    std::string startGameType = getStringInput(prompt, invalidInputPrompt, choices);

    Hackamon game = Hackamon();
    game.run(startGameType);

    return 0;
}