#pragma once
# include <iostream>
# include <map>

namespace ft
{

template <typename Pair>
class node
{
public:
	typedef node	Node;
	typedef Pair	value_type;

	node(value_type val) : value(val), isnull(false)
	{
	}
 
	node(void) : isnull(true)
	{
	}

	value_type	value;
	bool		isnull;
	Node		parent;
	Node		left;
	Node		right;
};

template <class Node, class Compare>
class btree
{
public:
	typedef Node::value_type	Pair;
	typedef Node<Pair>			value_type;
	typedef Compare				key_compare;

	btree() : _comparator(key_compare()), root(), last(root), _size(0)
	{
	}

	void	insert(Pair val)
	{
		value_type tmp;

		tmp = this->root;
		while (_comparator(tmp, val))
		{
			tmp = tmp.left;
		}
	}

private:
	value_type	root;
	value_type	last;
	size_type	_size;
	key_compare	_comparator;
};

template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T> > >
class map
{
public:
	typedef Key							key_type;
	typedef T							mapped_type;
	typedef std::pair<const Key, T>		value_type;
	typedef	size_t						size_type;
	typedef ptrdiff_t					difference_type;
	typedef Compare						key_compare;
	typedef Allocator					allocator_type;
	typedef value_type&					reference;
	typedef const value_type& 			const_reference;
	typedef	Allocator::pointer			pointer;
	typedef	Allocator::const_pointer 	const_pointer;
	typedef	bidirectional_iterator<value_type>	iterator;
	typedef	bidirectional_iterator<const value_type>	const_iterator;
	typedef std::reverse_iterator						reverse_iterator;
	typedef	std::reverse_iterator<const_iterator> const_reverse_iterator;



private:
	typedef btree<Node, Pair, Compare> tree_type;

	tree_type _tree;
};

}

int main()
{
	ft::btree<node<std::pair<int, int> > >;
	return (0);
}