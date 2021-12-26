#include<iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<iomanip>
using namespace std;
int k=7,r=0,flag=0;
COORD coord = {0, 0};

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct date
{
    int mm,dd,yy;
};

ofstream fout;
ifstream fin;

class item
{
    int itemno;
    char name[25];
    date d;
public:
    void add()
    {
        cout<<"Shomere mahsull: ";
        cin>>itemno;
        cout<<"Esme mahsull: ";
        cin>>name;

    }
    void show()
    {
        cout<<"\n\shomare mahsull: ";
        cout<<itemno;
        cout<<"\n\n\esme mahsull: ";
        cout<<name;
    }
    void report()
    {
        gotoxy(3,k);
        cout<<itemno;
        gotoxy(13,k);
        puts(name);
    }
    int retno()
    {
        return(itemno);

    }

};

class amount: public item
{
    float price,qty,gross,dis,netamt;
public:
    void add();
    void show();
    void report();
    void calculate();
    void pay();
    float retnetamt()
    {
        return(netamt);
    }
} amt;

void amount::add()
{
    item::add();
    cout<<"\n\n\gheymat: ";
    cin>>price;
    cout<<"\n\n\tedad: ";
    cin>>qty;
    cout<<"\n\n\darsad off: ";
    cin>>dis;
    calculate();
    fout.write((char *)&amt,sizeof(amt));
    fout.close();
}
void amount::calculate()
{
    netamt=qty*(gross-(gross*(dis/100)));
}
void amount::show()
{
    fin.open("itemstore.dat",ios::binary);
    fin.read((char*)&amt,sizeof(amt));
    item::show();
    cout<<"\n\n\tNet amount: ";
    cout<<netamt;
    fin.close();
}

void amount::report()
{
    item::report();
    gotoxy(23,k);
    cout<<price;
    gotoxy(33,k);
    cout<<qty;
    gotoxy(52,k);
    cout<<dis;
    gotoxy(64,k);
    cout<<netamt;
    k=k+1;
    if(k==50)
    {
        gotoxy(25,50);
        cout<<"PRESS ANY KEY TO CONTINUE...";
        getch();
        k=7;
        system("cls");
        gotoxy(30,3);
        cout<<" JOZIEATE MAHSULL ";
        gotoxy(3,5);
        cout<<"SHOMAREH";
        gotoxy(13,5);
        cout<<"ESME MAHSULL";
        gotoxy(23,5);
        cout<<"GHEYMATE MAHSULL";
        gotoxy(33,5);
        cout<<"TEDAD";
        gotoxy(52,5);
        cout<<"DEDUCTION";
        gotoxy(64,5);
        cout<<"NET AMOUNT";
    }
}

void amount::pay()
{
    show();
    cout<<"\n\n\n\t\t*********************************************";
    cout<<"\n\t\t                 DETAILS                  ";
    cout<<"\n\t\t*********************************************";
    cout<<"\n\n\t\ghymat                     :"<<price;
    cout<<"\n\n\t\tedad                  :"<<qty;
    cout<<"\n\t\darsad takhfif         :"<<dis;
    cout<<"\n\n\n\t\tNET AMOUNT              :Rs."<<netamt;
    cout<<"\n\t\t*********************************************";
}

int main()
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout<<setprecision(2);
    fstream tmp("temp.dat",ios::binary|ios::out);
menu:
    system("cls");
    gotoxy(25,2);
    cout<<"Super Market Billing ";
    gotoxy(25,3);
    cout<<"===========================\n\n";
    cout<<"\n\t\t1.faktor\n\n";
    cout<<"\t\t2.ezafe-virayesh va hazfe mahsull\n\n";
    cout<<"\t\t3.jozieate item morede nazar\n\n";
    cout<<"\t\t4.Exit\n\n";
    cout<<"\t\lotfan gozine morede nazare khodra entkhab konid: ";
    int ch,ff;
    float gtotal;
    cin>>ch;
    switch(ch)
    {
    case 1:
ss:
        system("cls");
        gotoxy(25,2);
        cout<<"Bill Details";
        gotoxy(25,3);
        cout<<"================\n\n";
        cout<<"\n\t\t1.hame item ha\n\n";
        cout<<"\t\t2.bazgasht b meno asli\n\n";
        cout<<"\t\t:lotfan gozine morede nazare khodra entkhab konid: ";
        int cho;
        cin>>cho;
        if(cho==1)
        {
            system("cls");
            gotoxy(30,3);
            cout<<" FACTOR ";
            gotoxy(3,5);
            cout<<"SHOMARE MAHSULL";
            gotoxy(13,5);
            cout<<"ESM";
            gotoxy(23,5);
            cout<<"GHEYMAT";
            gotoxy(33,5);
            cout<<"TEDAD";
            gotoxy(52,5);
            cout<<"TAKHFIF %";
            gotoxy(64,5);
            cout<<"NET AMOUNT";
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\nFile Not Found...";
                goto menu;
            }
            fin.seekg(0);
            gtotal=0;
            while(!fin.eof())
            {
                fin.read((char*)&amt,sizeof(amt));
                if(!fin.eof())
                {
                    amt.report();
                    gtotal+=amt.retnetamt();
                    ff=0;
                }
                if(ff!=0) gtotal=0;
            }
            gotoxy(17,k);
            cout<<"\n\n\n\t\t\MBLAGHE KOLL"<<gtotal;
            getch();
            fin.close();
        }
        if(cho==2)
        {
            goto menu;
        }
        goto ss;
    case 2:
