#include <iostream>


template <typename T>
class Vector
{
private:
    size_t _size = 0;
    size_t _capacity = 0;
    T* _elements = nullptr;
    
private:
    void _resize();
    
public:
    Vector(size_t cap);
    ~Vector();
    
    void add(T i);
    void print();
};


template<typename T>
Vector<T>::Vector(size_t cap)
{
    this->_capacity = cap;
    this->_elements = new T[cap];
}

template<typename T>
Vector<T>::~Vector()
{
    delete[] this->_elements;
}

template<typename T>
void Vector<T>::_resize()
{
    _capacity = 2 * _size;
    T* tmp = new T[_capacity];
    
    for (size_t i = 0; i < _size; i++)
    {
        tmp[i] = _elements[i];
    }
    
    delete[] _elements;
    _elements = tmp;
}

template<typename T>
void Vector<T>::add(T i)
{
    if (_capacity == 0)
    {
        _resize();
        // *((unsigned int*)0) = 0xDEAD;
    }
    
    _capacity--;
    _elements[_size] = i;
    _size++;
}

template<typename T>
void Vector<T>::print()
{
    for (size_t i = 0; i < _size; i++)
    {
        std::printf("%d ", _elements[i]);
    }
    
    std::printf("\n");
}


int main()
{
    {
        Vector<int> v(2);
        v.print();
        v.add(1);
        v.add(2);
        v.add(3);
        v.print();
    }
    
    return 0;
}