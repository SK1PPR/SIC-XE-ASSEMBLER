
# SIC-XE-ASSEMBLER

The Simplified Instructional Computer (Extended edition) is a hypothetical computer system introduced in System Software: An Introduction to Systems Programming, by Leland Beck.
It is implemented using C++ programming language and uses Standard Template Library’s map for hash tables.
The input and output are all based on file management.
This repository aims to create an assembler for code written in SIC-XE.
The features the assembler allows for are:

-   Addressing Modes:
    - Direct Addressing Mode
    -   Indirect Addressing Mode
    -   Simple Addressing Mode
    -   Immediate Addressing Mode
    -   Relative Addressing Mode
        -   Program Counter (PC Register)
        -   Base (Base Register)
-   Extended Instruction (4bit Instruction)
-   Literals
-   Control Sections

## Design of Assembler

### Introduction

- SIC/XE stands for Simplified Instructional Computer Extra Equipment or Extra Expensive. This is particularly the advanced version of SIC,both of which are closely related and is upward compatible as well.
- Memory : It is made up of 8 bit bytes and the memory size is 1 megabyte (230 bytes). The memory size difference between SIC AND SIC/XE leads to a change in the instruction formats along with more versatile addressing modes in SIC/XE . 1 word in SIC/XE architecture is made up of 24 bits or 3 bytes . The entire addressing is based on byte addressing and word addresses are specified by their lower-order bits.
- Data Formats (SIC/XE): Characters are stored/represented as per their ASCII codes (American Standard Codes for Information Interchange) Integers are represented by Binary Numbers and floating point numbers(decimal values) using 48-bit formats as per IEEE.

### Details

Input to assembler- Assembler source program using the instruction set of SIC/XE. Output- Assembler will generate the following files as output-
- Pass 1 will generate a Symbol Table.
- Pass 1 will also generate Intermediate File for the Pass 2.
- Pass 2 will generate a listing file containing the input assembly code and address, block number, object code of each instruction.
-  Pass 2 will also generate an object program including following type of record: H, D, R, T, M and E types.
- An error file is also generated displaying the errors in the assembly program (if any).

## Assembler architecture

### Pass 1

- It updates the intermediate file and error file using the source file.
- If it is unable to find the source file or else if the intermediate file does not open, it writes the corresponding error in the error file and if the error file does not open, print it to the console.
- We declare the variables required. Then it takes the first line as input and check if it is a comment line.
- Until the lines are comments, we take them as input and print them to our intermediate file and update our line number.
- Once, the line is not a comment it checks if the opcode is `START`, if found, it updates the line number, `LOCCTR` and start address if not found, it initializes the start address and `LOCCTR` as `0`. Then, I have use two nested `while()` loops, in which the outer loop iterates till the opcode equals `END` and the inner loop iterates until the opcode is `END` or `CSECT`.
- Inside the inner loop, it checks if the line is a comment. If comment, it is printed to the intermediate file,line number is updated , and next input line is taken as input .
- If not a comment, it checks if there is a label in the line, if present it checks if label is present in the `SYMTAB`, if found we print an error saying Duplicatesymbol in the error file or else assign a name, address and other required values to the symbol and store it in the `SYMTAB`.
- Then, it checks if the opcode is present in the OPTAB, if present we find out its format and then accordingly change the `LOCCTR`.
- If not found in `OPTAB`, check it with assembler directives like `WORD`, `RESW`, `BYTE`, `RESBY` `TE`, `LTORG`, `ORG`,`BASE`,`USE`, `EQU`, `EXTREF` or `EXTDEF`.
- Accordingly, it inserts the symbols, external references and external definitions in the `SYMTAB` or the map for the control section which we created.
- For instance, for opcodes like `USE`, we insert a new `BLOCK` entry in the `BLOCK` map as defined in the `utility.cpp` file, for `LTORG` we call the handle `LTORG()` function defined in `pass1.cpp`, for `ORG`, we point out `LOCCTR` to the operand value given, for `EQU`, we check if whether the operand is an expression then we check whether the expression is valid by using the `evaluateExpression()` function, if valid then we enter the symbols in the `SYMTAB`.
- And if the opcode doesn’t match with the above given opcodes, we print an error message in the error file. Accordingly, we then update our data which is to be written in the intermediate file.
- After the ending of the while loop for control section, we update our `CSECT` TAB,the values for labels, `LOCCTR`, startaddress and length, and head on for the next control section until the outer loop ends.
- After the loop ends, we store the program length and then go on for printing the `SYMTAB`, `LITTAB` and other tables for control sections if present.
- After that the `pass2()` begins.

