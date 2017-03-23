#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

enum DFAstates { START, INCOMMENT, INNUM, INID, INASSIGN, DONE };
DFAstates state = START; //set START to be intial state
string ReservedWords[] = { "if","then","else","end","repeat","until","read","write" };

void DealWithCode(string S);
bool IsSymbol(char c);
bool IsDigit(char d);
bool IsLetter(char l);
bool IsSpace(char s);

int main() {
	cout << "Put Your Tiny Code in The TinyCode.txt File" << endl;
	cout << "Output at The Output.txt File" << endl;

	//reading tiny code from file
	ifstream file;
	string line, program;
	file.open("TinyCode.txt");
	while (!file.eof()) {
		getline(file, line);
		program += line;
	}

	//writing output to file
	freopen("Output.txt", "w", stdout);
	DealWithCode(program);
	fclose(stdout);
	system("pause");

	return 0;
}

void DealWithCode(string S)
{
	bool reserved = 0;       //flag for reserved words
	string temp;           //to store string if number or identifier
	int i = 0;             //index
	cout << "Token Value  | ";
	cout << "Token Type" << endl;
	cout << "-------------|-------------" << endl;
	while (state != DONE) {
		switch (state) {
		case START:
			if (IsSpace(S[i])) //if space still at start except we reach the end of program
			{
				i++;
				if (i == S.length()) state = DONE;
				else state = START;
			}
			else if (IsDigit(S[i])) //if digit go to INNUM
			{
				state = INNUM;
			}
			else if (IsLetter(S[i])) //if letter go to INID
			{
				state = INID;
			}
			else if (S[i] == ':') {
				state = INASSIGN;
			}
			else if (S[i] == '{') {
				i++;
				state = INCOMMENT;
			}
			//other
			else if (IsSymbol(S[i])) //list of symbols 
			{

				if (S[i] == '+')
				{
					cout << S[i] << "            |" << " PLUS" << endl;
				}
				else if (S[i] == '-')
				{
					cout << S[i] << "            |" << " MINUS" << endl;
				}
				else if (S[i] == '*')
				{
					cout << S[i] << "            |" << " MULTIPLY" << endl;
				}
				else if (S[i] == '/')
				{
					cout << S[i] << "            |" << " BACK SLASH" << endl;
				}
				else if (S[i] == '=')
				{
					cout << S[i] << "            |" << " EQUAL" << endl;
				}
				else if ((S[i] == '<') && (S[i + 1] == '='))
				{
					cout << S[i] << S[i + 1] << "           |" << " LESS THAN OR EQUAL" << endl;
					i++;
				}
				else if ((S[i] == '>') && (S[i + 1] == '='))
				{
					cout << S[i] << S[i+1] << "           |" << " GREATER THAN OR EQUAL" << endl;
					i++;
				}
				else if (S[i] == '<')
				{
					cout << S[i] << "            |" << " LESS THAN" << endl;
				}
				else if (S[i] == '>')
				{
					cout << S[i] << "            |" << " GREATER THAN" << endl;
				}
				else if (S[i] == '(')
				{
					cout << S[i] << "            |" << " ROUND BRACKET OPEN" << endl;
				}
				else if (S[i] == ')')
				{
					cout << S[i] << "            |" << " ROUND BRACKET OPEN" << endl;
				}
				else if (S[i] == ';')
				{
					cout << S[i] << "            |" << " SEMI COLON" << endl;
				}
				else
				{
					cout << S[i] << "            |" << " SYMBOL" << endl;
				}

				i++;
				if (i == S.length()) state = DONE;
				else state = START;
			}
			else state = DONE;
			break;
		case INCOMMENT:
			if (state == INCOMMENT) {
				while (S[i] != '}') {
					i++;
				}
				i++; //43an an2el lly ba3d el comment kolo 
				if (i == S.length()) state = DONE;
				else state = START;
			}
			break;

		case INNUM:
		//till we have any thing except number we store numbers in temp
			while (IsDigit(S[i])) {
				temp += S[i];
				i++;
			}
			temp.resize(13);
			cout << temp << "| NUMBER" << endl;
			temp = ""; //ha empty eltemp dah 34an lma agy ast3mloh tany b2a
			if (i == S.length()) state = DONE;
			else state = START;
			break;

		case INID:
			while (IsLetter(S[i])) {
				temp += S[i];
				i++;
			}
			//for loop to loop over the reserved words array to check temp reserved or not
			for (int i = 0; i < 8; i++)
			{
				if (ReservedWords[i] == temp) reserved = 1; //flag =1 if reserved
			}
			if (reserved) //reserved
			{
				temp.resize(13);
				cout << temp;
				transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
				cout << "| "<< temp << endl;
			}
			else  //identifier 
			{
				temp.resize(13);
				cout << temp;
				cout << "| IDINTIFIER" << endl;
			}
			temp = "";
			reserved = 0; // empty temp & flag = 0
			if (i == S.length()) state = DONE;
			else state = START;
			break;

		case INASSIGN:
			if (S[i] == ':') {
				i += 2;
				cout << ":=" << "           ";
				cout << "| ASSIGN" << endl;
				state = START;
			}
			else {
				if (i == S.length()) state = DONE;
				else state = START;
			}
			break;

		case DONE:
			break;
		}
	}
}

bool IsSymbol(char c)
{
	return (c == '+' || '-' || '*' || '/' || '=' || '<' || '>' || '(' || ')' || ';' );
}

bool IsDigit(char d)
{
	return (d >= '0' && d <= '9');
}

bool IsLetter(char l)
{
	return (l >= 'a' && l <= 'z' || l >= 'A' && l <= 'Z');
}

bool IsSpace(char s)
{
	return (s == ' ');
}


