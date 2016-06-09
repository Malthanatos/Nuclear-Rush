#include <iostream>
#include <Windows.h>
#include <string.h>

using namespace std;

void p1(){
	SetConsoleTitle("Puzzle 1");
	//ICS
	cout << "01001001 01000011 01010011 has a brother. This brother has a secret.\nThis secret is guarded by a password which does not involve the number 170.\nIf it did then the password would be 81322, but it does not, so it is not.\nAnyways what you want is most assuredly not the name of the farthest\ncomputer from every other." << endl;
	cin.get();
	cout << "This challenge was definitely NOT written to say exactly the opposite\nof what it says" << endl;
	cin.get();
	cout << "Actually, maybe it is..." << endl;
	//Answer: outland
	return;
}

void p2(){
	SetConsoleTitle("Puzzle 2");
	//What year did Peter learn how to type?
	cout << "01010111 01101000 01100001 01110100 00100000 01111001 01100101 01100001\n01110010 00100000 01100100 01101001 01100100 00100000 01010000 01100101\n01110100 01100101 01110010 00100000 01101100 01100101 01100001 01110010\n01101110 00100000 01101000 01101111 01110111 00100000 01110100 01101111\n00100000 01110100 01111001 01110000 01100101 00111111\n" << endl;
	cin.get();
	//Peter the Anteater
	cout << "01010000 01100101 01110100 01100101 01110010 00100000 01110100 01101000\n01100101 00100000 01000001 01101110 01110100 01100101 01100001 01110100\n01100101 01110010\n" << endl;
	cin.get();
	//Laptop
	cout << "01001100 01100001 01110000 01110100 01101111 01110000\n" << endl;
	cin.get();
	//Student Center
	cout << "01010011 01110100 01110101 01100100 01100101 01101110 01110100 00100000\n01000011 01100101 01101110 01110100 01100101 01110010\n" << endl;
	//Answer: 2003
	return;
}

//This is hideous, don't look at it...
char map[16][80] = {
"\t     \t\t    ??? \n","\n","\n","\n",
"\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n",
"\t\xDB     \xDB    \xDB\xDB    \xDB          \xDB\n",
"\t\xDB    \xDB     \xDB\xDB    \xDB\t    \xDB\n",
"\t\xDB   \xDB      \xDB\xDB    \xDB\t    \xDB\n",
"\t\xDB\xDB\xDB\xDB       \xDB\xDB    \xDB\t    \xDB\n",
"\t\t\t\xDB \xDB\t    \xDB\n",
"\t\t       \xDB   \xDB\t    \xDB\n",
"\t\t\t\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n","\n","\n","\n",
"\t\t\t\n"};

int color_draw(char *line, int y, int len, int color, bool finish_line){
	//I love this function!
	//color the line's characters and background according to "color"
	//  for "len" characters starting from position "y", (finish the line, or don't)
	//  and return the position of the next character to be printed
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int j;
	for (j = 0; j < y; j++){
		cout << line[j];
	}
	SetConsoleTextAttribute(h, color);
	for (j = y; j < y + len; j++){
		cout << line[j];
	}
	SetConsoleTextAttribute(h, 0x0F);
	if (finish_line){
		for (j = y + len; j < strlen(line); j++){
			cout << line[j];
		}
	}
	return ++j;
}

void print_map(){
	int i;
	cout << "\n\n";
	for (i = 0; i < 16; i++){
		if (i > 3 && i < 9){
			color_draw(map[i], 12, 2, 0x02, true);
		}
		else if (i == 9){
			color_draw(map[i], 3, 1, 0x06, true);
		}
		else if (i == 10){
			color_draw(map[i], 9, 1, 0x04, true);
		}
		else if (i == 11){
			color_draw(map[i], 3, 2, 0x01, true);
		}
		else{
			cout << map[i];
		}
	}
	cout << "\n\n";
	return;
}

