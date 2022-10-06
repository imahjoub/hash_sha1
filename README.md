hash_sha1
=====================
<p align="center">
    <a href="https://github.com/imahjoub/hash_sha1" alt="GitHub code size in bytes">
        <img src="https://img.shields.io/github/languages/code-size/imahjoub/hash_sha1" /></a>
    <a href="https://github.com/imahjoub/hash_sha1/blob/main/LICENSE_1_0.txt">
        <img src="https://img.shields.io/badge/license-BSL%201.0-blue.svg" alt="Boost Software License 1.0"></a>
    <a href="https://github.com/imahjoub/hash_sha1" alt="Activity">
        <img src="https://img.shields.io/github/commit-activity/y/imahjoub/hash_sha1" /></a>
</p>

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
