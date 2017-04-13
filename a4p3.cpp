/*
Program Name: Bomb
Author: Caleb Edens

Function: This program is a bomb with four color coded modules for the user to crack. 
Each module is solved by reverse engineering the answer from the binary and if they
get one wrong, the bomb blows up. All four modules must be solved in order to disarm
the bomb. 
*/

#include <string>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <bitset>
#include <iostream>
#include <windows.h>
#include <sstream>
using namespace std;

//These are global variables used in the original binary (This is bad but accurate to original)
int wire_yellow = 1;
int wire_green = 1;
int wire_blue = 1; 
int wire_red = 1;
int disarmed = 1;
unsigned int r[3];

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

/////////////////////////////////////SYSTEM////////////////////////////////////////////////////
//This section contains all of the functions that handle console output. 
///////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////
//Input: char wire = the character that should be displayed if the wire has been cut
//Function: Prints the wires at the end of display lines 2 through 5 based on their
//global variable values. wire = 1: prints a colored space, wire = 0: prints wire
/////////////////////////////////////
void wireDraw(char wire){
	//Yellow Wire
	if(wire_yellow < 1){
		SetConsoleTextAttribute(hConsole, 14);
		printf("%c",wire);
		printf("  ");
	}
	else{
		SetConsoleTextAttribute(hConsole, 230);
		printf(" ");
		SetConsoleTextAttribute(hConsole, 14);
		printf("  ");
	}
	//Green Wire
	if(wire_green < 1){
		SetConsoleTextAttribute(hConsole, 10);
		printf("%c",wire);
		printf("  ");
	}
	else{
		SetConsoleTextAttribute(hConsole, 160);
		printf(" ");
		SetConsoleTextAttribute(hConsole, 14);
		printf("  ");
	}
	//Blue Wire
	if(wire_blue < 1){
		SetConsoleTextAttribute(hConsole, 9);
		printf("%c",wire);
		printf("  ");
	}
	else{
		SetConsoleTextAttribute(hConsole, 155);
		printf(" ");
		SetConsoleTextAttribute(hConsole, 14);
		printf("  ");
	}
	//Red Wire
	if(wire_red < 1){
		SetConsoleTextAttribute(hConsole, 12);
		printf("%c",wire);
		printf("  \n");
	}
	else{
		SetConsoleTextAttribute(hConsole, 200);
		printf(" ");
		SetConsoleTextAttribute(hConsole, 14);
		printf("  \n");
	}
}

