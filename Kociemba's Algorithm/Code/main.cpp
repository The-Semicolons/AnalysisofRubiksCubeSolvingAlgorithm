/// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "rubiks.h"
#include <iostream>
#include<string>
#include<vector>
#include<array>
using namespace std;
/// <summary>
/// Takes input of face color and returns enum value of that face
/// </summary >
/// <param name="c">Input character of face color</param>
/// <returns>enum eColor value of that face</returns>
eColor getColor(char c)
{
    switch (c)
    {
    case 'W': return WHITE;
    case 'Y': return YELLOW;
    case 'B': return BLUE;
    case 'G': return GREEN;
    case 'R': return RED;
    case 'O': return ORANGE;
    }
}

/// <summary>
/// This function converts enum eColor to string and returns to printCube function
/// </summary>
/// <param name="c">: enum eColor type input of face colors</param>
/// <returns>Character of color</returns>
char getColorCharacter(int c)
{
    switch (c)
    {
    case WHITE: return 'W';
    case YELLOW: return 'Y';
    case BLUE: return 'B';
    case GREEN: return 'G';
    case RED: return 'R';
    case ORANGE: return 'O';
    }
    exit(0);
}

/// <summary>
/// Inputs a vector element of moveList given by getMoveListString function and converts it to string
/// </summary>
/// <param name="m">: An element of vector moveList</param>
/// <returns>String of face moves</returns>
string getMoveString(const eMove& m)
{
    switch (m)
    {
    case U: return "U";
    case D: return "D";
    case F: return "F";
    case B: return "B";
    case L: return "L";
    case R: return "R";
    case U2: return "U2";
    case D2: return "D2";
    case F2: return "F2";
    case B2: return "B2";
    case L2: return "L2";
    case R2: return "R2";
    }
    return "";
}



/// <summary>
/// To optimise the solution of solving a Rubik's cube by removing the unnecessary/extra moves
/// </summary>
/// <param moveString">: A string consisting of all the stages to solve a cube</param>
/// <returns>String of optimised moves</returns>

std::string optimiseMoves(std::string& moveString) {
    int start = 0;
    std::string prevMove, optimizedString;

    for (int i = 0; i < moveString.size(); i++) {
        if (moveString[i] == ' ') {
            auto Currentmove = moveString.substr(start, i - start); //creating substrings of all the moves

            if (prevMove[0] == Currentmove[0]) { //Checking for the 0th index of the 2 moves for the face (L, R, F, B, U or D)
                prevMove.clear();

                if (Currentmove[1] == '2' || prevMove[1] == '2') { //For cases like L L2 (L L2 = L')
                    optimizedString.push_back(Currentmove[0]);
                    optimizedString = optimizedString + "\' ";
                }
                else {
                    prevMove.push_back(Currentmove[0]); //For cases like L L (L L = L2)
                    prevMove = prevMove + "2 ";
                }
            }
            else {
                optimizedString = optimizedString + prevMove;
                prevMove = Currentmove + ' ';
            }
            start = i + 1;
        }
    }
    return optimizedString + prevMove;
}


/// <summary>
/// Converts vector list of moves into string
/// </summary>
/// <param name="moveList">: List of moves generated by different stages</param>
/// <returns>String sequence of moves</returns>
string getMoveListString(const vector<eMove>& moveList)
{
    string moveSequenceString;
    for (auto& m : moveList)                               //Traversing all the elements of vector moveList
    {
        moveSequenceString += getMoveString(m) + ' ';
    }
    return moveSequenceString;
}

/// <summary>
/// This function prints the cube
/// </summary>
/// <param name="faces">: FaceArray type input of faces</param>
/// <param name="centers">: Array input of centers</param>
void printCube(const FaceArray& faces, eColor centres[]) {
    std::cout << std::endl;
    std::cout << "-----Printing Cube-----" << std::endl;
    for (int i = 0; i < 6; ++i) {                          //Iterating loop for 6 faces
        char c[9];
        uint_fast32_t face = faces[i];                     //Storing a face of cube in variable face

        c[3] = getColorCharacter(face & 0xF);              //Extracting colors from face variable       
        face = face >> 4;
        c[6] = getColorCharacter(face & 0xF);
        face = face >> 4;
        c[7] = getColorCharacter(face & 0xF);
        face = face >> 4;
        c[8] = getColorCharacter(face & 0xF);
        face = face >> 4;
        c[5] = getColorCharacter(face & 0xF);
        face = face >> 4;
        c[2] = getColorCharacter(face & 0xF);
        face = face >> 4;
        c[1] = getColorCharacter(face & 0xF);
        face = face >> 4;
        c[0] = getColorCharacter(face & 0xF);
        c[4] = getColorCharacter(centres[i]);

        for (int j = 0; j < 9; ++j)                        //Printing the Extracted colors
            std::cout << c[j];

        std::cout << std::endl;
    }
    std::cout << "-----------------------" << std::endl;
}

