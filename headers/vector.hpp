//
// Created by matsony on 19.07.22.
//

#ifndef FT_CONTAINERS_FINAL_VECTOR_HPP
#define FT_CONTAINERS_FINAL_VECTOR_HPP

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <cstdio>

#include "utils.hpp"
#include "iterators.hpp"

namespace ft {
const std::string OOR_MSG =
		"vector::at: n (which is %lu) >= this->size() (which is %lu)";

template<typename T, typename Allocator = std::allocator<T> >
class vector {
	template<bool IsConst>
	struct common_iterator;

public:
	typedef T value_type;
	typedef Allocator allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef typename allocator_type::size_type size_type;

	typedef vector::common_iterator<NotConst> iterator;
	typedef vector::common_iterator<Const> const_iterator;
	typedef common_reverse_iterator<iterator> reverse_iterator;
	typedef common_reverse_iterator<const_iterator> const_reverse_iterator;


private:
	value_type *arr;
	size_type len;
	size_type cap;
	allocator_type alloc;

private:
	//Utils:
	void uptocap(size_type newcap);

	void destroy(void);

public:
	vector(const allocator_type &_alloc = allocator_type())
			: arr(NULL), len(0), cap(0), alloc(_alloc) {}

	vector(const size_type n, const value_type &val = value_type(),
		   const allocator_type &_alloc = allocator_type());

	template<class InputIterator>
	vector(InputIterator first, typename IsInputIter<InputIterator>::type last,
		   const allocator_type &_alloc = allocator_type())
			: arr(NULL), len(0), cap(0), alloc(_alloc) { assign(first, last); }

	vector(const vector &inst)
			: arr(NULL), len(0), cap(0), alloc(allocator_type()) { *this = inst; }

	~vector(void) { clear(); }

	vector &operator=(const vector &inst);

	//Iterators:
	iterator begin(void);

	const_iterator begin(void) const;

	iterator end(void);

	const_iterator end(void) const;

	reverse_iterator rbegin(void);

	const_reverse_iterator rbegin(void) const;

	reverse_iterator rend(void);

	const_reverse_iterator rend(void) const;

	const_iterator cbegin(void) const;

	const_iterator cend(void) const;

	const_reverse_iterator crbegin(void) const;

	const_reverse_iterator crend(void) const;

	//Element access:
	reference operator[](const size_type i) { return arr[i]; }

	const_reference operator[](const size_type i) const { return arr[i]; }

	reference at(const size_type n);

	const_reference at(const size_type n) const;

	reference front(void) { return *arr; }

	const_reference front(void) const { return *arr; }

	reference back(void) { return arr[len - 1]; }

	const_reference back(void) const { return arr[len - 1]; }

	//Capacity:
	size_type size(void) const { return len; }

	size_type max_size(void) const { return alloc.max_size(); }

	void resize(const size_type n, const value_type val = value_type());

	size_type capacity(void) const { return cap; }

	bool empty(void) const { return len == false; }

	void reserve(const size_type n) {
		if (n <= cap) return;
		uptocap(n);
	}

	void shrink_to_fit(void) {
		if (len == cap) return;
		uptocap(len);
	}

	//Modifiers:
	template<typename InputIterator>
	typename IsInputIter<InputIterator, ft::setVoid>::type
	assign(InputIterator first, InputIterator last);

	void assign(const size_type n, const value_type &val);

	void push_back(const value_type &value);

	void pop_back(void) { if (len) alloc.destroy(&arr[--len]); }

	iterator insert(iterator position, const value_type &val);

	void insert(iterator position, size_t n, const value_type &val);

	template<typename InputIterator>
	void insert(iterator position, InputIterator first,
				typename IsInputIter<InputIterator>::type last);

	template<typename InputIterator>
	typename IsInputIter<InputIterator>::type
	erase(InputIterator position);

	template<typename InputIterator>
	typename IsInputIter<InputIterator>::type
	erase(InputIterator first, InputIterator last);

