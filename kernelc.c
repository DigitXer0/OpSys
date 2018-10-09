int factorial(int num)
{
	if(num >= 1)
		return num * factorial(num - 1);
	else
		return 1;
}

void clearBss(char* bssStart, char* bssEnd)
{
	for(;bssStart != bssEnd; bssStart++)
	{
		*bssStart = 0;
	}
}

void kmain(){
	factorial(5);
	asm volatile (
		"mov esi, 0xf00d\n"
		"hlt"
		::: "memory");	
}
