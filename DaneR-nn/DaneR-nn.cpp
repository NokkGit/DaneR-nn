#include <iostream>
#include "funkcje.h"
using namespace std;

int main() {
	vector <kl> planLekcji;
	vector <classes> klasa;
	vector <teachers> nauczyciele;
	takeDataFromTXT(planLekcji,klasa,nauczyciele);

	insertionSortByHours(planLekcji);

	bubbleSortByClassNum(klasa);

	quickSortByFavClass(nauczyciele, 0, nauczyciele.size() - 1);

	displaySubjects(planLekcji);
	displayClassrooms(klasa);
	displayTeachers(nauczyciele);
}

//Wypisywanie danych z pliku classes.txt
//
//Klasa : 2t
//Grupa : Ga1
//Nauczyciel : Marek Bekier
//Przedmiot : Pracownia programowania
//Ilość godzin : 2
//
//Grupa : Ga2
//Nauczyciel : Wojciech Mierzwa
//Przedmiot : Sieci komputerowe
//Ilość godzin : 3
//
//Grupa : Gda
//Nauczyciel : Lidia Flis
//Przedmiot : Religia
//Ilość godzin : 1
//
//-------------------------------------- -
//
//Wypisywanie danych z pliku classrooms.txt
//
//Przedmiot : J.polski
//Numer sali : 23
//Ilość miejsc : 32
//Imie i nazwisko nauczyciela : Marek Olszewski
//
//Przedmiot : Informatyka
//Numer sali : 14.1
//Ilość miejsc : 17
//Imie i nazwisko nauczyciela : Marek Bekier
//
//Przedmiot : Religia
//Numer sali : 2
//Ilość miejsc : 32
//Imie i nazwisko nauczyciela : Lidia Flis
//
//-------------------------------------- -
//
//Wypisywanie danych z pliku teachers.txt
//
//Imie i nazwisko : Marek Bekier
//Przedmioty : Informatyka, Sieci
//Preferowana sala : 14.1
//
//Imie i nazwisko : Lidia Flis
//Przedmioty : Religia
//Preferowana sala : 2
//
//Imie i nazwisko : Małgorzata Traczyk
//Przedmioty : Wiedza o kulturze
//Preferowana sala : 0
//
//-------------------------------------- -