/////////////////////////////////////
//Input: N/A
//Function: Handles the menu output based on the wire and disarm variables. 
//Notes: Every "SetConsoleTextAttribute" simply changes the color of all things 
//displayed in the console following it.
/////////////////////////////////////
void menu(){
	//Line 1
	SetConsoleTextAttribute(hConsole, 15);
	printf("----------------------------------------");
	SetConsoleTextAttribute(hConsole, 230);
	printf(" ");
	SetConsoleTextAttribute(hConsole, 15);
	printf("--");
	SetConsoleTextAttribute(hConsole, 160);
	printf(" ");
	SetConsoleTextAttribute(hConsole, 15);
	printf("--");
	SetConsoleTextAttribute(hConsole, 155);
	printf(" ");
	SetConsoleTextAttribute(hConsole, 15);
	printf("--");
	SetConsoleTextAttribute(hConsole, 200);
	printf(" ");
	SetConsoleTextAttribute(hConsole, 15);
	printf("---\n");

	//line2
	SetConsoleTextAttribute(hConsole, 12);
	printf("     ___  ___    ___  ___    ___  ___   ");
	wireDraw('*');

	//line3
	SetConsoleTextAttribute(hConsole, 12);
	if(disarmed == 0){
		printf("    /__  /__    /__  /__    /__  /__    ");
	}
	else{
		printf("    /  / /  /   /  / /  /   /  / /  /   ");
	}
	wireDraw('.');

	//line4
	SetConsoleTextAttribute(hConsole, 12);
	if(disarmed == 0){
		printf("   /    /      /    /      /    /       ");
	}
	else{
		printf("   /__/ /__/   /__/ /__/   /__/ /__/    ");
	}
	wireDraw('.');

	//line5
	SetConsoleTextAttribute(hConsole, 15);
	printf("     HOURS      MINUTES     SECONDS     ");
	wireDraw('*');

	//line6
	SetConsoleTextAttribute(hConsole, 15);
	printf("+---------------------------------------");
	SetConsoleTextAttribute(hConsole, 230);
	printf(" ");
	SetConsoleTextAttribute(hConsole, 15);
	printf("--");
	SetConsoleTextAttribute(hConsole, 160);
	printf(" ");
	SetConsoleTextAttribute(hConsole, 15);
	printf("--");
	SetConsoleTextAttribute(hConsole, 155);
	printf(" ");
	SetConsoleTextAttribute(hConsole, 15);
	printf("--");
	SetConsoleTextAttribute(hConsole, 200);
	printf(" ");
	SetConsoleTextAttribute(hConsole, 15);
	printf("--+\n");

	if(disarmed == 0){
		printf("Segmentation fault (core dumped)");
	}
	else{
		//line7
		char output6[] = "|                                                   |";
		puts(output6);

		//line8
		printf("|      ");
		SetConsoleTextAttribute(hConsole, 14);
		printf(",");
		SetConsoleTextAttribute(hConsole, 15);
		printf("   DR. VON NOIZEMAN'S NUCLEAR BOMB   ");
		SetConsoleTextAttribute(hConsole, 14);
		printf(",");
		SetConsoleTextAttribute(hConsole, 15);
		printf("      |\n");

		//line9
		printf("|     ");
		SetConsoleTextAttribute(hConsole, 14);
		printf("/!\\");
		SetConsoleTextAttribute(hConsole, 15);
		printf(" AUTHORIZED ACCESS ONLY - KEEP OUT ");
		SetConsoleTextAttribute(hConsole, 14);
		printf("/!\\");
		SetConsoleTextAttribute(hConsole, 15);
		printf("     |\n");

		//line10
		puts(output6);

		//line11
		if(wire_yellow < 1 && wire_green < 1 && wire_blue < 1 && wire_red < 1){
			printf("|                      ");
			SetConsoleTextAttribute(hConsole, 2);
			printf("[DISARM]                     ");
			SetConsoleTextAttribute(hConsole, 15);
			printf("|");

		}
		else{
			printf("|       ");
			//Yellow wire selection display
			if(wire_yellow < 1){
				SetConsoleTextAttribute(hConsole, 8);
				printf("[1] YELLOW ");
			}
			else{
				SetConsoleTextAttribute(hConsole, 2);
				printf("[1] ");
				SetConsoleTextAttribute(hConsole, 15);
				printf("YELLOW ");
			}
			//Green wire selection display
			if(wire_green < 1){
				SetConsoleTextAttribute(hConsole, 8);
				printf("[2] GREEN ");
			}
			else{
				SetConsoleTextAttribute(hConsole, 2);
				printf("[2] ");
				SetConsoleTextAttribute(hConsole, 15);
				printf("GREEN ");
			}
			//Blue wire selection display
			if(wire_blue < 1){
				SetConsoleTextAttribute(hConsole, 8);
				printf("[3] BLUE ");
			}
			else{
				SetConsoleTextAttribute(hConsole, 2);
				printf("[3] ");
				SetConsoleTextAttribute(hConsole, 15);
				printf("BLUE ");
			}
			//Red wire selection display
			if(wire_red < 1){
				SetConsoleTextAttribute(hConsole, 8);
				printf("[4] RED       ");
			}
			else{
				SetConsoleTextAttribute(hConsole, 2);
				printf("[4] ");
				SetConsoleTextAttribute(hConsole, 15);
				printf("RED       ");
			}
			SetConsoleTextAttribute(hConsole, 15);
			printf("|\n");
		}
		
		//line12
		puts(output6);

		//line13
		char output11[] = "+---------------------------------------------------+";
		puts(output11);
	}
	
}

