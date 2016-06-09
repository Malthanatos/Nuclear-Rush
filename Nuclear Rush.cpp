#include <iostream>
#include <windows.h> //Sleep, console
#include <string>
#include <ctime>
#include <stdlib.h>
#include <iomanip>

using namespace std;

bool rod[5] = {false,false,false,false,false};
string solutions[5] = {"outland","2003","12a","228","rh b62a"};
int end_time = 0;
int rod_pos[5] = {4,7,10,13,16};
int rod_time[5] = {1800,3600,7200,10800,14400};
int rod_time_left[5] = {0,0,0,0,0};
//line number, char pos
char core[12][80] = {
"\t\xDB  \xDB  \xDB  \xDB  \xDB  \xDB  \xDB\n",
"\t\xDB~~\xDB~~\xDB~~\xDB~~\xDB~~\xDB~~\xDB\n",
"\t\xDB~~\xDB~~\xDB~~\xDB~~\xDB~~\xDB~~\xDB\n",
"\t\xDB~~\xDB~~\xDB~~\xDB~~\xDB~~\xDB~~\xDB\n",
"\t\xDB~~~~~~~~~~~~~~~~~\xDB\n",
"\t\xDB~~~~~~~~~~~~~~~~~\xDB\n",
"\t\xDB~~~~~~~~~~~~~~~~~\xDB\n",
"\t\xDB~~~~~~~~~~~~~~~~~\xDB\n",
"\t\xDB~~~~~~~~~~~~~~~~~\xDB\n",
"\t\xDB~~~~~~~~~~~~~~~~~\xDB\n",
"\t\xDB~~~~~~~~~~~~~~~~~\xDB\n",
"\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n",
};

void update_rod(int x, bool y){
	rod[x] = y;
	rod_time_left[x] = rod_time[x] + time(0);
	if (y){
		for (int i = 3; i < 12; i++){
			core[i][3 * x + 4] = '\xDB';
		}
	}
}

void rod_status(){
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int r = 0; r < 5; r++){
		SetConsoleTextAttribute(h, 0x0F);
		cout << "Cooling Rod #" << r + 1 << ": ";
		if (rod[r]){
			SetConsoleTextAttribute(h, 0x0A);
			cout << "Enabled " << endl;
		}
		else{
			SetConsoleTextAttribute(h, 0x0C);
			cout << "Disabled" << endl;
		}
	}
	SetConsoleTextAttribute(h, 0x0F); //reset color
}

void reactor(){
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 0x08);
	//draw space: 80 * 20 or 79 * 19
	cout << "\n\n";
	for (int i = 0; i < 12; i++){
		if (i > 0 && i < 11){
			cout << core[i][0] << core[i][1];
			SetConsoleTextAttribute(h, 0x3B);
			for (int j = 2; j < 19; j++){
				cout << core[i][j];
			}
			SetConsoleTextAttribute(h, 0x08);
			cout << core[i][19] <<core[i][20];
		}
		else{
			cout << core[i];
		}
	}
	SetConsoleTextAttribute(h, 0x0F); //reset color
	cout << "\n\n";
}

int char_random(){
	int y = rand() % 255 + 0;
	// null, bell, backspace, tab, new line, carriage return
	// by alt code these would be:
	// null, dot, dot with outline, hollow circle, filled circle, single note
	// other function characters use alt codes correctly
	while (y == 0 || y == 7 || y == 8 || y == 9 || y == 10 || y == 13){
		y = rand() % 255 + 0;
	}
	return y;
}

void crash(HANDLE h, CONSOLE_SCREEN_BUFFER_INFO bufferInfo){
	SetConsoleCursorPosition(h, bufferInfo.dwCursorPosition);
	int x,y;
	for (int i = 0; i < 10000; i++){
		x = rand() % 255 + 0;
		y = char_random();
		SetConsoleTextAttribute(h, x);
		cout << (char)y;
	}
	return;
}

int remaining_time(int x){
	++end_time;
	int secs_left, hours, minutes, seconds;
	secs_left = rod_time_left[x] - (int)time(0);
	hours = secs_left / 3600;
	minutes = (secs_left % 3600) / 60;
	seconds = secs_left % 60;
	cout << "Time to core breach: " << setw(2) << setfill('0') << hours;
	cout << ":" << setw(2) << setfill('0') << minutes;
	cout << ":" << setw(2) << setfill('0') << seconds << "        ";
	return secs_left * 1000;
}

