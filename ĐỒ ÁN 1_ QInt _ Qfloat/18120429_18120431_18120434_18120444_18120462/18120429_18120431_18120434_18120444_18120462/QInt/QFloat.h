#pragma once
#include "QInt.h"
#include  "XuLyChuoi.h"
using namespace std;

#define QFLOAT_SIZE		4
#define SIGN_BIT		127
#define EXP_BIT			112
#define SIGNIF_BIT		0
#define NUMS_OF_SIGNIF	112
#define NUMS_OF_EXP		15
#define BIAS			16383

class QFloat: public QInt {
private:
	int data[QFLOAT_SIZE];

public:
	QFloat();
	~QFloat();
	QFloat(int, string);
	//lấy bit tại i
	int getBitFloat(int i);
	//set bit tại i
	void setBitFloat(int i);
	//Toán tử gán
	QFloat& operator=(const QFloat& A);
	QFloat& operator ~ ();
	QFloat operator + (int);// cộng số int
	//nhập ở hệ bất kỳ (2 or 10)
	void scanQFloat();
	//hàm nhân 2
	string mulByTwo(string str);
	//kiểm tra = 0
	bool isEqualZero_Float();
	//hàm chuyển hệ 10 sang hệ 2
	bool* decToBinFloat(QFloat x);
	//hàm chuyển hệ 2 sang 10
	QFloat binToDecFloat(bool* bit);
	void PrintQfloat(bool* s);
	string PrintQInt_p(int p);// xuất theo cơ số
};
bool* stringtobin(string s);
int Exponent(bool* s);
float Significand(bool* s);
float Significand1(bool* s);
string Tostring(bool* s);