//
//  number.h
//  Sudoku
//
//  Created by Bao Phung on 8/2/17.
//  Copyright © 2017 Bao Phung. All rights reserved.
//

#ifndef number_h
#define number_h

#include <iostream>
#include <stdlib.h>
#include <time.h>

using std::cin;
using std::cout;
using std::endl;

class Number
{
    private:
        int show, num;
    public:
        Number();
        int show_status();
        void set_status(int);
        int get_num();
        void set_num(int);
};


#endif /* number_h */
