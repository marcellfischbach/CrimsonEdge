#pragma once

#include <string>



namespace ce {


#ifdef CE_WIN32

typedef unsigned __int8  uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;

typedef signed __int8  Int8;
typedef signed __int16 Int16;
typedef signed __int32 Int32;
typedef signed __int64 Int64;


typedef unsigned __int8  u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;

typedef signed __int8  i8;
typedef signed __int16 i16;
typedef signed __int32 i32;
typedef signed __int64 i64;


#endif



typedef size_t Size;


}