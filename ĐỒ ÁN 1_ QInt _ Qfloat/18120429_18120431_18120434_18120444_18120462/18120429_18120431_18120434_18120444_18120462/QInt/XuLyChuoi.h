#pragma once

#ifndef _CHUOI_H_
#define _CHUOI_H_
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <conio.h>
#include<math.h>
#include <stdio.h>
#include<fstream>

using namespace std;
void DocBitbool(bool* a);
string output(char a[]);
int ChuoiHopLe1(string num);
int ChuoiHopLe(string num);

string Chia2(string dec);
string HexToBin(string hex);
string Cong(string dec1, string dec2);
char* BinToHex(bool* bit);
#endif