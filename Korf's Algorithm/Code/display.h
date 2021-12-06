// display.h : This file contains the "Display" class.
// File Created by : Utkarsh Gupta [9.10.2021 12:02:38]
// 

#pragma once

// Header Files
#include <iostream>
#include <windows.h>

// Local Header Files
#include "cube.h"

/// <summary>
/// Class used for all functions related to printing data/messages on console.
/// </summary>
class Display {
private:
	/// <summary>
	/// Function converts the integer to it's correspongding Colour in the cube.
	/// </summary>
	/// <param name="num">Integer of which the colour needs to be rturned.</param>
	/// <returns>First character of the colour. </returns>
	static char printColor(int num) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		switch (num) {
		case 0:
			SetConsoleTextAttribute(hConsole, 12);
			return 'R';
		case 1:
			SetConsoleTextAttribute(hConsole, 9);
			return 'B';
		case 2:
			SetConsoleTextAttribute(hConsole, 6);
			return 'Y';
		case 3:
			SetConsoleTextAttribute(hConsole, 10);
			return 'G';
		case 4:
			SetConsoleTextAttribute(hConsole, 15);
			return 'W';
		case 5:
			SetConsoleTextAttribute(hConsole, 14);
			return 'O';
		default:
			throw("ERROR : Invalid integer input.");
		}
	}

public:
	/// <summary>
	/// Displays the welcome message for Korf Algorithm.
	/// </summary>
	static void welcomeMessage(void) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 15);
		std::cout << "\n Richard E. Korf's Rubik's Cube Solving Algorithm\n\n"
			<< "|================================================| \n\n";
		
	}

	/// <summary>
	/// Prints the current state of the Rubik's cube in console.
	/// </summary>
	/// <param name="a"> Object of class "Cube", which is needed to be printed.</param>
	static void printCube(Cube a) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		std::cout << "Current state of the cube ->" << std::endl
			<< "        =========\n";

		for (int i = 0; i < LENGTH; i++) {
			std::cout << "        | ";

			for (int j = 0; j < BREADTH; j++) {
				std::cout << printColor(a.currentState[YELLOW][i][j]) << " ";
				SetConsoleTextAttribute(hConsole, 15);
			}
			std::cout << "|" << std::endl;
		}

		for (int i = 0; i < 33; i++) {
			std::cout << "=";
		}

		std::cout << std::endl;

		for (int i = 0; i < LENGTH; i++) {
			std::cout << "| ";

			for (int j = 0; j < BREADTH; j++) {
				std::cout << printColor(a.currentState[BLUE][i][j]) << " ";
				SetConsoleTextAttribute(hConsole, 15);
			}

			std::cout << "| ";

			for (int j = 0; j < BREADTH; j++) {
				std::cout << printColor(a.currentState[RED][i][j]) << " ";
				SetConsoleTextAttribute(hConsole, 15);
			}

			std::cout << "| ";

			for (int j = 0; j < BREADTH; j++) {
				std::cout << printColor(a.currentState[GREEN][i][j]) << " ";
				SetConsoleTextAttribute(hConsole, 15);
			}

			std::cout << "| ";

			for (int j = 0; j < BREADTH; j++) {
				std::cout << printColor(a.currentState[ORANGE][i][j]) << " ";
				SetConsoleTextAttribute(hConsole, 15);
			}

			std::cout << "|" << std::endl;
		}

		for (int i = 0; i < 33; i++) {
			std::cout << "=";
		}

		std::cout << std::endl;

		for (int i = 0; i < LENGTH; i++) {
			std::cout << "        | ";

			for (int j = 0; j < BREADTH; j++) {
				std::cout << printColor(a.currentState[WHITE][i][j]) << " ";
				SetConsoleTextAttribute(hConsole, 15);
			}

			std::cout << "|" << std::endl;
		}

		std::cout << "        =========\n";
	}

	/// <summary>
	/// Displays the menu for the applications.
	/// </summary>
	/// <returns>Integer based on the input from the user.</returns>
	static int displayMenu(void) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 3);
		std::string input;
		std::cout << "          Menu" << std::endl
			<< "========================" << std::endl
			<< "1.          Input Cube State" << std::endl
			<< "2.             Scramble Cube" << std::endl
			<< "3.                Solve Cube" << std::endl
			<< "4.       Algorithm Analytics" << std::endl
			<< "5.                     About" << std::endl
			<< "6.                      Help" << std::endl
			<< "7.                      Exit" << std::endl
			<< "Choice: ";
		SetConsoleTextAttribute(hConsole, 15);
		std::cin >> input;
		if (input == "1" || input == "Input Cube State") {
			return 1;
		}
		else if (input == "2" || input == "Scramble Cube") {
			SetConsoleTextAttribute(hConsole, 6);
			std::cout << std::endl << "How you would like to scramble the cube?" << std::endl
				<< "========================================" << std::endl
				<< "1.          Automatically (using Markov chain algorithm)" << std::endl
				<< "2.               Manually" << std::endl
				<< "3.    Return to main menu" << std::endl
				<< "4.       Exit application" << std::endl
				<< "Choose: ";
			SetConsoleTextAttribute(hConsole, 15);
			std::cin >> input;
			if (input == "1" || input == "Automatically") {
				return 21;
			}
			else if (input == "2" || input == "Manually") {
				return 22;
			}
			else if (input == "3" || input == "Return") {
				std::cout << std::endl;
				return 23;
			}
			else if (input == "4" || input == "Exit") {
				exit(0);
			}
			else {
				throw("ERROR : Invalid input.");
			}
		}
		else if (input == "3" || input == "Solve Cube") {
			return 3;
		}
		else if (input == "4" || input == "Algorithm Analytics") {
			// Needs work
			return 4;
		}
		else if (input == "5" || input == "About") {
			SetConsoleTextAttribute(hConsole, 8);
			std::cout << "In 1997 Richard Korf[16] announced an algorithm with which he had optimally solved random instances of the cube. Of the ten random cubes he did, none"
				<< "required more than 18 face turns.The method he used is called IDA * andis described in his paper \"Finding Optimal Solutions to Rubik's Cube Using Pattern"
				<< "Databases\". Korf describes this method as follows:" << std::endl << std::endl
				<< "IDA * is a depth - first search that looks for increasingly longer solutions in a series of iterations, using a lower - bound heuristic to prune branches"
				<< "once a lower bound on their length exceeds the current iterations bound." << std::endl << std::endl
				<< "It works roughly as follows.First he identified a number of subproblems that are small enough to be solved optimally.He used :" << std::endl
				<< "1. The cube restricted to only the corners, not looking at the edges." << std::endl
				<< "2. The cube restricted to only 6 edges, not looking at the corners nor at the other edges." << std::endl
				<< "3. The cube restricted to the other 6 edges." << std::endl << std::endl
				<< "Clearly the number of moves required to solve any of these subproblems is a lower bound for the number of moves needed to solve the entire cube."
				<< std::endl << std::endl;
			SetConsoleTextAttribute(hConsole, 15);
		}
		else if (input == "6" || input == "Help") {
			return 7;
		}
		else if (input == "7" || input == "Exit") {
			exit(0);
		}
		else {
			throw("ERROR: Invalid Input");
		}
	}
};
