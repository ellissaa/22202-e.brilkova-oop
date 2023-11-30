#ifndef CIRC_BUFF_INCLUDED
#define CIRC_BUFF_INCLUDED

#include <stdexcept>
#include <utility>
#include <iterator>
#include <algorithm>

template <typename ContentT>

class CircularBuffer {
private:
    ContentT* m_buffer;
    int m_capacity; //размер памяти, выделенной для буфера
    int m_size; //кол-во элементов  в буфере
    int m_first_added; //индекс первого элемента буфера, который добавили
    int m_last_added; //последнего

public:
    // создаем пустой кольцевой буфер
    CircularBuffer() : m_buffer(nullptr), m_capacity(0), m_size(0), m_first_added(0), m_last_added(0) {};
    //деструктор - чистим всю память
    ~CircularBuffer() {
        delete[] m_buffer;
    };

    //создаем копию буфера сb
    CircularBuffer(const CircularBuffer& cb) : m_capacity(cb.m_capacity), m_size(cb.m_size),
    m_first_added(cb.m_first_added), m_last_added(cb.m_last_added) {
        m_buffer = new ContentT[m_capacity];
        for (int i = 0; i < m_size; i++) {
            (*this)[i] = cb[i];
        }
    };

    //конструирует буфер заданной ёмкости
    explicit CircularBuffer(int capacity) : m_capacity(capacity), m_size(0), m_first_added(0), m_last_added(0) {
        m_buffer = new ContentT[capacity];
    };

    //конструирует буфер заданной ёмкости, целиком заполняет его элементом elem
    CircularBuffer(int capacity, const ContentT& elem) : m_capacity(capacity), m_size(capacity),
    m_first_added(0), m_last_added(std::max(0, capacity - 1)) {
        m_buffer = new ContentT[capacity];
        for (int i = 0; i < capacity; i++) {
            m_buffer[i] = elem;
        }
    };

    //доступ по индексу относительно first_added
    ContentT& operator[](int index) {
        int abs_index = (m_first_added + index) % m_capacity;
        return m_buffer[abs_index];
    };
    const ContentT& operator[](int i) const {
        int abs_index = (m_first_added + i) % m_capacity;
        return m_buffer[abs_index];
    };

    //доступ по индексу. методы бросают исключение в случае неверного индекса
    ContentT& at(int index) {
        if (index < 0 || index >= m_size) {
            throw std::out_of_range("Index is out of range.");
        }
        int abs_index = (m_first_added + index) % m_capacity;
        return m_buffer[abs_index];
    };
    const ContentT& at(int index) const {
        if (index < 0 || index >= m_size) {
            throw std::out_of_range("Index is out of range.");
        }
        int abs_index = (m_first_added + index) % m_capacity;
        return m_buffer[abs_index];
    };

    ContentT& front() { //ссылка на первый элемент.
        if (IsEmpty()) {
            throw std::out_of_range("Buffer if empty.");
        }
        return m_buffer[m_first_added];
    };
    ContentT& back() { //ссылка на последний элемент.
        if (IsEmpty()) {
            throw std::out_of_range("Buffer if empty.");
        }
        return m_buffer[m_last_added];
    };
    const ContentT& front() const {
        if (IsEmpty()) {
            throw std::out_of_range("Buffer if empty.");
        }
        return m_buffer[m_first_added];
    };
    const ContentT& back() const {
        if (IsEmpty()) {
            throw std::out_of_range("Buffer if empty.");
        }
        return m_buffer[m_last_added];
    };

    //Линеаризация - сдвинуть кольцевой буфер так, что его первый элемент
    //переместится в начало аллоцированной памяти. Возвращает указатель
    //на первый элемент.
    ContentT* linearize() {
        if (IsEmpty()) {
            return nullptr;
        }
        ContentT* buffer_begin = m_buffer;
        ContentT* buffer_end = m_buffer + m_capacity;

        std::rotate(buffer_begin, buffer_begin + m_first_added, buffer_end); //сдвиг влево

        m_first_added = 0;
        m_last_added = m_size - 1;
        return m_buffer;
    };
    //Проверяет, является ли буфер линеаризованным.
    bool is_linearized() const {
        return m_first_added == 0;
    };

    //Сдвигает буфер так, что по нулевому индексу окажется элемент
    //с индексом new_begin.
    void rotate(int new_begin) {
        if (new_begin < 0 || new_begin >= m_size) {
            throw std::out_of_range("Index is out of range.");
        }

        int abs_index = (m_first_added + new_begin) % m_capacity;
        ContentT* buffer_begin = m_buffer;
        ContentT* buffer_end = m_buffer + m_capacity;
        std::rotate(buffer_begin, buffer_begin + abs_index, buffer_end);

        m_first_added = (m_first_added + m_capacity - abs_index) % m_capacity;
        m_last_added = (m_last_added + m_capacity - abs_index) % m_capacity;
    };

    ContentT* buffer() {
        return m_buffer;
    }

