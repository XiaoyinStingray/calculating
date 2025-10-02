//author:zhao jun yu PB24061271
//Email:zhaojunyu0515@mail.ustc.edu.cn
//Project_2024.11-12:self-defined machine code operator

#include "function.h"
int defaultmode(void){
    int a=0;
    a+=setting_in();
    choice=choice_mode;
    if(choice_write) a+=write_flie();
    else a+=write_person();//printf("\n####\n");
    return a;
}
void waiting(void){
    printf("\n%d codes have been done.Here is the registers:\n",regis_pc);
    debug();
    printf("Press any bottom to continue the program!\n");
    char t;
    while ((t=getchar())!='\n'&&t!=EOF);
    getchar();
}
int gdb_in(void){
    FILE *fp;
    fp=fopen("gdbfile.txt","r");
    if(fp==NULL) {printf("Error:the GDB file can't be opened!\n");return 1;}
    unsigned short ch;
    while (!feof(fp))
    {   
        fscanf(fp,"%hu\n",&ch);
        GDB[ch]=1;//printf("##%hu %hu\n",GDB[ch],ch);
    }
    fclose(fp);
    return 0;
}
int gdb_selection(void){
    int i=1,t,a=0;
    if(a) return 1;
    while (i)
    {  
    printf("*****************************************\n");
    printf("*please select choice for the gdb file: *\n");
    printf("*I.create a new file(press '1')         *\n");
    printf("*II.add more point(press '2')           *\n");
    printf("*III.delete some point(press '3')       *\n");
    printf("*IV.show me all the point(press '4')    *\n");
    printf("*0.back to the former menu(press '0')   *\n");
    printf("*****************************************\n");
    scanf("%d",&t);
    if(t==0) i=0;
    else if(t==1) a+=gdb_I();
    else if(t==2) a+gdb_II();
    else if(t==3) a+=gdb_III();
    else if(t==4) a+=gdb_IV();
    else printf("Error: unexisted selection.\n");
    if(a) return 1;
    }
    return 0;
}
int gdb_I(void){
    FILE *fp;
    fp=fopen("gdbfile.txt","wt");
    if(fp==NULL) {printf("Error:the GDB file can't be opened!\n");return 1;}
    unsigned short count=1,t;
    printf("press '0' to end\n");
    printf("Input the %d%s point:",count,help(count));
    fflush(stdin);fflush(stdout);scanf("%hu",&t);fflush(stdin);fflush(stdout);
    while (t)
    {
        printf("After the %d%s instruction is done ,the program will be paused.\n",t,t%10==1?"st":(t%10==2?"nd":(t%10==3?"rd":"th")));
        fprintf(fp,"%hu\n",t);//printf("!!!\n");
        count++;
        printf("Input the %d%s point:",count,help(count));
        scanf("%hu",&t);fflush(stdin);fflush(stdout);
    }
    fclose(fp);
    return 0;
}
int gdb_II(void){
    FILE *fp;
    fp=fopen("gdbfile.txt","rt");
    if(fp==NULL) {printf("Error:the GDB file can't be opened!\n");return 1;}
    unsigned short count=1,t;
    while ((!feof(fp)))
    {
        fscanf(fp,"%hu\n",&t);
        count++;
    }
    fclose(fp);
    fp=fopen("gdbfile.txt","at");
    t=1;
    printf("press '0' to end\n");
    printf("Input the %d%s point:",count,help(count));
    fflush(stdin);fflush(stdout);scanf("%hu",&t);fflush(stdin);fflush(stdout);
    while (t)
    {
        printf("After the %d%s instruction is done ,the program will be paused.\n",t,t%10==1?"st":(t%10==2?"nd":(t%10==3?"rd":"th")));
        fprintf(fp,"%hu\n",t);//printf("!!!\n");
        count++;
        printf("Input the %d%s point:",count,help(count));
        scanf("%hu",&t);fflush(stdin);fflush(stdout);
    }
    fclose(fp);
    return 0;
}
int gdb_III(void){
    FILE *fp;
    fp=fopen("gdbfile.txt","rt");
    if(fp==NULL) {printf("Error:the GDB file can't be opened!\n");return 1;}
    unsigned short count=0,t,j;
    unsigned short *temp=(unsigned short *)malloc(sizeof(unsigned short));
    while ((!feof(fp)))
    {
        fscanf(fp,"%hu\n",&t);
        *(temp+(count))=t;
        count++;
        temp=(unsigned short *)realloc(temp,sizeof(unsigned short));
    }
    *(temp+count)='\0';
    fclose(fp);
    printf("Press '0' to end\n");
    printf("Please input the number of the code to cancel the point:\n");
    scanf("%hu",&t);
    while (t)
    {
        for(j=0;j<count;j++)
            if(*(temp+j)==t) {
                *(temp+j)=0;
                printf("The point of instruction %d has been canceled.\n",t);
                break;
            }
        if(j==count) printf("Error:the point doesn't exist!\n");
        printf("Please input the number of the code to cancel the point:\n");
        scanf("%hu",&t);
    }
    fp=fopen("gdbfile.txt","wt");
    if(fp==NULL) {printf("Error:the GDB file can't be opened!\n");return 1;}
    for(j=0;j<count;j++){
        if(*(temp+j)) {fprintf(fp,"%hu\n",*(temp+j));}
    }
    printf("The new gdbfile has been created.\n");
    fclose(fp);
    free(temp);
    return 0;
}
int gdb_IV(void){
    FILE *fp;
    fp=fopen("gdbfile.txt","rt");
    if(fp==NULL) {printf("Error:the GDB file can't be opened!\n");return 1;}
    unsigned short count=1,t;
    while ((!feof(fp)))
    {
        fscanf(fp,"%hu\n",&t);
        printf("The %d%s point is %d.\n",count,help(count),t);
        count++;
    }
    printf("All the point have been listed!Total: %d.\n",count-1);
    fclose(fp);
    return 0;
}
const char* help(unsigned short count){
    if(count%10==1&&count&100!=11) return "st";
    else if (count%10==2&&count&100!=12) return "nd";
    else if (count%10==3&&count&100!=13) return "rd";
    else return "th";
}