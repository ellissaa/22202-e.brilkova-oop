#ifndef CIRC_BUFF_INCLUDED
#define CIRC_BUFF_INCLUDED

#include <stdexcept>
#include <utility>
#include <iterator>
#include <algorithm>

class CircularBuffer {
private:
    int* m_buffer;
    int m_capacity; //размер памяти, выделенной для буфера
    int m_size; //кол-во элементов  в буфере
    int m_first_added; //индекс первого элемента буфера, который добавили
    int m_last_added; //последнего

public:
    // создаем пустой кольцевой буфер
    CircularBuffer();
    //деструктор - чистим всю память
    ~CircularBuffer();

    //создаем копию буфера сb
    CircularBuffer(const CircularBuffer& cb);

    //конструирует буфер заданной ёмкости
    explicit CircularBuffer(int capacity);

    //конструирует буфер заданной ёмкости, целиком заполняет его элементом elem
    CircularBuffer(int capacity, const int& elem);

    //доступ по индексу относительно first_added
    int& operator[](int index);
    const int& operator[](int index) const;

    //доступ по индексу. методы бросают исключение в случае неверного индекса
    int& at(int index);
    const int& at(int index) const;

    int& front(); //ссылка на первый элемент.
    int& back(); //ссылка на последний элемент.
        
    const int& front() const;
    const int& back() const;

    //Линеаризация - сдвинуть кольцевой буфер так, что его первый элемент
    //переместится в начало аллоцированной памяти. Возвращает указатель
    //на первый элемент.
    int* linearize();
    //Проверяет, является ли буфер линеаризованным.
    bool is_linearized() const;

    //Сдвигает буфер так, что по нулевому индексу окажется элемент с индексом new_begin.
    void rotate(int new_begin);

    int* buffer();

    //Количество элементов, хранящихся в буфере.
    int size() const;
    bool IsEmpty() const;
    bool IsFull() const;

    //Количество свободных ячеек в буфере.
    int reserve() const;

    //ёмкость буфера
    int capacity() const;
    //меняет вместимость буфера
    void set_capacity(int new_capacity);
    
    //Изменяет размер буфера. В случае расширения новые элементы заполняются элементом item.
    void resize(int new_size, const int& item = int());

    //Оператор присваивания.
    CircularBuffer& operator=(const CircularBuffer& cb);

    //Оператор суммирования двух буферов.
    CircularBuffer operator+(const CircularBuffer& cb2) const;

    //Обменивает содержимое буфера с буфером cb.
    void Swap(CircularBuffer& cb);

    //Добавляет элемент в конец буфера.
    //Если текущий размер буфера равен его ёмкости, то переписывается
    //первый элемент буфера (т.е., буфер закольцован).
    void push_back(const int& item = int());
    //Добавляет новый элемент перед первым элементом буфера.
    //Аналогично push_back, может переписать последний элемент буфера.
    void push_front(const int& item = int());

    //удаляет первый элемент буфера.
    int pop_front();
    //удаляет последний элемент буфера.
    int pop_back();

    //Вставляет элемент item по индексу pos. Ёмкость буфера остается неизменной.
    void insert(int pos, const int& item = int());
    
    //Удаляет элементы из буфера в интервале [first, last).
    void erase(int first, int last);

    //Очищает буфер.
    void clear();
};

#endif
