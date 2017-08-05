//
//  board.cpp
//  Sudoku
//
//  Created by Bao Phung on 8/2/17.
//  Copyright © 2017 Bao Phung. All rights reserved.
//

#include "./sudoku.h"

Sudoku::Sudoku()
{
    board = new Number *[9];
    for(int i = 0; i < 9; i++)
        board[i] = new Number[9];
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++)
            board[i][j].set_num(0);
    }
}

Sudoku::~Sudoku()
{
    for(int i = 0; i < 9; i++)
        delete [] board[i];
    delete [] board;
}

/*parameters: x and y coordinates lower bounds, w and z coordinates upper bounds
 *This function is a general function applied to all squares but the middle that will 
 * randomly allocate each number 1-9 in each block, and will also check for uniqueness*/
void Sudoku::initializeSquareLocation(int x, int w, int y, int z, int m, int n)
{
    for(int i = x; i < w; i++){
        for(int j = y; j < z; j++){
            board[i][j].set_num(rand()%9 + 1);
            
            /*this loop checks the square if there's any repeat occurrences within it*/
            int a = i, b = j;
            while(a >= m && b >= n){
                if(a == m && b == n)
                    break;
                if(a != m && b == n){
                    b = z - 1;
                    a--;
                }
                else
                    b--;
                if(board[i][j].get_num() == board[a][b].get_num()){
                    a = i;
                    b = j;
                    board[i][j].set_num(rand()%9 + 1);
                }
            }
        }
    }
}

void Sudoku::initializeSquareOne()
{
    initializeSquareLocation(0, 3, 0, 3, 0, 0);
}

void Sudoku::initializeSquareTwo()
{
    int n = 0;
    initializeSquareLocation(0, 3, 3, 6, 0, 3);
    
    /*Iterate through Square 2's boundaries, checking for unique row appearances from Square 1*/
    for(int i = 0; i < 3; i++){
        for(int j = 3; j < 6; j++){
            int l = 0;
            while(l < 3){
                if(board[i][j].get_num() == board[i][l].get_num()){
                    l = 3;
                    if(j == 4 || j == 5)
                        j = 3;
                    initializeSquareLocation(i, 3, j, 6, 0, 3);
                    j--;
                    n++;
                    if(n == 100){
                        
                        l = 3;
                        i = 3;
                        j = 6;
                    }
                }
                else
                    l++;
            }
        }
    }
    /*Limiter count that is set to redo initializations of squares 1 and 2 if called for 100 times*/
    if(n == 100)
        initializeSquareTwo();
}

void Sudoku::initializeSquareThree()
{
    int n = 0;
    initializeSquareLocation(0, 3, 6, 9, 0, 6);
    
    /*Iterate through Square 2's boundaries, checking for unique row appearances from Square 1 and 2*/
    for(int i = 0; i < 3; i++){
        for(int j = 6; j < 9; j++){
            int l = 0;
            while(l < 6){
                if(board[i][j].get_num() == board[i][l].get_num()){
                    l = 6;
                    if(j == 7 || j == 8)
                        j = 6;
                    initializeSquareLocation(i, 3, j, 9, 0, 6);
                    j--;
                    n++;
                    if(n == 100){
                        l = 6;
                        i = 3;
                        j = 9;
                    }
                }
                else
                    l++;
            }
        }
    }
    /*Limiter count that is set to redo initializations of squares 1, 2, 3 if called for 100 times*/
    if(n == 100)
        initializeSquareThree();
}

void Sudoku::initializeSquareFour()
{
    int n = 0;
    initializeSquareLocation(3, 6, 0, 3, 3, 0);
    
    /*Iterate through Square 2's boundaries, checking for unique column appearances from Square 1*/
    for(int i = 3; i < 6; i++){
        for(int j = 0; j < 3; j++){
            int l = 0;
            while(l < 3){
                if(board[i][j].get_num() == board[l][j].get_num()){
                    l = 3;
                    if(j == 1 || j == 2)
                        j = 0;
                    initializeSquareLocation(i, 6, j, 3, 3, 0);
                    j--;
                    n++;
                    if(n == 100){
                        l = 3;
                        i = 6;
                        j = 3;
                    }
                }
                else
                    l++;
            }
        }
    }
    /*Limiter count that is set to redo initialization of square 4 if called for 100 times*/
    if(n == 100)
        initializeSquareFour();
}

