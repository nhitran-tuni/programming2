#include <iostream>

using namespace std;

bool Repeat_char(string key)
{
    bool repeat = true;
    int len = key.length();
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (key.at(i) == key.at(j)) {
                repeat = false;
                break;
            }
        }
    }
    return repeat;
}

string Change_text(string key, string text)
{
    string origin_key = "abcdefghijklmnopqrstuvwxyz";
    string result;
    int index;
    int len = text.length();
    for (int i = 0; i < len; i++) {
        index = origin_key.find(text.at(i));
        result += key.at(index);
    }
    return result;
}

int main()
{
    string key;
    cout << "Enter the encryption key: ";
    cin >> key;

    bool repeat = Repeat_char(key);

    if (key.length() != 26) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
    }
    else if (repeat == 0) {
        cout << "Error! The encryption key must contain all alphabets a-z." << endl;
    }
    else for(int i = 0; i < 26; i++){
        if (isupper(key.at(i))) {
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            break;
        }
        else{
            string text;
            cout << "Enter the text to be encrypted: ";
            cin >> text;
            string result = Change_text(key, text);
            cout << "Encrypted text: " << result << endl;
        }
    }
}
