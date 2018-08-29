/* math.c */

#include "stack_ops.h"

/* multiply */
void multiply(void) {
    int a = pop(); // 3
    int b = pop(); // 5
    push(a * b);
}

/* subtract */
void subtract(void) {
    int a = pop(); // 3
    int b = pop(); // 5
    push(b-a);
    // 5 3 -
}

/* add top two stack items */
// NAMED(_plus, "plus");
void plus(void) {
    int a = 0;
    int b = 0;
    a = pop();
    b = pop();
    push(a+b);
}

/* add top two items */
// NAMED(_add, "+");
void add(void) {
    int a = pop();
    TOS = a + TOS;
}
