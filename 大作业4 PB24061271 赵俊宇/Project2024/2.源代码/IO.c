//author:zhao jun yu PB24061271
//Email:zhaojunyu0515@mail.ustc.edu.cn
//Project_2024.11-12:self-defined machine code operator

#include "function.h"
int write_flie(void){
    char *str;
    str=(char *)malloc(64*sizeof(char));
    printf("Please input the name of the file(including the file extension):\n");
    fflush(stdin);fflush(stdout);
    scanf("%s",str);
    FILE *file = fopen(str, "rt");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    int j=0,i=1;
    char ch;
    ch=fgetc(file);
    while (!feof(file)) {
        //printf("$$%c$$\n",ch);
        if(ch=='0'||ch=='1') {ram[i]= ram[i]*2+ch-'0';j++;}
        else if(ch=='\n'){i++;
            if(j!=16) {printf("Error file content! %d\n",i);
                        return 1;}
            j=0;}
        else {printf("Error file content! open\n");
                        return 1;}
        ch=fgetc(file);
    }
    i++;
            if(!(j==1||j==16)) {printf("Error file content! %d\n",i);
                        return 1;}
            j=0;
    number=i;
    fclose(file);//printf("##\n");
    free(str);
    return 0;
}
int write_person(void){
    int s=0,j=0,i=1;
    char ch=getchar();
    while (ch!='\n')
    {
        if(ch=='0'||ch=='1') {s=s*2+ch-'0';j++;}
        else if(ch==' '){
            ram[i]=s;
            {if(j!=16) {printf("Error input content\n"); 
                        return 1;}
            else {j=0;i++;s=0;number++;}}
                        }
        else {printf("Error input content!\n");
                        return 0;}
        ch=getchar();
    }
    ram[i]=s;
    if(j!=16) {printf("error input content!\n"); 
                        return 1;}
    else {j=0;i++;s=0;number++;}
    return 0;
}
int setting_in(void){
    FILE *fp;
    fp=fopen("setting.txt","r");
    if(fp==NULL) {printf("Error:open failed!\n");return 1;}
    char ch,ch2;
    int op;
    int count=0;
    while((!feof(fp))&&count<4){
        ch=fgetc(fp);
        op=ch-'0';//printf("%d %d ",op,count);
        if((op!=0&&op!=1)){printf("Error content of setting file!\n"); return 1;}
        switch (++count)
        {
        case 1:choice_mode=op;
            break;
        case 2:choice_gdb=op;
            break;
        case 3:choice_halt=op;
            break;
        case 4:choice_write=op;
            break;
        }
    }
    fclose(fp);
    return 0;
}

int setting_out(void){
    FILE *fp;
    fp=fopen("setting.txt","w");
    if(fp==NULL) {printf("Error:the setting change failed.\n");return 1;}
    fprintf(fp,"%d",choice_mode);
    fprintf(fp,"%d",choice_gdb);
    fprintf(fp,"%d",choice_halt);
    fprintf(fp,"%d",choice_write);
    fclose(fp);
    return 0;
}
int setting(void){
    int target=1;
    int t,a=0;
    a+=setting_in();
    if(a) return a;
    while (target)
    {
    printf("********************************************\n");
    printf("*the setting menu: (press 0 or 1 to switch)*\n");
    printf("*I.  debug mode:       %s                 *\n",(choice_mode)?"ON ":"OFF");
    printf("*II. GDB:              %s                 *\n",(choice_gdb)?"ON ":"OFF");
    printf("*III.HALT step by step:%s                 *\n",(choice_halt)?"ON ":"OFF");
    printf("*IV.the input way:     %s                *\n",(choice_write)?"FILE":"HAND");
    printf("*0: back to the former menu                *\n");
    printf("********************************************\n");
    printf("please select your choice:");
    scanf("%d",&t); getchar();
    if (t==0) target=0;
    else if(t==1){
        int t1=1;
        while (t1)
        {
        printf("the new default mode is:\n");
        scanf("%d",&choice_mode); getchar();
        if((choice_mode!=0)&&(choice_mode!=1)) printf("Error choice!\n");
        else t1=0;
        }
    }
    else if(t==2){
        int t1=1;
        while (t1)
        {
        printf("the new GDB condition is:\n");
        scanf("%d",&choice_gdb); getchar();
        if((choice_gdb!=0)&&(choice_gdb!=1)) printf("Error choice!\n");
        else t1=0;
        }
    }
    else if(t==3){
        int t1=1;
        while(t1)
        {
        printf("the new halt step by step condition is:\n");
        scanf("%d",&choice_halt); getchar();
        if((choice_halt!=0)&&(choice_halt!=1)) printf("Error choice!\n");
        else t1=0;
        }
    }
    else if(t==4){
        int t1=1;
        while (t1)
        {
        printf("the new default mode is:\n");
        scanf("%d",&choice_write); getchar();
        if((choice_write!=0)&&(choice_write!=1)) printf("Error choice!\n");
        else t1=0;
        }
    }
    else printf("Error choice!\n");
    if(choice_gdb==1&&choice_halt==1) printf("Warning: the gdb and halt have been both situmulated!The GDB won't work!\n");
    }
    a+=setting_out();
    return a;    
}