#include <iostream>
#include <conio.h>
#include <fstream>
#define YELLOW  "\033[33m"
#define PURPLE  "\033[35m"
#define GREEN   "\033[32m"
#define WHITE   "\033[37m"
#define BLUE    "\033[34m"
#define RED     "\033[31m"

using namespace std;

class contact{
private:
char firstName[50], lastName[50], address[50], email[50];

	long long phNo;
		
public:
	void createContact() {
		cout<<"Enter your first name: ";
		cin>>firstName;
		cout<<"Enter your last name: ";
		cin>>lastName;
		cout<<"Enter phone: ";
		cin>>phNo;
		cout<<"Enter address: ";
		cin>>address;
		cout<<"Enter email: ";
		cin>>email;	
	}
		
	void showContact() {
		cout<<"Name: "<<firstName<<" "<<lastName<<endl;
		cout<<"Phone: "<<phNo<<endl;
		cout<<"Address: "<<address<<endl;
		cout<<"Email: "<<email<<endl;	
	}
		
	void writeOnFile() {
		char ch;
		ofstream file1;
		file1.open("contact.dat",ios::binary|ios::app);

		do {
			createContact();
			file1.write(reinterpret_cast<char*>(this),sizeof(*this));
			cout<<"Do you have next data?(y/n)";
			cin>>ch;
		}while(ch=='y');

		cout<<YELLOW<<"Contact has been Sucessfully Created...";
		file1.close();
	}
		
	void readFromFile() {
		ifstream file2;
		file2.open("contact.dat",ios::binary);

		cout<<WHITE<<"\n================================\n";
		cout<<WHITE<<"LIST OF CONTACTS";
		cout<<WHITE<<"\n================================\n";

		while(!file2.eof()) {
			if(file2.read(reinterpret_cast<char*>(this),sizeof(*this)))
			{
				showContact();
				cout<<"\n================================\n";
			}
		}
		file2.close();
	}
		
	void searchOnFile() {
		ifstream file3;
		long long phone;
		cout<<"Enter phone no.: ";
		cin>>phone;
		file3.open("contact.dat",ios::binary);

		while(!file3.eof()) {
			if(file3.read(reinterpret_cast<char*>(this), sizeof(*this))) {
				if (phone==phNo) {
					showContact();
					return;
				}
			}
		}
		cout<<"\n\n No record not found";
		file3.close(); 
	}
	
	void deleteFromFile() {
		long long num;
		bool flag = false;
		ofstream file4;
		ifstream file5;

		file5.open("contact.dat",ios::binary);
		file4.open("temp.dat",ios::binary);

		cout<<"Enter phone no. to delete: ";
		cin>>num;

		while(!file5.eof()) {
			if(file5.read(reinterpret_cast<char*>(this),sizeof(*this))) {
				if(phNo!=num) {
					file4.write(reinterpret_cast<char*>(this),sizeof(*this));
				}
				else 
					flag = true;
			}
		}
		file5.close();
		file4.close();
		remove("contact.dat");
		rename("temp.dat","contact.dat");

		flag==true?
		cout<<endl<<endl<<"\tContact Deleted...":
		cout<<endl<<endl<<"\tContact Not Found...";
	}	
	
		
	void editContact() {
		long long num;
		fstream file6;

		cout<<"Edit contact";
		cout<<"\n===============================\n\n";
		cout<<"Enter the phone number to be edit: ";
		cin>>num;

		file6.open("contact.dat",ios::binary|ios::out|ios::in);

		while(!file6.eof()) {
			if(file6.read(reinterpret_cast<char*>(this),sizeof(*this))) {
				if (phNo==num) {
					cout<<"Enter new record\n";
					createContact();
					int pos=-1*sizeof(*this);
					file6.seekp(pos,ios::cur);
					file6.write(reinterpret_cast<char*>(this),sizeof(*this));
					cout<<endl<<endl<<"\t Contact Successfully Updated...";
					return;
				}
			}
		}
		cout<<RED<<"\n\n No record not found";
		file6.close(); 
	}
};

int main() {
	system("cls");
    cout<<GREEN<<"\n\n\n\n\n\n\n\n\t\t\t * WELCOME TO CONTACT MANAGEMENT SYSTEM *"<<endl;
    cout<<GREEN<<"\t\t\t\t Press Enter to Proceed";
	getch();

	while(1) {
		contact c1;
		int choice;

		system("cls");
		cout<<"\nCONTACT MANAGEMENT SYSTEM";
        cout<<"\n\nMAIN MENU";
		cout<<"\n=====================\n";
        cout<<"[1] Add a new Contact\n";
        cout<<"[2] List all Contacts\n";
        cout<<"[3] Search for contact\n";
        cout<<"[4] Delete a Contact\n";
        cout<<"[5] Edit a Contact\n";
        cout<<"[0] Exit";
		cout<<"\n=====================\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice) {
        	case 1:
        		system("cls");
        		c1.writeOnFile();
        		break;

        	case 2:
				system("cls");
        		c1.readFromFile();
        		break;

			case 3:
        		system("cls");
        		c1.searchOnFile();
        		break;

        	case 4:
				system("cls");
        		c1.deleteFromFile();
        		break;

        	case 5:
			    system("cls");
        		c1.editContact();
        		break;

        	case 0:
        		system("cls");
        		cout<<"\n\n\n\t\t\tThank You!!."<<endl<<endl;
        		exit(0);
        		break;

        	default:
				continue;	
		}

		int opt;
		cout<<PURPLE<<"\n\n..::Enter the Choice:\n[1] Main Menu\t\t[0] Exit\n";
		cin>>opt;

		switch (opt) {
			case 0:
        		system("cls");
        		cout<<"\n\n\n\t\t\tThank!!."<<endl<<endl;
        		exit(0);
        		break;

			default:
				continue;
		}
	}

	return 0;
}
