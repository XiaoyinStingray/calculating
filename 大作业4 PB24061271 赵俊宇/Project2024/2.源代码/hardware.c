//author:zhao jun yu PB24061271
//Email:zhaojunyu0515@mail.ustc.edu.cn
//Project_2024.11-12:self-defined machine code operator

//硬件部分
//寄存器 Register:8+3 r0-r7 r_pc:程序计数器(8) r_cd:条件码寄存器(9) 
/* 
   r_pc
   r_trap   
   r_cd  
   r_7  7   //预留给JSR
*/
unsigned short regis[8]={0};
unsigned short regis_pc=0;
unsigned short regis_cd=0;
unsigned short regis_trap=0;
//断电就消失(重新运行就消失),好像RAM 
unsigned short ram[65536]={0};
unsigned short GDB[65536]={0};
//Random Access Memory:65536-1
int number=0;

int state=1;
//计算机状态，判断是否运行
int choice_halt=0;
int choice_gdb=0;
int choice_mode=0;
int choice_write=0;
int choice=0;
