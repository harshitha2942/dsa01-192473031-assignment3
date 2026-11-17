# Task 04 – Arithmetic and stream operators

Money is stored as an integer number of paise, avoiding binary floating-point rounding in ordinary currency arithmetic. `+` returns a new value; `+=` mutates the left operand and returns `Money&` so chained compound assignments work. `<<` is a non-member because the left operand is an `ostream`, not a `Money`. `+` as a member corresponds to `a.operator+(b)`.

The arithmetic/comparison operators are members because they inspect the left-hand Money object. Stream operators are friends so they can access the private paise field. `>>` reads rupees and paise as two integers in this teaching implementation.

## Engineering decision
Multiplication of one Money amount by another Money amount is generally meaningless for billing. Multiplication by a scalar (quantity, tax factor) and division by a scalar can be useful, with explicit rounding rules. Negative values may be useful for credits/refunds; this program prints them with a leading minus sign.

## Complexity
Each operation is O(1) time and O(1) extra space. A friend non-member `operator+` can support `100 + m` if an implicit converting constructor is allowed; a member `m + 100` can use conversion of the right operand. The `Money` constructor here is intentionally not explicit, but integer-to-Money conversion is not a conversion from a single integer amount in the strict semantic sense unless interpreted as rupees.

## Required experiments
- Verify Rs 0.75 + Rs 0.50 = Rs 1.25.
- Compare integer-paise calculations with a double-based loop of 1,000,000 additions; report the actual difference and measured time.
- Compare the readability of `a + b` with named calls such as `add(a,b)`.
- Add a validated input format if your instructor expects keyboard input.