/*The last and middle square that will be initialized.  Instead of randomizing like all the others, all that is needed is to fill the necessary holes in each square position within this square*/
void Sudoku::initializeSquareFive()
{
    for(int i = 3; i < 6; i++){
        for(int j = 3; j < 6; j++){
            for(int num = 1; num <= 9; num++){
                int s = 0, a = 0, m = 6, e = 6, cont = 1;
                while(s < 3){
                    if(board[i][s].get_num() == num){
                        s = 3;
                        cont = 0;
                    }
                    else
                        s++;
                }
                while(a < 3 && cont == 1){
                    if(board[a][j].get_num() == num){
                        a = 3;
                        cont = 0;
                    }
                    else
                        a++;
                }
                while(m < 9 && cont == 1){
                    if(board[i][m].get_num() == num){
                        m = 9;
                        cont = 0;
                    }
                    else
                        m++;
                }
                while(e < 9 && cont == 1){
                    if(board[e][j].get_num() == num){
                        e = 9;
                        cont = 0;
                    }
                    else
                        e++;
                }
                /*cont remains 1 if num is able to escape these conditions*/
                if(cont == 1){
                    board[i][j].set_num(num);
                    break; /*found the unique number already, get out of this loop*/
                }
                
            }
        }
    }
    /*Bandaid solution, a more efficient way can definitely be implemented*/
    while(!notEmptySquare() || !notDuplicates())
        initializeBoard();
}

/*Helper function for detecting any empty squares*/
int Sudoku::notEmptySquare()
{
    for(int i = 3; i < 6; i++){
        for(int j = 3; j < 6; j++){
            if(board[i][j].get_num() == 0)
                return 0;
        }
    }
    return 1;
}

/*Helper function for detecting any duplicate numbers in square 5*/
int Sudoku::notDuplicates()
{
    for(int i = 3; i < 6; i++){
        for(int j = 3; j < 6; j++){
            int x = i, y = j;
            while(x >= 3 && y >= 3){
                if(x == 3 && y == 3)
                    break;
                if(y == 3){
                    y = 5;
                    x--;
                }
                else
                    y--;
                if(board[i][j].get_num() == board[x][y].get_num()){
                    return 0;
                }
            }
        }
    }
    return 1;
}

void Sudoku::initializeSquareSix()
{
    int n = 0, p = 0;
    initializeSquareLocation(3, 6, 6, 9, 3, 6);
    
    /*Iterate through Square 6's boundaries, checking for unique column appearances from Squares 4 and 3.  Square 5 will be included last, so no need to check within that square*/
    for(int i = 3; i < 6; i++){
        for(int j = 6; j < 9; j++){
            int l = 0, u = 0, cont = 1;
            /*Checks square 4's rows*/
            while(l < 3){
                if(board[i][j].get_num() == board[i][l].get_num()){
                    l = 3;
                    if(j == 7 || j == 8)
                        j = 6;
                    initializeSquareLocation(i, 6, j, 9, 3, 6);
                    j--;
                    n++;
                    if(n == 500){
                        l = 3;
                        i = 6;
                        j = 9;
                        cont = 0;
                    }
                }
                else
                    l++;
            }
            /*Checks square 3's columns*/
            while(cont == 1 && u < 3){
                if(board[i][j].get_num() == board[u][j].get_num()){
                    u = 3;
                    if(j == 7 || j == 8)
                        j = 6;
                    initializeSquareLocation(i, 6, j, 9, 3, 6);
                    j--;
                    p++;
                    if(p == 500){
                        u = 3;
                        i = 6;
                        j = 9;
                    }
                }
                else
                    u++;
            }
        }
    }
    /*Limiter counts that is set to redo initialization of square 6 if one of the limiter counts is called for 500 times*/
    if(n == 500 || p == 500)
        initializeSquareSix();
}

void Sudoku::initializeSquareSeven()
{
    int n = 0;
    initializeSquareLocation(6, 9, 0, 3, 6, 0);
    for(int i = 6; i < 9; i++){
        for(int j = 0; j < 3; j++){
            int l = 0;
            while(l < 6){
                if(board[i][j].get_num() == board[l][j].get_num()){
                    l = 6;
                    if(j == 1 || j == 2)
                        j = 0;
                    initializeSquareLocation(i, 9, j, 3, 6, 0);
                    j--;
                    n++;
                    if(n == 100){
                        l = 6;
                        i = 9;
                        j = 3;
                    }
                }
                else
                    l++;
            }
        }
    }
    if(n == 100)
        initializeSquareSeven();
}

