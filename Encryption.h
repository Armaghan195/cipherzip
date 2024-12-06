#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
#include <iostream>

using namespace std;

struct listnode {
	char data;
	listnode* next;

	listnode(char c) : data(c), next(nullptr) {}
};

class encryption
{
private:
	static listnode* createlinkedlist(const std::string& text);
	static void deletelinkedlist(listnode* head);
	static listnode* generatekeylist(listnode* texthead, const std::string& key);
	static listnode* encrypttext(listnode* plaintexthead, listnode* keyhead);
	static listnode* decrypttext(listnode* ciphertexthead, listnode* keyhead);
};


#endif
