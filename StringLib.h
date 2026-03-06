#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};


const string ClientsFileName = "ClientData";

namespace StringLib {

    string ReadString()
    {
        string S1;
        cout << "Please Enter Your String?\n";
        getline(cin, S1);
        return S1;
    }

    void PrintFirstLetterOfEachWord(string Sentence)
    {
        if (Sentence.empty())
            return;
        if (Sentence.at(0) != ' ')
            cout << Sentence.at(0) << endl;
        for (int i = 0; i < Sentence.length() - 1; i++)
        {
            if ((Sentence.at(i) == ' ') && (Sentence.at(i + 1) != ' '))
                cout << Sentence.at(i + 1) << endl;
        }
    }

    string UpperCaseTheFirstLetterOfEachWord(string Sentence)
    {
        if (Sentence.empty())
            return Sentence;
        if (Sentence[0] != ' ')
            Sentence[0] = toupper(Sentence[0]); // toupper returns int (ASCII), so we cast it to char
        for (int i = 1; i < Sentence.length(); i++)
        {
            if (Sentence[i - 1] == ' ' && Sentence[i] != ' ')
                Sentence[i] = toupper(Sentence[i]);
        }
        return Sentence;
    }

    string LowerCaseTheFirstLetterOfEachWord(string Sentence)
    {
        if (Sentence.empty())
            return Sentence;
        if (Sentence[0] != ' ')
            Sentence[0] = tolower(Sentence[0]); // toupper returns int (ASCII), so we cast it to char
        for (int i = 1; i < Sentence.length(); i++)
        {
            if (Sentence[i - 1] == ' ' && Sentence[i] != ' ')
                Sentence[i] = tolower(Sentence[i]);
        }
        return Sentence;
    }

    string LowerCase2TheFirstLetterOfEachWord(string Sentence)
    {
        bool IsFirstWord = true;

        for (int i = 0; i < Sentence.length(); i++)
        {
            if (Sentence[i] != ' ' && IsFirstWord)
                Sentence[i] = tolower(Sentence[i]);
            IsFirstWord = (Sentence[i] == ' ') ? true : false;
        }
        return Sentence;
    }

    string UpperAllLetters(string Sentence)
    {
        for (int i = 0; i < Sentence.length(); i++)
        {
            Sentence[i] = toupper(Sentence[i]);
        }
        return Sentence;
    }

    string LowerAllLetters(string Sentence)
    {
        for (int i = 0; i < Sentence.length(); i++)
        {
            Sentence[i] = tolower(Sentence[i]);
        }
        return Sentence;
    }

    char ReadChar()
    {
        char A;
        cout << "Please Enter a Character?\n";
        cin >> A;
        return A;
    }

    char invertChar(char A)
    {
        return (isupper(A)) ? tolower(A) : toupper(A);
    }

    void invertAndPrintChar(char A)
    {
        A = (isupper(A)) ? tolower(A) : toupper(A);
        cout << A;
    }

    string InvertingLettersInString(string Str)
    {
        for (int i = 0; i < Str.length(); i++)
        {
            Str.at(i) = StringLib::invertChar(Str.at(i));
        }
        return Str;
    }

    short CharacterRepetitionInString(const string& Str, char& Character)
    {
        int Counter = 0;
        for (char C : Str)
        {
            if (C == Character)
                Counter++;
        }
        return Counter;
    }

    int RepetitionInLetterInEveryCase(const string& Str, char C)
    {
        short Counter = 0;
        char CharInLoop = toupper(C);
        for (char n : Str)
        {
            if (toupper(n) == CharInLoop)
                Counter++;
        }
        return Counter;
    }

    bool IsVowel(char C)
    {
        C = tolower(C);
        switch (C)
        {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
        default:
            return false;
        }
    }

    int NumberOfVowels(string Str)
    {
        int Counter = 0;
        for (int i = 0; i < Str.length(); i++) // better to use Ranged loop
        {
            if (StringLib::IsVowel(Str.at(i)))
                Counter++;
        }
        return Counter;
    }

