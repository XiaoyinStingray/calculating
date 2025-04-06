//author:zhao jun yu PB24061271
//Email:zhaojunyu0515@mail.ustc.edu.cn
//Project_2024.11-12:self-defined machine code operator

#include"function.h"
int main(){
    int a=0,b,t,wait=1;
    while (wait)
    {
    printf("********************************************\n");
    printf("*Please choose the way you put in:         *\n");
    printf("*I.  write by file(press '1')              *\n");
    printf("*II. write in person(press '2')            *\n");
    printf("*III.write by file(debug mode)(press '3')  *\n");
    printf("*IV.write in person(debug mode)(press '4') *\n");
    printf("*V.default mode(press '5')                 *\n");
    printf("*VI.default mode setting(press '6')        *\n");
    printf("*VI.create your GDB setting file(press '7')*\n");
    printf("*0.exit from the program(press '0')        *\n");
    printf("********************************************\n");
    scanf("%d",&t);     getchar();
    if(t==0) goto GG;
    if(t>=1&&t<=5) wait=0;
    if(t==1) a+=write_flie();
    else if(t==2) a+=write_person();
    else if(t==3){
        a+=write_flie();
        choice =1;}
    else if(t==4){
        a+=write_person();
        choice =1;}
    else if(t==5){
        a+=setting_in();
        if((!choice_halt)&&choice_gdb) a+=gdb_in();
        a+=defaultmode();
        }
    else if(t==6){
        a+=setting();//printf("%%\n");
    }
    else if(t==7){
        a+=gdb_selection();
    }
    else {printf("Error selection!\n");}
    if(a!=0) return 0;
} 

    if(choice){
        printf("debug mode:\nbefore running:\n");
        for(int i=1;i<number;i++) {
            outputbin(ram[i],16);
            printf(" %d\n",i);}
        debug();}
    //初始化
    regis_pc= 1;
    regis_cd= 2;
    while(state){
        //printf("1\n");
        if(choice) printf("%d\n",(short)regis_pc);
        unsigned short operand=ram[regis_pc];
        b=selection(operand);
        if(choice) printf("\nnzp:%d\n",(short)regis_cd);
        if(choice_halt) waiting();
        if((!choice_halt)&&choice_gdb){
            if(GDB[regis_pc]) waiting();
        }
        regis_pc++;
        if(b!=0) goto GG;
    }
GG:    if(choice) {printf("after running");debug();}
    printf("Thank you for your using!\n");
    return 0;
}