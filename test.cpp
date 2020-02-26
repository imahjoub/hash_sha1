#include <iostream>
#include <vector>

#include<hash_sha1/hash_sha1.h>


int main()
{
  SHA1 Hash;

  using HashType = const std::array<uint32_t, 5U>;

  // Message is the word "xyz" in HEX 
  const std::vector<uint8_t> Message ( { 0x78, 0x79, 0x7A } );

  HashType ExpectedValue =
  {{
     0x66b27417U,
     0xd37e024cU,
     0x46526c2fU,
     0x6d358a75U,
     0x4fc552f3U
  }};

  Hash.Initialize();

  Hash.Update(Message, Message.size());

  HashType Sha1Result   = Hash.Final();

  const bool HashIsTrue = ((Sha1Result == ExpectedValue) ? true :false);

  std::cout << "Hash is: " << std::boolalpha << HashIsTrue << std::endl;

  // Print the hash value
  std::cout << "Hash Value is: " << std::endl;

  for(const auto& i: Sha1Result)
  {
    std::cout << "0x" << std::hex << i << "U," << std::endl;
  }
  
  return 0;
}


