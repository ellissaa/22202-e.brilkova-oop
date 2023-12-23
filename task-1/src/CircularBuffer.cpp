#include <stdexcept>
#include <utility>
#include <iterator>
#include <algorithm>
#include "CircularBuffer.h"

CircularBuffer::CircularBuffer() : m_buffer(nullptr), m_capacity(0), m_size(0), m_first_added(0), m_last_added(0) {}
CircularBuffer::~CircularBuffer() {
    delete[] m_buffer;
}

CircularBuffer::CircularBuffer(const CircularBuffer& cb)
        : m_capacity(cb.m_capacity), m_size(cb.m_size),
          m_first_added(cb.m_first_added), m_last_added(cb.m_last_added) {
    m_buffer = new int[m_capacity];
    for (int i = 0; i < m_size; i++) {
        (*this)[i] = cb[i];
    }
}

CircularBuffer::CircularBuffer(int capacity)
        : m_capacity(capacity), m_size(0), m_first_added(0), m_last_added(0) {
    m_buffer = new int[capacity];
}

CircularBuffer::CircularBuffer(int capacity, const int& elem) : m_capacity(capacity), m_size(capacity),
                                                     m_first_added(0), m_last_added(std::max(0, capacity - 1)) {
    m_buffer = new int[capacity];
    for (int i = 0; i < capacity; i++) {
        m_buffer[i] = elem;
    }
}

int& CircularBuffer::operator[](int index) {
    int abs_index = (m_first_added + index) % m_capacity;
    return m_buffer[abs_index];
}
//CircularBuffer<int> cb(10);
// cb[i] = 5;
const int& CircularBuffer::operator[](int i) const {
    int abs_index = (m_first_added + i) % m_capacity;
    return m_buffer[abs_index];
}
// const CircularBuffer<int> cb(10);
// if cb[i] == 5 ...

int& CircularBuffer::at(int index) {
    if (index < 0 || index >= m_size) {
        throw std::out_of_range("Index is out of range.");
    }
    int abs_index = (m_first_added + index) % m_capacity;
    return m_buffer[abs_index];
}
const int& CircularBuffer::at(int index) const {
    if (index < 0 || index >= m_size) {
        throw std::out_of_range("Index is out of range.");
    }
    int abs_index = (m_first_added + index) % m_capacity;
    return m_buffer[abs_index];
}

int& CircularBuffer::front() {
    if (IsEmpty()) {
        throw std::out_of_range("Buffer if empty.");
    }
    return m_buffer[m_first_added];
}
const int& CircularBuffer::front() const {
    if (IsEmpty()) {
        throw std::out_of_range("Buffer if empty.");
    }
    return m_buffer[m_first_added];
}

int& CircularBuffer::back() {
    if (IsEmpty()) {
        throw std::out_of_range("Buffer if empty.");
    }
    return m_buffer[m_last_added];
}
const int& CircularBuffer::back() const {
    if (IsEmpty()) {
        throw std::out_of_range("Buffer if empty.");
    }
    return m_buffer[m_last_added];
}

int* CircularBuffer::linearize() {
    if (IsEmpty()) {
        return nullptr;
    }
    int* buffer_begin = m_buffer;
    int* buffer_end = m_buffer + m_capacity;

    std::rotate(buffer_begin, buffer_begin + m_first_added, buffer_end); //сдвиг влево

    m_first_added = 0;
    m_last_added = m_size - 1;
    return m_buffer;
}

bool CircularBuffer::is_linearized() const {
    return m_first_added == 0;
}

void CircularBuffer::rotate(int new_begin) {
    if (new_begin < 0 || new_begin >= m_size) {
        throw std::out_of_range("Index is out of range.");
    }

    int abs_index = (m_first_added + new_begin) % m_capacity;
    int* buffer_begin = m_buffer;
    int* buffer_end = m_buffer + m_capacity;
    std::rotate(buffer_begin, buffer_begin + abs_index, buffer_end);

    m_first_added = (m_first_added + m_capacity - abs_index) % m_capacity;
    m_last_added = (m_last_added + m_capacity - abs_index) % m_capacity;
}

int* CircularBuffer::buffer() {
    return m_buffer;
}

int CircularBuffer::size() const {
    return m_size;
}
bool CircularBuffer::IsEmpty() const {
    return m_size == 0;
}
bool CircularBuffer::IsFull() const {
    return m_size == m_capacity;
}

int CircularBuffer::reserve() const {
    return m_capacity - m_size;
}

int CircularBuffer::capacity() const {
    return m_capacity;
}

void CircularBuffer::set_capacity(int new_capacity) {
    linearize();
    int* new_buffer = new int[new_capacity];

    for (int i = 0; i < std::min(m_size, new_capacity); i++) {
        new_buffer[i] = m_buffer[i];
    }
    m_capacity = new_capacity;
    m_size = std::min(m_size, new_capacity);
    m_last_added = std::max(0, m_size - 1);

    delete[] m_buffer;
    m_buffer = new_buffer;
}