/////////////////////////////////////
//Input: N/A
//Function: Displays the explosian and forces the program to exit. 
/////////////////////////////////////
void boom(){
	char output[] = "KABOOM\n";
	puts(output);
	Sleep(1000);
	char output1[] = "          .-^^---....,,--_\n      _--/                \\--_\n     <                        >)\n     |                         |\n      \\._                   _./\n          '''--. . , ; .--'''\n               | |   |\n            .-=||  | |=-.\n            `-=#$%&%$#=-'\n               | ;  :|\n     _____.,-#%&$@%#&#~,._____\nSegmentation fault (core dumped)";
	puts(output1);
	exit(0);
	return;
}

/////////////////////////////////////
//Input: int color = The number of what module the text is being displayed in. 
//string input = The text that will be printed in the selected color.
//bool newLine = Says if there should be a new line character placed at the end.
//Function: Prints the text in the pretty display format with the color matching 
//the module that it is currently in. If this function did not exist, there would
//be blocks of about four lines just to print one line of text due to the 
//color changes that are required. 
/////////////////////////////////////
void text(int color, string input, bool newLine){
	//Yellow Text
	if(color == 1){
		SetConsoleTextAttribute(hConsole, 230);
		printf(" ");
		SetConsoleTextAttribute(hConsole, 14);
	}
	//Green Text
	else if(color == 2){
		SetConsoleTextAttribute(hConsole, 160);
		printf(" ");
		SetConsoleTextAttribute(hConsole, 10);
	}
	//Blue Text
	else if(color == 3){
		SetConsoleTextAttribute(hConsole, 155);
		printf(" ");
		SetConsoleTextAttribute(hConsole, 9);
		
	}
	//Red Text
	else if(color == 4){
		SetConsoleTextAttribute(hConsole, 200);
		printf(" ");
		SetConsoleTextAttribute(hConsole, 12);
	}
	//Gray Text
	else if(color == 5){
		SetConsoleTextAttribute(hConsole, 140);
		printf(" ");
		SetConsoleTextAttribute(hConsole, 8);
	}
	printf(" %s ", input.c_str());
	SetConsoleTextAttribute(hConsole, 15);
	if(newLine){
		printf("\n");
	}
}


/////////////////////////////////////YELLOW////////////////////////////////////////////////////
//This section contains all of the code that runs when the user selects the Yellow path.
//
//Answer: 84371065 
///////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////
//Input: char* buf = a pointer to the input buffer that all of the user input will go to
//Function: Gathers the user input for what they think the password for this section is. 
/////////////////////////////////////
void yellow_preflight(char* buf){
	text(1,"ENTER UNLOCK PASSWORD 1:", false);
	fgets(buf, 10, stdin);
	return;
}

/////////////////////////////////////
//Input: N/A
//Function: Processes the user input and campares each character of the input to the correct character. 
//If all are correct, wire_yellow is set to 0, else the bomb blows up.  
/////////////////////////////////////
void yellow(){
	char buffer[20]; 
	yellow_preflight(buffer);
	if(buffer[0] == '8' && buffer[1] == '4' && buffer[2] == '3' && buffer[3] == '7' && buffer[4] == '1' && buffer[5] == '0' && buffer[6] == '6' && buffer[7] == '5'){
		text(1,"UNLOCK PASSWORD 1 ACCEPTED, LOCK DISENGAGED", true);
		wire_yellow = 0;
	}
	else{
		wire_yellow = wire_yellow<<=10;
		boom(); //TODO
	}
	return;
}

