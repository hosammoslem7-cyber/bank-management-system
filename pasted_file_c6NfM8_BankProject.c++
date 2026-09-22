#include <iostream>
#include <iomanip>
#include <vector>
#include <cctype>
#include <fstream>
#include "my_input_lib.h"
#include <ctime>
#include <array>
using namespace std;
const string FileName = "Data Of clients.txt";

enum enTrans
{
  eDeposit = 1,
  eWithdraw,
  eTotalBalance,
  eMainmenue
};

enTrans read_Transaction()
{
  short num;
  cout << "Choose what do you want to do \n";
  cin >> (num);
  return enTrans(num);
}

enum enMainmenue
{
  Show_client_list = 1,
  Add_new_client,
  Delete_client,
  Update_client_info,
  Find_client,
  Transaction,
  Exit
};

enMainmenue read_operation_of_Main_Menue()
{
  short num;
  cout << "Choose what do you want to do \n";
  cin >> (num);
  return enMainmenue(num);
}

string readstring()
{
  cout << " Enter any word!\n ";
  string word;
  getline(cin >> ws, word);
  return word;
}

struct stData
{
  string AccountNumber;
  string PinCode;
  string Name;
  string Phone;
  int Balance;
};

vector<stData>::iterator po;

bool is_repeated(vector<stData> &Vstring, string &AccountNum)
{

  for (stData &stClient : Vstring)
  {
    if (stClient.AccountNumber == AccountNum)
    {
      return true;
    }
  }
  return false;
}

stData
read(vector<stData> &Vstring)
{
  stData stClient;
  cout << " Enter AccountNumber\n";
  getline(cin >> ws, stClient.AccountNumber);

  while (is_repeated(Vstring, stClient.AccountNumber))
  {
    cout << " There is already exist,Enter another one\n";
    getline(cin >> ws, stClient.AccountNumber);
  }

  cout << " Enter PinCode \n";
  getline(cin, stClient.PinCode);

  cout << " Enter Name \n";
  getline(cin, stClient.Name);

  cout << " Enter Phone \n";
  getline(cin, stClient.Phone);

  cout << " Enter Balance \n";
  cin >> stClient.Balance;
  return stClient;
}

stData change_data(string AccountNum)
{
  stData stClient;
  stClient.AccountNumber = AccountNum;

  cout << " Enter PinCode \n";
  getline(cin >> ws, stClient.PinCode);

  cout << " Enter Name \n";
  getline(cin, stClient.Name);

  cout << " Enter Phone \n";
  getline(cin, stClient.Phone);

  cout << " Enter Balance \n";
  cin >> stClient.Balance;
  return stClient;
}

vector<string> splitWords(string word, string deli)
{
  vector<string> Vwords;
  short pos = 0;
  string sword;
  while ((pos = word.find(deli)) != std::string::npos)
  {
    sword = word.substr(0, pos);
    if (sword != " ")
    {
      Vwords.push_back(sword);
    }
    word.erase(0, pos + deli.length());
  }
  if (word != " ")
  {
    Vwords.push_back(word);
  }
  return Vwords;
}

string convertRecordToLine(stData stClient, string seperator)
{
  string Line = "";

  Line += stClient.AccountNumber + seperator;
  Line += stClient.PinCode + seperator;
  Line += stClient.Name + seperator;
  Line += stClient.Phone + seperator;
  Line += to_string(stClient.Balance);

  return Line;
}

stData convertLineToRecord(string word)

{
  stData stClient;
  vector<string> Vwords = splitWords(word, "#//#");
  stClient.AccountNumber = Vwords[0];
  stClient.PinCode = Vwords[1];
  stClient.Name = Vwords[2];
  stClient.Phone = Vwords[3];
  stClient.Balance = stoi(Vwords[4]);
  return stClient;
}

vector<stData> read_Data_from_File(string fileName)
{
  vector<stData> Vstruct;
  fstream MyFile;
  MyFile.open(fileName, ios::in);
  if (MyFile.is_open())
  {
    string Line;
    stData stClients;
    while (getline(MyFile, Line))
    {
      stClients = convertLineToRecord(Line);
      Vstruct.push_back(stClients);
    }
    MyFile.close();
  }
  return Vstruct;
}

void printClientsOnTheTable(stData &Client)
{
  cout << "|" << left << setw(15) << Client.AccountNumber;
  cout << "|" << left << setw(10) << Client.PinCode;
  cout << "|" << left << setw(40) << Client.Name;
  cout << "|" << left << setw(12) << Client.Phone;
  cout << "|" << left << setw(12) << Client.Balance;
}

