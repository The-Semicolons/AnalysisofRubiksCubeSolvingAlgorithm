// main.c : This file contains the 'main' function. Program execution begins and ends there.
// File Created by : Utkarsh Gupta [28.09.2021 22:35:54]
// 

// Importing Header Files
#include <time.h>
#include <stdio.h>
//#include <iostream>

// Local Header Files
#include "cube.h"
#include "logger.h"
#include "markovchain.h"
#include "display.h"

/// <summary>
/// Program execution starts and ends here.
/// </summary>
int main(void) {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	Cube rubiksCube = Cube();
	MarkovChain scrambler = MarkovChain();

	int noOfSteps;
	std::vector<std::string> steps;
	std::string tempString;

	Display::welcomeMessage();

	while (true) {
		int input;

		input = Display::displayMenu();

		switch (input) {
		case 1:
			
			break;
		case 21:
			SetConsoleTextAttribute(hConsole, 4);
			std::cout << "For how many number of steps you would like to scramble the cube? ";
			SetConsoleTextAttribute(hConsole, 15);
			std::cin >> noOfSteps;
			steps = scrambler.generateMoves(noOfSteps);
			SetConsoleTextAttribute(hConsole, 2);
			std::cout << "Scrambling moves : ";
			for (int i = 0; i < noOfSteps; i++) {
				std::cout << steps[i] << ", ";
			}
			std::cout << std::endl;
			SetConsoleTextAttribute(hConsole, 8);
			std::cout << "Performing scrambling on the cube." << std::endl;
			rubiksCube.move(steps);
			SetConsoleTextAttribute(hConsole, 15);
			Display::printCube(rubiksCube);
			SetConsoleTextAttribute(hConsole, 15);
			break;
		case 22:
			SetConsoleTextAttribute(hConsole, 4);
			std::cout << "For how many number of steps you would like to scramble the cube? ";
			SetConsoleTextAttribute(hConsole, 15);
			std::cin >> noOfSteps;
			SetConsoleTextAttribute(hConsole, 4);
			std::cout << "Enter steps (R1, R2, R3, L1, L2, L3, F1, F2, F3, U1, U2, U3, B1, B2, B3, D1, D2, D3)" << std::endl;
			for (int i = 0; i < noOfSteps; i++) {
				SetConsoleTextAttribute(hConsole, 4);
				std::cout << i + 1 << " : ";
				SetConsoleTextAttribute(hConsole, 15);
				std::cin >> tempString;
				steps.insert(steps.end(), tempString);
				SetConsoleTextAttribute(hConsole, 8);
				std::cout << "Performing scrambling on the cube." << std::endl;
				rubiksCube.move(steps);
				SetConsoleTextAttribute(hConsole, 15);
				Display::printCube(rubiksCube);
			}
			break;
		case 23:

			break;
		case 3:

			break;
		case 4:

			break;
		case 5:

			break;
		case 6:

			break;
		default:
			break;
		}
	}
	
	return 0;
}

