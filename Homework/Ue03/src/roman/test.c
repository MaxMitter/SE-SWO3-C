#include "roman.h"

int main(int argc, char const *argv[])
{
    printf("Test MCMLXV: %d\n", roman_to_decimal("MCMLXV\0"));
    printf("Test MCMLXLVIV: %d\n", roman_to_decimal("MCMLXLVIV\0"));
    printf("Test XI.VI: %d.%d\n", roman_to_decimal("XI\0"), roman_to_decimal("VI\0"));
    printf("Test DCL: %d\n", roman_to_decimal("DCL\0"));
    printf("Test MM: %d\n", roman_to_decimal("MM\0"));


    char test1965[50] = {'\0'};

    decimal_to_roman(1965, test1965);
    printf("Test 1965: %s\n", test1965);
    char test1999[50] = {'\0'};
    decimal_to_roman(1999, test1999);
    printf("Test 1999: %s\n", test1999);
    char test11[50] = {'\0'};
    char test06[50] = {'\0'};
    decimal_to_roman(11, test11);
    decimal_to_roman(06, test06);
    printf("Test 11.06: %s.%s\n", test11, test06);
    char test650[50] = {'\0'};
    decimal_to_roman(650, test650);
    printf("Test 650: %s\n", test650);
    char test2000[50] = {'\0'};
    decimal_to_roman(2000, test2000);
    printf("Test 2000: %s\n", test2000);
    return 0;
}
