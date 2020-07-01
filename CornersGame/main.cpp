#include <iostream>
#include "CornersManager.h"

int main() {
	//setlocale(LC_ALL, "Russian");
	CornersManager manager;
	if (!manager.Start()) {
		std::cout << "Wrong init";
		system("pause");
		return 0;
	}
	while (!manager.isGameFinished()) {
		manager.MakeMove();
	}

	system("pause");
	return 0;
}