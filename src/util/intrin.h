/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                         * 
 *  Copyright (C) 2020 Aria Seiler                                       * 
 *                                                                         * 
 *  This program is free software: you can redistribute it and/or modify   * 
 *  it under the terms of the GNU General Public License as published by   * 
 *  the Free Software Foundation, either version 3 of the License, or      * 
 *  (at your option) any later version.                                    * 
 *                                                                         * 
 *  This program is distributed in the hope that it will be useful,        * 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         * 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the           * 
 *  GNU General Public License for more details.                           * 
 *                                                                         * 
 *  You should have received a copy of the GNU General Public License      * 
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.  * 
 *                                                                         * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef UTIL_INTRIN_H_
#define UTIL_INTRIN_H_

//TODO: Write alternatives for intrinsics that aren't supported

#if _ARCH_X86 || _ARCH_X64

typedef union __declspec(intrin_type) __declspec(align(16)) __m128i
{
    s08 S08[16];
    s16 S16[ 8];
    s32 S32[ 4];
    s64 S64[ 2];
    
    u08 U08[16];
    u16 U16[ 8];
    u32 U32[ 4];
    u64 U64[ 2];
} i128;

typedef union __declspec(intrin_type) __declspec(align(16)) __m128
{
    s08 S08[16];
    s16 S16[ 8];
    s32 S32[ 4];
    s64 S64[ 2];
    
    u08 U08[16];
    u16 U16[ 8];
    u32 U32[ 4];
    u64 U64[ 2];
    
    r32 R32[ 4];
    r64 R64[ 2];
} r128;

// SSE
#define _MM_HINT_T0 1

void _mm_sfence(void);
void _mm_prefetch(c08 *Address, s32 Hint);
r128 _mm_set_ps1(r32 Value);
#define Asm_WriteFence()                        RETURNS(void) _mm_sfence()
#define Asm_Prefetch(c08_p__Address, s32__Hint) RETURNS(void) _mm_prefetch(c08_p__Address, s32__Hint)
#define R128_SetSingle_32(r32__Value)           RETURNS(r128) _mm_set_ps1(r32__Value)

// SSE2
i128 _mm_and_si128(i128 A, i128 B);
i128 _mm_xor_si128(i128 A, i128 B);
i128 _mm_add_epi64(i128 A, i128 B);
i128 _mm_cmpeq_epi8(i128 A, i128 B);
s32  _mm_movemask_epi8(i128 A);
i128 _mm_loadu_si128(i128 *Src);
void _mm_storeu_si128(i128 *Dest, i128 Src);
i128 _mm_set1_epi32(s32 Value);
i128 _mm_set_epi64x(s64 Value1, s64 Value0);
i128 _mm_setzero_si128(void);
r128 _mm_sqrt_ss(r128 A);
#define I128_AND_128(i128__A, i128__B)                   RETURNS(i128) _mm_and_si128(i128__A, i128__B)
#define I128_XOR_128(i128__A, i128__B)                   RETURNS(i128) _mm_xor_si128(i128__A, i128__B)
#define I128_Add_64(i128__A, i128__B)                    RETURNS(i128) _mm_add_epi64(i128__A, i128__B)
#define I128_CompareEqual_8(i128__A, i128__B)            RETURNS(i128) _mm_cmpeq_epi8(i128__A, i128__B)
#define I128_MoveMask_8(i128__A)                         RETURNS(s32)  _mm_movemask_epi8(i128__A)
#define I128_LoadUnaligned_128(i128_p__Src)              RETURNS(i128) _mm_loadu_si128(i128_p__Src)
#define I128_StoreUnaligned_128(i128_p__Dest, i128__Src) RETURNS(void) _mm_storeu_si128(i128_p__Dest, i128__Src)
#define I128_Set_32(s32__Value)                          RETURNS(i128) _mm_set1_epi32(s32__Value)
#define I128_SetSingle_64(s64__Value1, s64__Value2)      RETURNS(i128) _mm_set_epi64x(s64__Value1, s64__Value2)
#define I128_SetZero_128()                               RETURNS(i128) _mm_setzero_si128()
#define R128_SqrtSingle_32(r128__A)                      RETURNS(r128) _mm_sqrt_ss(r128__A)

// SSE3
i128 _mm_alignr_epi8(i128 A, i128 B, s32 Shift);
i128 _mm_shuffle_epi8(i128 Value, i128 Mask);
#define I128_AlignRight_8(i128__A, i128__B, s32__Shift) RETURNS(i128) _mm_alignr_epi8(i128__A, i128__B, s32__Shift)
#define I128_Shuffle_8(i128__Value, i128__Mask)         RETURNS(i128) _mm_shuffle_epi8(i128__Value, i128__Mask)

// SSE4.1
s32 _mm_extract_epi32(i128 Value, s32 Index);
s64 _mm_extract_epi64(i128 Value, s32 Index);
#define I128_Extract_32(i128__Value, s32__Index) RETURNS(s32) _mm_extract_epi32(i128__Value, s32__Index)
#define I128_Extract_64(i128__Value, s32__Index) RETURNS(s64) _mm_extract_epi64(i128__Value, s32__Index)

// AES
i128 _mm_aesdec_si128(i128 Value, i128 RoundKey);
#define I128_AESDEC_128(i128__Value, i128__RoundKey) RETURNS(i128) _mm_aesdec_si128(i128__Value, i128__RoundKey)

#endif


void __debugbreak(void);
void _ReadWriteBarrier(void);
void _WriteBarrier(void);
// long _InterlockedOr(volatile s32 *Value, s32 Mask);
// long _InterlockedAnd(volatile s32 *Value, s32 Mask);
b08  _interlockedbittestandset(volatile s32 *Base, s32 Offset);
b08  _interlockedbittestandreset(volatile s32 *Base, s32 Offset);
long _InterlockedIncrement(volatile s32 *Addend);
long _InterlockedCompareExchange(volatile s32 *Destination, s32 Exchange, s32 Comparand);
#define Intrin_DebugBreak()                              RETURNS(void) __debugbreak()
#define Intrin_ReadWriteBarrier()                        RETURNS(void) _ReadWriteBarrier()
#define Intrin_WriteBarrier()                            RETURNS(void) _WriteBarrier()
// #define Intrin_InterlockedOR(v_s32_p__Value, s32__Mask)  RETURNS(s32)  _InterlockedOr(v_s32_p__Value, s32__Mask)
// #define Intrin_InterlockedAND(v_s32_p__Value, s32__Mask) RETURNS(s32)  _InterlockedOr(v_s32_p__Value, s32__Mask)
#define Intrin_InterlockedBitTestAndSet(v_s32_p__Base, s32__Offset) \
                                                         RETURNS(b08)  _interlockedbittestandset(v_s32_p__Base, s32__Offset)
#define Intrin_InterlockedBitTestAndReset(v_s32_p__Base, s32__Offset) \
                                                         RETURNS(b08)  _interlockedbittestandreset(v_s32_p__Base, s32__Offset)
#define Intrin_InterlockedIncrement(v_s32_p__Addend)     RETURNS(s32)  _InterlockedIncrement(v_s32_p__Addend)
#define Intrin_InterlockedCompareExchange(v_s32_p__Destination, s32__Exchange, s32__Comparand) \
                                                         RETURNS(s32)  _InterlockedCompareExchange(v_s32_p__Destination, s32__Exchange, s32__Comparand)


#endif