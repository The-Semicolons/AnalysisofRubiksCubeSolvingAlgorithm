// cube.h : This file contains the "Cube" class.
// File Created  by : Utkarsh Gupta [28.09.2021 22:35:54]
// 

#pragma once

#include<vector>
#include<string>

// Red coloured face.
#define RED 0
// Blue coloured face.
#define BLUE 1
// Yellow coloured face.
#define YELLOW 2
// Green coloured face.
#define GREEN 3
// White coloured face.
#define WHITE 4
// Orange coloured face.
#define ORANGE 5

// FACES: Stores number of faces of the cube.
#define FACES 6
// LENGTH: Stores number of cubies length wise.
#define LENGTH 3
// BREADTH: Stores number of cubies length wise.
#define BREADTH 3

/// <summary>
/// This class contains the functions and variables
/// that are responsible for controling the states
/// and movement of the cube.
/// </summary>
class Cube {

// Private flag <|
private:
	/// <summary>
	/// Constant variable. Integer array of size 6x3x3.
	/// Stores the solved/goal/unscrambled state of cube.
	/// </summary>
	const int goalState[FACES][LENGTH][BREADTH] = {
												   {{0,0,0},
													{0,0,0},
													{0,0,0}
												   },
												   {{1,1,1},
													{1,1,1},
													{1,1,1}
												   },
												   {{2,2,2},
													{2,2,2},
													{2,2,2}
												   },
												   {{3,3,3},
													{3,3,3},
													{3,3,3}
												   },
												   {{4,4,4},
													{4,4,4},
													{4,4,4}
												   },
												   {{5,5,5},
													{5,5,5},
													{5,5,5}
												   }
	};

	/// <summary>
	/// Temporary array to store the state of the cube.
	/// </summary>
	int tempState[FACES][LENGTH][BREADTH];

	/// <summary>
	/// This function copies the current state of the cube
	/// to a temporary variable, so that actions can be
	/// performed directly onto the current state.
	/// </summary>
	void copyCurrentStateToTempState() {
		for (int i = 0; i < FACES; i++) {
			for (int j = 0; j < LENGTH; j++) {
				for (int k = 0; k < BREADTH; k++) {
					this->tempState[i][j][k] = this->currentState[i][j][k];
				}
			}
		}
	}

// Public flag <|
public:
	/// <summary>
	/// Integer array of size 6x3x3. Stores the
	/// current (can be solved or unsolved) state of cube.
	/// </summary>
	int currentState[FACES][LENGTH][BREADTH] = {
												{{0,0,0},
												 {0,0,0},
												 {0,0,0}
												},
												{{1,1,1},
												 {1,1,1},
												 {1,1,1}
												},
												{{2,2,2},
												 {2,2,2},
												 {2,2,2}
												},
												{{3,3,3},
												 {3,3,3},
												 {3,3,3}
												},
												{{4,4,4},
												 {4,4,4},
												 {4,4,4}
												},
												{{5,5,5},
												 {5,5,5},
												 {5,5,5}
												}
	};

	/// <summary>
	/// Default constructor: Initialises and instance of class Cube.
	/// </summary>
	Cube(void) {

	}

	/// <summary>
	/// Constructor: Initialises and instance of class Cube.
	/// </summary>
	/// <param name="state">The state of the cube through which you wanted to initialise the cube.</param>
	Cube(int state[6][3][3]) {
		for (int i = 0; i < FACES; i++) {
			for (int j = 0; j < LENGTH; j++) {
				for (int k = 0; k < BREADTH; k++) {
					this->currentState[i][j][k] = state[i][j][k];
				}
			}
		}
	}

	/// <summary>
	/// Destructor
	/// </summary>
	~Cube(void) {

	}

	/// <summary>
	/// Checks whether the cube is solved or not by comparing
	/// the current state of the cube with the goal state of
	/// the cube.
	/// </summary>
	/// <returns>True: if cube is solved. False: if cube is not solved.</returns>
	bool isSolved(void) {
		for (int i = 0; i < FACES; i++) {
			for (int j = 0; j < LENGTH; j++) {
				for (int k = 0; k < BREADTH; k++) {
					if (this->currentState[i][j][k] != this->goalState[i][j][k]) {
						return false;
					}
				}
			}
		}
		return true;
	}

	/// <summary>
	/// Simulates the move R1 of the cube. Rotates the right face 90 degrees clockwise.
	/// </summary>
	void moveR1(void) {
		this->copyCurrentStateToTempState();
		for (int i = 0; i < 3; i++) {
			this->currentState[YELLOW][i][2] = this->tempState[RED][i][2];
			this->currentState[ORANGE][i][2] = this->tempState[YELLOW][i][2];
			this->currentState[WHITE][i][2] = this->tempState[ORANGE][i][2];
			this->currentState[RED][i][2] = this->tempState[WHITE][i][2];
			for (int j = 0; j < 3; j++) {
				this->currentState[GREEN][i][j] = this->tempState[GREEN][2 - j][i];
			}
		}
	}

