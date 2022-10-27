hash_sha1
=====================

<p align="center">
    <a href="https://github.com/imahjoub/hash_sha1/actions">
        <img src="https://github.com/imahjoub/hash_sha1/actions/workflows/hash_sha1.yml/badge.svg" alt="Build Status"></a>
    <a href="https://github.com/imahjoub/hash_sha1/issues?q=is%3Aissue+is%3Aopen+sort%3Aupdated-desc">
        <img src="https://custom-icon-badges.herokuapp.com/github/issues-raw/imahjoub/hash_sha1?logo=github" alt="Issues" /></a>
    <a href="https://app.codacy.com/gh/imahjoub/hash_sha1/dashboard">
        <img src="https://app.codacy.com/project/badge/Grade/913aec26f468405ab0ff9a29beb6d400" alt="Codacy Badge" /></a>
    <a href="https://sonarcloud.io/summary/new_code?id=imahjoub_hash_sha1">
        <img src="https://sonarcloud.io/api/project_badges/measure?project=imahjoub_hash_sha1&metric=alert_status" alt="Quality Gate Status"></a>
    <a href="https://codecov.io/gh/imahjoub/hash_sha1">
        <img src="https://codecov.io/gh/imahjoub/hash_sha1/branch/master/graph/badge.svg?token=EE28IC5E6T" alt="code coverage"></a>
    <a href="https://github.com/imahjoub/hash_sha1" alt="GitHub code size in bytes">
        <img src="https://img.shields.io/github/languages/code-size/imahjoub/hash_sha1" /></a>
    <a href="https://github.com/imahjoub/hash_sha1/blob/main/LICENSE_1_0.txt">
        <img src="https://img.shields.io/badge/license-BSL%201.0-blue.svg" alt="Boost Software License 1.0"></a>
    <a href="https://github.com/imahjoub/hash_sha1" alt="Activity">
        <img src="https://img.shields.io/github/commit-activity/y/imahjoub/hash_sha1" /></a>
</p>

A simple implementation of SHA-1 in C++ (header-only). This implementation uses little endian byte order.

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

  // Get hash result
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
[CodeSonar](https://sonarcloud.io/summary/new_code?id=imahjoub_hash_sha1) and [Codacy](https://app.codacy.com/gh/imahjoub/hash_sha1).


## References
Algorithm specification can be found here:
* http://csrc.nist.gov/publications/fips/fips180-2/fips180-2withchangenotice.pdf
