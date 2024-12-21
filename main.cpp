#include <iostream>
#include <string>
#include "encryption.h"
#include "Compression.h"
using namespace std;

int main() {
    string infile = "input.txt";
    string encryptedfile = "encrypted.txt";
    string decryptedfile = "decrypted.txt";
    string compressedfile = "compressed.gz";
    string decompressedfile = "decompressed.txt";
    string key = "keyword";

    while (true) {
        cout << "menu:\n";
        cout << "1. encrypt file\n";
        cout << "2. decrypt file\n";
        cout << "3. compress file\n";
        cout << "4. decompress file\n";
        cout << "5. exit\n";
        cout << "enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "enter input file path: ";
            cin >> infile;
            cout << "enter output encrypted file path: ";
            cin >> encryptedfile;
            cout << "enter key: ";
            cin >> key;
            if (encryption::encryptfile(infile, encryptedfile, key)) {
                cout << "encryption successful\n";
            }
            else {
                cout << "encryption failed\n";
            }
        }
        else if (choice == 2) {
            cout << "enter input encrypted file path: ";
            cin >> encryptedfile;
            cout << "enter output decrypted file path: ";
            cin >> decryptedfile;
            cout << "enter key: ";
            cin >> key;
            if (encryption::decryptfile(encryptedfile, decryptedfile, key)) {
                cout << "decryption successful\n";
            }
            else {
                cout << "decryption failed\n";
            }
        }
        else if (choice == 3) {
            cout << "enter input file path: ";
            cin >> infile;
            cout << "enter output compressed file path: ";
            cin >> compressedfile;
            if (Compression::compressFile(infile, compressedfile)) {
                cout << "compression successful\n";
            }
            else {
                cout << "compression failed\n";
            }
        }
        else if (choice == 4) {
            cout << "enter input compressed file path: ";
            cin >> compressedfile;
            cout << "enter output decompressed file path: ";
            cin >> decompressedfile;
            if (Compression::decompressFile(compressedfile, decompressedfile)) {
                cout << "decompression successful\n";
            }
            else {
                cout << "decompression failed\n";
            }
        }
        else if (choice == 5) {
            break;
        }
        else {
            cout << "invalid choice\n";
        }
    }

    return 0;
}