	/// <summary>
	/// Simulates the move R2 of the cube. Rotates the right face 180 degrees clockwise.
	/// </summary>
	void moveR2(void) {
		this->copyCurrentStateToTempState();
		for (int i = 0; i < 3; i++) {
			this->currentState[YELLOW][i][2] = this->tempState[WHITE][i][2];
			this->currentState[ORANGE][i][2] = this->tempState[RED][i][2];
			this->currentState[WHITE][i][2] = this->tempState[YELLOW][i][2];
			this->currentState[RED][i][2] = this->tempState[ORANGE][i][2];
			for (int j = 0; j < 3; j++) {
				this->currentState[GREEN][i][j] = this->tempState[GREEN][2 - i][2 - j];
			}
		}
	}

	/// <summary>
	/// Simulates the move R' of the cube. Rotates the right face 90 degrees anti-clockwise.
	/// </summary>
	void moveR3(void) {
		this->copyCurrentStateToTempState();
		for (int i = 0; i < 3; i++) {
			this->currentState[YELLOW][i][2] = this->tempState[ORANGE][i][2];
			this->currentState[ORANGE][i][2] = this->tempState[WHITE][i][2];
			this->currentState[WHITE][i][2] = this->tempState[RED][i][2];
			this->currentState[RED][i][2] = this->tempState[YELLOW][i][2];
			for (int j = 0; j < 3; j++) {
				this->currentState[GREEN][i][j] = this->tempState[GREEN][j][2 - i];
			}
		}
	}

	/// <summary>
	/// Simulates the move L1 of the cube. Rotates the left face 90 degrees clockwise.
	/// </summary>
	void moveL1(void) {
		this->copyCurrentStateToTempState();
		for (int i = 0; i < 3; i++) {
			this->currentState[YELLOW][i][0] = this->tempState[RED][i][0];
			this->currentState[ORANGE][i][0] = this->tempState[YELLOW][i][0];
			this->currentState[WHITE][i][0] = this->tempState[ORANGE][i][0];
			this->currentState[RED][i][0] = this->tempState[WHITE][i][0];
			for (int j = 0; j < 3; j++) {
				this->currentState[BLUE][i][j] = this->tempState[BLUE][2 - j][i];
			}
		}
	}

	/// <summary>
	/// Simulates the move L2 of the cube. Rotates the left face 180 degrees clockwise.
	/// </summary>
	void moveL2(void) {
		this->copyCurrentStateToTempState();
		for (int i = 0; i < 3; i++) {
			this->currentState[YELLOW][i][0] = this->tempState[WHITE][i][0];
			this->currentState[ORANGE][i][0] = this->tempState[RED][i][0];
			this->currentState[WHITE][i][0] = this->tempState[YELLOW][i][0];
			this->currentState[RED][i][0] = this->tempState[ORANGE][i][0];
			for (int j = 0; j < 3; j++) {
				this->currentState[BLUE][i][j] = this->tempState[BLUE][2 - i][2 - j];
			}
		}
	}

	/// <summary>
	/// Simulates the move L' of the cube. Rotates the left face 90 degrees anti-clockwise.
	/// </summary>
	void moveL3(void) {
		this->copyCurrentStateToTempState();
		for (int i = 0; i < 3; i++) {
			this->currentState[YELLOW][i][0] = this->tempState[ORANGE][i][0];
			this->currentState[ORANGE][i][0] = this->tempState[WHITE][i][0];
			this->currentState[WHITE][i][0] = this->tempState[RED][i][0];
			this->currentState[RED][i][0] = this->tempState[YELLOW][i][0];
			for (int j = 0; j < 3; j++) {
				this->currentState[BLUE][i][j] = this->tempState[BLUE][j][2 - i];
			}
		}
	}

	/// <summary>
	/// Simulates the move F1 of the cube. Rotates the front face 90 degrees clockwise.
	/// </summary>
	void moveF1(void) {
		this->copyCurrentStateToTempState();
		for (int i = 0; i < 3; i++) {
			this->currentState[YELLOW][i][2] = this->tempState[RED][i][2];
			this->currentState[ORANGE][i][2] = this->tempState[YELLOW][i][2];
			this->currentState[WHITE][i][2] = this->tempState[ORANGE][i][2];
			this->currentState[RED][i][2] = this->tempState[WHITE][i][2];
			for (int j = 0; j < 3; j++) {
				this->currentState[RED][i][j] = this->tempState[RED][2 - j][i];
			}
		}
	}

