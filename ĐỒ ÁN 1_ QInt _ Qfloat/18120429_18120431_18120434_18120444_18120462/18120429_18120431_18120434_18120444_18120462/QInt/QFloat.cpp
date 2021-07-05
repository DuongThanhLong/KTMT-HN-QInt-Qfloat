#include "QFloat.h"

QFloat::QFloat() :QInt() {
	//data[1] = data[2] = data[3] = data[4] = 0;
}

QFloat::~QFloat() {

}
//hàm đọc hệ 10, xuất ra hệ 2
/*
QFloat::QFloat(int p, string num) {
	int K = (int)(pow(2, 14) - 1);
	int am = 0;
	QFloat temp;
	if (num[0] == '-')
	{
		am = 1;
		num.erase(0, 1);
	}
	if (p == 2) {
		int i = 127;//vị trí setBit
		for (int j = ((int)num.length() - 1); j >= 0; j--)
		{
			if (num[j] == '1')
				temp.SetBit(i);
			if (i == 0)
				break;
			i--;
		}
	}
	else if (p == 10) {//p=10

		int vt = (int)num.find(".");// vị trí dấu .
		stringstream num1; // chứa num ---> tách nguyên và thực
		string nguyen, thuc;// chứa phần nguyên và phần thục ở dạng chuỗi
		QInt *Nguyen, Thuc;// dạng bit 
						  // nguyên chỉ xét bit từ 113 bit (từ bit 1 đầu tiên)  xem như qint
						  // nếu hơn 112 bit thì phần dư xem như tràn, bit 112 là bit nhớ
						  // thực xét từ 0 --> 127 dùng để xét mũ âm và phần định trị nếu cần
						  // nếu nguyên lớn hơn 112 bit xem như thực =0
		int E = 0;// số mũ 
		int e;// phần dãy bit E
		int vitri = 127; // vitri bit 1 dau tien của Nguyen
		if (vt == -1)
		{
			nguyen = num;
			thuc = "0";
		}
		else
		{
			num.replace(vt, 1, " ");// bỏ dấu .
			num1 << num;
			num1 >> nguyen >> thuc;
		}
		if (nguyen == "0" && thuc == "0") {
			cout << "DAY LA SO 0 !!!" << endl;
			*this = temp;
			return;
		}
		else if (nguyen == "0") {
			Thuc = SetBitPhanThuc(thuc, E);
			if (E < (-K)) {// chưa xét TH 0.F*2^E
				cout << "DAY LA SO DAC BIET, KHONG THE BIEU DIEN" << endl;
				*this = temp;
				return;
			}
			for (int i = 16; i < 128; i++) {
				if (Thuc.GetBit(i - 15))
					temp.SetBit(i);
			}
			cout << E << endl;
			// thiếu quy tròn
		}
		else {
			Nguyen = new QInt(10, nguyen);
			E = SoMu2(nguyen) - 1;
			if (E > K + 1) {
				cout << "DAY LA SO DAC BIET, KHONG THE BIEU DIEN" << endl;
				*this = temp;
				return;
			}

			for (int i = 0; i < 128; i++) {
				if (Nguyen->GetBit(i)) {
					vitri = i;
					break;
				}
			}
			int j = 16;
			for (int i = vitri + 1; i < 128; i++) {// k xét bit 1 đâu tiên vì là dạng 1.F
				if (Nguyen->GetBit(i))
				{
					temp.SetBit(j);// đưa nguyen vào định trị
					j++;
				}
			}
			if (vitri > 15)
			{
				if (thuc != "0")
					Thuc = SetBitPhanThuc2(thuc);
				int j = 0;
				for (int i = 128 - (vitri - 15); i < 128; i++) {
					if (Thuc.GetBit(j))
						temp.SetBit(i);
					j++;
				}
			}
		}
		e = E + K;// đưa vào Exp
		if (am == 1)
			temp.SetBit(0);
		for (int i = 1; i < 16; i++) {// phần Exp
			if (((e >> (31 - (i + 16))) & 1)) // 15 bit cuối
				temp.SetBit(i);
		}
	}
	*this = temp;
}
*/

/*
QFloat::~QFloat() {}
string QFloat::PrintQInt_p(int p) {}// xuất theo cơ số
*/
//lấy bit tại i
int QFloat::getBitFloat(int i) {
	return ((data[i / 32] >> (31 - i % 32)) & 1);
}

//đặt bit tại i
void QFloat::setBitFloat(int i) {
	data[i / 32] = (data[i / 32] | (1 << (31 - i % 32))); // X.data[i/32] = (X.data[i/32] | (1 << (31 - i%32)))
}

//chuyển nhị phân sang thập phân
QFloat QFloat::binToDecFloat(bool* bit)
{
	for (int i = 0; i < 128; i++)
		this->setBitFloat(i);
	return *this;
}

//chuyển thập phân sang nhị phân
bool* QFloat::decToBinFloat(QFloat x)
{
	bool* Bit = new bool[128];
	for (int i = 127; i >= 0; i--)
	{
		Bit[i] = (data[i / 8] >> (7 - (i % 8)) & 1);
	}
	// Thu tu cua data = i/8
	// Vi tri bit cua data = 7 - (i%8)
	return Bit;
}

int Exponent(bool* s) // chuyển phần mũ về 
{
	bool* temp = new bool[15];
	for (int i = 0; i < 15; i++)
	{
		temp[i] = s[i + 1];
	}
	int x = 0;
	for (int j = 0; j < 15; j++)
	{
		x = x | (temp[j] << (14 - j));
	}
	return x - (pow(2, 14) - 1); // trừ cho số k
}