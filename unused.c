#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 82
#define NUM_LETTERS 26

int main() {
    int N; /* number of cases */
    int i, j, k;

    /* stores the case-by-case string */
    char *input = (char *)calloc(MAX_INPUT, sizeof(char));

    /* stores the number of times each character has occurred in input */
    int *occurrences = (int *)calloc(NUM_LETTERS, sizeof(int));

    scanf("%d\n", &N);

    for (i = 0; i < N; i++) {
        fgets(input, 81, stdin);
        printf("%s", input);
        size_t length = strlen(input) - 1;

        for (j = 0; j < length; j++) {
            if (isalpha(input[j])) {
                ++occurrences[ tolower(input[j]) - 'a' ];
            }
        }

        printf("Letters missing in case %d: ", i + 1);
        for (k = 0; k < NUM_LETTERS; k++) {
            if (!occurrences[k])
                printf("%c", k + 'a');
        }
        printf("\n");

        memset(input, '\0', MAX_INPUT);
        memset(occurrences, 0, sizeof(int) / sizeof(char) * NUM_LETTERS);
    }

    free(input);
    free(occurrences);
    return 0;
}
