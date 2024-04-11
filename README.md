
# SIC-XE-ASSEMBLER

The Simplified Instructional Computer (Extended edition) is a hypothetical computer system introduced in System Software: An Introduction to Systems Programming, by Leland Beck.
This repository aims to create an assembler for code written in SIC-XE.
The features the assembler allows for are:

-   Addressing Modes:
    -   Direct Addressing Mode
    -   Indirect Addressing Mode
    -   Simple Addressing Mode
    -   Immediate Addressing Mode
    -   Relative Addressing Mode
        -   Program Counter (PC Register)
        -   Base (Base Register)
-   Extended Instruction (4bit Instruction)
-   Control Sections

## Design of Assembler

## Instructions for compiling


## Sample Input

```
COPY    START    0
        EXTDEF   BUFFER,BUFEND,LENGTH
        EXTREF   RDREC,WRREC
FIRST   STL      RETADR
CLOOP  +JSUB     RDREC
        LDA      LENGTH
        COMP    #0
        JEQ      ENDFIL
       +JSUB     WRREC
        J        CLOOP
ENDFIL  LDA     =C'EOF'
        STA      BUFFER
        LDA     #3
        STA      LENGTH
       +JSUB     WRREC
        J       @RETADR
RETADR  RESW     1
LENGTH  RESW     1
        LTORG
BUFFER  RESB     4096
BUFEND  EQU      *
MAXLEN  EQU      BUFEND-BUFFER
RDREC   CSECT
.
.       SUBROUTINE TO READ RECORD INTO BUFFER
.
        EXTREF   BUFFER,LENGTH,BUFFEND
        CLEAR    X
        CLEAR    A
        CLEAR    S
        LDT      MAXLEN
RLOOP   TD       INPUT
        JEQ      RLOOP
        RD       INPUT
        COMPR    A,S
        JEQ      EXIT
       +STCH     BUFFER,X
        TIXR     T
        JLT      RLOOP
EXIT   +STX      LENGTH
        RSUB
INPUT   BYTE     X'F1'
MAXLEN  WORD     BUFEND-BUFFER
.....
WRREC   CSECT
.
.       SUBROUTINE TO WRITE RECORD FROM BUFFER
.
        EXTREF    LENGTH,BUFFER
        CLEAR     X
       +LDT       LENGTH
WLOOP   TD       =X'05'
        JEQ       WLOOP
       +LDCH      BUFFER,X
        WD       =X'05'
        TIXR      T
        JLT       WLOOP
        RSUB
        END       FIRST
```

## Sample Output

