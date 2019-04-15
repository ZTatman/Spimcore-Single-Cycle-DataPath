#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
	// Instructions R, M, S, C, H, X.

	// TO-DO: ALU Switch statement

	// ALUControl Switch statement
	switch(ALUControl) {

		// Print Register Contents
		case 'R':

		// Show Memory Contents
		case 'M':

		// Step Forward 1 Instruction
		case 'S':

		// Continue All Instructions Until Halt
		case 'C':

		// Check If Program Is Halted
		case 'H':

		// Quit
		case 'X':

		// Instructions do not match, Halt Occurs
		default: 
			return 1;
	}
}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
	// Word-aligned means that PC is a multiple of 4.
	// Also check if PC goes beyond address 0xFFF, (65535)_10.
	if (PC % 4 == 0 && PC < 65535 )
	{
		instruction = Mem[PC >> 2];
		return 0;
	}

	// Else PC != word-aligned, Halt Occurs.
	return 1;
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
	// op = instruction[31-26];
	// r1 = instruction[25-21];
	// r2 = instruction[20-16];
	// r3 = instruction[15-11]; 
	// funct = instruction[5-0];
	// offset = instruction[15-0];
	// jsec = instruction[25-0];

	*op = (instruction & 0xFC000000) >> 26;
	*r1 = (instruction & 0x3E00000) >> 21;
	*r2 = (instruction & 0x1F0000) >> 16;
	*r3 = (instruction & 0xF800) >> 11;
	*funct = (instruction & 0x3F);
	*offset = (instruction & 0xFFFF);
	*jsec = (instruction & 0x3FFFFFF);
}


/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

// Reference to stuct_controls control signals
// =========================================== 
	/*
	RegDst;
	Jump;
	Branch;
	MemRead;
	MemtoReg;
	ALUOp;
	MemWrite;
	ALUSrc;
	RegWrite;
	*/


	// R-type Inst.
	if (op == 0) // ( add, sub, or, and ) instructions
	{
		
		struct_controls->RegDst = 1;
		struct_controls->ALUOp = 7; // 111 = r-type instruction operation
		struct_controls->RegWrite = 1;
		struct_controls->ALUSrc = 0;
		struct_controls->MemWrite = 0;
		struct_controls->MemRead = 0;
		struct_controls->MemtoReg = 0;
		struct_controls->Jump = 0;
		struct_controls->Branch = 0;

	}
	// Addi
	else if (op == 16)
	{
		struct_controls->RegDst = 0;
		struct_controls->ALUOp = 0; // 000 = add
		struct_controls->RegWrite = 1;
		struct_controls->ALUSrc = 1;
		struct_controls->MemWrite = 0;
		struct_controls->MemRead = 0;
		struct_controls->MemtoReg = 0;
		struct_controls->Jump = 0;
		struct_controls->Branch = 0;
	}
	// Load Word
	else if (op == 35)
	{
		struct_controls->RegDst = 0;
		struct_controls->ALUOp = 0; // 000 = add
		struct_controls->RegWrite = 1;
		struct_controls->ALUSrc = 1;
		struct_controls->MemWrite = 0;
		struct_controls->MemRead = 1;
		struct_controls->MemtoReg = 1;
		struct_controls->Jump = 0;
		struct_controls->Branch = 0;
	}
	// Load Upper immediate 
	else if ( op == 15)
	{
		struct_controls->RegDst = 2;
		struct_controls->ALUOp = 6; // 110 = shift left extended_value by 16 bits
		struct_controls->RegWrite = 0;
		struct_controls->ALUSrc = 1;
		struct_controls->MemWrite = 1;
		struct_controls->MemRead = 0;
		struct_controls->MemtoReg = 2;
		struct_controls->Jump = 0;
		struct_controls->Branch = 0;
	}
	// Store Word
	else if (op == 43)
	{
		struct_controls->RegDst = 2;
		struct_controls->ALUOp = 0; // 000 = add
		struct_controls->RegWrite = 0;
		struct_controls->ALUSrc = 1;
		struct_controls->MemWrite = 1;
		struct_controls->MemRead = 0;
		struct_controls->MemtoReg = 2;
		struct_controls->Jump = 0;
		struct_controls->Branch = 0;
	}
	// Branch On Equal
	else if (op == 4)
	{
		struct_controls->RegDst = 2;
		struct_controls->ALUOp = 1; // 001 = subtract
		struct_controls->RegWrite = 0;
		struct_controls->ALUSrc = 0;
		struct_controls->MemWrite = 0;
		struct_controls->MemRead = 0;
		struct_controls->MemtoReg = 2;
		struct_controls->Jump = 0;
		struct_controls->Branch = 1;
	}
	// slt
	else if (op == )
	{
		struct_controls->RegDst = 0;
		struct_controls->ALUOp = 2; // 010 = slt & slt immediate
		struct_controls->RegWrite = 1;
		struct_controls->ALUSrc = 1;
		struct_controls->MemWrite = 0;
		struct_controls->MemRead = 0;
		struct_controls->MemtoReg = 0;
		struct_controls->Jump = 0;
		struct_controls->Branch = 0;
	}
	// slt immediate
	else if (op == 10)
	{
		struct_controls->RegDst = 0;
		struct_controls->ALUOp = 2; // 010 = slt & slt immediate
		struct_controls->RegWrite = 1;
		struct_controls->ALUSrc = 1;
		struct_controls->MemWrite = 0;
		struct_controls->MemRead = 0;
		struct_controls->MemtoReg = 0;
		struct_controls->Jump = 0;
		struct_controls->Branch = 0;
	}
	// stl immediate unsigned
	else if (op == 11)
	{
		struct_controls->RegDst = 0;
		struct_controls->ALUOp = 3; // 011 = slt immediate unsigned
		struct_controls->RegWrite = 1;
		struct_controls->ALUSrc = 1;
		struct_controls->MemWrite = 0;
		struct_controls->MemRead = 0;
		struct_controls->MemtoReg = 0;
		struct_controls->Jump = 0;
		struct_controls->Branch = 0;
	}
	// Jump
	else if (op == 2)
	{
		struct_controls->RegDst = 2;
		struct_controls->ALUOp = 0; // 0 = "Do not care"
		struct_controls->RegWrite = 0;
		struct_controls->ALUSrc = 2;
		struct_controls->MemWrite = 0;
		struct_controls->MemRead = 0;
		struct_controls->MemtoReg = 0;
		struct_controls->Jump = 1;
		struct_controls->Branch = 0;
	}
}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{

}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}

