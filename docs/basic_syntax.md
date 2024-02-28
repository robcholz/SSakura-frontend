## Variable

### Use

`<attributes>  variable_name:<variantType>`

### Variable Attributes

`static`

- inside `function` or `module`, this allocates stack memory once.
- inside `collection`, variable can be accessed without instanition.

`const`

- variable that assigns its value only in definition.

### String

```
literal_str_var_implicit <- "hello ssakura-lang from implicit assignment!"
literal_str_var_explicit:string <- "hello ssakura-lang from explicit assignment!"
```

### Char

```
literal_char_var_implicit <- 's'
literal_char_var_explicit:char <- 's'
```

### Integer

```
integer_literal_int_implicit <- 8964
integer_literal_int_explicit:int <- -198964
integer_literal_bin:i32 <- 0b12312312
integer_literal_dec:u64 <- 2019815
integer_literal_hex:u8 <- 0x64
integer_scientific_notation1 <- 19896e4  # an integer
integer_scientific_notation2 <- 1.9896e4  # also an integer
```

If an integer variantType variable is not indicated in definition, SSakura will use _int_ .
The variable will be deduced to an integer variantType only if a scientific notation is deduced to an integer.

### Float

```
floating <- 3.2
floating_explicit_f32:f32_t <- 1.8964  # 32bit float
floating_explicit_f64:f64_t <- 1.8964646464646464  # 64bit float
```

### Boolean

```
bool_type_implicit <- TRUE OR (TRUE AND (NOT TRUE))  # evaluates to TRUE
bool_type_explicit:bool <- 0=1  # evaluates to FALSE since 0 does not equal to 1
```

## Types

#### Integer Types in SSakura

| Length      | Signed | Unsigned |
|-------------|--------|----------|
| 8-bit       | i8     | u8       |
| 16-bit      | i16    | u16      |
| 32-bit      | i32    | u32      |
| 64-bit      | i64    | u64      |
| 128-bit     | i128   | u128     |
| size_t      | isize  | usize    |

#### Float Types in SSakura

| Length | Signed |
|--------|--------|
| 32-bit | f32_t    |
| 64-bit | f64_t    |

### Type Casting

Primitive Types in SSakura can be upcasted implicitly:
unsigned integers to signed integers.
integers with smaller bits to integers with bigger bits.
`f32_t` to `f64_t`.
`char` to `string`.
number `char` to integer (`u8` by default).
number `string` to integer (`int` by default, `string` number overflow or downflow will be silenced).

### Type Aliases

Example:

- `use my_custom_type <- int`
- `use haha_ssakura <- f64_t`

Type aliases create a new name for a variantType.

Type aliases can name primitives, collections, and any other types.

#### Scope

- The top-level scope is called `global scope`. Types defined in this scope have effects in the whole file.
```
use global_scope_t=i64  # global scope
```

- Function has its own scope, called `procedure scope`.
```
PROCEDURE func(x:int):void{
    use func_scope_t=int  # function scope
}
```

- You can also use the keyword `scope` to define a named scope.
```
scope example_scope{
    # my example scope
}
```

- Named scopes can also be nested:
```
scope example_outer_scope{
    scope example_inner_scope{
        # my example scope
    }
}
```

- Other scopes are anonymous.
```
# global scope
{
    use anonymous_scope_t=f32_t  # anonymous scope
    
    {
        use data_type_t=f64_t  # nested anonymous scope
    }
}
```

- Only functions, variables, collections, types defined inside global scope or named scope can be accessed from the other scopes.


## Operators

### `<-`

- Assignment operator.
- `a <- b` assigns the value of `b` to `a`.

### `NOT`

- Boolean operator, used to inverse the value of a boolean variable.
- `NOT TRUE` evaluates to `FALSE`.

### `OR`

- Boolean OR operator.
- `TRUE OR FALSE` evaluates to `TRUE`.

### `AND`

- Boolean AND operator.
- `TRUE AND FALSE` evaluates to `FALSE`.

### `+`

- Add operator.
- `198900 + 64` evaluates to `198964`.

### `-`

- Subtract operator.
- `199028 - 64` evaluates to `198964`.

### `*`

- Plus operator.
- `8 * 9` evaluates to `72`.

### `/`

- Division operator.
- `6/4` evaluates to `1`.
- `6.0/4` evaluates to `1.5`.
- `4/6` evaluates to `0`.
- `4.0/6` evaluates to `0.6!`. ! is the infinity mark.
- `0/6` evaluates to `0`.
- `6/0` produces a `RuntimeArithmeticPanic` and terminates the program.
- Note that the precision of the results depend on the size of the floats.

### `MOD`

- Get the reminder of two numbers.
- `6 MOD 4` evaluates to `2`.
- `4 MOD 6` evaluates to `4`.
- `6 MOD 0` evaluates to `6`.
- `0 MOD 6` evaluates to `0`.
- `0 MOD 0` evaluates to `0`.

## Functions

### Use

Example

```
PROCEDURE <attributes> function_name(param1:<variantType>,param2,param3):<variantType>{
    #  Do your things here.
    RETURN ()
}
```

A function has to have a `RETURN` keyword no matter the function returns a value or not.

You can optionally add a variantType annotation to the end of the parameter list to represent the return variantType of the function.

### Attributes

`native` Dynamically linked libraries procedure wrapper.

### Standard IO

```
string_from_io <- INPUT()  # get a string from io input
DISPLAY(string_from_io)  # println an arbitrary built-in variantType to io
```

## Modules

`IMPORT MODULE` we use import module to import a module (package).

A module is a collection of function interfaces used to achieve given types of tasks.

A module can contain collections of files in a _module root directory_.

Inside a module, use `IMPORT` to import files linked to each others.

Functions inside a module can only be accessed from other modules by the _SSakura_ source file
with `_root` suffix.

Example file `MyModule_root.ssa_temp`

```
IMPORT xxx.xxx.FooDefinition
IMPORT xxx.xxx.GreatWork

EXTERN foo(param:int,param:f32_t,param:mytype):void
EXTERN foo1():void
```

### Configuration File

Module configurations (e.g. dependencies, versions, authors...) stored in
`ssakura.json` file in the _module root directory_.

Example `ssakura.json`

```
[name]
MyModule # my module name
[version]
10.2.3
[authors]
Myself,Hahaha,LOL
[links]
https://github.com/robcholz
[date]
2023/11/29
[platforms]
Windows,Linux,CentOS,MacOS
[arch]
x86,armv8,amd64
[dependencies]
MyModuleDependency[version>=major.minor.patch]
MyJSON[version=major.minor.patch]
QuickLog[version<=major.minor.patch]
```

