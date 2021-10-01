#include "rubiks.h"
#include<vector>
#include<iostream>
using namespace std; 

#define F_UP 0
#define F_DOWN 1
#define F_FRONT 2
#define F_BACK 3
#define F_LEFT 4
#define F_RIGHT 5

/// Function to implement Depth first search
bool DFS(const int depth, std::vector<eMove>& moveList, const std::array<eMove, 6>& availableMoves, const FaceArray& faces, const eColor centres[6], bool (*isStageGoal)(const FaceArray& faces, const eColor centres[6]), const eMove& lastMove) {
	
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




/// <summary>
/// This function defines how each move is taking place
/// </summary>
/// <param name="move">: Specifies the move name</param>
/// <param name="faces">: An array of size 6 which stores the face names</param>
void doMove(const eMove& move, FaceArray& faces) {
    switch (move) {
    case U2: doMove(U, faces);
    case U: {
        //90 degree clockwise twist. roll the last 8 bits to front
        //0xff is the hexadecimal number FF which has a integer value of 255
        //"& 0xff" effectively masks the variable so it leaves only the value in the last 8 bits, and ignores all the rest of the bits.
        faces[F_UP] = (faces[F_UP] >> 8) | ((faces[F_UP] & 0xFF) << 24);

        uint_fast32_t F_value = faces[F_FRONT] & 0xFFF00000;
        faces[F_FRONT] = (faces[F_FRONT] & 0x000FFFFF) | (faces[F_RIGHT] & 0xFFF00000);
        faces[F_RIGHT] = (faces[F_RIGHT] & 0x000FFFFF) | (faces[F_BACK] & 0xFFF00000);
        faces[F_BACK] = (faces[F_BACK] & 0x000FFFFF) | (faces[F_LEFT] & 0xFFF00000);
        faces[F_LEFT] = (faces[F_LEFT] & 0x000FFFFF) | F_value;
        break;
    }

    case D2: doMove(D, faces);
    case D: {
        faces[F_DOWN] = (faces[F_DOWN] >> 8) | ((faces[F_DOWN] & 0xFF) << 24);

        uint_fast32_t F_value = faces[F_FRONT] & 0x0000FFF0;
        faces[F_FRONT] = (faces[F_FRONT] & 0xFFFF000F) | (faces[F_LEFT] & 0x0000FFF0);
        faces[F_LEFT] = (faces[F_LEFT] & 0xFFFF000F) | (faces[F_BACK] & 0x0000FFF0);
        faces[F_BACK] = (faces[F_BACK] & 0xFFFF000F) | (faces[F_RIGHT] & 0x0000FFF0);
        faces[F_RIGHT] = (faces[F_RIGHT] & 0xFFFF000F) | F_value;
        break;
    }

    case F2: doMove(F, faces);
    case F: {
        faces[F_FRONT] = (faces[F_FRONT] >> 8) | ((faces[F_FRONT] & 0xFF) << 24);

        uint_fast32_t F_value = faces[F_UP] & 0x0000FFF0, val;

        faces[F_UP] = (faces[F_UP] & 0xFFFF000F) | ((faces[F_LEFT] & 0x00FFF000) >> 8);
        faces[F_LEFT] = (faces[F_LEFT] & 0xFF000FFF) | ((faces[F_DOWN] & 0xFFF00000) >> 8);
        val = ((faces[F_RIGHT] & 0x000000FF) << 24) | ((faces[F_RIGHT] & 0xF0000000) >> 8);     //roll bits [6-7-0 to 0-1-2]
        faces[F_DOWN] = (faces[F_DOWN] & 0x000FFFFF) | val;
        val = (F_value >> 8) | (F_value << 24);
        faces[F_RIGHT] = (faces[F_RIGHT] & 0x0FFFFF00) | val;
        break;
    }

    case B2: doMove(B, faces);
    case B: {
        faces[F_BACK] = (faces[F_BACK] >> 8) | ((faces[F_BACK] & 0xFF) << 24);

        uint_fast32_t F_value = (faces[F_UP] & 0xFFF00000), val;

        faces[F_UP] = (faces[F_UP] & 0x000FFFFF) | ((faces[F_RIGHT] & 0x00FFF000) << 8);
        faces[F_RIGHT] = (faces[F_RIGHT] & 0xFF000FFF) | ((faces[F_DOWN] & 0x0000FFF0) << 8);
        val = ((faces[F_LEFT] & 0x000000FF) << 8) | ((faces[F_LEFT] & 0xF0000000) >> 24);
        faces[F_DOWN] = (faces[F_DOWN] & 0xFFFF000F) | val;
        val = (F_value >> 24) | (F_value << 8);
        faces[F_LEFT] = (faces[F_LEFT] & 0x0FFFFF00) | val;
        break;
    }

    case L2: doMove(L, faces);
    case L: {
        faces[F_LEFT] = (faces[F_LEFT] >> 8) | ((faces[F_LEFT] & 0xFF) << 24);

        uint_fast32_t F_value = (faces[F_UP] & 0xF00000FF), val;

        val = ((faces[F_BACK] & 0x00FF0000) >> 16) | ((faces[F_BACK] & 0x0000F000) << 16);
        faces[F_UP] = (faces[F_UP] & 0x0FFFFF00) | val;
        val = ((faces[F_DOWN] & 0x000000FF) << 16) | ((faces[F_DOWN] & 0xF0000000) >> 16);
        faces[F_BACK] = (faces[F_BACK] & 0xFF000FFF) | val;
        faces[F_DOWN] = (faces[F_DOWN] & 0x0FFFFF00) | (faces[F_FRONT] & 0xF00000FF);
        faces[F_FRONT] = (faces[F_FRONT] & 0x0FFFFF00) | F_value;
        break;
    }

    case R2: doMove(R, faces);
    case R: {
        faces[F_RIGHT] = (faces[F_RIGHT] >> 8) | ((faces[F_RIGHT] & 0xFF) << 24);

        uint_fast32_t F_value = (faces[F_UP] & 0x00FFF000), val;

        faces[F_UP] = (faces[F_UP] & 0xFF000FFF) | (faces[F_FRONT] & 0x00FFF000);
        faces[F_FRONT] = (faces[F_FRONT] & 0xFF000FFF) | (faces[F_DOWN] & 0x00FFF000);
        val = ((faces[F_BACK] & 0x000000FF) << 16) | ((faces[F_BACK] & 0xF0000000) >> 16);
        faces[F_DOWN] = (faces[F_DOWN] & 0xFF000FFF) | val;
        val = (F_value >> 16) | (F_value << 16);
        faces[F_BACK] = (faces[F_BACK] & 0x0FFFFF00) | val;
        break;
    }
    }
}

/// <summary>
/// This function passes a set of moves(as calculated by the solver after each stage) which needs to be executed 
/// by the doMove function
/// </summary>
/// <param name="faces">: An array of size 6 which stores the face names</param>
/// <param name="moveList">: The list of moves</param>
/// 
void doMoveList(FaceArray& faces, const std::vector<eMove>& moveList) {
    for (auto& m : moveList) { //The auto keyword specifies that the type of the variable that is being declared will be automatically deducted from its initializer
        doMove(m, faces);
    }
}





