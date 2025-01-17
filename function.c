//author:zhao jun yu PB24061271
//Email:zhaojunyu0515@mail.ustc.edu.cn
//Project_2024.11-12:self-defined machine code operator

#include"function.h"
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
int selection(unsigned short operand){
    int oper=IN_IV(operand);
    //printf("$$%d$$\n",oper);
        if(oper==0) {op_br(operand);}
        else if(oper==1)op_add(operand);
        else if(oper==2)op_ld(operand);
        else if(oper==3)op_st(operand);
        else if(oper==4)op_jsr_jsrr(operand);
        else if(oper==5)op_and(operand);
        else if(oper==6)op_ldr(operand);
        else if(oper==7)op_str(operand);
        else if(oper==8)op_rti(operand);
        else if(oper==9)op_not(operand);
        else if(oper==10)op_ldi(operand);
        else if(oper==11)op_sti(operand);
        else if(oper==12)op_ret_jmp(operand);
        else if(oper==13)op_res(operand);
        else if(oper==14)op_lea(operand);
        else if(oper==15)op_trap(operand);
        else{printf("Error insturction!");
            return 1;}
    return 0;
}
void selection_trap(unsigned short trap8){
    unsigned short trap=trap8&0b111;
    int dr=(trap8>>5)&0b111; //printf("$$%d\n",dr);
    if(trap==1) input(regis[dr]);
    else if(trap==2) output();
    else if(trap==3) putin();
    else if(trap==4) end();
    else if(trap==5) write(dr);
    else if(trap==0) {devide(dr);
                        //printf("%d\n",dr);
                        }
}
void output(void){
    printf("%c",(short)regis_trap+48);
}
void input(unsigned short a){
    regis_trap=a;
}
void putin(void){
    char ch,t;
    printf("\n");
    while ((t=getchar())!='\n'&&t!=EOF);
    ch=getchar();
    regis_trap=ch-'0';
}
void end(void){
    state=0;
    //printf("$$%d$$",state);
}
void write(unsigned short a){
    regis[a]=regis_trap;
}
void devide(unsigned short a){
    if(regis_trap==0) {printf("\nThe num of devide can't be zero!\n");state=0;}
    else {regis[a]=regis[a]/regis_trap; new_condition(regis[a]);}
}
//更新条件码
void new_condition(unsigned short oper){
    short oper_= (short)oper;
    if(oper_>0) regis_cd=1;
    else if(oper_<0) regis_cd=4;
    else regis_cd=2;
}
//debug
void debug(void){
    printf("\n");
    printf("regis_cd:%d\n",regis_cd);
    printf("regis_trap:%d\n",regis_trap);
    printf("regis_pc:%d\n",regis_pc);
    for(int i=0;i<8;i++) printf("regis[%d] :%d\n",i,(short)regis[i]);    
    printf("\n"); 
}
void outputbin(unsigned short oper,int num){
    int a[16]={0},j=0;
    if (choice==1){
    while (oper!=0)
    {   a[j++]=oper%2;
        oper/=2;
    }
    for(int i=num-1;i>=0;i--) printf("%d",a[i]);
    }

    
}
//预处理数据:防止溢出,方便运算,做出符号位,二进制补码
short pre_preparation(unsigned short oper,int num){
    short oper_=(short)(((1U << num)-1)&oper);
    if ((1&(oper_ >>(num-1))) ==1){
        oper_ =oper_ | (0b1111111111111111 << num);
    }
    else ;
    return (oper_);
}

int IN_II(unsigned short operand){
    return (0b111&operand);
}
int IN_IV(unsigned short operand){
    int a=operand>>12;
    a=0b1111&a;
    return a;
}
unsigned short U_IV(unsigned short operand){
    unsigned short a=(pre_preparation(operand,5));
    return a;
}
int V(unsigned short operand){
    return (0b1&(operand>>5));
}
unsigned short U_V(unsigned short operand){
    unsigned short a=(pre_preparation(operand,6));
    return a;
}
int VI_VIII(unsigned short operand){
    return (0b111&(operand>>6));
}
int IX_XI(unsigned short operand){
    return (0b111&(operand>>9));
}
int nzp(unsigned short operand){
    int a= (regis_cd&(0b111&(operand>>9)));
    //printf("%d",a);
    return a;
}
unsigned short U_VII(unsigned short operand){
    unsigned short a=operand&0b11111111;
    return a;
}
unsigned short U_IX(unsigned short operand){
    unsigned short a=(unsigned short)pre_preparation(operand,9);
    //printf("%d\n",a);
    return a;
}
int XI(unsigned short operand){
    return (0b1&(operand>>11));
}
unsigned short U_XI(unsigned short operand){
    unsigned short a=pre_preparation(operand,11);
    return a;
}

