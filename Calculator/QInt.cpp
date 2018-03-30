#include "stdafx.h"
#include "QInt.h"


void SetBit(QInt &a, int bit, int i)
{
	a.data[i / 32] = a.data[i / 32] | (bit << (31 - (i % 32)));
}
bool GetBit(QInt a, int i)
{
	return (a.data[i / 32] >> (31 - i % 32)) & 1;
}
string strDiv2(string strX)
{
	string strResult;
	int nValue, nMod = 0;
	int index = 0;
	for (int i = 0; i < strX.length(); i++)
	{
		nValue = (strX[i] + nMod * 10 - 48) / 2;
		if (i || nValue)
		{
			strResult.push_back(nValue + 48);
			index++;
		}
		nMod = (strX[i] - 48) % 2;
	}
	return strResult;
}
void StrToQInt(string strX, QInt &a)
{
	// bắt đầu set bit tại vị trí cuối cùng
	int i = 127;
	while (strX != "")
	{
		// Tính phần dư
		int bit = (strX[strX.length() - 1] - 48) % 2;
		// Tạo bit (biến bit) tại vị trí bit i của biến a
		SetBit(a, bit, i);
		// Chia chuỗi số X cho 2
		strX = strDiv2(strX);
		i--;
	}
}
void DecStrToQInt(string strX, QInt & a)
{
	if (strX[0] == '-')
	{
		strX.erase(0, 1);
		StrToQInt(strX, a);
		TwoComplement(a);
	}
	else
		StrToQInt(strX, a);
}
void ScanQInt(QInt &x)
{
	//biên chuỗi lưu giá trị người dùng nhập vào dưới dạng thập phân
	string strX;
	cin >> strX;
	if (strX[0] == '-')
	{
		strX.erase(0, 1);
		StrToQInt(strX, x);
		TwoComplement(x);
		return;
	}
	StrToQInt(strX, x);
}
string PrintQInt(QInt x)
{
	//chuỗi lưu dạng thập phân
	string strX = "0";
	int i = 0;
	bool bit = GetBit(x, i);
	//biểu diễn số âm bằng số bù 2
	if (bit)
	{
		intoNor(x);
		for (; i < 128; i++)
		{
			bit = GetBit(x, i);
			if (bit)
				strX = strAdd(strX, str2Squared(127 - i));
		}
		strX.insert(0, 1, '-');
	}
	////biểu diễn số dương
	else
	{
		for (; i < 128; i++)
		{
			bit = GetBit(x, i);
			if (bit)
				strX = strAdd(strX, str2Squared(127 - i));
		}
	}
	return strX;
}

string strAdd(string strX, string strY)
{
	string strResult;
	int Temp = 0, div = 0, mod = 0;
	int lengthX = strX.length();
	int lengthY = strY.length();
	while (lengthX != 0 && lengthY != 0)
	{
		if (strX[0] == '0') { lengthX--; break; }
		if (strY[0] == '0') { lengthY--; break; }
		Temp = div + (strX[lengthX - 1] - 48) + (strY[lengthY - 1] - 48);
		mod = Temp % 10;
		strResult.insert(0, 1, mod + 48);
		div = Temp / 10;
		lengthX--; lengthY--;
		strX.pop_back(); strY.pop_back();
	}
	if (lengthX > 0)
	{
		int i = strX.length() - 1;
		while (div && i >= 0)
		{
			if (strX[i] == '9') {
				strX[i] = '0';
				i--; div = 1;
			}
			else
			{
				strX[i] += div;
				div = 0;
			}
		}
		if (div) strX.insert(0, 1, '1');
		strResult.insert(0, strX);
	}
	else if (lengthY > 0)
	{
		int i = strY.length() - 1;
		while (div && i >= 0)
		{
			if (strY[i] == '9') {
				strY[i] = '0';
				i--; div = 1;
			}
			else
			{
				strY[i] += div;
				div = 0;
			}
		}
		if (div) strY.insert(0, 1, '1');
		strResult.insert(0, strY);
	}
	else
	{
		if (div) strResult.insert(0, 1, div + 48);
	}
	return strResult;
}

