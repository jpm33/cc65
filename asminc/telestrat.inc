;
; Oric TELEMON definition
; TELEMON 2.4 & TELEMON 3.x
; For TELEMON 3.x check http://orix.oric.org
;

; ---------------------------------------------------------------------------
; Constants

SCREEN_XSIZE    = 40            ; Screen columns
SCREEN_YSIZE    = 28            ; Screen rows

FUNCTKEY        = $A5

FNAME_LEN       = 11            ; Maximum length of file-name

; ---------------------------------------------------------------------------
; I/O Identifier
; Theses identifers are used for channel management
; 

XKBD            = $80           ; Keyboard
XRSE            = $83           ; RS232 in
XSCR            = $88           ; Screen
XRSS            = $90           ; RS232 out

; ---------------------------------------------------------------------------
; Zero page

; ---------------------------------------------------------------------------
; Page 00
RES             := $00
RESB            := $02

TR0             := $0C
TR1             := $0D
TR2             := $0E
TR3             := $0F
TR4             := $10
TR5             := $11
TR6             := $12
TR7             := $13

PTR_READ_DEST   := $2C           ; Used for XFREAD and XWRITE only in TELEMON 3.x

HRSX            := $46
HRSY            := $47

HRS1            := $4D
HRS2            := $4F
HRS3            := $51
HRS4            := $53
HRS5            := $55

HRSFB           := $57

; RS232T
; b0-b3 : speed 
;         1111 => 19200 bps  (please note that telestrat can't handle this speed without stopping all IRQ except ACIA's one)
;         1100 =>  9600 bps  (default from TELEMON)
;         1110 =>  4800 bps 
;         1010 =>  2400 bps 
;         1000 =>  1200 bps 
;         0111 =>   600 bps 
;         0110 =>   300 bps 
;         0101 =>   150 bps 
;         0010 =>    75 bps 

; b4    : 0 external clock, 1 internal clock
; b6-b5 : 00 8 bits
;         01 7 bits
;         10 6 bits
;         11 5 bits
; b7    : 0  a stop  

RS232T          := $59

; RS232C 
; b0-b3 : 0
; b4    : 1 if echo
; b5    : 1 if parity
; b7-b6 : 00 in/out parity odd
;       : 01 on/out parity even
;       : 10 parity sent, answer not tested
;       : 11 SPACE SENT, reception not tested

RS232C          := $5A

; ---------------------------------------------------------------------------
; Low memory
IRQVec          := $02FB        ; "fast" interrupt vector

; ---------------------------------------------------------------------------
; I/O locations

; 6522
.struct VIA                     ; Versatile Interface Adapter
        .res    $0300
PRB     .byte                   ; Port Register B
PRA     .byte                   ; Port Register A
DDRB    .byte                   ; Data Direction Register B
DDRA    .byte                   ; Data Direction Register A
T1      .word                   ; Timer 1
T1L     .word                   ; Timer 1 Latch
T2      .word                   ; Timer 2
SR      .byte                   ; Shift Register
ACR     .byte                   ; Auxiliary Control Register
PCR     .byte                   ; Peripheral Control Register
IFR     .byte                   ; Interrupt Flags Register
IER     .byte                   ; Interrupt Enable Register
PRA2    .byte                   ; Port Register A without handshaking
.endstruct


.struct VIA2                    ; Versatile Interface Adapter
        .res    $0320
PRB     .byte                   ; Port Register B
PRA     .byte                   ; Port Register A
DDRB    .byte                   ; Data Direction Register B
DDRA    .byte                   ; Data Direction Register A
T1      .word                   ; Timer 1
T1L     .word                   ; Timer 1 Latch
T2      .word                   ; Timer 2
SR      .byte                   ; Shift Register
ACR     .byte                   ; Auxiliary Control Register
PCR     .byte                   ; Peripheral Control Register
IFR     .byte                   ; Interrupt Flags Register
IER     .byte                   ; Interrupt Enable Register
PRA2    .byte                   ; Port Register A without handshaking
.endstruct

; 6551
.struct ACIA                    ; Asynchronous Communications Interface Adapter
        .res    $031C
DATA    .byte
STATUS  .byte
CMD     .byte                   ; Command register
CTRL    .byte                   ; Control register
.endstruct

SCREEN          := $BB80


; ---------------------------------------------------------------------------
; ROM entries

; TELEMON primitives (2.4 & 3.x)

; all values are used to call bank 7 of telestrat cardridge. It works with 'brk value' 
XRD0             = $08
XRDW0            = $0C
XWR0             = $10 
XWSTR0           = $14          ; Write a string in text mode
XTEXT            = $19
XHIRES           = $1A
XFILLM           = $1C
XMINMA           = $1F
XVARS            = $24          ; Only in TELEMON 3.x, in TELEMON 2.4, it's XNOMFI ($24)
XCRLF            = $25          ; Jump a line and return to the beginning of the line
XFREAD           = $27          ; Only in TELEMON 3.x (bank 7 of Orix)
XOPEN            = $30          ; Only in TELEMON 3.x (bank 7 of Orix)
XCOSCR           = $34          ; Switch off cursor
XCSSCR           = $35          ; Switch on cursor
XCLOSE           = $3A          ; Only in TELEMON 3.x close file (bank 7 of Orix)
XFWRITE          = $3B          ; Only in TELEMON 3.x write file (bank 7 of Orix)
XSONPS           = $40
XOUPS            = $42          ; Send Oups sound into PSG
XPLAY            = $43
XSOUND           = $44 
XMUSIC           = $45 
XZAP             = $46
XSHOOT           = $47
XMKDIR           = $4B          ; Create a folder. Only available in TELEMON 3.x (bank 7 of Orix)
XRM              = $4D          ; Remove a folder or a file. Only available in TELEMON 3.x (bank 7 of Orix)
XMALLOC          = $5B          ; Only in TELEMON 3.x (bank 7 of Orix)
XFREE            = $62          ; Only in TELEMON 3.x (bank 7 of Orix)
XSOUT            = $67          ; Send accumulator value (A) to RS232, available in TELEMON 2.4 & 3.x : if RS232 buffer is full, the Oric Telestrat freezes
XHRSSE           = $8C          ; Set hires position cursor
XDRAWA           = $8D          ; Draw a line 
XDRAWR           = $8E          ; Draw a line 
XCIRCL           = $8F
XCURSE           = $90
XCURMO           = $91
XPAPER           = $92
XINK             = $93
XBOX             = $94
XABOX            = $95
XFILL            = $96
XCHAR            = $97
XSCHAR           = $98          ; Draw a string in hires
XEXPLO           = $9C 
XPING            = $9D

; ---------------------------------------------------------------------------
; ROM entries variables

PWD_PTR          = $00

; ---------------------------------------------------------------------------
; Page $200
SCRX             := $220
SCRY             := $224
ADSCRL           := $218
ADSCRH           := $21C
HRSPAT           := $2AA        ; Hires pattern : it's used to draw pattern for a line or a circle
IRQVECTOR        := $2FA


; ---------------------------------------------------------------------------
; Page $500

BUFNOM           := $517
BUFEDT           := $590

MAX_BUFEDT_LENGTH=110

; ---------------------------------------------------------------------------
; Hardware
CH376_DATA       := $340
CH376_COMMAND    := $341

; ---------------------------------------------------------------------------
; MACRO 

.macro  BRK_TELEMON   value
	.byte $00,value
.endmacro