void printClientList(stData &Client)
{
  cout << setw(15) << left << "AccountNumber :" << Client.AccountNumber << "\n";
  cout << setw(15) << left << "PinCode        :" << Client.PinCode << "\n";
  cout << setw(15) << left << "Name          :" << Client.Name << "\n";
  cout << setw(15) << left << "Phone         :" << Client.Phone << "\n";
  cout << setw(15) << left << "Balance       :" << Client.Balance << "\n";
}

void Show_Client_List(vector<stData> &Vstring)

{
  cout << "\n-----------------------------------------------------------------------------------------------------------------------------------------------------------\n";

  cout << "\n\t\t\t\t\tClient List (" << Vstring.size() << ") client(s)\t\t\t\t\n";
  cout << "\n-----------------------------------------------------------------------------------------------------------------------------------------------------------\n";
  cout << "|" << left << setw(15) << "Account Number ";
  cout << "|" << left << setw(10) << " Pin code ";
  cout << "|" << left << setw(40) << "Client Name ";
  cout << "|" << left << setw(12) << "Phone ";
  cout << "|" << left << setw(12) << "Balance ";
  cout << "\n-----------------------------------------------------------------------------------------------------------------------------------------------------------\n";

  if (Vstring.size() == 0)
  {
    cout << "No elements here\n";
  }
  else
  {
    for (stData &stClient : Vstring)
    {
      printClientsOnTheTable(stClient);
      cout << "\n";
    }

    cout << "\n--------------------------------------------------------------------------------\n";
  }
}

bool FindClient(vector<stData> &Vstring)
{
  vector<stData>::iterator iter;
  string AccountNum = readstring();
  for (iter = Vstring.begin(); iter != Vstring.end(); ++iter)
  {
    if (iter->AccountNumber == AccountNum)
    {
      po = iter;
      printClientList(*po);
      cout << "\n";
      return true;
    }
  }

  return false;
}

bool FindAccountNum(vector<stData> &Vstring, string AccountNum)
{
  vector<stData>::iterator iter;

  for (iter = Vstring.begin(); iter != Vstring.end(); ++iter)
  {
    if (iter->AccountNumber == AccountNum)
    {
      po = iter;
      return true;
    }
  }
  return false;
}

void Fill_Data_In_File(string fileName, vector<stData> &Vstring)
{
  fstream MyFile;
  MyFile.open(fileName, ios::out);
  if (MyFile.is_open())
  {
    for (stData &stClient : Vstring)
    {
      MyFile << convertRecordToLine(stClient, "#//#") << "\n";
    }
    MyFile.close();
  }
}

void Append_Data_To_File(string fileName, string Line)
{
  fstream MyFile;
  MyFile.open(fileName, ios::out | ios::app);
  if (MyFile.is_open())
  {
    MyFile << Line << "\n";

    MyFile.close();
  }
}

void Delete(vector<stData> &Vstring)
{

  string AccountNum = readstring();
  if (FindAccountNum(Vstring, AccountNum))
  {
    printClientList(*po);

    char choice = ' ';
    cout << "\n\n Do you want delete this data? \n";
    cin >> choice;
    if (toupper(choice) == 'Y')
    {
      Vstring.erase(po);
      Fill_Data_In_File(FileName, Vstring);
    }
  }
  else
  {
    cout << "It is not found\n";
  }
}

void Update_Data(vector<stData> &Vstring)
{
  string AccountNum = readstring();
  if (FindAccountNum(Vstring, AccountNum))
  {

    printClientList(*po);

    char choice = ' ';
    cout << "\n\n Do you want update this data? \n";
    cin >> choice;
    if (toupper(choice) == 'Y')
    {

      *po = change_data(po->AccountNumber);
      Fill_Data_In_File(FileName, Vstring);
    }
  }

  else
  {
    cout << "It is not found\n";
  }
}

void AddNewClient(vector<stData> &Vstring)
{
  stData stClients = read(Vstring);
  string Line = convertRecordToLine(stClients, "#//#");
  Append_Data_To_File(FileName, Line);
  Vstring = read_Data_from_File(FileName);
}

void AddClients(vector<stData> &Vstring)
{
  char choice = 'y';
  do
  {
    AddNewClient(Vstring);
    cout << "Added successfully,Do you want enter another Data\n ";
    cin >> choice;

  } while (toupper(choice) == 'Y');
}

