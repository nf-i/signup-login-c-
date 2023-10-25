#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

namespace UserData {

    const string FILE_PATH = "user_data.txt";

    map<string, string> load() {
        map<string, string> user_data;
        ifstream file(FILE_PATH);

        if (file.is_open()) {
            string username, password;
            while (file >> username >> password) {
                user_data[username] = password;
            }
            file.close();
        }

        return user_data;
    }

    void save(const map<string, string>& user_data) {
        ofstream file(FILE_PATH);

        if (file.is_open()) {
            for (const auto& entry : user_data) {
                file << entry.first << " " << entry.second << "\n";
            }
            file.close();
        }
    }

    void sign_up() {
        string username, password;

        cout << "Enter your username: ";
        cin >> username;

        cout << "Enter your password: ";
        cin >> password;

        map<string, string> user_data = load();

        if (user_data.find(username) != user_data.end()) {
            cout << "Username already exists. Please choose a different one.\n";
            return;
        }

        user_data[username] = password;
        save(user_data);

        cout << "Sign up successful!\n";
    }

    void login() {
        string username, password;

        cout << "Enter your username: ";
        cin >> username;

        cout << "Enter your password: ";
        cin >> password;

        map<string, string> user_data = load();

        auto it = user_data.find(username);
        if (it != user_data.end() && it->second == password) {
            cout << "Welcome, " << username << "!\n";
        } else {
            cout << "Invalid username or password. Please try again.\n";
        }
    }
}

int main() {
    while (true) {
        cout << "\n1. Sign Up\n";
        cout << "2. Login\n";
        cout << "3. Quit\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                UserData::sign_up();
                break;
            case 2:
                UserData::login();
                break;
            case 3:
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}
