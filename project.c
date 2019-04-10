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
	// jsec = instruction[35-0];

	*op = (instruction & 0xFC000000) >> 26;
	*r1 = (instruction & 0x3E00000) >> 21;
	*r2 = (instruction & 0x1F0000) >> 16;
	*r3 = (instruction & 0xF800) >> 11
	*funct = (instruction & 0x3F) << 26;
	*offset = (instruction & 0x7FFF) << 16;
	// jsec = 
}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

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

