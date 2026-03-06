#include <iostream>
#include <iomanip>
#include <vector>
#include <cctype>
#include "StringLib.h"
using namespace std;

struct stUser
{
    string Name;
    string Password;
    int Permission;
    bool DeleteMark = false;
};

enum enMainOptions { 
    ShowClientList = 1, AddNewClient = 2, DeleteClient = 3, 
    UpdateClient = 4, FindClient = 5, Transactions = 6, 
    ManageUsers = 7, Logout = 8, Exit = 9 
};

enum enManageUserOption
{
    ListUsers = 1, AddNewUser = 2, DeleteUser = 3,
    UpdateUser = 4, FindUser = 5, MainMenuM = 6
};

enum enTransactionsOpentions { Deposit = 1, Withdraw = 2, TotalBalances = 3, MainMenuT = 4 };

enum SeperatorType { thick = 1, Thin = 0 };

const string FileOfClientData = "ClientData.txt";

const string FileOfUserData = "Users.txt";

stUser Admin = {"Admin", "", -1};

string ReadString(string Message)
{
    string Str;
    cout << Message;
    getline(cin >> ws, Str);
    return Str;
}

bool YesOrNo(string Message)  
{
    string YOrN = "";
    cout << Message;
    getline(cin >> ws, YOrN);
    return StringLib::LowerAllLetters(YOrN) == "yes"; // remember dont use if Its already boolean    
}

bool YOrNQuestion(string Message)
{
    char YOrN;
    cout << Message;
    cin >> YOrN;
    return tolower(YOrN) == 'y';
}

void PressAnyKeySentence()
{
    cout << "\n\nPress any Key to go back to Main Menu...";
    system("pause>0");
}



void LineSeperator(short Length, SeperatorType Type = SeperatorType::thick)
{
    if (Type == SeperatorType::thick)
        for (short i = 0; i <= Length; i++)
            cout << '=';
    else
        for (short i = 0; i <= Length; i++)
            cout << '-';
}
int ReadInt(string Message)
{
    int Num;
    cout << Message;
    cin >> Num;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid Input, Enter a number? ";
        cin >> Num;
    }
    return Num;
}
double ReadDouble(string Message)
{
    double Num;
    cout << Message;
    cin >> Num;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid Input, Enter a number? ";
        cin >> Num;
    }
    return Num;
}

string ReadAccountNumber()
{
    string AccountNumber;
    cout << "Please enter Account Number? ";
    getline(cin >> ws, AccountNumber);
    return AccountNumber;
}

void AccessDeniedScreen()
{
    LineSeperator(40, SeperatorType::Thin);
    cout << '\n';
    cout << "Access Denied,\n";
    cout << "You Dont Have Permission To Do This,\n";
    cout << "Please Contact Your Admin.";
    cout << '\n';
    LineSeperator(40, SeperatorType::Thin);
    cout << '\n';
    PressAnyKeySentence();
}

string ConvertRecordToLine(stUser User, string Seperator = "#//#")
{
    string stUserRecord = "";

    stUserRecord += User.Name + Seperator;
    stUserRecord += User.Password + Seperator;
    stUserRecord += to_string(User.Permission);
    // When we convert digit to string, it brings with it many zeros

    return stUserRecord;
}

bool CheckPermissionOfUser(const int& UserPermission, const short &OperationNum)
{
    short PermissionLevel = pow(2, OperationNum);
    if (UserPermission == -1 || ((UserPermission & PermissionLevel) == PermissionLevel))
        return true;
    cout << '\n';
    AccessDeniedScreen();
    return false;
}

void IncreasePermissionLevel(int& UserPermission, const short NumOrder)
{
    const static short arrPermissionLevel[7] = {1, 2, 4, 8, 16, 32, 64};
    UserPermission += arrPermissionLevel[NumOrder];
}

void AddAccessToMainOperations(int& UserPermission)
{
    char YOrN;

    string arrAccessType[] = {"show Client List? ",
    "Add New Client? ", "Delete Client? ",
    "Update Client? ", "Find Client? ", "Transactions? ",
    "Manage Users? "};

    cout << "Do you want to give access to : \n\n";
    for (short i = 0; i < 7; i++)
    {
        cout << arrAccessType[i] << "y/n? ";
        cin >> YOrN;      
        if ('y' == char(tolower(YOrN))) // remove char cuz it works without it
            IncreasePermissionLevel(UserPermission,i);
        cout << '\n';
    } 
}