- **handle LT_ORG()** : It uses pass by reference. We print the literal pool present till time by taking the arguments from the `pass1()` function. We run an iterator to print all the literals present in the `LITTAB` and then update the line number. If for some literal, we did not find the address, we store the present address in the `LITTAB` and then increment the `LOCCTR` on the basis of the literal present.
- **evaluateExpression()** : It uses pass by reference. It uses a while loop to get the symbols from the expression. If the symbol is not found in the `SYMTAB`, we keep the error message in the error file. There is a variable `pairCount` which keeps the account of whether the expression is absolute or relative and if the `pairCount` gives some unexpected value, an error message is printed .
- **TABLES**: It contains all the data structures required for assembler to run. It contains the structs for `labels`, `opcode`, `literal`, `blocks`, `extdef`, `extref`, and `control sections`. The `CSECT` Tab contains `Maps` are defined for various tables with their indices as strings with the names of the labels or opcodes as required.
- **UTILITY**: It contains useful functions that will be required by the other files.
- **intstringtodecimal(stringstr)** : converts string to integer.
- **getString()** : takes in input as a character and returns a string.
- **intToStringHex()** : takes in input as int and then converts it into its hexadecimal equivalent with the string data type.
- **expandString()** : expands the input string to the given input size. It takes in the string to be expanded as a parameter and length of the output string and the character to be inserted in order to expand that string.
- **stringHexToInt()** : converts the hexadecimal string to an integer and returns the integer value.
- **stringToHexString()** : takes in a string as input and then converts the string into its hexadecimal equivalent and then returns the equivalent as a string.
- **checkWhiteSpace()** : checks if blanks are present. If present, returns true or else false.
- **checkCommentLine()** : check the comment by looking at the first character of the input string, and then accordingly returns true if comment or else false.
- **if_all_num()** : checks if all the elements of the string of the input string are number digits.
- **readFirstNonWhiteSpace()** : takes in the string and iterates until it gets the first non-space character. It is a pass-by reference function which updates the index of the input string until the blank space characters end and return void.
- **writeToFile()** : takes in the name of the file and the string to be written on to the file. Then writes the input string onto the new line of the file.
- **getRealOpcode()** : for opcodes of format 4, for example, `+JSUB` the function will see whether if the opcode contains some additional bit like ‘+’ or some other flag bits, then it returns the opcode leaving the first flag bit.
- **getFlagFormat()** : returns the flag bit if present in the input string or else it returns a null string.
- Class EvaluateString contains the functions :
- **peek()** : returns the value at the present index.
- **get()** : returns the value at the given index and then increments the index by one.  `number()` returns the value of the input string in integer format.

