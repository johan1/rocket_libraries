#ifndef _ROCKET_ALGORITHM_H_
#define _ROCKET_ALGORITHM_H_

#include <algorithm>
#include <functional>
#include <iterator>

namespace rocket {

/*
 * Functors
 */

// Accessor functors

template <int N>
struct getter {
	template <typename... UTypes>
	typename std::tuple_element<N, std::tuple<UTypes...>>::type &
	operator()(std::tuple<UTypes...> &t) { return std::get<N>(t); }

	template <typename... UTypes>
	typename std::tuple_element<N, std::tuple<UTypes...>>::type const&
	operator()(std::tuple<UTypes...> const& t) { return std::get<N>(t); }
};

template <>
struct getter<0> {
	template <typename... UTypes>
	typename std::tuple_element<0, std::tuple<UTypes...>>::type &
	operator()(std::tuple<UTypes...> &t) { return std::get<0>(t); }

	template <typename... UTypes>
	typename std::tuple_element<0, std::tuple<UTypes...>>::type const&
	operator()(std::tuple<UTypes...> const& t) { return std::get<0>(t); }

	template <typename P>
	auto operator()(P &p) -> decltype(p.first)& { return p.first; }

	template <typename P>
	auto operator()(P const &p) -> decltype(p.first) const& { return p.first; }
};

template <>
struct getter<1> {
	template <typename... UTypes>
	typename std::tuple_element<1, std::tuple<UTypes...>>::type &
	operator()(std::tuple<UTypes...> &t) { return std::get<1>(t); }

	template <typename... UTypes>
	typename std::tuple_element<1, std::tuple<UTypes...>>::type const&
	operator()(std::tuple<UTypes...> const& t) { return std::get<1>(t); }

	template <typename P>
	auto operator()(P &p) -> decltype(p.second)& { return p.second; }

	template <typename P>
	auto operator()(P const &p) -> decltype(p.second) const& { return p.second; }
};

/*
 *  Full range functions.
 */

// Sorting
template <typename Container, typename Compare>
void sort(Container &container, Compare &&compare) {
	std::sort(std::begin(container), std::end(container), std::forward<Compare>(compare));
}

template <typename Container, typename Compare>
void sort(Container &container) {
	std::sort(std::begin(container), std::end(container));
}

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

// Full range transform
template <typename Container, typename OutputIt, typename UnaryOperation>
OutputIt transform(Container const& c, OutputIt it, UnaryOperation unary_op) {
	return std::transform(std::begin(c), std::end(c), it, unary_op);
}

/*
 * Utilities
 */

// Remove/erase ideom on containers
template <typename Container, typename Value>
void erase(Container &container, Value const& value) {
	container.erase(std::remove(container.begin(), container.end(), value), container.end());
}

template <typename Container, typename Predicate>
void erase_if(Container &container, Predicate p) {
	container.erase(std::remove_if(container.begin(), container.end(), p), container.end());
}

// Map utilies

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


// TODO: This is maybe not so useful.
template <typename InputIt, typename Value>
InputIt find_and_apply(InputIt first, InputIt last, Value const& v,
		std::function<void(typename std::iterator_traits<InputIt>::value_type &)> const& procedure) {
	auto it = std::find_if(first, last, v);
	if (it != last) {
		procedure(*it);
	}
	return it;
}

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

}

#endif
