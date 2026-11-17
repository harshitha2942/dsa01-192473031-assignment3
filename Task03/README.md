# Task 03 – Dynamic constructors and destructors

The dynamic constructor allocates an array of row pointers, then one character array per row. `O` means available and `X` means booked. The destructor releases each row with `delete[]`, then releases the row-pointer array.

## Lifetime order
- Local automatic objects are destroyed in reverse order of construction when their scope ends.
- A block-local object is destroyed at the closing brace of that block.
- A dynamically allocated object is destroyed only when `delete` is applied to its pointer.
- If `delete` is omitted, the object and its allocations leak. Using `delete` instead of `delete[]` for an array is undefined behaviour.

A destructor has no parameters and no return type, and cannot be overloaded because destruction is one well-defined operation for an object.

## Memory layout
```text
seats ──> [row ptr 0] ──> [ O | X | O ]
          [row ptr 1] ──> [ O | O | X ]
```
For R rows, the implementation makes R+1 allocations: one pointer array and R row arrays. Access is O(1). The pointer array uses R * sizeof(char*) extra bytes.

## Complexity and alternative
A contiguous `new char[rows * seats]` layout uses one allocation, with index `r * seatsPerRow + s`; access remains O(1), and it avoids row-pointer overhead. `vector<vector<char>>` is safer and manages memory automatically but generally has one vector allocation per row plus the outer vector storage.

## Required experiments
- Save the normal sanitizer output.
- Temporarily omit `delete evening` and run under AddressSanitizer/LeakSanitizer to capture the leak report.
- Measure payload memory: R*S bytes for the seat characters, plus row pointers and allocator overhead. Record measured estimates for 10x20, 100x200 and 1000x2000.
- Zero rows are handled without allocation.
- The destructor summary is printed at object destruction, not at `show()`.
