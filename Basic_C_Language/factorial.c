#include <stdio.h>

int factorial(int num) {
	
	if (num == 1) {
		return 1;
	}

    return num * factorial(num - 1);

}

int main(void) {

	int num;
	
	scanf("%d", &num);
	printf("output : %d\n", factorial(num));

	return 0;
}