/************************************************************************/
/* File Name : lc4_disassembler.c 										*/
/* Purpose   : This file implements the reverse assembler 				*/
/*             for LC4 assembly.  It will be called by main()			*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include "lc4_memory.h"
#include <string.h>
#include <stdlib.h>

int reverse_assemble (row_of_memory* memory)
{
  /* binary constants should be proceeded by a 0b as in 0b011 for decimal 3 */
  row_of_memory* head = memory;
  row_of_memory* opcodematch;
  short unsigned int opcode = 0001;
  int num;
  //printf("%d\n",opcode);
  //while(opcodematch != NULL){
  int binarynum;
  
  int subcodemask = 56;
  int subcodenum;
  int firstmask = 3584;
  int first;
  int secondmask = 448;
  int second;
  int thirdmask = 7;
  int third;

  //memset(subcode, '\0', sizeof(subcode));
  int n, i;  

  while(1){
    char* assembly = malloc(15);
    opcodematch = search_opcode (head, opcode); 
    if(opcodematch == NULL){
      free(assembly);
      break;
    }
    //printf("0x%hX\n", opcodematch -> contents);
    //printf("%d\n", opcodematch -> contents);
    binarynum = opcodematch -> contents;
    subcodenum = binarynum & subcodemask;
    //printf("%d\n", subcodenum);

  switch(subcodenum){
            case 0 :
                //str = "000";
                strcat(assembly, "ADD");
                //printf("%s\n", instr_bin_str);
                break;
            case 8 :
                //str = "001";
                strcat(assembly, "MUL");
                //printf("%s\n", instr_bin_str);
                break;
            case 16 :
                //str = "001";
                strcat(assembly, "SUB");
                //printf("%s\n", instr_bin_str);
                break;
            case 24 :
                //str = "001";
                strcat(assembly, "DIV");
                //printf("%s\n", instr_bin_str);
                break;
            
            
  }
  //printf("%s\n", assembly);
  first = binarynum & firstmask;
  switch(first){
            case 0 :
                //str = "000";
                strcat(assembly, " R0,");
                //printf("%s\n", instr_bin_str);
                break;

            case 512 :
                //str = "000";
                strcat(assembly, " R1,");
                //printf("%s\n", instr_bin_str);
                break;
            case 1024 :
                //str = "001";
                strcat(assembly, " R2,");
                //printf("%s\n", instr_bin_str);
                break;
            case 1536 :
                //str = "001";
                strcat(assembly, " R3,");
                //printf("%s\n", instr_bin_str);
                break;
            case 2048 :
                //str = "001";
                strcat(assembly, " R4,");
                //printf("%s\n", instr_bin_str);
                break;
            case 2560 :
                //str = "001";
                strcat(assembly, " R5,");
                //printf("%s\n", instr_bin_str);
                break;
            case 3072 :
                //str = "001";
                strcat(assembly, " R6,");
                //printf("%s\n", instr_bin_str);
                break;
            case 3584 :
                //str = "001";
                strcat(assembly, " R7,");
                //printf("%s\n", instr_bin_str);
                break;
  }
  //printf("%s\n", assembly);

  second = binarynum & secondmask;

  switch(second){
            case 0 :
                //str = "000";
                strcat(assembly, " R0,");
                //printf("%s\n", instr_bin_str);
                break;
            case 64 :
                //str = "001";
                strcat(assembly, " R1,");
                //printf("%s\n", instr_bin_str);
                break;
            case 128 :
                //str = "001";
                strcat(assembly, " R2,");
                //printf("%s\n", instr_bin_str);
                break;
            case 192 :
                //str = "001";
                strcat(assembly, " R3,");
                //printf("%s\n", instr_bin_str);
                break;
            case 256 :
                //str = "001";
                strcat(assembly, " R4,");
                //printf("%s\n", instr_bin_str);
                break;
            case 320 :
                //str = "001";
                strcat(assembly, " R5,");
                //printf("%s\n", instr_bin_str);
                break;
            case 384 :
                //str = "001";
                strcat(assembly, " R6,");
                //printf("%s\n", instr_bin_str);
                break;
            case 448 :
                //str = "001";
                strcat(assembly, " R7,");
                //printf("%s\n", instr_bin_str);
                break;
  }
  //printf("%s\n", assembly);

  third = binarynum & thirdmask; 

  switch(third){
            case 0 :
                //str = "000";
                strcat(assembly, " R0");
                //printf("%s\n", instr_bin_str);
                break;
            case 1 :
                //str = "001";
                strcat(assembly, " R1");
                //printf("%s\n", instr_bin_str);
                break;
            case 2 :
                //str = "001";
                strcat(assembly, " R2");
                //printf("%s\n", instr_bin_str);
                break;
            case 3 :
                //str = "001";
                strcat(assembly, " R3");
                //printf("%s\n", instr_bin_str);
                break;
            case 4 :
                //str = "001";
                strcat(assembly, " R4");
                //printf("%s\n", instr_bin_str);
                break;
            case 5 :
                //str = "001";
                strcat(assembly, " R5");
                //printf("%s\n", instr_bin_str);
                break;
            case 6 :
                //str = "001";
                strcat(assembly, " R6");
                //printf("%s\n", instr_bin_str);
                break;
            case 7 :
                //str = "001";
                strcat(assembly, " R7");
                //printf("%s\n", instr_bin_str);
                break;
  }
  //printf("%s\n", assembly);

  opcodematch -> assembly = assembly;
  //printf("%s\n", opcodematch -> assembly);
  //free(assembly);

  }



  //}



	return 0 ;
}