//命名规则全部参考LC-3
//0000 
void op_br(unsigned short operand){
    int target=nzp(operand);  //printf("$$%d$$",target);  
        if(choice) {printf("BR ");}
    unsigned short pcoffset9 =U_IX(operand);    
        if(choice) { printf("offest:%d regis_pc:%d",(short)pcoffset9,regis_pc);}
    if(target) regis_pc=regis_pc+pcoffset9;    
        if(choice) {printf(" regis_pc:%d\n",(short)regis_pc);}
}
//0001
void op_add(unsigned short operand){//outputbin(operand,16);
    int target=V(operand);      //printf("^%d\n",target);
    int dr=IX_XI(operand);      
    int sr1=VI_VIII(operand);
        if(choice) {printf("ADD resig[%d] regis[%d] ",dr,sr1);}
    if(target==0){
       int sr2=IN_II(operand);  
       regis[dr]=regis[sr1]+regis[sr2]; 
            if(choice) {printf("regis[%d] %d\n",sr2,(short)regis[dr]);}
    }
    else {
        unsigned short imm5=U_IV(operand);
        regis[dr]=regis[sr1]+imm5;      
            if(choice) {printf("imm5:%d %d\n",(short)imm5,(short)regis[dr]);}
    }
    new_condition(regis[dr]);
}
//0010
void op_ld(unsigned short operand){
    unsigned short pcoffset9=U_IX(operand);
    int dr=IX_XI(operand);      
        if(choice) {printf("LD dr ");}
    unsigned short det=regis[8]+pcoffset9;
    regis[dr]=ram[det];          
        if(choice) {printf("offset:%d regis[%d]:%d\n",(short)pcoffset9,dr,(short)regis[dr]);}
    new_condition(regis[dr]); 
}
//0011
void op_st(unsigned short operand){
    unsigned short pcoffset9=U_IX(operand);
    int sr=IX_XI(operand);        
        if(choice) {printf("ST sr ");}
    unsigned short det=regis_pc+pcoffset9;
    ram[det]=regis[sr];
        if(choice) {printf("offset:%d regis[%d]:%d\n",(short)pcoffset9,sr,(short)regis[sr]);}
}
//0100
void op_jsr_jsrr(unsigned short operand){
    int target=XI(operand);
    if(target ==0)  {
        int BaseR=VI_VIII(operand);
        regis_pc=BaseR;
            if(choice) printf("JSRR BaseR regis_pc:%d\n",(short)regis_pc);
    }
    else {
        unsigned short pcoffset11=U_XI(operand);
        regis_pc+=pcoffset11;
            if(choice) printf("JSR BaseR offset:%d regis_pc:%d\n",(short)pcoffset11,(short)regis_pc);
    }
}
//0101
void op_and(unsigned short operand){
    int target=V(operand);
    int dr=IX_XI(operand);
    int sr1=VI_VIII(operand);
        if(choice) {printf("AND regis[%d]:%d ",sr1,(short)regis[sr1]);}
    if(target==0){
       int sr2=IN_II(operand);
       regis[dr]=regis[sr1]&regis[sr2];
            if(choice) {printf("regis[%d]:%d %d\n",sr2,(short)regis[sr2],(short)regis[dr]);}
    }
    else {
        unsigned short imm5=U_IV(operand);
        regis[dr]=regis[sr1]&imm5;
            if(choice) {printf("imm5:%d %d\n",(short)imm5,(short)regis[dr]);}
    }
    new_condition(regis[dr]);
}
//0110
void op_ldr(unsigned short operand){
    unsigned short offest6=U_V(operand);
    int BaseR=VI_VIII(operand);
    int dr=IX_XI(operand);
        if(choice) {printf("LDR regis[%d] ",dr);}
    unsigned short det=regis[BaseR]+offest6;
    regis[dr]=ram[det];         
        if(choice) {printf("resig[%d]:%d\n",dr,(short)regis[dr]);}
    new_condition(regis[dr]);
}
//0111
void op_str(unsigned short operand){
    unsigned short offest6=U_V(operand);
    int BaseR=VI_VIII(operand);
    int sr=IX_XI(operand);
        if(choice) {printf("STR regis[%d] ",sr);}
    unsigned short det=regis[BaseR]+offest6;
        if(choice) {printf("regis[%d]:%d ram[%d]:%d ",BaseR,(short)regis[BaseR],det,(short)ram[det]);}
    ram[det]=regis[sr];
        if(choice) {printf("offset:%d %d\n",(short)offest6,(short)ram[det]);}
}
//1000
void op_rti(unsigned short operand){
    int target=V(operand);
    int dr=IX_XI(operand);
    int sr1=VI_VIII(operand);
        if(choice) {printf("RTI regis[%d]:%d ",sr1,(short)regis[sr1]);}
    if(target==0){
       int sr2=IN_II(operand);
       regis[dr]=regis[sr1]*regis[sr2];
            if(choice) {printf(" * regis[%d]:%d %d\n",sr2,(short)regis[sr2],(short)regis[dr]);}
    }
    else {
       int sr2=IN_II(operand);
       if(regis[sr2]==0) {printf("The number of mol can't be zero!\n");state=0;}
       else{
       regis[dr]=regis[sr1]%regis[sr2];
            if(choice) {printf(" %% regis[%d]:%d %d\n",sr2,(short)regis[sr2],(short)regis[dr]);}
       }
    }
    new_condition(regis[dr]);
}
//1001
void op_not(unsigned short operand){
    int dr=IX_XI(operand);
    int sr=VI_VIII(operand);
        if(choice) {printf("NOT regis[%d] regis[%d] ",dr,sr);}
    regis[dr]= ~regis[sr];
        if(choice) {printf("%d\n",(short)regis[dr]);}
    new_condition(regis[dr]);
}
//1010
void op_ldi(unsigned short operand){
    int dr=IX_XI(operand);
    unsigned short pcoffset9=U_IX(operand);
        if(choice) {printf("LDI regis[%d] ",dr);}
    unsigned short det1=regis_pc+pcoffset9;
    unsigned short det2=ram[det1];
    regis[dr]=ram[det2];
        if(choice) {printf("offset:%d %d\n",(short)pcoffset9,(short)regis[dr]);}
    new_condition(regis[dr]);
}
//1011
void op_sti(unsigned short operand){
    int sr=IX_XI(operand);
    unsigned short pcoffset9=U_IX(operand);
        if(choice) {printf("STI regis[%d] offset:%d ",sr,(short)pcoffset9);}
    unsigned short det1=regis_pc+pcoffset9;
        if(choice) {printf("ram[%d]:%d ",det1,(short)ram[det1]);}
    unsigned short det2=ram[det1];
    unsigned short a=regis[sr];   //printf("$$ram[%d]:%d",sr,ram[sr]);
    ram[det2]=a;
        if(choice) {printf("ram[%d]:%d\n",det2,(short)ram[det2]);}


}
//1100
void op_ret_jmp(unsigned short operand){
    int BaseR=VI_VIII(operand);
    regis_pc=regis[BaseR];
        if(choice) {printf("RET/JMP regis[%d]:%d regis_pc:%d\n",BaseR,(short)regis[BaseR],(short)regis_pc);}
}
//1101
void op_res(unsigned short operand){
        int dr=IX_XI(operand);
        regis[dr]=(unsigned short)(-1*(int)regis[dr]);
        if(choice) {printf("RES regis[%d]: ",dr);printf("%d\n",(short)regis[dr]);}
        new_condition(regis[dr]);
}
//1110
void op_lea(unsigned short operand){
    int dr=IX_XI(operand);
    unsigned short pcoffset9=U_IX(operand);
    unsigned short det=regis_pc+pcoffset9;
        if(choice) {printf("LEA regis[%d] regis_pc:%d ",dr,(short)regis_pc);}
    regis[dr]=det;
        if(choice) {printf("%d",(short)regis[dr]);}
    new_condition(regis[dr]);
}
//1111
void op_trap(unsigned short operand){
    unsigned short trapvect8=U_VII(operand); //outputbin(trapvect8,8);printf("\n");
        if(choice) printf("TRAP trapvect8:%d\n",trapvect8);
    selection_trap(trapvect8);
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