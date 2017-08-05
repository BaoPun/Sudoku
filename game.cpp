//
//  game.cpp
//  Sudoku
//
//  Created by Bao Phung on 8/2/17.
//  Copyright © 2017 Bao Phung. All rights reserved.
//

#include "./sudoku.h"

int main()
{
    srand((unsigned int)(time(NULL)));
    cout << "Welcome to Sudoku" << endl << endl;
    int con, x, y, guess, wrong = 0;
    Sudoku sudoku;
 
    sudoku.initializeBoard();
    sudoku.hideInitializedBoard();
    
    while(sudoku.checkVictory() == 0){
        
        sudoku.displayBoard();
        cout << "Choose a block (boundaries 0-8) to uncover in (x, y): ";
        cin >> x >> y;
        
        while(x < 0 || x > 8 || y < 0 || y > 8){
            cout << "Choose valid coordinates: ";
            cin >> x >> y;
        }
        
        while(sudoku.checkValidSpot(x, y)){
            cout << "Choose an uncovered block in (x, y): ";
            cin >> x >> y;
            while(x < 0 || x > 8 || y < 0 || y > 8){
                cout << "Choose valid coordinates: ";
                cin >> x >> y;
            }
        }
        
        cout << "Which number do you think this is? ";
        cin >> guess;
        while(guess < 0 || guess > 9){
            cout << "Please guess between 1-9: ";
            cin >> guess;
        }
        
        sudoku.uncoverSpot(x, y, guess);
        if(!sudoku.checkValidSpot(x, y))
            wrong++;
        
        if(sudoku.checkVictory() == 0){
            cout << "Do you want to keep playing? (1 yes): ";
            cin >> con;
            if(con != 1)
                break;
        }
        else
            cout << "Congratulations, you have won the game with this many wrong tries: " << wrong << "!" << endl;
    }
    
    sudoku.displayBoard();
    return 0;
}
