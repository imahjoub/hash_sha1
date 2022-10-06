hash_sha1
=====================

SHA-1 or Secure Hash Algorithm 1 is a cryptographic hash function which takes an input and produces a 160-bit (20-byte) hash value.

## How To Use:

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
