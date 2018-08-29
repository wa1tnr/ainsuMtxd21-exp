// Tue Aug 28 23:24:03 UTC 2018

/* dict.h */

#define LOCATE_BOUNDS_ERR -11

// #define LLENGTH 48 // affects the 'words' word only, atm
#define LLENGTH 19 // affects the 'words' word only, atm
extern int linelen; // = LLENGTH; // = 28


extern int locate();
extern const int entries; // = sizeof dictionary / sizeof dictionary[0];

typedef void (*func)(void);           // signature of functions in dictionary

typedef struct {
    const char*    name;              // Pointer the Word Name in flash
    const func     function;          // Pointer to function
} entry;

extern const entry dictionary[];
extern void nop(void);
