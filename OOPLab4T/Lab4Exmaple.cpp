#include <iostream>
//***                    Перше завдання
//
using namespace std;
enum STATE {
	OK, BAD_INIT, BAD_DIV
};
class VectorDouble
{
	double* vec;
	int num = 2;
	int state = 0;
	static double bad_index; 
public:
	VectorDouble() :VectorDouble(1) {}
	VectorDouble(int n);
	VectorDouble(int n, double);
	VectorDouble(const VectorDouble& s);  
	VectorDouble& operator=(const VectorDouble& s);
	VectorDouble& operator=(VectorDouble&& s) noexcept;
	void Init(int n);   
	void Init(int n, double);  
	~VectorDouble() {
		if (vec) delete[] vec;
	}
	friend istream& operator>>(istream& is, VectorDouble& s);
	friend ostream& operator<<(ostream& os, VectorDouble& s);
	double& operator[](int index);

	VectorDouble& operator++();
	VectorDouble& operator+=(const VectorDouble& s);
	VectorDouble& operator+=(const double& b);
	VectorDouble& operator+=(const float& b);
	VectorDouble  operator+(const VectorDouble& b);
	VectorDouble  operator+(const double& b);
	VectorDouble  operator+(const float& b);

	VectorDouble& operator--();
	VectorDouble& operator-=(const VectorDouble& s);
	VectorDouble& operator-=(const double& b);
	VectorDouble& operator-=(const float& b);
	VectorDouble  operator-(const VectorDouble& b);
	VectorDouble  operator-(const double& b);
	VectorDouble  operator-(const float& b);

	VectorDouble& operator*=(const VectorDouble& b);
	VectorDouble& operator*=(const double& b);
	VectorDouble& operator*=(const float& b);
	VectorDouble operator*(const VectorDouble& b);
	VectorDouble operator*(const double& b);
	VectorDouble operator*(const float& b);

	VectorDouble& operator/=(const VectorDouble& b);
	VectorDouble& operator/=(const double& b);
	VectorDouble& operator/=(const float& b);

	VectorDouble& operator/(const VectorDouble& b);
	VectorDouble operator/(const double& b);
	VectorDouble operator/(const float& b);

	bool operator>(const VectorDouble& s);
	bool operator>=(const VectorDouble& s);
	bool operator<(const VectorDouble& s);
	bool operator<=(const VectorDouble& s);
};