void SaveUsersDataToFile(string FileName, const vector <stUser>& vUsers)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out); // overwrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (const stUser& C : vUsers)
            if (C.DeleteMark == false)
            {
                // we only write records that are not marked for delete
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }

        MyFile.close();
    }
}


stUser ConvertLineToRecordstUsers(string Line, string Seperator = "#//#")
{
    stUser Users;
    vector <string> vUsers;

    vUsers = StringLib::SplitString(Line, Seperator);

    Users.Name = vUsers[0];
    Users.Password = vUsers[1];
    Users.Permission = stod(vUsers[2]); //cast string to double
    return Users;
}

vector <stUser> LoadUsersDataFromFile(string FileName)
{
    vector <stUser> vUsers;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode
    if (MyFile.is_open())
    {
        string Line;
        stUser User;
        while (getline(MyFile, Line))
        {
            User = ConvertLineToRecordstUsers(Line);
            vUsers.push_back(User);
        }
        MyFile.close();
    }
    return vUsers;
}

bool checkUserInfoExistance(vector <stUser>& vUser,  stUser& User)
{
    for (stUser& C : vUser)
    {
        if (C.Name == User.Name)
        {
            User = C;
            return true;
        }
    }
    return false;
}

bool CheckUserLoginIsRight(vector <stUser>& vUser, stUser& User)
{
    for (stUser& C : vUser)
    {
        if (C.Name == User.Name && C.Password == User.Password)
        {
            User = C;
            return true;
        }
    }
    return false;
}

bool MarkUserForDeleteByUsername(const string Username, vector <stUser>& vUsers)
{
    for (stUser& C : vUsers)
        if (C.Name == Username)
        {
            C.DeleteMark = true;
            return true;
        }
    return false;
}

void PrintClientRecord(const stClient& Client)
{
    cout << "The following are the client details:\n";
    LineSeperator(40);
    cout << '\n';
    cout << "\nAccout Number : " << Client.AccountNumber;
    cout << "\nPin Code      : " << Client.PinCode;
    cout << "\nName          : " << Client.Name;
    cout << "\nPhone         : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << '\n';
    LineSeperator(40);
}

void PrintUserCard(const stUser& User)
{
    cout << "The following is user details:\n";
    LineSeperator(40, SeperatorType::Thin);
    cout << "\nUsername   : " << User.Name;
    cout << "\nPassword   : " << User.Password;
    cout << "\nPermission : " << User.Permission;
    cout << '\n';
    LineSeperator(40, SeperatorType::Thin);
}


bool IsAccountNumberExistInVector(const vector <stClient>& vClientsData, string AccountNumber)
{
    for (int i = 0; i < vClientsData.size(); i++)
    {
        if (AccountNumber == vClientsData[i].AccountNumber)
            return true;
    }
    return false;
}

stClient ReadNewClient(stClient& Client)
{

    cout << "Enter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    Client.AccountBalance = ReadDouble("Enter Account Balance? ");

    return Client;
}


void UpdateClientInfoFromVector(vector <stClient>& ClientsData, const string& AccountNumber)
{
    for (stClient& C : ClientsData)
        if (C.AccountNumber == AccountNumber)
            ReadNewClient(C);
}


bool UpdateClientInfo(vector <stClient>& vClientData, string AccountNumber)
{
    bool IsUpdated = false;
    char YOrN;
    stClient ClientInfo;
    if (StringLib::FindClientByAccountNumber(AccountNumber, vClientData, ClientInfo))
    {
        PrintClientRecord(ClientInfo);
        cout << "\n\nAre you sure you want update this Client? y/n ? ";
        cin >> YOrN;
        if (tolower(YOrN) == 'y')
        {
            UpdateClientInfoFromVector(vClientData, AccountNumber);
            cout << "\n\nClient Updated Succesfully.";
            IsUpdated = true;
        }
        else
            cout << "\n\nClient NOT Updated.";
    }
    else
    {
        cout << "\n\nClient with Account Number (" << AccountNumber << ") Not Found!";
    }
    return IsUpdated;
}


