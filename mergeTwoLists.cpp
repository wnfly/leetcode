#include "pch.h"
#include <iostream>
using namespace std;

struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

void PrintList(ListNode* head);

ListNode* mergeTwoLists_norepeat(ListNode* l1, ListNode* l2)
{
	ListNode *c = l1->val < l2->val ? l1 : l2;
	ListNode *head = c;
	while (l1 && l2)
	{
		if (!l1)
		{
			if (c->val != l2->val)
			{
				c->next = l2;
				break;
			}
			else
			{
				l2 = l2->next;
				continue;
			}
		}
		if (!l2)
		{
			if (c->val != l1->val)
			{
				c->next = l1;
				break;
			}
			else
			{
				l1 = l1->next;
				continue;
			}
		}
		if (l1->val < l2->val)
		{
			if (c->val != l1->val)
			{
				c->next = l1;
				c = c->next;
			}
			l1 = l1->next;
		}
		else if (l1->val > l2->val)
		{
			if (c->val != l2->val)
			{
				c->next = l2;
				c = c->next;
			}
			l2 = l2->next;
		}
		else
		{
			if (c->val != l1->val)
			{
				c->next = l1;
				c = c->next;
			}
			l1 = l1->next;
			l2 = l2->next;
		}
	}

	return head;
}

ListNode* mergeTwoLists_my(ListNode* l1, ListNode* l2)
{
	if (!l1)
		return l2;
	if (!l2)
		return l1;

	ListNode *c = NULL;
	if (l1->val <= l2->val)
	{
		c = l1;
		l1 = l1->next;
	}
	else
	{
		c = l2;
		l2 = l2->next;
	}
	ListNode *head = c;

	while (l1 && l2)
	{
		if (l1->val <= l2->val)
		{
			c->next = l1;
			l1 = l1->next;
			c = c->next;
		}
		else
		{
			c->next = l2;
			l2 = l2->next;
			c = c->next;
		}
	}
	if (!l1)
		c->next = l2;
	if (!l2)
		c->next = l1;

	return head;
}

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
{
	ListNode head(-1), *c = &head;
	while (l1 && l2)
	{
		if (l1->val <= l2->val)
		{
			c->next = l1;
			l1 = l1->next;
			c = c->next;
		}
		else
		{
			c->next = l2;
			l2 = l2->next;
			c = c->next;
		}
	}
	if (!l1)
		c->next = l2;
	if (!l2)
		c->next = l1;

	return head.next;
}

ListNode* mergeTwoLists_5ms_sample(ListNode* l1, ListNode* l2)
{
	ListNode *res = new ListNode(-1), *cur = res;
	while (l1 && l2) {
		if (l1->val <= l2->val) {
			cur->next = l1;
			cur = cur->next;
			l1 = l1->next;
		}
		else {
			cur->next = l2;
			cur = cur->next;
			l2 = l2->next;
		}
	}
	if (l1) {
		cur->next = l1;
	}
	if (l2) {
		cur->next = l2;
	}
	return res->next;
}

int mainmt()
{
	ListNode l3(4);
	ListNode l2(2);
	l2.next = &l3;
	ListNode l1(1);
	l1.next = &l2;

	ListNode l6(4);
	ListNode l5(3);
	l5.next = &l6;
	ListNode l4(1);
	l4.next = &l5;

	ListNode *c = mergeTwoLists(&l1, &l4);
	PrintList(c);

	return 0;
}

void PrintList(ListNode* head)
{
	while (head)
	{
		cout << head->val << " ";
		head = head->next;
	}
	cout << endl;
}