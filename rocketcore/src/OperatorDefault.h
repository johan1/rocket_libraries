#ifndef _OPERATOR_DEFAULT_H_
#define _OPERATOR_DEFAULT_H_

template <typename T>
inline
bool operator!=(T const& t1, T const& t2) {
    return !(operator==(t1, t2));
}

template <typename T>
inline
bool operator>=(T const& t1, T const& t2) {
    return !(operator<(t1, t2));
}

template <typename T>
inline
bool operator>(T const& t1, T const& t2) {
    return (operator<(t2, t1));
}

template <typename T>
inline
bool operator<=(T const& t1, T const& t2) {
    return !(operator>(t2, t1));
}

#endif
