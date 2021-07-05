#include"XuLyChuoi.h"

int ChuoiHopLe1(string num) {// trả về 1 nếu hợp lệ, trả 0 nếu k hopej lệ
	int i = 0;
	if (num[i] == '-' || num[i] == '+')// dấu
		i++;
	do {
		if (num[i] < '0' || (num[i] > '9' && num[i] < 'A') || num[i]>'F')//ngoại lệ
		{
			cout << "SO BAN NHAP KHONG HOP LE !!!\n";// throw hay cout??
			return 0;
		}
		i++;
	} while (i < (int)num.length());
	return 1;
}
int ChuoiHopLe(string num) {// trả về cơ số nếu hợp lệ, trả 0 nếu k hopej lệ
	int i = 0;
	int check2, check10, check16;// biến kiểm tra cơ số
	check2 = check16 = check10 = 0; //tại sao không dùng 1 biến? vì chạy vòng lặp biến sẽ thay đổi
	if (num[i] == '-' || num[i] == '+')// dấu
		i++;
	do {
		if (num[i] < '0' || (num[i] > '9' && num[i] < 'A') || num[i]>'F')//ngoại lệ
		{
			cout << "SO BAN NHAP KHONG HOP LE !!!\n";// throw hay cout??
			break;
		}
		if ('A' <= num[i] && num[i] <= 'F') {
			check16 = 1;
		}
		if (check16 == 0) {
			if (num[i] != '0' && num[i] != '1') { check10 = 1; }

			if (check10 == 0) check2 = 1;// nhập '101' sẽ ra nhị phân
		}
		i++;
	} while (i < (int)num.length());
	if (check16 == 1)
		return 16;
	if (check10 == 1)
		return 10;
	if (check2 == 1) return 2;
	else return 0;
}
string Chia2(string dec) {// không âm
	int k = 0, n = (int)dec.length();
	ostringstream kq;
	//string kq;
	for (int i = 0; i < n; i++) { // bỏ qua số 1 dư nếu có
		int l = ((int)dec.front() - 48);// giá trị đầu
		k = k * 10 + l;
		kq << (int)(k / 2);
		k = k % 2;

		dec.erase(0, 1);
	}
	return kq.str();
}
string HexToBin(string hex) {// chuỗi 16 --> 2   khoông aâm
	ostringstream bin;
	for (int i = 0; i < (int)hex.length(); i++) {
		for (int j = 4; j < 8; j++) { // 4 bit cuối của mỗi kí tự
			int a;
			if (hex[i] >= '0' && hex[i] <= '9')
				a = (int)((hex[i] >> (7 - j)) & 1);
			else
				a = (int)(((hex[i] - 7) >> (7 - j)) & 1); // trừ 7 để 4bit cuối A -->10 B-->11...
			bin << a;
		}
	}
	return bin.str();
}
string Cong(string dec1, string dec2) {
	if (dec1.empty())
		return dec2;
	if (dec2.empty())
		return dec1;
	int  n, nho;
	string kq;
	nho = 0;
	if ((int)dec1.length() < (int)dec2.length())
	{
		kq = dec1;
		dec1 = dec2;
		dec2 = kq;
		kq.clear();
	}
	n = (int)dec1.length();
	// dòng for chạy n+1 lần vì xét biến nhớ VD 9+9=18 chạy 2 lần
	for (int i = 0; i <= n; i++) {//str.insert(0, str2); strcat(s1, s2);
		int a, b;
		if (dec1.empty())
		{
			a = 0;
			if (nho == 0)
				break;
		}
		else
			a = ((int)dec1.back() - 48); // giá trị theo ascii 1-->4
		if (dec2.empty())
			b = 0;
		else
			b = ((int)dec2.back() - 48);// có thể dungf stoi
		int k = (a + b) + nho;
		if (k > 9) {
			nho = 1;
			k -= 10;
		}
		else
			nho = 0;
		ostringstream t;
		t << k;
		kq.insert(0, t.str());
		if (!dec1.empty())
			dec1.pop_back();
		if (!dec2.empty())
			dec2.pop_back();
	}
	return kq;
}
char* BinToHex(bool* bit)
{
	int n = 128;
	int sizebit = 128;

	char* a = new char[(sizebit / 4)];
	for (int h = (sizebit / 4) - 1; h >= 0; h--)
	{
		bool* temp = new bool[4];
		int j = 3;
		for (int k = n - 1; k >= n - 1 - 3; k--)
		{
			temp[j] = bit[k];
			j--;
		}
		char x = 0;
		for (int i = 0; i < 4; i++)
		{
			x = x | (temp[i] << (3 - i));
		}
		if (x >= 10)
			a[h] = x + 55;
		else
			a[h] = x + 48;
		n = n - 4;

	}
	return a;

}
void DocBitbool(bool* a) {
	int n = 128;
	for (int i = 0; i < n; i++) {
		if (a[i])
			cout << '1';
		else
			cout << '0';
	}
	cout << "\n*************\n";
}
string output(char a[])
{
	stringstream a1;
	for (int i = 0; i < 32; i++)
	{
		if (a[i] != '0')
		{
			for (int j = i; j < 32; j++) {
				a1 << a[j];
			}
			break;
		}

	}
	return a1.str();
}
