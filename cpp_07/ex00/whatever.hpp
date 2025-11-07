
template <typename T>
<<<<<<< HEAD
T swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
    return a;
}

// min function template
template <typename T>
T min(T &a, T &b) {
    return (a < b) ? a : b;
}

// max function template
template <typename T>
T max(T &a, T &b) {
    return (a > b) ? a : b;
}

// Optional: equal function
template <typename T>
bool equal( T a,  T b)
{
    return (a == b);
}
=======
T max(T a, T b)
{
    return (a > b ? a : b);
}

template<typename T>
T min(T a, T b)
{
    return (a > b ? b : a);
}

template<typename T>
void swap(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}
>>>>>>> 1f99390516a3159bcdd63437145e8ef7708ac85f
