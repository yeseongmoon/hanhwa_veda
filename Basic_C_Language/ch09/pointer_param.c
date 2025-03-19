#include <stdio.h>

void swap(int* np1, int* np2) {
	int temp = *np1;
	*np1 = *np2;
	*np2 = temp;
}

int main(void) {

	int num1 = 10, num2 = 20;
	
	printf("%d %d\n", num1, num2);
	swap(&num1, &num2);
	printf("%d %d\n", num1, num2);

	return 0;

}