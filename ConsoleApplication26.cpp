#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <conio.h>
#include <iomanip>

using namespace std;

int writeNumbers();
int chooseMenu();
int chooseUr(string*, int);

template <typename T> 
class Urav {
private:
	T a, b, c;
	T disk;
	T x1;
	T x2;
public:
	Urav() {
		a = b = c = x1 = x2 = disk = 0;
	}
	Urav(T a1, T b1, T c1) {
		a = a1;
		b = b1;
		c = c1;
		disk = b * b - 4 * a * c;
		x1 = (-b + sqrt(disk)) / (2 * a);
		x2 = (-b - sqrt(disk)) / (2 * a);
	}
	void show() {
		disk = b * b - 4 * a * c;
		x1 = (-b + sqrt(disk)) / (2 * a);
		x2 = (-b - sqrt(disk)) / (2 * a);
		cout << a << "x^2";
		if (b < 0) cout << b << "x";
		else cout << "+" << b << "x";
		if (c < 0) cout << c;
		else cout << "+" << c;
		cout << endl;
		cout << "D = b^2-4ac" << endl;
		T rav = 4 * a * c;
		if (rav < 0) cout << "D = " << b * b << "+" << -rav;
		else cout << "D = " << b * b << "-" << rav;
		cout << " = " << disk << endl;
		cout << "x1,2 = (-b + sqrt(D))/2a" << endl;
		cout << "x1 = " << x1 << endl;
		cout << "x2 = " << x2 << endl;
	}
	Urav<T>& operator*=(int abc) {
		a *= abc;
		b *= abc;
		c *= abc;
		return* this;
	}
	Urav<T>& operator-(Urav<T>& ur) {
		a = a - ur.a;
		b = b - ur.b;
		c = c - ur.c;
		return*this;
	}
	string getUrav() {
		string s;
		s = to_string(a) + "x^2";
		if (b < 0) s = s + to_string(b) + "x";
		else s = s + "+" + to_string(b) + "x";
		if (c < 0) s = s + to_string(c);
		else s = s + "+" + to_string(c);
		return s;
	}
	friend void operator>><T>(istream&, Urav<T>&);
};


template <typename T> void operator>>(istream& in, Urav<T>& ur) {
	cout << "Введите коэффицент a: ";
	ur.a = writeNumbers();
	system("cls");
	cout << "Введите коэффицент b: ";
	ur.b = writeNumbers();
	system("cls");
	cout << "Введите коэффицент c: ";
	ur.c = writeNumbers();
	system("cls");
}


int main() {
	setlocale(0, "rus");
	int nUr = 0;
	Urav<double>* ur = new Urav<double>[1];
	while (true) {
		int choose = chooseMenu();
		if (choose == 0) {
			nUr++;
			Urav<double>* ptr = new Urav<double>[nUr];
			for (int i = 0; i < nUr - 1; i++)
				ptr[i] = ur[i];
			ur = ptr;
			ptr = NULL;
			delete[]ptr;
			cin >> ur[nUr - 1];
		}else
			if (choose == 1) {
				for (int i = 0; i < nUr; i++) {
					ur[i].show();
					cout << endl;
				}
				system("pause");
				system("cls");
			}else
				if (choose == 2) {
					string* aa = new string[nUr];
					for (int i = 0; i < nUr; i++)
						aa[i] = ur[i].getUrav();
					int choose1 = chooseUr(aa, nUr);
					delete[]aa;
					if (choose1 == nUr) break;
					cout << "Введите число на которое умножить коэффиценты: ";
					int a = writeNumbers();
					ur[choose1] *= a;
				}else
					if (choose == 3) {
						string* aa = new string[nUr];
						for (int i = 0; i < nUr; i++)
							aa[i] = ur[i].getUrav();
						int choose1 = chooseUr(aa, nUr);
						if (choose1 == nUr) break;
						int choose2 = chooseUr(aa, nUr);
						if (choose2 == nUr) break;
						ur[choose1] = ur[choose1] - ur[choose2];
						delete[]aa;
						cout << "Вычетание прошло успешно!" << endl;
						system("pause");
						system("cls");
					}
					else
						break;
	}
}

int chooseMenu() {
	int choose_menu = 0, key = 0;
	system("cls");
	while (true){
		choose_menu = (choose_menu + 5) % 5;

		if (choose_menu == 0) cout << "-> Добавить уравнение" << endl;
		else cout << " Добавить уравнение" << endl;

		if (choose_menu == 1) cout << "-> Посмотреть уравнения и решить" << endl;
		else cout << " Посмотреть уравнения и решить" << endl;

		if (choose_menu == 2) cout << " -> Умножить коэфиценты на число" << endl;
		else cout << " Умножить коэфиценты на число" << endl;

		if (choose_menu == 3) cout << " -> Вычесть коэфиценты одного уравнение от другого" << endl;
		else cout << " Вычесть коэфиценты одного уравнение от другого" << endl;

		if (choose_menu == 4) cout << " -> Выход" << endl;
		else cout << " Выход" << endl;

		key = _getch();
		if (key == 224){
			key = _getch();
			if (key == 72) choose_menu--;
			if (key == 80) choose_menu++;
		}
		if (key == 13) {
			system("cls");
			return choose_menu;
		}
		system("cls");
	}
}

int writeNumbers() {
	string numbers;
	while (true) {
		int key;
		key = _getch();
		if (key == 224) {
			key = _getch();
		}
		else
			if (key == 8) {
				if (numbers.length() != 0) {
					cout << '\b' << " " << '\b';
					numbers.erase(numbers.length() - 1);
				}
			}
			else
				if (key == 13 && numbers.length() != 0 && numbers != "-") break;
				else
					if ((key >= '0' && key <= '9') || (key == '-' && numbers.length() == 0)) {
						numbers = numbers + (char)key;
						cout << (char)key;
					}
	}
	cout << endl;
	return stoi(numbers);
}

int chooseUr(string* a, int nUr) {
	int choose_menu = 0, keyboard_button = 0;
	while (true) {
		cout << "Стрелочками ВВЕРХ и ВНИЗ выберите пункт меню" << endl;
		choose_menu = (choose_menu + (nUr + 1)) % (nUr + 1);

		for (int i = 0; i < nUr; i++)
			if (i == choose_menu) { cout << " -> " << i + 1 << " - " << a[i] << endl; }
			else { cout << " " << i + 1 << " - " << a[i] << endl; }

		if (choose_menu == nUr) { cout << " -> Выйти с выбора" << endl; }
		else cout << " Выйти с выбора" << endl;

		keyboard_button = _getch();
		if (keyboard_button == 224) {
			keyboard_button = _getch();
			if (keyboard_button == 72) choose_menu--;
			if (keyboard_button == 80) choose_menu++;
		}
		if (keyboard_button == 13) { system("cls"); return choose_menu; }
		system("cls");
	}
}