double VectorDouble::bad_index = 0;
VectorDouble::VectorDouble(int n) {
	if (n <= 0)    n = 1;  
	num = n;
	vec = new double[n];
	for (int i = 0; i < n; i++) {
		vec[i] = 0.0;
	}
}
VectorDouble::VectorDouble(int n, double b) : VectorDouble(n) {
	for (int i = 0; i < num; i++) {
		vec[i] = b;
	}
}
VectorDouble::VectorDouble(const VectorDouble& s) {
	num = s.num;
	vec = new double[num];
	state = 1;
	for (int i = 0; i < num; i++)   vec[i] = s.vec[i];
}
VectorDouble& VectorDouble::operator=(const VectorDouble& s) {
	if (this == &s) return *this;
	if (num != s.num)
	{
		if (vec) delete[] vec;
		num = s.num;
		vec = new double[num];
		state = 1;
	}
	for (int i = 0; i < num; i++)   vec[i] = s.vec[i];
	return *this;
}
VectorDouble& VectorDouble::operator=(VectorDouble&& s) noexcept
{
	if (this == &s) return *this;
	num = s.num; state = s.state;
	if (this->vec != nullptr) delete[] vec;
	vec = s.vec;
	s.num = 0; s.vec = nullptr; s.state = -1;
	return *this;
}
void VectorDouble::Init(int n) {
	if (num != n) {
		if (vec != nullptr) delete[] vec;
		num = n;
		vec = new double[n];
	}
	for (int i = 0; i < num; i++) 	vec[i] = 0;
}
void VectorDouble::Init(int n, double b) {
	if (num != n) {
		if (vec != nullptr) delete[] vec;
		num = n;
		vec = new double[n];
	}
	for (int i = 0; i < num; i++) 	vec[i] = b;
}
istream& operator>>(istream& is, VectorDouble& s) {
	for (int i = 0; i < s.num; i++)
	{
		is >> s.vec[i];
	}
	return is;
};
ostream& operator<<(ostream& os, VectorDouble& s) {
	for (int i = 0; i < s.num; i++)
		os << s.vec[i] << '\t';
	os << endl;
	return os;
}
double& VectorDouble::operator[](int index)
{
	if (index >= 0 && index < num) return vec[index];
	cout << " Error : operator[] - index out of range \n";
	return bad_index;
}
VectorDouble& VectorDouble::operator-=(const VectorDouble& b)
{
	int i;
	if (num == b.num) for (i = 0; i < num; i++) vec[i] -= b.vec[i];
	else {
		cout << " Warning: vectors of different sizes are used in operation -= \n";
		if (num < b.num) {
			double* tmp;
			tmp = new double[b.num];
			for (i = 0; i < num; i++) tmp[i] = vec[i] - b.vec[i];
			for (; i < b.num; i++) tmp[i] = -b.vec[i];
			num = b.num;
			if (vec != nullptr) delete[] vec;
			vec = tmp;
		}
		else 	for (i = 0; i < b.num; i++) vec[i] -= b.vec[i];
	}
	return *this;
}
VectorDouble& VectorDouble::operator-=(const double& b)
{
	if (num > 0) {
		for (int i = 0; i < num; i++) vec[i] -= b;
	}
	return *this;
}
VectorDouble& VectorDouble::operator-=(const float& b)
{
	if (num > 0) {
		for (int i = 0; i < num; i++) vec[i] -= b;
	}
	return *this;
}
VectorDouble& VectorDouble::operator--()
{
	for (int i = 0; i < num; i++) vec[i] -= 1;
	return *this;
}
VectorDouble VectorDouble::operator-(const VectorDouble& b)
{
	VectorDouble tmp(*this);
	tmp -= b;
	return tmp;
}
VectorDouble VectorDouble::operator-(const double& b)
{
	VectorDouble tmp(*this);
	tmp -= b;
	return tmp;
}
VectorDouble VectorDouble::operator-(const float& b)
{
	VectorDouble tmp(*this);
	tmp -= b;
	return tmp;
}
VectorDouble& VectorDouble::operator++()
{
	for (int i = 0; i < num; i++) vec[i] += 1;
	return *this;
}
VectorDouble& VectorDouble::operator+=(const VectorDouble& b)
{
	int i;
	if (num == b.num) for (i = 0; i < num; i++) vec[i] += b.vec[i];
	else
	{
		cout << " Warning: vectors of different sizes are used in operation += \n";
		if (num < b.num) {
			double* tmp;
			tmp = new double[b.num];
			for (i = 0; i < num; i++) tmp[i] = vec[i] + b.vec[i];
			for (; i < b.num; i++) tmp[i] = b.vec[i];
			num = b.num;
			if (vec != nullptr) delete[] vec;
			vec = tmp;
		}
		else for (i = 0; i < b.num; i++) vec[i] += b.vec[i];
	}
	return *this;
}
VectorDouble& VectorDouble::operator+=(const double& b)
{
	if (num > 0) {
		for (int i = 0; i < num; i++) vec[i] += b;
	}
	return *this;
}
VectorDouble& VectorDouble::operator+=(const float& b)
{
	if (num > 0) {
		for (int i = 0; i < num; i++) vec[i] += b;
	}
	return *this;
}
VectorDouble VectorDouble::operator+(const VectorDouble& b)
{
	VectorDouble tmp(*this);
	tmp += b;
	return tmp;
}
VectorDouble VectorDouble::operator+(const double& b)
{
	VectorDouble tmp(*this);
	tmp += b;
	return tmp;
}
VectorDouble VectorDouble::operator+(const float& b)
{
	VectorDouble tmp(*this);
	tmp += b;
	return tmp;
}
VectorDouble& VectorDouble::operator*=(const  VectorDouble& b)
{
	if (num != b.num) { std::cout << " Error : vectors of different sizes are used in operation %= \n"; return *this; }
	for (int i = 0; i < num; i++) vec[i] *= b.vec[i];
	return *this;
}
VectorDouble& VectorDouble::operator*=(const double& b) {
	VectorDouble tmp;
	if (b == 0) {
		tmp.state = BAD_DIV;
		cout << "Eror BAD_DIV" << endl;
		return *this;
	}
	for (int i = 0; i < num; i++) vec[i] *= b;
	return *this;
	return tmp;
}
VectorDouble& VectorDouble::operator*=(const float& b) {
	VectorDouble tmp;
	if (b == 0) {
		tmp.state = BAD_DIV;
		cout << "Eror BAD_DIV" << endl;
		return *this;
	}
	for (int i = 0; i < num; i++) vec[i] *= b;
	return *this;
	return tmp;
}
VectorDouble VectorDouble::operator*(const  VectorDouble& b)
{
	if (num != b.num) { std::cout << " Error : vectors of different sizes are used in operation %= \n"; return *this; }
	for (int i = 0; i < num; i++) vec[i] *= b.vec[i];
	return *this;
}
VectorDouble VectorDouble::operator*(const double& b) {
	VectorDouble rez(*this);
	VectorDouble tmp;
	if (b == 0) {
		tmp.state = BAD_DIV;
		cout << "Eror BAD_DIV" << endl;
		return rez;
	}
	rez *= b;
	return rez;
	return tmp;
}
VectorDouble VectorDouble::operator*(const float& b) {
	VectorDouble rez(*this);
	VectorDouble tmp;
	if (b == 0) {
		tmp.state = BAD_DIV;
		cout << "Eror BAD_DIV" << endl;
		return rez;
	}
	rez *= b;
	return rez;
	return tmp;
}
VectorDouble& VectorDouble::operator/=(const  VectorDouble& b)
{
	if (num != b.num) { std::cout << " Error : vectors of different sizes are used in operation %= \n"; return *this; }
	for (int i = 0; i < num; i++) vec[i] /= b.vec[i];
	return *this;
}
VectorDouble& VectorDouble::operator/=(const double& b) {
	VectorDouble tmp;
	if (b == 0) {
		tmp.state = BAD_DIV;
		cout << "Eror BAD_DIV" << endl;
		return *this;
	}
	else for (int i = 0; i < num; i++) vec[i] /= b;
	return *this;
	return tmp;
}
VectorDouble& VectorDouble::operator/=(const float& b) {
	VectorDouble tmp;
	if (b == 0) {
		tmp.state = BAD_DIV;
		cout << "Eror BAD_DIV" << endl;
		return *this;
	}
	else for (int i = 0; i < num; i++) vec[i] /= b;
	return *this;
	return tmp;
}


