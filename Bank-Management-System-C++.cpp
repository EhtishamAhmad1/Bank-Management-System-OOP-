#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <cctype>
#include <iomanip>
#include <stdio.h>

using namespace std;

class bank
{
private:
    int acc_no, amount;
    char name[100];
    char acc_type[10];

public:
    void create_acc();
    void modify_acc();
    int account();
    void show_acc();
    // void close_acc();
    void all_acc() const;
    void dep(int);
    void with(int);
    int amnt();
};

///////////creating account//////////
void bank::create_acc()
{
    cout << "You selected to create a new account\n";
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter account number: ";
    cin >> acc_no;
    cout << "Enter the type of account (Checking 'C'/Savings 'S') you want to create: ";
    cin >> acc_type;
    cout << "Enter initial amount in the account: ";
    cin >> amount;
    cout << "\t\tAccount created\n\n";
}

////////////modyfying account/////////////////
void bank::modify_acc()
{
    cout << "Enter new name for account holder: ";
    cin >> name;
    cout << "Enter new account number: ";
    cin >> acc_no;
    cout << "Enter new account type: ";
    cin >> acc_type;
    cout << "Enter new deposit amount for account: ";
    cin >> amount;
    cout << "\t\tAccount updated\n\n";
}

int bank::account()
{
    return acc_no;
}

void bank::show_acc()
{
    cout << "\n\t\t\tAccount No. : " << acc_no;
    cout << "\n\t\t\tAccount Holder Name : ";
    cout << name;
    cout << "\n\t\t\tType of Account : " << acc_type;
    cout << "\n\t\t\tBalance amount : " << amount << "\n\n";
}

void bank::all_acc() const
{
    cout << "\t\t" << acc_no << " " << name << " \t" << acc_type << " \t" << amount << endl;
}

void bank::dep(int x)
{
    amount += x;
}

void bank::with(int x)
{
    amount -= x;
}

int bank::amnt()
{
    return amount;
}

void write_acc();
void read_acc();
void up_acc();
void delete_acc();
void dep_with(int, int);
void display_all();

///////////MAIN PROGRAM////////////
int main()
{
    char ch;
    char ch2;
    char ch3;
    int num;
    string pass;
    bank b;

    cout << "\t\t\t\t--------------------------\n";
    cout << "\t\t\t\t\tBANK SYSTEM\n";
    cout << "\t\t\t\t--------------------------\n";
    cout << "\t\t\t\t\t WELCOME\n";
    do
    {
        cout << "\t\t\t\t1-Login as an Employee\n";
        cout << "\t\t\t\t2-Login as a Customer\n";
        cout << "\t\t\t\t3-Exit\n";
        /*


        cout << "\t\t\t8-Exit\n";*/

        cout << "\t\t\tEnter your choice :";
        cin >> ch;
        switch (ch)
        {
        case '1':
            do
            {
                cout << "\n\t\t\tEnter password to login as an Employee : ";
                cin >> pass;
                if (pass != "abc123")
                {
                    cout << "\n\t\t\tWrong password enter again \n";
                }
            } while (pass != "abc123");

            cout << "\n\t\t\tYou are logged in as an Employee \n";
            do
            {

                cout << "\t\t\t1-Add Account\n";
                cout << "\t\t\t2-Modify Account\n";
                cout << "\t\t\t3-Close account\n";
                cout << "\t\t\t4-All Account Holder List\n";
                cout << "\t\t\t5-Exit\n";

                cin >> ch2;
                switch (ch2)
                {
                case '1':
                    write_acc();
                    break;
                case '2':
                    up_acc();
                    break;
                case '3':
                    delete_acc();
                    break;
                case '4':
                    display_all();
                    break;
                default:
                    cout << "\t\t\tPlease choose correct option\n";
                }

            } while (ch2 != '5');

            break;
        case '2':
            cout << "\n\t\t\tYou are logged in as a Customer\n";

            do
            {
                cout << "\t\t\t1-Withdraw Amount\n";
                cout << "\t\t\t2-Deposit Amount\n";
                cout << "\t\t\t3-Balance Enquiry\n";
                cout << "\t\t\t4-Exit\n";
                cin >> ch3;
                switch (ch3)
                {
                case '1':
                    cout << "Enter account number to withdraw ammount: ";
                    cin >> num;
                    dep_with(num, 1);
                    break;
                case '2':
                    cout << "Enter account number to deposit ammount: ";
                    cin >> num;
                    dep_with(num, 2);
                    break;
                case '3':
                    read_acc();
                    break;
                default:
                    cout << "\nPlease enter correct number\n";
                }
            } while (ch3 != '4');
            break;
        }

    } while (ch != '3');

    return 0;
}

