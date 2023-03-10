#include <stdio.h>

typedef struct{
    char name[20];
} Name;

void go(Name *s) {
    fgets(s->name, 20, stdin);
    printf("%s", s->name);
}

void main() {
    Name s;
    go(&s);
}