void Sudoku::initializeSquareEight()
{
    int n = 0, e = 0, t = 0;
    initializeSquareLocation(6, 9, 3, 6, 6, 3);
    for(int i = 6; i < 9; i++){
        for(int j = 3; j < 6; j++){
            int s = 0, u = 0, p = 6, cont = 1;
            while(s < 3){
                if(board[i][j].get_num() == board[i][s].get_num()){
                    s = 3;
                    if(j == 4 || j == 5)
                        j = 3;
                    initializeSquareLocation(i, 9, j, 6, 6, 3);
                    j--;
                    n++;
                    if(n == 1000){
                        i = 9;
                        j = 6;
                        s = 3;
                        cont = 0;
                    }
                }
                else
                    s++;
            }
            while(cont == 1 && u < 3){
                if(board[i][j].get_num() == board[u][j].get_num()){
                    u = 3;
                    if(j == 4 || j == 5)
                        j = 3;
                    initializeSquareLocation(i, 9, j, 6, 6, 3);
                    j--;
                    e++;
                    if(e == 1000){
                        u = 3;
                        i = 9;
                        j = 6;
                        cont = 0;
                    }
                }
                else
                    u++;
            }
            while(cont == 1 && p < 8){
                if(board[i][j].get_num() == board[i][p].get_num()){
                    p = 8;
                    if(j == 4 || j == 5)
                        j = 3;
                    initializeSquareLocation(i, 9, j, 6, 6, 3);
                    j--;
                    t++;
                    if(t == 1000){
                        p = 8;
                        i = 9;
                        j = 6;
                        cont = 0;
                    }
                }
                else
                    p++;
            }
            
        }
    }
    if(n == 1000 || e == 1000 || t == 1000){
        initializeSquareSeven();
        initializeSquareEight();
    }
}

void Sudoku::initializeSquareNine()
{
    int n = 0, p = 0;
    initializeSquareLocation(6, 9, 6, 9, 6, 6);
    for(int i = 6; i < 9; i++){
        for(int j = 6; j < 9; j++){
            int l = 0, e = 0, cont = 1;
            while(l < 6){
                if(board[i][j].get_num() == board[i][l].get_num()){
                    l = 6;
                    if(j == 7 || j == 8)
                        j = 6;
                    initializeSquareLocation(i, 9, j, 9, 6, 6);
                    j--;
                    n++;
                    if(n == 5000){
                        l = 6;
                        j = 9;
                        i = 9;
                        cont = 0;
                    }
                }
                else
                    l++;
            }
            while(cont == 1 && e < 6){
                if(board[i][j].get_num() == board[e][j].get_num()){
                    e = 6;
                    if(j == 7 || j == 8)
                        j = 6;
                    initializeSquareLocation(i, 9, j, 9, 6, 6);
                    j--;
                    p++;
                    if(p == 5000){
                        e = 6;
                        j = 9;
                        i = 9;
                        cont = 0;
                    }
                }
                else
                    e++;
            }
        }
    }
    if(n == 5000 || p == 5000){
        initializeSquareSix();
        initializeSquareEight();
        initializeSquareNine();
    }
}

/*Initializes all the individual squares, but leaves out square 5 as the last square initialized*/
void Sudoku::initializeBoard()
{
    initializeSquareOne();
    initializeSquareTwo();
    initializeSquareThree();
    initializeSquareFour();
    initializeSquareSeven();
    initializeSquareSix();
    initializeSquareEight();
    initializeSquareNine();
    initializeSquareFive();
}

