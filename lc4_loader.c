/************************************************************************/
/* File Name : lc4_loader.c		 										*/
/* Purpose   : This file implements the loader (ld) from PennSim		*/
/*             It will be called by main()								*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include "lc4_memory.h"
#include <byteswap.h>
#include <stdlib.h>
#include <string.h>


/* declarations of functions that must defined in lc4_loader.c */

FILE* open_file(char* file_name)
{
	FILE* file;

	file = fopen(file_name,"rb");
	if (file != NULL){
		return file;
	}
	else{
    printf("error open file");
		return NULL;
	}

	
}

int parse_file (FILE* my_obj_file, row_of_memory** memory)
  
/* remember to adjust 16-bit values read from the file for endiannness
 * remember to check return values from fread() and/or fgetc()
 */
  
{
  FILE* file;
  unsigned short int count = 0;
  unsigned short int type ; 
  unsigned short int address = 0x0000;
  unsigned short int tem = 0;
  unsigned long int tem_label = 0;

  int i;
  int n;
  fseek(my_obj_file, 0, SEEK_SET);
  row_of_memory* head = *memory;

	if (my_obj_file != NULL){
    while(1) {
      
      fread(&type, sizeof(type), 1, my_obj_file);
      if( feof(my_obj_file) ) { 
         break ;
      }
      fread(&address, sizeof(address), 1, my_obj_file);
      if( feof(my_obj_file) ) { 
         break ;
      }
      fread(&count, sizeof(count), 1, my_obj_file);
      if( feof(my_obj_file) ) { 
         break ;
      }
      type = bswap_16(type);
      address = bswap_16(address);
      count = bswap_16(count);
      printf("0x%hX \n", type);
      printf("0x%hX \n", address);
      //printf("0x%hX \n", count);
      printf("%d \n", count);

      if(type == 0xCADE){
        printf("it's CADE line\n");

      //printf("0x%hX \n", tem);
        row_of_memory* cade_code = *memory; // initial the linked list head

        for (i=0; i < count; i++){
          fread(&tem, sizeof(tem), 1, my_obj_file);
          if( feof(my_obj_file) ) { 
            break ;
          }
          tem = bswap_16(tem);
          add_to_list(memory, address, tem);
          address = address + 0x0001;
        }
        while (cade_code != NULL) {
          printf("0x%hX\n", cade_code -> address);
          printf("0x%hX\n", cade_code -> contents);
          cade_code = cade_code -> next;
        }
      }

      if(type == 0xDADA){
        printf("it's DADA line\n");

      //printf("0x%hX \n", tem);
        row_of_memory* dada_code = *memory; // initial the linked list head

        for (i=0; i < count; i++){
          fread(&tem, sizeof(tem), 1, my_obj_file);
          if( feof(my_obj_file) ) { 
            break ;
          }
          tem = bswap_16(tem);
          add_to_list(memory, address, tem);
          address = address + 0x0001;
        }
        while (dada_code != NULL) {
          printf("0x%hX\n", dada_code -> address);
          printf("0x%hX\n", dada_code -> contents);
          dada_code = dada_code -> next;
      }
      }

      if(type == 0xC3B7){
        printf("it's Label line\n");
        char* addlabel = malloc(count+1);
        row_of_memory* searchlist = *memory;
        row_of_memory* search_result;

        //printf("0x%hX \n", tem);

        fread(&tem_label, count, 1, my_obj_file);
        if( feof(my_obj_file) ) { 
          break ;
        }
          //tem_label = bswap_16(tem_label);
          //label = tem_label;
        printf("read the label in hex 0x%lX\n", tem_label);
        //sprintf(label, "0x%lX\n", tem_label);
        //printf("%s", label);
        for (i=0; i < count; i++){
          addlabel[i] = tem_label & 0xFF;
          tem_label = tem_label >> 8;
        }
        printf("label in char %s\n", addlabel);
        //printf("%hX\n", address);
        //while (searchlist != NULL) {
        //  printf("%d\n", searchlist-> address);
        //  searchlist = searchlist->next;
        //}

        search_result = search_address (searchlist, address);
        //printf("%s\n", search_result -> label);

        if(search_result != NULL){
          search_result -> label = addlabel;
          printf("add label %s\n", search_result -> label);
        }
        else{
          //add_to_list(memory, address, 0);
          //row_of_memory* searchlist = *memory;
          //search_result = search_address (searchlist, address);
          //search_result -> label = addlabel;
          //printf("create new node with label %s\n", search_result -> label);

	        row_of_memory* new_node;
	        new_node = malloc(sizeof(row_of_memory));

	        new_node -> address = address;
	        new_node -> contents = '\0';
	        new_node -> label = addlabel;
	        new_node -> assembly = NULL;
	        new_node -> next = NULL;

	        if (*memory == NULL){
		        *memory = new_node;
	        }

	        else{
		        row_of_memory* current = *memory;
		        while (current -> next != NULL) {
              current = current -> next;
            }
		        current -> next = new_node;
	        }
          
        }
        
      }

    }
    return (0);
    if(fclose(my_obj_file) != 0)
    {
      return (2);
    }
  }
  else{
    printf("error of parse file");
    return (1);
    fclose(my_obj_file);
  }
}


