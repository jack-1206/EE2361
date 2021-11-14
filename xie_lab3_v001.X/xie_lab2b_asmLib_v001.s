;.include "xc.inc"
;
;.text                       ;BP (put the following data in ROM(program memory))
;
;; This is a library, thus it can *not* contain a _main function: the C file will
;; define main().  However, we
;; we will need a .global statement to make available ASM functions to C code.
;; All functions utilized outside of this file will need to have a leading 
;; underscore (_) and be included in a comment delimited list below.
.global _write_0, _write_1, _xie_wait_100us, _xie_wait_1ms, _rst
    
_write_0:      
    BSET LATA, #0x0
    repeat #3
    nop
    BCLR LATA, #0x0
    repeat #6
    nop
    return    
    
_write_1:      
    BSET LATA, #0x0
    repeat #10
    nop
    BCLR LATA, #0x0
    nop
    return
    
_xie_wait_100us:
    repeat #1593
    nop
    return
    
_xie_wait_1ms:
    repeat #15993
    nop 
    return

_rst:
    repeat #800
    nop
    return

