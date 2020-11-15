#include <stdio.h>

#define NEW_LINE printf("\n")

void print_sequence(char text_left[], char text_top[], char sequence[]) {
    //printf(" w| %s\n", text_top);
    //printf(" v| %s\n", text_left);
    //printf("  | %s\n", sequence);

    printf("w |");
    int i = 0;
    int seq_counter = 0;
    int len = strlen(text_top);
    int seq_len = strlen(sequence);

    while (seq_counter <= seq_len) {
        if (sequence[seq_counter] == 'i') {
            printf("   ");
        } else {
            printf(" %c ", text_top[i]);
            i++;
        }
        seq_counter++;
    }
    NEW_LINE;

    printf("v |");
    i = 0;
    seq_counter = 0;
    len = strlen(text_left);
    while (seq_counter <= seq_len) {
        if (sequence[seq_counter] == 'd') {
            printf("   ");
        } else {
            if (i < len) {
                printf(" %c ", text_left[i]);
                i++;
            }
        }
        seq_counter++;
    }
    NEW_LINE;

    printf("  |");
    for (i = 0; i < strlen(sequence); i++) {
        printf(" %c ", sequence[i]);
    }
    NEW_LINE;
}

int main(int argc, char const *argv[])
{
    char test1[] = "ATCTGAT\0";
    int str1len = strlen(test1);
    char test2[] = "TGCATA\0";
    print_sequence(test1, test2, "dd cc i\0");
    return 0;
}
