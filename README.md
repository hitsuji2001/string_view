### Desciption

An attemp to make a "string" type in C and for C.

### Quick start

This library follow [stb](https://github.com/nothings/stb) style header file. But in short:  

```c
#include <...>
...
#define STRING_VIEW_IMPLEMENTATION
#include "./string_view.h"

#include <...>
...

// Code
```

### General Goals

- [ ] Easy to use
- [ ] Fast
- [ ] Have some basic operations
   - [x] Convert from C string to StringView
   - [ ] Split
      - [x] Split first by a delim
      - [ ] Split by a delim (TODO)
   - [x] Trim
      - [x] Trim left
      - [x] Trim right
      - [x] Trim both side
   - [ ] Replace a "pattern" with another string
      - [ ] Replace first
      - [ ] Replace all
   - [ ] Uppercase all characters
   - [ ] Lowercase all characters
   - [ ] Captitalize a string
   - [ ] Join 2 string together
   - [x] Check if starts with a delim
   - [x] Check if ends with a delim
   - [ ] Comparation
      - [x] Equals (Check if 2 "string" are the same)
      - [ ] Equal ignores case (same as above but ignores cases)
   - [x] Check if all of characters are in alphabet
   - [x] Check if all of characters are numbers
   - [x] Check if all of characters are in alphabet or are numbers
   - [x] Find
      - [ ] Check if string contain a specified "pattern"
      - [ ] Check if string contain a specified "pattern" and then return the position

### Example