	allocator_type get_allocator(void) const { return alloc; }

	void swap(vector &x);

	void clear(void);

};

//Compaire operators:
template<typename T, typename Allocator>
bool operator==(const vector<T, Allocator> &f, const vector<T, Allocator> &s) {
	return equal(f.begin(), f.end(), s.begin(), s.end());
}

template<typename T, typename Allocator>
bool operator!=(const vector<T, Allocator> &f, const vector<T, Allocator> &s) {
	return !(f == s);
}

template<typename T, typename Allocator>
bool operator<(const vector<T, Allocator> &f, const vector<T, Allocator> &s) {
	return ft::lexicographical_compare(f.begin(), f.end(), s.begin(), s.end());
}

template<typename T, typename Allocator>
bool operator<=(const vector<T, Allocator> &f, const vector<T, Allocator> &s) {
	return (f < s) || (f == s);
}

template<typename T, typename Allocator>
bool operator>(const vector<T, Allocator> &f, const vector<T, Allocator> &s) {
	return !(f < s) && (f != s);
}

template<typename T, typename Allocator>
bool operator>=(const vector<T, Allocator> &f, const vector<T, Allocator> &s) {
	return (f > s) || (f == s);
}

//std::swap:
template<typename T, typename Allocator>
void swap(vector<T, Allocator> &f, vector<T, Allocator> &s) { f.swap(s); }

template<typename T, typename Allocator>
ft::vector<T, Allocator>::vector(
		const size_type n, const value_type &val, const allocator_type &_alloc)
		: arr(NULL), len(n), cap(n), alloc(_alloc) {
	arr = alloc.allocate(cap);
	for (size_t i = 0; i < len; i++)
		alloc.construct(&arr[i], val);
}

template<typename T, typename Allocator>
ft::vector<T, Allocator> &ft::vector<T, Allocator>::operator=(
		const vector &inst) {
	if (this == &inst)
		return (*this);
	clear();
	len = inst.len;
	cap = inst.cap;
	if (cap) {
		arr = alloc.allocate(cap);
		for (size_t i = 0; i < len; i++) {
			alloc.construct(&arr[i], inst.arr[i]);
		}
	} else {
		arr = NULL;
	}
	return (*this);
}

//Utils:
template<typename T, typename Allocator>
void ft::vector<T, Allocator>::uptocap(
		typename ft::vector<T, Allocator>::size_type newcap) {
	ft::vector<T, Allocator>::value_type *tmp;

	tmp = alloc.allocate(newcap);
	for (size_t i = 0; i < len && i < newcap; i++) {
		try {
			alloc.construct(&tmp[i], arr[i]);
		}
		catch (...) {
			for (size_t j = 0; j < i; j++)
				alloc.destroy(&tmp[j]);
			alloc.deallocate(tmp, newcap);
			throw;
		}
	}
	for (size_t i = 0; i < len; i++)
		alloc.destroy(&arr[i]);
	alloc.deallocate(arr, cap);
	cap = newcap;
	if (len > cap)
		len = cap;
	arr = tmp;
}

//Element acsses:
template<typename T, typename Allocator>
typename ft::vector<T, Allocator>::reference
ft::vector<T, Allocator>::at(const size_type n) {
	if (n < len)
		return arr[n];
	char err[128];
	snprintf(err, 128, OOR_MSG.c_str(), n, len);
	throw std::out_of_range(err);
}

template<typename T, typename Allocator>
typename ft::vector<T, Allocator>::const_reference
ft::vector<T, Allocator>::at(const size_type n) const {
	if (n < len)
		return arr[n];
	char err[128];
	snprintf(err, 128, OOR_MSG.c_str(), n, len);
	throw std::out_of_range(err);
}

template<typename T, typename Allocator>
void ft::vector<T, Allocator>::destroy(void) {
	for (size_t i = 0; i < len; i++) {
		alloc.destroy(&arr[i]);
	}
	len = 0;
}

//Capacity:
template<typename T, typename Allocator>
void ft::vector<T, Allocator>::resize(
		const size_type n, const value_type val) {
	if (n == len)
		return;
	if (n < len) {
		while (len != n)
			pop_back();
	} else {
		while (len != n)
			push_back(val);
	}
}

//Modifiers:
template<typename T, typename Allocator>
template<typename InputIterator>
typename ft::IsInputIter<InputIterator, ft::setVoid>::type
ft::vector<T, Allocator>::assign(InputIterator first, InputIterator last) {
	destroy();
	while (first != last)
		push_back(*first++);
}

template<typename T, typename Allocator>
void ft::vector<T, Allocator>::assign(
		const size_type n, const value_type &val) {
	destroy();
	while (len != n)
		push_back(val);
}

template<typename T, typename Allocator>
void ft::vector<T, Allocator>::push_back(const value_type &value) {
	if (arr) {
		if (len == cap)
			uptocap(cap * 2);
	} else {
		cap = 2;
		arr = alloc.allocate(cap);
	}
	alloc.construct(&arr[len], value);
	len++;
}

template<typename T, typename Allocator>
typename ft::vector<T, Allocator>::iterator
ft::vector<T, Allocator>::insert(iterator position, const value_type &val) {
	size_t i;
	size_t j;

	if (position.base() == end().base()) {
		push_back(val);
		return end() - 1;
	} else if (position.base() == begin().base()) {
		reserve(len + 1);
		i = len - 1;
		while (i < len) {
			alloc.construct(&arr[i + 1], arr[i]);
			alloc.destroy(&arr[i--]);
		}
		alloc.construct(arr, val);
		len++;
		return begin();
	}
	j = distance(begin(), position);
	reserve(len + 1);
	i = len;
	while (i > j) {
		alloc.construct(&arr[i], arr[i - 1]);
		alloc.destroy(&arr[--i]);
	}
	alloc.construct(&arr[j], val);
	len++;
	return begin() + j;
}

template<typename T, typename Allocator>
void ft::vector<T, Allocator>::insert(
		iterator position, size_t n, const value_type &val) {
	size_t i;
	size_t j;
	value_type *tmp;

	if (position.base() == end().base()) {
		while (n--)
			push_back(val);
	} else if (position.base() == begin().base()) {
		tmp = alloc.allocate(n + size());
		try {
			i = 0;
			while (i < n + size()) {
				if (i < n)
					alloc.construct(&tmp[i], val);
				else
					alloc.construct(&tmp[i], arr[i - n]);
				i++;
			}
		}
		catch (...) {
			j = 0;
			while (j < i)
				alloc.destroy(&tmp[j++]);
			alloc.deallocate(tmp, n + size());
			throw;
		}
		j = 0;
		while (j < len)
			alloc.destroy(&arr[j++]);
		alloc.deallocate(arr, cap);
		arr = tmp;
		len = i;
		cap = i;

	} else {
		tmp = alloc.allocate(n + size());
		try {
			i = 0;
			j = 0;
			while (arr + i < position.base())
				alloc.construct(&tmp[j++], arr[i++]);
			while (j < i + n)
				alloc.construct(&tmp[j++], val);
			while (i < len)
				alloc.construct(&tmp[j++], arr[i++]);
		}
		catch (...) {
			i = 0;
			while (i < j)
				alloc.destroy(&tmp[i++]);
			alloc.deallocate(tmp, n + size());
			throw;
		}
		i = 0;
		while (i < len)
			alloc.destroy(&arr[i++]);
		alloc.deallocate(arr, cap);
		arr = tmp;
		len = j;
		cap = j;
	}
}

template<typename T, typename Allocator>
template<typename InputIterator>
void ft::vector<T, Allocator>::insert(iterator position, InputIterator first,
									  typename IsInputIter<InputIterator>::type last) {
	size_t i;
	size_t j;
	size_t tmp_size;
	value_type *tmp;

	if (position.base() == end().base()) {
		while (first != last)
			push_back(*first++);
	} else if (position.base() == begin().base()) {
		tmp_size = ft::distance(first, last) + size();
		tmp = alloc.allocate(tmp_size);
		try {
			i = 0;
			while (first != last)
				alloc.construct(&tmp[i++], *first++);
			j = 0;
			while (j < len)
				alloc.construct(&tmp[i++], arr[j++]);
		}
		catch (...) {
			j = 0;
			while (j < i)
				alloc.destroy(&tmp[j++]);
			alloc.deallocate(tmp, tmp_size);
			throw;
		}
		j = 0;
		while (j < len)
			alloc.destroy(&arr[j++]);
		alloc.deallocate(arr, cap);
		arr = tmp;
		len = i;
		cap = i;
	} else {
		tmp_size = ft::distance(first, last) + size();
		tmp = alloc.allocate(tmp_size);
		try {
			i = 0;
			j = 0;
			while (arr + i < position.base()) {
				alloc.construct(&tmp[i], arr[i]);
				i++;
			}
			j = i;
			while (first != last)
				alloc.construct(&tmp[i++], *first++);
			while (j < len)
				alloc.construct(&tmp[i++], arr[j++]);
		}
		catch (...) {
			j = 0;
			while (j < i)
				alloc.destroy(&tmp[j++]);
			alloc.deallocate(tmp, tmp_size);
			throw;
		}
		j = 0;
		while (j < len)
			alloc.destroy(&arr[j++]);
		alloc.deallocate(arr, cap);
		arr = tmp;
		len = i;
		cap = i;
	}
}

template<typename T, typename Allocator>
void ft::vector<T, Allocator>::clear(void) {
	if (arr) {
		destroy();
		alloc.deallocate(arr, cap);
	}
	cap = 0;
	arr = NULL;
}

template<typename T, typename Allocator>
template<typename InputIterator>
typename ft::IsInputIter<InputIterator>::type
ft::vector<T, Allocator>::erase(InputIterator position) {
	InputIterator ret = position;
	InputIterator it = position;
	InputIterator end = this->end();

	if (position == end)
		return position;
	alloc.destroy(position.base());
	position++;
	len--;
	if (position == end)
		return this->end();
	while (position != end) {
		alloc.construct(it.base(), *position);
		alloc.destroy(position.base());
		it++;
		position++;
	}
	return ret;
}

template<typename T, typename Allocator>
template<typename InputIterator>
typename ft::IsInputIter<InputIterator>::type
ft::vector<T, Allocator>::erase(InputIterator first, InputIterator last) {
	InputIterator it = first;
	InputIterator ret = first;
	InputIterator end = this->end();

	if (last.base() <= first.base())
		throw std::out_of_range("ft::vector::insert: iterator out of range");
	while (first != last) {
		alloc.destroy(first.base());
		first++;
		len--;
	}
	if (last == end)
		return this->end();
	while (last != end) {
		alloc.construct(it.base(), *last);
		it++;
		last++;
	}
	return ret;
}

template<typename T, typename Allocator>
void ft::vector<T, Allocator>::swap(vector<T, Allocator> &x) {
	if (this == &x)
		return;

	value_type *xarr = x.arr;
	size_type xlen = x.len;
	size_type xcap = x.cap;

	x.arr = arr;
	x.len = len;
	x.cap = cap;

	arr = xarr;
	len = xlen;
	cap = xcap;
}


//Iterators:
template<typename T, typename Allocator>
typename ft::vector<T, Allocator>::iterator
ft::vector<T, Allocator>::begin(void) {
	return iterator(arr);
}

template<typename T, typename Allocator>
typename ft::vector<T, Allocator>::const_iterator
ft::vector<T, Allocator>::begin(void) const {
	return const_iterator(arr);
}

template<typename T, typename Allocator>
typename ft::vector<T, Allocator>::iterator
ft::vector<T, Allocator>::end(void) {
	return iterator(arr + len);
}

template<typename T, typename Allocator>
typename ft::vector<T, Allocator>::const_iterator
ft::vector<T, Allocator>::end(void) const {
	return const_iterator(arr + len);
}

template<typename T, typename Allocator>
typename ft::vector<T, Allocator>::reverse_iterator
ft::vector<T, Allocator>::rbegin(void) {
	return reverse_iterator(end());
}

template<typename T, typename Allocator>
typename ft::vector<T, Allocator>::const_reverse_iterator
ft::vector<T, Allocator>::rbegin(void) const {
	return const_reverse_iterator(const_iterator(cend()));
}

template<typename T, typename Allocator>
typename ft::vector<T, Allocator>::reverse_iterator
ft::vector<T, Allocator>::rend(void) {
	return reverse_iterator(begin());
}

template<typename T, typename Allocator>
typename ft::vector<T, Allocator>::const_reverse_iterator
ft::vector<T, Allocator>::rend(void) const {
	return const_reverse_iterator(cbegin());
}

template<typename T, typename Allocator>
typename ft::vector<T, Allocator>::const_iterator
ft::vector<T, Allocator>::cbegin(void) const {
	return const_iterator(arr);
}

template<typename T, typename Allocator>
typename ft::vector<T, Allocator>::const_iterator
ft::vector<T, Allocator>::cend(void) const {
	return const_iterator(arr + len);
}

template<typename T, typename Allocator>
typename ft::vector<T, Allocator>::const_reverse_iterator
ft::vector<T, Allocator>::crbegin(void) const {
	return const_reverse_iterator(arr + len);
}

template<typename T, typename Allocator>
typename ft::vector<T, Allocator>::const_reverse_iterator
ft::vector<T, Allocator>::crend(void) const {
	return const_reverse_iterator(arr);
}


template<typename T, typename Allocator>
template<bool IsConst>
struct ft::vector<T, Allocator>::common_iterator
		: public iterator_base<std::random_access_iterator_tag,
				typename conditional<IsConst, value_type, const value_type>::type> {
	typedef
	typename common_iterator::iterator_base::difference_type diff_type;

	typedef
	typename conditional_t<IsConst, diff_type, const diff_type>::type diff_t;

	typedef
	typename conditional_t<IsConst, value_type, const value_type>::type value_t;

	typedef
	typename conditional_t<IsConst, iterator, const_iterator>::type iter_t;

private:
	value_t *item;

public:
	common_iterator(void) : item(NULL) {}

	common_iterator(value_t *_item) { item = _item; }

	common_iterator(const iterator &inst) : item(NULL) { *this = inst; }

	~common_iterator(void) {}

	iter_t &operator=(const iterator &inst) {
		if (item == inst.base())
			return *this;
		item = inst.base();
		return *this;
	}

	iter_t operator+(diff_t n) const { return iter_t(item + n); }

	iter_t operator-(diff_t n) const { return iter_t(item - n); }

	diff_t operator-(const iter_t &rhs) { return item - rhs.item; }

	diff_t operator-(const common_iterator &rhs) const { return item - rhs.item; }

	iter_t &operator+=(diff_t n) {
		item += n;
		return *this;
	}

	iter_t &operator-=(diff_t n) {
		item -= n;
		return *this;
	}

	iter_t &operator++(void) {
		++item;
		return *this;
	}

	iter_t operator++(int) { return iter_t(item++); }

	iter_t &operator--(void) {
		--item;
		return *this;
	}

	iter_t operator--(int) { return iter_t(item--); }

	value_t &operator*(void) const { return *item; }

	value_t *operator->(void) const { return item; }

	value_t &operator[](diff_t n) const { return item[n]; }

	value_t *base(void) const { return item; }

	void swap(iter_t &rhs) {
		value_t *tmp = item;
		item = rhs.item;
		rhs.item = tmp;
	}
};
}

#endif //FT_CONTAINERS_FINAL_VECTOR_HPP
