--file demo
print("------file demo------")

--format file system
--file.format()

--write data to a new file
file.open("test.lua","w+")
file.writeline("print('hello world1')");
file.writeline("print('hello world2')");
file.writeline("print('hello world3')");
file.close()

--read back
file.open("test.lua","r")
print(file.readline())
print(file.readline())
print(file.readline())
file.close()

--check file existing or not
if file.open('test.lua')~=nil then
	print("File test.lua exist")
else
	print("File test.lua does not exist")
end

--rename the file
file.rename("test.lua","testNew.lua")

--show the file system information
print("--File system infomation--")
last,used,totol=file.info();
print("last:  "..last.."bytes")
print("used:  "..used.."bytes")
print("totol: "..totol.."bytes")

--list the files
print("--File list--")
for k,v in pairs(file.list()) do 
	print("name:"..k.."  size(bytes):"..v) 
end

--remove the file
--file.remove("test.lua")

--compile the file to lc 
--file.compile("testNew.lua")

--dofile
--dofile('testNew.lua')
--dofile('testNew.lc')


