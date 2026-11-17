# Task 02 – Copy constructors: shallow and deep copy

This implementation uses a dynamically allocated array and follows the Rule of Three: destructor, copy constructor and copy-assignment operator. Each copied object owns a separate array. Assignment allocates/copies a replacement before releasing the old array, and handles `p = p`.

## Memory diagrams
**Shallow copy (incorrect):**
```text
p.medicines ──┐
              ├──> [ Paracetamol | ORS ]
q.medicines ──┘
```
Both objects point to the same allocation. Editing through either changes the same array; both destructors attempt `delete[]` on the same pointer, causing a double-free/use-after-free.

**Deep copy (correct):**
```text
p.medicines ─────> [ Paracetamol | ORS ]
q.medicines ─────> [ Paracetamol | ORS ]  (different allocation)
```
The Rule of Three functions go together because raw owning pointers require explicit copying and destruction. The copy constructor is used for direct initialisation from another object, pass-by-value, and return-by-value when copy elision does not remove the copy.

## Expected primary output
The first data line should be:
```text
Ibuprofen ORS | Paracetamol Cetirizine | Paracetamol ORS
```
Additional copy messages and timings follow.

## Complexity
Copying n medicine names takes O(n) time and O(n) additional space. A shallow pointer copy is O(1), but is incorrect for independent ownership. Replacing the raw array with `std::vector<std::string>` allows the Rule of Zero: the compiler-generated copy operations perform a deep element copy safely.

## Required experiments
- Save a sanitizer run of this version using `-fsanitize=address`.
- For the deliberately broken version, remove the copy constructor (and retain a destructor), then copy `p` to `q`. The compiler-generated copy is shallow for the pointer; sanitizer should report an invalid/double free when both objects are destroyed. Save the actual report.
- Compare pass-by-value (copy construction may occur) with `const&` (no copy of the object).
- Repeat copy timing for 10, 1,000 and 100,000 medicines. Run multiple trials and report your measured average, not the single sample printed by the program.
- Note: sanitizer diagnostics vary by compiler/platform; include the actual output from your machine.