void HeaderOfSubScreens(string title)
{
    LineSeperator(40, SeperatorType::Thin);
    cout << '\n';
    cout << setw(8) << "" << title;
    cout << '\n';
    LineSeperator(40, SeperatorType::Thin);
}

void AddNewClientToVector(vector <stClient>& vClientsData)
{
    stClient Client;
    Client.AccountNumber = ReadAccountNumber();
    while (IsAccountNumberExistInVector(vClientsData, Client.AccountNumber))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }
    vClientsData.push_back(ReadNewClient(Client));
}


void FindClientInfo(const vector <stClient>& vClientsData, string AccountNumber)
{
    stClient ClientInfo;
    if (StringLib::FindClientByAccountNumber(AccountNumber, vClientsData, ClientInfo))
    {
        cout << '\n';
        PrintClientRecord(ClientInfo);
    }
    else
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
}

void ManageUsersMenuScreen()
{
    LineSeperator(40);
    cout << '\n';
    cout << setw(8) << "" << "Manage Users Menu Screen";
    cout << '\n';
    LineSeperator(40);

    cout << "\n\t [1] List Users.\n";
    cout << "\t [2] Add New User.\n";
    cout << "\t [3] Delete User.\n";
    cout << "\t [4] Update User.\n";
    cout << "\t [5] Find User.\n";
    cout << "\t [6] Main Menu.\n";
    LineSeperator(40);
}

void MainMenuScreen() // ^
{
    LineSeperator(40);
    cout << '\n';
    cout << setw(12) << "" << "Main Menu Screeen";
    cout << '\n';
    LineSeperator(40);

    cout << "\n\t [1] Show Client List.\n";
    cout << "\t [2] Add New Client.\n";
    cout << "\t [3] Delete Client.\n";
    cout << "\t [4] Update Client Info.\n";
    cout << "\t [5] Find Client.\n";
    cout << "\t [6] Transactions.\n";
    cout << "\t [7] Manage Users.\n";
    cout << "\t [8] Logout.\n";
    cout << "\t [9] Exit.\n";
    LineSeperator(40);
}

void TransactionsMenuScreen()
{
    LineSeperator(40);
    cout << '\n';
    cout << setw(8) << "" << "Transactions Menu Screeen";
    cout << '\n';
    LineSeperator(40);
    cout << "\n\t[1] Deposite.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menu.\n";
    LineSeperator(40);
}

void UsersTableHeader(short NumOfUsers)
{
    cout << setw(40) << ""
        << "Users List (" << NumOfUsers
        << ") Users(s).\n";
    StringLib::HeaderFrame(110);
    cout << "\n\n";
    cout << "| ";
    StringLib::SetRight(20, "User Name");
    cout << "| ";
    StringLib::SetRight(15, "Password");
    cout << "| ";
    StringLib::SetRight(65, "Permission");    
    cout << '\n';
    StringLib::HeaderFrame(110);
    cout << endl;
}

void FillTableRow(const stUser& User)
{
    cout << "| ";
    StringLib::SetRight(20, User.Name);
    cout << "| ";
    StringLib::SetRight(15, User.Password);
    cout << "| ";
    StringLib::SetRight(35, to_string(User.Permission));  
    cout << '\n';
}

void TableOfUsersData(const vector <stUser> &vUsersData)
{
    UsersTableHeader(vUsersData.size());
    cout << '\n';
    for (const stUser n : vUsersData)
    {
        FillTableRow(n);
    }
    StringLib::HeaderFrame(110);
}

void ClientsListScreen(const vector <stClient>& vClientsData, const int &UserPermission, enMainOptions MainOption) // ^
{
    if (!CheckPermissionOfUser(UserPermission, short(MainOption) - 1))
        return;
    
    StringLib::TableOfClientData(vClientsData);
    PressAnyKeySentence();
}



