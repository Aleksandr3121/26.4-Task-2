#include <iostream>
#include <map>
#include <string>
#include <set>
#include <cstdint>

using namespace std;

class PhoneBook {
public:
    void Add(const string& name, uint64_t number) {
        if (!book_phones.insert({number, name}).second) {
            cerr << "This contact has already been saved" << endl;
        } else book_names[name].insert(number);
    }

    pair<uint64_t, bool> Request(const string& name) {
        auto it = book_names.find(name);
        if (it == book_names.end()) {
            cerr << "There is no such contact in the phone book" << endl;
            return {0, false};
        }
        return {*it->second.begin(), true};
    }

private:
    map<string, set<uint64_t>> book_names;
    map<uint64_t, string> book_phones;
};

class Telephone {
public:
    void Add(const string& name, const string& number) {
        if (name.empty() || number.empty()
            || number.substr(0, 2) != "+7"
            || !Checking(number)) {
            cerr << "Wrong format" << endl;
            return;
        }
        phoneBook.Add(name, stoull(number));
    }

    void Call(const string& input) {
        if (input.empty()) {
            cerr << "Wrong format" << endl;
            return;
        }
        if (input.substr(0, 2) == "+7") {
            //Проверка формата по условию
            if (!Checking(input)) {
                cerr << "Wrong format" << endl;
                return;
            }
            cout << "CALL " << input << endl;
        } else {
            auto p = phoneBook.Request(input);
            if (p.second)cout << "CALL +" << p.first << endl;
        }
    }

    void Sms(const string& input) {
        if (input.empty()) {
            cerr << "Wrong format" << endl;
            return;
        }
        if (input.substr(0, 2) == "+7") {
            //Проверка формата по условию
            if (!Checking(input)) {
                cerr << "Wrong format" << endl;
                return;
            }
            cout << "Enter the text of the SMS: ";
            string sms;
            cin.ignore(32767, '\n');
            getline(cin, sms);
            cout << "SMS sent to the number " << input << endl;
        } else {
            auto p = phoneBook.Request(input);
            if (p.second) {
                cout << "Enter the text of the SMS: ";
                string sms;
                cin.ignore(32767, '\n');
                getline(cin, sms);
                cout << "SMS sent to the number +" << p.first << endl;
            }
        }
    }

private:
    bool Checking(const string& number) {
        if (number.size() != 12)return false;
        bool first = true;
        for (size_t i = 2; i < number.size(); ++i) {
            if (first) {
                if (number[i] < '1' || number[i] > '9')return false;
            } else {
                if (number[i] < '0' || number[i] > '9')return false;
            }
            first = false;
        }
        return true;
    }

    PhoneBook phoneBook;
};

int main() {
    Telephone telephone;
    string input_str;
    string name;
    string number;
    while (cin >> input_str && input_str != "exit") {
        if (input_str == "add") {
            cout<<"Enter the contact name: ";
            cin >> name;
            cout<<"Enter the contact number: ";
            cin>>number;
            telephone.Add(name, number);
        } else if (input_str == "call") {
            cout<<"Enter the contact name or the contact number: ";
            cin >> input_str;
            telephone.Call(input_str);
        } else if (input_str == "sms") {
            cout<<"Enter the contact name or the contact number: ";
            cin >> input_str;
            telephone.Sms(input_str);
        } else cout << "Unknown command" << endl;
    }
    return 0;
}