string strMulti2(string strX)
{
	return strAdd(strX, strX);
}

string str2Squared(int n)
{
	string strX = "2";
	if (!n)
		return "1";
	for (int i = 1; i < n; i++)
	{
		strX = strMulti2(strX);
	}
	return strX;
}

void TwoComplement(QInt & x)
{
	for (int i = 0; i < 4; i++)
	{
		x.data[i] = ~x.data[i];
	}
	QInt one;
	SetBit(one, 1, 127);
	x = x + one;
}

void intoNor(QInt & x)
{
	QInt one;
	SetBit(one, 1, 127);
	x = x - one;
	for (int i = 0; i < 4; i++)
	{
		x.data[i] = ~x.data[i];
	}
}

bool * DecToBin(QInt x)
{
	bool *Bin = new bool[128];
	for (int i = 0; i < 128; i++)
	{
		bool bit = GetBit(x, i);
		Bin[i] = bit;
	}
	return Bin;
}

QInt BinToDec(bool * bit)
{
	QInt Dec;
	for (int i = 0; i < 128; i++)
	{
		SetBit(Dec, bit[i], i);
	}
	return Dec;
}

char BinToHex0(bool *b)
{
	string temp;
	string kq = "0";
	char x;
	for (int i = 0; i<4; i++)
		if (b[i] != 0)
		{
			temp = str2Squared(3 - i);
			kq = strAdd(kq, temp);
		}
	if (kq.length() < 2)
	{
		x = kq[0];
		return x;
	}
	else
	{
		int m = (kq[0] - 48) * 10 + kq[1] - 48;
		switch (m)
		{
		case 10:
			x = 'A';
			break;
		case 11:
			x = 'B';
			break;
		case 12:
			x = 'C';
			break;
		case 13:
			x = 'D';
			break;
		case 14:
			x = 'E';
			break;
		default:
			x = 'F';
			break;
		}
	}
	return x;
}

int lengthBit(bool *bit)
{
	for (int i = 0; i < 128; i++)
		if (bit[i] == 1)
			return 128 - i;
	return 0;
}

char* BintoHex(bool* bit)
{
	int n = lengthBit(bit);
	int l = n / 4;
	int lmax = l;
	bool b[4];
	if (n % 4 != 0) lmax++;
	char *kq = new char[lmax];
	for (int i = 0; i < lmax; i++)
	{
		for (int k = 0; k < 4; k++)
			b[k] = 0;
		for (int j = 0; j < 4; j++)
			b[3 - j] = bit[128 - 4 * i - j - 1];

		kq[lmax - i - 1] = BinToHex0(b);

	}

	return kq;
}


string HexToBin(string s)
{
	int a;
	string temp1 = "0000";
	string kq = "";
	string temp;
	int n = s.length();
	for (int i = 0; i < n; i++)
	{

		if (s[i] - 48 > 0 && s[i] - 48 < 10)
		{
			a = s[i] - 48;
			for (int j = 0; j<4; j++)
			{
				temp1[3 - j] = a % 2 + 48;
				a = a / 2;
			}

			kq = kq + temp1;
		}
		else
		{
			switch (s[i] - 55)
			{
			case 10:
				temp = "1010";
				kq = kq + temp;
				break;
			case 11:
				temp = "1011";
				kq = kq + temp;
				break;
			case 12:
				temp = "1100";
				kq = kq + temp;
				break;
			case 13:
				temp = "1101";
				kq = kq + temp;
				break;
			case 14:
				temp = "1110";
				kq = kq + temp;
				break;

			default:
				temp = "1111";
				kq = kq + temp;
				break;
			}
		}
	}
	for (int i = 0; i<kq.length(); i++)
		if (kq[i] == '1')
		{
			kq.erase(0, i);
			break;
		}
	return kq;
}
QInt operator+(QInt a, QInt b)
{
	QInt sum;
	//bit nhớ
	int rebit = 0;
	int bita, bitb, bitsum;
	for (int i = 127; i >= 0; i--)
	{
		bita = GetBit(a, i);
		bitb = GetBit(b, i);
		bitsum = bita^bitb;
		bitsum = bitsum^rebit;
		SetBit(sum, bitsum, i);
		if ((bita && bitb) || (bita && rebit) || (bitb && rebit))
			rebit = 1;
		else
			rebit = 0;
	}
	if ((bita && bitb && !bitsum) || (!bita && !bitb && bitsum))
		_DEBUG_ERROR("overload");
	return sum;
}

