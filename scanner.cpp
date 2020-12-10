#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


string RES_WORDS[] = { "if","then","else","end","repeat","until","read","write" };

bool isDigit(char d) { return (d >= '0' && d <= '9'); }

bool isLetter(char l) { return (l >= 'a' && l <= 'z' || l >= 'A' && l <= 'Z'); }

bool isSpace(char s) { return (s == ' ' || s == '\t' || s == '\n'); }

bool isSymbol(char c) { return (c == '+' || c =='-' ||c == '*' ||c == '/' ||c == '=' || c =='<' ||c == '(' ||c == ')' ||c == ';'); }


string token;

typedef enum {idle,start,num,id,assign,comment,special,reserved,error} stateType;



stateType state=idle;


ofstream ofile;


void done() {
	
	if (state == start ) {
		ofile << "unexpected output at token \n"<< token;
	}
	else if (state == num) {
		ofile << token << " : Number \n";
	}
	else if (state ==id ) {
		ofile << token << " : Identifier \n";
	}
	else if (state ==comment ) {
		ofile << token << " : Comment \n";
	}
	else if (state ==special ) {
		ofile << token << " : Special Symbol \n";
	}
	else if (state == reserved) {
		ofile << token << " : Reserved Word \n";
	}
	else if (state = error) {
		ofile << "ERROR, unexpected output at :" << token;
	}

}


int main() {
	
	ifstream myReadFile;
	myReadFile.open("tiny_sample_code.txt");
	string input, line;
	cout << "Welcome to Scanner assignment \n ";
	cout << "A file \"scanner_output.txt\" will be generated with the scanner output";


	if (myReadFile.is_open()) {
		while (!myReadFile.eof()) { myReadFile >> line; input += " ";input+=line; }
	}
	else cout << "Error opening file, Please check file name and location.";
	//char* inputChar = new char[input.size()];
	//strcpy_s(inputChar, 10000,input.c_str());
	
	ofile.open("scanner_output.txt");
	ofile << "Scanner Output for file \"tiny_sample_code.txt\" : \n";
	




	char x;

	state = start;


	for (int i = 0;i < input.size();i++) {
		x = input[i];
		if (x == ' ' && state!=comment) {
			state = start;
		}
		else if (x == '{') {
			token = x;
			state = comment;
		}
		else if (state == start) {
			if (isDigit(x)) {
				state = num;
				token = "";
				token.push_back(x);
				if (!isDigit(input[i+1])) {
					done();
					state = start;
				}
			}
			else if (isSymbol(x)) {
				token = x;
				state = special;
				done();
				state = start;
			}
			else if (x == ':') {

				if (input[i + 1] == '='){
					token = "";
					token.push_back(x);
					token.push_back(input[i + 1]);
					state = special;
					done();
					input[i + 1] = ' ';
					state = start;
				}
				else {
					token = x;
					state = error;
					done();
					state = start;
				}
			}
			else if (isLetter(x)) {
				token = "";
				state = id;
				
				if (!isLetter(input[i+1])) {
				    token.push_back(x);
				    state = id;
				    for (int j = 0; j < 8; j++)
			        {
				        if (RES_WORDS[j] == token) state = reserved;
			        }
					done();
					state = start;
					
				}
			
				else {
					token.push_back(x);
					if (isalnum(input[i + 1]) || input[i+1]=='_') {
						state = id;
					}
					else {
						state = id;
						done();
						state = start;
					}
				}
			}
		
			else {
				token = x;
				state = error;
				done();
				state = start;
			}
		}
		else if (state == comment) {
			if (x == '}') {
				token += x;
				done();
				state = start;
			}
			else {
				token += x;
				state = comment;
			}
		}
		else if (state == num) {
			token.push_back(x);
			if (isDigit(input[i + 1])) {
				state = num;
			}
			else {
				done();
				state = start;
			}
		}
		else if (state == id) {
			token.push_back(x);
			if (isLetter(input[i+1])) {
				state = id;
			}
			else {
				    for (int j = 0; j < 8; j++)
			        {
				        if (RES_WORDS[j] == token) state = reserved;
			        }
				done();
				state = start;
			}
		}
	}
	myReadFile.close();
	ofile.close();


}