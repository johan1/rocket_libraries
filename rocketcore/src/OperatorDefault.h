#ifndef _OPERATOR_DEFAULT_H_
#define _OPERATOR_DEFAULT_H_

template <typename T>
struct strict_totally_ordered {
	// t1 > t2 <=> t2 < t1
	friend bool operator>(T const& t1, T const& t2) {
		return operator<(t2, t1);
	}

	// t1 >= t2 <=> !(t1 < t2)
	friend bool operator>=(T const& t1, T const& t2) {
		return !operator<(t1, t2);
	}

	// t1 <= t2 <=> !(t1 > t2)
	friend bool operator<=(T const& t1, T const& t2) {
		return !operator>(t1, t2);
	}

	// t1 == t2 <=> t1 <= t2 && t2 <= t1
	friend bool operator==(T const& t1, T const& t2) {
		return operator<=(t1, t2) && operator<=(t2, t1);
	}

	// t1 != t2 <==> !(t1 == t2)
	friend bool operator!=(T const& t1, T const& t2) {
		return !operator==(t1, t2);
	}
};

#endif
