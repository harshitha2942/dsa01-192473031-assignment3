# Task 05 – Increment, comparison and subscript

The compiler distinguishes prefix `operator++()` from postfix `operator++(int)`. The dummy `int` parameter is only a signature marker. Prefix changes the object and returns a reference. Postfix saves and returns the old value, so it makes a copy and is generally less efficient for class types.

The mutable and const `operator[]` overloads allow mutation through a non-const playlist and read-only access through a const playlist. This implementation throws `std::out_of_range` for negative and too-large indices.

## Required prediction (before execution)
For the supplied Counter program:
```text
5 7 7
```
`c++` returns the old value 5 and then stores 6. `++c` changes 6 to 7 and returns the updated value, so `b` is 7 and final `c` is 7. Postfix makes a copy; prefix does not need to.

## Complexity
Increment and indexed access are O(1). Checked indexing performs one bounds comparison (plus branch); `at(i)` also checks and throws, while unchecked indexing has undefined behaviour when out of range. Record measured checked/unchecked access costs over 10,000,000 iterations if you implement both versions.

## Required experiments
- Build and time with both `-O0` and `-O2`; timing is machine/compiler dependent.
- Add an unchecked comparison implementation and measure it separately.
- Test minute and hour rollover, including 59:59 to 1:00:00.
- Save actual output and timing in `outputs/`.