	/// <summary>
	/// Simulates the move F2 of the cube. Rotates the front face 180 degrees clockwise.
	/// </summary>
	void moveF2(void) {
		this->copyCurrentStateToTempState();
		for (int i = 0; i < 3; i++) {
			this->currentState[YELLOW][i][2] = this->tempState[WHITE][i][2];
			this->currentState[ORANGE][i][2] = this->tempState[RED][i][2];
			this->currentState[WHITE][i][2] = this->tempState[YELLOW][i][2];
			this->currentState[RED][i][2] = this->tempState[ORANGE][i][2];
			for (int j = 0; j < 3; j++) {
				this->currentState[GREEN][i][j] = this->tempState[GREEN][2 - i][2 - j];
			}
		}
	}

	/// <summary>
	/// Simulates the move F' of the cube. Rotates the front face 90 degrees anti-clockwise.
	/// </summary>
	void moveF3(void) {
		this->copyCurrentStateToTempState();
		for (int i = 0; i < 3; i++) {
			this->currentState[YELLOW][i][2] = this->tempState[ORANGE][i][2];
			this->currentState[ORANGE][i][2] = this->tempState[WHITE][i][2];
			this->currentState[WHITE][i][2] = this->tempState[RED][i][2];
			this->currentState[RED][i][2] = this->tempState[YELLOW][i][2];
			for (int j = 0; j < 3; j++) {
				this->currentState[GREEN][i][j] = this->tempState[GREEN][j][2 - i];
			}
		}
	}
	/// <summary>
	/// Simulates the move U1 of the cube. Rotates the upper face 90 degrees clockwise.
	/// </summary>
	void moveU1(void) {
		this->copyCurrentStateToTempState();
		for (int i = 0; i < 3; i++) {
			this->currentState[YELLOW][i][2] = this->tempState[RED][i][2];
			this->currentState[ORANGE][i][2] = this->tempState[YELLOW][i][2];
			this->currentState[WHITE][i][2] = this->tempState[ORANGE][i][2];
			this->currentState[RED][i][2] = this->tempState[WHITE][i][2];
			for (int j = 0; j < 3; j++) {
				this->currentState[GREEN][i][j] = this->tempState[GREEN][2 - j][i];
			}
		}
	}

	/// <summary>
	/// Simulates the move U2 of the cube. Rotates the upper face 180 degrees clockwise.
	/// </summary>
	void moveU2(void) {
		this->copyCurrentStateToTempState();
		for (int i = 0; i < 3; i++) {
			this->currentState[YELLOW][i][2] = this->tempState[WHITE][i][2];
			this->currentState[ORANGE][i][2] = this->tempState[RED][i][2];
			this->currentState[WHITE][i][2] = this->tempState[YELLOW][i][2];
			this->currentState[RED][i][2] = this->tempState[ORANGE][i][2];
			for (int j = 0; j < 3; j++) {
				this->currentState[GREEN][i][j] = this->tempState[GREEN][2 - i][2 - j];
			}
		}
	}

	/// <summary>
	/// Simulates the move U' of the cube. Rotates the upper face 90 degrees anti-clockwise.
	/// </summary>
	void moveU3(void) {
		this->copyCurrentStateToTempState();
		for (int i = 0; i < 3; i++) {
			this->currentState[YELLOW][i][2] = this->tempState[ORANGE][i][2];
			this->currentState[ORANGE][i][2] = this->tempState[WHITE][i][2];
			this->currentState[WHITE][i][2] = this->tempState[RED][i][2];
			this->currentState[RED][i][2] = this->tempState[YELLOW][i][2];
			for (int j = 0; j < 3; j++) {
				this->currentState[GREEN][i][j] = this->tempState[GREEN][j][2 - i];
			}
		}
	}
	/// <summary>
	/// Simulates the move B1 of the cube. Rotates the back face 90 degrees clockwise.
	/// </summary>
	void moveB1(void) {
		this->copyCurrentStateToTempState();
		for (int i = 0; i < 3; i++) {
			this->currentState[YELLOW][i][2] = this->tempState[RED][i][2];
			this->currentState[ORANGE][i][2] = this->tempState[YELLOW][i][2];
			this->currentState[WHITE][i][2] = this->tempState[ORANGE][i][2];
			this->currentState[RED][i][2] = this->tempState[WHITE][i][2];
			for (int j = 0; j < 3; j++) {
				this->currentState[GREEN][i][j] = this->tempState[GREEN][2 - j][i];
			}
		}
	}

	/// <summary>
	/// Simulates the move B2 of the cube. Rotates the back face 180 degrees clockwise.
	/// </summary>
	void moveB2(void) {
		this->copyCurrentStateToTempState();
		for (int i = 0; i < 3; i++) {
			this->currentState[YELLOW][i][2] = this->tempState[WHITE][i][2];
			this->currentState[ORANGE][i][2] = this->tempState[RED][i][2];
			this->currentState[WHITE][i][2] = this->tempState[YELLOW][i][2];
			this->currentState[RED][i][2] = this->tempState[ORANGE][i][2];
			for (int j = 0; j < 3; j++) {
				this->currentState[GREEN][i][j] = this->tempState[GREEN][2 - i][2 - j];
			}
		}
	}

