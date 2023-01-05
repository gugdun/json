# JSON library for C++

A basic JSON parsing and serialization library written in C++. 
It was originally developed only to help me with my labs at university, 
though it is not optimized for speed and has not been tested for production use.

## Compile

Library uses CMake, so just use it to generate build scripts 
and build library using your favourite build system and compiler.

Build and install shared library:
``` bash
$ cmake -B out -G Ninja .
$ cmake --build out
$ sudo cmake --install out
```

## Use

Library is VERY simple and pretty self-explanatory so just read the source code :)

In order to use this library, all you have to do is include `json.h` 
and link shared library (`-ljson`) with your executable.

Use static method `json::parse(std::istream &input)` to parse text from a stream
into `json` object. To serialize `json` into `std::string` use `json::to_string()`.