void add_curve(){
	char block[80];
	//map[13]
	for (int i = 0; i < 26; i++){
		if (i >= 14 && i <= 25){
			block[i] = '\xDB';
		}
		else{
			block[i] = ' ';
		}
	}
	block[26] = '\n';
	strcpy(map[13], block);
	//map[14]
	for (int i = 0; i < 34; i++){
		if ((i >= 6 && i <= 15) || (i >= 25 && i <= 33)){
			block[i] = '\xDB';
		}
		else{
			block[i] = ' ';
		}
	}
	block[17] = 'R';
	block[18] = 'i';
	block[19] = 'n';
	block[20] = 'g';
	block[22] = 'R';
	block[23] = 'd';
	block[34] = '\n';
	strcpy(map[14], block);
	//map[15]
	for (int i = 0; i < 42; i++){
		if ((i >= 0 && i <= 7) || (i >= 33 && i <= 41)){
			block[i] = '\xDB';
		}
		else{
			block[i] = ' ';
		}
	}
	block[42] = '\n';
	strcpy(map[15], block);
	return;
}

void p3(){
	SetConsoleTitle("Puzzle 3");
	cout << "What 3 alphanumeric characters replace these 3 question marks:" << endl;
	print_map();
	cin.get();
	
	//*Adds a curvature and a pair of boxes representing the outer ring and the trees/benches respectively*
	add_curve();
	cout << "This one is hard but the more hints you ask for the easier it is..." << endl;
	print_map();
	cin.get();
	
	//*Adds North and South labels*
	map[0][1] = 'S';
	map[0][2] = 'o';
	map[0][3] = 'u';
	map[0][4] = 't';
	map[0][5] = 'h';
	map[15][20] = 'N';
	map[15][21] = 'o';
	map[15][22] = 'r';
	map[15][23] = 't';
	map[15][24] = 'h';
	cout <<  "Honestly after this one you are basically cheating..." << endl;
	print_map();
	cin.get();
	
	//The Buildings are given labels (PSLH and CRH)*
	map[5][2] = 'P';
	map[5][3] = 'S';
	map[5][4] = 'L';
	map[5][5] = 'H';
	map[5][19] = 'C';
	map[5][20] = 'R';
	map[5][21] = 'H';
	cout << "Really?" << endl;
	print_map();
	cin.get();
	cout << "Kinda sad by now, but fine.\nGo where the question marks are and look up about 25 feet" << endl;
	//Answer: 12a
	return;
}

void p4(){
	SetConsoleTitle("Puzzle 4");
	cout << "The password to the fourth cooling rod is broken up into three riddles.\nSolve these riddles to obtain the password. You may need a UCI map.\nPress enter to show the next hint/riddle." << endl;
	cin.get();
	cout << "Problem 1: Of blue and red, and the shape of the anteater head. How many of the shapes, are of the color red. This is the first digit of your password." << endl;
	cin.get();
	cout << "Hint: It is an abstract artwork located somewhere on UCI campus" << endl;
	//Answer: 2
	cin.get();
	cout << "Problem 2: Somewhere on the UCI campus, there is a Lab without windows.\nLocate this building and look up the building number on the UCI map.\nThe last digit will be the second digit of your password." << endl;
	cin.get();
	cout << "Hint: The building's name start with S. It is located in the opposite side of\nthe first riddle" << endl;
	//Answer: 2
	cin.get();
	cout << "Problem 3: Somewhere on the UCI Campus, there is a Ring. In the middle of the\nring there is a rocky hill. At the bottom of the hill, you will see a plaque\nwith its namesakes name. What year was he born in? The last digit is the last\ndigit of your password." << endl;
	cin.get();
	cout << "Hint: Aldrich Park" << endl;
	//Answer: 8
	//Answer: 228
	return;
}

void p5(){
	SetConsoleTitle("Puzzle 5");
	cout << "What is the building code and room number of the UCI Nuclear Reactor?\n(ex answer: eh 1100, ics 364a, rh b54a etc.)" << endl;
	cin.get();
	cout << "No hints" << endl;
	//Answer: rh b62a
	return;
}

int main(int argc, char *argv[]){
	//FreeConsole();
	//AllocConsole();
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 0x0F);
	int id = 0;
	if (argc > 1){
		id = atoi(argv[1]);
	}
	if (id == 51647){
		p1();
	}
	else if (id == 36548){
		p2();
	}
	else if (id == 84614){
		p3();
	}
	else if (id == 46153){
		p4();
	}
	else if (id == 79189){
		p5();
	}
	else{
		cout << "No cheating!\nIf you are even reading this you should feel\nbad cause you are cheating even more!" << endl;
		cout << id << endl;
		cin.get();
		return 0;
	}
	while(true){
		cin.get();
	}
	return 0;
}