void AddNewClientScreen(vector <stClient>& vClientsData, const int& UserPermission, enMainOptions MainOption) // ^
{
    if (!CheckPermissionOfUser(UserPermission, short(MainOption) - 1))
        return;

    HeaderOfSubScreens("Add New Clients Screen");
    cout << '\n';
    char YOrN = 'y';
    cout << "\nAdding New Client: \n\n";
    do
    {
        AddNewClientToVector(vClientsData);
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> YOrN;
    } while (tolower(YOrN) == 'y');
    PressAnyKeySentence();
}

void DeleteClientInfoFromVector(vector <stClient>& vClientsData, const int& UserPermission, enMainOptions MainOption) // ^
{
    if (!CheckPermissionOfUser(UserPermission, short(MainOption) - 1))
        return;

    HeaderOfSubScreens("Delete Client Screen");
    cout << "\n\n";
    string AccountNumber = ReadAccountNumber();
    StringLib::DeleteClientByAccountNumber(AccountNumber, vClientsData);
    PressAnyKeySentence();
}

void UpdateClientInfoScreen(vector <stClient>& vClientsData, const int& UserPermission, enMainOptions MainOption) // ^ 
{
    if (!CheckPermissionOfUser(UserPermission, short(MainOption) - 1))
        return;
    HeaderOfSubScreens("Update Client Info Screen");
    cout << '\n';
    string AccountNumber = ReadAccountNumber();
    cout << '\n';
    UpdateClientInfo(vClientsData, AccountNumber);
    PressAnyKeySentence();
}

void FindClientScreen(const vector <stClient>& vClientsData, const int& UserPermission, enMainOptions MainOption) // ^
{
    if (!CheckPermissionOfUser(UserPermission, short(MainOption) - 1))
        return;
    HeaderOfSubScreens("Find Client Screen");
    cout << "\n\n";
    FindClientInfo(vClientsData, ReadAccountNumber());
    PressAnyKeySentence();
}


void SaveClientInfoInVector(vector <stClient>& vClientsData, const stClient& ClientInfo, const string& AccountNumber)
{
    if (vClientsData.empty())
        return;
    for (int i = 0; i < vClientsData.size(); i++)
        if (vClientsData[i].AccountNumber == AccountNumber)
        {
            vClientsData[i] = ClientInfo;
            return;
        }
}

void SaveUserInfoInVector(vector <stUser>& vUsers, const stUser& User)
{
    if (vUsers.empty())
        return;
    for (int i = 0; i < vUsers.size(); i++)
        if (vUsers[i].Name == User.Name)
        {
            vUsers[i] = User;
            return;
        }
}


void PrintClientRecord(stClient& ClientInfo)
{
    cout << "The following are the client details:\n";
    LineSeperator(40, SeperatorType::Thin);
    StringLib::PrintClientCard(ClientInfo);
    cout << '\n';
    LineSeperator(40, SeperatorType::Thin);

}

bool DepositMoneyUsingVector(stClient& ClientInfo)
{
    int Num;
    bool Deposit = true;
    PrintClientRecord(ClientInfo);
    cout << "\n\n";
    Num = ReadDouble("Please enter deposite amount? ");
    cout << "\n\n";
    if (YesOrNo("Are you sure you want to perform this transactions? [Yes,No] ?"))
    {
        ClientInfo.AccountBalance = ClientInfo.AccountBalance + Num;
        cout << "\n\n";
        cout << "Done successfully, new balance " << ClientInfo.AccountBalance << endl;
        PressAnyKeySentence();
        return Deposit;
    }
    Deposit = false;
    return Deposit;
}


void DepositScreen(vector <stClient>& vClientsData)
{
    HeaderOfSubScreens(" Deposit Screen");
    cout << "\n\n";
    stClient ClientInfo;
    string AccountNumber = ReadAccountNumber();
    while (!StringLib::FindClientByAccountNumber(AccountNumber, vClientsData, ClientInfo))
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!" << endl;

        if (YesOrNo("Do you want to continue? [Yes,No] ?\n"))
            AccountNumber = ReadAccountNumber();
        else
            return;
    }
    cout << '\n';
    if (DepositMoneyUsingVector(ClientInfo))
    {
        SaveClientInfoInVector(vClientsData, ClientInfo, AccountNumber);
    }
    return;
}


