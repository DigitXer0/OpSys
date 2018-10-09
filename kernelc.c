#include "console.h"

void kmain(struct MultibootInfo* mbiInit){
	mbi = mbiInit;
	console_init();
	while(1){}
}

