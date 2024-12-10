#include "Encryption.h"
#include <iostream>
#include <cctype>
#include <fstream>

listnode* encryption::createlinkedlist(const std::string& text) {
    if (text.empty()) return nullptr;

    listnode* head = new listnode(text[0]);
    listnode* current = head;

    for (size_t i = 1; i < text.length(); ++i) {
        current->next = new listnode(text[i]);
        current = current->next;
    }

    return head;
}

void encryption::deletelinkedlist(listnode* head) {
    while (head) {
        listnode* temp = head;
        head = head->next;
        delete temp;
    }
}

listnode* encryption::generatekeylist(listnode* texthead, const std::string& key)
{
    if (!texthead || key.empty())
        return NULL;

    listnode* keyhead = NULL;
    listnode* currentkeynode = NULL;

    int keylength = key.length();
    int keyindex = 0;

    listnode* currenttextnode = texthead;

    while (currenttextnode)
    {
        if (isalpha(currenttextnode->data))
        {
            char keychar = key[keyindex % keylength];
            listnode* newnode = new listnode(keychar);

            if (!keyhead)
            {
                keyhead = newnode;
                currentkeynode = keyhead;

            }
            else
            {
                currentkeynode->next = newnode;
                currentkeynode = currentkeynode->next;
            }

            ++keyindex;

        }

        else
        {
            listnode* newnode = new listnode(currenttextnode->data);

            if (!keyhead)
            {
                keyhead = newnode;
                currentkeynode = keyhead;
            }
            else
            {
                currentkeynode->next = newnode;
                currentkeynode = currentkeynode->next;
            }

        }

        currenttextnode = currenttextnode->next;
    }
    return keyhead;
}



listnode* encryption::encrypttext(listnode* plaintexthead, listnode* keyhead)
{
    if (!plaintexthead || !keyhead)
        return NULL;

    listnode* chipertexthead = NULL;
    listnode* currentchipernode = NULL;

    listnode* currentplainnode = plaintexthead;
    listnode* currentkeynode = keyhead;

    while (currentplainnode || currentkeynode)
    {
        char plainchar = currentplainnode->data;
        char keychar = currentkeynode->data;

        char encryptedchar;

        if (isalpha(plainchar))
        {
            char base = isupper(plainchar) ? 'A' : 'a';
            char basekey = islower(keychar) ? 'A' : 'a';

            encryptedchar = static_cast<char>(base + (plainchar - base + (plainchar - base)) % 26);  // fourmulaaaaaaaaaaaaaaaaaaaa

        }
        else
        {
            encryptedchar = plainchar;

        }

        listnode* newnode = new listnode(encryptedchar);

        if (!chipertexthead)
        {
            chipertexthead = newnode;
            currentchipernode = chipertexthead;
        }
        else
        {
            currentchipernode->next = newnode;
            currentchipernode = currentchipernode->next;

        }

        currentplainnode = currentplainnode->next;
        currentkeynode = currentkeynode->next;

    }

    return chipertexthead;
}


listnode* encryption::decrypttext(listnode* ciphertexthead, listnode* keyhead)
{
    if (!ciphertexthead || !keyhead) 
        return NULL;

    listnode* plaintexthead = NULL;
    listnode* currentplainnode = NULL;

    listnode* currentciphertnode = ciphertexthead;
    listnode* currentkeynode = keyhead;

    while (currentciphertnode && currentkeynode) 
    {
        char cipherchar = currentciphertnode->data;
        char keychar = currentkeynode->data;

        char decryptedchar;

        if (isalpha(cipherchar)) 
        {
            char base = isupper(cipherchar) ? 'A' : 'a';
            char basekey = isupper(keychar) ? 'A' : 'a';

            decryptedchar = static_cast<char> ( base + (cipherchar - base - (keychar - basekey) + 26) % 26);
        }
        else 
        {
            decryptedchar = cipherchar;
        }

        listnode* newnode = new listnode(decryptedchar);

        if (!plaintexthead) 
        {
            plaintexthead = newnode;
            currentplainnode = plaintexthead;
        }
        else 
        {
            currentplainnode->next = newnode;
            currentplainnode = currentplainnode->next;
        }

        currentciphertnode = currentciphertnode->next;
        currentkeynode = currentkeynode->next;
    }

    return plaintexthead;
}

string encryption::linkedlisttostring(listnode* head)
{
    string result;
    listnode* current = head;

    while (current)
    {
        result += current->data;
        current = current->next;

    }

    return result;
}

bool encryption::encryptfile(const string& inputfilepath, const string& outputfilepath, const string& key)
{
    ifstream inputfile(inputfilepath);
    if (!inputfile.is_open())
    {
        cerr << "cannot open input file: " << inputfilepath << endl;
            return false;
    }
    
    string plaintext((istreambuf_iterator<char>(inputfile)), istreambuf_iterator<char>());
    inputfile.close();

    listnode* plaintexthead = createlinkedlist(plaintext);
    listnode* keyhead = generatekeylist(plaintexthead, key);

    listnode* ciphertexthead = encrypttext(plaintexthead, keyhead);
    string ciphertext = linkedlisttostring(ciphertexthead);

    ofstream outputfile(outputfilepath);
    if (!outputfile.is_open()) 
    {
        cerr << "cannot open output file: " << outputfilepath << endl;

        deletelinkedlist(plaintexthead);
        deletelinkedlist(keyhead);
        deletelinkedlist(ciphertexthead);

        return false;
    }

    outputfile << ciphertext;
    outputfile.close();

    deletelinkedlist(plaintexthead);
    deletelinkedlist(keyhead);
    deletelinkedlist(ciphertexthead);

    return true;

    
}

bool encryption::decryptfile(const string& inputfilepath, const string& outputfilepath, const string& key) 
{
    ifstream inputfile(inputfilepath);
    if (!inputfile.is_open()) 
    {
        cerr << "cannot open input file: " << inputfilepath << endl;
        return false;
    }

    string ciphertext((istreambuf_iterator<char>(inputfile)), istreambuf_iterator<char>());
    inputfile.close();

    listnode* ciphertexthead = createlinkedlist(ciphertext);
    listnode* keyhead = generatekeylist(ciphertexthead, key);

    listnode* plaintexthead = decrypttext(ciphertexthead, keyhead);

    string plaintext = linkedlisttostring(plaintexthead);

    ofstream outputfile(outputfilepath);
    if (!outputfile.is_open()) 
    {
        cerr << "cannot open output file: " << outputfilepath << endl;

        deletelinkedlist(ciphertexthead);
        deletelinkedlist(keyhead);
        deletelinkedlist(plaintexthead);

        return false;
    }

    outputfile << plaintext;
    outputfile.close();

    deletelinkedlist(ciphertexthead);
    deletelinkedlist(keyhead);
    deletelinkedlist(plaintexthead);

    return true;
}