VectorDouble& VectorDouble::operator/(const  VectorDouble& b)
{
	if (num != b.num) { std::cout << " Error : vectors of different sizes are used in operation %= \n"; return *this; }
	for (int i = 0; i < num; i++) vec[i] /= b.vec[i];
	return *this;
}
VectorDouble VectorDouble::operator/(const double& b) {
	VectorDouble rez(*this);
	VectorDouble tmp;
	if (b == 0) {
		tmp.state = BAD_DIV;
		cout << "Eror BAD_DIV" << endl;
		return rez;
	}
	rez /= b;
	return rez;
	return tmp;
}
VectorDouble VectorDouble::operator/(const float& b) {
	VectorDouble rez(*this);
	VectorDouble tmp;
	if (b == 0) {
		tmp.state = BAD_DIV;
		cout << "Eror BAD_DIV" << endl;
		return rez;
	}
	rez /= b;
	return rez;
	return tmp;
}
bool VectorDouble::operator>(const VectorDouble& s) {
	for (int i = 0; i < num; i++) {
		if (vec[i] > s.vec[i])
			return true;
	}
	return false;
}
bool VectorDouble::operator>=(const VectorDouble& s) {
	for (int i = 0; i < num; i++) {
		if (vec[i] >= s.vec[i])
			return true;
	}
	return false;
}
bool VectorDouble::operator<(const VectorDouble& s) {
	for (int i = 0; i < num; i++) {
		if (vec[i] < s.vec[i])
			return true;
	}
	return false;
}
bool VectorDouble::operator<=(const VectorDouble& s) {
	for (int i = 0; i < num; i++) {
		if (vec[i] <= s.vec[i])
			return true;
	}
	return false;
}
//--------------------------------------------------------------------------------------------------------------------------
int main() {
	system("chcp 1251");
	VectorDouble vector1(8);
	VectorDouble vector2(2, 7);
	VectorDouble vector3(2, 11.4);
	VectorDouble vector4(6, 0);
	VectorDouble vectorcopy(vector2);
	float y = 2.5;
	double x = 1.9;
	cout << "Task1:   VectorDouble:" << endl;
	cout << vector1;
	cout << vector2;
	cout << vector3;
	cout << "Операції:" << endl;
	cout << "***Перевантаження ++:" << endl << endl;
	cout << (++vector2) << endl;
	cout << "***Перевантаження vector + vector:" << endl << endl;
	vector2 += vector2;
	cout << vector2 << endl;
	cout << "***Перевантаження vector +double:" << endl << endl;
	vector2 += x;
	cout << vector2 << endl;
	cout << "***Перевантаження vector + float:" << endl << endl;
	vector2 += y;
	cout << vector2 << endl;
	cout << "***Перевантаження --:" << endl << endl;
	cout << (--vector2) << endl;
	cout << "***Перевантаження vector - double:" << endl << endl;
	vector2 -= x;
	cout << vector2 << endl;
	cout << "***Перевантаження vector - float:" << endl << endl;
	vector2 -= y;
	cout << vector2 << endl;
	cout << "***Перевантаження vector - vector:" << endl << endl;
	vector2 -= vector3;
	cout << vector2 << endl;
	cout << "***Перевантаження vector * vector:" << endl << endl;
	vector2 *= vector3;
	cout << vector2 << endl;
	cout << "***Перевантаження vector / vector:" << endl << endl;
	vector2 /= vector3;
	cout << vector2 << endl;
	cout << "***Перевантаження vector * 0:" << endl << endl;
	vector2 *= 1.5;
	cout << vector2 << endl;
	cout << "***Перевантаження vector / 0 :" << endl << endl;
	vector2 /= 2.1;
	cout << vector2 << endl;
	cout << "Вираз:" << endl << endl;
	cout << "vector4= (vector2 * vector3) / y :" << endl << endl;
	vector4 = (vector2 * vector3) / y;
	cout << vector4 << endl;
	//------------------------------------------------------------------------------------------------------------
	if (vectorcopy < vector2)  cout << "Обєкт для коаіювання менший за вектор" << endl << endl;
	else if (vectorcopy > vector2)  cout << "Обєкт для копіювання більший за вектор" << endl << endl;
	else if (vectorcopy <= vector2) cout << "Обєкт для копіювання більший або рівний за вектор" << endl << endl;
	else if (vectorcopy >= vector2) cout << "Обєкт для копіювання більший або рівний за вектор" << endl << endl;
}