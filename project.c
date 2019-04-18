#include "spimcore.h"


void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
	int Control = (int) ALUControl;
	// addition
	if (Control == 0)
	{
		*ALUresult = A + B;
	}
	// subtraction
	else if (Control == 1)
	{
		*ALUresult = A - B;
	}

	// set less than 
	else if (Control == 2)
	{
		if ((int)A < (int)B)
			*ALUresult = 1;
		else
			*ALUresult = 0;
	}

	// set less than unsigned
	else if (Control == 3)
	{
		if (A < B)
			*ALUresult = 1;
		else
			*ALUresult = 0;
	}

	// bitwise and
	else if (Control == 4)
	{
		*ALUresult = A & B;
	}

	// bitwise or
	else if (Control == 5)
	{
		*ALUresult = A | B;
	}

	// shift left by 16 bits
	else if (Control == 6)
	{
		*ALUresult = B << 16;
	}

	// bitwise not
	else if (Control == 7)
	{
		*ALUresult = ~A;
	}

	// Set to 1 if result is 0.
	*Zero = (*ALUresult == 0);
}


int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
	// Word-aligned means that PC is a multiple of 4.
	if (PC % 4 == 0)
	{
		*instruction = Mem[PC >> 2];
		return 0;
	}

	// Else PC != word-aligned, Halt Occurs.
	return 1;
}


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
	*funct = instruction & 0x3F;
	*offset = instruction & 0xFFFF;
	*jsec = instruction & 0x3FFFFFF;
}


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

		controls->RegDst = 1;
		controls->ALUOp = 7; // 111 = r-type instruction operation
		controls->RegWrite = 1;
		controls->ALUSrc = 0;
		controls->MemWrite = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->Jump = 0;
		controls->Branch = 0;
		return 0;

	}
	// Addi
	else if (op == 8)
	{
		controls->RegDst = 0;
		controls->ALUOp = 0; // 000 = add
		controls->RegWrite = 1;
		controls->ALUSrc = 1;
		controls->MemWrite = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->Jump = 0;
		controls->Branch = 0;
		return 0;
	}
	// Load Word
	else if (op == 35)
	{
		controls->RegDst = 0;
		controls->ALUOp = 0; // 000 = add
		controls->RegWrite = 1;
		controls->ALUSrc = 1;
		controls->MemWrite = 0;
		controls->MemRead = 1;
		controls->MemtoReg = 1;
		controls->Jump = 0;
		controls->Branch = 0;
		return 0;
	}
	// Load Upper immediate
	else if (op == 15)
	{
		controls->RegDst = 0;
		controls->ALUOp = 6; // 110 = shift left extended_value by 16 bits
		controls->RegWrite = 1;
		controls->ALUSrc = 1;
		controls->MemWrite = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->Jump = 0;
		controls->Branch = 0;
		return 0;
	}
	// Store Word
	else if (op == 43)
	{
		controls->RegDst = 0;
		controls->ALUOp = 0; // 000 = add
		controls->RegWrite = 0;
		controls->ALUSrc = 1;
		controls->MemWrite = 1;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->Jump = 0;
		controls->Branch = 0;
		return 0;
	}
	// Branch On Equal
	else if (op == 4)
	{
		controls->RegDst = 2;
		controls->ALUOp = 1; // 001 = subtract
		controls->RegWrite = 0;
		controls->ALUSrc = 0;
		controls->MemWrite = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 2;
		controls->Jump = 0;
		controls->Branch = 1;
		return 0;
	}
	// slt immediate
	else if (op == 10)
	{
		controls->RegDst = 0;
		controls->ALUOp = 2; // 010 = slt & slt immediate
		controls->RegWrite = 1;
		controls->ALUSrc = 1;
		controls->MemWrite = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->Jump = 0;
		controls->Branch = 0;
		return 0;
	}
	// stl immediate unsigned
	else if (op == 11)
	{
		controls->RegDst = 0;
		controls->ALUOp = 3; // 011 = slt immediate unsigned
		controls->RegWrite = 1;
		controls->ALUSrc = 1;
		controls->MemWrite = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->Jump = 0;
		controls->Branch = 0;
		return 0;
	}
	// Jump
	else if (op == 2)
	{
		controls->RegDst = 2;
		controls->ALUOp = 0; // 0 = "Do not care"
		controls->RegWrite = 0;
		controls->ALUSrc = 2;
		controls->MemWrite = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 2;
		controls->Jump = 1;
		controls->Branch = 2;
		return 0;
	}
	
	return 1;
}


void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
	*data1 = Reg[r1];
	*data2 = Reg[r2];
}



void sign_extend(unsigned offset,unsigned *extended_value)
{
	if (offset >> 15)
	{
		int n = -1 << 16;
		offset |= n;
	}
	*extended_value = offset;
}


int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

	char control = ALUOp;

	//Check which data we are opperating on by ALU src
	if(ALUSrc)
	{
		data2 = extended_value;
	}
	
	if (control == 0 || control == 1 || control == 2 || control == 3 || control == 4 ||
				control == 5 || control == 6)
	{
		ALU(data1,data2,control,ALUresult,Zero);
		return 0;
	}
	
	if (control == 7)
	{
	// R-types Instructions
		switch(funct)
		{
			case 6:
				control = 6;
				break;
			case 32:
				control = 0;
				break;
			case 34:
				control = 1;
				break;
			case 36:
				control = 4;
				break;
			case 37:
				control = 5;
				break;
			// case 39:
			// 	control = 7;
				break;
			case 42:
				control = 2;
				break;
			case 43:
				control = 3;
				break;

			// halt
			default:
				return 1;
		}
		ALU(data1,data2,control,ALUresult,Zero);
		return 0;
	}
	return 1;
}

int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

	// reading from memory
	if (MemRead)
		if ((ALUresult % 4) == 0)
			*memdata = Mem[ALUresult >> 2];
		// halt
		else
			return 1;

	// writting to memory
	if (MemWrite)
		if ((ALUresult % 4) == 0)
			Mem[ALUresult >> 2] = data2;
		// halt
		else
			return 1;
	return 0;
}


void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
	if (RegWrite)
		if (!MemtoReg)
			if (RegDst)
				Reg[r3] = ALUresult;
			else
				Reg[r2] = ALUresult;
	
		else if (MemtoReg)
			Reg[r2] = memdata;	
}


void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{
	*PC += 4;
	if (Jump == 1)
		*PC = (jsec << 2) | (*PC & 0xF0000000);
	if (Zero == 1 && Branch == 1)
		*PC = *PC + (extended_value << 2);
}
