#include "malloc.h"

int main()
{
	free((void*)8);
	free((void*)16);
	free((void*)0xffffff00);
}
