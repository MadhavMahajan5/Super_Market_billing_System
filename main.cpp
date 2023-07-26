#include <iostream>
#include <fstream>
using namespace std;
class shopping
{
private:
    int pcode;
    float price;
    float dis;
    string pname;

public:
    void menu();
    void adminstartor();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

void shopping::menu()
{
m:
    int choice;
    string username;
    string password;

    cout << "\t\t\t\t______________________________________________________________\n";
    cout << "\t\t\t\t                                                              \n";
    cout << "\t\t\t\t                   Supermarket Main menu                     \n";
    cout << "\t\t\t\t                                                              \n";
    cout << "\t\t\t\t______________________________________________________________\n";
    cout << "\t\t\t\t                                                              \n";
    cout << "\t\t\t\t     1) Admin Login                 |" << endl;
    cout << "\t\t\t\t                                    |                          \n";
    cout << "\t\t\t\t     2) Buyer login                 |" << endl;
    cout << "\t\t\t\t                                    |                          \n";
    cout << "\t\t\t\t     3) Exit                        |" << endl;
    cout << "\t\t\t\t                                    |                          \n";
    cout << "\t\t\t\t  Please Select! ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "\t\t\t Please Login \n";
        cout << "\t\t\t Enter username \n";
        cin >> username;
        cout << "\t\t\t Enter password \n";
        cin >> password;
        if (username == "admin" && password == "98745")
        {
            adminstartor();
        }
        else
            cout << "Invalid user login" << endl;
        break;

    case 2:
        buyer();
    case 3:
        exit(0);
    default:
        cout << "please select from given options!" << endl;
    }
    goto m;
}

void shopping::adminstartor()
{
m:
    int choice;
    cout << "\n\n\n\t\t\t Adminstrator menu ";
    cout << "\n\t\t\t| _____1) Add the product ____________|";
    cout << "\n\t\t\t|                                     |";
    cout << "\n\t\t\t| _____2) Modify the Product _________|";
    cout << "\n\t\t\t|                                     |";
    cout << "\n\t\t\t| _____3) Delete the product _________|";
    cout << "\n\t\t\t|                                     |";
    cout << "\n\t\t\t| _____4) Back to main menu __________|";
    cout << "\n\t\t\t|                                     |";

    cout << "\n\n\n\tPlease enter your choice :" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
        add();
        break;

    case 2:
        edit();
        break;
    case 3:
        rem();
        break;
    case 4:
        menu();
        break;
    default:
        cout << "Invalid choice!" << endl;
    }
    goto m;
}

void shopping::buyer()
{
m:
    int choice;
    cout << "\t\t\t Buyer \n";
    cout << "\t\t\t___________\n";
    cout << endl;
    cout << "\t\t\t 1)Buy Product \n";
    cout << "\t\t\t 2)Go back \n";

    cin >> choice;
    switch (choice)
    {
    case 1:
        receipt();
        break;
    case 2:
        menu();
        break;

    default:
        cout << "Please select valid option " << endl;
        break;
    }
    goto m;
}

