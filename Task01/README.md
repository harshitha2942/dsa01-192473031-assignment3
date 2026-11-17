# Task 01 – Constructors and constructor overloading

## Design
`Book()` delegates to the full constructor. The title-only constructor also delegates. The full constructor validates copies before the object can be constructed. The members are initialised in declaration order: `title`, `author`, then `copies`, regardless of the order written in an initializer list.

The compiler supplies a default constructor only when no user-declared constructor (including a copy/move constructor) prevents implicit default-constructor generation. Once a constructor is declared, a default constructor is not automatically added. Initializer lists directly initialise members; assignment in the body would first default-construct members and then assign them. This matters for `const` members, references and class types.

`explicit` prevents an unintended implicit conversion such as `Book b = "Dune";`. `Book b("Dune");` remains valid.

## Object states
| Object | Title | Author | Copies |
|---|---|---|---:|
| empty | Untitled | Unknown | 0 |
| donated | The Alchemist | Unknown | 1 |
| complete | Wings of Fire | A. P. J. Abdul Kalam | 5 |

## Complexity
Each constructor performs a fixed number of member initialisations: O(1) time and O(1) auxiliary space (excluding dynamically owned string character storage). A single constructor with default arguments can replace overloads, but named overloads communicate the three creation cases more clearly. Both designs should call one shared validation point; this implementation centralises validation in the full constructor.

## Required experiments to add
1. Remove all user-declared constructors and observe implicit default construction; then declare a parameterised constructor and try `Book books[3];` to record the missing-default-constructor diagnostic.
2. Deliberately declare `int copies; string title;` but initialise in the opposite order. Compile with `-Wreorder` and save the warning.
3. Try a negative count and retain the rejection output.
4. Remove `explicit`, compile `Book b = "Dune";`, then restore `explicit` and record the error.
5. Add your compiler diagnostics and screenshots to `outputs/`.
