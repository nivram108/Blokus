#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <string>
#include <cstring>
#include "shapes.h"
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define YELLOW  "\033[33m"      /* Yellow */
#define MAGENTA "\033[45m"      /* Magenta */

class Game
{
private:
    int biggestRange, bestA, bestB;
    vector<Shape> shapes, shapesA, shapesB;
    char board[14][14];

    int firstStepFlagA, firstStepFlagB;

    //list of whether the piece is used(true) or not(false)
    bool piecesUseA[21], piecesB[21];
    bool* piecesUsePointer;

    static const int shoulders[][2];
    static const int sides[][2];
    
    //Check if it's first step and if it's a legal first step.
    bool isLegalFirst(Shape shp, int x, int y, char player);
    //To check if the block is connected so it's LEGAL
    bool isConnectedToShoulder(Shape shp, int x, int y, char player);
    //To check if the block is touched so it's ILLEGAL.
    bool isTouchedBySelf(Shape shp, int x, int y, char player);
    //To check if the board is spare to place the block so it's LEGAL
    bool isSpare(Shape shp, int x, int y);

public:
    Game();
    
    //Create shapes and initial board and identifiers for placed shapes.
    void init();
    //Set all the pointers to the assigned player's
    void setPlayer(const char& player);
    //Check if the selected piece used(true) or not(false)
    bool isPieceUse(const int& k);
    //Set the selected piece used
    void setPieceUse(const int& k);
    //List the shapes of the player that have not been placed yet.
    void listShapes(const char& player);
    //Print out the current board status.
    void printBoard();
    //check if the selected shape index is between 0 and 20.
    bool checkShapeID(const int& i);
    //Make a single move. Return true if the move is success.
    bool playerMove(const Shape& shp, const int& shapeID, const char& player, const int& x, const int& y);
    //To check if the game is ended.
    bool isGameEnd(const char& player);
    //To return the winner of the game.
    string winner();

    //----------------------------AI's NEED--------------------------------//
    //To check the move is legal or not, that is, Connected, not Touched and Spare to place.
    bool isLegalMove(const Shape& shp, const int& x, const int& y, const char& player);
    //To check if the shape can be place anywhere or not.
    bool hasPlaceToPut(const int& id, const char& player);
    //Checking game is ended or not, but without print anything. ( for AI )
    bool checkGameEndAI(const char& player);
};

#endif
