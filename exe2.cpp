////#include <conio.h>
////#include <stdio.h>
////#include <iostream>
////#include <string>
////#include <stdlib.h>
////#include <fstream>
////using namespace std;
////
////void encrypt(string msg)
////{
////   int i, x=1;
////
////		if(x==1)
////		{
////  
////			  //first case for encrypting a string
////   
////				 for(i = 0; (i < 100 && msg[i] != '\0'); i++)
////					msg[i] = msg[i] + 2; 
////
////				 cout << msg << endl;
////  
////		}		
////		_getch();
////
////   //   //second case for decrypting a string
////   //   case 2:
////   //      for(i = 0; (i < 100 && msg[i] != '\0'); i++)
////   //      msg[i] = msg[i] - 2; //the key for encryption is 3 that is subtracted to ASCII value
////
////   //   cout << "\nDecrypted string: " << msg << endl;
////   //   break;
////
////   //   default:
////   //      cout << "\nInvalid Input !!!\n";
////   //}
////   //_getch();
////}
////int main()
////{
////	string msg;
////
////	cout<<"please enter a message\t";
////	cin>>msg;
////	encrypt(msg);
////}
////
////C++ program for encryption and decryption
//#include<iostream>
//#include<stdlib.h>
//#include<math.h>
//#include<string.h>
//#include <conio.h>
//
//using namespace std;
//
//int x, y, n, t, i, flag;
//long int e[50], d[50], temp[50], j;
//char en[50], m[50];
//char msg[100];
//int prime(long int); //function to check for prime number
//void encryption_key();
//long int cd(long int);
//void encrypt();
//void decrypt();
//
//int main()
//{
//   cout << "\nENTER FIRST PRIME NUMBER\n";
//   cin >> x;
//
//   //checking whether input is prime or not
//   flag = prime(x);
//   if(flag == 0)
//   {
//      cout << "\nINVALID INPUT\n";
//      exit(0);
//   }
//
//   cout << "\nENTER SECOND PRIME NUMBER\n";
//   cin >> y;
//
//   flag = prime(y);
//   if(flag == 0 || x == y)
//   {
//      cout << "\nINVALID INPUT\n";
//      exit(0);
//   }
//
//   cout << "\nENTER MESSAGE OR STRING TO ENCRYPT\n";
//   cin >> msg;
//
//   for(i = 0; msg[i] != NULL; i++)
//      m[i] = msg[i];
//   n = x * y;
//   t = (x - 1) * (y - 1);
//
//   encryption_key();
//   cout << "\nPOSSIBLE VALUES OF e AND d ARE\n";
//
//   for(i = 0; i < j - 1; i++)
//      cout << "\n" << e[i] << "\t" << d[i];
//
//   encrypt();
//   decrypt();
//   return 0;
//} //end of the main program
//
//int prime(long int pr)
//{
//   int i;
//   j = sqrt(pr);
//   for(i = 2; i <= j; i++)
//   {
//      if(pr % i == 0)
//         return 0;
//   }
//   return 1;
// }
//
////function to generate encryption key
//void encryption_key()
//{
//   int k;
//   k = 0;
//   for(i = 2; i < t; i++)
//   {
//      if(t % i == 0)
//         continue;
//      flag = prime(i);
//      if(flag == 1 && i != x && i != y)
//      {
//         e[k] = i;
//         flag = cd(e[k]);
//         if(flag > 0)
//         {
//            d[k] = flag;
//            k++;
//         }
//         if(k == 99)
//         break;
//      }
//   }
//}
//
//long int cd(long int a)
//{
//   long int k = 1;
//   while(1)
//   {
//      k = k + t;
//      if(k % a == 0)
//         return(k/a);
//   }
//}
//
////function to encrypt the message
//void encrypt()
//{
//   long int pt, ct, key = e[0], k, len;
//   i = 0;
//   len = strlen(msg);
//
//   while(i != len)
//   {
//      pt = m[i];
//      pt = pt - 96;
//      k = 1;
//      for(j = 0; j < key; j++)
//      {
//         k = k * pt;
//         k = k % n;
//      }
//      temp[i] = k;
//      ct= k + 96;
//      en[i] = ct;
//      i++;
//   }
//   en[i] = -1;
//   cout << "\n\nTHE ENCRYPTED MESSAGE IS\n";
//   for(i=0; en[i] != -1; i++)
//      cout << en[i];
//}
//
////function to decrypt the message
//void decrypt()
//{
//   long int pt, ct, key = d[0], k;
//   i = 0;
//   while(en[i] != -1)
//   {
//      ct = temp[i];
//      k = 1;
//      for(j = 0; j < key; j++)
//      {
//         k = k * ct;
//         k = k % n;
//      }
//      pt = k + 96;
//      m[i] = pt;
//      i++;
//   }
//   m[i] = -1;
//   cout << "\n\nTHE DECRYPTED MESSAGE IS\n";
//   for(i = 0; m[i] != -1; i++)
//      cout << m[i];
//
//  cout << endl;
//  _getch();
//}

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

char getmenuselection (char m);
void encrypt (char key[]);
void decrypt (char code[]);


int main()
{
	ifstream input;
	ifstream in;
	ofstream out;
	char menu;
	char file [80];
	char codekey;
	char myname[128];
	menu=0;

	menu=getmenuselection(menu); //Asks user what function to use.

		if (menu == 'e' || menu == 'E') //Option to encrypt a file.
		{
		cout << "Enter original file name... ";
		input.open (file);
		cin >> file;
		encrypt (file);
		input.close();									
		cout << "Encrypted string is: " << file <<endl;
		return main();
		}
		if (menu == 'd'|| menu == 'D')//Option to decrypt a file.
		{
		cout << "Enter original file name... ";
		input.open (file);
		cin >> file;
		decrypt (file);
		input.close();									
		cout << "Decrypted string is: " << file <<endl;
		return main();
		}
		if (menu == 'q') //Option to end the program.
		{
		cout << "Goodbye...";
		cin.ignore(2);
		return 0;
		}
cin.ignore(2);
return 0;				
}
char getmenuselection (char m) //Menu selection function.
{
	cout << "Select 'E' to encrypt a file or select 'D' to decrypt a file. ";
	cin >> m;
    switch (m)
    {
       case 'e':
	   case 'E':   cout << "You have selected to encrypt a file... " << endl;
                 break;
       case 'd':
	   case 'D':   cout <<  "You have selected to decrypt a file... " << endl; 
				break;
	   case 'q':
	   case 'Q':   cout <<  "You have selected to quit..." << endl; 
				break;
       default: cout << "Invalid entry, please try again... ";                
				return getmenuselection (m);
}return (m);
}
void encrypt (char key[]) //encryption function.
{
	for(int i = 0; i < 5; i++) key[i] += 2; 
}										
void decrypt (char code[]) //decryption function.
{
	for(int i = 0; i < 5; i++) code[i] -= 2;
}