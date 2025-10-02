//author:zhao jun yu PB24061271
//Email:zhaojunyu0515@mail.ustc.edu.cn
//Project_2024.11-12:self-defined machine code operator
#ifndef _FUNCTION_H_
#define _FUNCTION_H_




#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//硬件部分
//寄存器 Register:8+3 r0-r7 r_pc:程序计数器(8) r_cd:条件码寄存器(9) 寄存器总数(10)

// r_7:7(预留给JSR) r_pc:8 r_cd:9 
// 条件码: positive:0b001 zero:0b010 negative:0b100

//指令 Operation Code: 命名规则全部参考LC-3

/*  BR,   //0000
    ADD,  //0001
    LD,   //0010
    ST,   //0011
    JSR,  //0100
    AND,  //0101
    LDR,  //0110
    STR,  //0111
    RTI,  //1000 啥意思啊不懂
    NOT,  //1001
    LDI,  //1010
    STI,  //1011
    JMP,  //1100
    RES,  //1101 准备做原创取负指令
    LEA,  //1110
    TRAP  //1111 哈哈做不出来了
*/
extern int number;
extern unsigned short ram[65536];
extern unsigned short GDB[65536];
extern unsigned short regis[8];
extern unsigned short regis_pc;
extern unsigned short regis_cd;
extern unsigned short regis_trap;
extern int state;
extern int choice;
extern int choice_halt;
extern int choice_gdb;
extern int choice_mode;
extern int choice_write;
//write
int write_flie(void);
int write_person(void);
//selection
int selection(unsigned short operand);
void selection_trap(unsigned short operand);
//trap
void output(void);
void input(unsigned short a);
void putin(void);
void end(void);
void write(unsigned short a);
void devide(unsigned short a);
//adjust
void new_condition(unsigned short oper);
void debug(void);
void outputbin(unsigned short oper,int num);
short pre_preparation(unsigned short oper,int num);
//calculating
int IN_II(unsigned short operand);
int IN_IV(unsigned short operand);
unsigned short U_IV(unsigned short operand);
int V(unsigned short operand);
unsigned short U_V(unsigned short operand);
int VI_VIII(unsigned short operand);
int IX_XI(unsigned short operand);
int nzp(unsigned short operand);
unsigned short U_VII(unsigned short operand);
unsigned short U_IX(unsigned short operand);
int XI(unsigned short operand);
unsigned short U_XI(unsigned short operand);
//operation
void op_br(unsigned short operand);
void op_add(unsigned short operand);
void op_ld(unsigned short operand);
void op_st(unsigned short operand);
void op_jsr_jsrr(unsigned short operand);
void op_and(unsigned short operand);
void op_ldr(unsigned short operand);
void op_str(unsigned short operand);
void op_rti(unsigned short operand);
void op_not(unsigned short operand);
void op_ldi(unsigned short operand);
void op_sti(unsigned short operand);
void op_ret_jmp(unsigned short operand);
void op_res(unsigned short operand);
void op_lea(unsigned short operand);
void op_trap(unsigned short operand);

int setting_in(void);
int setting_out(void);
int setting(void);
int defaultmode(void);
void waiting(void);
int gdb_selection(void);
int gdb_I(void);
int gdb_II(void);
int gdb_III(void);
int gdb_IV(void);
int gdb_in(void);
const char* help(unsigned short count);

#endif // _FUNCTION_H_