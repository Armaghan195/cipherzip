#include "Encryption.h"
#include <iostream>
#include <cctype>

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


listnode* encryption::decrypttext(listnode* chipertexthead, listnode* keyhead)
{

}



