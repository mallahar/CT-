// Ethan Madden and Mallahar Shinde
// 15/05/2018
#include "account_encrypt.h"
#include "library.h";
#define ACCOUNT 50
#define ESCAPE 27

class reserve
{
public:
	string name,timeOfDay;
	int people,timeOfReservation, hourOfReservation, minuteOfReservation;
};

class input
{
public:
	string password,
		name,
		email;
};

void userMenu ();

int admin_arrows ();

void modifyAccount ();

void reservation ();

void makeReservation ();

void deleteReservation ();

void changeReservation ();

void receipt ();

int main();

void delete_User_Account();

void delete_admin_account();

string * MenuItems(); // a function that returns the name of a menu item.

string * adminItems(); // a function that returns the name of a menu item.

void gotoxy(int,int); // by this function you can goto any position on the cmd line screen.

void ChangeCursorStatus(bool);

void createAccount(); // every menu item needs a seperate function, so this is for the first item.

void logIn(); //    and the second item etc...

void help(); //if you want another way to implement the functionallity of a menu item plz
                 //    contact me at my email.

void ExitOption(); // this is also an item function but i named it like this coz every menu must
                   //    have an exit item.

int main()
{
	system("cls");
	ChangeCursorStatus(false);
	typedef void (*TMenuOption)(); // typedef for defining a 'pointer to function' type.

	int ItemCount=4; // This variable holds the number of menu items.
	int MenuChoice=1; // This variable holds the position of the cursor.
	char key; //for entering the key (up arrow,down arrow,etc...);

	TMenuOption *MenuOption=new TMenuOption[ItemCount];//array of pointers to functions (dynamic).
	MenuOption[0]=createAccount; //filling the array with the functions.
	MenuOption[1]=logIn;
	MenuOption[2]=help;
	MenuOption[3]=ExitOption;

	while(1) //infinite loop. (this loop will not break that's why we need an exit function).
	{
		for (int i=0;i<ItemCount;i++) // Draw the menu.
		{
			gotoxy(3,3+i);
			MenuChoice==i+1 ? cout<<" -> " : cout<<"    "; // if (i+1) == the cursor then
			                                               //    print ' -> ' else print '    '.
			                                               //    by the way i call '->' the cursor
			cout<<MenuItems()[i]<<endl; // print the name of the item.
		} // finish the drawing.

		key=getch(); //get the key.

		/*
		   getch() is like cin>>bla;
		   but the differance is that by 'cin' you can enter char,double,int,etc...
		   with more than one digit and the value you entered is printed on the screen

		   but with getch you can only enter ONE CHARACTER and will not be printed on
		   the sceen and return the entered key to the variable 'key' in this case.
		*/

		switch (key) //check the entered key.
		{
		case '\r': // if the entered key is 'Enter'.
			try
			{
				(*MenuOption[MenuChoice-1])(); // call the function of the index 'cursor-1' in
				                               //     the 'pointer to function' array.
			}
			catch(...)
			{}  // we have to use try and catch coz if we did'nt fill that index with a function.
				//                     a runtime error will appear.

			break;

		case 'P': // if the entered key is the 'up arrow' notice that its equal to 'P' (capital)
			MenuChoice++; //then we will increment the cursor by one.
			if (MenuChoice>ItemCount) // if the cursor value is more than the items count.
				MenuChoice=1;         //    then it will return back to the first item.
			break;

		case 'H': // same but with 'down arrow' and decrement the cursor.
			MenuChoice--;
			if (MenuChoice<1)
				MenuChoice=ItemCount;
			break;

		case 27: // 27 is the asscii to the escape key (Esc)
			try {(*MenuOption[ItemCount-1])();} // useually when the 'Esc' key is pressed the last
			                                    //     item will be called (executed). but you can
			                                    //     change it to whatever you want.
			catch(...){}
			break;
		default:// any another key.
			if (key>='1' && key <=char(ItemCount+'0'))//check if the pressed key is in the range
				                                      //    of (1,2,3,...,#of items) [all char(s)]
			{
				try {(*MenuOption[int(key)-'0'-1])();} //call the function of the pressed number.
				     //  you can make the cursor move to that item instead of calling (executing)
					 //  it by replacing all the code between 'if (bla){' and '}' with this
				     //  statement MenuChooice=int(key)-'0'
				catch(...){}
			}
		}
	}

	delete MenuOption;
	return 0;
}
string * MenuItems() // this function returns a pointer to a string.
{
	string *item=new string[4];
	item[0]="create account";
	item[1]="login";
	item[2]="help";
	item[3]="Exit";

	return item;
}
void gotoxy(int xpos, int ypos)  // just take this function as it is.
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput,scrn);
}
void ChangeCursorStatus(bool Visible)
{
	CONSOLE_CURSOR_INFO *c=new CONSOLE_CURSOR_INFO;
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);

	if (Visible)
	{
		c->bVisible=TRUE;
		c->dwSize=0;//(0) is invild so the default value is set
	}
	else
	{
		c->bVisible=FALSE;
		c->dwSize=1;//it must be assigned to a valid value
	}

	SetConsoleCursorInfo(h,c);
}
void createAccount ()
{
	input create;
	int i=0;

	system("cls");
	gotoxy(3,2);

	ofstream myfile;
	myfile.open("account_info.txt",ios::app);

	//cout<<"<Esc> to go back\n";
	//	    while (true)
 //   {
 //       int c = 0;

 //       switch ((c = _getch()))
 //       {
 //       case ESCAPE:
	//		main();
 //           break;
 //       }
 //   }

	cout << "Create an account" << endl << endl;

	cout << endl << "Email: " << endl;
	cin >> create.email;

	regex email = regex("\\w+(\\.\\w+)*@\\w+(\\.\\w+)+");

	while (!regex_match(create.email, email))
	{
		cout << endl << "Error! Incorrect input!" << endl;
		cout << endl << "Enter your email: " << endl;
		cin >> create.email;
	}

	myfile << create.email << " ";
	cout << endl << "Username: " << endl;
	cin >> create.name;
	myfile << create.name << " ";

	cout << endl << "Password: " << endl;
	char c = getch();
	while(c!='\n'&&c!='\r'&&c!='\b')
	{
		create.password += c;
		system("cls");

		cout << "Create an account" << endl << endl;

		cout << "Email: " << endl;
		cout << create.email << endl;

		cout << endl << "Username: " << endl;
		cout << create.name << endl;

		cout << endl << "Password: " << endl;
		cout << string(create.password.size(),'*');

		c = getch();

	}

	myfile<<create.password << endl;

	myfile.close();
}
void logIn ()
{
	input login_info;


	system("cls");
	gotoxy(3,1);

	int login(0),i=0,flag=0;
	string names[ACCOUNT],passwords[ACCOUNT],email[ACCOUNT];

	ifstream myfile;
	myfile.open("account_info.txt",ios::out);

	ifstream admin;
	admin.open("admin_account.txt",ios::out);

	i=0;
	if(myfile.is_open())
	{
		while(!myfile.eof())
		{
			myfile >> email[i];
			myfile >> names[i];
			myfile >> passwords[i];
			i++;
		}
	}

   	fflush(stdin);
	cout << "Log In" << endl << endl;

	cout << "Enter in your Username: " << endl;
	cin >> login_info.name;

	cout << endl << "Enter in your Password: " << endl;
	cin >> login_info.password;

	for(i=0;i<ACCOUNT;i++)
	{

		if(login_info.name.compare(names[i])==0 && login_info.password.compare(passwords[i])==0)
		{
			flag=1;
		}
	}

	if(flag==1)
	{
		userMenu();
		myfile.close();
	}
	else
	{
		input admin_login;
		int x=0,i=0;

		if(admin.is_open())
		{
			while(!admin.eof())
			{
				admin >> email[i];
				admin >> names[i];
				admin >> passwords[i];
				i++;
			}
		}
		for(i=0;i<ACCOUNT;i++)
		{
			if(login_info.name.compare(names[i])==0 && login_info.password.compare(passwords[i])==0)
			{
				x=1;
			}
		}
		if(x==1)
		{
			admin_arrows();
		}
		else
		{
			cout<<"account is not avaliable";
		}

		admin.close();
	}
	getch();
	system("cls");
}
void gotoxy_1(int,int); // by this function you can goto any position on the cmd line screen.

