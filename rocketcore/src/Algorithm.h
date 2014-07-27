#ifndef _ROCKET_ALGORITHM_H_
#define _ROCKET_ALGORITHM_H_

#include <algorithm>
#include <functional>
#include <iterator>

namespace rocket {

// Functors

// Predicate functor that checks if pointer is managed by pointer wrapper.
template <typename T>
struct managed_by_sp_impl {
	managed_by_sp_impl(T const* ptr) : ptr(ptr) {}

	template <typename SP>
	bool operator()(SP const& sp) const {
		return sp.get() == ptr;
	}

	T const* ptr;
};

template <typename T>
managed_by_sp_impl<T> managed_by_sp(T const* ptr) {
	return managed_by_sp_impl<T>(ptr);
}

// Predicate functor that checks if container contains element
template <typename Container>
struct contains_element_impl {
	contains_element_impl(Container const& container) : container(container) {}

	template <typename T>
	bool operator()(T const& t) const {
		return std::find(container.begin(), container.end(), t) != container.end();
	}

	Container const& container;
};

template <typename Container>
contains_element_impl<Container> contains_element(Container const& container) {
	return contains_element_impl<Container>(container);
}

// Vector utilities
template <typename Vector, typename Value>
void erase(Vector &vec, Value const& value) {
	vec.erase(std::remove(vec.begin(), vec.end(), value), vec.end());
}

template <typename Vector, typename Predicate>
void erase_if(Vector &vec, Predicate p) {
	vec.erase(std::remove_if(vec.begin(), vec.end(), p), vec.end());
}

template <typename InputIt, typename Value>
InputIt find_and_apply(InputIt first, InputIt last, Value const& v,
		std::function<void(typename std::iterator_traits<InputIt>::value_type &)> const& procedure) {
	auto it = std::find_if(first, last, v);
	if (it != last) {
		procedure(*it);
	}
	return it;
}

/*
 * Map utilitise
 */

/*!
 * Applies procedure on mapped value if found.
 * Returns whether or not we applied procedure. E.g. if map has entry with key.
 */
template <typename Map, typename Key>
bool find_and_apply(Map& map, Key const& key,
		std::function<void(typename Map::mapped_type&)> const& procedure) {
	auto it = map.find(key);
	if (it != map.end()) {
		procedure(it->second);
	}
	return it != map.end();
}

/*!
 * Applies procedure on mapped value if found.
 * TODO: For this to be general enough we need optionals.
 * Returns whether or not we applied procedure. E.g. if map has entry with key.
 */
template <typename Map, typename Key>
bool find_and_apply(Map const& map, Key const& key,
		std::function<void(typename Map::mapped_type const&)> const& procedure) {
	auto it = map.find(key);
	if (it != map.end()) {
		procedure(it->second);
	}
	return it != map.end();
}

/*
 *  Full range functions.
 */

// Full range find/find_if
template <typename Container, typename Value>
typename Container::iterator find(Container &c, Value const& v) {
	return std::find(std::begin(c), std::end(c), v);
}

template <typename Container, typename Value>
typename Container::const_iterator find(Container const& c, Value const& v) {
	return std::find(std::begin(c), std::end(c), v);
}

template <typename Container, typename Predicate>
typename Container::iterator find_if(Container &c, Predicate const& p) {
	return std::find_if(std::begin(c), std::end(c), p);
}

template <typename Container, typename Predicate>
typename Container::const_iterator find_if(Container const& c, Predicate const& p) {
	return std::find_if(std::begin(c), std::end(c), p);
}

}

#endif
