#include"QInt.h"
#include "QFloat.h"
void UseQInt(string fileInput, string fileOutput) {// xét mỗi dòng
	fstream file_input;
	fstream file_output;
	file_input.open(fileInput, ios::in);
	file_output.open(fileOutput, ios::out);
	while (!file_input.eof())
	{
		string line;
		getline(file_input, line);
		stringstream line1;
		line1 << line; // lưu line
		vector<string> MangToanTu = { "~","+"," - ","*","/","<",">","==","<=",">=","&","|","^","<<",">>","rol","ror" };
		// MangToanTu[0] là toán tử 1 ngôi
		int NgoiToanTu = 0;// =0 khi không có toán tử, =1 khi là toán tử "~", còn lại =2
		string ToanTu = "";// mặc định không có tt
		int p1, p2;// cơ số     // ? int hay string // với NgoiToanTu!=0 p2 là duy nhất --> cơ số xuất
		string str1, str2;// 2 số cần tính toán,
						  // nếu NgoiToanTu!=2 --> str2 là chuỗi duy nhất
						  // nếu ToanTu là "<<",">>","rol","ror" thì str2 là n bit
		QInt* kq;// biến chứa kq  ,kq xuất theo cơ số p2
		int ss = -1;// kq so sánh  0 là false 1 là true -1 khi k phải phép ss
		if (line.find(MangToanTu[0], 0) != -1) { // kiểm tra tt 1 ngôi
			NgoiToanTu = 1;
		}
		else {
			for (int i = 1; i < MangToanTu.size(); i++) {// tt 2ngoi
				if (line.find(MangToanTu[i]) != -1) {
					NgoiToanTu = 2;
					break;
				}
			}
		}
		// đưa chuỗi vào kq, p2 là cơ số xuất
		if (NgoiToanTu == 0) {
			line1 >> p1 >> p2 >> str1;
			kq = new QInt(p1, str1);
		}
		else if (NgoiToanTu == 1) {
			line1 >> p2 >> ToanTu >> str1;
			kq = new QInt(p2, str1);
			(*kq) = ~(*kq);
		}
		else {
			kq = new QInt();
			QInt* a, *b;// ab Là QInt của str1 str2
			line1 >> p2 >> str1 >> ToanTu >> str2;
			a = new QInt(p2, str1);
			b = new QInt(p2, str2);
			if (ToanTu == "+")
				*kq = *a + *b;
			else if (ToanTu == "-")
				*kq = *a - *b;
			else if (ToanTu == "*")
				*kq = (*a) * (*b);
			else if (ToanTu == "/")
				*kq = (*a) / (*b);
			else if (ToanTu == "<")
				ss = *a < *b;
			else if (ToanTu == ">")
				ss = *a > * b;
			else if (ToanTu == "==")
				ss = *a == *b;
			else if (ToanTu == "<=")
				ss = *a <= *b;
			else if (ToanTu == ">=")
				ss = *a >= *b;
			else if (ToanTu == "&")
				*kq = *a & *b;
			else if (ToanTu == "|")
				*kq = *a | *b;
			else if (ToanTu == "^")
				*kq = *a ^ *b;
			else { // "<<",">>","rol","ror"
				int n = stoi(str2);
				if (ToanTu == "<<") {
					*kq = *a << n;
				}
				else if (ToanTu == ">>") {
					*kq = *a >> n;
				}
				else if (ToanTu == "rol") {
					for (int i = 0; i < n; i++) {
						*kq = a->RoL();
					}
				}
				else if (ToanTu == "ror") {
					for (int i = 0; i < n; i++) {
						*kq = a->RoR();
					}
				}
			}
		}

		// KẾT QUẢ

		if (ss == -1) {//không phải toán tử so sánh
			{
				cout << kq->PrintQInt_p(p2) << endl;
				file_output << kq->PrintQInt_p(p2) << endl;

			}
		}
		else
		{
			cout << ((ss == 0) ? "false" : "true") << endl;
			file_output << ((ss == 0) ? "false" : "true") << endl;

		}
	}
	file_input.close();
	file_output.close();
}
//int main() {
//	string fileI, fileO;
//	cout << "FILE INPUT: ";
//	cin >> fileI;
//	cout << "FILE OUTPUT:  ";
//	cin >> fileO;
//	UseQInt(fileI, fileO);
//
//	return 0;
//}



int main(int argc, char* argv[]) {
	//test tay
//	string fileI, fileO;
//	cout << "FILE INPUT: ";
//	cin >> fileI;
//	cout << "FILE OUTPUT:  ";
//	cin >> fileO;
//	UseQInt(fileI, fileO);
	if (argc < 4)
	{
		cout << "tham so khong hop le\n";
	}
	else {
		string fileI, fileO, mode;
		fileI = string(argv[1]);
		fileO = string(argv[2]);
		mode = string(argv[3]);
		if (mode == "1") {
			UseQInt(fileI, fileO);
			cout << "\nChuong trinh ket thuc\n";
		}
		else
			cout << "CHUA CO CHUONG TRINH QFLOAT\n";
	}
	return 0;
}

/*
int main() {
	QFloat a(10, "12.625");
	a.DocBitNP();
	return 0;
}
*/