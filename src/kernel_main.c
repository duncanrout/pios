#include "list.h"
#include "rprintf.h"
#include "serial.h"
#include "page.h"
# define NULL (void)0

//void clear_bss();

//extern int __bss_start;
//extern int __bss_end;
extern struct ppage* free_list;
int global;
 
void kernel_main(){
        //clear_bss();

	//Homework 7 - worked with luis, used code from haris (inclass)
	//list.h and list.c are updated to the professor's code
	init_pfa_list();
	struct ppage* test = free_list->next;
	test = test->next;
	esp_printf(putc, "Physical Address: %x\n", test->physical_addr);
	test = allocate_physical_pages(2);
	esp_printf(putc, "Allocated Address:  %x \n", test->physical_addr);
	test = allocate_physical_pages(2);
	esp_printf(putc, "Allocated Address:  %x \n", test->physical_addr);
	free_physical_pages(test);
	esp_printf((void *)putc, "Address after Freeing: %x\n", test->physical_addr);
	
	while (1){
	//temp
	}
}

/*
void clear_bss() {
	char * bssStart = &__bss_start;
	char * bssEnd = &__bss_end;
	int bssSize = bssEnd - bssStart;
	for (int i=0; i<bssSize; i++){
		bssStart[i] = 0;
	}
}*/




