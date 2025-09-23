macro exeheader isntexe,ntname {
org 0
if isntexe eq 1
db 'NT'
else
db 'VM'
end if
if isntexe eq 1
db ntname
times (14-$) db 0
end if
}
macro beginvmcode vmtype
{
dd exe_size
db vmtype
org 0
virtual
vmcode::
}
macro endvmcode
{
instr_count=($/4)
end virtual
;now we process the data
datindx=0
org 0
repeat instr_count
load instr dword from vmcode:datindx
if instr < (1 shl 7)
db instr
else if instr < (1 shl 14)
db (instr and 0x7f) or 0x80
db (instr shr 7)
else if instr < (1 shl 21)
db (instr and 0x7f) or 0x80
db ((instr shr 7) and 0x7f) or 0x80
db (instr shr 14)
else if instr < (1 shl 28)
db (instr and 0x7f) or 0x80
db ((instr shr 7) and 0x7f) or 0x80
db ((instr shr 14) and 0x7f) or 0x80
db ((instr shr 21) and 0x7f)
else
db (instr and 0x7f) or 0x80
db ((instr shr 7) and 0x7f) or 0x80
db ((instr shr 14) and 0x7f) or 0x80
db ((instr shr 21) and 0x7f) or 0x80
db ((instr shr 28) and 0x7f)
end if
datindx=datindx+4
end repeat
exe_size=$
}
