#include "spimcore.h"


/* ALU */
/* 10 Points */
//Alexander Cote
void ALU(unsigned A, unsigned B, char ALUControl, unsigned *ALUresult, char *Zero)
{

	switch (ALUControl)
	{

		case 0:
			*ALUresult = A + B;
			if (*ALUresult == 0)		
				*Zero = 1;
			else
				*Zero = 0;
			break;
		
		case 1:
			*ALUresult = A - B;
			if (*ALUresult == 0)
				*Zero = 1;
			else
				*Zero = 0;
			break;
		
		case 2:
			*ALUresult = A < B;
			if (*ALUresult == 0)
				*Zero = 1;
			else
				*Zero = 0;
			break;
		
		case 3:
			*ALUresult = A < B;
			if (*ALUresult == 0)
				*Zero = 1;
			else
				*Zero = 0;
			break;
		
		case 4:
			*ALUresult = A & B;
			if (*ALUresult == 0)
				*Zero = 1;
			else
				*Zero = 0;
			break;
		
		case 5:
			*ALUresult = A | B;
			if (*ALUresult == 0)
				*Zero = 1;
			else
				*Zero = 0;
			break;
		
		case 6:
			*ALUresult = B << 16;
			if (*ALUresult == 0)
				*Zero = 1;
			else
				*Zero = 0;
			break;
		
		case 7:
			*ALUresult = ~A;
			if (*ALUresult == 0)
				*Zero = 1;
			else
				*Zero = 0;
			break;
	}		
	return;
}


/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC, unsigned *Mem, unsigned *instruction)
{

}


/* instruction partition */
/* 10 Points */
void
instruction_partition(unsigned instruction, unsigned *op, unsigned *r1, unsigned *r2, unsigned *r3, unsigned *funct,
					  unsigned *offset, unsigned *jsec)
{

}



/* Instruction Decode */
/* 15 Points */
// Michael Ibeh
int instruction_decode(unsigned op, struct_controls *controls){
			/*typedef struct
			{
			char RegDst;  // 0 for I-Type that write to reg (addi, andi, ori, lw)
			char Jump;	  // only 1 for jump instructions, 0 else
			char Branch;  // 1 for beq, 0 else determines next PC
			char MemRead; // 1 for lw, 0 else gives processor perm to read from memory
			char MemtoReg;// 1 for lw, 0 for all R-type & I-type that write to register (0 - sends res from ALU to register, 1 - val from mem to register)
			char ALUOp;   // 1 beq, 2 R-Type, 0 else
			char MemWrite;// 1 for sw, 0 else gives processor perm to write to data mem
			char ALUSrc;  // 0 for R-type and beq, 1 for addi, andi, ori, lw, sw
			char RegWrite;// 1 for R-types, addi, andi, ori, lw, 0 else
			}struct_controls;*/

	// R-Type
	if(op == 0){
		controls->RegDst = 1;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->ALUOp = 2;
		controls->MemWrite = 0;
		controls->ALUSrc = 0;
		controls->RegWrite = 1;

		return 0;
	}
	
	// J-Type
	if(op == 2){
		controls->RegDst = 0;
		controls->Jump = 1;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->ALUOp = 0;
		controls->MemWrite = 0;
		controls->ALUSrc = 0;
		controls->RegWrite = 0;

		return 0;
	}

	//I-Type
	switch(op){

		// addi
		case 0b001000:
			controls->RegDst = 0;
			controls->Jump = 0;
			controls->Branch = 0;
			controls->MemRead = 0;
			controls->MemtoReg = 0;
			controls->ALUOp = 0;
			controls->MemWrite = 0;
			controls->ALUSrc = 1;
			controls->RegWrite = 1;
			break;

		// lw
		case 0b100011:
			controls->RegDst = 0;
			controls->Jump = 0;
			controls->Branch = 0;
			controls->MemRead = 1;
			controls->MemtoReg = 1;
			controls->ALUOp = 0;
			controls->MemWrite = 0;
			controls->ALUSrc = 1;
			controls->RegWrite = 1;
			break;

		// sw
		case 0b101011:
			controls->RegDst = 1;
			controls->Jump = 0;
			controls->Branch = 0;
			controls->MemRead = 0;
			controls->MemtoReg = 0;
			controls->ALUOp = 0;
			controls->MemWrite = 1;
			controls->ALUSrc = 1;
			controls->RegWrite = 0;
			break;

		// lui
		case 0b001111:
			controls->RegDst = 1;
			controls->Jump = 0;
			controls->Branch = 0;
			controls->MemRead = 0;
			controls->MemtoReg = 0;
			controls->ALUOp = 0;
			controls->MemWrite = 0;
			controls->ALUSrc = 0;
			controls->RegWrite = 0;
			break;

		// slti
		case 0b001010:
			controls->RegDst = 1;
			controls->Jump = 0;
			controls->Branch = 0;
			controls->MemRead = 0;
			controls->MemtoReg = 0;
			controls->ALUOp = 0;
			controls->MemWrite = 0;
			controls->ALUSrc = 0;
			controls->RegWrite = 0;
			break;

		// sltiu
		case 0b001011:
			controls->RegDst = 1;
			controls->Jump = 0;
			controls->Branch = 0;
			controls->MemRead = 0;
			controls->MemtoReg = 0;
			controls->ALUOp = 0;
			controls->MemWrite = 0;
			controls->ALUSrc = 1;
			controls->RegWrite = 1;
			break;
				
		// beq
		case 0b000100:
			controls->RegDst = 1;
			controls->Jump = 0;
			controls->Branch = 1;
			controls->MemRead = 0;
			controls->MemtoReg = 0;
			controls->ALUOp = 1;
			controls->MemWrite = 0;
			controls->ALUSrc = 0;
			controls->RegWrite = 0;
			break;
	}

	return 0;
}