void ChangeCursorStatus_1(bool);

int admin_arrows()
{
	system("cls");

	ChangeCursorStatus_1(false);
	typedef void (*TMenuOption)(); // typedef for defining a 'pointer to function' type.

	int ItemCount=5; // This variable holds the number of menu items.
	int adminChoice=1; // This variable holds the position of the cursor.
	char key; //for entering the key (up arrow,down arrow,etc...);

	TMenuOption *MenuOption=new TMenuOption[ItemCount];//array of pointers to functions (dynamic).
	MenuOption[0]=createAccount; //filling the array with the functions.
	MenuOption[1]=modifyAccount;
	MenuOption[2]=delete_User_Account;
	MenuOption[3]=delete_admin_account;
	MenuOption[4]=userMenu;
	MenuOption[5]=ExitOption;

	while(1) //infinite loop. (this loop will not break that's why we need an exit function).
	{
		for (int i=0;i<ItemCount;i++) // Draw the menu.
		{
			gotoxy(3,3+i);
			adminChoice==i+1 ? cout<<" -> " : cout<<"    "; // if (i+1) == the cursor then
			                                               //    print ' -> ' else print '    '.
			                                               //    by the way i call '->' the cursor
			cout<<adminItems()[i]<<endl; // print the name of the item.
		} // finish the drawing.

		key=getch(); //get the key.

		/*
		   getch() is like cin>>bla;
		   but the differance is that by 'cin' you can enter char,double,int,etc...
		   with more than one digit and the value you entered is printed on the screen

		   but with getch you can only enter ONE CHARACTER and will not be printed on
		   the sceen and return the entered key to the variable 'key' in this case.
		*/

		switch (key) //check the entered key.
		{
		case '\r': // if the entered key is 'Enter'.
			try
			{
				(*MenuOption[adminChoice-1])(); // call the function of the index 'cursor-1' in
				                               //     the 'pointer to function' array.
			}
			catch(...)
			{}  // we have to use try and catch coz if we did'nt fill that index with a function.
				//                     a runtime error will appear.

			break;

		case 'P': // if the entered key is the 'up arrow' notice that its equal to 'P' (capital)
			adminChoice++; //then we will increment the cursor by one.
			if (adminChoice>ItemCount) // if the cursor value is more than the items count.
				adminChoice=1;         //    then it will return back to the first item.
			break;

		case 'H': // same but with 'down arrow' and decrement the cursor.
			adminChoice--;
			if (adminChoice<1)
				adminChoice=ItemCount;
			break;

		case 27: // 27 is the asscii to the escape key (Esc)
			try {(*MenuOption[ItemCount-1])();} // useually when the 'Esc' key is pressed the last
			                                    //     item will be called (executed). but you can
			                                    //     change it to whatever you want.
			catch(...){}
			break;
		default:// any another key.
			if (key>='1' && key <=char(ItemCount+'0'))//check if the pressed key is in the range
				                                      //    of (1,2,3,...,#of items) [all char(s)]
			{
				try {(*MenuOption[int(key)-'0'-1])();} //call the function of the pressed number.
				     //  you can make the cursor move to that item instead of calling (executing)
					 //  it by replacing all the code between 'if (bla){' and '}' with this
				     //  statement MenuChooice=int(key)-'0'
				catch(...){}
			}
		}
	}

	delete MenuOption;
	return 0;
}
string * adminItems() // this function returns a pointer to a string.
{
	string *item=new string[6];
	item[0]="Create Account";
	item[1]="Modify Account";
	item[2]="Delete User Account";
	item[3]="Delete Admin Account";
	item[4]="User menu";
	item[5]="Exit";

	return item;
}
void gotoxy_1(int xpos_1, int ypos_1)  // just take this function as it is.
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos_1; scrn.Y = ypos_1;
	SetConsoleCursorPosition(hOuput,scrn);
}
void ChangeCursorStatus_1(bool Visible)
{
	CONSOLE_CURSOR_INFO *c=new CONSOLE_CURSOR_INFO;
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);

	if (Visible)
	{
		c->bVisible=TRUE;
		c->dwSize=0;//(0) is invild so the default value is set
	}
	else
	{
		c->bVisible=FALSE;
		c->dwSize=1;//it must be assigned to a valid value
	}

	SetConsoleCursorInfo(h,c);
}
void userMenu ()
{
	int selection(0);

	system("cls");

	cout << "1: Reservations" << endl;
	cout << "2: Receipt" << endl;
	cout << "3: Log out" << endl;
	cout << "4: Exit Program" << endl;

	cout << endl << endl << "Enter in a number: " << endl;

	cin >> selection;

	while (selection < 1 || selection > 4)
	{
		cout << "Invalid Input!" << endl;
		cin >> selection;
	}
	do {

		switch(selection)
		{
		case 1: reservation();
			break;
		case 2: receipt();
			break;
		case 3: main();
			break;
		case 4:ExitOption();
			break;
		}

	} while (selection != 4);
}
void help()
{
	system("cls");
	gotoxy(25,10);
	cout<<""<<endl;
	getch();
	system("cls");
}
void modifyAccount ()
{
	system ("cls");
	int i=0,opt=0,count=0;
	string email[ACCOUNT],names[ACCOUNT],password[ACCOUNT];
	cout << "Delete Account" << endl << endl;

	ifstream delete_user;
	delete_user.open("account_info.txt");

	ifstream delete_admin;
	delete_admin.open("admin_account.txt");
	cout<<"email\t\t\t""names\t\t\t""passwords\n\n";

	if(delete_user.is_open())
	{
		while(!delete_user.eof())
		{
			delete_user >> email[i];
			delete_user >> names[i];
			delete_user >> password[i];

			cout<<email[i]<<"\t\t"<<names[i]<<"\t\t"<<password[i]<<endl;
		}

	}
	cout<<"\n"<<"admin accounts\n\n";
	cout<<"email\t\t\t""names\t\t\t""passwords\n\n";
	if(delete_admin.is_open())
	{
		while(!delete_admin.eof())
		{
			delete_admin >> email[i];
			delete_admin >> names[i];
			delete_admin >> password[i];
			i++;
			cout<<email[i]<<"\t\t"<<names[i]<<"\t\t"<<password[i]<<endl;
		}

	}
	cout<<"which account would you like to delete:\t";
	cin>>opt;
	while(opt<i ||opt>i)
	{
		cout<<"error option is out of range\n";
		cout<<"which account would you like to delete:\t";
		cin>>opt;
	}
	email[opt]=count;
	names[opt]=count;
	password[opt]=count;
	cout<<"account:\t"<<opt<<":\thas been deleted\n";
	count--;
	delete_user.close();
	delete_admin.close();
	getch();
}
void delete_User_Account ()
{
	system ("cls");
	int i=0,j=0,opt=0,counter=0;
	string email[ACCOUNT],names[ACCOUNT],password[ACCOUNT];
	cout << "Delete Account" << endl << endl;

	ifstream delete_user;
	delete_user.open("account_info.txt");

	cout<<"\temail\t\t\t"<<"names\t\t\t"<<"passwords\n\n";

	if(delete_user.is_open())
	{
		while(!delete_user.eof())
		{
			i++;
			delete_user >> email[i];
			delete_user >> names[i];
			delete_user >> password[i];

			cout<<(i)<<"\t"<<email[i]<<"\t"<<names[i]<<"\t\t\t"<<password[i]<<endl;
		}

	}
	cout<<"\nwhich account would you like to delete:\t";
	cin>>opt;
	while(opt<1 ||opt>i)
	{
		cout<<"error option is out of range\n";
		cout<<"which account would you like to delete:\t";
		cin>>opt;
	}
	opt--;
	counter=j;
	counter--;
	cout<<counter<<endl;
	email[opt]=email[counter];
	names[opt]=names[counter];
	password[opt]=password[counter];
	counter--;;


	for(i=0;i<=counter;i++)
	{
		cout<<email[i]<<"\t"<<names[i]<<"\t"<<password[i]<<endl;


	}
	_getch();
	cout<<"account:\t"<<opt<<":\thas been deleted\n";
	counter--;
	delete_user.close();
	getch();
}
void delete_admin_account()
{
	int j=0;
	string email[ACCOUNT],names[ACCOUNT],password[ACCOUNT];
	ifstream delete_admin;
	delete_admin.open("admin_account.txt");
	cout<<"\temail\t\t\t"<<"names\t\t\t"<<"passwords\n\n";

	cout<<"\n"<<"admin accounts\n\n";
	cout<<"\temail\t\t\t""names\t\t\t""passwords\n\n";
	if(delete_admin.is_open())
	{
		while(!delete_admin.eof())
		{
			j++;
			delete_admin >> email[j];
			delete_admin >> names[j];
			delete_admin >> password[j];

			cout<<(j)<<"\t"<<email[j]<<"\t\t"<<names[j]<<"\t\t"<<password[j]<<endl;
		}

	}
	delete_admin.close();

}
void reservation ()
{
	int opt=0;

	system ("cls");

	cout << "Reservation" << endl << endl;

	cout << "Do you wish to make a reservation (1)," << endl;
	cout << "Delete an existing reservation (2)," << endl;
	cout << "Change an existing reservation (3)," << endl;
	cout << "Or exit the program (4)?" << endl;
	cin >> opt;

	while (opt < 1 || opt > 4)
	{
		cout << "Invalid Input!" << endl;
		cin >> opt;
	}
	do
	{
		switch(opt)
		{
		case 1:makeReservation();
			break;
		case 2:deleteReservation();
			break;
		case 3:changeReservation();
			break;
		case 4:ExitOption();
			break;
		}
	}while(opt!=4);
}

