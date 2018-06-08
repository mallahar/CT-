#include <iostream>
#include <string>
#include <conio.h>
#include <cctype>
using namespace std;

void main()
{
	string password;
    char input, passChar[100];
	int i=0;

		system("cls");
		cout<<"ENTER PASSWORD: ";
		for (i=0;;i++)
		{
			input=getch();
			if ((input!=8)&&(input!=13))
			{	
				passChar[i]=input;
			}
			else if (input==8)
				i-=2;
			else if (input==13)
				break;

			system("cls");
			cout<<"ENTER PASSWORD: ";
			for (int j=0; j<i+1; j++)
				cout<<"*";
		}
		cout<<input;
		_getch();
}

int exe ()
{
  std::string str ("hello world!");
  str.pop_back();
  std::cout << str << '\n';
  _getch();
  return 0;
}