//
//  arrayList.c
//  ALGForInterView
//
//  Created by guoruiqing on 2021/2/18.
//

#include "arrayList.h"

int PartSort(int a[], int start, int end);

void mergeList(int a[], int aLen, int b[], int bLen, int result[])
{
    int p = 0; //遍历数组a的指针
    int q = 0; //遍历数组b的指针
    int i = 0; //记录当前存储位置
    
    //任意数组没有到达边界则进行遍历
    while (p < aLen && q < bLen) {
        // 如果a数组对应位置的值小于b数组对应位置的值
        if(a[p] <= b[q]){
            // 存储a数组的值
            result[i] = a[p];
            // 移动a数组的遍历指针
            p++;
        }else
        {
            // 存储b数组的值
            result[i] = b[q];
            // 移动b数组的遍历指针
            q++;
        }
        // 指向合并结果的下一个存储位置
        i++;
    }
    
    // 如果a数组有剩余
    while (p < aLen) {
        // 将a数组剩余部分拼接到合并结果的后面
        result[i] = a[p++];
        i++;
    }
    
    // 如果b数组有剩余
    while (q < bLen) {
        // 将b数组剩余部分拼接到合并结果的后面
        result[i] = b[q++];
        i++;
    }
}


//求一个无序数组的中位数
int findMedian(int a[], int aLen)
{
    int low = 0;
    int high = aLen - 1;
    
    int mid = (aLen - 1) / 2;
    int div = PartSort(a, low, high);
    
    while (div != mid) {
        if(mid < div)
        {
            //左半区间找
            div = PartSort(a, low, div - 1);
        }else
        {
            //右半区间找
            div = PartSort(a, div + 1, high);
        }
    }
    
    return a[mid];
}

int PartSort(int a[], int start, int end)
{
    int low = start;
    int high = end;
    
    //选取关键字
    int key = a[end];
    
    while (low < high) {
        //左边找比key大的值
        while (low < high && a[low] <= key) {
            ++low;
        }
        
        //右边找比key小的值
        while (low < high && a[high] >= key) {
            --high;
        }
        
        if(low < high)
        {
            //找到之后交换左右的值
            int temp = a[low];
            a[low] = a[high];
            a[high] = temp;
        }
    }
    
    int temp = a[high];
    a[high] = a[end];
    a[end] = temp;
    return  low;
}

//冒泡排序
/**
 *    【冒泡排序】：相邻元素两两比较，比较完一趟，最值出现在末尾
 *    第1趟：依次比较相邻的两个数，不断交换（小数放前，大数放后）逐个推进，最值最后出现在第n个元素位置
 *    第2趟：依次比较相邻的两个数，不断交换（小数放前，大数放后）逐个推进，最值最后出现在第n-1个元素位置
 *     ……   ……
 *    第n-1趟：依次比较相邻的两个数，不断交换（小数放前，大数放后）逐个推进，最值最后出现在第2个元素位置
 */
void maopaoOrder()
{
    int a[10] = {3,2,1,4,5,0,6,7,9,8};
    int temp = 0;
    
    for(int i = 0; i < 10 - 1;i++){
        
        for(int j = 0; j < 10 - i - 1;j++){
            
            if(a[j] > a[j+1]){
                temp = a[j+1];
                a[j+1] = a[j];
                a[j] = temp;
            }
        }
    }
    
    for(int i = 0; i < 10;i++)
    {
        printf("%i ",a[i]);
    }
}

/**
 *    【选择排序】：最值出现在起始端
 *
 *    第1趟：在n个数中找到最小(大)数与第一个数交换位置
 *    第2趟：在剩下n-1个数中找到最小(大)数与第二个数交换位置
 *    重复这样的操作...依次与第三个、第四个...数交换位置
 *    第n-1趟，最终可实现数据的升序（降序）排列。
 *
 */

void selectSort(int *arr, int length)
{
    for(int i = 0; i < length - 1;i++){
        for(int j = i + 1; j < length;j++){
            if(arr[i] > arr[j]){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

/**
 *    折半查找：优化查找时间（不用遍历全部数据）
 *
 *    折半查找的原理：
 *   1> 数组必须是有序的
 *   2> 必须已知min和max（知道范围）
 *   3> 动态计算mid的值，取出mid对应的值进行比较
 *   4> 如果mid对应的值大于要查找的值，那么max要变小为mid-1
 *   5> 如果mid对应的值小于要查找的值，那么min要变大为mid+1
 *
 */
 
// 已知一个有序数组, 和一个key, 要求从数组中找到key对应的索引位置
int findKey(int *arr, int length, int key)
{
    int min = 0, max = length - 1, mid;
    while (min <= max) {
        mid = (min + max) / 2;
        if(key > arr[mid]){
            min = mid + 1;
        }else if(key < arr[mid]){
            max = mid - 1;
        }else{
            return  mid;
        }
    }
    
    return -1;
}



