    void PrintVowelsFromString(const string& Str)
    {
        for (const char& C : Str)
        {
            if (StringLib::IsVowel(C))
                cout << "\t" << C;
        }
    }

    void PrintEachWordInString(string S1)
    {
        string delim = " "; // delimiter

        cout << "\nYour string words are: \n\n";
        short pos = 0;
        string sWord; // define a string variable

        // use find() function to get the position of the delimiters
        while ((pos = S1.find(delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos); // store the word
            if (sWord != "")
                cout << sWord << endl;

            S1.erase(0, pos + delim.length()); /* erase() until
            postion and move to next word. */
        }
        if (S1 != "")
        {
            cout << S1 << endl; // it print last word of the string
        }
    }

    vector <string> SplitString(string Str, string Delim)
    {
        vector <string> vStr;
        int pos;
        string sWord;
        while ((pos = Str.find(Delim)) != string::npos)
        {
            sWord = Str.substr(0, pos);
            if (sWord != "")
                vStr.push_back(sWord);

            Str.erase(0, pos + Delim.length());
        }
        if (Str != "")
            vStr.push_back(Str);

        return vStr;
    }

    int CountWordsInString(string Str)
    {
        int pos;
        string Space = " ";
        string sWord;
        int Counter = 0;
        while ((pos = Str.find(Space)) != string::npos)
        {
            sWord = Str.substr(0, pos);
            if (sWord != "")
                Counter++;
            Str.erase(0, pos + Space.length());
        }
        if (Str != "")
            Counter++;
        return Counter;
    }


    string TrimLeft(string S1)
    {
        for (short i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ')
                return S1.substr(i, S1.length() - i);
        }
        return "";
    }

    string TrimRight(string S1)
    {
        for (short i = S1.length() - 1; i >= 0; i--)
            if (S1[i] != ' ')
                return S1.substr(0, i + 1);
        return "";
    }

    string Trim(string S1)
    {
        return TrimRight(TrimLeft(S1));
    }

    //string JoinString(const vector <string>& vStr, string Delimiter)
    //{
    //    if (vStr.empty())
    //        return "";
    //    string JoinedString = "";
    //    for (int i = 0; i < vStr.size() - 1; i++)
    //    {
    //        JoinedString += vStr[i];  // += is imprtant لمنع حالات النسخ المؤقت!
    //        JoinedString += Delimiter; // اضافة عنصر عنصر هو الصح!
    //    }
    //    JoinedString.append(vStr[vStr.size() - 1]);
    //    return JoinedString;
    //}

    string JoinString(const vector <string>& vString, string Delim)
    {
        if (vString.empty())
            return "";
        string S1 = "";
        for (const string& s : vString)
        {
            S1 += s;
            S1 += Delim;
        }
        return S1.substr(0, S1.length() - Delim.length());
    }

    string JoinString(const string arrString[], int Length, string Delimiter)
    {

        if (Length == 0) // السهم هذا دليل على انه pointer من نوع struct
            return "";
        string Str = "";
        for (int i = 0; i < Length; i++)
        {
            Str += arrString[i];
            Str += Delimiter;
        }
        return Str.substr(0, Str.length() - Delimiter.length());
    }

    string ReverseWordsInString(string S1)
    {
        vector <string> vString;
        string S2 = "";

        vString = SplitString(S1, " ");

        // declare iterator
        vector <string>::iterator iter = vString.end();

        while (iter != vString.begin())
        {
            --iter; // طرح اول عشان vString.end() ببدأ من بعد العنصر الاخير

            S2 += *iter;
            S2 += " ";
        }

        S2 = S2.substr(0, S2.length() - 1);

        return S2;
    }

    string ReplaceWord(string Str, string WordToReplace, string Word)
    {
        int PostionOfWord = 0;
        int PostionOfSearch = 0;
        if (Str.empty())
            return "";

        while ((PostionOfWord = Str.find(WordToReplace, PostionOfSearch)) != string::npos)
        {
            Str.replace(PostionOfWord, WordToReplace.length(), Word);
            PostionOfSearch = PostionOfWord + Word.length();
        }
        return Str;
    }

    string RemovePunctuationsFromString(string Str)
    {
        string NewStr = "";
        for (int i = 0; i < Str.length(); i++)
            if (!ispunct(Str[i]))
                NewStr += Str[i];
        return NewStr;
    }

    string ReplaceWordInStringUsingSplit(string S1, string StringToReplace, string sReplaceTo, bool MatchCase = true)
    {
        vector <string> vString = StringLib::SplitString(S1, " ");

        for (string& s : vString)
        {
            if (MatchCase)
            {
                if (s == StringToReplace)
                    s = sReplaceTo;
            }
            else
            {
                if (StringLib::LowerAllLetters(s) == StringLib::LowerAllLetters(StringToReplace))
                    s = sReplaceTo;
            }
        }

        return StringLib::JoinString(vString, " ");
    }

    stClient ConvertLineToRecord(string Line, string Seperator = "#//#")
    {
        stClient Client;
        vector <string> vClientData;

        vClientData = StringLib::SplitString(Line, Seperator);

        Client.AccountNumber = vClientData[0];
        Client.PinCode = vClientData[1];
        Client.Name = vClientData[2];
        Client.Phone = vClientData[3];
        Client.AccountBalance = stod(vClientData[4]);//cast string to
        // double
        return Client;
    }



    void PrintClientCard(stClient Client)
    {
        cout << "\nThe following is the extracted client record:\n";
        cout << "---------------------------------------------";
        cout << "\nAccout Number : " << Client.AccountNumber;
        cout << "\nPin Code      : " << Client.PinCode;
        cout << "\nName          : " << Client.Name;
        cout << "\nPhone         : " << Client.Phone;
        cout << "\nAccount Balance: " << Client.AccountBalance;
        cout << "\n--------------------------------------------";

    }

    stClient ReadNewClient()
    {
        stClient Client;

        cout << "Enter Account Number? ";
        getline(cin >> ws, Client.AccountNumber);

        cout << "Enter PinCode? ";
        getline(cin, Client.PinCode);

        cout << "Enter Name? ";
        getline(cin, Client.Name);

        cout << "Enter Phone? ";
        getline(cin, Client.Phone);

        cout << "Enter AccountBalance? ";
        cin >> Client.AccountBalance;

        return Client;
    }

    string ConvertRecordToLine(stClient Client, string Seperator = "#//#")
    {
        string stClientRecord = "";

        stClientRecord += Client.AccountNumber + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += Client.Name + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += to_string(Client.AccountBalance); // When we convert digit to string, it brings with it many zeros

        return stClientRecord;
    }

    vector <stClient> LoadCleintsDataFromFile(string FileName)
    {
        vector <stClient> vClients;
        fstream MyFile;
        MyFile.open(FileName, ios::in);//read Mode
        if (MyFile.is_open())
        {
            string Line;
            stClient Client;
            while (getline(MyFile, Line))
            {
                Client = ConvertLineToRecord(Line);
                vClients.push_back(Client);
            }
            MyFile.close();
        }
        return vClients;
    }

    bool FindClientByAccountNumber(string AccountNumber, stClient&
        Client)
    {
        vector <stClient> vClients =
            LoadCleintsDataFromFile(ClientsFileName);
        for (stClient C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                Client = C;
                return true;
            }
        }
        return false;
    }