bool WithdrawMoneyUsingVector(stClient& ClientInfo)
{
    int Num;
    bool Withdraw = true;
    PrintClientRecord(ClientInfo);
    cout << "\n\n";
    Num = ReadDouble("Please enter Withdraw amount? ");

    while (Num > ClientInfo.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << ClientInfo.AccountBalance << endl;
        Num = ReadDouble("Please enter anther amount? ");
    }
    cout << "\n\n";
    if (YesOrNo("Are you sure you want to perform this transactions? [Yes,No] ?"))
    {
        ClientInfo.AccountBalance = ClientInfo.AccountBalance - Num;
        cout << "\n\n";
        cout << "Done successfully, new balance " << ClientInfo.AccountBalance << endl;
        PressAnyKeySentence();
        return Withdraw;
    }
    Withdraw = false;
    return Withdraw;
}

void WithdrawScreen(vector <stClient>& vClientsData)
{
    HeaderOfSubScreens("Withdraw Screen");
    cout << "\n\n";
    stClient ClientInfo;
    string AccountNumber = ReadAccountNumber();
    while (!StringLib::FindClientByAccountNumber(AccountNumber, vClientsData ,ClientInfo))
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!" << endl;
        if (YesOrNo("Do you want to continue? [Yes,No] ?\n"))
            AccountNumber = ReadAccountNumber();
        else
            return;
    }
    cout << '\n';
    if (WithdrawMoneyUsingVector(ClientInfo))
    {
        SaveClientInfoInVector(vClientsData, ClientInfo, AccountNumber);
    }
    return;
}

void HeaderOfTotalBalancesTable(const int& NumberOfClients)
{
    cout << '\n';
    cout << setw(40) << ""
        << "Client List (" << NumberOfClients
        << ") Client(s).\n";
    StringLib::HeaderFrame(110);
    cout << "\n\n";
    cout << "| " << left << setw(20) << "Account Number";
    cout << "| " << left << setw(45) << "Client Name";
    cout << "| " << left << setw(35) << "Balance";
    cout << "\n";
    StringLib::HeaderFrame(110);
}

void RowOfTotalBalancesTable(const stClient& ClientInfo)
{
    cout << "| " << left << setw(20) << ClientInfo.AccountNumber;
    cout << "| " << left << setw(45) << ClientInfo.Name;
    cout << "| " << left << setw(35) << ClientInfo.AccountBalance;
}
void TotalBalancesScreen(const vector <stClient>& vClientsData)
{
    double TotalBalances = 0;
    HeaderOfTotalBalancesTable(vClientsData.size());
    cout << '\n';
    if (vClientsData.size() == 0)
    {
        cout << "There is no Client Data right now!" << endl;
    }
    else
    {
        for (int i = 0; i < vClientsData.size(); i++)
        {
            TotalBalances = TotalBalances + vClientsData[i].AccountBalance;
            RowOfTotalBalancesTable(vClientsData[i]);
            cout << endl;
        }
        cout << '\n';
        StringLib::HeaderFrame(110);
        cout << '\n';
        cout << setw(40) << "" << "Total Balances = " << TotalBalances;
    }
    PressAnyKeySentence();
}

void ListUserScreen(const vector <stUser> &vUsersData)
{
    cout << '\n';
    TableOfUsersData(vUsersData);
    PressAnyKeySentence();
}

void AddNewUserScreen(vector <stUser>& vUsersData)
{
    stUser User;
    User.Permission = 0;
    do
    {
        system("cls");
        HeaderOfSubScreens("Add New User Screen");
        cout << "\nAdding New User: \n\n";
        User.Name = ReadString("Enter Username? ");
        User.Password = ReadString("Enter Password? ");
        while (checkUserInfoExistance(vUsersData, User))
        {                    
            cout << '\n';
            cout << "User with [" << User.Name << "] already exists,";
            User.Name = ReadString("Enter another Username? ");
            User.Password = ReadString("Enter Password? ");
        }
        if (YesOrNo("\nDo you want to give full access? yes/no? "))       
            User.Permission = -1;     
        else
        {
            cout << '\n';
            AddAccessToMainOperations(User.Permission);
        }           
        vUsersData.push_back(User);
    } while (YesOrNo("\nUser Added Successfully, do you want to add more Users? yes/no? "));
    
    PressAnyKeySentence();
}

