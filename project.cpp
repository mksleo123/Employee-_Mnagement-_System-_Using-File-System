
#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<iomanip>
#include<stdlib.h>
#include<cstring>
#include<string>
#define max 100
#define datafile (char *)"Employee.txt"
#define indexfile (char *)"index.txt"
#define transfile (char *)"salary.txt"
using namespace std;
fstream holdfile, indfile, tfile;
int i,indsize;
char buffer[1000];
char buff[1000];

void header()
{
        cout<<"                                          ____________________________________________________________________________________\n\n";
        cout<<"                                                                        EMPLOYEE MANAGEMENT SYSTEM\n";
        cout<<"                                          ____________________________________________________________________________________\n\n\n";
}

class Employee
{
    char eid[15],name[20],age[5],phone[12],dob[15],address[30];
    public:
    void read();
    void pack();
    friend int search(char*);
    void recDisp(int);
    void remove(int);
    void dataDisp();
    void unpack();
};
class index
{
    public:
    char ieid[15],addr[5];
    void initial();
    void write();
}in,id[max];

class salaries 
{
    public:
    char teid[15],date[20],type[10],amount[10];
    void add();
    void showAll();
    void showOne();
}t;


void index::initial()
{
    indfile.open(indexfile,ios::in);
    if(!indfile)
    {
        indsize=0;
        return;
    }
    for(indsize=0;;indsize++)
    {
        indfile.getline(id[indsize].ieid,15,'|');
        indfile.getline(id[indsize].addr,5,'\n');
        if(indfile.eof())
            break;
    }
    indfile.close();
}
// function to open file
void opener(fstream &sfile,char* fn,ios_base::openmode mode)
{
    sfile.open(fn,mode);
    if(!sfile)
    {
        cout<<"                                          Unable to open the file\n";
        exit(1);
    }
}
// function to write in the index file
void index::write()
{
    opener(indfile,indexfile,ios::out);
    for(i=0;i<indsize;i++)
        indfile<<id[i].ieid<<"|"<<id[i].addr<<"\n"; //  the acno  and the address of the detail of the account Employee will be written in the index file at the last of the file(indsize position)
    indfile.close();
}

int search(char* facno)
{
    int low=0,high=indsize-1;
    int mid;
    while(low<=high)
    {
        mid=(low+high)/2;
        if(strcmp(facno,id[mid].ieid)==0)
            return mid;
        else if(strcmp(facno,id[mid].ieid)>0)
            low=mid+1;
        else
            high=mid-1;
    }
    return -1;
}

// function to read
void Employee::read()
{
    int k;
    cin.ignore();
    cout<<"                                          Enter the Employee ID\n";
    cout<<"                                          ";
    cin>>eid;
    if(search(eid)>=0)
    {
        cout<<"                                          The Employee ID Already Exists\n";
        return;
    }
    for(i=indsize;i>0;i--)
    {
        if(strcmp(eid,id[i-1].ieid)<0)
            id[i]=id[i-1];
        else
            break;
    }  // i will be at the positon where the ID of the employee to be inserted in the index file
    opener(holdfile,datafile,ios::app);
    cout<<"\n                                          Enter the Name\n";
    cout<<"                                          ";
    cin>>name;
    cout<<"\n                                          Enter the age\n";
    cout<<"                                          ";
    cin>>age;
    cout<<"\n                                          Enter the phone number\n";
    cout<<"                                          ";
    cin>>phone;
    cout<<"\n                                          Enter Date of Birth\n";
    cout<<"                                          ";
    cin>>dob;
    cout<<"\n                                          Enter the Address\n";
    cout<<"                                          ";
    cin>>address;
    pack(); //the data will be inseted in the buffer
    holdfile.seekg(0,ios::end);  //seek to 0 character from the end of the file
    k=holdfile.tellg();  //current position of the pointer that is there in the Employeefile file
    holdfile<<buffer<<endl;  //holdfile will be at the and of file and the data in the buffer will be written at the end of the file
    strcpy(id[i].ieid,eid);  //eid will be copied to the current position of indsize
    itoa(k,id[i].addr,10);  //the integer value k(starting address of the of the details of the Employee that is entered) will be converted into string and will be copied to the address field of the indexfile in the form of decimal(10) compatibal string
    indsize++;
}
// function to pack
void Employee::pack()
{
    strcpy(buffer,eid); strcat(buffer,"|");
    strcat(buffer,name); strcat(buffer,"|");
    strcat(buffer,age); strcat(buffer,"|");
    strcat(buffer,phone); strcat(buffer,"|");
    strcat(buffer,dob); strcat(buffer,"|");
    strcat(buffer,address); strcat(buffer,"|");
}

