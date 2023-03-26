# Cata __Development freezed, moved to [cvm](https://github.com/C0DIC/cvm) for now__

Programming language written in C

Remember,
__!!!PROJECT IS UNDER HARD DEVELOPMENT__

## Quick start

``` console
make
./cata examples/01-hello.cata
```

## Hello World

``` elixir
write "Hello, world!"
```

## Variables

``` elixir
var hello: str = "hello, friend!"
var number: int = 45

write hello
write number
```

## Loops (still unstable)

``` elixir
loop 0..10
    write "Looping!"
end
```

## Goals

- Lexer :heavy_check_mark:
- Parser :heavy_minus_sign:
- STD Library :heavy_multiplication_x:

## References

[CataString](https://github.com/C0DIC/catastring) library for "strings" in C
