#include <stdio.h>

int main(void) {

	char ch, * cp;
	int num, * np;
	float fnum, * fp;
	double dnum, * dp;

	printf("&ch : %p, &num : %p, &fnum : %p, &dnum : %p\n", 
		&ch, &num, &fnum, &dnum);

	cp = &ch;
	np = &num;
	fp = &fnum;
	dp = &dnum;
	printf("cp : %p, np : %p, fp : %p, dp : %p\n",
		cp, np, fp, dp);
	
	//*cp = 'A';
	//*np = 24;
	//*fp = 1.34;
	//*dp = 3.14159345;

	//printf("%c %d %f %lf\n", ch, num, fnum, dnum);

	cp++;
	np += 2;
	fp++;
	dp += 2;
	printf("cp : %p, np : %p, fp : %p, dp : %p\n",
		cp, np, fp, dp);

	printf("size : %d\n", sizeof(*cp));

	return 0;

}