-   LIS file
```
	 Pass	1 ... 

line number     address        label    op      operands        
===============================================================
1               000000         COPY     START   0               
2               000000                  EXTDEF     BUFFER,BUFEND,LENGTH
3               000000                  EXTREF     RDREC,WRREC  
4               000000         FIRST    STL     RETADR          
5               000003         CLOOP   +JSUB    RDREC           
6               000007                  LDA     LENGTH          
7               00000A                  COMP    #0              
8               00000D                  JEQ     ENDFIL          
9               000010                 +JSUB    WRREC           
10              000014                  J       CLOOP           
11              000017         ENDFIL   LDA     =C'EOF'         
12              00001A                  STA     BUFFER          
13              00001D                  LDA     #3              
14              000020                  STA     LENGTH          
15              000023                 +JSUB    WRREC           
16              000027                  J       @RETADR         
17              00002A         RETADR   RESW    1               
18              00002D         LENGTH   RESW    1               
19              000030                  LTORG                   
20              000030         *        =C'EOF'                 
21              000033         BUFFER   RESB    4096            
22              001033         BUFEND   EQU     *               
23              001033         MAXLEN   EQU     BUFEND-BUFFER   

***************************************************************

	 Symbol		 Table		 (values in hex)

=================================
|	name     address   Abs/Rel	|
|	--------------------------	|
|	BUFEND    1033         Rel	|
|	BUFFER    0033         Rel	|
|	CLOOP     0003         Rel	|
|	COPY      0000         Rel	|
|	ENDFIL    0017         Rel	|
|	FIRST     0000         Rel	|
|	LENGTH    002D         Rel	|
|	MAXLEN    1000         Rel	|
|	RETADR    002A         Rel	|
=================================
                               .
                               .       SUBROUTINE TO READ RECORD INTO BUFFER
                               .
24              000000                  EXTREF     BUFFER,LENGTH,BUFFEND
25              000000                  CLEAR   X               
26              000002                  CLEAR   A               
27              000004                  CLEAR   S               
28              000006                  LDT     MAXLEN          
29              000009         RLOOP    TD      INPUT           
30              00000C                  JEQ     RLOOP           
31              00000F                  RD      INPUT           
32              000012                  COMPR   A,S             
33              000014                  JEQ     EXIT            
34              000017                 +STCH    BUFFER,X        
35              00001B                  TIXR    T               
36              00001D                  JLT     RLOOP           
37              000020         EXIT    +STX     LENGTH          
38              000024                  RSUB                    
39              000027         INPUT    BYTE    X'F1'           
40              000028         MAXLEN   WORD    BUFEND-BUFFER   
                               .....

***************************************************************

	 Symbol		 Table		 (values in hex)

=================================
|	name     address   Abs/Rel	|
|	--------------------------	|
|	EXIT      0020         Rel	|
|	INPUT     0027         Rel	|
|	MAXLEN    0028         Rel	|
|	RLOOP     0009         Rel	|
=================================
                               .
                               .       SUBROUTINE TO WRITE RECORD FROM BUFFER
                               .
41              000000                  EXTREF      LENGTH,BUFFER
42              000000                  CLEAR   X               
43              000002                 +LDT     LENGTH          
44              000006         WLOOP    TD      =X'05'          
45              000009                  JEQ     WLOOP           
46              00000C                 +LDCH    BUFFER,X        
47              000010                  WD      =X'05'          
48              000013                  TIXR    T               
49              000015                  JLT     WLOOP           
50              000018                  RSUB                    
51              00001B                  END     FIRST           
52              00001B         *        =X'05'                  

***************************************************************

	 Symbol		 Table		 (values in hex)

=================================
|	name     address   Abs/Rel	|
|	--------------------------	|
|	WLOOP     0006         Rel	|
=================================

*****************************************************************************************

	 Pass	2 ... 

line number     address        label    op      operands        n i x b p e    opcode    
=========================================================================================
53              000000         COPY     START   0                                        
54              000000                  EXTDEF     BUFFER,BUFEND,LENGTH                         
55              000000                  EXTREF     RDREC,WRREC                           
56              000000         FIRST    STL     RETADR          1 1 0 0 1 0    172027    
57              000003         CLOOP   +JSUB    RDREC           1 1 0 0 0 1    4B100000  
58              000007                  LDA     LENGTH          1 1 0 0 1 0    032023    
59              00000A                  COMP    #0              0 1 0 0 1 0    292000    
60              00000D                  JEQ     ENDFIL          1 1 0 0 1 0    332007    
61              000010                 +JSUB    WRREC           1 1 0 0 0 1    4B100000  
62              000014                  J       CLOOP           1 1 0 0 1 0    3F2FEC    
63              000017         ENDFIL   LDA     =C'EOF'         1 1 0 0 1 0    032016    
64              00001A                  STA     BUFFER          1 1 0 0 1 0    0F2016    
65              00001D                  LDA     #3              0 1 0 0 1 0    012003    
66              000020                  STA     LENGTH          1 1 0 0 1 0    0F200A    
67              000023                 +JSUB    WRREC           1 1 0 0 0 1    4B100000  
68              000027                  J       @RETADR         1 0 0 0 1 0    3E2000    
69              00002A         RETADR   RESW    1                                        
70              00002D         LENGTH   RESW    1                                        
71              000030                  LTORG                                            
72              000030         *        =C'EOF'                                464F45    
73              000033         BUFFER   RESB    4096                                     
74              001033         BUFEND   EQU     *                                        
75              000000                  EXTREF     BUFFER,LENGTH,BUFFEND                         
76              000000                  CLEAR   X               1 1 0 0 0 0    B410      
77              000002                  CLEAR   A               1 1 0 0 0 0    B400      
78              000004                  CLEAR   S               1 1 0 0 0 0    B440      
79              000006                  LDT     MAXLEN          1 1 0 0 1 0    77201F    
80              000009         RLOOP    TD      INPUT           1 1 0 0 1 0    E3201B    
81              00000C                  JEQ     RLOOP           1 1 0 0 1 0    332FFA    
82              00000F                  RD      INPUT           1 1 0 0 1 0    DB2015    
83              000012                  COMPR   A,S             1 1 0 0 0 0    A004      
84              000014                  JEQ     EXIT            1 1 0 0 1 0    332009    
85              000017                 +STCH    BUFFER,X        1 1 1 0 0 1    57900000  
86              00001B                  TIXR    T               1 1 0 0 0 0    B850      
87              00001D                  JLT     RLOOP           1 1 0 0 1 0    3B2FE9    
88              000020         EXIT    +STX     LENGTH          1 1 0 0 0 1    13100000  
89              000024                  RSUB                    1 1 0 0 0 0    4F0000    
90              000027         INPUT    BYTE    X'F1'                          F1        
91              000000                  EXTREF      LENGTH,BUFFER                         
92              000000                  CLEAR   X               1 1 0 0 0 0    B410      
93              000002                 +LDT     LENGTH          1 1 0 0 0 1    77100000  
94              000006         WLOOP    TD      =X'05'          1 1 0 0 1 0    E32012    
95              000009                  JEQ     WLOOP           1 1 0 0 1 0    332FFA    
96              00000C                 +LDCH    BUFFER,X        1 1 1 0 0 1    53900000  
97              000010                  WD      =X'05'          1 1 0 0 1 0    DF2008    
98              000013                  TIXR    T               1 1 0 0 0 0    B850      
99              000015                  JLT     WLOOP           1 1 0 0 1 0    3B2FEE    
100             000018                  RSUB                    1 1 0 0 0 0    4F0000    
101             00001B                  END     FIRST                                    
```

-   Object file
```
H^COPY  ^000000^00001B

D^BUFFER^000033^BUFEND^001033^LENGTH^00002D


R^RDREC^WRREC


T^000000^10^172027^4B100000^032023^292000^332007
T^000010^10^4B100000^3F2FEC^032016^0F2016^012003
T^000020^0A^0F200A^4B100000^3E2000

M^000004^05^+RDREC
M^000011^05^+WRREC
M^000024^05^+WRREC


*****************************************************************************************

H^RDREC ^000000^00001B


R^BUFFER^LENGTH^BUFFEND


T^000000^0C^B410^B400^B440^77201F^E3201B
T^00000C^0F^332FFA^DB2015^A004^332009^57900000
T^00001B^0C^B850^3B2FE9^13100000^4F0000^F1

M^000018^05^+BUFFER
M^000021^05^+LENGTH
M^000028^06^-BUFFER


*****************************************************************************************

H^WRREC ^000000^00001B


R^LENGTH^BUFFER


T^000000^10^B410^77100000^E32012^332FFA^53900000
T^000010^0B^DF2008^B850^3B2FEE^4F0000

M^000003^05^+LENGTH
M^00000D^05^+BUFFER


*****************************************************************************************


```