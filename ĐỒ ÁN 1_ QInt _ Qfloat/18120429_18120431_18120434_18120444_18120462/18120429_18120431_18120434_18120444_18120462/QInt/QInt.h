#pragma once
#ifndef _QINT_H_
#define _QINT_H_

#include"XuLyChuoi.h"

#define _SIZE 4


class QInt {
private:
	int data[_SIZE];
public:
	QInt();
	QInt(string);
	QInt(int, string);
	~QInt();
public:
	void ScanQInt();
	void PrintQInt();
	string PrintQInt_p(int p);// xuất theo cơ số
public:
	void SetBit(int);
	int GetBit(int);
	void DocBitNP();// đọc đủ bit
public:
	bool* DecToBin();//Hàm chuyển đổi số QInt thập phân sang nhị phân:
	char* DectoHex();//Hàm chuyển đổi số QInt thập phân sang thập lục phân:
	bool isEqualZero();// kiểm tra số 0

public:
	QInt operator + (int);// cộng số int
	QInt operator + (QInt) const;// cộng 
	QInt operator - (QInt) const;// trừ
	QInt operator * (QInt) const;// nhân
	QInt operator / (QInt);// chia
public:
	QInt& operator = (const QInt&);// gán
	bool operator>(QInt);
	bool operator<(QInt);
	bool operator<=(QInt);
	bool operator>=(QInt);
	bool operator==(QInt);
public:
	QInt operator & (const QInt&) const;//AND 
	QInt operator | (const QInt&) const;// OR
	QInt operator ^ (const QInt&) const;//XOR
	QInt& operator ~ ();//NOT
public:
	QInt operator >> (int);// dịch phải
	QInt operator << (int);// dịch trái
	QInt& RoL();// xoay trái
	QInt& RoR();// xoay phải
//public:
//	friend istream& operator>>(istream& input, QInt& num);
//	friend ostream& operator<<(ostream& output, const QInt& num);
};
//int SizeOfBool(bool* a);
QInt BinToDec(bool* bit);
#endif
