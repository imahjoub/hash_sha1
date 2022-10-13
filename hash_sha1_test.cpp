///////////////////////////////////////////////////////////////////
//                                                               //
//  Copyright Iliass Mahjoub 2019 - 2022.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
//                                                               //
///////////////////////////////////////////////////////////////////

#include <iostream>
#include "sha1.h"

auto hash_sha1_test1() -> bool
{
  const std::array<std::uint8_t, 3U> msg1 = {'a', 'b', 'c' };

  sha1_output_type expected_hash1 =
  {
    0xA9U, 0x99U, 0x3EU, 0x36U, 0x47U, 0x06U,
    0x81U, 0x6AU, 0xBAU, 0x3EU, 0x25U, 0x71U,
    0x78U, 0x50U, 0xC2U, 0x6CU, 0x9CU, 0xD0U,
    0xD8U, 0x9DU
  };

  hash_sha1 hash1;

  hash1.sha1_init();

  hash1.sha1_update(msg1.data(), msg1.size());

  sha1_output_type hash_result1 = hash1.sha1_final();

  return (hash_result1 == expected_hash1);
}

#ifdef HASH_HASH1_PC
auto hash_sha1_test2() -> bool
{
   const uint8_t msg2[] =
   {
     "abcdefghijklmnopqrstuvwxyz"
     "abcdefghijklmnopqrstuvwxyz"
     "abcdefghijklmnopqrstuvwxyz"
     "abcdefghijklmnopqrstuvwxyz"
     "abcdefghijklmnopqrstuvwxyz"
     "abcdefghijklmnopqrstuvwxyz"
     "abcdefghijklmnopqrstuvwxyz"
     "abcdefghijklmnopqrstuvwxyz"
     "abcdefghijklmnopqrstuvwxyz"
     "abcdefghijklmnopqrstuvwxyz"
     "abcdefghijklmnopqrstuvwxyz"
     "abcdefghijklmnopqrstuvwxyz"
   };

  sha1_output_type expected_hash2 =
  {
    0xF4U, 0x0DU, 0x9AU, 0xEBU, 0xFFU, 0x1CU,
    0xF2U, 0x6EU, 0xFAU, 0xF0U, 0xB5U, 0x44U,
    0xDFU, 0xB5U, 0x2EU, 0xF2U, 0x46U, 0x95U,
    0x32U, 0xC6U
  };

  hash_sha1 hash2;

  hash2.sha1_init();

  hash2.sha1_update(msg2, strlen(reinterpret_cast<const char*>(msg2)));

  sha1_output_type hash_result2 = hash2.sha1_final();

  return (hash_result2 == expected_hash2);
}
#endif // HASH_HASH1_PC

extern "C"
{
  volatile std::uint32_t hash_sha1_gdb_result;

  auto hash_sha1_get_gdb_result(void) -> bool;

  auto hash_sha1_get_gdb_result(void) -> bool // LCOV_EXCL_LINE
  {
    hash_sha1_gdb_result =
      static_cast<std::uint32_t>
      (
        hash_sha1_test1() ? UINT32_C(0xF00DCAFE) : UINT32_C(0xFFFFFFFF)
      );

    volatile auto hash_result_is_ok =
      (hash_sha1_gdb_result == UINT32_C(0xF00DCAFE));

    return hash_result_is_ok;
  }
}

auto main() -> int
{
  bool hash_result_is_ok = false;

  #ifdef HASH_HASH1_QEMU
  hash_result_is_ok = hash_sha1_get_gdb_result();
  #else

  hash_result_is_ok = (   hash_sha1_test1()
                       && hash_sha1_test2()
                       && hash_sha1_get_gdb_result());

  std::cout << "hash_result_is_ok: " << std::boolalpha << hash_result_is_ok << std::endl;

  #endif // HASH_HASH1_QEMU

  return hash_result_is_ok ? 0 : -1;
}
