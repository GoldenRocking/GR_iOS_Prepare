//
//  main.c
//  ALGForInterView
//
//  Created by guoruiqing on 2021/2/18.
//

#include <stdio.h>
#include "charHandle.h"
#include "arrayList.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    
    char ch[] = "Hello, World";
    char_reverse(ch);

    printf("\n");
    printf("%s",ch);
    printf("\n");
    printf("Hello, world\n");
    
    maopaoOrder();
    
    return 0;
}
