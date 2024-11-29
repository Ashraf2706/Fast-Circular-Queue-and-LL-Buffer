
# Fast Circular Queue and Linked List Buffer

## Overview
This project implements two types of buffers in C++:
1. **ArrayBuffer**: A circular queue implemented with a dynamically allocated array.
2. **ListBuffer**: A linked list of `ArrayBuffer` objects, providing dynamic memory management and enhanced flexibility.

The project includes a comprehensive testing framework to ensure the correctness of buffer operations such as enqueue, dequeue, copy constructors, and assignment operators.

## Features
### ArrayBuffer
- Implements a circular queue using a dynamically allocated array.
- Supports:
  - **Enqueue**: Adds elements to the end of the buffer.
  - **Dequeue**: Removes elements from the front of the buffer.
  - **Copy Constructor**: Creates a deep copy of the buffer.
  - **Assignment Operator**: Assigns the contents of one buffer to another.
  - **Clear**: Frees allocated memory and resets buffer attributes.
  - **Dump**: Outputs the contents of the buffer for debugging.

### ListBuffer
- Composed of multiple `ArrayBuffer` objects connected in a circular linked list.
- Supports:
  - **Dynamic Expansion**: Automatically grows by creating new `ArrayBuffer` objects when capacity is exceeded.
  - **Dynamic Shrinking**: Deletes empty buffers to free memory.
  - **Copy Constructor**: Creates a deep copy of the list of buffers.
  - **Assignment Operator**: Assigns the contents of one list to another.
  - **Clear**: Frees allocated memory and resets the list.
  - **Dump**: Outputs the contents of all buffers for debugging.

## Files
### Source Files
- **`fastq.cpp`**:
  - Implements the `ArrayBuffer` and `ListBuffer` classes.
  - Provides the logic for buffer operations, dynamic memory management, and linked list traversal.
- **`fastq.h`**:
  - Declares the `ArrayBuffer` and `ListBuffer` classes.
  - Defines constants and private helper functions.
- **`mytest.cpp`**:
  - Contains the `Tester` class, which provides a suite of tests for `ArrayBuffer` and `ListBuffer`.
  - Includes edge case testing, exception handling, and memory management validation.

## Installation
1. Compile the program:
   ```bash
   g++ -o mytest mytest.cpp fastq.cpp
   ```
2. Run the program:
   ```bash
   ./mytest
   ```

## Usage
### ArrayBuffer Example
- Enqueue and Dequeue Operations:
  ```cpp
  ArrayBuffer buffer(5);
  buffer.enqueue(10);
  buffer.enqueue(20);
  cout << buffer.dequeue(); // Output: 10
  ```
- Copy Constructor:
  ```cpp
  ArrayBuffer buffer(3);
  buffer.enqueue(1);
  buffer.enqueue(2);
  ArrayBuffer copy(buffer);
  ```
- Dump:
  ```cpp
  buffer.dump(); // Outputs the contents of the buffer.
  ```

### ListBuffer Example
- Enqueue and Dequeue Operations:
  ```cpp
  ListBuffer buffer(2);
  buffer.enqueue(10);
  buffer.enqueue(20);
  buffer.enqueue(30); // Creates a new buffer dynamically.
  cout << buffer.dequeue(); // Output: 10
  ```
- Copy Constructor:
  ```cpp
  ListBuffer buffer(3);
  buffer.enqueue(1);
  buffer.enqueue(2);
  ListBuffer copy(buffer);
  ```
- Dump:
  ```cpp
  buffer.dump(); // Outputs the contents of all buffers in the list.
  ```

## Testing
The `Tester` class validates the following:
- **ArrayBuffer Tests**:
  - Normal operations (enqueue, dequeue).
  - Edge cases (buffer size of 1, full and empty conditions).
  - Copy constructor and assignment operator functionality.
  - Exception handling for underflow and overflow errors.
- **ListBuffer Tests**:
  - Dynamic expansion and shrinking of buffers.
  - Correct traversal of linked list structure.
  - Copy constructor and assignment operator functionality.
  - Exception handling for underflow errors.

### Example Output
- ArrayBuffer Tests:
  ```
  Testing Array Buffer Normal Case: Passed!
  Testing Array Buffer Edge Case: Passed!
  Testing Array Buffer Exception Case: Passed!
  ```
- ListBuffer Tests:
  ```
  Testing List Buffer Normal Case: Passed!
  Testing List Buffer Edge Case: Passed!
  Testing List Buffer Exception Case: Passed!
  ```

## Dependencies
- **Standard C++ Libraries**:
  - `<iostream>`
  - `<stdexcept>`

## Authors
- **Ashraf Kawooya**
- **Date**: 12/1/2024

## License
This project is for educational purposes and does not include warranties or guarantees.
