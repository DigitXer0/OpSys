#include "console.h"

void sweet();

void kmain(struct MultibootInfo* mbi2){
	mbi = mbi2;
	console_init();
	sweet();
	while(1){}
}

