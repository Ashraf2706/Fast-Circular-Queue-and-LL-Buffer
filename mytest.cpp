// Testing file creaated by Ashraf Kawooya
#include "fastq.h"

class Tester{
public:
    // Array Buffer tests
    bool test_array_buffer_normal_case();
    bool test_array_buffer_edge_case();
    bool test_array_buffer_exception_case();
    bool test_array_buffer_copy_constructor();
    bool test_array_buffer_assignment_operator();
    bool test_array_empty_buffer();
    bool test_array_full_buffer();
    bool test_empty_array_assignment_operator();
    
    // String Buffer tests
    bool test_list_buffer_normal_case();
    bool test_list_buffer_edge_case();
    bool test_list_buffer_exception_case();
    bool test_list_buffer_copy_constructor();
    bool test_list_buffer_assignment_operator();
    bool test_list_empty_buffer();
    bool test_empty_list_copy_constructor();
    

};
int main(){
    Tester tester;
    {
    // Array Buffer Tests
    cout << "Testing Array Buffer Normal Case: ";
    if(tester.test_array_buffer_normal_case()){
        cout << "Passed!" << endl;
    }else{
        cout << "Failed!" << endl;
    }

    cout << "Testing Array Buffer Edge Case: ";
    if(tester.test_array_buffer_edge_case()){
        cout << "Passed!" << endl;
    }else{
        cout << "Failed!" << endl;
    }

    cout << "Testing Array Buffer Exception Case: ";
    if(tester.test_array_buffer_exception_case()){
        cout << "Passed!" << endl;
    }else{
        cout << "Failed!" << endl;
    }

    cout << "Testing Array Buffer Copy Constructor: ";
    if(tester.test_array_buffer_copy_constructor()){
        cout << "Passed!" << endl;
    }else{
        cout << "Failed!" << endl;
    }

    cout << "Testing Array Buffer Assignment Operator: ";
    if(tester.test_array_buffer_assignment_operator()){
        cout << "Passed!" << endl;
    }else{
        cout << "Failed!" << endl;
    }

    cout << "Testing Array Buffer Dequeue when Empty: ";
    if(tester.test_array_empty_buffer()){
        cout << "Passed!" << endl;
    }else{
        cout << "Failed!" << endl;
    }

    cout << "Testing Array Buffer Enqueue when Full: ";
    if(tester.test_array_full_buffer()){
        cout << "Passed!" << endl;
    }else{
        cout << "Failed!" << endl;
    }

    cout << "Testing Assignment Operator for Empty Array: ";
    if(tester.test_empty_array_assignment_operator()){
        cout << "Passed!" << endl;
    }else{
        cout << "Failed!" << endl;
    }

    // List Buffer Tests
    cout << "Testing List Buffer Normal Case: ";
    if(tester.test_list_buffer_normal_case()){
        cout << "Passed!" << endl;
    }else{
        cout << "Failed!" << endl;
    }

    cout << "Testing List Buffer Edge Case: ";
    if(tester.test_list_buffer_edge_case()){
        cout << "Passed!" << endl;
    }else {
        cout << "Failed!" << endl;
    }

    cout << "Testing List Buffer Exception Case: ";
    if(tester.test_list_buffer_exception_case()){
        cout << "Passed!" << endl;
    }else {
        cout << "Failed!" << endl;
    }

    cout << "Testing List Buffer Copy Constructor: ";
    if(tester.test_list_buffer_copy_constructor()){
        cout << "Passed!" << endl;
    }else{
        cout << "Failed!" << endl;
    }

    cout << "Testing List Buffer Assignment Operator: ";
    if(tester.test_list_buffer_assignment_operator()){
        cout << "Passed!" << endl;
    }else{
        cout << "Failed!" << endl;
    }

    cout << "Testing List Buffer Dequeue when Empty: ";
    if(tester.test_list_empty_buffer()){
        cout << "Passed!" << endl;
    }else{
        cout << "Failed!" << endl;
    }

    cout << "Testing Copy Constructor for Empty List: ";
    if(tester.test_empty_list_copy_constructor()){
        cout << "Passed!" << endl;
    }else{
        cout << "Failed!" << endl;
    }
    }
    return 0;
}

bool Tester::test_array_buffer_normal_case(){
    // Test normal case for ArrayBuffer
    ArrayBuffer buffer(5);
    for(int i = 0; i < 5; i++){
        buffer.enqueue(i);
    }
    for(int i = 0; i < 5; i++){
        if(buffer.dequeue() != i){
            return false;
        }
    }
    return true;
}
bool Tester::test_array_buffer_edge_case(){
    // Test edge case for ArrayBuffer
    ArrayBuffer buffer(1);
    buffer.enqueue(100);
    return buffer.dequeue() == 100;
}

