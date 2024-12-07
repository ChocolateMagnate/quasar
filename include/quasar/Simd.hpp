
#ifndef QUASAR_SIMD_HPP
#define QUASAR_SIMD_HPP


namespace simd {
  // 128 bits as 16 chars (16 * 8 bits = 128 bits)
  typedef char char16_t __attribute__((ext_vector_type(16)));

  // 128 bits as 4 ints (4 * 32 bits = 128 bits)
  typedef int int4_t __attribute__((ext_vector_type(4)));

  // 128 bits as 2 doubles (2 * 64 bits = 128 bits)
  typedef double double2_t __attribute__((ext_vector_type(2)));

}
#endif //QUASAR_SIMD_HPP