    vector <string> ExtractDataFromFile(string FileName)
    {
        vector <string> vClientData;
        fstream File;
        File.open(FileName, ios::in);

        if (File.is_open())
        {
            string Line;
            while (getline(File, Line))
                if (Line != "")
                    vClientData.push_back(Line);
            File.close();
        }
        return vClientData;
    }

    string SearchForAccountNumber(const vector <string>& vClientData, string AccountNumber)
    {
        if (vClientData.empty())
            return "";
        for (const string& n : vClientData)
        {
            if ((n.find(AccountNumber)) != std::string::npos)
                return n;
        }
        return "";
    }

    bool FindClientByAccountNumber(const string AccountNumber, const vector <stClient>& vClients, stClient& Client)
    {
        for (const stClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                Client = C;
                return true;
            }
        }
        return false;
    }

    bool MarkClientForDeleteByAccountNumber(const string AccountNumber, vector <stClient>& vClients)
    {
        for (stClient& C : vClients)
            if (C.AccountNumber == AccountNumber)
            {
                C.MarkForDelete = true;
                return true;
            }
        return false;
    }


    void SaveClientsDataToFile(string FileName, const vector <stClient>& vClients)
    {
        fstream MyFile;
        MyFile.open(FileName, ios::out); // overwrite

        string DataLine;

        if (MyFile.is_open())
        {
            for (const stClient& C : vClients)
                if (C.MarkForDelete == false)
                {
                    // we only write records that are not marked for delete
                    DataLine = ConvertRecordToLine(C);
                    MyFile << DataLine << endl;
                }

            MyFile.close();
        }
    }

    vector <stClient> LoadClientsDataFromFile(string FileName)
    {
        vector <stClient> vClients;
        fstream MyFile;
        MyFile.open(FileName, ios::in);//read Mode
        if (MyFile.is_open())
        {
            string Line;
            stClient Client;
            while (getline(MyFile, Line))
            {
                Client = ConvertLineToRecord(Line);
                vClients.push_back(Client);
            }
            MyFile.close();
        }
        return vClients;
    }

    bool DeleteClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
    {
        bool Delete = false;
        stClient Client;
        char Answer = 'n';

        if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        {
            PrintClientCard(Client);

            cout << "\n\nAre you sure you want delete delete this Client? y/n ? ";
            cin >> Answer;

            if (tolower(Answer) == 'y')
            {
                MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
                SaveClientsDataToFile(ClientsFileName, vClients);

                // Refresh Clients
                vClients = LoadClientsDataFromFile(ClientsFileName);

                cout << "\n\nClient Deleted Successfully.";
                Delete = true;
            }
        }
        else
        {
            cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        }
        return Delete;
    }

    void HeaderFrame(short Length)
    {
        for (int i = 0; i <= Length; i++)
            cout << '_';
    }

    void SetRight(const int Space, const string& WordToPostion)
    {
        cout << WordToPostion << setw(Space - WordToPostion.length());
    }

    void ClientInfoHeader(int NumberOfClients)
    {
        cout << setw(40) << ""
            << "Client List (" << NumberOfClients
            << ") Client(s).\n";
        HeaderFrame(110);
        cout << "\n\n";
        cout << "| ";
        SetRight(20, "Account Number");
        cout << "| ";
        SetRight(15, "Pin Code");
        cout << "| ";
        SetRight(35, "Client Name");
        cout << "| ";
        SetRight(15, "Phone");
        cout << "| ";
        SetRight(15, "Balance");
        cout << '\n';
        HeaderFrame(110);
        cout << endl;
    }

    void FillTableRow(const stClient &ClientInfo)
    {
        cout << "| ";
        SetRight(20, ClientInfo.AccountNumber);
        cout << "| ";
        SetRight(15, ClientInfo.PinCode);
        cout << "| ";
        SetRight(35, ClientInfo.Name);
        cout << "| ";
        SetRight(15, ClientInfo.Phone);
        cout << "| ";
        SetRight(15, to_string(ClientInfo.AccountBalance));
        cout << '\n';
    }

    void TableOfClientData(const vector <stClient>& vClientData)
    {
        ClientInfoHeader(vClientData.size());
        for (const stClient& n : vClientData)
        {
            FillTableRow(n);
        }
        cout << '\n';
        HeaderFrame(110);
    }
  
    string ReadAccountNumber()
    {
        string AccountNumber;
        cout << "Please enter Account Number? \n";
        getline(cin >> ws, AccountNumber);
        return AccountNumber;
    }

    double ReadNumber(string Message)
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
}