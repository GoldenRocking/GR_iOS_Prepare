//
//  list.c
//  ALGForInterView
//
//  Created by guoruiqing on 2021/2/18.
//

#include "list.h"
#include <stdlib.h>

struct Node* reverseList(struct Node *head)
{
    // 定义遍历指针，初始化为头结点
    struct Node *p = head;
    // 反转后的链表头部
    struct Node *newH = NULL;
    
    // 遍历链表
    while (p != NULL) {
        // 记录下一个结点
        struct Node *temp = p->next;
        p->next = newH;
        // 当前结点的next指向新链表头部
        newH = p;
        // 移动p指针
        p = temp;
    }
    
    return newH;
}

// 构造一个链表
struct Node* constructList(void)
{
    //头节点定义
    struct Node *head = NULL;
    // 记录当前尾结点
    struct Node *cur = NULL;
    
    for(int i = 1;i < 5;i++){
        struct Node *node = malloc(sizeof(struct Node));
        node->data = i;
        
        // 头结点为空，新结点即为头结点
        if(head == NULL) {
            head = node;
        }else
        {
            // 当前结点的next为新结点
            cur->next = node;
        }
        
        //设置当前结点为新结点
        cur = node;
    }
    
    return head;
}


void printList(struct Node *head)
{
    struct Node* temp = head;
    while (temp != NULL) {
        printf("node is %d \n", temp->data);
        temp = temp->next;
    }
}
