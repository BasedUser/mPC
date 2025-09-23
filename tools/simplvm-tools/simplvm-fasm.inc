;designed for fasm
ADD equ 0
SUB equ 1
DIV equ 2
MUL equ 3
IDIV equ 4 
MOD equ 5
POW equ 6
XOR equ 7
AND equ 8
OR equ 9
EQ equ 0
LT equ 1
GT equ 2
LE equ 3
GE equ 4
NE equ 5
SIMPLVM equ 0
macro stnum val
{
dd val
}
macro mov to,from
{
stnum 0
stnum to
stnum from
}
macro ld reg,val
{
stnum 1
stnum reg
stnum val
}
macro opind type,ro,rt
{
stnum 2
stnum (type shl 1)
stnum ro
stnum rt
}
macro opimm type,ro,val
{
stnum 2
stnum (type shl 1) or 1
stnum ro
stnum val
}
macro ldrimm reg,addr
{
uaddr=addr
stnum 3
stnum 1
stnum reg
stnum (uaddr shr 2)
}
macro ldrind reg,regaddr
{
stnum 3
stnum 0
stnum reg
stnum regaddr
}
;wrr imm field is imm2(bit 0),imm1(bit 1)
;imm1 is for val
;imm2 is for addr
macro wrrimmimm val,addr
{
uaddr=addr
stnum 4
stnum 3
stnum val
stnum (uaddr shr 2)
}
macro wrraimm reg,addr
{
uaddr=addr
stnum 4
stnum 1
stnum reg
stnum (uaddr shr 2)
}
macro wrrindind reg,regaddr
{
stnum 4
stnum 0
stnum reg
stnum regaddr
}
macro wrraind val,regaddr
{
stnum 4
stnum 2
stnum val
stnum regaddr
}
macro cmpi op,reg,imm
{
stnum 5
stnum ((op shl 1) or 1)
stnum reg
stnum imm
}
macro cmp op,reg,rego
{
stnum 5
stnum (op shl 1)
stnum reg
stnum rego
}
macro jmp to
{
jmpaddr=to ; so that $ refers to the start of the instruction!!!
stnum 6
stnum (jmpaddr shr 2);since new vm index is every 4 bytes
}
macro jif to
{
jmpaddr=to
stnum 7
stnum (jmpaddr shr 2)
}
