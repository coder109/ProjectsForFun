# Generator In C

## Introduction

What is a generator? In Python, for example, this is a generator:

```Python
def generator(upper_bound: int):
    return_number = 0
    while return_number < upper_bound:
        yield return_number
        return_number += 1
```

You can generate different value from this generator by:

```Python
g = generator(10)
print(next(g)) # This will return 0
print(next(g)) # This will return 1
```

## How the fuarrk does a generator work?

In my perspective, a generator can be divided into several parts:

1. **Return Value**: the variable that is to be yielded once the `next()` function is called.
2. **Function that Changes the Return Value**: the function that tells us how to modify the **Return Value**.
3. **(Optional)Boundary Statement**: the statement that tells us when to stop the generation, or iteration.

In general, this is an iteration, but *blockable*.

## How to run?

Just (modify or) run:
```Bash
gcc main.c
```

and run the executable file.

## How to use it?

The implementation is based on macro definition, so you can simply just copy and paste them.



When coding, the first step is to create a generator and then initialize the variable in the main function.

```C
GENERATOR(int, x, change_function, check_function); // Create a generator

int main(int argc, char **argv) {
    x = 0; // Initialize
    return 0;
}
```

Then, you can generate the values with `next_fn()`.

## TODO

- [ ] Thread Safe
- [ ] Easier to use

