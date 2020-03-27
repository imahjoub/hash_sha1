*************************************************
### README file: Sha-1 algorithm
### Last changes: 2020-03-27     
*************************************************


### 1. Definition:
******************
SHA-1 or Secure Hash Algorithm 1 is a cryptographic hash function which takes an input and produces a 160-bit (20-byte) hash value.
This hash value is known as a message digest. This message digest is usually then rendered as a hexadecimal number which is 40 digits long.

### 2. Important properties:
***************************

#### Each hash is unique but always repeatable:
The word 'bird' will hash to something that no other word hashes too, but it will always hash to the same thing.

#### The function is "one way":
If you are given the value of what 'bird' hashes too but you didn't know what made it, you would never be able to find out that 'bird' was the original word.


### 3. How To Use:
****************
You could use like this:

1. Create a hash object 

	SHA1 HashObj

2. Call the initialise function 

	HashObj.Initialize();

3. Call the Update function with a message to hash

	HashObj.Update(ExampleMessage, ExampleMessage.size());  

4. Get the hash value

	HashObj.Final();
	
PS : the repository has also a test file, see this also