### Pass 2
- It takes in the intermediate file as input using the `readIntermediateFile()` function and generates the listing file and the object program. Similar to pass1, if the intermediate file is unable to open, It prints the error message in the error file. Same with the object file if unable to open. It then reads the first line of the intermediate file.
- Until the lines are comments, It takes them as input and print them to our intermediate file and update our line number.
- If the opcode is `START`, initialize out start address as the `LOCCTR` and write the line into the listing file.
- Then it checks whether the number of sections in our intermediate file was greater than one, if so, then update the program length as the length of the first control section, or else it keeps the program length unchanged. it then writes the first header record in the object program.
- Then until the opcode comes as `END` or `CSECT` if the control sections are present, it takes in the input lines from the intermediate file and then updates the listing file and then write the object program in the text record using the `textrecord()` function.
-  Then it writes the object code on the basis of the types of formats used in the instruction.
- Based on different types of opcodes such as `BYTE` , `WORD` , `BASE` , `NOBASE` , `EXTDEF` , `EXTREF` , `CSECT` , it will generate different types of object codes. For the format 3 and format 4 instruction formats, it will use the `createObjectCodeFormat34()` function in the `pass2.cpp`.
- For writing the end record, it uses the `writeEndRecord()` function.
- If control sections are present, it will use the `writeRRecord()` and `writeDRecord()` to write
the external references and the external definitions.
- For the instructions with immediate addressing, it will write the modification record.
- When the inner loop for the control section finishes, it will again loop to print the next section until the last opcode for `END` occurs.
- **readTillTab()** :takes in the string as input and reads the string until tab(backslash t) occurs.
- **readIntermediateFile()** : takes in line number, `LOCCTR`, `opcode`, `operand`, `label` and `input` `output` files. If the line is comment returns true and takes in the next input line. Then using the `readTillTab()` function, it reads the `label`, `opcode`, `operand` and the `comment`. Based on the different types of opcodes, it will count in the necessary conditions to take in the operand.
- **createObjectCodeFormat34()** : When it gets format for the opcode as 3 or 4, we call this function. It checks the various situations in which the opcode can be and then taking into consideration the operand and the number of half bytes calculates the object code for the instruction. It also modifies the modification record when there is a need to do so.
- **writeDRecord()**: It writes in the D record after the H record is written if the control sections are present.
- **writeRRecord()**: It writes in the R record for the control section.
- **writeEndRecord()**: It will write the end record for the program. After the execution of the `pass1.cpp`, it will print the Tables like `SYMTAB`, `LITTAB`, etc., in a separate file and then execute the `pass2.cpp`.

### Data Structures used in Implementation
- Map
- Struct Details :
- Maps are associative containers that store elements in a mapped fashion.
- Each element has a key value and a mapped value. Structure(struct) is a collection of variables
of different data types under a single name.
- It is similar to a class in that, both holds a collection of data of different data types.
- Map is used to store the `SYMBOL TABLE`, `OPCODE TABLE`, `REGISTER TABLE`, `LITERAL TABLE`, `BLOCK TABLE`, `CONTROL SECTIONS`.
- Each map of these tables contains a key in the form of string(data type) which represent an element of the table and the mapped value is a struct which stores the information of that element.
Structures of each are as follows :
- **SYMTAB** : The struct contains information on labels like name, address, block number, a character representing whether the label exits in the symbol table or not, an integer representing whether label is relative or not.
- **OPTAB** : The struct contains information of opcode like name, format, a character representing whether the opcode is valid or not.
- **LITTAB** : The struct contains information of literals like its value, address, block number, a character representing whether the literal exits in the literal table or not.
- **REGTAB** : The struct contains information of registers like its numeric equivalent, a character representing whether the registers exits or not.
- **BLOCKS** : The struct contains information of blocks like its name, start address, block number, location counter value for end address of block, a character representing whether the block exits or not.
- **CSECT** : The struct contains information of different control section like its name, start address,section number,length, location counter value for end address of section. It also contains two maps for `extref` and `extdef` of particular section.



## Instructions

### Compiling the binary

Run the following command in terminal to run the code
```
git clone https://github.com/SK1PPR/SIC-XE-ASSEMBLER.git

g++ pass2.cpp
```

### Running the code
The above command will create an `a.out` or `pass2.exe` depending on the operating system
Create an `input.txt` that contains the `SIC-XE` code.

```
./a.out input.txt
```

The program will generate the following files
```
object_input.txt
error_input.txt
listing_input.txt
intermediate_input.txt
```
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