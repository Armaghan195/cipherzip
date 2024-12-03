#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
#include <iostream>

using namespace std;

struct ListNode
{
	char data;
	ListNode* next;

	ListNode(char c) : data(c), next(NULL){}

};

class Encryption
{
private:
	static ListNode* createLinkedList(const string& text);
	static void deleteLinkedList(ListNode* head);
};


#endif
