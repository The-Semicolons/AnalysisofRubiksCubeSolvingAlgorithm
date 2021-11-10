// markovchain.h : This file contains the "MarkovChain" class.
// File Created by : Utkarsh Gupta [28.09.2021 22:35:54]
// 

#include <time.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>

#pragma once

// Total number of states possible.
#define NO_OF_STATES 18

/// <summary>
/// This class is responsible for holding the functions and variables required to execute
/// the Markov chain algorithm.
/// </summary>
class MarkovChain {
// Private flag <|
private:
	/// <summary>
	/// All the eighteen possible moves of the cube.
	/// </summary>
	const std::string states[NO_OF_STATES] = { "F1", "F2", "F3", "R1", "R2", "R3", "L1", "L2", "L3", "B1", "B2", "B3", "U1", "U2", "U3", "D1", "D2", "D3" };

	/// <summary>
	/// Vector array to store scrambling steps.
	/// </summary>
	std::vector<std::string> steps;

	/// <summary>
	/// All the possible combinations of two consequent moves.
	/// </summary>
	const std::string transitionName[NO_OF_STATES][NO_OF_STATES] = {
		{ "F1F1", "F1F2", "F1F3", "F1R1", "F1R2", "F1R3", "F1L1", "F1L2", "F1L3", "F1B1", "F1B2", "F1B3", "F1U1", "F1U2", "F1U3", "F1D1", "F1D2", "F1D3" },
		{ "F2F1", "F2F2", "F2F3", "F2R1", "F2R2", "F2R3", "F2L1", "F2L2", "F2L3", "F2B1", "F2B2", "F2B3", "F2U1", "F2U2", "F2U3", "F2D1", "F2D2", "F2D3" },
		{ "F3F1", "F3F2", "F3F3", "F3R1", "F3R2", "F3R3", "F3L1", "F3L2", "F3L3", "F3B1", "F3B2", "F3B3", "F3U1", "F3U2", "F3U3", "F3D1", "F3D2", "F3D3" },
		{ "R1F1", "R1F2", "R1F3", "R1R1", "R1R2", "R1R3", "R1L1", "R1L2", "R1L3", "R1B1", "R1B2", "R1B3", "R1U1", "R1U2", "R1U3", "R1D1", "R1D2", "R1D3" },
		{ "R2F1", "R2F2", "R2F3", "R2R1", "R2R2", "R2R3", "R2L1", "R2L2", "R2L3", "R2B1", "R2B2", "R2B3", "R2U1", "R2U2", "R2U3", "R2D1", "R2D2", "R2D3" },
		{ "R3F1", "R3F2", "R3F3", "R3R1", "R3R2", "R3R3", "R3L1", "R3L2", "R3L3", "R3B1", "R3B2", "R3B3", "R3U1", "R3U2", "R3U3", "R3D1", "R3D2", "R3D3" },
		{ "L1F1", "L1F2", "L1F3", "L1R1", "L1R2", "L1R3", "L1L1", "L1L2", "L1L3", "L1B1", "L1B2", "L1B3", "L1U1", "L1U2", "L1U3", "L1D1", "L1D2", "L1D3" },
		{ "L2F1", "L2F2", "L2F3", "L2R1", "L2R2", "L2R3", "L2L1", "L2L2", "L2L3", "L2B1", "L2B2", "L2B3", "L2U1", "L2U2", "L2U3", "L2D1", "L2D2", "L2D3" },
		{ "L3F1", "L3F2", "L3F3", "L3R1", "L3R2", "L3R3", "L3L1", "L3L2", "L3L3", "L3B1", "L3B2", "L3B3", "L3U1", "L3U2", "L3U3", "L3D1", "L3D2", "L3D3" },
		{ "B1F1", "B1F2", "B1F3", "B1R1", "B1R2", "B1R3", "B1L1", "B1L2", "B1L3", "B1B1", "B1B2", "B1B3", "B1U1", "B1U2", "B1U3", "B1D1", "B1D2", "B1D3" },
		{ "B2F1", "B2F2", "B2F3", "B2R1", "B2R2", "B2R3", "B2L1", "B2L2", "B2L3", "B2B1", "B2B2", "B2B3", "B2U1", "B2U2", "B2U3", "B2D1", "B2D2", "B2D3" },
		{ "B3F1", "B3F2", "B3F3", "B3R1", "B3R2", "B3R3", "B3L1", "B3L2", "B3L3", "B3B1", "B3B2", "B3B3", "B3U1", "B3U2", "B3U3", "B3D1", "B3D2", "B3D3" },
		{ "U1F1", "U1F2", "U1F3", "U1R1", "U1R2", "U1R3", "U1L1", "U1L2", "U1L3", "U1B1", "U1B2", "U1B3", "U1U1", "U1U2", "U1U3", "U1D1", "U1D2", "U1D3" },
		{ "U2F1", "U2F2", "U2F3", "U2R1", "U2R2", "U2R3", "U2L1", "U2L2", "U2L3", "U2B1", "U2B2", "U2B3", "U2U1", "U2U2", "U2U3", "U2D1", "U2D2", "U2D3" },
		{ "U3F1", "U3F2", "U3F3", "U3R1", "U3R2", "U3R3", "U3L1", "U3L2", "U3L3", "U3B1", "U3B2", "U3B3", "U3U1", "U3U2", "U3U3", "U3D1", "U3D2", "U3D3" },
		{ "D1F1", "D1F2", "D1F3", "D1R1", "D1R2", "D1R3", "D1L1", "D1L2", "D1L3", "D1B1", "D1B2", "D1B3", "D1U1", "D1U2", "D1U3", "D1D1", "D1D2", "D1D3" },
		{ "D2F1", "D2F2", "D2F3", "D2R1", "D2R2", "D2R3", "D2L1", "D2L2", "D2L3", "D2B1", "D2B2", "D2B3", "D2U1", "D2U2", "D2U3", "D2D1", "D2D2", "D2D3" },
		{ "D3F1", "D3F2", "D3F3", "D3R1", "D3R2", "D3R3", "D3L1", "D3L2", "D3L3", "D3B1", "D3B2", "D3B3", "D3U1", "D3U2", "D3U3", "D3D1", "D3D2", "D3D3" }
	};