char* DecToHex(QInt x)
{
	bool *b = NULL;
	b = DecToBin(x);
	char* c = NULL;
	c = BintoHex(b);
	return c;

}
QInt operator-(QInt a, QInt b)
{
	TwoComplement(b);
	return a + b;
}

QInt operator*(QInt a, QInt b)
{
	//M = a, Q = b
	int Q[2];
	int M[2];
	for (int i = 3; i > 1; i--)
	{
		M[i - 2] = a.data[i];
		Q[i - 2] = b.data[i];
	}
	//Q-1
	int C = 0;
	//khởi tạo A = 0, k = n
	int A[2] = { 0 }, k = 64;
	//bit cuối của Q
	int Q0 = 0;
	while (k > 0)
	{
		Q0 = Q[1] & 1;
		//nếu 2 bit cuôi của Q0C = 10
		if (Q0 && !C)
		{
			int M2[2];
			M2[1] = ~M[1];
			M2[0] = ~M[0];
			if (M2[1] == -1)
				M2[0]++;
			M2[1]++;
			//
			int bitA, bitM;
			bitA = A[1] >> 31;
			bitM = M2[1] >> 31;
			A[1] = A[1] + M2[1];
			A[0] = A[0] + M2[0];
			if ((bitA && bitM) || (bitA && !(A[1] >> 31)))
				A[0] ++;
		}
		//nếu 2 bit cuôi của Q0C = 01
		else if (!Q0 && C)
		{
			int bitA, bitM;
			bitA = A[1] >> 31;
			bitM = M[1] >> 31;
			A[1] = A[1] + M[1];
			A[0] = A[0] + M[0];
			if ((bitA && bitM) || (bitA && !(A[1] >> 31)))
				A[0] ++;
		}
		//nếu 2 bit cuôi của Q0C = 00, 11 thì A không thay đổi
		//shift right [A, Q, Q-1]
		C = Q[1] & 1;
		Q[1] = Q[1] >> 1;
		if (Q[1] >> 31)
			Q[1] = Q[1] ^ (!(Q[0] & 1) << 31);
		else
			Q[1] = Q[1] | ((Q[0] & 1) << 31);

		Q[0] = Q[0] >> 1;
		if (Q[0] >> 31)
			Q[0] = Q[0] ^ (!(A[1] & 1) << 31);
		else
			Q[0] = Q[0] | ((A[1] & 1) << 31);
		A[1] = A[1] >> 1;
		if (A[1] >> 31)
			A[1] = A[1] ^ (!(A[0] & 1) << 31);
		else
			A[1] = A[1] | ((A[0] & 1) << 31);
		A[0] = A[0] >> 1;
		k--;
	}
	QInt sum;
	sum.data[0] = A[0];
	sum.data[1] = A[1];
	sum.data[2] = Q[0];
	sum.data[3] = Q[1];
	return sum;
}

QInt operator/(QInt Q, QInt M)
{
	QInt A;
	if (GetBit(Q, 0))
		A = ~A;
	int k = 128;
	while (k > 0)
	{
		//dịch trái----------------
		A = A << 1;
		//bit đầu tiền của Q
		bool bit = GetBit(Q, 0);
		//gán bit đâu của Q cho bit cuối của A
		A.data[3] = A.data[3] | bit;
		Q = Q << 1;
		//--------------------------
		A = A - M;
		if (GetBit(A, 0))
		{
			//bit Q0
			bit = GetBit(Q, 127);
			if (bit)
				Q.data[3] ^= (1 << 31);
			else
				SetBit(Q, 0, 127);
			A = A + M;
		}
		else
			SetBit(Q, 1, 127);
		k--;
	}
	return Q;
}

