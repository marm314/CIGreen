#ifndef _INPUT_COMMANDS_H_
#define _INPUT_COMMANDS_H_

#include<iostream>
#include<algorithm>
#include<fstream>
#include<stdlib.h>
#include<string>
#include<stdio.h>
#include<iomanip>
#include"String_ops.h"
#include"Numbers.h"

using namespace std;
//////////////////////////
//Functions declaration //
//////////////////////////
class Input
{
 public:
 int nBasis,nBasis2;
 
 Input();
 Input(string);
 ~Input();
};
#endif // _INPUT_COMMANDS_H_



