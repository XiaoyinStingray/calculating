#include<stdio.h>
int main(){
    unsigned short a[65536]={0};
    short c=-3;
    unsigned short b=(unsigned short)c;
    printf("%d %d",b,a[b]);
}