// function to record display
void Employee::recDisp(int pos)
{
    opener(holdfile,datafile,ios::in);
    holdfile.seekg(atoi(id[pos].addr),ios::beg);
    cout<<"\n                                          The searched record details are:\n";
    cout<<"                                          --------------------------------\n\n";
    unpack();
}
// function to Remove
void Employee::remove(int pos)
{
    opener(holdfile,datafile,ios::in|ios::out);
    holdfile.seekg(atoi(id[pos].addr),ios::beg);
    holdfile.put('$');
    for(i=pos;i<indsize;i++)
        id[i]=id[i+1];
    indsize--;
}
// function to data display
void Employee::dataDisp()
{
    cout<<setiosflags(ios::left);
    int c=1;
    while(!holdfile.eof())
    {
            unpack();
    }
}
// function to unpack
void Employee::unpack()
{
    holdfile.getline(buffer,1000,'\n'); // the content of one employee in the datafile will be stored in the buffer
    i=0;
    if(buffer[i]!='$')  //$ denotes the data is deleted
    {
        int j=0;
        while(buffer[i]!='\0')
        {   
            if(j==0)
            {
                cout<<"\n                                          EMPLOYEE ID : ";
                j++;
            }
            if(buffer[i]=='|')
            {
                cout<<endl;
                switch(j)
                {
                    case 1 :cout<<"\n                                          NAME           : ";
                            j++;
                            break;
                    case 2 :cout<<"\n                                          AGE            : ";
                            j++;
                            break;
                    case 3 :cout<<"\n                                          PHONE NUMBER   : ";
                            j++;
                            break;
                    case 4 :cout<<"\n                                          DATE OF BIRTH  : ";
                            j++;
                            break;
                    case 5 :cout<<"\n                                          ADDRESS        : ";
                            j++;
                            break;
                }
            }
            else
                cout<<buffer[i];
            i++;
        }
        cout<<endl;
    }
}

//Transaction cass functions

//For adding a salaries
void salaries::add()
{
    tfile.open(transfile,ios::app);
    cin.ignore();
    cout<<"                                          Enter the Salary details"<<endl;
    cout<<"                                          -----------------------------\n\n";
    cout<<"\n                                          Enter the Employee ID"<<endl;
    cout<<"                                          ";
    cin>>teid;
    cout<<"\n                                          Enter the Date of issuing"<<endl;
    cout<<"                                          ";
    cin>>date;
    cout<<"\n                                          Enter the type of Salary"<<endl;
    cout<<"                                          ";
    cin>>type;
    cout<<"\n                                          Enter the Amount"<<endl;
    cout<<"                                          ";
    cin>>amount;
    strcpy(buff,teid); strcat(buff,"|");
    strcat(buff,date); strcat(buff,"|");
    strcat(buff,type); strcat(buff,"|");
    strcat(buff,amount); strcat(buff,"|");
    tfile<<buff<<endl;
}

//For showing all the transactions
void salaries::showAll()
{
    cout<<setiosflags(ios::left);
    tfile.open(transfile,ios::in);
    if(tfile.eof())
    {
        cout<<"                                          File has no entry\n";
        return;
    }
    cout<<"                                          The Salary Transaction Details:"<<endl;
    cout<<"                                          ------------------------\n\n";
    while(!tfile.eof())
    {
            tfile.getline(buff,100,'\n');
            int i=0;
            int j=0;
            while(buff[i]!='\0')
            {
                if(j==0)
                {
                    cout<<"                                          Employee ID  : ";
                    j++;
                }
                if(buff[i]=='|')
                {
                    cout<<endl;
                    switch(j)
                    {
                        case 1 :cout<<"                                          Date            : ";
                                j++;
                                break;
                        case 2 :cout<<"                                          Type            : ";
                                j++;
                                break;
                        case 3 :cout<<"                                          Amount          : ";
                                j++;
                                break;
                    }
                }
                else
                    cout<<buff[i];
                i++;
            }
            cout<<endl;
    }
}

