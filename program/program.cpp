#include<iostream>
#include<fstream>
#include<conio.h>
#include<cstdlib>
#include<vector>
#include<string>

using namespace std;

void test_pliku(ifstream& plik) {
	if (plik.good())
		cout << "Odczyt pliku wejscia - OK" << endl;
	else
		cout << "Blad odczytu pliku wejscia!" << endl;
	system("pause");
}
void wczytanie(ifstream& plik, vector<string>& dane) {
	string noweslowo;
	while (plik >> noweslowo) {
		bool flaga = 0;
		//for (int q = 0; q < noweslowo.length(); q++) {
		int q = 0;
		while(q < noweslowo.length()){
			if (noweslowo[q] >= 'A' && noweslowo[q] <= 'Z') noweslowo[q] += 'a' - 'A';
			q++;
		}
		for (int i = 0; i < dane.size() && !flaga; i++) {
			if (noweslowo == dane[i])
				flaga = 1;
		}
		if (flaga == 0) {
			for (int q = 0; q < noweslowo.length(); q++) {
				if (noweslowo[q] >= 'A' && noweslowo[q] <= 'Z') noweslowo[q] += 'a' - 'A';
			}
			dane.push_back(noweslowo);
		}
	}
}
void sortujAZq(vector<string>& dane) {
	string temp;
	int j;

	for (int i=1; i < dane.size(); i++) {
		temp = dane[i];
		for (j = i - 1; j >= 0 && dane[j] > temp; j--)
			dane[j + 1] = dane[j];
		dane[j + 1] = temp;
	}
}
void sortujZAq(vector<string>& dane) {
	string temp;
	int j;

	for (int i = 1; i < dane.size(); i++) {
		temp = dane[i];
		for (j = i - 1; j >= 0 && dane[j] < temp; j--)
			dane[j + 1] = dane[j];
		dane[j + 1] = temp;
	}
}
void sortujAZb(vector<string>& dane) {

	int czy_byla_zmiana;

	do {
		czy_byla_zmiana = 0;
		for (int i = 0; i < (dane.size() - 1); i++) {
			if (dane[i] > dane[i + 1]) {
				string j = dane[i];
				dane[i] = dane[i + 1];
				dane[i + 1] = j;
				czy_byla_zmiana = 1;
			}
		}
	} while (czy_byla_zmiana);
}
void sortujZAb(vector<string>& dane) {

	int czy_byla_zmiana;

	do {
		czy_byla_zmiana = 0;
		for (int i = 0; i < (dane.size() - 1); i++) {
			if (dane[i] < dane[i + 1]) {
				string j = dane[i];
				dane[i] = dane[i + 1];
				dane[i + 1] = j;
				czy_byla_zmiana = 1;
			}
		}
	} while (czy_byla_zmiana);
}
void dodaj_slowo(vector<string> & dane) {
	string noweslowo;
	cout << "Podaj slowo ktore chcesz dodac: ";
	cin >> noweslowo;
	bool flaga = 0;
	for (int i = 0; i < dane.size(); i++) {
		if (noweslowo == dane[i])
			flaga = 1;
	}
	if (flaga == 0)
		dane.push_back(noweslowo);
}
void usun_slowo(vector<string> & dane) {
	string slowo_do_usuniecia;
	cout << "Podaj slowo ktore chcesz usunac: ";
	cin >> slowo_do_usuniecia;
	for (int i = 0; i < dane.size(); i++) {
		if (slowo_do_usuniecia == dane[i])
			dane[i].erase();
	}
}
void zapis_do_pliku(ofstream& plik, vector<string>& dane) {

	for (int i = 0; i < dane.size(); i++) {
		plik << dane[i] << endl;
	}
}
void zapis_do_pliku_naj(ofstream & plik, vector<string> & dane) {
	string max = dane[0], min = dane[0];
	for (int i = 1; i < (dane.size() - 1); i++) {
		if (max.length() < dane[i].length()) max = dane[i];
		if (min.length() > dane[i].length()) min = dane[i];
	}

	plik << "Najdluzszy wyraz to: " << max << endl;
	plik << "Najkrotszy wyraz to: " << min << endl;
	cout << endl;
	for (int i = 0; i < dane.size(); i++) {
		plik << dane[i] << endl;
	}
}
int main() {
	ifstream wejscie;
	ofstream wyjscie;
	wejscie.open("dane.txt");
	wyjscie.open("posortowane.txt");
	vector <string> slownik;
	int menu_c = 0;
	int menu_min = 0;
	int menu_max = 10;
	int input;
	while (true) {
		system("cls");
		cout << (menu_c == 0 ? "> " : "  ") << "Test pliku" << endl;
		cout << (menu_c == 1 ? "> " : "  ") << "Wczytaj dane z pliku" << endl;
		cout << (menu_c == 2 ? "> " : "  ") << "Sortuj A-Z babelkowo" << endl;
		cout << (menu_c == 3 ? "> " : "  ") << "Sortuj Z-A babelkowo" << endl;
		cout << (menu_c == 4 ? "> " : "  ") << "Sortuj A-Z insert sort" << endl;
		cout << (menu_c == 5 ? "> " : "  ") << "Sortuj Z-A insert sort" << endl;
		cout << (menu_c == 6 ? "> " : "  ") << "Dodaj wyraz" << endl;
		cout << (menu_c == 7 ? "> " : "  ") << "Usun wyraz" << endl;
		cout << (menu_c == 8 ? "> " : "  ") << "Zapisz do pliku" << endl;
		cout << (menu_c == 9 ? "> " : "  ") << "Zapisz do pliku z podaniem najdluzszego i najkrotrzego wyrazu" << endl;
		cout << (menu_c == 10 ? "> " : "  ") << "Zamknij program" << endl;
		input = _getch();
		if (input == 224)
			switch (_getch()) {
			case 80: if (menu_c < menu_max) menu_c++; break;
			case 72: if (menu_c > menu_min) menu_c--; break;
			}
		if (input == 13)
			switch (menu_c) {
			case 0: test_pliku(wejscie); break;
			case 1: wczytanie(wejscie, slownik); break;
			case 2: sortujAZb(slownik); break;
			case 3: sortujZAb(slownik); break;
			case 4: sortujAZq(slownik); break;
			case 5: sortujZAq(slownik); break;
			case 6: dodaj_slowo(slownik); break;
			case 7: usun_slowo(slownik); break;
			case 8: zapis_do_pliku(wyjscie, slownik); break;
			case 9: zapis_do_pliku_naj(wyjscie, slownik); break;
			case 10: exit(0);
			}
	}
	wejscie.close();
	wyjscie.close();
	return 0;
}
