#include "list.h"
#include "page.h"
#define NULL (void*)0
#define NPAGES 128
extern int __end;

struct ppage physical_page_array[NPAGES];
struct ppage* free_list = NULL;

void init_pfa_list(void){
	void* address_p = (((unsigned long)&__end) & ~(0x200000 -1)) + 0x200000;
	int x;
	for(x=0; x<NPAGES; x++){
		listAdd(&free_list, (struct listElement*) &physical_page_array[x]);
		physical_page_array[x].physical_addr = address_p;
		address_p += 0x200000;
	}
}

struct ppage *allocate_physical_pages(unsigned int npages){
	int x;
	struct ppage* new_var = free_list;
	struct ppage* new_list = NULL;
	for(x=0; x<npages; x++){
		listRemove(new_var);
		listAdd(&new_list, new_var);
	}
	return new_list;
}

void free_physical_pages(struct ppage *ppage_list){
	struct ppage* new_var = ppage_list;
	while(ppage_list != NULL){
		listRemove(new_var);
		listAdd(&free_list, new_var);
	}
}
