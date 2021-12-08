#include "rubiks.h"
#include<vector>
#include<iostream>
#include<set>
#include<array>
using namespace std;

#define F_UP 0
#define F_DOWN 1
#define F_FRONT 2
#define F_BACK 3
#define F_LEFT 4
#define F_RIGHT 5

set<uint_fast64_t> permutations;

/// <summary>
/// Function to implement Depth first search
/// </summary>
/// <param name="depth"> Specifies the search depth </param>
/// <param name="moveList"> Specifies all the moves that can be made </param>
/// <param name="availableMoves"> Specifies the available moves that can be made</param>
/// <param name="faces"> Array of type FaceArray for storing scrambled faces</param>
/// <param name="centres"> Array for storing centre colours of a face </param>
/// <param name="isStageGoal"> Returns boolean value if the stage is goal stage </param>
/// <param name="lastMove"> Specifies the last move made </param>
/// <returns>Bollean value True if goal state is found else False</returns>
bool DFS(const int depth, std::vector<eMove>& moveList, const array<eMove, 6>& availableMoves, const FaceArray& faces, const eColor centres[6],
    bool (*isStageGoal)(const FaceArray& faces, const eColor centres[6]), const eMove& lastMove)
{

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
        if (m - lastMove == 2) {
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
/// Function to implement Iterative Deepening Depth First Search (IDDFS)
/// </summary>
/// <param name="availableMoves"> Specifies the available moves that can be made </param>
/// <param name="faces"> Array of type FaceArray for storing scrambled faces </param>
/// <param name="centres"> Array for storing centre colours of a face </param>
/// <param name="isStageGoal"> Returns boolean value if the stage is goal stage </param>
/// <returns>Vector of moves found by algorithm to solve the cube</returns>
vector<eMove> IDDFS(const array<eMove, 6>& availableMoves, const FaceArray& faces, const eColor centres[6], bool(*isStageGoal)(const FaceArray& faces, const eColor centres[6])) {

    vector<eMove> moveList;
    cout << endl << "IDDFS Depth: 1";
    int depth = 1;
    while (!DFS(depth, moveList, availableMoves, faces, centres, isStageGoal, NONE)) { //If DFS function returns false, then IDDFS is used
        depth++;
        cout << ". " << depth;
    }
    cout << ". Complete" << std::endl;

    return moveList;
}

/// <summary>
/// Finds the cubie color of the cubir passed
/// </summary>
/// <param name="faces"></param>
/// <param name="faceIndex"></param>
/// <param name="cubieIndex"></param>
/// <returns>Returns enum of type eColor</returns>
eColor getSquareColor(const FaceArray& faces, int faceIndex, int cubieIndex)
{
    int shiftBits = 4 * (7 - cubieIndex);
    int cubieColor = ((faces[faceIndex] >> shiftBits) & 0xF);
    return static_cast<eColor>(cubieColor);
}

/// <summary>
/// returns the face index for a particular color
/// </summary>
/// <param name="centres"></param>
/// <param name="faceColor"></param>
int getFace(const eColor centres[6], eColor faceColor) {
    for (int i = 0; i < 6; ++i) {
        if (faceColor == centres[i])
            return i;
    }
    return -1;
}

/// <summary>
/// returns the index of an edge cubie of given face and color
/// </summary>
/// <param name="centres"></param>
/// <param name="cubieFaceIndex"></param>
/// <param name="edgeColor"></param>
int getEdgeCubieIndex(const eColor centres[6], int cubieFaceIndex, const eColor& edgeColor) {
    switch (cubieFaceIndex) {
    case F_FRONT: {
        if (edgeColor == centres[F_UP])
            return 1;
        if (edgeColor == centres[F_RIGHT])
            return 3;
        if (edgeColor == centres[F_DOWN])
            return 5;
        if (edgeColor == centres[F_LEFT])
            return 7;
        break;
    }
    case F_BACK: {
        if (edgeColor == centres[F_UP])
            return 1;
        if (edgeColor == centres[F_RIGHT])
            return 7;
        if (edgeColor == centres[F_DOWN])
            return 5;
        if (edgeColor == centres[F_LEFT])
            return 3;
        break;
    }
    case F_UP: {
        if (edgeColor == centres[F_FRONT])
            return 5;
        if (edgeColor == centres[F_RIGHT])
            return 3;
        if (edgeColor == centres[F_BACK])
            return 1;
        if (edgeColor == centres[F_LEFT])
            return 7;
        break;
    }
    case F_DOWN: {
        if (edgeColor == centres[F_FRONT])
            return 1;
        if (edgeColor == centres[F_RIGHT])
            return 3;
        if (edgeColor == centres[F_BACK])
            return 5;
        if (edgeColor == centres[F_LEFT])
            return 7;
        break;
    }
    case F_LEFT: {
        if (edgeColor == centres[F_UP])
            return 1;
        if (edgeColor == centres[F_BACK])
            return 7;
        if (edgeColor == centres[F_DOWN])
            return 5;
        if (edgeColor == centres[F_FRONT])
            return 3;
        break;
    }
    case F_RIGHT: {
        if (edgeColor == centres[F_UP])
            return 1;
        if (edgeColor == centres[F_BACK])
            return 3;
        if (edgeColor == centres[F_DOWN])
            return 5;
        if (edgeColor == centres[F_FRONT])
            return 7;
        break;
    }
    }
    return -1;
}

/// <summary>
/// 
/// </summary>
/// <param name="faces"></param>
/// <returns></returns>
uint_fast64_t makePermutation(const FaceArray& faces)
{
    uint_fast64_t perm = 0;
    for (auto& f : { F_LEFT, F_FRONT, F_RIGHT, F_BACK })
    {
        for (int i = 0;i <= 6;i += 2)
        {
            perm = (perm << 4) | getSquareColor(faces, f, i);
        }
    }
    return perm;
}

/// <summary>
/// Checks if input cube given by user is solved or scrambled
/// </summary>
/// <param name="faces"></param>
/// <returns>Returns bollean value True or False</returns>
bool isInitialiseStageGoal(const FaceArray& faces, const eColor centres[6])
{
    auto perm = makePermutation(faces);
    if (permutations.count(perm) == 0)
    {
        permutations.insert(perm);
        if (permutations.size() == 96)
            return true;
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
        for (int j = 0;j < 8;++j)			//Nested loop for traversing 8 colors of face of cube
        {
            face = (face << 4) | centers[i];  //Storing color of center face in the 8 faces 
        }
        solvedState[i] = face;
    }
    array<eMove, 6> availableMoves = { L2, R2, F2, B2, U2, D2 };
    IDDFS(availableMoves, solvedState, centers, isInitialiseStageGoal);
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
void doMoveList(FaceArray& faces, const std::vector<eMove>& moveList) {
    for (auto& m : moveList) { //The auto keyword specifies that the type of the variable that is being declared will be automatically deducted from its initializer
        doMove(m, faces);
    }
}

/// <summary>
/// This function checks whether an edge pice is good or not.
/// An edge piece is "GOOD if it can be moved to its solved position without using quarter turns of the up or down faces.
/// if an 'A' edge actually belongs in a 'B' position, then a quarter up/down turn is needed and hence the edge is bad and vice versa
/// if 'A' edge belongs to 'A' position then edge is good
/// </summary>
/// <param name="fromFace"></param>
/// <param name="fromCubieIndex"></param>
/// <param name="toFace"></param>
/// <param name="toCubieInd"></param>
bool isGoodEdge(int fromFace, int fromCubieInd, int toFace, int toCubieInd) {
    static bool A_edges[6][8] = {
        {0, 1, 0, 0, 0, 1, 0, 0}, {0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1}, {0, 1, 0, 1, 0, 1, 0, 1}
    };
    return A_edges[fromFace][fromCubieInd] == A_edges[toFace][toCubieInd];
}

/// <summary>
/// This function checks whether all edges are good or not.
/// There are 12 edges in the cube
/// F edges -> 4      [(1, 5), (3, 7), (5, 1), (7, 3)]
/// B edges -> 4      [(1, 1), (3, 7), (5, 5), (7, 3)]
/// edges in between -> 4     [(1, 7), (3, 1), (5, 3), (7, 5)]
/// </summary>
/// <param name="faces"></param>
/// <param name="centres"></param>
bool isAllEdgesGood(const FaceArray& faces, const eColor centres[6]) {

    int i = 1, j = i, f = F_LEFT;
    int toFace, toCubieInd;

    for (auto face : { F_UP, F_RIGHT, F_DOWN, F_LEFT }) {

        //F edges
        toFace = getFace(centres, getSquareColor(faces, F_FRONT, i));
        toCubieInd = getEdgeCubieIndex(centres, toFace, getSquareColor(faces, face, (i + 4) % 8));
        if (!isGoodEdge(F_FRONT, i, toFace, toCubieInd))
            return false;

        //B edges
        toFace = getFace(centres, getSquareColor(faces, F_BACK, i));
        toCubieInd = getEdgeCubieIndex(centres, toFace, getSquareColor(faces, face, j));
        if (!isGoodEdge(F_BACK, i, toFace, toCubieInd))
            return false;
        j = (j == i) ? (i + 6) % 8 : i + 2;

        //between edges
        toFace = getFace(centres, getSquareColor(faces, f, i));
        toCubieInd = getEdgeCubieIndex(centres, toFace, getSquareColor(faces, face, (i + 6) % 8));
        if (!isGoodEdge(f, i, toFace, toCubieInd))
            return false;
        f = face;

        i += 2;
    }

    return true;
}

/// <summary>
/// Function to get moves of Stage 1
/// </summary>
/// <param name="faces">: Array of type FaceArray for storing scrambled faces</param>
/// <param name="centres">: Array for storing centre colours of a face </param>
/// <returns>Moves found by the algorithm to solve the cube</returns>
std::vector<eMove> getStage1Moves(const FaceArray& faces, const eColor centres[6]) {

    if (isAllEdgesGood(faces, centres)) {
        return std::vector<eMove>();
    }


    array<eMove, 6> availableMoves{ L, R, F, B, U, D };             //Available moves in Stage 1
    return IDDFS(availableMoves, faces, centres, isAllEdgesGood);   //Applying IDDFS on this stage

}

/// <summary>
/// Function to check for Stage 2
/// </summary>
/// <param name="faces">: Array of type FaceArray for storing scrambled faces</param>
/// <param name="centres">: Array for storing centre colours of a face </param>
/// <returns>True if cube satisfies the conditions of stage 2 else false</returns>
bool isStage2Goal(const FaceArray& faces, const eColor centres[6]) {
    //Accomplishing the correct corner orientation in this stage
    const eColor& color_left = centres[F_LEFT], & color_right = centres[F_RIGHT];

    //Comparing centres of the left and right faces with the corners
    for (int i = 0; i <= 6; i += 2) {
        eColor c1 = getSquareColor(faces, F_LEFT, i), c2 = getSquareColor(faces, F_RIGHT, i);
        if (!((c1 == color_left || c1 == color_right) && (c2 == color_left || c2 == color_right))) {
            return false;
        }
    }

    //Checking the edges - FU, FD, BU, BD
    const eColor& color_front = centres[F_FRONT], & color_back = centres[F_BACK], & color_up = centres[F_UP], & color_down = centres[F_DOWN];
    for (auto& i : { 1, 5 }) {

        eColor c1 = getSquareColor(faces, F_FRONT, i), c2 = getSquareColor(faces, F_BACK, i);
        if (!((c1 == color_front || c1 == color_back) && (c2 == color_front || c2 == color_back))) {
            return false;
        }

        c1 = getSquareColor(faces, F_UP, i), c2 = getSquareColor(faces, F_DOWN, i);
        if (!((c1 == color_up || c1 == color_down) && (c2 == color_up || c2 == color_down))) {
            return false;
        }
    }

    return true;
}


/// <summary>
/// Function to get moves of Stage 2
/// </summary>
/// <param name="faces">: Array of type FaceArray for storing scrambled faces</param>
/// <param name="centres">: Array for storing centre colours of a face </param>
/// <returns>Moves found by the algorithm to solve the cube in stage 2</returns>
std::vector<eMove> getStage2Moves(const FaceArray& faces, const eColor centres[6]) {

    if (isStage2Goal(faces, centres)) {
        return std::vector<eMove>();
    }


    array<eMove, 6> availableMoves{ L, R, F, B, U2, D2 };           //Available moves in Stage 2
    return IDDFS(availableMoves, faces, centres, isStage2Goal);     //Applying IDDFS on this stage
}


/// <summary>
/// Checks if cube has reached goal state or not
/// </summary>
/// <param name="faces"></param>
/// <param name="centres"></param>
/// <returns>True if cube is in solved state else false</returns>
bool isSolved(const FaceArray& faces, const eColor centres[6])
{
    for (int f = 0;f < 6;++f)
    {
        for (int i = 0;i < 8;++i)
        {
            if (getSquareColor(faces, f, i) != centres[f])
                return false;
        }
    }
    return true;
}

/// <summary>
/// Function to get moves of Stage 4
/// </summary>
/// <param name="faces"></param>
/// <param name="centres"></param>
/// <returns>Moves found by the algorithm to solve the cube in stage 4</returns>
vector<eMove> getStage3Moves(const FaceArray& faces, const eColor centres[6])
{
    if (isSolved(faces, centres))
        return vector<eMove>();
    array<eMove, 6> availableMoves{ U, D, R2, L2, F2, B2};           //Available moves in Stage 4
    return IDDFS(availableMoves, faces, centres, isSolved);             //Applying IDDFS on this stage
}