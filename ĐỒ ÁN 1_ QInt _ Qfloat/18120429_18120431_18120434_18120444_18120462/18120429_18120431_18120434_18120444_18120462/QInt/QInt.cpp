#include"QInt.h"


bool* QInt::DecToBin()
{
	bool* Bin = new bool[128];
	int thuTu = 3;
	int viTriBit = 0;
	for (int i = 127; i >= 0; i--) {
		if (viTriBit == 32) {
			viTriBit = 0;
			thuTu--;
		}
		Bin[i] = ((data[thuTu] >> viTriBit) & 1);
		viTriBit++;
	}
	return Bin;
}
char* QInt::DectoHex()
{
	bool* bin = this->DecToBin();
	int n = 128;
	int sizebit = 128;
	char* a = new char[sizebit / 4];
	for (int h = (sizebit / 4) - 1; h >= 0; h--)
	{
		bool* temp = new bool[4];
		int j = 3;
		for (int k = n - 1; k >= n - 1 - 3; k--)
		{
			temp[j] = bin[k];
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
bool QInt::isEqualZero()// kiểm tra số 0
{
	for (int i = 0; i < _SIZE; i++)
	{
		if (data[i] != 0)
		{
			return false;
		}
	}
	return true;
}

QInt BinToDec(bool* bit)//Hàm chuyển đổi số QInt nhị phân sang thập phân:
{
	QInt a;
	int n = 128;
	int j = 127;
	for (int i = n - 1; i >= 0; i--) {
		if (bit[i])
			a.SetBit(j);
		j--;
		if (j < 0)
			break;
	}
	return a;
}

void QInt::SetBit(int i) {
	data[i / 32] = (data[i / 32] | (1 << (31 - i % 32))); // X.data[i/32] = (X.data[i/32] | (1 << (31 - i%32)))
}
int QInt::GetBit(int i) {
	return ((data[i / 32] >> (31 - i % 32)) & 1);
}
void QInt::DocBitNP()
{
	for (int i = 0; i < 128; i++) //tuong tac bit i --> data[i/32], bit thu[i%32] từ trái qua phải 
	{
		cout << GetBit(i);
	}
}

QInt::QInt() {
	data[0] = data[1] = data[2] = data[3] = 0;
}
QInt::QInt(string num) {
	int p = ChuoiHopLe(num);
	QInt temp(p, num);
	*this = temp;
}
QInt::QInt(int p, string num) {
	int am = 0;
	int i = 0;
	QInt temp;
	if (num[i] == '-' || num[i] == '+')
	{
		if (num[i] == '-')
			am = 1;
		num.erase(0, 1);
	}
	if (p == 16) {
		num = HexToBin(num);
		p = 2;
	}
	if (p == 2) {
		int i = 127;//vị trí setBit
		for (int j = (int)num.length() - 1; j >= 0; j--)
		{
			if (num[j] == '1')
				temp.SetBit(i);
			if (i == 0)
				break;
			i--;
		}
	}
	else if (p == 10) {//p=10
		int i = 127;
		do {
			int n = ((int)num.back() - 48);
			if (n % 2 == 1)
				temp.SetBit(i);
			num = Chia2(num);
			if (num.length() == 1 && n == 0)
				break;
			if (i == 0)
				break;
			i--;

		} while (!num.empty());
	}

	if (am == 1) {
		temp = ~(temp)+1;
	}
	*this = temp;
}

QInt::~QInt() {}

QInt QInt::operator + (int n) {// chỉ xét +1
	QInt x;
	if (n == 1) {

		int i = 127;
		do {
			if (GetBit(i) == 0) {
				x.SetBit(i);
				do {
					if (GetBit(i))
						x.SetBit(i);
					i--;
				} while (i >= 0);
			}
			// phép +1 chỉ 2 TH 0+1 hoặc 1+1=10
			// --> đổi bit 0 cuối thành 1  :  1000111 --> 1001000

			i--;
		} while (i >= 0);

	}
	return x;
}
QInt QInt::operator + (QInt num) const {
	QInt temp1 = *this;
	QInt temp2;
	while (!(temp1.isEqualZero()))
	{
		temp2 = num & temp1;
		num = num ^ temp1;
		temp1 = temp2 << 1;
	}
	return num;
}
QInt QInt::operator - (QInt num) const {
	QInt temp1 = *this;
	QInt temp2;
	num = ~num + 1;
	while (!(temp1.isEqualZero()))
	{
		temp2 = num & temp1;
		num = num ^ temp1;
		temp1 = temp2 << 1;
	}
	return num;
}
QInt QInt::operator * (QInt num) const {
	QInt kq;
	QInt temp = *this;
	for (int i = 127; i >= 0; i--) {
		if (num.GetBit(i))
			kq = kq + temp;
		temp = temp << 1;

	}
	return kq;
}
QInt QInt::operator / (QInt b) {// a/b
	if (b.isEqualZero())
	{
		cout << " KHONG THE CHIA 0!!!" << endl; //throw hay cout
		//throw" KHONG THE CHIA 0!!!";
		return *this;
	}
	if (this->isEqualZero())
		return *this;
	int am = -1;// cùng dấu
	QInt kq;
	QInt a1 = *this;
	if (this->GetBit(0) != b.GetBit(0)) {// khác dấu
		am = GetBit(0);// am=1 --> a am b duong, ngược lại
		if (am)
			a1 = ~a1 + 1;
		else
			b = ~b + 1;
	}
	else if (GetBit(0)) {//cùng âm
		a1 = ~a1 + 1;
		b = ~b + 1;
	}
	if (a1 < b) //a<b -->  a/b=0
	{
		return kq;
	}
	int n;//chênh lệch số bit VD: 10001 và 111 --> n=2
	for (int t1 = 0; t1 <= 127; t1++) {// tim thứ tự bit 1 đầu tiên của a, b
		if (a1.GetBit(t1)) {
			for (int t2 = t1; t2 <= 127; t2++) {
				if (b.GetBit(t2)) {
					n = t2 - t1;
					break;
				}
			}
			break;
		}
	}
	QInt b1;// b1=b<<n   
	for (int t = n; t >= 0; t--) {// thực hiện chia 
		b1 = b << t;
		if (a1 >= b1) {
			a1 = a1 - b1;
			kq.SetBit(127);
		}
		if (t == 0) // lúc này số bit a1<= b
			break;
		kq = kq << 1;
	}
	if (am != -1)
		kq = ~kq + 1;
	return kq;
}
QInt& QInt::operator = (const QInt& num) {
	for (int i = 0; i < _SIZE; i++)
	{
		this->data[i] = num.data[i];
	}
	return *this;
}


bool QInt::operator>(QInt num) {
	if (this->GetBit(0) != num.GetBit(0)) {// khác dấu
		return num.GetBit(0);
	}
	for (int i = 1; i < 127; i++) {
		if (GetBit(i) > num.GetBit(i)) // dương và bù 2 cùng chiều so sánh
			return 1;
		if (GetBit(i) < num.GetBit(i))
			return 0;
	}
	return 0;
}
bool QInt::operator<(QInt num) {
	if (this->GetBit(0) != num.GetBit(0)) {// khác dấu
		return GetBit(0);
	}
	for (int i = 0; i < 127; i++) {
		if (GetBit(i) < num.GetBit(i)) // bù 1 và bù 2 cùng chiều so sánh
			return 1;
		if (GetBit(i) > num.GetBit(i))
			return 0;
	}
	return 0;
}
bool QInt::operator<=(QInt num) {
	if (*this < num || *this == num)
		return 1;
	return 0;
}
bool QInt::operator>=(QInt num) {
	if (*this > num || *this == num)
		return 1;
	return 0;
}
bool QInt::operator==(QInt num) {
	for (int i = 0; i < 127; i++) {
		if (this->GetBit(i) != num.GetBit(i))
			return 0;
	}
	return 1;
}

QInt QInt::operator & (const QInt& num) const {
	QInt result;

	for (int i = 0; i < _SIZE; i++)
	{
		result.data[i] = data[i] & num.data[i];
	}

	return result;
}
QInt QInt::operator | (const QInt& num) const {
	QInt result;

	for (int i = 0; i < _SIZE; i++)
	{
		result.data[i] = data[i] | num.data[i];
	}

	return result;
}
QInt QInt::operator ^ (const QInt& num) const {
	QInt result;

	for (int i = 0; i < _SIZE; i++)
	{
		result.data[i] = data[i] ^ num.data[i];
	}

	return result;
}
QInt& QInt::operator ~ () {
	for (int i = 0; i < _SIZE; i++)
	{
		data[i] = ~data[i];
	}
	return *this;
}

QInt QInt::operator >> (int n) {
	bool* a;
	bool* b = new bool[128];

	a = DecToBin();

	for (int i = 0; i < 128; i++)
	{
		b[i] = 0;
	}
	for (int i = n; i < 128; i++)
	{
		b[i] = a[i - n];
	}

	return BinToDec(b);
}
QInt QInt::operator << (int n) {
	bool* a = new bool[128];
	bool* b = new bool[128];

	a = DecToBin();

	for (int i = 0; i < 128; i++)
	{
		b[i] = 0;
	}
	for (int i = 127 - n; i >= 0; i--)
	{
		b[i] = a[i + n];
	}

	return BinToDec(b);
}

QInt& QInt::RoL() {// thay đổi *this
	int nho = GetBit(0);// lưu bit bị đẩy
	*this = *this << 1; // dịch
	if (nho == 1)
		SetBit(127);
	return *this;
}
QInt& QInt::RoR() {
	int nho = GetBit(127);// lưu bit bị đẩy
	*this = *this >> 1;
	if (nho == 1)
		SetBit(0);
	return *this;
}

//istream& operator>>(istream& input, QInt& num){}
//ostream& operator<<(ostream& output, const QInt& num){}


void QInt::ScanQInt() {
	string num;
	int p;
	int i = 0;
	int am = 0;//0 âm 1 dương
	do {
		cout << "Nhap so: ";
		cin >> num;
		p = ChuoiHopLe(num);
		if (p != 0)
			break;
	} while (p == 0);
	if (num[i] == '-' || num[i] == '+')
	{
		if (num[i] == '-')
			am = 1;
		num.erase(0, 1);
	}
	if (p == 16) {
		num = HexToBin(num);
		p = 2;
	}
	if (p == 2) {
		int i = 127;//vị trí setBit
		for (int j = (int)num.length() - 1; j >= 0; j--)
		{
			if (num[j] == '1')
				this->SetBit(i);
			if (i == 0)
				break;
			i--;
		}
	}
	else {//p=10
		int i = 127;
		do {
			int n = ((int)num.back() - 48);
			if (n % 2 == 1)
				this->SetBit(i);
			num = Chia2(num);
			//cout << num << " ----- ";
			if (num.length() == 1 && n == 0)
				break;
			if (i == 0)
				break;
			i--;

		} while (!num.empty());
	}
	if (am == 1) {
		*this = ~(*this) + 1;
	}
}

void QInt::PrintQInt() {
	string k = "";
	QInt x = *this;
	if (GetBit(0) == 1) {
		x = ~(x)+1;
	}
	for (int i = 1; i < 128; i++) {
		//ostringstream a;
		//a << GetBit(x, i);
		//k = Cong(Cong(k, k), Cong(a.str(),a.str()));
		// k=(k+bit[i])*2
		k = Cong(k, k);

		if (x.GetBit(i) == 1)
		{
			k = Cong(k, "1");
		}
		/*
		VD: dãy bit 1011  ---> Thập phân: ((1*2 + 0)*2 +1)*2 +1*/
	}

	if (GetBit(0)) {
		k.insert(0, "-");
	}
	cout << k << endl;
}

string QInt::PrintQInt_p(int p) {// xuất theo cơ số
	if (p == 10) {
		string k = "";
		QInt x = *this;
		if (GetBit(0) == 1) {
			x = ~(x)+1;
		}
		for (int i = 1; i < 128; i++) {
			k = Cong(k, k);

			if (x.GetBit(i) == 1)
			{
				k = Cong(k, "1");
			}
			/*
			VD: dãy bit 1011  ---> Thập phân: ((1*2 + 0)*2 +1)*2 +1*/
		}

		if (GetBit(0)) {
			k.insert(0, "-");
		}
		return k;
	}
	else if (p == 2) {
		stringstream k;
		for (int i = 0; i < 128; i++) {
			if (GetBit(i)) {
				for (int j = i; j < 128; j++)
					k << GetBit(j);
				break;
			}
		}
		return k.str();
	}
	else
		return output(this->DectoHex());
}