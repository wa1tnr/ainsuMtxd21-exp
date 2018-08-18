/* warm.h */
/* wa1tnr - August, 2018 LGPL v2.1 */

// #include "driver_examples.h"
// #include "driver_init.h"
// #include "utils.h"

/* Terminal Input Buffer for interpreter */
// #define maxtib 16

// extern struct io_descriptor *io;
extern int state_warm; // = 0;
extern void _warm(void); // { // reboot the machine
extern void capture_warm(); // { // trap keystrokes to build a command

