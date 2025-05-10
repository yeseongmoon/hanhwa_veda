#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

	char big_name[1000] = "";
	char name[20];
	
	while (1) {

		printf("put the name : ");
		fgets(name, sizeof(name), stdin);
		name[strlen(name) - 1] = '\0';
		//printf(">> %s...\n", name);

		// check if the name is end
		if (strcmp(name, "end") == 0) {
			break;
		}

		// check if the length of big_name is bigger than 1000
		if (strlen(big_name) + strlen(name) + strlen(", ") > sizeof(big_name)) {
			break;
		}

		strcat(big_name, name);
		strcat(big_name, ", ");
	}

	printf("BIG NAME :\n%s", big_name);
	return 0;
}