#include "rubiks.h"
#include<vector>
#include<iostream>

/// Function to implement Depth first search
bool DFS(const int depth, std::vector<Move>& moveList, const std::array<Move, 6>& availableMoves, const FaceArray& faces, const Color centres[6], bool (*isStageGoal)(const FaceArray& faces, const Color centres[6]), const Move& lastMove) {
	
	if (depth == 0) {
		return false;
	}

	//Recursive loop for going back to the base state
	for (auto& m : availableMoves) {
		//if the move is a double move and is the current move
		if (lastMove % 2 && m == lastMove) {
			continue;
		}
		//if the move is a non-affecting move
		if (m - lastMove == 2{
			continue;
		}

		auto facesCopy = faces;

		doMove(m, facesCopy); //doMove takes move (U,U2,D,D2---) and the face as its parameters
		//if goal stage reached, adding the move to the moveList
		if (isStageGoal(facesCopy, centres)) {
			moveList.insert(moveList.begin(), m);   //begin() returns iterator to the first element in the list of moves
		    return true;
		}

		//Checking for the previous depth
		if (DFS(depth - 1, moveList, availableMoves, facesCopy, centres, isStageGoal, m)) {
			moveList.insert(moveList.begin(), m); //inserting the last move to the list
			return true;
		}

	}
	return false;
}










/// <summary>
/// Stores solved state of cube and calls function responsible for applying IDDFS algorithm
/// </summary>
/// <param name="centers">: Contains color of center face of cube</param>
void initialiseSolver(const eColor centers[6])
{
	FaceArray solvedState;
	for (int i = 0;i < 6;i++)				//Loop for traversing all the 6 faces of cube
	{
		uint_fast32_t face = 0;
		for (int j = 0;j < 8;j++)			//Nested loop for traversing 8 colors of face of cube
		{
			face = (face << 4) | centers[i];  //Storing color of center face in the 8 faces 
		}
		solvedState[i] = face;
	}
	eMove availableMoves[6] = { L2, R2, F2, B2, U2, D2 };
	doIDDFS(availableMoves, solvedState, centers, isInitialiseStageGoal);
	//Make doIDDFS function and isInitialiseStageGoal to continue the code
}