void DeleteUsersScreen(vector <stUser>& vUsersData, const stUser& MainUser)
{
    stUser User;
    HeaderOfSubScreens("Add New User Screen");
    cout << '\n';
    User.Name = ReadString("Please Enter Username? ");
    cout << '\n';
    if (!checkUserInfoExistance(vUsersData, User))
    {
        cout << "User with Username (" << User.Name << ") is Not Found!";
        PressAnyKeySentence();
        return;
    }
    else if (User.Name == Admin.Name || User.Name == MainUser.Name)
    {
        cout << "You cannot Delete This user.";
        PressAnyKeySentence();
        return;
    }
    PrintUserCard(User);
    if (!YOrNQuestion("\n\nAre you sure you want to delete this user? y/n ? "))
    {
        PressAnyKeySentence();
        return;
    }                  
     MarkUserForDeleteByUsername(User.Name, vUsersData);
     cout << "\nUser Deleted Successfully.";
     PressAnyKeySentence();
}

void UpdateUserScreen(vector <stUser>& vUsersData)
{
    stUser User;
    HeaderOfSubScreens("Update Users Screen");
    cout << '\n';
    User.Name = ReadString("Please Enter Username? ");
    cout << '\n';
    if (!checkUserInfoExistance(vUsersData, User))
    {
        cout << "User with Username (" << User.Name << ") is Not Found!";
        PressAnyKeySentence();
        return;
    }
    PrintUserCard(User);
    if (!YOrNQuestion("\n\nAre you sure you want to update this user? y/n ? "))
    {
        PressAnyKeySentence();
        return;
    }
    cout << '\n';
    User.Password = ReadString("Enter Password? ");
    if (!(User.Name == Admin.Name)) // Admin has fixed Permission
    {
        if (YesOrNo("\nDo you want to give full access? yes/no? "))
            User.Permission = -1;
        else
        {
            cout << '\n';
            User.Permission = 0;
            AddAccessToMainOperations(User.Permission);
        }
    }    
    SaveUserInfoInVector(vUsersData, User);
    cout << "\nUser Updated Successfully.";
    PressAnyKeySentence();
}

void FindUserScreen(vector <stUser>& vUsersData)
{
    stUser User;
    HeaderOfSubScreens("Find User Screen");
    cout << '\n';
    User.Name = ReadString("Please Enter Username? ");
    cout << '\n';
    if (!checkUserInfoExistance(vUsersData, User))
    {
        cout << "User with Username (" << User.Name << ") is Not Found!";
        PressAnyKeySentence();
        return;
    }
    PrintUserCard(User);
    PressAnyKeySentence();

}

void LogoutScreen(stUser &User)
{
    vector <stUser> vUsersData = LoadUsersDataFromFile(FileOfUserData);
   
    HeaderOfSubScreens("      Login Screen");
    cout << '\n';
    User.Name = ReadString("Enter Username? ");
    User.Password = ReadString("Enter Password? ");

    while (!checkUserInfoExistance(vUsersData, User))
    {
        system("cls");
        HeaderOfSubScreens("      Login Screen");
        cout << '\n';
        cout << "Invalid Username/Password!\n";
        User.Name = ReadString("Enter Username? ");
        User.Password = ReadString("Enter Password? ");
    }

    system("cls");
}

void ControlPanelOfTransactions(vector <stClient>& vClientsData, const int& UserPermission, enMainOptions MainOption)
{
    if (!CheckPermissionOfUser(UserPermission, short(MainOption) - 1))
        return;
    short TransactionsNum = 4;
    enTransactionsOpentions OperationOfTrans;
    do
    {        
        TransactionsMenuScreen();
        TransactionsNum = ReadInt("\nChoose what do you want to do? [1 to 4]? ");
        OperationOfTrans = enTransactionsOpentions(TransactionsNum);
        system("cls");
        switch (OperationOfTrans)
        {
        case enTransactionsOpentions::Deposit:
            DepositScreen(vClientsData);
            break;
        case enTransactionsOpentions::Withdraw:
            WithdrawScreen(vClientsData);
            break;
        case enTransactionsOpentions::TotalBalances:
            TotalBalancesScreen(vClientsData);
            break;
        }
        StringLib::SaveClientsDataToFile(FileOfClientData, vClientsData); // Save will protect the data In case electricity went out.
        system("cls");
    } while (OperationOfTrans != enTransactionsOpentions::MainMenuT);

}


