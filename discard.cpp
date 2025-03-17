//name - Atharva Satavi 
//PRN - 2301106116

#include <iostream>
#include <bitset>
#include <string>

using namespace std;

string text_to_bits(const string &text) {
    string bit_string;
    for (char c : text) {
        bit_string += bitset<8>(c).to_string(); // Convert char to 8-bit binary
    }
    return bit_string;
}

string discard_last_row(const string &bit_string) {
    string key_54bit;
    for (size_t i = 0; i < 64; i++) {
        if ((i + 1) % 8 != 0) {
            key_54bit += bit_string[i];
        }
    }
    return key_54bit;
}

string generate_54bit_key(const string &user_key, string &bit_string) {
    if (user_key.length() != 8) {
        throw invalid_argument("Key must be exactly 8 characters long");
    }
    
    bit_string = text_to_bits(user_key);
    return discard_last_row(bit_string);
}

void print_bits_formatted(const string &bit_string, int group_size = 7) {//prints bit per line as per the given no of grp size 
    for (size_t i = 0; i < bit_string.length(); i++) {
        cout << bit_string[i];
        if ((i + 1) % group_size == 0) {
            cout << endl; // Print newline every group_size bits
        }
    }
    if (bit_string.length() % group_size != 0) {
        cout << endl;
    }
}

int main() {
    string user_key;
    cout << "Enter an 8-character key: ";
    cin >> user_key;
    
    try {
        string bit_string;
        string key_54bit = generate_54bit_key(user_key, bit_string);
        
        cout << "\n64-bit key representation:" << endl;
        print_bits_formatted(bit_string, 8);
        
        cout << "\nAfter discardation (54-bit key):" << endl;
        print_bits_formatted(key_54bit, 7);
    } catch (const invalid_argument &e) {
        cerr << e.what() << endl;
        return 1;
    }
    
    return 0;
}
