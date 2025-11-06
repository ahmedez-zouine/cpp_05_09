
template <typename T>
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
