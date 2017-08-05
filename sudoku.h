//
//  board.h
//  Sudoku
//
//  Created by Bao Phung on 8/2/17.
//  Copyright © 2017 Bao Phung. All rights reserved.
//

#ifndef board_h
#define board_h

#include "./number.h"

class Sudoku
{
    private:
        Number **board;
    public:
        Sudoku();
        ~Sudoku();
    
        /*Functions to help initialize the entire board*/
        void initializeSquareLocation(int, int, int, int, int, int);
        void initializeSquareOne();
        void initializeSquareTwo();
        void initializeSquareThree();
        void initializeSquareFour();
        void initializeSquareFive();
        void initializeSquareSix();
        void initializeSquareSeven();
        void initializeSquareEight();
        void initializeSquareNine();
        void initializeBoard();
        int notEmptySquare();
        int notDuplicates();
    
        /*Functions to play the actual game*/
        void hideInitializedBoard();
        int checkVictory();
        int checkValidSpot(int, int);
        void uncoverSpot(int, int, int);
        int getStatus(int, int);
    
        void displayBoard();
};


#endif /* board_h */