//For showing the Transaction of a particular Employee ID
void salaries::showOne()
{
    tfile.open(transfile,ios::in);
    int f=0;
    cout<<"                                          Enter the Employee ID"<<endl;
    cout<<"                                          ";
    char oacno[10];
    cin>>oacno;
    int amount=0;
    while(!tfile.eof())
    {
        int i=0;
        int fl=0;
        int c=0;
        tfile.getline(buff,100,'\n');
        while(buff[i]!='|')
        {
            if(buff[i]!=oacno[i])
            {
                fl=1;
                break;
            }
            i++;
        }
        i++;
        char am[10];
        char ty[20];
        int m=0;
        int n=0;
        if(fl==0)
        {
            f=1;
            int j=0;
            while(buff[i]!='\0')
            {
                if(j==0)
                {
                    cout<<"                                          Date of salary Transaction : ";
                    j++;
                }
                if(buff[i]=='|')
                {
                    cout<<endl;
                    switch(j)
                    {
                        case 1 :cout<<"                                          Type of Transaction : ";
                                j++;
                                break;
                        case 2 :cout<<"                                          Amount              : ";
                                j++;
                                break;
                    }
                    c++;
                }
                else
                {
                    cout<<buff[i];
                    if(c==1)
                    {
                        ty[m]=buff[i];
                        m++;
                    }
                    if(c==2)
                    {
                        am[n]=buff[i];
                        n++;
                    }
                }
                ty[m]='\0';
                am[n]='\0';

                i++;
            }
            
            double amo=stod(am);
            if(strcmp(ty,"Credit")==0)
                amount=amount+amo;
            else
                amount=amount-amo;
        }
        cout<<endl;
    }
    cout<<"                                          Total Amount of the Employee is --"<<amount<<endl;
    if(f==0)
        cout<<"No salaries of the given Employee ID"<<endl;
}

int main()
{
    int ch,pos,flag;
    char seid[15];
    Employee h;
    system("cls");
    in.initial();
    for(;;)
    {
        header();
        cout<<"                                          1.ADD Employee\n\n";
        cout<<"                                          2.Display all the Employees in the compamy\n\n";
        cout<<"                                          3.Search a particular Employee\n\n";
        cout<<"                                          4.Delete the details of existing  Employee\n\n";
        cout<<"                                          5.Add a salary Transaction \n\n";
        cout<<"                                          6.Show all the salaries transactions \n\n";
        cout<<"                                          7.Show salaries of a particular Employee\n\n";
        cout<<"                                          8.exit\n";
        cout<<"                                          ";
        cin>>ch;
        switch(ch)
        {
            case 1: system("cls");
                    header();
                    cout<<"                                          Enter the details of the new Employee\n";
                    cout<<"                                          ------------------------------------\n\n";
                    h.read();
                    in.write();
                    break;
            case 2: system("cls");
                    header();
                    opener(holdfile,datafile,ios::in);
                    cout<<endl<<"\n                                          Account Employee Details\n";
                    cout<<"                                          ----------------------\n";
                    h.dataDisp();
                    cout<<endl<<"                                          Index file details are:\n\n";
                    cout<<"                                          Employee ID"<<"   Address";
                    for(i=0;i<indsize;i++)
                    {
                        cout<<endl<<"                                              "<<id[i].ieid<<"            "<<id[i].addr<<endl;
                    }
                    break;
            case 3: system("cls");
                    header();
                    cout<<"                                          Enter the Employee ID to be searched\n\n";
                    cout<<"                                          ";
                    cin>>seid;
                    flag=search(seid);
                    if(flag==-1)
                        cout<<"                                          Record Not found\n\n";
                    else
                        h.recDisp(flag);
                    break;
            case 4: system("cls");
                    header();
                    cout<<"                                          Enter the employee ID to be delete from the record\n";
                    cout<<"                                          ";
                    cin>>seid;
                    pos=search(seid);
                    if(pos==-1)
                        cout<<"                                          Record not found\n";
                    else
                    {
                        h.remove(pos);
                        in.write();
                    }
                    break;
            case 5: system("cls");
                    header();
                    t.add();
                    break;
            case 6: system("cls");
                    header();
                    t.showAll();
                    break;
            case 7: system("cls");
                    header();
                    t.showOne();
                    break;
            default: exit(0);
        }
        holdfile.close();
        tfile.close();
    }
}
