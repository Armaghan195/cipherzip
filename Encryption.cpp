#include "Encryption.h"
#include <iostream>

ListNode* Encryption::createLinkedList(const string& text)
{
	ListNode* head = new ListNode(text[0]);
	ListNode* current = head;

	for (size_t i = 1; i < text.length(); ++i)
	{
		current->next = new ListNode(text[i]);
		current = current->next;
	}

	return head;
}

void Encryption::deleteLinkedList(ListNode* head)
{
	while (head)
	{
		ListNode* temp = head;
		head = head->next;
		delete temp;
	}
}



