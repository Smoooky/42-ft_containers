//
// Created by matsony on 20.07.22.
//

#ifndef FT_CONTAINERS_FINAL_SET_HPP
#define FT_CONTAINERS_FINAL_SET_HPP

#include "rbtree.hpp"
#include "vector.hpp"

namespace ft
{
template <
		typename Key,
		typename Compare = std::less<Key>,
		typename Allocator = std::allocator<pair<const Key, void*> > >
class set
{
	typedef typename
	ft::RBTree<typename Allocator::value_type, Compare, Allocator>  rbtree_t;

public:
	typedef Key                                         key_type;
	typedef Key                                         value_type;
	typedef Compare                                     key_compare;
	typedef Compare                                     value_compare;
	typedef Allocator                                   allocator_type;
	typedef typename allocator_type::reference          reference;
	typedef typename allocator_type::const_reference    const_reference;
	typedef typename allocator_type::pointer            pointer;
	typedef typename allocator_type::const_pointer      const_pointer;
	typedef typename allocator_type::size_type          size_type;

	typedef typename rbtree_t::const_iterator           iterator;
	typedef typename rbtree_t::const_iterator           const_iterator;
	typedef typename rbtree_t::const_reverse_iterator   reverse_iterator;
	typedef typename rbtree_t::const_reverse_iterator   const_reverse_iterator;

private:
	key_compare     comp;
	allocator_type  alloc;
	rbtree_t        rbt;

public:
	explicit set(const key_compare &_comp = key_compare(),
				 const allocator_type &_alloc = allocator_type())
			:comp(_comp), alloc(_alloc){}

	template <typename InputIterator>
	set(InputIterator first, typename ft::IsInputIter<InputIterator>::type last,
		const key_compare &_comp = key_compare(),
		const allocator_type &_alloc = allocator_type())
			: comp(_comp), alloc(_alloc)
	{
		while (first != last)
		{
			rbt.insert(*first++);
		}

	}

	set(const set &inst)
			: comp(key_compare()), alloc(allocator_type()), rbt(rbtree_t(inst.rbt)){}

	~set(void){}

	set &operator=(const set &inst)
	{
		if (this == &inst)
			return *this;
		rbt = rbtree_t(inst.rbt);
		return *this;
	}

	//Iterators:
	iterator                begin(void){return rbt.begin();}
	const_iterator          begin(void) const {return rbt.begin();}
	iterator                end(void){return rbt.end();}
	const_iterator          end(void) const{return rbt.end();}
	reverse_iterator        rbegin(void){return rbt.rbegin();}
	const_reverse_iterator  rbegin(void) const {return rbt.rbegin();}
	reverse_iterator        rend(void){return rbt.rend();}
	const_reverse_iterator  rend(void) const {return rbt.rend();}
	const_iterator          cbegin(void) const {return rbt.cbegin();}
	const_iterator          cend(void) const {return rbt.cend();}
	const_reverse_iterator  crbegin(void) const {return rbt.crbegin();}
	const_reverse_iterator  crend(void) const {return rbt.crend();}

	//Capacity:
	bool    empty(void) const {return rbt.size() == 0;}
	size_t  size(void) const {return rbt.size();}
	size_t  max_size(void) const {return rbt.max_size();}

	//Modifiers:
	pair<iterator, bool>    insert(const value_type &val)
	{
		return rbt.insert(val);
	}

	iterator                insert(iterator position, const value_type& val)
	{
		(void)position;
		return rbt.insert(val).first;
	}

	template <class InputIterator>
	void        insert (InputIterator first, InputIterator last)
	{
		while (first != last)
		{
			rbt.insert(*first);
			first++;
		}
	}

	void        erase(iterator position){rbt.remove(*position);}
	size_type   erase(const key_type &key){return rbt.remove(key);}
	void        erase(iterator first, iterator last)
	{
		vector<key_type>                    keys;
		typename vector<key_type>::iterator it;
		typename vector<key_type>::iterator ite;

		while (first != last)
		{
			keys.push_back(*first);
			first++;
		}
		it = keys.begin();
		ite = keys.end();
		while (it != ite)
		{
			rbt.remove(*it++);
		}

	}

