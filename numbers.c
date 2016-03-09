#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[])
{
	int T;
	int i;
	int j;
	int exponent;
	int digits;
	long double num;
	int final;

	scanf("%d", &T);
	for (i = 0; i < T; i++) {
		scanf("%d", &exponent);
		num = powl(3 + sqrtl(5), exponent);
		digits = (int) log10l(num) + 1;
		for (j = 0; j < digits - 3; j++) {
			num /= 10;
		}
		final = floor(num);
		printf("Case #%d: %03d\n", i + 1, final);
	}
}