void makeReservation ()
{
	reserve make;

	ofstream myfile;
	myfile.open("ReservationTextFile.txt", ios::out);

	system ("cls");

	cout << "Make a Reservation" << endl << endl;

	cout << "Enter your name: " << endl;
	cin >> make.name;

	cout << "Enter the time you would like to book: " << endl;
	cin >> make.timeOfReservation;

	cout << "Enter the number of people you are coming with: " << endl;
	cin >> make.people;

	myfile << make.name << endl;
	myfile << make.timeOfReservation << endl;
	myfile << make.people << endl;

	myfile.close();

	getch();
}

void deleteReservation ()
{
	reserve make[ACCOUNT];
	string line, validation, temp;
	int count(0), elements(0), i(0), opt(0), counter(0), deleteline;

	system ("cls");
	
	cout << "Delete a Reservation" << endl << endl;

	ifstream myfile;
	myfile.open("ReservationTextFile.txt");

	istringstream readInformation;
		
	if (myfile.is_open())
	{
		while (!myfile.eof() && i < ACCOUNT)
		{
			getline(myfile, temp);
			
			if (temp.size() == 0)
				break;

			readInformation = istringstream(temp);

			readInformation >> validation;

			if (validation != "$")
			break;
				
			readInformation >> make[i].name;
			readInformation >> make[i].hourOfReservation;
			readInformation >> make[i].minuteOfReservation;
			readInformation >> make[i].timeOfDay;
			readInformation >> make[i].people;

			cout << i << "\t" << make[i].name << "  " << make[i].hourOfReservation << ":" << make[i].minuteOfReservation
			<< make[i].timeOfDay << "  " << make[i].people << endl;

			i++;
		}
		elements = i;
	}

	cout << "Which line do you want to remove?" << endl;
	cin >> deleteline;

	myfile.close();

	ofstream reservations;
	reservations.open("ReservationTextFile.txt");

	if (reservations.is_open())
	{
		for (i = 0; i < elements; i++)
		{
			if (i == deleteline)
			{
				continue;
			}

			reservations << "$ ";
			reservations << make[i].name << " ";
			reservations << make[i].hourOfReservation << " ";
			reservations << make[i].minuteOfReservation << " ";
			reservations << make[i].timeOfDay << " ";
			reservations << make[i].people << endl;

			cout << i << "\t" << make[i].name << "  " << make[i].hourOfReservation << ":" << make[i].minuteOfReservation
			<< make[i].timeOfDay << "  " << make[i].people << endl;
		}
	}

	reservations.close();

	getch();
}

void changeReservation ()
{
	string name;
	int timeOfReservation;
	int people;

	system ("cls");

	cout << "Change a Reservation" << endl << endl;

	ofstream myfile;
	myfile.open("ReservationTextFile.txt", ios::app);

	cout << "Enter your name: " << endl;
	cin >> name;

	myfile << name << "__";

	cout << "Enter the time you would like to book: " << endl;
	cin >> timeOfReservation;

	myfile << timeOfReservation << "__";

	cout << "Enter the number of people you are coming with: " << endl;
	cin >> people;

	myfile << people << endl;

	myfile.close();

	getch();
}

void receipt ()
{
	system ("cls");

	cout << "Receipt" << endl << endl;

	getch();
}
void ExitOption()
{
	cout<<"\nexiting";
	getch();
	exit(0);

}

//Main (UNFINISHED)
//User Menu (DONE)
//Admin Menu (DONE)
//Welcome Screen (DONE)
//Create Account (DONE)
//Log In (DONE)
//Reservation (DONE)
//Make a Reservation (DONE)
//Delete a Reservation (UNFINISHED)
//Change a Reservation (UNFINISHED)
//Receipt (UNFINISHED)
//Exit (DONE)

// 7/12 DONE
