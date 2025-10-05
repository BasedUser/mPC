format binary
include 'ccp-exe.inc'
include 'simplvm-fasm.inc'
include 'mmio.inc'
exeheader 0,""
macro puts_nonl strcptr
{
local ..printer,..waiter,..freedom
ld 0,(strcptr/4)
..printer:
wrrimmimm 2,tid
ldrind 1,0
opimm ADD,0,1
cmpi EQ,1,0
jif ..freedom
wrraimm 1,m1
wrrimmimm 1,wantact
..waiter:
ldrimm 1,wantact
cmpi NE,1,-1
jif ..waiter
jmp ..printer
..freedom:
}
beginvmcode SIMPLVM
ld 16,2
opimm POW,16,48
ld 8,string/4
ldrimm 0,curripcmsgind
opimm ADD,0,ipcmsgs/4
getdata:
ldrind 1,0
cmpi NE,1,1 ; check if the packet is from CCP
jif moredata
wrraind -1,0
opimm ADD,0,IPCMSG.m1/4
ldrind 1,0
;parse m1
mov 2,1
opind IDIV,2,16
cmpi EQ,2,0
jif gotdata
mov 3,2
mov 5,2
cmpi EQ,2,6
jif noreducer
opimm SUB,2,1
noreducer:
opimm SUB,2,1
ld 4,256
opind POW,4,2
mov 5,4
gitloop:
mov 4,1
opind IDIV,4,5
opimm MOD,4,256
wrrindind 4,8
cmpi EQ,4,0
jif skipadd
opimm ADD,8,1
skipadd:
opimm IDIV,5,256
opimm SUB,2,1
cmpi GE,2,0
jif gitloop
cmpi LT,3,6
jif gotdata
opimm ADD,0,10-(IPCMSG.m1/4)
cmpi LT,0,((7*512)+510)
jif moredata
opimm SUB,0,510
moredata:
jmp getdata
gotdata:
wrraind 10,8
opimm ADD,8,1
wrraind 0,8
puts_nonl string
wrrimmimm 1,tid ; send task end packet to CCP
wrrimmimm 0,m1
wrrimmimm 1,wantact
jmp $
string:
endvmcode
