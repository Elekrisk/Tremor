# Tremor Specification

## Data types

There are multiple data types in Tremor.

### Integers

Integers can be both signed and unsigned, and with a width of 8, 16, 32 or 64 bits.
The keywords for these integers is `iX` for signed integers and `uX` for unsigned
integers, where `X` is the width. 

|| 8 | 16 | 32 | 64
|---
| **Signed** | i8 | i16 | i32 | i64
| **Unsigned** | u8 | u16 | u32 | u64

### Integer-like

There are several datatypes that are stored as integers, but that is interpreted
differently by the compiler. These are:

#### Chars

There are two datatypes for representing characters: `char` and `wchar`.

* `char` is an 8-bit wide datatype, used for storing ASCII characters.
* `wchar` is a 32-bit wide datatype, used for storing UTF32-encoded Unicode
  characters.

#### Bool

A `bool` is used to store a boolean value, i.e. true or false. Internally, it is
stored as an 8-bit integer, however can only assume the values `0` and `1`.

### Floating-point

There are two floating point datatypes: `f32` and `f64`. As the names suggest,
one is 32 bits wide and the other is 64 bits wide. These datatypes follow the
`binary32` and `binary64` *IEEE 754* formats.

### Pointer

A pointer holds a memory address to a value of a specific data type. A pointer
type is written like this: `<type>*`, where `<type>` is a valid data type.
As a pointer is a valid data type, a pointer can point to another pointer.

The value that the pointer is pointing to can be accessed via the dereference
operator, the unary `*`, like so: `*variable`.

The address to a variable can be accessed via the unary `&` operator, in a similar
way that the dereference operates.