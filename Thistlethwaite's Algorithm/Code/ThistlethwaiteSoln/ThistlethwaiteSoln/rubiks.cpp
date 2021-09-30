#include "rubiks.h"
#include<vector>
#include<iostream>


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