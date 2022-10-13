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

A simple implementation of SHA-1 in C++ (header-only). This implementation uses little endian byte order.

## Characteristics of the SHA-1 Algorithm

  * SHA-1 is an unkeyed cryptographic hashing function that takes an input of variable length and produces a 120-bit long hash output




## Using the `hash_sha1`

  * The following program shows a test example

  ```cpp
  // Create an object of hash_sha1
  hash_sha1 hash1;

  // Original message
  const std::array<std::uint8_t, 3U> msg1 = {'a', 'b', 'c' };

  // Initialize hash
  hash1.sha1_init();

  // Update the hash with given data
    hash1.sha1_update(msg1.data(), msg1.size());

  // Final hash result
  sha1_output_type hash_result1 = hash1.sha1_final();
  ```

## Testing, continuous integration and quality
Testing and continuous integration runs on GitHub Actions.
Various OS/compiler combinations are used including
GCC/clang/MSVC.

Code coverage uses GCC/gcov/lcov and has a
quality-gate with comparison/baseline-check provided by third-party [Codecov](https://app.codecov.io/gh/imahjoub/hash_sha1).

Additional quality checks are performed on pull-request
and merge to master using modern third party open-source services.
These include
[LGTM](https://lgtm.com/projects/g/imahjoub/hash_sha1/alerts/?mode=list)
and [CodeSonar](https://sonarcloud.io/summary/new_code?id=imahjoub_hash_sha1).


## References
Algorithm specification can be found here:
* http://csrc.nist.gov/publications/fips/fips180-2/fips180-2withchangenotice.pdf