void CircularBuffer::resize(int new_size, const int& item) {
    set_capacity(new_size);
    int free_cells = reserve();

    for (int i = 0; i < free_cells; i++) {
        push_back(item);
    }
}

CircularBuffer& CircularBuffer::operator=(const CircularBuffer& cb) {
    if (&cb != this) {
        m_capacity = cb.m_capacity;
        m_size = cb.m_size;
        m_first_added = cb.m_first_added;
        m_last_added = cb.m_last_added;

        int* old_buffer = m_buffer;
        m_buffer = new int[m_capacity];
        for (int i = 0; i < m_size; i++) {
            (*this)[i] = cb[i];
        }
        delete[] old_buffer;
    }
    return *this;
}

CircularBuffer CircularBuffer::operator+(const CircularBuffer& cb2) const {
    int size_sum = m_size + cb2.m_size;
    int capacity_sum = size_sum;

    CircularBuffer cb_sum(capacity_sum);
    for (int i = 0; i < m_size; i++) {
        cb_sum.push_back((*this)[i]);
    }
    for (int i = 0; i < cb2.m_size; i++) {
        cb_sum.push_back(cb2[i]);
    }
    return cb_sum;
}

void CircularBuffer::Swap(CircularBuffer& cb) {
    std::swap(m_buffer, cb.m_buffer);
    std::swap(m_capacity, cb.m_capacity);
    std::swap(m_size, cb.m_size);
    std::swap(m_first_added, cb.m_first_added);
    std::swap(m_last_added, cb.m_last_added);
}

void CircularBuffer::push_back(const int& item) {
    if (m_capacity == 0) {
        throw std::out_of_range("Buffer is zero capacity.");
    }

    m_last_added = IsEmpty() ? m_last_added : (m_last_added + 1) % m_capacity;
    m_buffer[m_last_added] = item;

    m_first_added = IsFull() ? (m_first_added + 1) % m_capacity : m_first_added;
    m_size = IsFull() ? m_size : m_size + 1;
}

void CircularBuffer::push_front(const int& item) {
    if (m_capacity == 0) {
        throw std::out_of_range("Buffer is zero capacity.");
    }

    m_first_added = IsEmpty() ? m_first_added : (m_first_added - 1 + m_capacity) % m_capacity;
    m_buffer[m_first_added] = item;

    m_last_added = IsFull() ? (m_last_added - 1 + m_capacity) % m_capacity : m_last_added;
    m_size = IsFull() ? m_size : m_size + 1;
}

int CircularBuffer::pop_front() {
    int& front_item = front();
    m_size--;

    if (IsEmpty()) {
        m_first_added = m_last_added;
    }
    else {
        m_first_added = (m_first_added + 1) % m_capacity;
    }
    return front_item;
}
int CircularBuffer::pop_back() {
    int& back_item = back();
    m_size--;

    if (IsEmpty()) {
        m_last_added = m_first_added;
    }
    else {
        m_last_added = (m_last_added - 1 + m_capacity) % m_capacity;
    }
    return back_item;
}

void CircularBuffer::insert(int pos, const int& item) {
    if (pos < 0 || pos > m_size) {
        throw std::out_of_range("Invalid position to insert.");
    }

    int old_first_added = m_first_added;
    push_back();
    for (int i = m_size - 1; i > pos; i--) {
        (*this)[i] = (*this)[i - 1]; // pos + 1 = pos
    }

    int abs_index = (old_first_added + pos) % m_capacity;
    m_buffer[abs_index] = item;
}

void CircularBuffer::erase(int first, int last) {
    if (first < 0 || first > m_size || last < 0 || last > m_size) {
        throw std::out_of_range("Index is out of range.");
    }
    if (first >= last) {
        return;
    }

    for (int i = last; i < m_size; i++) {
        int shift = i - last;
        (*this)[first + shift] = (*this)[i];
    }

    int num_deleted = last - first;
    m_size -= num_deleted;

    if (IsEmpty()) {
        m_last_added = m_first_added;
    }
    else {
        m_last_added = (m_last_added - num_deleted + m_capacity) % m_capacity;
    }
}

void CircularBuffer::clear() {
    m_size = 0;
    m_last_added = m_first_added;
}

bool operator==(const CircularBuffer& cb1, const CircularBuffer& cb2) {
    if (cb1.capacity() != cb2.capacity() || cb1.size() != cb2.size()) {
        return false;
    }
    for (int i = 0; i < cb1.size(); i++) {
        if (cb1[i] != cb2[i]) {
            return false;
        }
    }
    return true;
}    

bool operator!=(const CircularBuffer& cb1, const CircularBuffer& cb2) {
    return !(cb1 == cb2);
}