/// <summary>
/// This Function will take input of faces from the user
/// </summary>
/// <param name="faces">Array of type FaceArray</param>
/// <param name="centers">enum eColor for storing center faces</param>
void readData(FaceArray& faces, eColor centers[])
{
    int i, j;
    cout << "Type Faces in the order UDFBLR:" << endl;
    for (int i = 0;i < 6;i++)                   //loop for all 6 faces of cube
    {
        char c[9];
        //Taking input of 9 face colors in the form W,Y,G,R,O,B where each represents White, Yellow, Green, Red, Orange, Blue color
        cin >> c[0] >> c[1] >> c[2] >> c[3] >> c[4] >> c[5] >> c[6] >> c[7] >> c[8];
        faces[i] <<= 4;                      //Left shifting by 4 bytes to accomodate all faces in 32 bytes.
        faces[i] |= getColor(c[0]);         //Applying Bitwise OR Operation to store color enum value in faces
        faces[i] <<= 4;
        faces[i] |= getColor(c[1]);
        faces[i] <<= 4;
        faces[i] |= getColor(c[2]);
        faces[i] <<= 4;
        faces[i] |= getColor(c[5]);
        faces[i] <<= 4;
        faces[i] |= getColor(c[8]);
        faces[i] <<= 4;
        faces[i] |= getColor(c[7]);
        faces[i] <<= 4;
        faces[i] |= getColor(c[6]);
        faces[i] <<= 4;
        faces[i] |= getColor(c[3]);

        centers[i] = getColor(c[4]);        //Storing enum value of center color in centers array
    }
}

int main()
{
    FaceArray faces = { 0,0,0,0,0,0 };          //Initializing array for storing scrambled faces
    eColor centers[6];                          //Initializing array for storing Colours at middle cubie of the face

    readData(faces, centers);                   //Function that will take input of faces from the user

    std::cout << "Initialising..";
    initialiseSolver(centers);

    printCube(faces, centers);

    string moveString;

    auto moves = getStage1Moves(faces, centers);   //Applying IDDFS Algorithm on stage 1 moves
    auto stageString = getMoveListString(moves);   //Converting the moves returned by IDDFS to string 
    cout << "Stage 1 Moves: " << stageString;      //Printing the moves
    doMoveList(faces, moves);                      //Applying the moves on rubik's cube
    moveString += stageString;

    printCube(faces, centers);                      //Printing the cube

    moves = getStage2Moves(faces, centers);         //Applying IDDFS Algorithm on stage 2 moves
    stageString = getMoveListString(moves);         //Converting the moves returned by IDDFS to string 
    cout << "Stage 2 Moves: " << stageString;       //Printing the moves
    doMoveList(faces, moves);                       //Applying the moves on rubik's cube
    moveString += stageString;

    printCube(faces, centers);                       //Printing the cube


    moves = getStage3Moves(faces, centers);         //Applying IDDFS Algorithm on stage 3 moves
    stageString = getMoveListString(moves);         //Converting the moves returned by IDDFS to string 
    cout << "Stage 3 Moves: " << stageString;       //Printing the moves
    doMoveList(faces, moves);                       //Applying the moves on rubik's cube
    moveString += stageString;

    std::cout << "\n\nSolution: " << moveString << std::endl;
    moveString = optimiseMoves(moveString);
    std::cout << "Optimised: " << moveString << std::endl;

    int moveCount = 0;
    for (auto& c : moveString) {
        if (c == ' ')
            ++moveCount;
    }

    std::cout << "Moves Needed: " << moveCount << std::endl << std::endl;

    return 0;

}