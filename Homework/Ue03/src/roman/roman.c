#include <stdio.h>
#include <string.h>

#define MAX_LEN 50

int roman_to_decimal(char const r[]);
void decimal_to_roman(int d, char r[]);

int roman_to_decimal(char const r[]){
    int max = (int)strlen(r);

    int total = 0;
    for (int i = 0; i < max; i++) {
        switch (r[i])
        {
        case 'M':
            total += 1000;
            break;
        case 'D':
            total += 500;
            break;
        case 'C':
            if (r[i + 1] == 'M') {
                total += 900;
                i++;
            } else if (r[i + 1] == 'D') {
                total += 400;
                i++;
            } else
                total += 100;
            break;
        case 'L':
            if (r[i + 1] == 'M') {
                total += 950;
                i++;
            } else if (r[i + 1] == 'D') {
                total += 450;
                i++;
            } else
                total += 50;
            break;
        case 'X':
            if (r[i + 1] == 'C') {
                total += 90;
                i++;
            } else if (r[i + 1] == 'L') {
                total += 40;
                i++;
            } else
                total += 10;
            break;
        case 'V':
            if (r[i + 1] == 'L') {
                total += 45;
                i++;
            } else
                total += 5;
            break;
        case 'I':
            if (r[i + 1] == 'X') {
                total += 9;
                i++;
            } else if (r[i + 1] == 'V') {
                total += 4;
                i++;
            } else
                total += 1;
            break;
        default:
            total = -1;
            break;
        }
    }
    return total;
}

void decimal_to_roman(int d, char r[]) {
    int val = d;

    while (val >= 1000) {
        char replace[2] = "M";
        strncat(r, replace, 1);
        val -= 1000;
    }

    while (val >= 500) {
        if (val >= 900) {
            char replace[2] = "CM";
            strncat(r, replace, 2);
            val -= 900;
        } else {
            char replace[2] = "D";
            strncat(r, replace, 1);
            val -= 500;
        }
    }

    while (val >= 100) {
        if (val >= 400) {
            char replace[2] = "CM";
            strncat(r, replace, 2);
            val -= 400;
        } else {
            char replace[2] = "C";
            strncat(r, replace, 1);
            val -= 100;
        }
    }

    while (val >= 50) {
        if (val >= 90) {
            char replace[2] = "XC";
            strncat(r, replace, 2);
            val -= 90;
        } else {
            char replace[2] = "L";
            strncat(r, replace, 1);
            val -= 50;
        }
    }

    while (val >= 10) {
        if (val >= 40) {
            char replace[2] = "XL";
            strncat(r, replace, 2);
            val -= 40;
        } else {
            char replace[2] = "X";
            strncat(r, replace, 1);
            val -= 10;
        }
    }

    while (val >= 5) {
        if (val >= 9) {
            char replace[2] = "IX";
            strncat(r, replace, 2);
            val -= 9;
        } else {
            char replace[2] = "V";
            strncat(r, replace, 1);
            val -= 5;
        }
    }

    while (val >= 1) {
        if (val >= 4) {
            char replace[2] = "IV";
            strncat(r, replace, 2);
            val -= 4;
        } else {
            char replace[2] = "I";
            strncat(r, replace, 1);
            val -= 1;
        }
    }
}

int main(int argc, char const *argv[])
{
    char numb[] = {'M', 'C', 'M', 'L', 'X', 'V', '\0'};
    int num = roman_to_decimal(numb);
    printf("Test XC: %d\n", num);
    printf("Test XC: %d\n", roman_to_decimal("MCMLXV\0"));
    char r[MAX_LEN];

    for (int i = 0; i < MAX_LEN; i++)
        r[i] = '\0';

    decimal_to_roman(1965, r);
    printf("Test number: %s\n", r);
    return 0;
}
