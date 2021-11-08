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

internal array
Array_Create(heap *Heap,
             u32 InitialLength,
             type Type)
{
    array Array = {0};
    
    Array.Data = Heap_Allocate(Heap, InitialLength * TYPE_SIZE(Type));
    Array.Length = InitialLength;
    Array.Type = Type;
    
    return Array;
}

internal b08
Array_Has(array Array,
          vptr Value)
{
    u32 TypeSize = TYPE_SIZE(Array.Type);
    
    for(u32 Index = 0;
        Index < Array.Length;
        ++Index)
    {
        if(Mem_Cmp(Array.Data + Index * TypeSize, Value, TypeSize) == EQUAL)
        {
            return TRUE;
        }
    }
    
    return FALSE;
}

internal vptr
Array_Get(array Array,
          u32 Index)
{
    u32 TypeSize = TYPE_SIZE(Array.Type);
    
    return Array.Data + (Index * TypeSize);
}

internal void
Array_Set(array *Array,
          vptr Value,
          u32 Index)
{
    u32 TypeSize = TYPE_SIZE(Array->Type);
    u32 Capacity = Heap_GetSize(Array->Data) / TypeSize;
    
    if(Index >= Capacity)
    {
        u32 OldCapacity = Capacity;
        while(Index >= Capacity) Capacity *= 2;
        Heap_Resize(&Array->Data, Capacity * TypeSize);
        Mem_Zero(Array->Data + (OldCapacity * TypeSize), Capacity - OldCapacity);
    }
    
    Mem_Cpy(Array->Data + (Index * TypeSize), Value, TypeSize);
    
    if(Index >= Array->Length) Array->Length = Index + 1;
}


#define meow_u8 u08
#define meow_u64 u64
#define __m128i i128
#define meow_u128 i128
#define meow_umm u64
#define INSTRUCTION_REORDER_BARRIER Intrin_ReadWriteBarrier()
#define MeowU64From(A, I) (I128_Extract_64((A), (I)))
#define MeowU32From(A, I) (I128_Extract_32((A), (I)))
#define MeowHashesAreEqual(A, B) (I128_MoveMask_8(I128_CompareEqual_8((A), (B))) == 0xFFFF)
#define MEOW_PAGESIZE 4096
#define MEOW_PREFETCH 4096
#define MEOW_PREFETCH_LIMIT 0x3ff
#include <tools/meow_hash.h>

internal u64*
HashMap_Hash(vptr Data,
             type Type)
{
    Stack_Push();
    
    u64 *Result = Stack_Allocate(2 * sizeof(u64));
    
    u32 TypeSize;
    switch(Type)
    {
        case TYPE__ARRAY:
        {
            array String = *(array*)Data;
            TypeSize = String.Length * TYPE_SIZE(String.Type);
        } break;
        
        default:
        {
            TypeSize = TYPE_SIZE(Type);
        } break;
    }
    
    #define HASH__BUFFER_MUL 64
    u32 BufferSize = TypeSize * HASH__BUFFER_MUL;
    u08 *Buffer = Stack_Allocate(BufferSize);
    for(u32 Index = 0;
        Index < HASH__BUFFER_MUL;
        ++Index)
    {
        Mem_Cpy(Buffer + TypeSize * Index, Data, TypeSize);
    }
    
    meow_u128 Hash = MeowHash(MeowDefaultSeed, BufferSize, Buffer);
    Result[0] = MeowU64From(Hash, 0);
    Result[1] = MeowU64From(Hash, 1);
    
    Stack_Pop();
    return Result;
}

internal hash_map
HashMap_Create(heap *Heap,
               u32 InitialCount,
               type KeyType,
               type ValueType)
{
    hash_map Result = {0};
    
    Result.KeyType = KeyType;
    Result.ValueType = ValueType;
    Result.MaxEntries = InitialCount;
    // Result.Hashes = Heap_AllocateZeroed(Heap, InitialCount * (TYPE_SIZE(KeyType) + sizeof(u32)));
    // Result.Entries = Heap_AllocateZeroed(Heap, InitialCount * (TYPE_SIZE(ValueType) + sizeof(u32)));
    // Result.Hashes = Array_Create(Heap, 16, KeyType);
    Result.Entries = Array_Create(Heap, InitialCount, ValueType);
    
    return Result;
}

internal b08
HashMap_Has(hash_map Map,
            vptr Key)
{
    u64 *Hash = HashMap_Hash(Key, TYPE_SIZE(Map.KeyType));
    u32 Index = (u32)(*Hash % Map.MaxEntries);
    u08 *Entry = Array_Get(Map.Entries, Index);
    
    return (Entry == NULL);
}

