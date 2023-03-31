///////////////////////////////////////////////////////////////////
//                                                               //
//  Copyright Iliass Mahjoub 2019 - 2023.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
//                                                               //
///////////////////////////////////////////////////////////////////

#ifndef HASH_SHA1_2019_11_30_H
  #define HASH_SHA1_2019_11_30_H

  #include <algorithm>
  #include <array>
  #include <cstdint>

  using sha1_type = std::array<std::uint8_t, 20U>;

  class hash_sha1
  {
  public:
    hash_sha1()                 = default;
    hash_sha1(const hash_sha1&) = delete;
    hash_sha1(hash_sha1&&)      = delete;
    virtual ~hash_sha1()        = default; // LCOV_EXCL_LINE

    auto operator=(hash_sha1&&)      -> hash_sha1& = delete;
    auto operator=(const hash_sha1&) -> hash_sha1& = delete;

    auto sha1_init() -> void
    {
      datalen  = 0U;
      bitlen   = 0U;

      k[0U]             = UINT32_C(0x5A827999);
      k[1U]             = UINT32_C(0x6ED9EBA1);
      k[2U]             = UINT32_C(0x8F1BBCDC);
      k[3U]             = UINT32_C(0xCA62C1D6);
      init_hash_val[0U] = UINT32_C(0x67452301);
      init_hash_val[1U] = UINT32_C(0xEFCDAB89);
      init_hash_val[2U] = UINT32_C(0x98BADCFE);
      init_hash_val[3U] = UINT32_C(0x10325476);
      init_hash_val[4U] = UINT32_C(0xC3D2E1F0);
    }

    auto sha1_update(const std::uint8_t* msg, const std::size_t msg_length) -> void
    {
      for(std::size_t i = 0U; i < msg_length; ++i)
      {
        data[datalen] = msg[i];

        datalen++;

        if(datalen == 64U)
        {
          sha1_transform();
          datalen = 0U;
          bitlen += 512U;
        }
      }
    }

    auto sha1_final() -> sha1_type
    {
      std::size_t i = 0U;

      sha1_type hash_result = {0U};

      i = datalen;

      // Pad whatever data is left in the buffer.
      if(datalen < 56U)
      {
        data[i++] = 0x80U;
        std::fill((data.begin() + i), (data.begin() + 56U), 0U);
      }

      else
      {
        data[i++] = 0x80U;
        std::fill((data.begin() + i), data.end(), 0U);
        sha1_transform();
        std::fill_n(data.begin(), 56U, 0U);
      }

      // Append to the padding the total message's length in bits and transform.
      bitlen   += static_cast<std::uint64_t>(datalen * UINT8_C(8));

      data[63U] = static_cast<std::uint8_t>(bitlen >> UINT8_C( 0));
      data[62U] = static_cast<std::uint8_t>(bitlen >> UINT8_C( 8));
      data[61U] = static_cast<std::uint8_t>(bitlen >> UINT8_C(16));
      data[60U] = static_cast<std::uint8_t>(bitlen >> UINT8_C(24));
      data[59U] = static_cast<std::uint8_t>(bitlen >> UINT8_C(32));
      data[58U] = static_cast<std::uint8_t>(bitlen >> UINT8_C(40));
      data[57U] = static_cast<std::uint8_t>(bitlen >> UINT8_C(48));
      data[56U] = static_cast<std::uint8_t>(bitlen >> UINT8_C(56));

      sha1_transform();

      // Since this implementation uses little endian byte ordering and MD uses big endian,
      // reverse all the bytes when copying the final init_hash_val to the output hash.
      for(std::size_t j = 0U; j < 4U; ++j)
      {
        hash_result[j +  0U] = ((init_hash_val[0U] >> (24U - (j * 8U))) & UINT32_C(0x000000FF));
        hash_result[j +  4U] = ((init_hash_val[1U] >> (24U - (j * 8U))) & UINT32_C(0x000000FF));
        hash_result[j +  8U] = ((init_hash_val[2U] >> (24U - (j * 8U))) & UINT32_C(0x000000FF));
        hash_result[j + 12U] = ((init_hash_val[3U] >> (24U - (j * 8U))) & UINT32_C(0x000000FF));
        hash_result[j + 16U] = ((init_hash_val[4U] >> (24U - (j * 8U))) & UINT32_C(0x000000FF));
      }

      return hash_result;
    }

  private:
    std::uint32_t datalen;
    std::uint64_t bitlen;

    std::array<std::uint32_t, 4U> k;
    std::array<std::uint8_t, 64U> data;
    std::array<std::uint32_t, 5U> init_hash_val;

    auto sha1_transform() -> void
    {
      std::uint32_t tmp1 = 0U;
      std::uint32_t tmp2 = 0U;

      std::array<std::uint32_t, 80U> m     = {0U};
      std::array<std::uint32_t,  5U> state = {0U};

      for(std::size_t i = 0U, j = 0U; i < 16U; ++i, j += 4U)
      {
        m[i] = static_cast<std::uint32_t>
        (   static_cast<std::uint32_t>(static_cast<std::uint32_t>(data[j + 0U]) << 24U)
          + static_cast<std::uint32_t>(static_cast<std::uint32_t>(data[j + 1U]) << 16U)
          + static_cast<std::uint32_t>(static_cast<std::uint32_t>(data[j + 2U]) <<  8U)
          + static_cast<std::uint32_t>(static_cast<std::uint32_t>(data[j + 3U]) <<  0U)
        );
      }

      for(std::size_t i = 16U; i < 80U; ++i)
      {
        m[i] = (m[i - 3U] ^ m[i - 8U] ^ m[i - 14U] ^ m[i - 16U]);
        m[i] = (m[i] << 1U) | (m[i] >> 31U);
      }

      std::copy(init_hash_val.begin(), init_hash_val.end(), state.begin());

      for(std::size_t i = 0U; i < 80U; ++i)
      {
        if(            i < 20U) { tmp2 =   ch(state[1U], state[2U], state[3U]) + k[0U]; }
        if(20U <= i && i < 40U) { tmp2 = bxor(state[1U], state[2U], state[3U]) + k[1U]; }
        if(40U <= i && i < 60U) { tmp2 =  maj(state[1U], state[2U], state[3U]) + k[2U]; }
        if(60U <= i && i < 80U) { tmp2 = bxor(state[1U], state[2U], state[3U]) + k[3U]; }

        tmp1      = rotl(state[0U], 5U) + tmp2 + state[4U] + m[i];
        state[4U] = state[3U];
        state[3U] = state[2U];
        state[2U] = rotl(state[1U], 30U);
        state[1U] = state[0U];
        state[0U] = tmp1;
      }

      init_hash_val[0U] += state[0U];
      init_hash_val[1U] += state[1U];
      init_hash_val[2U] += state[2U];
      init_hash_val[3U] += state[3U];
      init_hash_val[4U] += state[4U];
    }

    static inline auto rotl(std::uint32_t a, std::uint32_t b) -> std::uint32_t
    {
      return (static_cast<std::uint32_t>(a << b) | static_cast<std::uint32_t>(a >> (32U - b)));
    }

    static inline auto maj(std::uint32_t x, std::uint32_t y, std::uint32_t z) -> std::uint32_t
    {
      return (static_cast<std::uint32_t>(x & y) ^ static_cast<std::uint32_t>(x & z) ^ static_cast<std::uint32_t>(y & z));
    }

    static inline auto ch(std::uint32_t x, std::uint32_t y, std::uint32_t z) -> std::uint32_t
    {
      return (static_cast<std::uint32_t>(x & y) ^ static_cast<std::uint32_t>(~x & z));
    }

    static inline auto bxor(std::uint32_t x, std::uint32_t y, std::uint32_t z) -> std::uint32_t
    {
      return (static_cast<std::uint32_t>(x) ^ static_cast<std::uint32_t>(y) ^ static_cast<std::uint32_t>(z));
    }
  };

#endif // HASH_SHA1_2019_11_30_H
