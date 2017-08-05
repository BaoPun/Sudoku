//
//  number.cpp
//  Sudoku
//
//  Created by Bao Phung on 8/2/17.
//  Copyright © 2017 Bao Phung. All rights reserved.
//

#include "./number.h"

Number::Number()
{
    show = 1;
    num = 0;
}

int Number::show_status()
{
    return show;
}

void Number::set_status(int s)
{
    show = s;
}

int Number::get_num()
{
    return num;
}

void Number::set_num(int n)
{
    num = n;
}