void ControlPanelOfManageUsers(const int& UserPermission,const stUser& User,enMainOptions MainOption)
{
    if (!CheckPermissionOfUser(UserPermission, short(MainOption) - 1))
        return;
    short Option;
    enManageUserOption enOption;
    vector <stUser> vUsersData;
    vUsersData = LoadUsersDataFromFile(FileOfUserData);
    do
    {      
        ManageUsersMenuScreen();
        cout << '\n';
        Option = ReadInt("Choose what do you want to do? [1 to 6]? ");
        enOption = enManageUserOption(Option);
        system("cls");
        switch (enOption)
        {
        case enManageUserOption::MainMenuM:
            break;
        case enManageUserOption::ListUsers:
            ListUserScreen(vUsersData);
            break;
        case enManageUserOption::AddNewUser:
            AddNewUserScreen(vUsersData);
            break;
        case enManageUserOption::DeleteUser:
            DeleteUsersScreen(vUsersData, User);
            break;
        case enManageUserOption::UpdateUser:
            UpdateUserScreen(vUsersData);
            break;
        case enManageUserOption::FindUser:
            FindUserScreen(vUsersData);
            break;       
        }
        SaveUsersDataToFile(FileOfUserData, vUsersData);// Ok         
        system("cls");
    } while (enOption != enManageUserOption::MainMenuM);
    
}

void MainControlPanel(stUser &User)
{
    short OptionNum = 7;
    enMainOptions Operation;
    vector <stClient> vClientsData;
    vClientsData = StringLib::LoadClientsDataFromFile(FileOfClientData);
    do
    { 
        MainMenuScreen();
        OptionNum = ReadInt("\nChoose what do you want to do? [1 to 9]? ");
        Operation = enMainOptions(OptionNum);
        system("cls");
        switch (Operation)
        {
        case enMainOptions::Exit:
            break;
        case enMainOptions::ShowClientList:
            ClientsListScreen(vClientsData, User.Permission, enMainOptions::ShowClientList);// another parameter
            break;
        case enMainOptions::AddNewClient:
            AddNewClientScreen(vClientsData, User.Permission, enMainOptions::AddNewClient);
            break;
        case enMainOptions::DeleteClient:
            DeleteClientInfoFromVector(vClientsData, User.Permission, enMainOptions::DeleteClient);
            break;
        case enMainOptions::UpdateClient:
            UpdateClientInfoScreen(vClientsData, User.Permission, enMainOptions::UpdateClient);
            break;
        case enMainOptions::FindClient:
            FindClientScreen(vClientsData, User.Permission, enMainOptions::FindClient);
            break;
        case enMainOptions::Transactions:
            ControlPanelOfTransactions(vClientsData, User.Permission, enMainOptions::Transactions);
            break;
        case enMainOptions::ManageUsers:
            ControlPanelOfManageUsers(User.Permission, User,enMainOptions::ManageUsers);
            break;
        case enMainOptions::Logout:
            LogoutScreen(User);
            break;
        }
        StringLib::SaveClientsDataToFile(FileOfClientData, vClientsData);
        system("cls");
    } while (Operation != enMainOptions::Exit);
    HeaderOfSubScreens("Program Ends :-)");  
}

void Login()
{
    vector <stUser> vUsersData = LoadUsersDataFromFile(FileOfUserData);
    stUser User;

    HeaderOfSubScreens("      Login Screen");
    cout << '\n';
    User.Name = ReadString("Enter Username? ");
    User.Password = ReadString("Enter Password? ");

    while (!CheckUserLoginIsRight(vUsersData, User))
    {
        system("cls");
        HeaderOfSubScreens("      Login Screen");
        cout << '\n';
        cout << "Invalid Username/Password!\n";
        User.Name = ReadString("Enter Username? ");
        User.Password = ReadString("Enter Password? ");
    }

    system("cls");
    MainControlPanel(User);
}


int main()
{
    Login();
    system("pause>0");
    //cout << (16 & -1) << endl;
}