// Only declaration.
void Show_Main_menue_screen(vector<stData> &Vstring);

void Go_to_main_menue(vector<stData> &Vstring)
{
  system("pause");
  system("cls");

  Show_Main_menue_screen(Vstring);
}

void show_Add_clients_screen(vector<stData> &Vstring)
{
  cout << "-------------------------------\n";
  cout << "\tAdd clients\n";
  cout << "-------------------------------\n";
  AddClients(Vstring);
}

void Show_delete_clients_screen(vector<stData> &Vstring)
{
  cout << "-------------------------------\n";
  cout << "\tDelete clients\n";
  cout << "-------------------------------\n";
  Delete(Vstring);
}

void Show_update_clients_screen(vector<stData> &Vstring)
{
  cout << "-------------------------------\n";
  cout << "\tUpdate clients\n";
  cout << "-------------------------------\n";
  Update_Data(Vstring);
}

void Show_find_clients_screen(vector<stData> &Vstring)
{
  cout << "-------------------------------\n";
  cout << "\tFind client\n";
  cout << "-------------------------------\n";
  FindClient(Vstring);
}
void Show_Transaction_screen(vector<stData> &Vstring);

void Perfrom_Mainmenue_operator(enMainmenue choice, vector<stData> &Vstring)
{
  switch (choice)
  {
  case enMainmenue::Show_client_list:
  {
    system("cls");
    Show_Client_List(Vstring);
    Go_to_main_menue(Vstring);
    break;
  }
  case enMainmenue::Add_new_client:

    system("cls");
    show_Add_clients_screen(Vstring);
    Go_to_main_menue(Vstring);
    break;

  case enMainmenue::Delete_client:
    system("cls");
    Show_delete_clients_screen(Vstring);
    Go_to_main_menue(Vstring);
    break;
  case enMainmenue::Update_client_info:
    system("cls");
    Show_update_clients_screen(Vstring);
    Go_to_main_menue(Vstring);
    break;
  case enMainmenue::Find_client:
    system("cls");
    Show_find_clients_screen(Vstring);
    Go_to_main_menue(Vstring);
    break;

  case enMainmenue::Transaction:
    system("cls");
    Show_Transaction_screen(Vstring);
    break;

  case enMainmenue::Exit:
    system("cls");
    break;
  }
}

void Show_Main_menue_screen(vector<stData> &Vstring)
{
  cout << "--------------------------------------------\n";
  cout << "\tMain menue screen\t\n";
  cout << "--------------------------------------------\n";
  cout << "\t" << "[1]" << "Show client list\n";
  cout << "\t"
          "[2]"
       << "Add new client\n";
  cout << "\t"
          "[3]"
       << "Delete client\n";
  cout << "\t"
          "[4]"
       << "Update client info\n";
  cout << "\t"
          "[5]"
       << "Find client\n";
  cout << "\t"
          "[6]"
       << "Transaction\n";
  cout << "\t[7]" << "Exit\n";
  cout << "--------------------------------------------------------------------------\n";
  Perfrom_Mainmenue_operator(((enMainmenue)read_operation_of_Main_Menue()), Vstring);
}

void Perfrom_Transaction_operator(enTrans Transaction, vector<stData> &Vstring);

void Show_Transaction_screen(vector<stData> &Vstring)
{
  cout << "--------------------------------------------\n";
  cout << "\tTransaction menue screen\t\n";
  cout << "--------------------------------------------\n";
  cout << "\t" << "[1]" << "Deposite\n";
  cout << "\t"
          "[2]"
       << "Withdraw\n";
  cout << "\t"
          "[3]"
       << "Total Balances\n";
  cout << "\t"
          "[4]"
       << "Mainmenue\n";

  cout << "--------------------------------------------------------------------------\n";
  Perfrom_Transaction_operator(read_Transaction(), Vstring);
}

void Perform_Deposite(vector<stData> &Vstring)
{

  char choice = ' ';
  int amount;
  cout << "\n\n Enter deposite amount ? \n";
  cin >> amount;
  cout << "Are you sure you want peform this Transaction?\n";
  cin >> choice;

  if (toupper(choice) == 'Y')
  {
    po->Balance += amount;
    Fill_Data_In_File(FileName, Vstring);
  }
}

void Check_Balance(vector<stData> &Vstring, int &amount)
{
  while (amount > po->Balance)
  {
    cout << "Amount exceeds the balance ,you can withdraw up to " << po->Balance << "\n";
    cout << "Enter another amount\n";
    cin >> amount;
  }
}

