import sys,os
from pathlib import Path
list=[]
def check_out_path(tpath,name,par):
	if tpath.is_dir():
		files=[]
		val=["d",0,par,None]
		for file in tpath.iterdir():
			files.append([file.name,check_out_path(file,file.name,val)])
		val[1]=len(files)
		val[3]=files
		list.insert(0,val)
		return val
	else:
		content=""
		file=tpath.open("rb")
		bin=file.read()
		file.close()
		val=[chr(0x100|int(i)) for i in bin]
		list.insert(0,["f",tpath.stat().st_size,"".join(val)])
		return list[0]
if len(sys.argv)<2:
 print("Usage: python3 gentarfs.py <directory-to-pack>")
 exit(-1)
target=Path(sys.argv[1])
check_out_path(target,"",None)
list[0][2]=list[0]
for obj in list:
	if obj[0]=="d":
		obj[2]=list.index(obj[2])
		obj[3]=[[nobj[0],list.index(nobj[1])] for nobj in obj[3]]
sizes=[]
for ind,obj in enumerate(list):
	if obj[0]=="d":#d LEN PAR ENTRIES
		sizes.append(3+len(obj[3])*19)
	elif obj[0]=="f":#f LEN CONTENT
		sizes.append(2+obj[1])
pos=[]
opos=0
for ind,obj in enumerate(list):
	pos.append(opos)
	opos+=sizes[ind]
strings=[]
for ind,obj in enumerate(list):
	if obj[0]=="d":
		arr=["".join([chr(0x100|ord(e[0][(i//6)*6+5-(i%6)])) if (i//6)*6+5-(i%6)<len(e[0]) else chr(0x100) if i<len(e[0]) else chr(0x100) for i in range(18)])+chr(0x5000+pos[e[1]]) for e in obj[3]]
		strings.append("d"+chr(0x5000+obj[1])+chr(0x5000+pos[obj[2]])+"".join(arr))
	else:
		strings.append("f"+chr(0x5000+obj[1])+obj[2])
string="".join(strings)
print(f"set fs \"{string}\"")
