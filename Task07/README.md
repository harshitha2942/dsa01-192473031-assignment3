# Task 07 – Complex number and AC impedance calculator

## Requirements and design
Data: real and imaginary components (`double`). Required operations: addition, subtraction, multiplication, division, equality, stream output and magnitude. Constructors: zero/default, real-only, and real-plus-imaginary.

For z1=a+jb and z2=c+jd:
- Addition: (a+c) + j(b+d)
- Subtraction: (a-c) + j(b-d)
- Multiplication: (ac-bd) + j(ad+bc)
- Division: ((ac+bd)/(c²+d²)) + j((bc-ad)/(c²+d²))
- Magnitude: sqrt(a²+b²)

The arithmetic and equality operators are members; stream insertion is a friend non-member because its left operand is `ostream`. Division checks for a zero denominator and throws `std::domain_error`.

## Verification
The program calculates series RLC impedance using:
- ZR = R
- ZL = jωL
- ZC = -j/(ωC)
- Zseries = ZR + ZL + ZC

It also evaluates a parallel example and explicitly tests division by zero. Verify the printed values independently with a calculator and record the hand calculation in your report.

## Alternative and complexity
`std::complex<double>` provides the same basic arithmetic and uses two floating-point components. Both custom and standard operations are O(1) time and O(1) space. The standard type is thoroughly tested and reduces implementation work; division-by-zero policy still needs to be chosen and checked by the application. Floating-point arithmetic is approximate, so exact equality is generally unsuitable for measured engineering values; this implementation uses a small tolerance.

## Remaining limitation
The equality tolerance is fixed and may not suit every scale or measurement precision. A production engineering application should use a scale-aware tolerance and validate physical input ranges.
