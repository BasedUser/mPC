virtual
include 'struct.inc'
struct IPCMSG
    sid dd ?
    tid dd ?
    ipcid dd ?
    m1 dd ?
    m2 dd ?
    m3 dd ?
    m4 dd ?
    m5 dd ?
    m6 dd ?
    m7 dd ? 
ends
org (7*512)*4
ipcmsgs:
rept 51 indx {
ipcmsg#indx IPCMSG
}
org ((7*512)+510)*4
curripcmsgind: dd ?
watchdogaddr: dd ?
org ((6*512)+503)*4
m7: dd ?
m6: dd ?
m5: dd ?
m4: dd ?
m3: dd ?
m2: dd ?
m1: n2: dd ?
tid: n1: pid: dd ?
wantact: dd ?
end virtual
