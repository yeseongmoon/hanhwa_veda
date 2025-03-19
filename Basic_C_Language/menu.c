#include <stdio.h>

void input_member(void);
void output_member(void);
void search_member(void);
void delete_member(void);

int main(void) {
	int choice;

	printf("1. Input\n");
	printf("2. Output\n");
	printf("3. Search\n");
	printf("4. Delete\n");
	printf("5. Exit\n");

	do {

	printf(">> ");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		input_member();
		break;
	case 2:
		output_member();
		break;
	case 3:
		search_member();
		break;
	case 4:
		delete_member();

		break;
	case 5:
		printf("You selected Exit\n");
		return 0;
	default:
		printf("Please choose another number\n");

	}
	} while (choice != 5);

	return 0;
}

// function definition
void input_member(void) {
	printf("You selected Input\n");
	return;
}

// function definition
void output_member(void) {
	printf("You selected Output\n");
	return;
}

// function definition
void search_member(void) {
	printf("You selected Search\n");
	return;
}

// function definition
void delete_member(void) {
	printf("You selected Delete\n");
	return;
}
