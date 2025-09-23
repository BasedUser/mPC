format binary
include 'ccp-exe.inc'
include 'simplvm-fasm.inc'
include 'mmio.inc'
exeheader 0,""
beginvmcode SIMPLVM
ld 0,(chars/4)
printer:
wrrimmimm 2,tid
ldrind 1,0
opimm ADD,0,1
cmpi EQ,1,0
jif freedom
wrraimm 1,m1
wrrimmimm 1,wantact
waiter:
ldrimm 1,wantact
cmpi NE,1,-1
jif waiter
jmp printer
freedom:
wrrimmimm 1,tid ; send task end packet to CCP
wrrimmimm 0,m1
wrrimmimm 1,wantact
jmp $
chars:
dd 'H','I',0x0a,0x00
endvmcode
