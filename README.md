# C++ Stack Machine Interpreter

A custom stack-based virtual machine interpreter written in C++. This project implements arbitrary-precision arithmetic (BigInt) using linked lists and recursive logic, allowing operations on numbers significantly larger than standard data types.

## Key Features
* **BigInt Arithmetic:** Numbers are stored as linked lists of digits, supporting unlimited size.
* **Recursive Architecture:** Stack operations and mathematical calculations rely heavily on recursion.
* **Complex Flow Control:** Supports conditional jumps, loops, and stack manipulation.

## Usage
Run the executable and provide the instruction string via standard input.

Example (Linux/Mac):
echo "'10'20+&" | ./stack_machine

Example (Windows CMD):
echo '10'20+& | stack_machine.exe

## Instruction Set Reference

### Stack Operations
| Cmd | Description |
|:---:|:---|
| ' | Push new node |
| , | Pop top node |
| : | Duplicate top node (deep copy) |
| ; | Swap top two nodes |
| @ | At - Fetch element from depth N |
| $ | Split string/number |
| # | Merge strings/numbers |

### Arithmetic & Logic
| Cmd | Description |
|:---:|:---|
| + | Add two numbers (BigInt support) |
| - | Negate (change sign) |
| < | Less Than comparison |
| = | Equal comparison |
| ! | NOT (logical negation) |
| ^ | Clean/Abs (Remove trailing minus) |

### I/O & Control Flow
| Cmd | Description |
|:---:|:---|
| & | Print entire stack |
| . | Input char from stdin |
| > | Output char to stdout |
| [ | Convert char to ASCII code |
| ] | Convert ASCII code to char |
| ~ | Mark current instruction pointer |
| ? | Jump if condition is met |