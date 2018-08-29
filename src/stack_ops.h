/* stack_ops.h */
// const int STKSIZE = 8;
#define STKSIZE 8
// const int STKMASK = 7;
#define STKMASK 7

extern int stack[];
extern int p; // = 0;

/* TOS is Top Of Stack */
#define TOS stack[p]

extern void push(int n);
extern int pop(void);
extern void dot(void);
extern void drop(void);
extern void dup(void);
extern void back(void);
extern void swap(void);
extern void dotS(void);
