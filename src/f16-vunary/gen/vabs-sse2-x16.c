// Auto-generated file. Do not edit!
//   Template: src/f16-vunary/sse2.c.in
//   Generator: tools/xngen
//
// Copyright 2022 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <emmintrin.h>

#include <xnnpack/common.h>
#include <xnnpack/math.h>
#include <xnnpack/vunary.h>


void xnn_f16_vabs_ukernel__sse2_x16(
    size_t n,
    const void* input,
    void* output,
    const union xnn_f16_abs_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(n != 0);
  assert(n % sizeof(uint16_t) == 0);
  assert(input != NULL);
  assert(output != NULL);

  const uint16_t* i = (const uint16_t*) input;
  uint16_t* o = (uint16_t*) output;
  const __m128i vnonsign_mask = _mm_load_si128((const __m128i*) params->sse.nonsign_mask);
  for (; n >= 16 * sizeof(uint16_t); n -= 16 * sizeof(uint16_t)) {
    __m128i vacc0 = _mm_loadu_si128((const __m128i*) i);
    __m128i vacc1 = _mm_loadu_si128((const __m128i*) (i + 8));
    i += 16;

    vacc0 = _mm_and_si128(vacc0, vnonsign_mask);
    vacc1 = _mm_and_si128(vacc1, vnonsign_mask);

    _mm_storeu_si128((__m128i*) o, vacc0);
    _mm_storeu_si128((__m128i*) (o + 8), vacc1);
    o += 16;
  }
  for (; n >= 8 * sizeof(uint16_t); n -= 8 * sizeof(uint16_t)) {
    __m128i vacc = _mm_loadu_si128((const __m128i*) i);
    i += 8;
    vacc = _mm_and_si128(vacc, vnonsign_mask);
    _mm_storeu_si128((__m128i*) o, vacc);
    o += 8;
  }
  if XNN_UNLIKELY(n != 0) {
    __m128i vacc = _mm_loadu_si128((const __m128i*) i);
    vacc = _mm_and_si128(vacc, vnonsign_mask);
    if (n & (4 * sizeof(uint16_t))) {
      _mm_storel_epi64((__m128i*) o, vacc);
      o += 4;
      vacc = _mm_unpackhi_epi64(vacc, vacc);
    }
    if (n & (2 * sizeof(uint16_t))) {
      *((uint32_t*) o) = (uint32_t) _mm_cvtsi128_si32(vacc);
      o += 2;
      vacc = _mm_srli_epi64(vacc, 32);
    }
    if (n & (1 * sizeof(uint16_t))) {
      *o = (uint16_t) _mm_extract_epi16(vacc, 0);
    }
  }
}
