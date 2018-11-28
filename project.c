#include "spimcore.h"
#include <stdint.h>
#include <limits.h>

#define ERR INT_MIN
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
int instruction_decode(unsigned op, struct_controls *controls)
{
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
	if (op == 0)
	{
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
	if (op == 2)
	{
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
	switch (op)
	{

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

			// Invalid Instruction
		default:
			return 1;
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
// Charlton Trezevant
void sign_extend(unsigned offset, unsigned *extended_value)
{
	*extended_value = (int32_t) offset;
}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1, unsigned data2, unsigned extended_value, unsigned funct, char ALUOp, char ALUSrc,
				   unsigned *ALUresult, char *Zero)
{
	// R type
	if (ALUOp == 7)
	{
		switch (funct)
		{
			case 32:
				ALU(data1, data2, 0, ALUresult, Zero);
				//addition
				break;
			case 34:
				ALU(data1, data2, 1, ALUresult, Zero);
				//subtraction
				break;
			case 42:
				ALU(data1, data2, 2, ALUresult, Zero);
				//set less then
				break;
			case 43:
				ALU(data1, data2, 3, ALUresult, Zero);
				// slt unsin
				break;
			case 36:
				ALU(data1, data2, 4, ALUresult, Zero);
				// AND
				break;
			case 37:
				ALU(data1, data2, 5, ALUresult, Zero);
				//OR
				break;
			default:
				return 1;
		}
		return 0;
	}
	else
	{
		if(ALUSrc==0)
		{
			extended_value=data2;
		}
		switch (ALUOp)
		{
			case 0:
				ALU(data1, extended_value, 0, ALUresult, Zero);
				//lw sw addi
				break;
			case 1:
				ALU(data1, extended_value, 1, ALUresult, Zero); //beq
			case 2:
				ALU(data1, extended_value, 2, ALUresult, Zero);
				//set less immediate
				break;
			case 3:
				ALU(data1, extended_value, 3, ALUresult, Zero);
				//set less immediate Unsigned
				break;
			case 6:
				ALU(data1, extended_value, 6, ALUresult, Zero);
				// load upper i
				break;
			default:
				return 1;

		}
	}
	return 0;


}


/* Read / Write Memory */
/* 10 Points */
// Michael Ibeh
int rw_memory(unsigned ALUresult, unsigned data2, char MemWrite, char MemRead, unsigned *memdata, unsigned *Mem)
{

	// Address not word aligned
	if (ALUresult % 4 != 0)
		return 1;
	// Adress out of bounds
	if (ALUresult > 0xFFFF || ALUresult < 0x4000)
		return 1;

	// Writing to memory
	if (MemWrite == 1)
	{
		Mem[ALUresult] = data2;
		return 0;
	}
	// Reading from memory
	if (MemRead == 1)
	{
		*memdata = Mem[ALUresult];
		return 0;
	}

}


/* Write Register */
/* 10 Points */
// Alexander Cote
void write_register(unsigned r2, unsigned r3, unsigned memdata, unsigned ALUresult, char RegWrite, char RegDst,
					char MemtoReg, unsigned *Reg)
{
	//memory is byte addressed
	if (RegDst==0&&r2==0){
		return;
	}
	if (RegDst==0&&r3==0){
		return;
	}
	if (RegWrite == 1)
	{
		if (MemtoReg == 1)
		{
			if (RegDst == 0)
				Reg[r2] = memdata;
			else if (RegDst == 1)
				Reg[r3] = memdata;
		}
		else if (ALUresult == 1)
		{
			if (RegDst == 0)
				Reg[r2] = ALUresult;
			else if (RegDst == 1)
				Reg[r3] = ALUresult;
		}
	}
	else
		return;
}

/* PC Update */
/* 10 Points */
// Michael Ibeh
void PC_update(unsigned jsec, unsigned extended_value, char Branch, char Jump, char Zero, unsigned *PC)
{

<<<<<<< HEAD
		unsigned shift, upperFour;

		// beq
		if(Branch == 1){
			new = *PC + (jsec * 4);
			*PC = new;
			*PC += 4;
			return;
		}
		
		// j
		if(Jump == 1){
			shift = jsec << 2;
			upperFour = (*PC + 4) & 0xF0000000;
			*PC = shift | upperFour;
			return;
		}
		
		// next sequential instruction
		*PC += 4;
=======
	unsigned new = 0;

	// beq
	if (Branch == 1)
	{
		new = *PC + (jsec * 4);
		*PC = new;
		return;
	}
>>>>>>> 97b81f3fa5788e589174e8636814787de481932f

	// j
	if (Jump == 1)
	{
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