/////////////////////////////////////GREEN/////////////////////////////////////////////////////
//This section contains all of the code that runs when the user selects the Green path.
//
//Answer: dcaotdae  *
//Note:Any character can go in that * slot. If nothing is the bomb will lock back up.
///////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////
//Input: char* buf = a pointer to the input buffer that all of the user input will go to
//Function: Gathers the user input for what they think the password for this section is. 
/////////////////////////////////////
void green_preflight(char* buf){
	text(2,"ENTER UNLOCK PASSWORD 2:", false);
	fgets(buf, 20, stdin);
	return;
}

/////////////////////////////////////
//Input: N/A
//Function: Checks to see if the start of the input is "dcaotdae" and then looks 3 
//characters after that to see if something is there. If "dcaotdae" is not there it
//blows up. If "dcaotdae" is there but there is no character 3 slots after it, the
//wire simply does not unlock. If both are there, the wire unlocks. 
/////////////////////////////////////
void green(){
	//char fakeName[3];
	// overflow attempted but results were very random between compiles 
	char buffer[20];
	buffer[10] = '\0';
	//fakeName[0] = '\0';
	green_preflight(buffer);
	if(strncmp(buffer, "dcaotdae", 8) == 0){
		text(2, "UNLOCK PASSWORD 2 ACCEPTED, LOCK DISENGAGED", true);
		Sleep(1000);
		text(2, "ACTION OVERIDDEN FROM USER NOIZEV, LOCK RE-ENGAGED", true);

		if(buffer[10] != '\0'){
		//if(fakeName[0] != '\0'){
			//printf(" %s", buffer );
			wire_green = wire_green>>1;
		}
	}
	else{
		boom();
	}
}

/////////////////////////////////////BLUE//////////////////////////////////////////////////////
//This section contains all of the code that runs when the user selects the Blue path.
//
//Answer: LLRR or LLRRRRRR or LLRRRRRRRRRR
//Note: This is supposed to emulate a graph traversal but that did not work so instead 
//it just checks a few correct sequences. 
///////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////
//Input: char* buf = a pointer to the input buffer that all of the user input will go to
//Function: Gathers the user input for what they think the password for this section is. 
/////////////////////////////////////
void blue_preflight(char* buf){
	text(3, "ENTER CIRCUIT TRAVERSAL PATH:", false);
	fgets(buf, 20, stdin);
	return;
}

/////////////////////////////////////
//Input: N/A
//Function: First it checks to be sure the input only contains Ls, Rs, and new line 
//characters. if it passes that test, it then compairs the input to a couple 
//pre defined strings to see if they match. If there is a match, the wire unlocks, 
//else it blows up. 
/////////////////////////////////////
void blue(){
	char buffer[30]; 
	blue_preflight(buffer);
	//Graph is unused but makes this resemble the original binary a little closer. 
	unsigned int graph[] = {156,193,4,8,150,250,187,71,120,193,4,8,20,194,4,8,110,26,23,80,180,193,4,8,216,193,4,8,241,243,218,35,168,193,4,8,156,193,4,8,211,132,66,99,192,193,4,8,240,193,4,8,177,78,76,52,252,193,4,8,204,193,4,8,239,121,64,12,20,194,4,8,120,193,4,8,149,189,94,66,132,193,4,8,204,193,4,8,73,231,172,7,168,193,4,8,228,193,4,8,136,58,122,35,132,193,4,8,240,193,4,8,182,108,132,75,132,193,4,8,20,194,4,8,152,154,186,31,192,193,4,8,156,193,4,8,255,211,74,58,192,193,4,8,132,193,4,8,22,140,132,22,120,193,4,8,144,193,4,8,206,228,158,73,180,193,4,8,192,193,4,8,251,248,26,38,132,193,4,8,204,193,4,8,42,168,14,119,252,193,4,8};
	
	//Checks the input characters for invalid characters
	for(int i = 0; i <= 14; i++){
		if(buffer[i] != 'L'){
			if(buffer[i] != 'R'){
				if(buffer[i] == '\n'){
					break;
				}
				else{
					boom();
				}
			}
		}
	}
	text(3, "PROGRAMMING GATE ARRAY...", false);
	Sleep(1000);
	SetConsoleTextAttribute(hConsole, 9);
	printf("SUCCEEDED\n");
	Sleep(1000);
	if(strncmp(buffer, "LLRR", 4) == 0 || strncmp(buffer, "LLRRRRRR", 8) == 0 || strncmp(buffer, "LLRRRRRRRRRR", 12) == 0){
		text(3, "VOLTAGE REROUTED FROM REMOTE DETONATION RECIEVER", true);
		wire_blue = wire_blue - 1;
	}
	else{
		SetConsoleTextAttribute(hConsole, 15);
		boom();
	}
}

