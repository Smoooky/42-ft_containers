//
// Created by matsony on 19.07.22.
//

#ifndef FT_CONTAINERS_FINAL_STACK_HPP
#define FT_CONTAINERS_FINAL_STACK_HPP

#include "vector.hpp"

namespace ft {
template<typename T, typename Container = ft::vector<T> >
class stack {
public:
	typedef T								value_type;
	typedef Container						container_type;
	typedef typename Container::size_type	size_type;

protected:
	Container	c;

public:
	stack(const container_type &cnt = container_type()): c(cnt) {};
	stack(const stack &inst) {*this = inst;}
	~stack(){}

	stack &operator=(const stack &inst) {
		if (this == &inst)
			return *this;
		c = inst.c;
		return (*this);
	}

	bool				empty() const {return c.empty();}
	size_type			size() const {return c.size();}
	value_type			&top() { return c.back();}
	const value_type	&top() const {return c.back();}
	void 				push(const value_type& val) {c.push_back(val);}
	void				pop() {c.pop_back();}
	void				swap(stack &x) {c.swap(x.c);}

	friend bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs.c == rhs.c;
	}

	friend bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs.c != rhs.c;
	}

	friend bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs.c < rhs.c;
	}

	friend bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs.c <= rhs.c;
	}

	friend bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs.c > rhs.c;
	}

	friend bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs.c >= rhs.c;
	}
};

template<typename T, typename Container>
void    swap(stack<T, Container> &x, stack<T, Container> &y){x.swap(y);}

}

#endif //FT_CONTAINERS_FINAL_STACK_HPP