/* Read Register */
/* 5 Points */
// Alexander Cote
void read_register(unsigned r1, unsigned r2, unsigned *Reg, unsigned *data1, unsigned *data2)
{
	*data1 = Reg[r1];
	*data2 = Reg[r2];
}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset, unsigned *extended_value)
{

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1, unsigned data2, unsigned extended_value, unsigned funct, char ALUOp, char ALUSrc,
				   unsigned *ALUresult, char *Zero)
{

}

/* Read / Write Memory */
/* 10 Points */
// Michael Ibeh
int rw_memory(unsigned ALUresult, unsigned data2, char MemWrite, char MemRead, unsigned *memdata, unsigned *Mem){

	// Address not word aligned
	if(ALUresult % 4 != 0)
		return 1;
	// Adress out of bounds
	if(ALUresult > 0xFFFF || ALUresult < 0x4000)
		return 1;
	
	// Writing to memory
	if(MemWrite == 1){
		Mem[ALUresult] = data2;
		return 0;
	}
	// Reading from memory
	if( MemRead == 1){
		memdata = Mem[ALUresult] 
		return 0;
	}

}


/* Write Register */
/* 10 Points */
// Alexander Cote
void write_register(unsigned r2, unsigned r3, unsigned memdata, unsigned ALUresult, char RegWrite, char RegDst,
					char MemtoReg, unsigned *Reg)
{
	if (RegWrite == 1)
	{
		if (MemtoReg == 1)
		{
			if(RegDst==0)
				Reg[r2] = memdata;
			else if(RegDst==1)
				Reg[r3] = memdata;
		}
		else if (ALUresult == 1)
		{
			if(RegDst==0)
				Reg[r2] = ALUresult;
			else if(RegDst==1)
				Reg[r3] = ALUresult;
		}
	}
	else
		return;
}

/* PC Update */
/* 10 Points */
// Michael Ibeh
void PC_update(unsigned jsec, unsigned extended_value, char Branch, char Jump, char Zero, unsigned *PC){

		unsigned new = 0;

		// beq
		if(Branch == 1){
			new = PC + (jsec * 4);
			*PC = new;
			return;
		}
		
		// j
		if(Jump == 1){
			*PC = jsec * 4;
			return;
		}
		
		// next sequential instruction
		*PC += 4;

		return;
}
/*
int main()
{
	unsigned *r = malloc(sizeof(unsigned));
	char *Zero = malloc(sizeof(char));
	ALU(1, 1, 1, r, Zero);

	return 0;
}
 */
