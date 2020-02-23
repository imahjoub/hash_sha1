#ifndef HAH_SHA1_2019_11_30_H_
  #define HAH_SHA1_2019_11_30_H_

  #include <algorithm>
  #include <array>
  #include <string>
  #include <vector>
  #include <type_traits>

class SHA1
{
public:
  using HashResultType = std::array<std::uint32_t, 5U>;
  using HashBlockType  = std::array<std::uint32_t, 16U>;

  SHA1()  = default;
  ~SHA1() = default;

  void Initialize()
  {
    // SHA1 initialization constants
    Digest[0U] = 0x67452301U;
    Digest[1U] = 0xEFCDAB89U;
    Digest[2U] = 0x98BADCFEU;
    Digest[3U] = 0x10325476U;
    Digest[4U] = 0xC3D2E1F0U;
  }

  void Update(const std::vector<std::uint8_t> Message, const std::size_t MessageSize)
  {
    std::size_t UpdateCounter = 0;

    while(UpdateCounter < MessageSize)
    {
      std::size_t RestOfBytes = MessageSize - UpdateCounter;

      if(RestOfBytes > BlockBytes)
      {
        std::copy(Message.cbegin() +  UpdateCounter,
                  Message.cbegin() + (UpdateCounter + BlockBytes),
                  std::back_inserter(Buffer));

        BufferToBlock(Buffer, TransformContainer);

        transform(TransformContainer);

        UpdateCounter += BlockBytes;

        Buffer.clear();
      }

      else
      {
        std::copy(Message.cbegin() + UpdateCounter,
                  Message.cend(),
                  std::back_inserter(Buffer));

        UpdateCounter  += MessageSize;
      }
    }
  }

  HashResultType Final()
  {
    // Total number of hashed bits
    std::uint64_t HashedBitsNumber = (((TransformCounter * BlockBytes) + Buffer.size()) * 8U);

    // Append original message length
    // This is the last of the 'message padding' steps.
    // You will now add the 64-bit representation of the original message length, in binary, to the end of the current message.
    Buffer.push_back(0x80U);

    std::size_t OriginaBufferlSize = Buffer.size();

    while(Buffer.size() < BlockBytes)
    {
      Buffer.push_back(0x00U);
    }

    HashBlockType LocalBlock;

    BufferToBlock(Buffer, LocalBlock);

    if(OriginaBufferlSize > BlockBytes - 8U)
    {
      transform(LocalBlock);
      std::fill(LocalBlock.begin(), LocalBlock.end() -2U, 0U);
    }

    // Append total_bits, split this std::uint64_t into two std::uint32_t
    LocalBlock[BlockInts - 1U] = static_cast<std::uint32_t>(HashedBitsNumber);
    LocalBlock[BlockInts - 2U] = (HashedBitsNumber >> 32);

    transform(LocalBlock);

    std::array<uint32_t, 5U> HashResult;

    std::copy(Digest.cbegin(), Digest.cend(), HashResult.begin());

    return HashResult;
  }

private:
  // number of 32bit integers per SHA1 block
  static const std::size_t BlockInts  = 16U;
  static const std::size_t BlockBytes = BlockInts * 4U;

  // TBD add some useful comments
  HashBlockType TransformContainer;

  std::array<std::uint32_t, 5U> Digest;
  std::vector<std::uint32_t>    Buffer;

  // Transforms counter
  std::size_t TransformCounter = 0U;

  static void BufferToBlock(const std::vector<std::uint32_t> &Buffer, HashBlockType &block)
  {
    // Convert the std::uint32_t (byte Buffer) to a std::uint32_t array (MSB)
    for(std::size_t i = 0; i < BlockInts; i++)
    {
      block[i] =   ((Buffer[(4*i) + 3] & 0xFFU)
                  | (Buffer[(4*i) + 2] & 0xFFU) <<  8U
                  | (Buffer[(4*i) + 1] & 0xFFU) << 16U
                  | (Buffer[(4*i) + 0] & 0xFFU) << 24U);
    }
  }

  static std::uint32_t Sha1LeftRoate(std::int32_t Value, std::size_t Bits)
  {
    return (((Value) << (Bits)) | (((Value) & 0XFFFFFFFFU) >> (32U - (Bits))));
  }

  static std::uint32_t sha1_blk(std::size_t i, HashBlockType& Block)
  {
    Block[i & 15] = Sha1LeftRoate(Block[(i+13)&15] ^ Block[(i+8)&15] ^ Block[(i+2)&15] ^ Block[i&15], 1U);

    return Block[i & 15];
  }

