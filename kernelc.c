#include "console.h"

void init_disk();

void sweet();

void kmain(struct MultibootInfo* mbi2){
	mbi = mbi2;
	console_init();
	init_disk();
	
	while(1){}
}