void shopping::add()
{

m:
    fstream data;
    int c, token = 0;
    float p, d;
    string n;

    cout << "\n\n\t\t\t Add new product ";
    cout << "\n\n\t Product code of the product ";
    cin >> pcode;
    cout << "\n\n\t Name of the product ";
    cin >> pname;
    cout << "\n\n\t Price of the product ";
    cin >> price;
    cout << "\n\n\t Discount on Product ";
    cin >> dis;

    data.open("database.txt", ios::in);

    if (!data)
    {
        data.open("database.txt", ios::app | ios::out);
        data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
        data.close();
    }
    else
    {
        data >> c >> n >> p >> d;

        while (!data.eof())
        {
            if (c == pcode)
            {
                token++;
            }
            data >> c >> n >> p >> d;
        }
        data.close();

        if (token == 1)
        {
            goto m;
        }
        else
        {
            data.open("database.txt", ios::app | ios::out); // out means write mode
            data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            data.close();
        }
    }
    cout << " \n\n\t\t   Record Inserted  ! ";
}
void shopping::edit()
{
    fstream data, data1;
    int pkey;
    int token = 0;
    int c;
    float p;
    float d;
    string n;

    cout << " \n\n\t\t\t Modify the record ";
    cout << " \n\t\t\t Product code  ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << " \n\n  file doesnot exist ";
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price >> dis;
        while (!data.eof())
        {
            if (pkey == pcode)
            {
                // pcode is the product code entered by the user to change  and if that pcode exists then we will ask the user to enter the new product code for the product
                cout << "\n\t\t Product New Code :";
                cin >> c;
                cout << "\n\t\tName of the Product:";
                cin >> n;
                cout << "\n\t\t Price :";
                cin >> p;
                cout << "\n\t\t Discount  :";
                cin >> d;

                data1 << " " << c << " " << n << " " << p << " " << d << " " << endl;
                cout << "\n\n\t\t\t\t Record edited ";
                token++;
            }
            else
            {
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << endl;
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt"); // old , new

        if (token == 0)
            cout << "\t\t Record not found , Sorry !";
    }
}

void shopping::rem()
{
    fstream data, data1;
    int pkey;
    int token = 0;
    cout << " \n\n\t Delete product ";
    cout << " \n\t\t enter the product code  ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\n\t\t\t File doesnot exist ";
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price >> dis;
        while (!data.eof())
        {
            if (pkey == pcode)
            {
                cout << "\n\n\t\t\t\t Product deleted successfully  ";
                token++;
            }
            else
            {
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << endl;
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt"); // old , new

        if (token == 0)
            cout << "\t\t Record not found , Sorry !";
    }
}

void shopping::list()
{
    fstream data;
    data.open("database.txt", ios::in);
    cout << "\n\n________________________________________________\n ";
    cout << " ProdNo. \t\t Name \t\t Price \n ";
    cout << "\n\n________________________________________________\n ";
    data >> pcode >> pname >> price >> dis;
    while (!data.eof())
    {
        cout << pcode << " \t\t" << pname << "\t\t " << price << " \t\t" << endl;
        data >> pcode >> pname >> price >> dis;
    }
    data.close();
}

void shopping::receipt()
{
m:
    fstream data;
    int arrc[100]; // array of codes
    int arrq[100]; // array of quantity
    char choice;
    int c = 0;
    float amount = 0;
    float discount = 0;
    float total = 0;

    cout << "\n\n\n\t\t\t  RECEIPT  \n";
    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\t\t Empty database ";
    }
    else
    {
        data.close();

        list();
        cout << "\n____________________________________\n";
        cout << "\n                                    \n";
        cout << "\n        Please place the order      \n";
        cout << "\n                                    \n";
        cout << "\n____________________________________\n";

        do
        {
            cout << "\n\t\t Enter product code ";
            cin >> arrc[c];
            cout << "\n\t\t Enter product quantity ";
            cin >> arrq[c];

            // to prevent the user from entering the same product code
            for (int i = 0; i < c; i++)
            {
                if (arrc[c] == arrc[i])
                {
                    cout << "\n\t\t Duplicate product code . Please try again ";
                    goto m;
                }
            }
            c++;
            cout << "\n\t Do you want to buy another product ? if yes then press y else n ";
            cin >> choice;
        } while (choice == 'y' || choice == 'Y');

        cout << "\n\n\t\t___________________________________RECEIPT_______________________________________\n";
        cout << "\n Product No\tProduct name\tProduct quantity \t Price \tAmount \tAmount with discount\n";

        for (int i = 0; i < c; i++)
        {
            data.open("database.txt", ios::in);
            data >> pcode >> pname >> price >> dis;
            
            while (!data.eof())
            {
                if (pcode == arrc[i])
                {
                    amount = price * arrq[i];
                    dis = amount - (amount * dis / 100);
                    total += dis;
                    cout << endl
                         << pcode << "\t\t" << pname << "\t\t" << arrq[i] << "\t\t" << price << "\t\t" << amount << "\t\t" << dis << "\t\t" << endl;
                }
                data >> pcode >> pname >> price >> dis;
            }
        }
        data.close();
    }
    cout << "\n\n________________________________________________\n";
    cout << "\t\t\t\t\t TOTAL AMOUNT : " << total;
}

int main()
{
    shopping sh;
    sh.menu();
    return 0;
}