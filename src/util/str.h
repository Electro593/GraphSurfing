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

#ifndef UTIL_STR_H_
#define UTIL_STR_H_


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//      SECTION: Types
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


//SUBSECTION: C08

typedef c08 *str;

typedef struct str_footer
{
    u32 Length;
    u32 CharSize;
} str_footer;


//SUBSECTION: C16

typedef u16 c16;


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//      SECTION: Functions
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


#if _MODE_DEBUG
    #define UTIL__STR_DEBUG__EXPORTS \
        FUNC(heap_data_DEBUG*, _Str_GetHeapDebugData_DEBUG, void) \
        FUNC(void,             _Str_HeapMark_DEBUG, void) \
        FUNC(void,             _Str_HeapCheck_DEBUG, void) \
        FUNC(void,             _Str_HeapPrint_DEBUG, void) \
    
    #define UTIL__STR_DEBUG__FUNCS \
    
    #define Str_GetHeapDebugData_DEBUG() _Str_GetHeapDebugData_DEBUG()
    #define Str_HeapMark_DEBUG() _Str_HeapMark_DEBUG()
    #define Str_HeapCheck_DEBUG() _Str_HeapCheck_DEBUG()
    #define Str_HeapPrint_DEBUG() _Str_HeapPrint_DEBUG()
#else
    #define UTIL__STR_DEBUG__EXPORTS
    #define UTIL__STR_DEBUG__FUNCS
    
    #define Str_GetHeapDebugData_DEBUG()
    #define Str_HeapMark_DEBUG()
    #define Str_HeapCheck_DEBUG()
    #define Str_HeapPrint_DEBUG()
#endif


#define UTIL__STR__EXPORTS \
    UTIL__STR_DEBUG__EXPORTS \
    \
    FUNC(b08,         Chr_IsBase10, c08 C) \
    FUNC(b08,         Chr_IsPrintable, c08 C) \
    FUNC(u32,         ChrArr_CountPrintableASCII, c08 *Arr) \
    FUNC(void,        Str_SetHeap, heap *Heap) \
    FUNC(str,         Str_Create, str *Dest, c08 *Chars, u32 Length) \
    FUNC(void,        Str_Free, str Str) \
    FUNC(u32,         Str_Len, str Str) \
    FUNC(u32,         Str_FindChar, str Str, c08 Char, s32 Index) \
    FUNC(str,         Str_Sub, str *Dest, str Src, u32 StartIndex, u32 EndIndex) \
    FUNC(str,         Str_Cat, str *StrA, str StrB) \
    FUNC(str,         Str_CatC, str *Str, c08 *ChrArr) \
    FUNC(str,         Str_Ins, str *Str, str Insertion, u32 Index) \
    FUNC(b08,         Str_To_Bool, str Str) \
    FUNC(r32,         Str_To_R32, str Str) \
    FUNC(s32,         Str_To_S32, str Str) \
    FUNC(u32,         Str_To_U32, str Str) \

#define UTIL__STR__FUNCS \
    UTIL__STR_DEBUG__FUNCS \
    \
    FUNC(c08,         Chr_ToLower, c08 C) \
    FUNC(c08,         Chr_ToUpper, c08 C) \
    FUNC(b08,         Chr_IsWhitespace, c08 C) \
    FUNC(b08,         Chr_IsBase2, c08 C) \
    FUNC(b08,         Chr_IsBase8, c08 C) \
    FUNC(b08,         Chr_IsBase16, c08 C) \
    FUNC(u32,         ChrArr_Len, c08 *Arr) \
    FUNC(heap*,       Str_GetHeap, void) \
    FUNC(void,        Str_SetHeap, heap *Heap) \
    FUNC(str,         Str_Resize, str *Str, u32 Length) \
    FUNC(str_footer*, Str_GetFooter, str Str) \
    FUNC(s32,         Str_Cmp, str A, str B) \
    FUNC(str,         Str_Dup, str *Dest, str Str) \
    FUNC(r64,         Str_To_R64, str Str) \
    // FUNC(wstr, Str_To_WStr, wstr Dest, str Src) \


// #define Str_CreateEmpty() Str_Create(NULL, NULL, 0)



#if 0
//SUBSECTION: Types

typedef c16* wstr;

//SUBSECTION: Functions

#define UTIL_FUNCS_STR_C16 \
    FUNC(u32,  WStr_Len, wstr WStr) \
    FUNC(u32,  WStr_Size, wstr WStr) \
    FUNC(u32,  WStr_FindChar, wstr WStr, c16 WChar, s32 Index) \
    \
    FUNC(void, WStr_Cat, wstr WStr, wstr Addend) \
    FUNC(void, WStr_Cpy, wstr Dest, wstr Src) \
    FUNC(void, WStr_Sub, wstr Dest, wstr Src, u32 StartIndex, u32 EndIndex) \
    FUNC(void, WStr_Ins, wstr WStr, wstr Insertion, u32 Index) \
    FUNC(void, WStr_Replace, wstr WStr, wstr Replacement, u32 Index) \
    FUNC(void, WStr_Clr, wstr WStr) \
    \
    FUNC(void, WStr_To_Str, str Dest, wstr Src) \

#endif


#endif