/////////////////////////////////////RED///////////////////////////////////////////////////////
//This section contains all of the code that runs when the user selects the Red path.
//
//Answer: KDG3DU32D38EVVXJM64
///////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////
//Input: char* buf = a pointer to the input buffer that all of the user input will go to
//Function: Gathers the user input for what they think the password for this section is.
//This also defines and displays the 3 numbers that the user will need to crack this module.
/////////////////////////////////////
void red_preflight(char* buf){
	//These rand functions do nothing but make the code harder to reverse. 
	r[0] = rand();
	r[1] = rand();
	r[2] = rand();
	//store the decimal representation of the hex values we display
	r[0] = 1804289383;
	r[1] = 846930886;
	r[2] = 1681692777;
	//display the hex values
	Sleep(1000);
	text(4, "CLOCK SYNC", false);
	printf("6B8B4567\n");
	Sleep(1000);
	text(4, "CLOCK SYNC", false);
	printf("327B23C6\n");
	Sleep(1000);
	text(4, "CLOCK SYNC", false);
	printf("643C9869\n");
	Sleep(1000);
	text(4, "ENTER CLOCK RESYNCHRONIZATION SEQUENCE:", false);
	fgets(buf, 21, stdin);
}

/////////////////////////////////////
//Input: N/A
//Function: Yakes the 3 numbers stored in the preflight and does a series of bitwise operations
//to determine what character from our character array we need to be comparing to.  
/////////////////////////////////////
void red(){
	char buffer[30];
	char input[] = "ABCDEFGHJKLMNPQRSTUVWXYZ23456789";
	red_preflight(buffer);
	for(int i = 0; i <=18; i++){
		if(buffer[i] == input[r[2] & 31]){
			r[2] = r[2]>>5 | r[1]<<27;
			r[1] = r[1]>>5 | r[0]<<27;
			r[0] = r[0]>>5;
		}
		else{
			wire_red = wire_red + 1; 
			boom();
			return;
		}
	}
	wire_red = 0; 
	return;
}

/////////////////////////////////////MAIN/////////////////////////////////////////////////////
//This section contains the main directory for all of the modules. 
///////////////////////////////////////////////////////////////////////////////////////////////
int main() {
	while (disarmed == 1){
		menu();
		text(5, "MENU SELECTION:", false);
		char buf[20];
		fgets(buf,20,stdin); 
		string input(buf);
		if(input == "1\n" || strcasecmp(input.c_str(), "yellow\n") == 0){
			yellow();
		}
		else if(input == "2\n" || strcasecmp(input.c_str(), "green\n") == 0){
			green();

		}
		else if(input == "3\n" || strcasecmp(input.c_str(), "blue\n") == 0){
			blue();
		}
		else if(input == "4\n" || strcasecmp(input.c_str(), "red\n") == 0){
			red();
		}
		else if(strcasecmp(input.c_str(), "exit\n") == 0 || strcasecmp(input.c_str(), "quit\n") == 0){
			break;
		}
		else if(strcasecmp(input.c_str(), "disarm\n") == 0){
			if(wire_yellow < 1 && wire_green < 1 && wire_blue < 1 && wire_red < 1){
				disarmed = 0;
				menu();
				exit(0);
			}
			else{
				boom();
			}
		}
		else{
			boom();
			break;
		}

		text(5, "PRESS ENTER TO RETURN TO MENU", false);
		getchar();
	}
}