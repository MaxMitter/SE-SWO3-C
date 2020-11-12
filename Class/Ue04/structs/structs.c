#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 20
#define MAX_GROUP_SIZE 30

typedef struct person {
    char name[MAX_NAME_LENGTH];
    int age;
    char gender;
} person;

static void print_person(person p) {
    printf("Person: %s | Age: %d | Gender: %c\n", p.name, p.age, p.gender);
}

int main()
{
    // struct person p1;
    person p1;

    strcpy(p1.name, "Graf");
    p1.gender = 'M';
    p1.age = 20;

    printf("sizeof(struct person) = %d\n", (int)sizeof(struct person));
    printf("sizeof(p1) = %d\n", (int)sizeof(p1));

    print_person(p1);

    // ------------------------- //

    person swo32[MAX_GROUP_SIZE];
    swo32[0] = p1;
    strcpy(swo32[1].name, "Stoiber");
    swo32[1].age = 21;
    swo32[1].gender = 'M';
    return 0;
}
