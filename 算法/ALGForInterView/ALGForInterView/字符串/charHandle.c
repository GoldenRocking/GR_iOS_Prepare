//
//  charHandle.c
//  ALGForInterView
//
//  Created by guoruiqing on 2021/2/18.
//

#include "charHandle.h"

// 字符串反转
void char_reverse(char *cha)
{
    // 定义头部指针
    char *begin = cha;
    
    // 定义尾部指针
    char *end = cha + strlen(cha) - 1;
    
    while (begin < end) {
        char temp = *begin;
        *(begin++) = *end;
        *(end--) = temp;
    }
    
}

// 查找第一个只出现一次的字符
char findFirstChar(char* cha)
{
    char result = '\0';
    
    // 定义一个数组 用来存储各个字母出现次数
    int array[256];
    
    // 对数组进行初始化操作
    for(int i = 0;i < 256;i++){
        array[i] = 0;
    }
    
    // 定义一个指针 指向当前字符串头部
    char *p = cha;
    // 遍历每个字符
    while (*p != '\0') {
        // 在字母对应存储位置 进行出现次数+1操作
        array[*(p++)]++;
    }
    
    // 将P指针重新指向字符串头部
    p = cha;
    // 遍历每个字母的出现次数
    while (*p != '\0') {
        // 遇到第一个出现次数为1的字符，打印结果
        if(array[*p] == 1)
        {
            result = *p;
            break;;
        }
        
        p++;
    }
    
    return result;
}
