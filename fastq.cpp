// CMSC 341 - Spring 2024 - Project 1
#include "fastq.h"

ArrayBuffer::ArrayBuffer(int capacity) : m_capacity(max(0, capacity)), m_count(0), m_start(0), m_end(0), m_next(nullptr){
    // Dynamically allocate memory for the buffer
    if(m_capacity > 0){
        m_buffer = new int[m_capacity];
    }else{
        m_buffer = nullptr;
    }
}

void ArrayBuffer::clear(){
    // Clear the buffer by deleting the dynamically allocated memory
    if(m_buffer != nullptr){
        delete[] m_buffer;
        m_buffer = nullptr;
    }
    m_capacity = 0;
    m_count = 0;
    m_start = 0;
    m_end = 0;
}

ArrayBuffer::~ArrayBuffer(){
    clear();
}

bool ArrayBuffer::empty() const {
    return m_count == 0;
}

void ArrayBuffer::enqueue(int data){
    if(m_count < m_capacity){
        m_buffer[m_end] = data;
        m_end = (m_end + 1) % m_capacity; //reset count
        m_count++;
    }else{
        throw overflow_error("Buffer is full");//error if buffer is full
    }
}

int ArrayBuffer::dequeue(){
    if(!empty()){
        int data = m_buffer[m_start];
        m_start = (m_start + 1) % m_capacity;
        m_count--;
        return data;
    }else{
        throw underflow_error("Buffer is empty");
    }
}

ArrayBuffer::ArrayBuffer(const ArrayBuffer & rhs) : m_capacity(rhs.m_capacity), m_count(rhs.m_count), m_start(rhs.m_start), m_end(rhs.m_end), m_next(
        nullptr){
    if(m_capacity > 0){
        m_buffer = new int[m_capacity];
        for(int i = 0; i < m_capacity; i++){
            m_buffer[i] = rhs.m_buffer[i];
        }
    }else{
        m_buffer = nullptr;
    }
}

const ArrayBuffer & ArrayBuffer::operator=(const ArrayBuffer & rhs){
    if(this != &rhs){
        clear();
        m_capacity = rhs.m_capacity;
        m_count = rhs.m_count;
        m_start = rhs.m_start;
        m_end = rhs.m_end;
        if(m_capacity > 0){
            m_buffer = new int[m_capacity];
            for(int i = 0; i < m_capacity; i++){
                m_buffer[i] = rhs.m_buffer[i];
            }
        }else{
            m_buffer = nullptr;
        }
    }
    return *this;
}

void ArrayBuffer::dump(){
    int start = m_start;
    //int end = m_end;
    int counter = 0;
    cout << "ArrayBuffer size: " << m_capacity << " : ";
    if (!empty()){
        while(counter < m_count){
            cout << m_buffer[start] << "[" << start << "]" << " ";
            start = (start + 1) % m_capacity;
            counter++;
        }
        cout << endl;
    }
    else cout << "ArrayBuffer is empty!" << endl;
}

ListBuffer::ListBuffer(int minBufCapacity){
    m_cursor = nullptr;
    m_listSize =0;
    if (minBufCapacity < 1) {
        m_minBufCapacity = DEFAULT_MIN_CAPACITY;// Set the minimum buffer capacity to default if invalid value is provided
    } else {
        m_minBufCapacity = minBufCapacity;
    }
}

ListBuffer::~ListBuffer(){
    clear();
}
void ListBuffer::clear(){
    if(m_cursor != nullptr){
        ArrayBuffer *temp = m_cursor;
        while(temp->m_next != m_cursor){
            ArrayBuffer *next = temp->m_next;
            delete temp;
            temp = next;
        }
        delete temp;
        m_cursor = nullptr;
        m_listSize = 0;
    }
}

void ListBuffer::enqueue(const int& data) {
    if(m_cursor == nullptr){
        m_cursor = new ArrayBuffer(m_minBufCapacity);
        m_cursor->enqueue(data);
        m_cursor->m_next = m_cursor;
        m_listSize++;
    }else{
        try{
            m_cursor->enqueue(data);
        }catch (overflow_error &e) {
            // If the current buffer is full, create a new buffer with increased capacity
            if (m_cursor->m_capacity * INCREASE_FACTOR <= m_minBufCapacity * MAX_FACTOR) {
                ArrayBuffer* newBuffer = new ArrayBuffer(m_cursor->m_capacity * INCREASE_FACTOR);
                newBuffer->m_next = m_cursor->m_next;
                m_cursor->m_next = newBuffer;
                m_cursor = newBuffer;
                enqueue(data);
                m_listSize++;
            } else {
                // Create a new buffer with the default minimum capacity
                ArrayBuffer* newBuffer = new ArrayBuffer(m_minBufCapacity);
                newBuffer->m_next = m_cursor->m_next;
                m_cursor->m_next = newBuffer;
                m_cursor = newBuffer;
                enqueue(data);
                m_listSize++;
            }
        }
    }
}

int ListBuffer::dequeue() {
    if (m_cursor == nullptr) {
        throw underflow_error("ListBuffer is empty");
    }

    // Dequeue from the oldest buffer, which is the next buffer after m_cursor
    ArrayBuffer* oldestBuffer = m_cursor->m_next;
    int data = oldestBuffer->dequeue();

    // If the oldest buffer becomes empty, remove it from the list
    if (oldestBuffer->empty()) {
        // If there's only one node in the list, and it's empty, do not remove it
        if (m_listSize == 1) {
            // Do nothing
        } else {
            // Remove the oldest buffer from the list
            m_cursor->m_next = oldestBuffer->m_next;
            delete oldestBuffer;
        }
        m_listSize--;
    }
    return data;
}

ListBuffer::ListBuffer(const ListBuffer & rhs) : m_cursor(nullptr), m_listSize(rhs.m_listSize), m_minBufCapacity(rhs.m_minBufCapacity){
    if(rhs.m_cursor != nullptr){
        m_cursor = new ArrayBuffer(*(rhs.m_cursor));
        ArrayBuffer *temp = rhs.m_cursor->m_next;
        ArrayBuffer *temp2 = m_cursor;
        while(temp != rhs.m_cursor){
            temp2->m_next = new ArrayBuffer(*temp);
            temp = temp->m_next;
            temp2 = temp2->m_next;
        }
        temp2->m_next = m_cursor;
    }
}

const ListBuffer & ListBuffer::operator=(const ListBuffer & rhs){
    if(this != &rhs){
        clear();
        m_listSize = rhs.m_listSize;
        m_minBufCapacity = rhs.m_minBufCapacity;
        if(rhs.m_cursor != nullptr){
            m_cursor = new ArrayBuffer(*(rhs.m_cursor));
            ArrayBuffer *temp = rhs.m_cursor->m_next;
            ArrayBuffer *temp2 = m_cursor;
            while(temp != rhs.m_cursor){
                 // Copy each buffer in the list
                temp2->m_next = new ArrayBuffer(*temp);
                temp = temp->m_next;
                temp2 = temp2->m_next;
            }
            temp2->m_next = m_cursor;
        }
    }
    return *this;
}

void ListBuffer::dump(){
    ArrayBuffer* temp = m_cursor->m_next;
    for(int i=0;i<m_listSize;i++){
        temp->dump();
        temp = temp->m_next;
        cout << endl;
    }
    cout << endl;
}