bool Tester::test_array_buffer_exception_case(){
    // Test exception case for ArrayBuffer
    ArrayBuffer buffer(2);
    try{
        buffer.dequeue();
        return false; //if no error is thrown, return false
    }catch (underflow_error &e){}
    buffer.enqueue(10);
    buffer.enqueue(20);
    try{
        buffer.enqueue(30);
        return false; //test failed if the error is not thrown
    }catch(overflow_error &e){
        return true;
    }
}

bool Tester::test_array_buffer_copy_constructor(){
    // Test copy constructor for ArrayBuffer
    ArrayBuffer original(3);
    original.enqueue(1);
    original.enqueue(2);
    original.enqueue(3);
    ArrayBuffer copy(original);

    if(original.dequeue() == 1 && copy.dequeue() == 1
    && original.dequeue() == 2 && copy.dequeue() == 2
    && original.dequeue() == 3 && copy.dequeue() == 3){
        return true;
    }else{
        return false;
    }
}

bool Tester::test_array_buffer_assignment_operator(){
    // Test assignment operator for ArrayBuffer
    ArrayBuffer original(2);
    original.enqueue(10);
    original.enqueue(20);
    ArrayBuffer copy = original;

    if(original.dequeue() == 10 && copy.dequeue() == 10
    && original.dequeue() == 20 && copy.dequeue() == 20){
        return true;
    }else{
        return false;
    }
}

bool Tester::test_list_buffer_normal_case(){
    // Test normal case for ListBuffer
    ListBuffer buffer(2);
    for(int i = 0; i < 5; i++){
        buffer.enqueue(i);
    }
    for(int i = 0; i < 5; i++){
        if(buffer.dequeue() != i){
            return false;
        }
    }
    return true;
}
bool Tester::test_list_buffer_edge_case(){
    // Test edge cases for ListBuffer
    bool success = true;

    // Test enqueue and dequeue with buffer size of 1
    ListBuffer buffer1(1);
    buffer1.enqueue(20);
    int dequeuedValue1 = buffer1.dequeue();
    if (dequeuedValue1 != 20) {
        success = false;
    }

    return success;
}
bool Tester::test_list_buffer_exception_case(){
     // Test exception case for ListBuffer
    ListBuffer buffer(2);
    try{
        buffer.dequeue();
        return false; //dequeue did not throw an error
    }
    catch(underflow_error &e){
        return true; //error catch from dequeue
    }
}

bool Tester::test_list_buffer_copy_constructor(){
    // Test copy constructor for ListBuffer
    ListBuffer original(2);
    original.enqueue(1);
    original.enqueue(2);

    ListBuffer copy(original);
    if(original.dequeue() == 1 && copy.dequeue() == 1
       && original.dequeue() == 2 && copy.dequeue() == 2){
        return true;
    }else{
        return false;
    }
}
bool Tester::test_list_buffer_assignment_operator(){
    // Test assignment operator for ListBuffer
    ListBuffer original(2);
    original.enqueue(1);
    original.enqueue(2);

    ListBuffer copy = original;
    if(original.dequeue() == 1 && copy.dequeue() == 1
       && original.dequeue() == 2 && copy.dequeue() == 2){
        return true;
    }else{
        return false;
    }
}

bool Tester::test_list_empty_buffer() {
    // Test dequeue from an empty buffer
    ListBuffer emptyBuffer(10);
    try {
        emptyBuffer.dequeue();
        return false; // Dequeue from an empty buffer did not throw an underflow error
    } catch (const underflow_error& e) {}

    return true;
}

bool Tester::test_array_empty_buffer(){
    // Test dequeue from an empty buffer
    ArrayBuffer emptyBuffer(10);
    try {
        emptyBuffer.dequeue();
    } catch (const underflow_error& e) {
        return true;
    }
    return false; // Dequeue from an empty buffer did not throw an underflow error
}

bool Tester::test_array_full_buffer() {
    // Test enqueue into a full buffer for ArrayBuffer
    ArrayBuffer buffer(2);
    buffer.enqueue(1);
    buffer.enqueue(2);
    try {
        buffer.enqueue(3); // Attempt to enqueue into full array
    } catch (overflow_error &e) {
        return true; // Exception thrown as expected
    }
    return false; // Test failed
}

bool Tester::test_empty_list_copy_constructor(){
    // Test copy constructor for empty ListBuffer
    ListBuffer buffer(3);
    ListBuffer buffer2(buffer);

    try{
        buffer2.dequeue();
        return false;
    } catch (underflow_error &e){
        return true;
    }
}

bool Tester::test_empty_array_assignment_operator(){
    // Test assignment operator for empty ArrayBuffer
    ArrayBuffer buffer(3);
    ArrayBuffer buffer2 = buffer;

    try{
        buffer2.dequeue();
        return false;
    } catch (underflow_error &e){
        return true;
    }
}