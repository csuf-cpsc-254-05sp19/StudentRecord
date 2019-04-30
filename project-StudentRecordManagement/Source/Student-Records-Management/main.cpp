#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <curses.h> //replaced the #include<conio.h>
#include <iomanip>

using namespace std;

struct student{
                    int roll_no;
                    char first_name[10], last_name[10];
                    char course[10];
                    int section;
               };
int main() {
    FILE *fp, *ft;
    char another, choice;
    struct student e;
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
        cout << "\n \t\t\t 5. Exit   Program";
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
                    cout << setw(15) << "Roll No." << setw(15) << "First Name" << setw(15) << " Last Name " << setw(15) << " Course " << setw(15) << " Section " << "\n";
                    while (fread(&e,recsize,1,fp) == 1){
                        cout <<"\n" << setw(15) << e.roll_no << setw(15) << e.first_name << setw(15)  << e.last_name << setw(15) << e.course <<  setw(15)  << e.section;
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
            case '5':
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
