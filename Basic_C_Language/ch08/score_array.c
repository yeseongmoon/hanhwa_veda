#include <stdio.h>

// put the score(music, art, p.e.) of 5 students, find the each average

int main(void) {
	int music[5], art[5], pe[5];
	float avg[5];

	for (int i = 0; i < sizeof(avg) / sizeof(avg[0]); i++) {
		printf("%d's score of music art p.e. : ", i+1);
		scanf("%d%d%d", &music[i], &art[i], &pe[i]);

		avg[i] = (music[i] + art[i] + pe[i]) / 3.0;
		printf("%d's average : %.2lf\n", i + 1, avg[i]);
	}

	return 0;
}