    //Количество элементов, хранящихся в буфере.
    int size() const {
        return m_size;
    };
    bool IsEmpty() const {
        return m_size == 0;
    };
    bool IsFull() const {
        return m_size == m_capacity;
    };

    //Количество свободных ячеек в буфере.
    int reserve() const {
        return m_capacity - m_size;
    };

    //ёмкость буфера
    int capacity() const {
        return m_capacity;
    };
    //меняет вместимость буфера
    void set_capacity(int new_capacity) {
        linearize();
        ContentT* new_buffer = new ContentT[new_capacity];

        for (int i = 0; i < std::min(m_size, new_capacity); i++) {
            new_buffer[i] = m_buffer[i];
        }
        m_capacity = new_capacity;
        m_size = std::min(m_size, new_capacity);
        m_last_added = std::max(0, m_size - 1);

        delete[] m_buffer;
        m_buffer = new_buffer;
    };
    //Изменяет размер буфера.
    //В случае расширения, новые элементы заполняются элементом item.
    void resize(int new_size, const ContentT& item = ContentT()) {
        set_capacity(new_size);
        int free_cells = reserve();

        for (int i = 0; i < free_cells; i++) {
            push_back(item);
        }
    };

    //Оператор присваивания.
    CircularBuffer& operator=(const CircularBuffer& cb) {
        if (&cb != this) {
            m_capacity = cb.m_capacity;
            m_size = cb.m_size;
            m_first_added = cb.m_first_added;
            m_last_added = cb.m_last_added;

            ContentT* old_buffer = m_buffer;
            m_buffer = new ContentT[m_capacity];
            for (int i = 0; i < m_size; i++) {
                (*this)[i] = cb[i];
            }
            delete[] old_buffer;
        }
        return *this;
    };

    //Обменивает содержимое буфера с буфером cb.
    void Swap(CircularBuffer& cb) {
        std::swap(m_buffer, cb.m_buffer);
        std::swap(m_capacity, cb.m_capacity);
        std::swap(m_size, cb.m_size);
        std::swap(m_first_added, cb.m_first_added);
        std::swap(m_last_added, cb.m_last_added);
    };

    //Добавляет элемент в конец буфера.
    //Если текущий размер буфера равен его ёмкости, то переписывается
    //первый элемент буфера (т.е., буфер закольцован).
    void push_back(const ContentT& item = ContentT()) {
        if (m_capacity == 0) {
            throw std::out_of_range("Buffer is zero capacity.");
        }

        m_last_added = IsEmpty() ? m_last_added : (m_last_added + 1) % m_capacity;
        m_buffer[m_last_added] = item;

        m_first_added = IsFull() ? (m_first_added + 1) % m_capacity : m_first_added;
        m_size = IsFull() ? m_size : m_size + 1;
    };
    //Добавляет новый элемент перед первым элементом буфера.
    //Аналогично push_back, может переписать последний элемент буфера.
    void push_front(const ContentT& item = ContentT()) { //разобрать
        if (m_capacity == 0) {
            throw std::out_of_range("Buffer is zero capacity.");
        }

        m_first_added = IsEmpty() ? m_first_added : (m_first_added - 1 + m_capacity) % m_capacity;
        m_buffer[m_first_added] = item;

        m_last_added = IsFull() ? (m_last_added - 1 + m_capacity) % m_capacity : m_last_added;
        m_size = IsFull() ? m_size : m_size + 1;
    };

    //удаляет первый элемент буфера.
    ContentT pop_front() {
        ContentT& front_item = front();
        m_size--;

        if (IsEmpty()) {
            m_first_added = m_last_added;
        }
        else {
            m_first_added = (m_first_added + 1) % m_capacity;
        }
        return front_item;
    };
    //удаляет последний элемент буфера.
    ContentT pop_back() {
        ContentT& back_item = back();
        m_size--;

        if (IsEmpty()) {
            m_last_added = m_first_added;
        }
        else {
            m_last_added = (m_last_added - 1 + m_capacity) % m_capacity;
        }
        return back_item;
    };

    //Вставляет элемент item по индексу pos. Ёмкость буфера остается неизменной.
    void insert(int pos, const ContentT& item = ContentT()) {
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
    };
    //Удаляет элементы из буфера в интервале [first, last).
    void erase(int first, int last) {
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
    };

    //Очищает буфер.
    void clear() {
        m_size = 0;
        m_last_added = m_first_added;
    };
};

template <typename ContentT>

bool operator==(const CircularBuffer<ContentT>& cb1, const CircularBuffer<ContentT>& cb2) {
    if (cb1.capacity() != cb2.capacity() || cb1.size() != cb2.size()) {
        return false;
    }

    for (int i = 0; i < cb1.size(); i++) {
        if (cb1[i] != cb2[i]) {
            return false;
        }
    }
    return true;
};

template <typename ContentT>

bool operator!=(const CircularBuffer<ContentT>& cb1, const CircularBuffer<ContentT>& cb2) {
    return !(cb1 == cb2);
};

#endif
