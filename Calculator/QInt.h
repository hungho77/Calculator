﻿#pragma once
#include<iostream>
#include<string>
using namespace std;
struct QInt
{
	//dữ liệu lưu 128 bit
	int data[4];
	QInt()
	{
		for (int i = 0; i < 4; i++)
			data[i] = 0;
	}
};
//gắn bit vào data tại vị trí i tương ứng
void SetBit(QInt &a, int bit, int i);
//lấy bit từ data tại vị trí i tương ứng
bool GetBit(QInt a, int i);
string strDiv2(string strX);
//hàm chuyển chuỗi về kiểu QInt
void StrToQInt(string strX, QInt &a);
//hàm nhập 
void ScanQInt(QInt &x);
//hàm xuất
string PrintQInt(QInt x);
//hàm cộng 2 chuỗi thập phân
string strAdd(string strX, string strY);
//hàm nhân chuỗi thập phân với 2
string strMulti2(string strX);
//hàm 2 lũy thừa n dạng chuỗi thập phân
string str2Squared(int n);
//hàm chuyển số âm về biểu diễn bù 2
void TwoComplement(QInt &x);
//hàm chuyển số bù 2 về biểu diễn số âm
void intoNor(QInt &x);
//hàm chuyển từ hệ thập phân sang hệ nhị phân
bool * DecToBin(QInt x);
////hàm chuyển từ hệ nhị phân sang hệ thập phân
QInt BinToDec(bool *bit);
////hàm chuyển từ hệ nhị phân sang hệ 16
char BinToHex0(bool *b);
int lengthBit(bool *bit);
char* BintoHex(bool* bit);
////hàm chuyển từ hệ thập phân sang hệ 16
char* DecToHex(QInt x);
string HexToBin(string s);
QInt operator + (QInt a, QInt b);
QInt operator - (QInt a, QInt b);
QInt operator * (QInt a, QInt b);
QInt operator / (QInt a, QInt b);
void operator ~(QInt &x);
QInt operator &(QInt &a, QInt &b);
QInt operator |(QInt &a, QInt &b);
QInt operator ^(QInt &a, QInt &b);
QInt operator <<(QInt &x, int n);
QInt operator >> (QInt &a, int x);

#pragma once