internal vptr
HashMap_Get(hash_map Map,
            vptr Key)
{
    u64 *Hash = HashMap_Hash(Key, TYPE_SIZE(Map.KeyType));
    u32 Index = (u32)(*Hash % Map.MaxEntries);
    u08 *Entry = Array_Get(Map.Entries, Index);
    
    if(Entry == NULL) return NULL;
    
    return Entry;
}

internal void
HashMap_Resize(hash_map *Map)
{
    // Stack_Push();
    
    // // Heap_Print_DEBUG(Heap_GetHeap(Heap_GetHeader(Map->Entries)), NULL);
    
    // Map->MaxEntries *= 2;
    // Heap_Resize(&Map->Entries, Map->MaxEntries * (TYPE_SIZE(Map->ValueType) + sizeof(u32)));
    
    // u32 BufferOffset = 0;
    // u08 *Buffer = Stack_Allocate(Map->EntryCount * (TYPE_SIZE(Map->ValueType) + sizeof(u32)));
    
    // u32 EntryCount = Map->EntryCount;
    // u08 *Entry = Map->Entries;
    // while(EntryCount > 0)
    // {
    //     if(*(u32*)Entry != 0)
    //     {
    //         EntryCount--;
            
    //         Mem_Cpy(Buffer + BufferOffset, Entry, TYPE_SIZE(Map->ValueType) + sizeof(u32));
    //         Mem_Zero(Entry, sizeof(u32) + TYPE_SIZE(Map->ValueType));
    //         BufferOffset += TYPE_SIZE(Map->ValueType) + sizeof(u32);
    //     }
        
    //     Entry += TYPE_SIZE(Map->ValueType) + sizeof(u32);
    // }
    
    // while(BufferOffset > 0)
    // {
    //     BufferOffset -= TYPE_SIZE(Map->ValueType) + sizeof(u32);
    //     u32 *HashIndex = (u32*)(Buffer + BufferOffset);
    //     u08 *Hash = Map->Hashes + (*HashIndex - 1) * HASH_MAP__BYTES_PER_HASH;
    //     u32 EntryIndex = (u32)(*(u64*)Hash % Map->MaxEntries);
    //     u08 *Entry = Map->Entries + EntryIndex * (TYPE_SIZE(Map->ValueType) + sizeof(u32));
        
    //     heap_header *Header = Heap_GetHeader(Map->Entries); UNUSED(Header);
    //     ASSERT(*(u32*)Entry == 0);
        
    //     Mem_Cpy(Entry, HashIndex, sizeof(u32));
    //     Mem_Cpy(Entry + sizeof(u32), Buffer + BufferOffset + sizeof(u32), TYPE_SIZE(Map->ValueType));
    // }
    
    // Stack_Pop();
}

internal void
HashMap_Set(hash_map *Map,
            vptr Key,
            vptr Value)
{
    r32 LoadFactor = (r32)Map->EntryCount / Map->Entries.Length;
    if(LoadFactor > 2.0f)
    {
        u32 OldCapacity = Map->Entries.Length;
        Heap_Resize(&Map->Entries, OldCapacity * 2);
        
        for(u32 ArrayIndex = 0;
            ArrayIndex < OldCapacity;
            ++ArrayIndex)
        {
            
        }
    }
    
    u64 *Hash = HashMap_Hash(Key, Map->KeyType);
    u32 Index = (u32)(*Hash % Map->MaxEntries);
    u08 *Entry = Array_Get(Map->Entries, Index);
    
    // if(*(u32*)Entry != 0)
    // {
    //     HashMap_Resize(Map);
    //     HashMap_Set(Map, Key, Value);
    //     return;
    // }
    
    // if((Map->EntryCount+1) * sizeof(i128) > Heap_GetSize(Map->Hashes))
    // {
    //     Heap_Resize(&Map->Hashes, Map->EntryCount * sizeof(i128) * 2);
    // }
    
    // Mem_Cpy(Map->Hashes + sizeof(i128) * Map->EntryCount, Hash, sizeof(i128));
    // Map->EntryCount++;
    // *(u32*)Entry = Map->EntryCount;
    // Mem_Cpy(Entry + sizeof(u32), Value, TYPE_SIZE(Map->ValueType));
    
    Mem_Cpy(Entry, Value, TYPE_SIZE(Map->ValueType));
}