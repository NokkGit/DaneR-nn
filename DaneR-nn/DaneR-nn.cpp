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