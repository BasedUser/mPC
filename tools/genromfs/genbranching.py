for i in range(32):
	print(f"set l{i} processor{i+1}")
print("end\n")

index=0
for i in range(32):
	for j in range(32):
		print(f"set l{j} \"e{index}\"")
		index+=1
	print("end\n")
