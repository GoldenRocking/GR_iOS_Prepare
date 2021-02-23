//
//  list.h
//  ALGForInterView
//
//  Created by guoruiqing on 2021/2/18.
//


#include <stdio.h>
struct Node{
    int data;
    struct Node *next;
};

// 链表反转
struct Node * reverseList(struct Node *head);

// 构造一个链表
struct Node* constructList(void);

// 打印链表中的数据
void printList(struct Node *head);
