#include <stdio.h>

int main(int argc, char** argv) {
    int T; // number of test cases
    int A; // size of Armin's mote
    int N; // number of other motes

    scanf("%d\n", &T);

    while (T--) {
        int moves = 0;
        scanf("%d %d\n", &A, &N);
        int *motes = (int *)calloc(N, sizeof(int));