void write_acc()
{
    bank b;
    fstream input;
    input.open("bank.dat", ios::binary | ios::app);
    /*if (!input)
    {
        cout << "file not created\n";
    }
    else
    {
        cout << "file created\n";
    }*/
    b.create_acc();
    input.write((char *)&b, sizeof(b));
    input.close();
}

void read_acc()
{

    bank b;
    int num, count = 0;
    ifstream output;
    output.open("bank.dat", ios::binary | ios::in);
    cout << "Enter account number to see details: \n";
    cin >> num;
    if (!output)
    {
        cout << "File not created\n\n";
    }
    else
    {
        while (output.read((char *)&b, sizeof(b)))
        {
            if (b.account() == num)
            {
                b.show_acc();
                count = 1;
                break;
            }
        }
        if (count == 0)
            cout << "\n\n\t\t\tAccount number does not exist\n\n";
        output.close();
    }
}

void up_acc()
{
    bank b;
    int num, count = 0;
    cout << "\"You selected to update account details\"\n";
    fstream update;
    update.open("bank.dat", ios::binary | ios::in | ios::out);
    update.seekg(0);
    cout << "Enter account number to update details: \n";
    cin >> num;
    if (!update)
    {
        cout << "File not found\n\n";
    }
    else
    {
        while (update.read((char *)&b, sizeof(b)))
        {

            if (b.account() == num)
            {
                b.show_acc();
                count = 1;

                b.modify_acc();
                int pos = (-1) * static_cast<int>(sizeof(b));
                update.seekp(pos, ios::cur);
                update.write((char *)&b, sizeof(b));
                break;
            }
        }
        if (count == 0)
            cout << "\n\n\t\t\tAccount number does not exist\n\n";
        update.close();
    }
}

void delete_acc()
{
    bank b;

    ifstream infile;
    ofstream outfile;
    infile.open("bank.dat", ios::binary | ios::in);
    outfile.open("temp.dat", ios::binary | ios::out);
    if (!infile || !outfile)
    {
        cout << "File not found ";
    }
    else
    {
        int acc_num;
        cout << "Enter account number to delete account : ";
        cin >> acc_num;
        while (infile.read((char *)&b, sizeof(b)))
        {
            if (b.account() != acc_num)
            {
                outfile.write((char *)&b, sizeof(b));
            }
        }
        infile.close();
        outfile.close();
        cout << "\t\t\"Account Deleted\"\n\n";
        remove("bank.dat");
        rename("temp.dat", "bank.dat");
    }
}

void dep_with(int n, int option)
{
    bank b;
    int amt;
    int count = 0;
    fstream file;
    file.open("bank.dat", ios::binary | ios::in | ios::out);
    // file.seekg(0);
    if (!file)
    {
        cout << "File not found ";
    }
    else
    {
        while (count == 0 && file.read((char *)&b, sizeof(b)))
        {

            if (b.account() == n)
            {
                b.show_acc();
                if (option == 1)
                {
                    cout << "Enter the ammount to withdraw : ";
                    cin >> amt;
                    int bal = b.amnt() - amt;
                    if (bal < 0)
                    {
                        cout << "\t\"Insufficient balance\"";
                    }
                    else
                    {
                        b.with(amt);
                    }
                }
                if (option == 2)
                {
                    cout << "Enter ammount to deposit : ";
                    cin >> amt;
                    b.dep(amt);
                }

                int pos = (-1) * static_cast<int>(sizeof(b));
                file.seekp(pos, ios::cur);
                file.write((char *)&b, sizeof(b));
                cout << "\n\t\t\"Record Updated\"\n";
                count = 1;
            }
        }
        file.close();
        if (count == 0)
        {
            cout << "\n\tAccount does not exist\n";
            cout << "\tRecord not updated\n ";
        }
    }
}

void display_all()
{
    // system("CLS");
    bank b;
    ifstream inFile;
    inFile.open("bank.dat", ios::binary | ios::in);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
    }
    else
    {
        cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
        cout << "\t\t====================================================\n";
        cout << "\t\tA/c no.\t"
             << "NAME\t"
             << "Type\t"
             << "Balance\n";
        cout << "\t\t====================================================\n";
        while (inFile.read((char *)&b, sizeof(b)))
        {
            b.all_acc();
        }
        cout << "\n\n";
    }
    inFile.close();
}
