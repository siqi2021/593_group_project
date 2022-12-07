/************************************************************************/
/* File Name : lc4_memory.c		 										*/
/* Purpose   : This file implements the linked_list helper functions	*/
/* 			   to manage the LC4 memory									*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include "lc4_memory.h"
#include <stdlib.h>

/*
 * adds a new node to a linked list pointed to by head
 */
int add_to_list (row_of_memory** head,
		 short unsigned int address,
		 short unsigned int contents)
{

  /* check to see if there is already an entry for this address and update the contents.  no additional steps required in this case */
  if((address != '\0') && (contents != '\0')){
  /* allocate memory for a single node */
	row_of_memory* new_node;
	new_node = malloc(sizeof(row_of_memory));
	/* populate fields in newly allocated node w/ address&contents, NULL for label and assembly */
	/* do not malloc() storage for label and assembly here - do it in parse_file() and reverse_assemble() */
	new_node -> address = address;
	new_node -> contents = contents;
	new_node -> label = NULL;
	new_node -> assembly = NULL;
	new_node -> next = NULL;
	/* if *head is NULL, node created is the new head of the list! */
	if (*head == NULL){
		*head = new_node;
	}

	/* otherwise, insert node into the list in address ascending order */
	else{
		row_of_memory* current = *head;
		while (current -> next != NULL) {
        current = current -> next;
    }
		current -> next = new_node;
	}
  

	/* return 0 for success, -1 if malloc fails */
	//free(new_node);
	return 0;
  //free(new_node);
	}
	else{
		printf("malloc fail\n");
		return (-1);
	}
	
}



/*
 * search linked list by address field, returns node if found
 */
row_of_memory* search_address (row_of_memory* head,
			       short unsigned int address )
{
	/* traverse linked list, searching each node for "address"  */
	row_of_memory* current = head;
	while (current -> address != address){
		current = current -> next;
    if (current == NULL){
      return NULL;
    }
	}
	/* return pointer to node in the list if item is found */
	//if(current != NULL){
	return (current);
	//}
	/* return NULL if list is empty or if "address" isn't found */
	//else{
	//  return NULL ;
	//}
}
/*
 * search linked list by opcode field, returns node if found
 */
row_of_memory* search_opcode  (row_of_memory* head,
				      short unsigned int opcode  )
{
    /* opcode parameter is in the least significant 4 bits of the short int and ranges from 0-15 */
		/* see assignment instructions for a detailed description */
    short unsigned int signopcode;
		short unsigned int signcontents;
		long int content_result[16];
		int i;
		signopcode = opcode << 12;
		//printf("%hx\n", signopcode);
    /* traverse linked list until node is found with matching opcode in the most significant 4 bits
	   AND "assembly" field of node is NULL */
		row_of_memory* current = head;

		while (current != NULL){
			
			signcontents = current -> contents;

			//printf("%ld\n", signcontents);
			signcontents = signcontents & 0xF000;
			//printf("%hx\n", signcontents);
			//printf("0x%hX\n", dada_code -> contents);
			if (signcontents == signopcode && current -> assembly == NULL){
				return current;
			}
			current = current -> next;
    	
		}

	/* return pointer to node in the list if item is found */
		
	/* return NULL if list is empty or if no matching nodes */

    return NULL;
    	
}


void print_list (row_of_memory* head )
{
	/* make sure head isn't NULL */
  if(head != NULL){
	/* print out a header */
  row_of_memory* current = head;
	int zero = 0;
    /* don't print assembly directives for non opcode 1 instructions if you are doing extra credit */

	/* traverse linked list, print contents of each node */

  printf(" <Label>\t<Address>\t<Contents>\t<assembly> \n");
  while (current != NULL){

		if(current -> contents == '\0'){
			printf("%10s\t%04hX\t\t%d\t\t%10s\n", current -> label, current -> address, zero , current -> assembly);
		}	
		else{
    printf("%10s\t%04hX\t\t%04hX\t\t%10s\n", current -> label, current -> address, current -> contents, current -> assembly);
		}
			
			current = current -> next;
    	
		}
  }
	return ;
  
}

/*
 * delete entire linked list
 */
int delete_list    (row_of_memory** head )
{
	/* delete entire list node by node */
	/* set the list head pointer to NULL upon deletion */
	row_of_memory* current;
	* head = current;
  row_of_memory* next = NULL;
 
    while (current != NULL){
      next = current -> next;
      free(current);
      current = next;
    }
 
    *head = NULL;
  
	return 0 ;
}
