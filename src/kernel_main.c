#include <stdio.h>

extern long __bss_start;
extern long __bss_end;
int i;



void clear_bss(){

	char *begin_bss = (char *) &__bss_start;
	char *end_bss = (char *) &__bss_end;

	for(; begin_bss < end_bss; begin_bss++) {
		*begin_bss = 0;
	}
}

void kernel_main(){
	while(1){
	}
}