	/// <summary>
	/// Contains the probabilities of two consecutive moves.
	/// </summary>
	const std::vector<std::vector<int>> transitionMatrix{
		{ 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{ 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{ 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{ 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{ 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{ 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{ 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{ 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{ 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2},
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2},
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2},
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2},
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2},
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2},
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0},
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0},
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0},
	};

	/// <summary>
	/// This function multiplies two matrices A & B.
	/// </summary>
	/// <param name="A">First Matrix.</param>
	/// <param name="B">Second Matrix.</param>
	/// <returns>Matrix C as C=A*B</returns>
	std::vector<std::vector<int>> multiplyMatrix(std::vector<std::vector<int>> A, std::vector<std::vector<int>> B) {
		std::vector<std::vector<int>> C(NO_OF_STATES, std::vector<int>(NO_OF_STATES, 0));
		for (int i = 0; i < NO_OF_STATES; i++) {
			for (int j = 0; j < NO_OF_STATES; j++) {
				for (int k = 0; k < NO_OF_STATES; k++){
					C[i][j] += A[i][k] * B[k][j];
				}
			}
		}
		return C;
	}

// Public flag <|
public: 

	/// <summary>
	/// Default constructor: Initialises and instance of class Cube.
	/// </summary>
	MarkovChain() {

	}

	/// <summary>
	/// Destructor.
	/// </summary>
	~MarkovChain() {

	}

	/// <summary>
	/// Generates the number of steps to scramble of cube.
	/// </summary>
	/// <param name="num"> : Number of maximum steps.</param>
	/// <returns>An array of steps to be performed.</returns>
	std::vector<std::string> generateMoves(int num = 5) {
		float highestProbability;
		std::vector<std::vector<int>> tempTransitionMatrix = this->transitionMatrix;

		srand(time(0));
		int currentState = rand() % NO_OF_STATES;

		for (int i = 0; i < num; i++) {
			this->steps.insert(this->steps.end(), this->states[currentState]);
			if ((i + 1) % 2) {
				highestProbability = *std::min(tempTransitionMatrix[currentState].begin(), tempTransitionMatrix[currentState].end() - 1);
			}
			else {
				highestProbability = *std::max(tempTransitionMatrix[currentState].begin(), tempTransitionMatrix[currentState].end() - 1);
			}

			std::vector<int> temp;

			for (int j = 0; j < NO_OF_STATES; j++) {
				if (tempTransitionMatrix[currentState][j] == highestProbability){
					temp.insert(temp.end(), j);
				}
			}

			currentState = temp[(rand() % temp.size())];

			tempTransitionMatrix = this->multiplyMatrix(tempTransitionMatrix, this->transitionMatrix);
		}
		
		return steps;
	}
};                                                                                                                                                                                          