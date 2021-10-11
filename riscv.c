#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 64-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file

int32_t* reg; // Array of 32 32-bit registers

void init_regs();
bool interpret(char* instr);
void write_read_demo();

/**
 * Initialize register array for usage.
 * Malloc space for each 32-bit register then initializes each register to 0.
 * Do not alter this function!
 */
void init_regs(){
	int reg_amount = 32;
	reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes
	for(int i = 0; i < 32; i++)
		reg[i] = i;
}



/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
bool interpret(char* instr){
        int i = 0;
	char** tokens = tokenize(instr);
	if(equals(tokens[0],LW))
	{
	   Load_Reg(tokens[1],tokens[2],tokens[3]);
	}//end if 
	else if(equals(tokens[0], "SW"))
	{
	   Store_Reg(tokens[1]],tokens[2],tokens[3]);
	
	
	}
	else if (equals(tokens[0], "ADD"))
	{
	    Add_reg(tokens[1],tokens[2], tokens[3]);
	}//end else if 
	else if (equals(tokens[0], "ADDI"))		
	{
	   ADDI_reg();
	}//end if	

	return true;
}
void Add_reg(char* tokenOne, char* tokenTwo,char* tokenThree)
{
	int32_t address = atoi(tokenTwo);
	int32_t t1 = atoi(tokenOne);
	int32_t t2 = atoi(tokenTwo);
	int32_t t3 = atoi(tokenThree);
	int32_t data = reg[t2] + reg[t3];
	reg[t1] = data;
}
void ADDI_reg(char* tokenOne,char* tokenTwo,char* tokenThree)
{
	int32_t t1 = atoi(tokenOne);
	int32_t t2 = atoi(tokenTwo);
	int32_t t3 = atoi(tokenThree);
	int32_t data = reg[t2] + t3;
	reg[t1] = data;
}
void Store_reg(char* tokenOne,char* tokenTwo,char* tokenThree)
{
	int32_t t2 = atoi(tokenTwo);
	int32_t t3 = atoi(tokenThree);
	int_t address_sum = reg[t2] + t3;
	int32_t n = write_address(address_sum,"mem.txt");
	reg(atoi(tokenOne[1])) = n;
}
void Load_Reg(char* tokenOne,char* tokenTwo,char* tokenThree) {
	
	int32_t t2 = atoi(tokenTwo);
	int32_t t3 = atoi(tokenThree);
	int32_t Address_sum =  reg[t2] + t3;
	int32_t n = read_address(Address_sum,"mem.txt");
	reg(atoi(tokenOne[1]) = n;
}//end method 

/**
 * Simple demo program to show the usage of read_address() and write_address() found in memory.c
 * Before and after running this program, look at mem.txt to see how the values change.
 * Feel free to change "data_to_write" and "address" variables to see how these affect mem.txt
 * Use 0x before an int in C to hardcode it as text, but you may enter base 10 as you see fit.
 */
void write_read_demo(){
	int32_t data_to_write = 0xFFF; // equal to 4095
	int32_t address = 0x98; // equal to 152
	char* mem_file = "mem.txt";

	// Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)
	int32_t write = write_address(data_to_write, address, mem_file);
	if(write == (int32_t) NULL)
		printf("ERROR: Unsucessful write to address %0X\n", 0x40);
	int32_t read = read_address(address, mem_file);

	printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
}
void print_regs(){

	int col_size = 10;

	for(int i = 0; i < 8; i++){

		printf("X%02i:%.*lld", i, col_size, (long long int) reg[i]);

		printf(" X%02i:%.*lld", i+8, col_size, (long long int) reg[i+8]);

		printf(" X%02i:%.*lld", i+16, col_size, (long long int) reg[i+16]);

		printf(" X%02i:%.*lld\n", i+24, col_size, (long long int) reg[i+24]);

	}

}

/**

 * Your code goes in the main

 *

 */

int main(){

	// Do not write any code between init_regs

	init_regs(); // DO NOT REMOVE THIS LINE



	print_regs();



	// Below is a sample program to a write-read. Overwrite this with your own code.

	//write_read_demo();



	printf(" RV32 Interpreter.\nType RV32 instructions. Use upper-case letters and 
space as a delimiter.\nEnter 'EOF' character to end program\n");



	char* instruction = malloc(1000 * sizeof(char));

	bool is_null = false;

	// fgets() returns null if EOF is reached.

	is_null = fgets(instruction, 1000, stdin) == NULL;

	while(!is_null){

		interpret(instruction);

		printf("\n");

		print_regs();

		printf("\n");



		is_null = fgets(instruction, 1000, stdin) == NULL;

	}



	printf("Good bye!\n");



	return 0;

}


