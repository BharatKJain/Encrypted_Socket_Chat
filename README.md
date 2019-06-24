# Encrypted_Socket_Chat
It is a simple socket chat with AES enncryption 
**PART 1-Getting Started with QT**

1)Download QT from the link:-
	
https://www.qt.io/download-qt-installer?hsCtaTracking=9f6a2170-a938-42df-a8e2-a9f0b1d6cdce%7C6cb0de4f-9bb5-4778-ab02-bfb62735f3e5

2)Install latest QT software (i.e. QTCreator IDE)

3)For installation references and starter guide with QTCreator visit

https://wiki.qt.io/Qt_for_Beginners

**PART 2-Understanding and Installing Crypto++ library**

1)Download the file for crypto++ from link below 

https://www.cryptopp.com/cryptopp820.zip

2)Compile and Install crypto++ library using terminal

* make
* make test
* sudo make install

3)Install the files of library in QT installation folder 

copy all the installed files in the system to the respective QT folders

4)To link library in QT right click on the project folder and click on 'Add Existing Library'

  To link library in GCC(or G++) use the following code
	g++ -DNDEBUG -g3 -O2 -Wall -Wextra -o AES AES.cpp -l:libcryptopp.a
	
  NOTE: AES is the executable file created and AES.cpp is the source file to be mentioned


**PART 3-The Main Code**

1) The ServerQT and ClientQT folder consist of the basic Socket Client and Server model:

* To Run the code execute the ServerQT file first and click on start connection.
* Then following server execute the client then start the client connection.
* Now,starting from the client side 1st message is sent then server (first recieves the message from client ) sends message, pattern is repeated. 
* Messing up the message pattern will cause the problems.

2)




_/*_
_compiling program using g++ in terminal:     g++ -DNDEBUG -g3 -O2 -Wall -Wextra -o AES AES.cpp -l:libcryptopp.a_
_executing c++ program :     ./AES_
_*/_


Important Links:

https://github.com/weidai11/cryptopp/blob/master/Install.txt