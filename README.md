-------------------------------------------------
- README file: Sha-1 algorithm                  -
- Last changes: 2020-03-03                      -
-------------------------------------------------

1. Definition:
--------------
SHA-1 or Secure Hash Algorithm 1 is a cryptographic hash function which takes an input and produces a 160-bit (20-byte) hash value.
This hash value is known as a message digest. This message digest is usually then rendered as a hexadecimal number which is 40 digits long.

2. Important properties:
------------------------
#Each hash is unique but always repeatable:
The word 'bird' will hash to something that no other word hashes too, but it will always hash to the same thing.

#The function is "one way":
If you are given the value of what 'bird' hashes too but you didn't know what made it, you would never be able to find out that 'bird' was the original word.

3. How hash algorithms actually work:
------------------------------------

Step 0: Initialize some variables

 The first step is to initialize five random strings of hex characters that will serve as part of the hash function (shown in hex):

H0 67DE2A01

H1
H2
H3
H4
?==BB03E28C
=011EF1DC
=9293E9E2
=CDEF23A9.
?	


-------------------------------------------------
- README file: Sha-1 algorithm                  -
- Last changes: 2020-03-03                      -
-------------------------------------------------

1. Definition:
--------------
SHA-1 or Secure Hash Algorithm 1 is a cryptographic hash function which takes an input and produces a 160-bit (20-byte) hash value.
This hash value is known as a message digest. This message digest is usually then rendered as a hexadecimal number which is 40 digits long.

2. Important properties:
------------------------
#Each hash is unique but always repeatable:
The word 'bird' will hash to something that no other word hashes too, but it will always hash to the same thing.

#The function is "one way":
If you are given the value of what 'bird' hashes too but you didn't know what made it, you would never be able to find out that 'bird' was the original word.

3. How hash algorithms actually work:
------------------------------------

Step 0: Initialize some variables

 The first step is to initialize five random strings of hex characters that will serve as part of the hash function (shown in hex):

H0 67DE2A01

H1
H2
H3
H4
?==BB03E28C
=011EF1DC
=9293E9E2
=CDEF23A9.
?	


-------------------------------------------------
- README file: Sha-1 algorithm                  -
- Last changes: 2020-03-03                      -
-------------------------------------------------

1. Definition:
--------------
SHA-1 or Secure Hash Algorithm 1 is a cryptographic hash function which takes an input and produces a 160-bit (20-byte) hash value.
This hash value is known as a message digest. This message digest is usually then rendered as a hexadecimal number which is 40 digits long.

2. Important properties:
------------------------
#Each hash is unique but always repeatable:
The word 'bird' will hash to something that no other word hashes too, but it will always hash to the same thing.

#The function is "one way":
If you are given the value of what 'bird' hashes too but you didn't know what made it, you would never be able to find out that 'bird' was the original word.

3. How hash algorithms actually work:
------------------------------------

Step 0: Initialize some variables

 The first step is to initialize five random strings of hex characters that will serve as part of the hash function (shown in hex):
         H0=67DE2A01
         H1=BB03E28C
         H2=011EF1DC
         H3=9293E9E2
         H4=CDEF23A9

Step 1: Pick a message of string  then padded by appending a 1, followed by enough 0s until the message is 448 bits.
The length of the message represented by 64 bits is then added to the end, producing a message that is 512 bits long:

                                                                           (length of string)
                                448                                               32
       --------------------------------------------------------                 -------
       0110 0010  0110 1001  0111 0010  0110 0100   1   00..00              00..10000
       ---------  ---------  ---------  ---------      ---------            ------------
           b          i          r          d           415bits               64bits