  void transform(HashBlockType& Block)
  {
    // Copy Digest[] to tmp transform array
    std::array<std::uint32_t, 5U> Tmp;
    std::copy(Digest.cbegin(), Digest.cend(), Tmp.begin());

    // SHA1_R0
    for(std::size_t i = 0U; i < 16U; ++i)
    {
      Function0(Tmp[0U], Tmp[1U], Tmp[2U], Tmp[3U], Tmp[4U], Block[i]);

      std::rotate(Tmp.begin() , Tmp.begin() + 4U, Tmp.end());
    }

    // SHA1_R1
    for(std::size_t i = 16U; i < 20U; ++i)
    {
      Function1(Tmp[0U], Tmp[1U], Tmp[2U], Tmp[3U], Tmp[4U], Block, i);

      if(i<19)
      {
        std::rotate(Tmp.begin() , Tmp.begin() + 4U, Tmp.end());
      }
    }

    // SHA1_R2
    for(std::size_t i = 20U; i < 40U; ++i)
    {
      std::rotate(Tmp.begin() , Tmp.begin() + 4U, Tmp.end());
      Function2(Tmp[0U], Tmp[1U], Tmp[2U], Tmp[3U], Tmp[4U], Block, i);
    }

    // SHA1_R3
    for(std::size_t i = 40U; i < 60U; ++i)
    {
      std::rotate(Tmp.begin() , Tmp.begin() + 4U, Tmp.end());

      Function3(Tmp[0U], Tmp[1U], Tmp[2U], Tmp[3U], Tmp[4U], Block, i);
    }

    // SHA1_R4
    for(std::size_t i = 60U; i <= 79U; ++i)
    {
      std::rotate(Tmp.begin() , Tmp.begin() + 4U, Tmp.end());
      Function4(Tmp[0U], Tmp[1U], Tmp[2U], Tmp[3U], Tmp[4U], Block, i);
    }

    std::rotate(Tmp.begin() , Tmp.begin() + 4U, Tmp.end());


    // Add the working vars back into Digest[]
    Digest[0U] += Tmp[0U];
    Digest[1U] += Tmp[1U];
    Digest[2U] += Tmp[2U];
    Digest[3U] += Tmp[3U];
    Digest[4U] += Tmp[4U];

    // Count the number of transformations
    ++TransformCounter;

  }

  inline void Function0(std::uint32_t& A, std::uint32_t& B, std::uint32_t& C, std::uint32_t& D,std::uint32_t& E, std::uint32_t& block)
  {
    E += (((B & (C ^ D)) ^ D) + block + 0x5A827999U + Sha1LeftRoate(A, 5U));
    B = Sha1LeftRoate(B, 30U);
  }

  inline void Function1(std::uint32_t& A, std::uint32_t& B, std::uint32_t& C, std::uint32_t& D, std::uint32_t& E, HashBlockType& block, std::size_t n)
  {
    E += ((B & (C ^ D)) ^D) + sha1_blk(n, block) + 0x5A827999U + Sha1LeftRoate(A, 5U);
    B = Sha1LeftRoate(B, 30U);
  }

  inline void Function2(std::uint32_t& A, std::uint32_t& B, std::uint32_t& C, std::uint32_t& D, std::uint32_t& E, HashBlockType& block, std::size_t n)
  {
    E += ((B ^ C ^ D) + sha1_blk(n, block) + 0x6ED9EBA1U + Sha1LeftRoate(A, 5U));
    B = Sha1LeftRoate(B, 30U);
  }

  inline void Function3(std::uint32_t& A, std::uint32_t& B, std::uint32_t& C, std::uint32_t& D, std::uint32_t& E, HashBlockType& block, std::size_t n)
  {
    E += ((((B | C)&D) | (B & C)) + sha1_blk(n, block) + 0x8F1BBCDCU + Sha1LeftRoate(A, 5U));
    B = Sha1LeftRoate(B, 30U);

  }

  inline void Function4(std::uint32_t& A, std::uint32_t& B, std::uint32_t& C, std::uint32_t& D, std::uint32_t& E, HashBlockType& block, std::size_t n)
  {
    E += ((B ^ C ^ D)           + sha1_blk(n, block) + 0xCA62C1D6U + Sha1LeftRoate(A, 5U));
    B = Sha1LeftRoate(B, 30U);
  }

};

#endif // HAH_SHA1_2019_11_30_H_
