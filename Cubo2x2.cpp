// Projeto T1 - Cubo 2x2



#include <iostream>

// ---Interface---
void faceU (){
	printf("\t\t\t\t\t\t\t _________ _________\n\t\t\t\t\t\t\t|         |         |\n\t\t\t\t\t\t\t|         |         |\n\t\t\t\t\t\t\t|         |         |\n\t\t\t\t\t\t\t|_________|_________|\n\t\t\t\t\t\t\t|         |         |\n\t\t\t\t\t\t\t|         |         |\n\t\t\t\t\t\t\t|         |         |\n\t\t\t\t\t\t\t|_________|_________|\n\n\t\t\t\t\t\t           |     |\n\t\t\t\t\t\t           |     |\n\t\t\t\t\t\t           |     |\n\t\t\t\t\t\t           |_____|\n\n");
}

void faceLRFB (){
	printf("\t _________ _________     _________ _________     _________ _________     _________ _________\n\t|         |         |   |         |         |   |         |         |   |         |         |\n\t|         |         |   |         |         |   |         |         |   |         |         |\n\t|         |         |   |         |         |   |         |         |   |         |         |\n\t|_________|_________|   |_________|_________|   |_________|_________|   |_________|_________|\n\t|         |         |   |         |         |   |         |         |   |         |         |\n\t|         |         |   |         |         |   |         |         |   |         |         |\n\t|         |         |   |         |         |   |         |         |   |         |         |\n\t|_________|_________|   |_________|_________|   |_________|_________|   |_________|_________|\n\n\t        |                       _____                   _____                   _____\n\t        |                       |___                    |___/                   |___/\n\t        |                       |                       |\\                      |   \\\n\t        |_____                  |                       | \\                     |___|\n\n");
}

void faceD (){
	printf("\t\t\t\t\t\t\t _________ _________\n\t\t\t\t\t\t\t|         |         |\n\t\t\t\t\t\t\t|         |         |\n\t\t\t\t\t\t\t|         |         |\n\t\t\t\t\t\t\t|_________|_________|\n\t\t\t\t\t\t\t|         |         |\n\t\t\t\t\t\t\t|         |         |\n\t\t\t\t\t\t\t|         |         |\n\t\t\t\t\t\t\t|_________|_________|\n\n\t\t\t\t\t\t           ______\n\t\t\t\t\t\t           |     |\n\t\t\t\t\t\t           |     |\n\t\t\t\t\t\t           |_____/\n\n");
}

void cubeInterface (){
	faceU();
	faceLRFB();
	faceD();
}

using namespace std;
int main(int argc, char *argv[]) {
	cubeInterface();
}