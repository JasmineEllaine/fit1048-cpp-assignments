/*
 * Developed for the LSST Data Management System.
 * This product includes software developed by the LSST Project
 * (https://www.lsst.org).
 * See the COPYRIGHT file at the top-level directory of this distribution
 * for details of code ownership.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>

int runMenu() {
	// Display menu header.
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl
		<< "The Tally Ho Probability Generator" << std::endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	// Display menu options.
	std::cout << "[0] End Testing the Program" << std::endl
		<< "[1] Display \"About\" Information" << std::endl
		<< "[2] Read and store data from files" << std::endl
		<< "[3] Generate a Dice Tally Table" << std::endl
		<< "[4] Save Tally Statistics to a File" << std::endl
		<< "[5] Load Tally Statistics from a File" << std::endl;
	// Display prompt.
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl
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

int main() {
	runMenu();
	int userChoice = getValidInput();
	std::cout << userChoice << std::endl;
	system("pause");

	return 0;
}