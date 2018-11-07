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
			{
				*Zero = 1;
			}
			else
			{
				*Zero = 0;
			}
			break;
		case 1:
			*ALUresult = A - B;
			if (*ALUresult == 0)
			{
				*Zero = 1;
			}
			else
			{
				*Zero = 0;
			}
			break;
		case 2:
			*ALUresult = A < B;
			if (*ALUresult == 0)
			{
				*Zero = 1;
			}
			else
			{
				*Zero = 0;
			}
			break;
		case 3:
			*ALUresult = A < B;
			if (*ALUresult == 0)
			{
				*Zero = 1;
			}
			else
			{
				*Zero = 0;
			}
			break;
			break;
		case 4:
			*ALUresult = A & B;
			if (*ALUresult == 0)
			{
				*Zero = 1;
			}
			else
			{
				*Zero = 0;
			}
			break;
		case 5:
			*ALUresult = A | B;
			if (*ALUresult == 0)
			{
				*Zero = 1;
			}
			else
			{
				*Zero = 0;
			}
			break;
		case 6:
			*ALUresult = B << 16;
			if (*ALUresult == 0)
			{
				*Zero = 1;
			}
			else
			{
				*Zero = 0;
			}
			break;
		case 7:
			*ALUresult = ~A;
			if (*ALUresult == 0)
			{
				*Zero = 1;
			}
			else
			{
				*Zero = 0;
			}
			break;
			return;
	}
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



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op, struct_controls *controls)
{

}

/* Read Register */
/* 5 Points */
//Alexander Cote
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
int rw_memory(unsigned ALUresult, unsigned data2, char MemWrite, char MemRead, unsigned *memdata, unsigned *Mem)
{

}


/* Write Register */
/* 10 Points */
//Alexander Cote
void write_register(unsigned r2, unsigned r3, unsigned memdata, unsigned ALUresult, char RegWrite, char RegDst,
					char MemtoReg, unsigned *Reg)
{
	if (RegWrite == 1)
	{
		if (MemtoReg == 1)
		{
			Reg[r2] = memdata;
			Reg[r3] = memdata;
		}
		else if (ALUresult == 1)
		{
			Reg[r2] = ALUresult;
			Reg[r3] = ALUresult;
		}
	}
	else
		return;
}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec, unsigned extended_value, char Branch, char Jump, char Zero, unsigned *PC)
{

}

int main()
{
	unsigned *r = malloc(sizeof(unsigned));
	char *Zero = malloc(sizeof(char));
	ALU(1, 1, 1, r, Zero);

	return 1;

}