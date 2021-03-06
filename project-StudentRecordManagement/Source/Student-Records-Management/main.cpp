#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <curses.h> //replaced the #include<conio.h>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>


using namespace std;

struct student{
                    int year;
                    int roll_no;
                    char first_name[10], last_name[10];
                    char course[10];
                    int section;
                    double gpa;
               };
/**************************************************************


readOut Function will update the students.txt everytime


***************************************************************/
void readStudents(vector<student>&s, string file);
void readOut(vector<student> s,string file);



int main() {
    FILE *fp, *ft;
    char another, choice;
    /*
        this portion is for the readStudents function
        im reading from the students txt file and pushing it into a vector
    */
    string file = "/home/student/CS254/OpenSourceProject/project-StudentRecordManagement/Libs/students.txt";
    vector<student> students; //vector holding structs
    readStudents(students, file);
    /*
        this portion is readOut function
    */
    
    



    struct student e;
    //vector<double> gpaArray; //this is used to store all gpas
    long int recsize;
    int modified = 0, roll_no;

    fp = fopen("users.txt","rb+"); //was rb+

    if (fp == NULL){
        fp = fopen("users.txt","wb+"); //was wb+

        if (fp == NULL)
        {
             puts("Cannot open file");
             return 0;
        }
    }

    recsize = sizeof(e);

    while(1) {
        system("clear");

        cout << "\t\t====== STUDENT INFORMATION SYSTEM ======";
        cout <<"\n\n                                          ";
        cout << "\n\n";
        cout << "\n \t\t\t 1. Add    Records";
        cout << "\n \t\t\t 2. List   Records";
        cout << "\n \t\t\t 3. Modify Records";
        cout << "\n \t\t\t 4. Delete Records";
	cout << "\n \t\t\t 5. Class  Average";
        cout << "\n \t\t\t 6. Year's Average";
        cout << "\n \t\t\t 7. Exit   Program";
        cout << "\n\n";
        cout << "\t\t\t Select Your Choice :=> ";
        cin >> choice;
        switch(choice)
        {
            case '1' :
            {
                fseek(fp,0,SEEK_END); 
                another ='Y';
                int index = 0;
                while(another == 'Y' || another == 'y')
                {
                    system("clear");
                    cout << "Enter Roll No: ";
                    cin >> e.roll_no;
                    cout << "Enter the First Name : ";
                    cin >> e.first_name;
                    cout << "Enter the Last Name : ";
                    cin >> e.last_name;
                    cout << "Enter the Course    : ";
                    cin >> e.course;
                    cout << "Enter the Section   : ";
                    cin >> e.section;
                    cout << "Enter the GPA  : ";    //added new gpa
                    cin >>e.gpa;
                    cout << "Enter the Class Year   : ";//add class year
                    cin >>e.year;
                    /*
                        new stuff
                    */
                    students.push_back(e);
                    readOut(students,file);//new feature
                    fwrite(&e,recsize,1,fp);
                    cout << "\n Add Another Record (Y/N) ";
                    cin >> another;
                }
                break;
            }
            case '2':
            {
                    system("clear");
                    rewind(fp);
                    cout << "=== View the Records in the Database ===";
                    cout << "\n";
                    cout << setw(15) <<"Year"<<setw(15)<< "Roll No." << setw(15) << "First Name" << setw(15) << " Last Name " << setw(15) << " Course " << setw(15) << " Section " <<setw(15)<< " GPA "<<"\n";
                    while (fread(&e,recsize,1,fp) == 1){
                        cout <<"\n" << setw(15) << e.year<<setw(15) << e.roll_no << setw(15) << e.first_name << setw(15)  << e.last_name << setw(15) << e.course <<  setw(15)  << e.section <<setw(15)<<e.gpa;
                    }
                    cout << "\n\n";
                    //system("pause");
                    break;
            }
            case '3' :
            {
                    system("clear");
                    another = 'Y';
                    while (another == 'Y'|| another == 'y')
                    {
                        cout << "\n Enter the Roll No. of the student : ";
                        cin >> roll_no;
                        rewind(fp);
                        modified = 0;
                        while (fread(&e,recsize,1,fp) == 1){
                            if (e.roll_no == roll_no){
                                cout << "Enter the First Name : ";
                                cin >> e.first_name;
                                cout << "Enter the Last Name : ";
                                cin >> e.last_name;
                                cout << "Enter the Course    : ";
                                cin >> e.course;
                                cout << "Enter the Section   : ";
                                cin >> e.section;
                                cout << "Enter the Class Year   :";
                                cin >> e.year;
                                cout << "Enter the GPA  :";
                                cin >>e.gpa;
                                fseek(fp, - recsize, SEEK_CUR);
                                fwrite(&e,recsize,1,fp);
                                modified = 1;
                                break;
                            }
                          }
                        if(modified == 0){
                            cout << "No matching records found";
                        }
                        cout << "\n Modify Another Record (Y/N)";
                        cin >> another;
                    }
                    break;
            }
            case '4':
            {
                    system("clear");
                    another = 'Y';
                    while (another == 'Y'|| another == 'y')
                    {
                        cout << "\n Enter the Roll No. of the student to delete : ";
                        cin >> roll_no;
                        ft = fopen("temp.txt", "wb"); //was wb
                        rewind(fp);
                        modified = 0;
                        while (fread (&e, recsize, 1, fp) == 1){
                            if (e.roll_no == roll_no){
                                modified = 1;
                            }
                            else
                                fwrite(&e, recsize, 1, ft);
                        }
                        fclose(fp);
                        fclose(ft);
                        remove("users.txt");
                        rename("temp.txt","users.txt");
                        fp=fopen("users.txt","rb"); //was rb
                        if(modified == 0){
                            cout << "No matching records found" << "\n";
                        }
                        else{
                            cout << "Record Deleted successfully" << "\n";
                        }
                        cout << "\n Delete Another Record (Y/N) ";
                        cin >> another;
                    }
                    break;
            }
	case '5':	// calculate the class average		
            {
                    system("clear");
                    rewind(fp);
		                
		                double sum = 0.0;
		                int v = 0;         
                    for(int i = 0; i < students.size(); i++){	 
			 if(students[i].gpa){
				 sum += students[i].gpa;  
				      v++;
			    }
                    }
		                sum /= v;	
				cout << "\t\t\tThe Total Class Average GPA: " << sum << endl;
             
                    break;
            }	
            case '6':			//calculates the average of a year given by the user
            {
		    char ans = 'Y';
		    while(ans == 'Y' || ans == 'y'){
                    system("clear");
                    rewind(fp);
		                int nyear = 0;
		                double total = 0.0;
		                int counter = 0;
		                cout << "Enter desired year average: ";	//gets a year from the user
		                cin >> nyear;
                    for(int i = 0; i < students.size(); i++){	//loops through the vector containing the student data and adding the appropriate GPAs to the total
			                if(students[i].year == nyear){
				                total += students[i].gpa;
				                counter++;
			                }
                    }
		                total /= counter;	//divides the sum of GPAs by the number of students
		                cout << "The class average for the year " << nyear << " is " << total << endl << endl << "Look up another year (Y/N)"; //returns the average
                    		cin >> ans;
			    //system("pause");
		    }
                    break;
            }
            case '7':
            {
                    fclose(fp);
                    cout << "\n\n";
                    cout << "\t\t     THANK YOU FOR USING THIS SOFTWARE";
                    cout << "\n\n";
                    exit(0);
            }
          }
     }


    system("pause");
    return 0;
}
////////////////////////////////////////////////////////////////

void readOut(vector<student> s,string file)
{
    ofstream outFile;
    outFile.open(file);
    for(int a = 0; a < s.size();a++)
    {
        outFile << s.at(a).year<<" "<<s.at(a).roll_no << " "<<s.at(a).first_name << " "<< 
        s.at(a).last_name << " "<< s.at(a).course << " " <<
        s.at(a).section << " " << s.at(a).gpa <<endl;
    }

    outFile.close();
}
