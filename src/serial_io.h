// #ifndef DRIVER_EXAMPLES_H_INCLUDED
// #define DRIVER_EXAMPLES_H_INCLUDED

// #ifdef __cplusplus
// extern "C" {
// #endif

extern struct io_descriptor *io;

extern void _que(void);
extern void _ok(void);
extern void _bkbar(void); // broken bar
extern void _spc(void);
extern void _cr(void); // line 113
extern void cr(void);
extern void USART_0_example_upper(void);
extern void USART_0_example_lower(void);

// #ifdef __cplusplus
// }
// #endif
// #endif // DRIVER_EXAMPLES_H_INCLUDED
