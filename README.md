hash_sha1
=====================

## 1. Definition:
SHA-1 or Secure Hash Algorithm 1 is a cryptographic hash function which takes an input and produces a 160-bit (20-byte) hash value.
This hash value is known as a message digest. This message digest is usually then rendered as a hexadecimal number which is 40 digits long.

## 2. How To Use:

You could use like this:

1. Create a hash object 
	```cpp
	SHA1 HashObj
	```

2. Call the initialise function 
	```cpp
	HashObj.Initialize();
	```

3. Call the Update function with a message to hash
	```cpp
	HashObj.Update(ExampleMessage, ExampleMessage.size());  
	```

4. Get the hash value
	```cpp
	HashObj.Final();	
	```
