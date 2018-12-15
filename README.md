1. Compression-service

This programm is a small compreesion service. This service consumes data in ASCII format over a TCP socket and return a compressed version of that data.

	1.1. Messaging Format
	All messages that flow over the socket share a common header that consists of three fixed width integer fields in the following order:
	• A 32 bit wide magic value which is always equal to 0x53545259.
	• A 16 bit payload length
	• A 16 bit request code / status code
	The header may or may not be followed by a payload depending on the message type.
	Lastly, all fields are in network byte order.

	1.2. Requests
	The compression service should support the following request types (request code noted in parenthesis):
	• “Ping” (RC: 1)
		– Serves as a means to check that the service is operating normally.
	• “Get Stats” (RC: 2)
		– Retrieves various internal statistics of the service.
	• “Reset Stats” (RC: 3)
		– Resets the internal statistics to their appropriate default values.
	• “Compress” (RC: 4)
		– Requests that some data be compressed using a particular compression scheme.
	All other request codes should be considered invalid.

	1.3 Compression Algorithm
	a => a
	aa => aa
	aaa => 3a
	aaaaabbb => 5a3b
	aaaaabbbbbbaaabb => 5a6b3abb
	abcdefg => abcdefg

2. Install

NAME - name of directory, in which you want to put all extracted files.

$ mkdir NAME && tar -xv --lzma -f compressive.tar.xz -C NAME && cd NAME && make all

3. Usage
Port can not be negative. Also port and requestCode can contain only numbers!

./client hostname port request_code

./server port

4. Server responses
```
0	-	OK
1	-	Unknown ERROR
2	-	Message Too Large
3	-	Wrong Request Code
33	-	Wrong Magic Number
34	-	Message contains numbers
35	-	Message contains capital characters
36	-	Message contains bad characters
```
5. Project developed
The project is written in C99,  developed on Mac OS X 10.13.3, BuildVersion - 17D47.
Apple LLVM version 9.0.0 (clang-900.0.39.2).
Built with clang, with flags -Wall -Wextra -Werror --std=c99


Made by Oleksandr Riabyi.
