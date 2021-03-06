#include <iostream>
#include <string>
#include <algorithm>
#include <windows.h>
#include <map>

using namespace std;
string getpass(const char* prompt, bool show_asterisk);
void initializeUsers(map<string,string> &users);

int main()
{
    string loggingUser;
    map<string, string> users;

    initializeUsers(users);

    cout << "Insert username: ";
    cin >> loggingUser;

    std::for_each(loggingUser.begin(), loggingUser.end(), [](char& c) {c = ::tolower(c);});

    string password = getpass("Please enter the password: ", true); // Show asterisks

	if (users[loggingUser] == password) {
		cout << "Welcome " << loggingUser << "!" << endl;
	}
	else {
		cout << "I don't know you" << endl;
	}
}

void initializeUsers(map<string, string> &users) {
    users["charles"] = "Magn3";
    users["link"] = "TriCourage";
    users["luigi"] = "BlikeMario";
}

string getpass(const char* prompt, bool show_asterisk = true)
{
    const char BACKSPACE = 8;
    const char RETURN = 13;

    string password;
    unsigned char ch = 0;

    cout << prompt << endl;

    DWORD con_mode;
    DWORD dwRead;

    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

    GetConsoleMode(hIn, &con_mode);
    SetConsoleMode(hIn, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

    while (ReadConsoleA(hIn, &ch, 1, &dwRead, NULL) && ch != RETURN)
    {
        if (ch == BACKSPACE)
        {
            if (password.length() != 0)
            {
                if (show_asterisk)
                    cout << "\b \b";
                password.resize(password.length() - 1);
            }
        }
        else
        {
            password += ch;
            if (show_asterisk)
                cout << '*';
        }
    }
    cout << endl;
    return password;
}
