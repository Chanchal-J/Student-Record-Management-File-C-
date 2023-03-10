//Project on Student Record Management - Data File Handling
#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdlib.h>

using namespace std;

class Student
{
	string roll_no;
	string course_id;
	string name;
	char gender;
	int year_of_passing;
	float cgpa;
	
	public:
		void getData();
		void showData();
		string getRollno() {return roll_no; }
		string getCourseID() {return course_id; }
		string getName() {return name; }
		char getGender() {return gender; }
		int getYear() {return year_of_passing; }
		float getCGPA() {return cgpa; }
}s;

void Student::getData()
{
	cout<<"\n\nEnter Student Details......\n";
	cout<<"Enter Roll No.          : ";
	cin>>roll_no;
	cout<<"Enter Full Name         : ";
	cin.ignore();
	getline(cin,name);
	cout<<"Enter Gender (M/F)      : ";
	cin>>gender;
	cout<<"Enter Year1 of passing   : ";
	cin>>year_of_passing;
	cout<<"Enter Course Code       : ";
	cin.ignore();
	getline(cin,course_id);
	cout<<"Enter CGPA              : ";
	cin>>cgpa;
	cout<<endl;
}

void Student::showData()
{
	cout<<"\n\n.......Student Details......\n";
	cout<<"Roll Number       : "<<roll_no<<endl;
	cout<<"Full Name         : "<<name<<endl;
	cout<<"Gender            : "<<gender<<endl;
	cout<<"Year of Passing   : "<<year_of_passing<<endl;
	cout<<"Course Code       : "<<course_id<<endl;
	cout<<"CGPA              : "<<cgpa<<endl;
	cout<<endl;
}

void addData()
{
	ofstream fout;
	fout.open("D:\\Resume Projects\\Student Record Management\\Students.dat",ios::binary|ios::out|ios::app);
	s.getData();
	fout.write((char*)&s,sizeof(s));
	fout.close();
	cout<<"\n\nData Successfully Saved to File....\n";
}

void displayData()
{
	ifstream fin;
	fin.open("D:\\Resume Projects\\Student Record Management\\Students.dat",ios::in|ios::binary);
	while(fin.read((char*)&s,sizeof(s)))
	{
		s.showData();
	}
	fin.close();
	cout<<"\n\nData Reading from File Successfully Done....\n";
}

void searchData()
{
	string n;
	int flag=0;
	ifstream fin;
	fin.open("D:\\Resume Projects\\Student Record Management\\Students.dat",ios::in|ios::binary);
	cout<<"Enter Roll Number you want to search : ";
	cin>>n;
	
	while(fin.read((char*)&s,sizeof(s)))
	{
		if(n==s.getRollno())
		{
			cout<<"The Details of Roll No. "<<n<<" shown herewith:\n";
			s.showData();
			flag++;
		}
	}
	fin.close();
	if(flag==0)
		cout<<"The Roll No. "<<n<<" not found....\n\n";
	cout<<"\n\nData Reading from File Successfully Done....\n";
}

void deleteData()
{
	string n;
	int flag=0;
	ifstream fin;
	ofstream fout;

	fin.open("D:\\Resume Projects\\Student Record Management\\Students.dat",ios::in|ios::binary);
	fout.open("D:\\Resume Projects\\Student Record Management\\TempStud.dat",ios::out|ios::app|ios::binary);

	cout<<"Enter Roll Number you want to move to Trash : ";
	cin>>n;
	
	while(fin.read((char*)&s,sizeof(s)))
	{
		if(n==s.getRollno())
		{
			cout<<"The Following Roll No. "<<n<<" has been moved to Trash:\n";
			s.showData();
			flag++;
		}
		else
		{
			fout.write((char*)&s,sizeof(s));
		}
	}
	fout.close();
	fin.close();
	if(flag==0)
		cout<<"The Roll No. "<<n<<" not found....\n\n";
	remove("D:\\Resume Projects\\Student Record Management\\Students.dat");
	rename("D:\\Resume Projects\\Student Record Management\\TempStud.dat","D:\\Resume Projects\\Student Record Management\\Students.dat");
}

void modifyData()
{
	string n;
	int flag=0, pos;
	fstream fio;

	fio.open("D:\\Resume Projects\\Student Record Management\\Students.dat",ios::in|ios::out|ios::binary);
	
	cout<<"Enter Roll Number you want to Modify : ";
	cin>>n;
	
	while(fio.read((char*)&s,sizeof(s)))
	{
		pos=fio.tellg();
		if(n==s.getRollno())
		{
			cout<<"The Following Roll No. "<<n<<" will be modified with new data:\n";
			s.showData();
			cout<<"\n\nNow Enter the New Details....\n";
			s.getData();
			fio.seekg(pos-sizeof(s));
			fio.write((char*)&s,sizeof(s));
			flag++;
		}
	}
	fio.close();
	
	if(flag==0)
		cout<<"The Roll No. "<<n<<" not found....\n\n";
}

void project()
{
	int ch;
	do
	{
		system("cls");
		cout<<"...............STUDENT RECORD SYSTEM..............\n";
		cout<<"======================================================\n";
		cout<<"0. Exit from Program\n";
		cout<<"1. Write Data to File\n";
		cout<<"2. Read Data From File\n";
		cout<<"3. Search Data From File\n";
		cout<<"4. Delete Data From File\n";
		cout<<"5. Modify Data in File\n";
		cout<<"Enter your choice  : ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
			case 0: break;
			case 1: addData(); break;
			case 2: displayData(); break;
			case 3: searchData(); break;
			case 4: deleteData(); break;
			case 5: modifyData(); break;
			default: cout<<"\n\nInvalid Choice\n\n"; break;
		}
		system("pause");
	}while(ch);
}

int main()
{
	project();
}
