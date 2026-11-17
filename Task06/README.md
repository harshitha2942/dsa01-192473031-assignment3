# Task 06 – Rules of operator overloading and Text

`Text` owns a null-terminated dynamic character array and implements constructor, copy constructor, copy assignment and destructor (Rule of Three). Assignment protects self-assignment and allocates the replacement before deleting the old storage. `+` creates a new value; `+=` appends in place.

## Language rules
The operators `::`, `.`, `.*`, `?:` and `sizeof` cannot be overloaded. Overloading cannot change precedence, associativity or arity. At least one operand must have a user-defined or enumeration type. `operator=` must be a non-static member function. A friend is appropriate for symmetric operations or when the left operand is not the class, such as `ostream << Text`.

## Complexity
For lengths n1, n2 and n3, evaluating `a+b+c` copies characters to construct the first concatenation and then copies that intermediate plus c. Character work is O(n1+n2+n3), with an intermediate allocation. A by-value `operator+(Text a, const Text& b)` using `+=` can reuse the parameter's storage but may introduce a parameter copy; move semantics and compiler elision affect actual allocations.

`std::string` is the preferred production choice because it handles capacity, allocation, exceptions and many edge cases. A custom class is justified for learning, specialised storage/encoding, or constrained embedded environments.

## Required experiments
- Add a static copy counter to the copy constructor and report copies for `a+b+c`.
- Run AddressSanitizer and save actual output.
- Compare 100,000 concatenations with `std::string`; avoid repeatedly appending to a new temporary in a way that creates quadratic work unless that is the experiment.
- Test empty strings, long strings and `x = x`.