	void            swap(set &inst){rbt.swap(inst.rbt);}
	void            clear(void){rbt.clear();}

	//Operations:
	iterator        find(const key_type &key)
	{
		return iterator(rbt.findNode(key), &rbt);
	}

	const_iterator  find(const key_type &key) const
	{
		return const_iterator(rbt.findNode(key), &rbt);
	}

	size_type       count(const key_type &key) const
	{
		if (rbt.findNode(key) == NULL)
			return 0;
		return 1;
	}

	iterator        lower_bound(const key_type &key)
	{
		iterator it = begin();
		iterator ite = end();
		while (it != ite && comp(*it, key))
		{
			++it;
		}
		return it;
	}

	const_iterator  lower_bound(const key_type &key) const
	{
		const_iterator it = begin();
		const_iterator ite = end();
		while (it != ite && comp(*it, key))
		{
			++it;
		}
		return it;
	}

	iterator        upper_bound(const key_type &key)
	{
		iterator it = begin();
		iterator ite = end();
		while (it != ite && !comp(key, *it))
		{
			++it;
		}
		return it;
	}

	const_iterator  upper_bound (const key_type &key) const
	{
		const_iterator it = begin();
		const_iterator ite = end();
		while (it != ite && !comp(key, *it))
		{
			++it;
		}
		return it;
	}

	pair<iterator, iterator>             equal_range(const key_type &key)
	{
		return make_pair<iterator, iterator>(lower_bound(key), upper_bound(key));
	}

	pair<const_iterator, const_iterator> equal_range(const key_type& key) const
	{
		return make_pair<const_iterator, const_iterator>(
				lower_bound(key), upper_bound(key));
	}

	//Allocator:
	allocator_type get_allocator(void) const {return allocator_type();}

	//Observers:
	key_compare     key_comp(void) const {return key_compare();}
	value_compare   value_comp(void) const {return value_compare();}

	void print(){rbt.print();}
};


//std::swap overload
template <typename Key, typename Compare, typename Allocator>
void    swap(ft::set<Key, Compare, Allocator> &lhs,
			 ft::set<Key, Compare, Allocator> &rhs){lhs.swap(rhs);}

//Comparee operators:
template <typename Key, typename Compare, typename Allocator>
bool    operator==(const ft::set<Key, Compare, Allocator> &f,
				   const ft::set<Key, Compare, Allocator> &s)
{
	return equal(f.begin(), f.end(), s.begin(), s.end());
}

template <typename Key, typename Compare, typename Allocator>
bool    operator!=(const ft::set<Key, Compare, Allocator> &f,
				   const ft::set<Key, Compare, Allocator> &s)
{
	return !(f == s);
}

template <typename Key, typename Compare, typename Allocator>
bool    operator<(const ft::set<Key, Compare, Allocator> &f,
				  const ft::set<Key, Compare, Allocator> &s)
{
	return ft::lexicographical_compare(f.begin(), f.end(), s.begin(), s.end());
}

template <typename Key, typename Compare, typename Allocator>
bool    operator<=(const ft::set<Key, Compare, Allocator> &f,
				   const ft::set<Key, Compare, Allocator> &s)
{
	return (f < s) || (f == s);
}

template <typename Key, typename Compare, typename Allocator>
bool    operator>(const ft::set<Key, Compare, Allocator> &f,
				  const ft::set<Key, Compare, Allocator> &s)
{
	return !(f < s) && (f != s);
}

template <typename Key, typename Compare, typename Allocator>
bool    operator>=(const ft::set<Key, Compare, Allocator> &f,
				   const ft::set<Key, Compare, Allocator> &s)
{
	return (f > s) || (f == s);
}
}

#endif //FT_CONTAINERS_FINAL_SET_HPP
