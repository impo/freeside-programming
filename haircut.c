#include <stdio.h>
#include <stdlib.h>

struct barber {
	int number;
	int total_time;
	int time_left;
};

void print_barbers(struct barber* barber_array, int num_barbers);

int cmp_barber_number(const void *lhs, const void *rhs);

int cmp_barber_total(const void *lhs, const void *rhs);

int cmp_barber_left(const void *lhs, const void *rhs);

int next_open(struct barber *barber_array, int num_barbers);

int main(int argc, char* argv[])
{
	int T; /* number of test cases */
	int N; /* your place in line */
	int B; /* barbers on duty */
	int i;
	int k;
	int j;
	int answer;
	struct barber *barber_array;

	scanf("%d\n", &T);
	for (k = 0; k < T; k++) {
		scanf("%d %d\n", &B, &N);
		barber_array = (struct barber *) malloc(sizeof(struct barber) * B);
		for (i = 0; i < B; i++) {
			struct barber tmp;
			tmp.number = i + 1;
			scanf("%d", &tmp.total_time);
			tmp.time_left = 0;
			barber_array[i] = tmp;
		}
		while (N--) {
			answer = barber_array[next_open(barber_array, B)].number;
		}
		printf("Case #%d: %d\n", k + 1, answer);
	}
	return 0;
}

int cmp_barber_number(const void *lhs, const void *rhs)
{
	struct barber *left;
	struct barber *right;

	left = (struct barber *) lhs;
	right = (struct barber *) rhs;

	if (left->number < right->number)
		return 0;
	else
		return 1;
}

void print_barbers(struct barber *barber_array, int num_barbers)
{
	int i;
	for (i = 0; i < num_barbers; i++) {
		printf("TIME LEFT: %d\nTOTAL TIME: %d\nNUMBER: %d\n\n",
			barber_array[i].time_left, barber_array[i].total_time,
			barber_array[i].number);
	}
}

int cmp_barber_total(const void *lhs, const void *rhs)
{
	struct barber *left;
	struct barber *right;

	left = (struct barber *) lhs;
	right = (struct barber *) rhs;

	if (left->total_time < right->total_time)
		return 0;
	else
		return 1;
}

int cmp_barber_left(const void *lhs, const void *rhs)
{
	struct barber *left;
	struct barber *right;

	left = (struct barber *) lhs;
	right = (struct barber *) rhs;

	if (left->time_left < right->time_left)
		return 0;
	else
		return 1;
}

int next_open(struct barber *barber_array, int num_barbers)
{
	int i;

	/* check to see which barber, if any, is not in use.  */
	/* prioritize for the barber with the lowest number.  */
	qsort(barber_array, num_barbers, sizeof(struct barber),
	      &cmp_barber_number);

	for (i = 0; i < num_barbers; i++) {
		if (barber_array[i].time_left == 0) {
			barber_array[i].time_left = barber_array[i].total_time;
			return i;
		}
	}

	/* if no barber is in use, find the one with the least time left */
	qsort(barber_array, num_barbers, sizeof(struct barber),
	      &cmp_barber_left);

	for (i = 0; i < num_barbers; i++) {
		if (barber_array[i].time_left > barber_array[0].time_left)
			barber_array[i].time_left -= barber_array[0].total_time;
		else
			barber_array[i].time_left = 0;
	}
	return 0;
}
