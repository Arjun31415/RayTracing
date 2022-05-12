#include "debug.hpp"
inline namespace Debug
{
template <class T1, class T2>

std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &p)
{
    os << '{' << p.first << ", " << p.second << '}';
    return os;
}

template <typename C, typename T,
          typename std::enable_if<!std::is_same<C, std::string>::value>::type *>
std::ostream &operator<<(std::ostream &os, const C &container)
{
    bool first = true;
    std::stringstream stream;
    stream << '[';
    for (const auto &x : container)
    {
        if (!first)
        {
            stream << ", ";
        }
        first = false;
        stream << x;
    }
    stream << ']';
    return os << stream.str();
}
} // namespace Debug
