#include <stdio.h>
#include <string.h>

int main(void) {
	
	char str[20] = "hello";
	char* sp;

	sp = str;

	/*
	for (int i = 0; i < strlen(str); i++) {
		//printf("%c %x\n", str[i], *(sp + i));
		printf("%c %x\n", *(str + i), sp[i]);
	}
	*/

	//for (sp = str; sp < str + strlen(str); sp++) {
	//	printf("%c ", *sp);
	//}

	fgets(sp, sizeof(str), stdin);
	sp[strlen(sp) - 1] = '\0';
	printf("%c\n", *sp);

	return 0;
}