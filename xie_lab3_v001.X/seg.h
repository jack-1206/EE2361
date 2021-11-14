#ifndef SEG_H
#define	SEG_H
#include <xc.h> // include processor files - each processor file is guarded.  

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // Insert declarations
    void init7seg(void);
    void showChar7seg(char myChar, int myDigit);
    void delay(long num);

#ifdef	__cplusplus
}
#endif
#endif  /* XC_HEADER_TEMPLATE_H */