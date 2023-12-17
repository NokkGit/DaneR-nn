#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class kl {
public:
	string klasa;
	string group;
	string subject;
	string teacher;
	int hForWeek;

	kl(string klasa, string group, string subject, string teacher, int hForWeek) : klasa(klasa), group(group), subject(subject), teacher(teacher), hForWeek(hForWeek) {};
};

class classes {
public:
	string className;
	float classNum;
	int classSize;
	string supervisor;

	classes(string className, float classNum, int classSize, string supervisor) : className(className), classNum(classNum), classSize(classSize), supervisor(supervisor) {};
};

class teachers {
public:
	string name;
	vector <string> teachedSubjects;
	float favClass;

	teachers(string name, const vector <string>& teachedSubjects, float favClass) : name(name), teachedSubjects(teachedSubjects), favClass(favClass) {};
};


void takeDataFromTXT(
	vector <kl>& planLekcji,
	vector <classes>& klasy,
	vector <teachers>& nauczyciele
) {
	setlocale(LC_ALL, "pl_PL.UTF-8"); //�eby da�o si� odczyta� polskie znaki z pliku (NIE KONSOLA)

	fstream teacher;
	fstream classrooms;
	fstream classe;

	string wiersz;
	bool skip = false;
	string nazwaKlasy;



	//Odczytywanie danych z pliku classes.txt
	classe.open("classes.txt", std::ios::in);
	if (classe.is_open()) {
		while (getline(classe, wiersz)) {
			if (skip) {
				skip = false;
				continue;
			}
			if (wiersz.find("Klasa") == 0) {
				nazwaKlasy = wiersz.substr(6); //Pomija s�owo Klasa
				skip = true;
				continue;
			}
			size_t pozycja = wiersz.find(';');
			string group, teacher;
			string subject;
			int hForWeek = 0;

			if (pozycja != string::npos) {
				group = wiersz.substr(0, pozycja);
				wiersz = wiersz.substr(pozycja + 1);
				pozycja = wiersz.find(';');

				if (pozycja != string::npos) {
					subject = wiersz.substr(0, pozycja);
					wiersz = wiersz.substr(pozycja + 1);
					pozycja = wiersz.find(';');

					if (pozycja != string::npos) {
						teacher = wiersz.substr(0, pozycja);
						hForWeek = stoi(wiersz.substr(pozycja + 1));
						//cout << nazwaKlasy;
						kl nowyPrzedmiot(nazwaKlasy, group, subject, teacher, hForWeek);
						planLekcji.push_back(nowyPrzedmiot);
					}
				}
			}
		}
	}
	classe.close();

	//Odczytywanie danych z pliku classrooms.txt
	classrooms.open("classrooms.txt", std::ios::in);
	if (classrooms.is_open()) {
		while (getline(classrooms, wiersz)) {
			size_t pozycja = wiersz.find(';');
			string className, supervisor;
			float classNum;
			int classSize = 0;

			if (pozycja != string::npos) {
				className = wiersz.substr(0, pozycja);
				wiersz = wiersz.substr(pozycja + 1);
				pozycja = wiersz.find(';');

				if (pozycja != string::npos) {
					classNum = stof(wiersz.substr(0, pozycja));
					wiersz = wiersz.substr(pozycja + 1);
					pozycja = wiersz.find(';');

					if (pozycja != string::npos) {
						classSize = stoi(wiersz.substr(0, pozycja));
						supervisor = wiersz.substr(pozycja + 1);
						classes nowaSala(className, classNum, classSize, supervisor);
						klasy.push_back(nowaSala);
					}
				}
			}
		}
	}
	classrooms.close();

	//Odczytywanie danych z pliku teachers.txt
	teacher.open("teachers.txt", std::ios::in);
	if (teacher.is_open()) {
		while (getline(teacher, wiersz)) {

			//Zmienne
			string name;
			float favClass;
			vector <string> teachedSubjects;
			size_t pozycja = wiersz.find(';');

			//Podzia� linii na cz�ci
			if (pozycja != string::npos) { //tak jakby przechodzi po tek�cie dop�ki nie znajdzie tego ";"
				name = wiersz.substr(0, pozycja);
				wiersz = wiersz.substr(pozycja + 1); //kolejna pozycja to b�dzie druga pozycja (po znaku ';')

				pozycja = wiersz.find(';');
				if (pozycja != string::npos) {
					string przedmioty = wiersz.substr(0, pozycja);

					istringstream ss(przedmioty);
					string przedmiot;
					while (getline(ss, przedmiot, ',')) {
						teachedSubjects.push_back(przedmiot);
					}
					if (pozycja != string::npos) {
						favClass = stof(wiersz.substr(pozycja + 1));
						wiersz = wiersz.substr(pozycja + 1);
						pozycja = wiersz.find(';');
					}

					teachers nowyNauczyciel(name, teachedSubjects, favClass);
					nauczyciele.push_back(nowyNauczyciel);
				}
			}
		}
	}
	teacher.close();
}

