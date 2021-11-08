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

#ifndef UTIL_DATA_H_
#define UTIL_DATA_H_

typedef struct link
{
    link *Next;
    // link *Prev;
} link;

typedef struct linked_list
{
    link *First;
    u32 Length;
    
    type Type;
} linked_list;

typedef struct array
{
    u08 *Data;
    u32 Length;
    
    type Type;
} array;

typedef struct hash_map
{
    #define HASH_MAP__BYTES_PER_HASH 16
    // ARRAY(u08) Hashes;
    ARRAY(linked_list) Entries;
    u32 EntryCount;
    
    type KeyType;
    type ValueType;
} hash_map;

#define UTIL__DATA__EXPORTS \
    FUNC(array,    Array_Create,   heap *Heap, u32 InitialLength, type Type) \
    FUNC(b08,      Array_Has,      array Array, vptr Value) \
    FUNC(vptr,     Array_Get,      array Array, u32 Index) \
    FUNC(void,     Array_Append,   array *Array, vptr Value) \
    FUNC(u64*,     HashMap_Hash,   vptr Data, type Type) \
    FUNC(hash_map, HashMap_Create, heap *Heap, u32 InitialCount, type KeyType, type ValueType) \
    FUNC(b08,      HashMap_Has,    hash_map Map, vptr Key) \
    FUNC(vptr,     HashMap_Get,    hash_map Map, vptr Key) \
    FUNC(void,     HashMap_Set,    hash_map *Map, vptr Key, vptr Value) \

#define UTIL__DATA__FUNCS \
    FUNC(void,     HashMap_Resize, hash_map *Map) \

// #define Array_Has(array__Array, Value)         RETURNS(b08)         _Array_Has(array__Array, &Value)
// #define Array_Append(array__Array, Value)      RETURNS(void)        _Array_Append(array__Array, &Value)
// #define HashMap_Has(hash_map__Map, Key)        RETURNS(b08)         _HashMap_Has(hash_map__Map, &Key)
// #define HashMap_Get(hash_map__Map, Key)        RETURNS(TYPE(Value)) _HashMap_Get(hash_map__Map, &Key)
// #define HashMap_Set(hash_map__Map, Key, Value) RETURNS(void)        _HashMap_Set(hash_map__Map,  &Key, &Value)

#endif