db:
        system("cls");
        gotoxy(25,2);
        cout<<"virayeshe surat hesab";
        gotoxy(25,3);
        cout<<"=================\n\n";
        cout<<"\n\t\t1.ezafe kardane etelaate mahsul\n\n";
        cout<<"\t\t2.virayeshe etelaate mahsull\n\n";
        cout<<"\t\t3.hazfe etelaate mahsull\n\n";
        cout<<"\t\t4.bazgasht b meno asli ";
        int apc;
        cin>>apc;
        switch(apc)
        {
        case 1:
            fout.open("itemstore.dat",ios::binary|ios::app);
            amt.add();
            cout<<"\n\t\mahsulle jadid ba movafaghiat ezafe shod!";
            getch();
            goto db;

        case 2:
            int ino;
            flag=0;
            cout<<"\n\n\shomare y mahsulli k mikhahid virayesh konid ra vared konid :";
            cin>>ino;
            fin.open("itemstore.dat",ios::binary);
            fout.open("itemstore.dat",ios::binary|ios::app);
            if(!fin)
            {
                cout<<"\n\nFile Not Found...";
                goto menu;
            }
            fin.seekg(0);
            r=0;
            while(!fin.eof())
            {
                fin.read((char*)&amt,sizeof(amt));
                if(!fin.eof())
                {
                    int x=amt.item::retno();
                    if(x==ino)
                    {
                        flag=1;
                        fout.seekp(r*sizeof(amt));
                        system("cls");
                        cout<<"\n\t\etelaate mojod\n";
                        amt.show();
                        cout<<"\n\n\t\etelaate jadid\n";
                        amt.add();
                        cout<<"\n\t\etelaat beruz resani shodand";
                    }
                }
                r++;
            }
            if(flag==0)
            {
                cout<<"\n\t\in item mojod nist...lotfan iteme jadid ra vared konid!";
                getch();
                goto db;
            }
            fin.close();
            getch();
            goto db;

        case 3:
            flag=0;
            cout<<"\n\n\shomare y itemi k mikhahid hazf konid ra vared konid :";
            cin>>ino;
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\nFile Not Found...";
                goto menu;
            }
            fin.seekg(0);
            while(fin.read((char*)&amt, sizeof(amt)))
            {
                int x=amt.item::retno();
                if(x!=ino)
                    tmp.write((char*)&amt,sizeof(amt));
                else
                {
                    flag=1;
                }
            }
            fin.close();
            tmp.close();
            fout.open("itemstore.dat",ios::trunc|ios::binary);
            fout.seekp(0);
            tmp.open("temp.dat",ios::binary|ios::in);
            if(!tmp)
            {
                cout<<"Error in File";
                goto db;
            }
            while(tmp.read((char*)&amt,sizeof(amt)))
                fout.write((char*)&amt,sizeof(amt));
            tmp.close();
            fout.close();
            if(flag==1)
                cout<<"\n\t\item ba movafaghiat hazf shod";
            else if (flag==0)
                cout<<"\n\t\item mojod nis lotfan mojaddadan talash konid";
            getch();
            goto db;
        case 4:
            goto menu;
        default:
            cout<<"\n\n\t\dobare emtehan konid";
            getch();
            goto db;
        }
    case 3:
        system("cls");
        flag=0;
        int ino;
        cout<<"\n\n\t\shomare y item ra vared konid :";
        cin>>ino;
        fin.open("itemstore.dat",ios::binary);
        if(!fin)
        {
            cout<<"\n\nFile Not Found...\nProgram Terminated!";
            goto menu;
        }
        fin.seekg(0);
        while(fin.read((char*)&amt,sizeof(amt)))
        {
            int x=amt.item::retno();
            if(x==ino)
            {
                amt.pay();
                flag=1;
                break;
            }
        }
        if(flag==0)
            cout<<"\n\t\item mojod nist lotfan mojadadan say konid";
        getch();
        fin.close();
        goto menu;
    case 4:
        system("cls");
        gotoxy(20,20);
        cout<<"mikhahid kharej shavid  (Y/N)?";
        char yn;
        cin>>yn;
        if((yn=='Y')||(yn=='y'))
        {
            gotoxy(12,20);
            system("cls");
            cout<<"************************** THANKS **************************************";
            getch();
            exit(0);
        }
        else if((yn=='N')||(yn=='n'))
            goto menu;
        else
        {
            goto menu;
        }
    default:
        cout<<"\n\n\t\dobare emtehan konid!";
        getch();
        goto menu;
    }
    return 0;
}
