#pragma once
#include <vector>

//Defining an array of block size 32 bits for storing colors of a face of cube
typedef uint_fast32_t FaceArray[6];

//Making a enum named eColor for all the colors of cube
enum eColor { WHITE, YELLOW, BLUE, GREEN, RED, ORANGE };

//Making a enum named eMove for possible moves in the cube
//two non affecting moves are separated by 2 ie U + 2 -> D
//all '2' moves are odd. ie U2 is 1, D2 is 3
//all single moves are even
//NONE for passing to DFS start
enum eMove { U = 0, U2 = 1, D = 2, D2 = 3, F = 10, F2 = 11, B = 12, B2 = 13, L = 20, L2 = 21, R = 22, R2 = 23, NONE = 50 };


void doMove(const eMove& move, FaceArray& faces);
void doMoveList(FaceArray& faces, const std::vector<eMove>& moveList);
