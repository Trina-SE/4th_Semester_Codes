#include <bits/stdc++.h>

using namespace std;

int main() {
    string s1;
    getline(cin, s1); // get the whole line as input
    cout << "string: " << s1 << endl;

    // Define a map to store the character and its hexadecimal value
    map<int, int> m;

    for (int i = 0; i < s1.size(); i++) {
        int character = int(s1[i]); // converting each character to its ASCII value
        stringstream store;
        store << hex << character; // convert character to hexadecimal and store in stringstream
        int hexValue;
        store >> hex >> hexValue; // convert the stringstream back to an integer in hexadecimal format
        m[character] = hexValue; // store the character and its hexadecimal value in the map
    }

    // Now you can iterate over the map and print the character and its hexadecimal value
    cout << "Character and Hexadecimal Value:" << endl;
    for (const auto& pair : m) {
        cout << "Character: " << char(pair.first) << ", Hexadecimal Value: " << hex << pair.second << endl;
    }

    return 0;
}