void Perform_Withdraw(vector<stData> &Vstring)
{

  char choice = ' ';
  int amount;
  cout << "\n\n Enter Withdraw amount ? \n";
  cin >> amount;
  Check_Balance(Vstring, amount);
  cout << "Are you sure you want peform this Transaction?\n";
  cin >> choice;

  if (toupper(choice) == 'Y')
  {
    po->Balance -= amount;
    Fill_Data_In_File(FileName, Vstring);
  }
}

bool repaet_search(vector<stData> &Vstring)
{

  while (true)
  {
    cout << "It is not found\n";

    string AccountNum = readstring();

    if (FindAccountNum(Vstring, AccountNum))
    {
      return true;
    }
  }
}

void Deposite(vector<stData> &Vstring)
{
  string AccountNum = readstring();
  if (FindAccountNum(Vstring, AccountNum))
  {

    printClientList(*po);

    Perform_Deposite(Vstring);
  }
  else
  {
    repaet_search(Vstring);
    printClientList(*po);

    Perform_Deposite(Vstring);
  }
}

void Withdraw(vector<stData> &Vstring)
{
  string AccountNum = readstring();
  if (FindAccountNum(Vstring, AccountNum))
  {

    printClientList(*po);

    Perform_Withdraw(Vstring);
  }
  else
  {
    repaet_search(Vstring);
    printClientList(*po);

    Perform_Withdraw(Vstring);
  }
}

int Total_Balances(vector<stData> &Vstring)
{
  int sum = 0;
  for (stData &client : Vstring)
  {
    sum += client.Balance;
  }
  return sum;
}

void Show_Deposite_screen(vector<stData> &Vstring)
{
  cout << "-------------------------------\n";
  cout << "\tDeposite_screen\n";
  cout << "-------------------------------\n";
  Deposite(Vstring);
}

void Show_Withdraw_screen(vector<stData> &Vstring)
{
  cout << "-------------------------------\n";
  cout << "\tWithdraw_screen\n";
  cout << "-------------------------------\n";
  Withdraw(Vstring);
}

void printBalancesList(stData &Client)
{
  cout << "|" << left << setw(15) << Client.AccountNumber;
  cout << "|" << left << setw(40) << Client.Name;
  cout << "|" << left << setw(12) << Client.Balance;
}

void Show_Balances_List(vector<stData> &Vstring)

{
  cout << "\n---------------------------------------------------------------------------------------------------------\n";

  cout << "\n\t\t\t\t\tBalances List (" << Vstring.size() << ") client(s)\t\t\t\t\n";
  cout << "\n---------------------------------------------------------------------------------------------------------\n";
  cout << "|" << left << setw(15) << "Account Number ";
  cout << "|" << left << setw(40) << "Client Name ";
  cout << "|" << left << setw(12) << "Balance ";
  cout << "\n---------------------------------------------------------------------------------------------------------\n";

  if (Vstring.size() == 0)
  {
    cout << "No elements here\n";
  }
  else
  {
    for (stData &stClient : Vstring)
    {
      printBalancesList(stClient);
      cout << "\n";
    }

    cout << "\n--------------------------------------------------------------------------------\n";
    cout << "\t\t\t\tTotal_Balances is " << Total_Balances(Vstring) << "\n";
  }
}

void Go_to_Transaction_menue(vector<stData> &Vstring)
{
  system("pause");
  system("cls");

  Show_Transaction_screen(Vstring);
}

void Perfrom_Transaction_operator(enTrans Transaction, vector<stData> &Vstring)
{
  switch (Transaction)
  {
  case enTrans::eDeposit:
    system("cls");
    Show_Deposite_screen(Vstring);
    Go_to_Transaction_menue(Vstring);
    break;

  case enTrans::eTotalBalance:
    system("cls");
    Show_Balances_List(Vstring);
    Go_to_Transaction_menue(Vstring);
    break;

  case enTrans::eWithdraw:
    system("cls");
    Show_Withdraw_screen(Vstring);
    Go_to_Transaction_menue(Vstring);
    break;

  case enTrans::eMainmenue:
    system("cls");
    Show_Main_menue_screen(Vstring);
    break;

  default:
    break;
  }
}

int main()
{
  srand((unsigned)time(NULL));
  vector<stData> Vstring = read_Data_from_File(FileName);

  Show_Main_menue_screen(Vstring);
  system("cls");
}
