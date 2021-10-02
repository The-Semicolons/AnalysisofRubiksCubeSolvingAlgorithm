/// ThistlethwaiteSoln.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "rubiks.h"
#include <iostream>
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
        faces[i] << 4;                      //Left shifting by 4 bytes to accomodate all faces in 32 bytes.
        faces[i] |= getColor(c[0]);         //Applying Bitwise OR Operation to store color enum value in faces
        faces[i] << 4;
        faces[i] |= getColor(c[1]);
        faces[i] << 4;
        faces[i] |= getColor(c[2]);
        faces[i] << 4;
        faces[i] |= getColor(c[5]);
        faces[i] << 4;
        faces[i] |= getColor(c[8]);
        faces[i] << 4;
        faces[i] |= getColor(c[7]);
        faces[i] << 4;
        faces[i] |= getColor(c[6]);
        faces[i] << 4;
        faces[i] |= getColor(c[3]);
        faces[i] << 4;

        centers[i] = getColor(c[4]);        //Storing enum value of center color in centers array
    }
}

int main()
{
    FaceArray faces = { 0,0,0,0,0,0 };          //Initializing array for storing scrambled faces
    eColor centers[6];                          //Initializing array foe storing Colours at middle cubie of the face

    readData(faces, centers);                   //Function that will take input of faces from the user

    std::cout << "Initialising..";
    initialiseSolver(centers);
}
