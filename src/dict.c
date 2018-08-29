// Tue Aug 28 23:24:03 UTC 2018
// On branch xKM_converser_d51-kk-

/* dict.c */

#include "dict.h"
#include <string.h>
#include "common.h"
#include "getKey.h"
#include "serial_io.h"

#include "stack_ops.h"
#include "math.h"
#include "flashDict.h"
#include "warm.h"
#include "dump.h"
#include "ascii_art.h"

int linelen = LLENGTH; // = 28
// previous:
// Mon Aug 27 03:53:51 UTC 2018

/* buffer required for strings read from flash */
char namebuf[maxtib];

uint8_t* adrs_ram = 0;

/* demo ascii art */
NAMED(_aart, "aart");
void aart(void) {
    forth_ascii();
}

/* destructively display top of stack, decimal */
NAMED(_dott, ".");
void dott(void) { // earlier dot() word bypassed temporarily
    dot(); // io_write(io, (uint8_t *)" ~dot~", 7);
}

// const char x[]=y
const char _nop[2]=" \0";
// NAMED(_nop, " "); // swapped _name with _nopp
void nop(void) { }

NAMED(_nopp, "nop");  // swapped _name with _nop
void nopp(void) { }

void help(void) {
    io_write(io, (uint8_t *) "    type 'words' instead of 'help'.\r\n\r\n", 39);
    io_write(io, (uint8_t *) "    8304 16 dump         \r\n", 27);
}

void dump(void) { // ( adrs lines --  )
    int popped = pop();
    for (int i= popped; i > 0; i--) {
        adrs_ram = cdump();
        push(((uint32_t)adrs_ram) + 16); // address of the most recent line dumped
    }
}

void words(void); // forward declaration // 28 Aug 22:35 UTC

/* look in stack_ops.c - for example - to find the
   definitions of most of the earliest dictionary
   entries referred to in the table found below. */

/* table of names and function addresses in flash */
// extern const entry dictionary[];
const entry dictionary[] = {
    { _nopp,      nopp   }, // just switched these 28 Aug 23:10 UTC
    { _plus,      plus   },
    { _cr_n,      cr     },
    { _dott,      dott   },
    { _dup,       dup    },
    { _drop,      drop   },
    { _back,      back   },
    { _swap,      swap   },
    { _dotS,      dotS   },
    { _multiply,  multiply },
    { _subtract,  subtract },
    { _add,       add    },
    { _dump,      dump   },
    { _words,     words  },
    { _help,      help   },
    { _aart,      aart   },
    { _warm_,     _warm  },
    { _nop,       nop    }, // just switched these 28 Aug 23:10 UTC
};

/* Number of words in the dictionary */
const int entries = sizeof dictionary / sizeof dictionary[0];

/* Find a word in the dictionary, returning its position */
int locate(void) {
  for (int i = entries - 1; i >= 0; i--) {
    strcpy(namebuf, dictionary[i].name);
    if (!strcmp(tib, namebuf)) return i;
  }
  return LOCATE_BOUNDS_ERR ; // return 0;
}

/* Display all words in dictionary */
void words(void) { // 28 Aug 20:05 UTC
    int count_ln = 0; // count of line's length
    for (int i = entries - 2; i >= 0; i--) { // entries - 2 mask the 'nop' word which is a space
        strcpy(namebuf, dictionary[i].name);
        count_ln = count_ln + strlen(namebuf) + 1 ; // how long this line is, so far
        io_write(io, (uint8_t *)namebuf, strlen(namebuf));
        _spc();
        if (count_ln > linelen) { // exceeded
            count_ln = 0; // reset
            _cr(); // newline
        }
    }
}