void Sudoku::hideInitializedBoard()
{
    int numHide, hideCount, hideCoin;
    
    /*Square 1*/
    numHide = rand()%10;
    while(numHide < 4 || numHide == 9)
        numHide = rand()%10;
    hideCount = numHide;
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            hideCoin = rand()%2 + 1;
            if(hideCoin == 2 && hideCount != 0 && board[i][j].show_status() == 1){
                board[i][j].set_status(0);
                hideCount--;
            }
            if(hideCount != 0 && i == 2 && j == 2){
                i = 0;
                j = -1;
            }
        }
    }
    
    /*Square 2*/
    numHide = rand()%10;
    while(numHide < 4 || numHide == 9)
        numHide = rand()%10;
    hideCount = numHide;
    
    for(int i = 0; i < 3; i++){
        for(int j = 3; j < 6; j++){
            hideCoin = rand()%2 + 1;
            if(hideCoin == 2 && hideCount != 0 && board[i][j].show_status() == 1){
                board[i][j].set_status(0);
                hideCount--;
            }
            if(hideCount != 0 && i == 2 && j == 5){
                i = 0;
                j = 2;
            }
        }
    }
    
    /*Square 3*/
    numHide = rand()%10;
    while(numHide < 4 || numHide == 9)
        numHide = rand()%10;
    hideCount = numHide;
    
    for(int i = 0; i < 3; i++){
        for(int j = 6; j < 9; j++){
            hideCoin = rand()%2 + 1;
            if(hideCoin == 2 && hideCount != 0 && board[i][j].show_status() == 1){
                board[i][j].set_status(0);
                hideCount--;
            }
            if(hideCount != 0 && i == 2 && j == 8){
                i = 0;
                j = 5;
            }
        }
    }
    
    /*Square 4*/
    numHide = rand()%10;
    while(numHide < 4 || numHide == 9)
        numHide = rand()%10;
    hideCount = numHide;
    
    for(int i = 3; i < 6; i++){
        for(int j = 0; j < 3; j++){
            hideCoin = rand()%2 + 1;
            if(hideCoin == 2 && hideCount != 0 && board[i][j].show_status() == 1){
                board[i][j].set_status(0);
                hideCount--;
            }
            if(hideCount != 0 && i == 6 && j == 2){
                i = 3;
                j = -1;
            }
        }
    }
    
    /*Square 5*/
    numHide = rand()%10;
    while(numHide < 4 || numHide == 9)
        numHide = rand()%10;
    hideCount = numHide;
    
    for(int i = 3; i < 6; i++){
        for(int j = 3; j < 6; j++){
            hideCoin = rand()%2 + 1;
            if(hideCoin == 2 && hideCount != 0 && board[i][j].show_status() == 1){
                board[i][j].set_status(0);
                hideCount--;
            }
            if(hideCount != 0 && i == 5 && j == 5){
                i = 3;
                j = 2;
            }
        }
    }
    
    /*Square 6*/
    numHide = rand()%10;
    while(numHide < 4 || numHide == 9)
        numHide = rand()%10;
    hideCount = numHide;
    
    for(int i = 3; i < 6; i++){
        for(int j = 6; j < 9; j++){
            hideCoin = rand()%2 + 1;
            if(hideCoin == 2 && hideCount != 0 && board[i][j].show_status() == 1){
                board[i][j].set_status(0);
                hideCount--;
            }
            if(hideCount != 0 && i == 5 && j == 8){
                i = 3;
                j = 5;
            }
        }
    }
    
    /*Square 7*/
    numHide = rand()%10;
    while(numHide < 4 || numHide == 9)
        numHide = rand()%10;
    hideCount = numHide;
    
    for(int i = 6; i < 9; i++){
        for(int j = 0; j < 3; j++){
            hideCoin = rand()%2 + 1;
            if(hideCoin == 2 && hideCount != 0 && board[i][j].show_status() == 1){
                board[i][j].set_status(0);
                hideCount--;
            }
            if(hideCount != 0 && i == 8 && j == 2){
                i = 6;
                j = -1;
            }
        }
    }
    
    /*Square 8*/
    numHide = rand()%10;
    while(numHide < 4 || numHide == 9)
        numHide = rand()%10;
    hideCount = numHide;
    
    for(int i = 6; i < 9; i++){
        for(int j = 3; j < 6; j++){
            hideCoin = rand()%2 + 1;
            if(hideCoin == 2 && hideCount != 0 && board[i][j].show_status() == 1){
                board[i][j].set_status(0);
                hideCount--;
            }
            if(hideCount != 0 && i == 8 && j == 5){
                i = 6;
                j = 2;
            }
        }
    }
    
    /*Square 9*/
    numHide = rand()%10;
    while(numHide < 4 || numHide == 9)
        numHide = rand()%10;
    hideCount = numHide;
    
    for(int i = 6; i < 9; i++){
        for(int j = 6; j < 9; j++){
            hideCoin = rand()%2 + 1;
            if(hideCoin == 2 && hideCount != 0 && board[i][j].show_status() == 1){
                board[i][j].set_status(0);
                hideCount--;
            }
            if(hideCount != 0 && i == 8 && j == 8){
                i = 6;
                j = 5;
            }
        }
    }
}

int Sudoku::checkVictory()
{
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board[i][j].show_status() == 0)
                return 0;
        }
    }
    return 1;
}

int Sudoku::checkValidSpot(int x, int y)
{
    return board[x][y].show_status();
}

void Sudoku::uncoverSpot(int x, int y, int guess)
{
    if(board[x][y].get_num() == guess){
        board[x][y].set_status(1);
    }
    else{
        cout << "Wrong guess!" << endl;
    }
}

void Sudoku::displayBoard()
{
    cout << "Viewing board" << endl;
    for(int i = 0; i < 9; i++){
        if(i == 3 || i == 6)
            cout << endl;
        for(int j = 0; j < 9; j++){
            if(board[i][j].show_status() == 1)
                cout << "|" << "[" << board[i][j].get_num() << "]";
            else
                cout << "|" << "[-]";
            if(j == 2 || j == 5 || j == 8)
                cout << "|";
            if(j == 8)
                cout << endl;
        }
    }
    cout << endl;
}

