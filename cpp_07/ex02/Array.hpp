template <typename T>

class Array
{
private:
    T* _array;
    unsigned int    _size;

public:

    Array() : _array(NULL), _size(0) {}

    Array(unsigned int size) : _size(size)
    {
        _array = new T[_size];
    }
    ~Array()
    {
        delete[] _array;
    }
    T& operator[](size_t index)
    {
        if (index >= _size)
            throw std::out_of_range("Index out of range");
        return _array[index];
    }

    const T& operator[](size_t index) const
    {
        if (index >= _size)
            throw std::out_of_range("Index out of range");
        return _array[index];
    }
    unsigned int size() const
    {
        return _size;
    }

    Array(const Array& other) : _size(other._size)
    {
        _array = new T[_size];
        for (size_t i = 0; i < _size; ++i)
        {
            _array[i] = other._array[i];
        }
    }
    Array& operator=(const Array& other)
    {
        if (this != &other)
        {
            delete[] _array;
            _size = other._size;
            _array = new T[_size];
            for (size_t i = 0; i < _size; ++i)
            {
                _array[i] = other._array[i];
            }
        }
        return *this;
    }

};

template <typename T>
void printElement(const Array<T>& arr)
{
    for (unsigned int i = 0; i < arr.size(); ++i)
    {
        std::cout << arr[i] << std::endl;
    }
}