#include <stdio.h>

// return 1 if num is a prime number, but otherwise return 0
int is_prime(int num) {
	if (num < 2) {
		return 0;
	}

	for (int i = 2; i <= num / 2; i++) {
		if (num % i == 0) {
			return 0;
		}
	}

	return 1;
}

int main(void) {

	int num;
	
	scanf("%d", &num);

	if (is_prime(num)) {
		printf("It is a prime number\n");
	}
	else {
		printf("It is not a prime number\n");
	}

	printf("%d\n", 109 / 2);
	return 0;
}