QInt operator~(QInt & x)
{
	QInt kq;
	for (int i = 0; i < 4; i++)
		kq.data[i] = ~x.data[i];
	return kq;
}


QInt operator &(QInt &a, QInt &b)
{
	QInt kq;
	for (int i = 0; i < 4; i++)
		kq.data[i] = a.data[i] & b.data[i];
	return kq;
}
QInt operator |(QInt &a, QInt &b)
{
	QInt kq;
	for (int i = 0; i < 4; i++)
		kq.data[i] = a.data[i] | b.data[i];
	return kq;
}
QInt operator ^(QInt &a, QInt &b)
{
	QInt kq;
	for (int i = 0; i < 4; i++)
		kq.data[i] = a.data[i] ^ b.data[i];
	return kq;
}
QInt operator<<(QInt & x, int n)
{
	bool *bit = DecToBin(x);
	for (int i = 0; i < 128 - n; i++)
	{
		bit[i] = bit[i + n];
	}
	for (int j = 128 - n; j < 128; j++)
		bit[j] = 0;
	return BinToDec(bit);
}

QInt operator >> (QInt &a, int x)
{
	bool*b;
	QInt kq;
	b = DecToBin(a);
	for (int i = 127; i >= x; i--)
		b[i] = b[i - x];
	if (GetBit(a, 0) == 0)
	{
		for (int i = 0; i < x; i++)
			b[i] = 0;
	}
	else
	{
		for (int i = 0; i < x; i++)
			b[i] = 1;
	}
	kq = BinToDec(b);
	return kq;
}

QInt operator-(QInt x)
{
	TwoComplement(x);
	return x;
}


void QInt::operator=(int n)
{
	data[3] = n;
	if (n >= 0)
	{
		for (int i = 0; i < 3; i++)
			data[i] = 0;
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			data[i] = 0;
			data[i] = ~data[i];
		}
	}
}

bool QInt::operator==(int n) const
{
	int a = data[3];
	return a == n;
}

int strToint(string s, int m, int n)
{
	if (n - m == 1)
		return s[m] - 48;
	else return (s[m] - 48) * 10 + s[n - 1] - 48;
}
void strCopy(string s, string &temp, int a, int b)
{
	for (int i = a; i < b; i++)
		temp.push_back(s[i]);
}
bool* strToBit(string s)
{
	int n = s.length();
	bool* bit = new bool[128]{ 0 };
	for (int i = 0; i<n; i++)
		bit[127 - i] = s[n - i - 1] - 48;
	return bit;
}
string case_Bin_To_Dec(string s)
{
	QInt a;
	bool* bit;
	bit = strToBit(s);
	a = BinToDec(bit);
	string kq;
	kq = PrintQInt(a);
	delete[]bit;
	return kq;
}
string case_Bin_To_Hex(string s)
{
	if (s == "0")
		return "0";
	QInt a;
	bool *bit;
	int n = s.length() / 4;
	if (s.length() % 4 != 0) n++;
	char* Char = new char[n];
	bit = strToBit(s);
	Char = BintoHex(bit);
	string kq;
	for (int i = 0; i < n; i++)
		kq.push_back(Char[i]);
	return kq;
}
string case_Dec_To_Bin(string s)
{
	QInt a;
	bool* bit;
	DecStrToQInt(s, a);
	bit = DecToBin(a);
	int n = lengthBit(bit);
	string kq;
	int temp;
	for (int i = 0; i < n; i++)
	{
		temp = bit[128 - n + i];
		kq.push_back(temp + 48);
	}
	if (kq.empty() == true)
		kq = "0";
	return kq;
}
string case_Dec_To_Hex(string s)
{
	string str = case_Dec_To_Bin(s);
	string kq = case_Bin_To_Hex(str);
	return kq;
}
string case_Hex_To_Bin(string s)
{
	string kq;
	kq = HexToBin(s);
	return kq;
}
string case_Hex_To_Dec(string s)
{
	string kq;
	kq = HexToBin(s);
	kq = case_Bin_To_Dec(kq);
	return kq;
}