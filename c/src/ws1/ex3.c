#include <stdio.h> /* printf */

int main (void)
{

	/* Another way write "Hello World!" in hexadecimal */
	char str[] = {0x22, 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 0x6F, 0x72,
              	  0x6C, 0x64, 0x21, 0x22,0x00};

	printf("%s\n", str);

	/* One way write "Hello World!" in hexadecimal */
	printf("\x22\x48\x65\x6C\x6C\x6F\x20\x57\x6F\x72\x6C\x64\x21\x22\n");

  return 0;
}