int open_puzzle(int id){
	char exe[19] = "./Puzzles.exe ";
	char code[6] = "00000";
	if (id == 0){
		strcpy(code, "51647");
	}
	else if (id == 1){
		strcpy(code, "36548");
	}
	else if (id == 2){
		strcpy(code, "84614");
	}
	else if (id == 3){
		strcpy(code, "46153");
	}
	else if (id == 4){
		strcpy(code, "79189");
	}
	strcat(exe, code);
	//cout << exe << endl;
	
	STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    // Start the child process
    if(!CreateProcess(
	    NULL,	// No module name (use command line)
        exe,	// Command line
        NULL,	// Process handle not inheritable
        NULL,	// Thread handle not inheritable
        FALSE,	// Set handle inheritance to FALSE
        CREATE_NEW_CONSOLE, //process creation flags, see: https://msdn.microsoft.com/en-us/library/windows/desktop/ms684863(v=vs.85).aspx
        NULL,	// Use parent's environment block
        NULL,	// Use parent's starting directory 
        &si,	// Pointer to STARTUPINFO structure
        &pi)	// Pointer to PROCESS_INFORMATION structure
    )
    {
        printf("CreateProcess failed (Error code: %d).\n", GetLastError());
		printf("Well that was not supposed to happen...\nMake sure that Puzzles.exe is in the same folder as this (Nuclear Rush.exe) is.\nIf it is and this still happened then write down the error code at the top\nand contact the developer immediatly.");
        return -1;
    }
    //user will close the process on their own
    
    // Wait until child process exits.
    //WaitForSingleObject(pi.hProcess, INFINITE );
    // Close process and thread handles. 
    //CloseHandle(pi.hProcess);
    //CloseHandle(pi.hThread);
    return 0;
}

int main(){
	//HWND console = GetConsoleWindow();
	//RECT r;
	//GetWindowRect(console, &r); //get current dims and pos
	// pos, new dims, redraw
	//MoveWindow(console, r.left, r.top, 800, 300, true);
	SetConsoleTitle("Reactor");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE h1 = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE puzzle = NULL;
	//DWORD mode = 0;
	//GetConsoleMode(h1, &mode);
	//SetConsoleMode(h1, mode & (~ENABLE_ECHO_INPUT));
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	SetConsoleTextAttribute(h, 0x0F);
	GetConsoleScreenBufferInfo(h, &bufferInfo);
	//for getting input while seconds count down WITHOUT PASUING THE PROGRAM *le gasp*:
	INPUT_RECORD buf[128]; 	//buffer to save
	DWORD len = 128; 		//size of buffer
	DWORD ev_count; 		//number of events that have been read
	DWORD fault;			//in case something microsoft related breaks
	string sln;
	bool crs = false;
	for (int i = 0; i < 5; i++){
		SetConsoleCursorPosition(h, bufferInfo.dwCursorPosition);
		if (open_puzzle(i) == -1){
			cin.get();
			return 0;
		}
		cout << "Reactor Status:" << endl;
		rod_status();
		reactor();
		update_rod(i, true);
		while(remaining_time(i) > 0 && sln != solutions[i]){
			cout << "Password: " << sln;
			h1 = GetStdHandle(STD_INPUT_HANDLE);
			Sleep(1000);
			//reading will pause program until something is written, so check if something has been
			PeekConsoleInput(h1, buf, len, &ev_count);
			if (ev_count > 0 && !ReadConsoleInput(h1, buf, len, &ev_count)){
				//no password difference so don't clear it
				cout << '\r';
				continue;
			}
			// while I have not accounted for all input events...
			for (int k = 0; k < ev_count; k++){
				//if event involved a key && key was pressed down (w/o this we get key up as well)
				if (buf[k].EventType == KEY_EVENT && buf[k].Event.KeyEvent.bKeyDown){
					if (buf[k].Event.KeyEvent.wVirtualKeyCode == VK_BACK && sln.length() > 0){
						sln = "";
					}
					else if (buf[k].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE){
						cout << "hax detected, not cool dude";
						sln = solutions[i];
						Sleep(1000);
					}
					else if (buf[k].Event.KeyEvent.wVirtualKeyCode == VK_HOME){
						if (open_puzzle(i) == -1){
							cin.get();
							return 0;
						}
					}
					else{
						sln.push_back(buf[k].Event.KeyEvent.uChar.AsciiChar);
					}
				}
			}
			//clear solution to prevent extra chars from remaining on screen when using backspace
			cout << '\r';
			cout << string(79, ' ');
			//clear line
			cout << '\r';
		}
		if (sln == solutions[i]){
			sln = "";
			puzzle = NULL;
		}
		else{
			crs = true;
			break;
		}
	}
	SetConsoleCursorPosition(h, bufferInfo.dwCursorPosition);
	cout << "Reactor Status:" << endl;
	rod_status();
	reactor();
	if (crs){
		crash(h, bufferInfo);
	}
	else{
		int hours, minutes, seconds;
		hours = end_time / 3600;
		minutes = (end_time % 3600) / 60;
		seconds = end_time % 60;
		cout << "\n\nReactor stabalized. Time Elapsed: " << setw(2) << setfill('0') << hours;
		cout << ":" << setw(2) << setfill('0') << minutes;
		cout << ":" << setw(2) << setfill('0') << seconds;
	}
	while(true){
		cin.get();
	}
	return 0;
}




