	/// <summary>
	/// Simulates the move B' of the cube. Rotates the back face 90 degrees anti-clockwise.
	/// </summary>
	void moveB3(void) {
		this->copyCurrentStateToTempState();
		for (int i = 0; i < 3; i++) {
			this->currentState[YELLOW][i][2] = this->tempState[ORANGE][i][2];
			this->currentState[ORANGE][i][2] = this->tempState[WHITE][i][2];
			this->currentState[WHITE][i][2] = this->tempState[RED][i][2];
			this->currentState[RED][i][2] = this->tempState[YELLOW][i][2];
			for (int j = 0; j < 3; j++) {
				this->currentState[GREEN][i][j] = this->tempState[GREEN][j][2 - i];
			}
		}
	}
	/// <summary>
	/// Simulates the move D1 of the cube. Rotates the down face 90 degrees clockwise.
	/// </summary>
	void moveD1(void) {
		this->copyCurrentStateToTempState();
		for (int i = 0; i < 3; i++) {
			this->currentState[YELLOW][i][2] = this->tempState[RED][i][2];
			this->currentState[ORANGE][i][2] = this->tempState[YELLOW][i][2];
			this->currentState[WHITE][i][2] = this->tempState[ORANGE][i][2];
			this->currentState[RED][i][2] = this->tempState[WHITE][i][2];
			for (int j = 0; j < 3; j++) {
				this->currentState[GREEN][i][j] = this->tempState[GREEN][2 - j][i];
			}
		}
	}

	/// <summary>
	/// Simulates the move D2 of the cube. Rotates the down face 180 degrees clockwise.
	/// </summary>
	void moveD2(void) {
		this->copyCurrentStateToTempState();
		for (int i = 0; i < 3; i++) {
			this->currentState[YELLOW][i][2] = this->tempState[WHITE][i][2];
			this->currentState[ORANGE][i][2] = this->tempState[RED][i][2];
			this->currentState[WHITE][i][2] = this->tempState[YELLOW][i][2];
			this->currentState[RED][i][2] = this->tempState[ORANGE][i][2];
			for (int j = 0; j < 3; j++) {
				this->currentState[GREEN][i][j] = this->tempState[GREEN][2 - i][2 - j];
			}
		}
	}

	/// <summary>
	/// Simulates the move D' of the cube. Rotates the down face 90 degrees anti-clockwise.
	/// </summary>
	void moveD3(void) {
		this->copyCurrentStateToTempState();
		for (int i = 0; i < 3; i++) {
			this->currentState[YELLOW][i][2] = this->tempState[ORANGE][i][2];
			this->currentState[ORANGE][i][2] = this->tempState[WHITE][i][2];
			this->currentState[WHITE][i][2] = this->tempState[RED][i][2];
			this->currentState[RED][i][2] = this->tempState[YELLOW][i][2];
			for (int j = 0; j < 3; j++) {
				this->currentState[GREEN][i][j] = this->tempState[GREEN][j][2 - i];
			}
		}
	}

	/// <summary>
	/// This function performes a set of moves on the cube.
	/// </summary>
	/// <param name="moves">List of moves needs to be performed on the cube.</param>
	void move(std::vector<std::string> moves) {
		for (int i = 0; i < moves.size(); i++) {
			this->move(moves[i]);
		}
	}

	/// <summary>
	/// This function performes a specific move on the cube.
	/// </summary>
	/// <param name="move">The move that needs to be performed. </param>
	void move(std::string move) {
		if (move == "F1") {
			this->moveF1();
		}
		else if (move == "F2") {
			this->moveF2();
		}
		else if (move == "F3") {
			this->moveF3();
		}
		else if (move == "U1") {
			this->moveU1();
		}
		else if (move == "U2") {
			this->moveU2();
		}
		else if (move == "U3") {
			this->moveU3();
		}
		else if (move == "B1") {
			this->moveB1();
		}
		else if (move == "B2") {
			this->moveB2();
		}
		else if (move == "B3") {
			this->moveB3();
		}
		else if (move == "R1") {
			this->moveR1();
		}
		else if (move == "R2") {
			this->moveR2();
		}
		else if (move == "R3") {
			this->moveR3();
		}
		else if (move == "L1") {
			this->moveL1();
		}
		else if (move == "L2") {
			this->moveL2();
		}
		else if (move == "L3") {
			this->moveL3();
		}
		else if (move == "D1") {
			this->moveD1();
		}
		else if (move == "D2") {
			this->moveD2();
		}
		else if (move == "D3") {
			this->moveD3();
		}
	}
};