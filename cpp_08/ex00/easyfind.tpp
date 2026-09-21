
#include <algorithm>

template<typename T>
int easyfind(T &container, int value_to_find)
{
    typename T::iterator res_it;
    res_it = std::find(container.begin(), container.end(), value_to_find);

    if(res_it != container.end())
        return std::distance(container.begin(), res_it);
    else
        return -1;
}