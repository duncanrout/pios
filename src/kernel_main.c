#include <stdio.h>
extern int __bss_start,__bss_end;

void clear_bss();

int temp;


void kernel_main(){
	clear_bss();
	while (1){
	}
}

void clear_bss(){
	(&__bss_start)[0] = 0x0c;
	int i = 0;
	while ((&__bss_start)+i != &__bss_end){
		(&__bss_start)[i] = 0;
		i++;
	}
}