void displaySubjects(const vector<kl>& planLekcji) {
	cout << "Wypisywanie danych z pliku classes.txt" << endl << endl;
	string currentClass = "";
	for (const auto& przedmiot : planLekcji) {
		setlocale(LC_ALL, "pl_PL.UTF-8");
		if (przedmiot.klasa != currentClass) {
			cout << "Klasa: " << przedmiot.klasa << endl;
			currentClass = przedmiot.klasa;
		}
		cout << "Grupa: " << przedmiot.group << endl;
		cout << "Nauczyciel: " << przedmiot.teacher << endl;
		cout << "Przedmiot: " << przedmiot.subject << endl;
		setlocale(LC_CTYPE, "polish");
		cout << "Ilo�� godzin: " << przedmiot.hForWeek << endl;
		cout << endl;
	}
	cout << "---------------------------------------" << endl << endl;;
}

void displayClassrooms(const vector<classes>& sala) {
	cout << "Wypisywanie danych z pliku classrooms.txt" << endl << endl;
	for (const auto& lekcjaSala : sala) {
		setlocale(LC_ALL, "pl_PL.UTF-8");
		cout << "Przedmiot: " << lekcjaSala.className << endl;
		cout << "Numer sali: " << lekcjaSala.classNum << endl;
		setlocale(LC_CTYPE, "Polish");
		cout << "Ilo�� miejsc: " << lekcjaSala.classSize << endl;
		setlocale(LC_ALL, "pl_PL.UTF-8");
		cout << "Imie i nazwisko nauczyciela: " << lekcjaSala.supervisor << endl;
		cout << endl;
	}
	cout << "---------------------------------------" << endl << endl;
}

void displayTeachers(const vector<teachers>& nauczyciel) {
	cout << "Wypisywanie danych z pliku teachers.txt" << endl << endl;
	for (const auto& teacher : nauczyciel) {
		setlocale(LC_ALL, "pl_PL.UTF-8");
		cout << "Imie i nazwisko: " << teacher.name << endl;
		cout << "Przedmioty: ";
		for (size_t i = 0; i < teacher.teachedSubjects.size(); ++i) {
			if (i != teacher.teachedSubjects.size() - 1) {
				cout << teacher.teachedSubjects[i] << ", ";
			}
			else {
				cout << teacher.teachedSubjects[i] << endl;
			}
		}
		cout << "Preferowana sala: " << teacher.favClass << endl;
		cout << endl;
	}
	cout << "---------------------------------------" << endl << endl;
}

// Sortowanie przez wstawianie wed�ug liczby godzin 'hForWeek'
void insertionSortByHours(vector<kl>& planLekcji) {
	int n = planLekcji.size();  // Zapisujemy ilo�� element�w w li�cie
	for (int i = 1; i < n; i++) {
		kl key = planLekcji[i];  // Wybieramy element do por�wnania
		int j = i - 1;

		// Przesuwamy elementy wi�ksze ni� 'key' w g�r� listy
		while (j >= 0 && planLekcji[j].hForWeek > key.hForWeek) {
			planLekcji[j + 1] = planLekcji[j];
			j = j - 1;
		}
		planLekcji[j + 1] = key;  // Wstawiamy 'key' na odpowiednie miejsce
	}
}

// Sortowanie b�belkowe wed�ug 'classNum' (numer klasy)
void bubbleSortByClassNum(vector<classes>& klasy) {
	int n = klasy.size();

	// Sprawdzanie element�w i zamiana miejscami, je�li poprzedni jest wi�kszy ni� nast�pny
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (klasy[j].classNum > klasy[j + 1].classNum) {
				swap(klasy[j], klasy[j + 1]);
			}
		}
	}
}

// Funkcja pomocnicza do algorytmu Quick Sort, dzieli list� na dwie cz�ci
int partitionTeachers(vector<teachers>& arr, int low, int high) {
	float pivot = arr[high].favClass;  // Wybieramy pivot jako ostatni element
	int i = (low - 1);

	// Por�wnujemy elementy z pivotem i zamieniamy je miejscami
	for (int j = low; j <= high - 1; j++) {
		if (arr[j].favClass < pivot) {
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);  // Zamieniamy pivot z elementem na prawo od mniejszego
	return (i + 1);
}

// Algorytm Quick Sort do sortowania wed�ug preferowanej klasy 'favClass'
void quickSortByFavClass(vector<teachers>& arr, int low, int high) {
	if (low < high) {
		// Wybieramy pivot, dzielimy list� i rekurencyjnie sortujemy obie cz�ci
		int pi = partitionTeachers(arr, low, high);
		quickSortByFavClass(arr, low, pi - 1);
		quickSortByFavClass(arr, pi + 1, high);
	}
}