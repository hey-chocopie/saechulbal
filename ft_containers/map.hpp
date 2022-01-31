#ifndef __MAP_HPP__
#define __MAP_HPP__
#include <memory>
#include <iostream>
#include <string>
#include "pair.hpp"
#include "./utility.hpp"
#include "random_access_iterator_tag.hpp"
// ex : map<int, int> m;
namespace ft
{
	template < class Key,                                     // map::key_type
           class T,                                       // map::mapped_type
           class Compare = less<Key>,                     // map::key_compare
           class Alloc = allocator<pair<const Key,T> >    // map::allocator_type
    > class map{
	public:
		//===========================Member types=======================
		typedef T											value_type;		//T
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;		//T&
		typedef typename allocator_type::const_reference	const_reference;//const T&
		typedef typename allocator_type::pointer			pointer;		//T*
		typedef typename allocator_type::const_pointer		const_pointer;	//const T*
		typedef ptrdiff_t									difference_type;
		typedef size_t										size_type;
		std::pair
		allocator_type										_alloc;
		value_type*											_array;
		size_type											_size;
		size_type											_capacity;

		typedef normal_iter<value_type>						iterator;
		typedef normal_iter<const value_type>				const_iterator;
		typedef reverse_iterator_tag<iterator>				reverse_iterator;
		typedef reverse_iterator_tag<const_iterator>		const_reverse_iterator;

		//===========================construct=======================
		//default (1) 설명 : vector<int> tmp = 6 같이 의도치않은 생성제외
		explicit vector(const allocator_type& alloc = allocator_type());
		//fill (2)
		explicit vector(size_t n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
		//range (3)
		template <class InputIterator>
				vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(), 
				typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = nullptr);
		//copy (4)
		vector (vector const& x);
		vector& operator= (const vector& rhd); 			

		//===========================iterator=======================
		iterator					begin();
		const_iterator				begin() const;
		iterator					end();
		const_iterator				end() const;
		reverse_iterator			rbegin();
		const_reverse_iterator		rbegin() const;
		reverse_iterator			rend();
		const_reverse_iterator		rend() const;

		//==========================Capacity=======================
		size_type					size() const;
		size_type					max_size() const;
		void						resize(size_type n, value_type val = value_type());
		size_type					capacity() const;
		bool						empty() const;			
		void						reserve(size_type n);

		//========================Element accenss:====================
		reference					operator[](size_type n);			
		const_reference				operator[](size_type n) const;
		reference					at(size_type n);
		const_reference				at(size_type n) const;
		reference					front();
		const_reference				front() const;
	    reference					back();
		const_reference				back() const;

		//=======================Modifers=====================
		template <class InputIterator>
		void						assign(InputIterator first, InputIterator last,
									typename enable_if<!is_integral<InputIterator>::value>::type* = 0); 
		void						assign(size_type n, const value_type& val);
		void						push_back(const value_type& val);
		void						pop_back ();
		//single element (1)
		iterator					insert(iterator position, const value_type& val);
		//fill (2)	
		void						insert(iterator position, size_type n, const value_type& val);
		//range (3)	
		template <class InputIterator>
		void						insert(iterator position, InputIterator first, InputIterator last,
									typename enable_if<!is_integral<InputIterator>::value, 
									InputIterator>::type* = nullptr);
		iterator					erase(iterator position);
		iterator					erase(iterator first, iterator last);
		void						clear();
		allocator_type				get_allocator() const;
		void						swap(vector& x);
	};
	
	//=======================Construct=====================
	template <typename T, class Alloc>
	vector<T, Alloc>::vector
		(const allocator_type& alloc)
		: _alloc(alloc), _array(0), _size(0),  _capacity(0)
	{
	}
	template <typename T, class Alloc>
	vector<T, Alloc>::vector
		(size_t n, const value_type& val, const allocator_type& alloc)
		: _alloc(alloc),  _size(n),_capacity(n)
	{
		_array = _alloc.allocate(_capacity);
		for (size_t i = 0; i < _size; i++)
			_alloc.construct(_array + i, val);
	}
	template <typename T, class Alloc>
	template <class InputIterator>
	vector<T, Alloc>::vector
		(InputIterator first, InputIterator last, const allocator_type& alloc,
		typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type*)
		: _alloc(alloc), _array(0)
	{
		this->assign(first, last);
	} 
	template <typename T, class Alloc>
	vector<T, Alloc>::vector (vector const& rhs) : _array(0)  
	{
		*this = rhs;
	}

	//===========================iterator=======================
	template <typename T, class Alloc>
	typename vector<T, Alloc>::iterator					vector<T, Alloc>::begin()
	{
		return ((_array));
	}
	template <typename T, class Alloc>
	typename vector<T, Alloc>::const_iterator			vector<T, Alloc>::begin() const
	{
		return (_array);
	}
	template <typename T, class Alloc>
	typename vector<T, Alloc>::iterator					vector<T, Alloc>::end()
	{
		return (_array + _size);
	}
	template <typename T, class Alloc>
	typename vector<T, Alloc>::const_iterator			vector<T, Alloc>::end() const
	{
		return (_array + _size);
	}
	template <typename T, class Alloc>
	typename vector<T, Alloc>::reverse_iterator			vector<T, Alloc>::rbegin()
	{
		return (reverse_iterator(vector<T, Alloc>::end()));
	}
	template <typename T, class Alloc>
	typename vector<T, Alloc>::const_reverse_iterator	vector<T, Alloc>::rbegin() const
	{
		return (const_reverse_iterator(vector<T, Alloc>::end()));
	}
	template <typename T, class Alloc>
	typename vector<T, Alloc>::reverse_iterator			vector<T, Alloc>::rend()
	{
		return (reverse_iterator(vector<T, Alloc>::begin()));
	}
	template <typename T, class Alloc>
	typename vector<T, Alloc>::const_reverse_iterator	vector<T, Alloc>::rend() const
	{
		return (const_reverse_iterator(vector<T, Alloc>::begin()));
	}

	//==========================Capacity=======================
	template <typename T, class Alloc>
	typename vector<T, Alloc>::size_type				vector<T, Alloc>::size() const
	{
		return this->_size;
	}
	template <typename T, class Alloc>
	typename vector<T, Alloc>::size_type				vector<T, Alloc>::max_size() const
	{
		return (_alloc.max_size()); 
	}
	template <typename T, class Alloc>
	void												vector<T, Alloc>::resize (size_type n, value_type val)
	{
		if (n < _size)
			_size = n;
		else if(n > _size)
		{
			if(n > _capacity)
			{
				for(; _size < n; )
					push_back(val);
				//설명 : push_back 안에 _size++있음.
			}
			else if(n <= _capacity)
			{
				for(; _size < n; _size++)
					_array[_size] = val;
			}
			_size = n;
		}
	}
	template <typename T, class Alloc>
	typename vector<T, Alloc>::size_type				vector<T, Alloc>::capacity() const
	{
		return (this->_capacity);
	}
	template <typename T, class Alloc>
	bool												vector<T, Alloc>::empty() const
	{
		return (_size == 0 ? true : false);
	}			
	template <typename T, class Alloc>
	void												vector<T, Alloc>::reserve(size_type n)
	{
		if(_capacity < n)
		{	
			T* tmp = _alloc.allocate(n);
			for(size_t i = 0; i < _size; i++)
			{
				_alloc.construct(tmp + i, *(_array + i));
			}
			Array_clear_free(_size, _capacity, _array, _alloc);
			_array = tmp;
			_capacity = n;
		}
	}

	//========================Element accenss:====================
	template <typename T, class Alloc>
	typename vector<T, Alloc>::reference		vector<T, Alloc>::operator[] (size_type n)
	{
		return ((this->_array)[n]);
	}	
	template <typename T, class Alloc>
	typename vector<T, Alloc>::const_reference	vector<T, Alloc>::operator[] (size_type n) const
	{
		return ((this->_array)[n]);
	}
	template <typename T, class Alloc>
	typename vector<T, Alloc>::reference		vector<T, Alloc>::at (size_type n)
	{
		if (n >= size())
			throw std::out_of_range("vector");
			//보충 : std의 에러를 던짐 한번 보기. 
		return (*(this->_array + n));
	}
	template <typename T, class Alloc>
	typename vector<T, Alloc>::const_reference	vector<T, Alloc>::at (size_type n) const
	{
		if (n >= size())
			throw std::out_of_range("vector"); 
		return (*(this->_array + n));
	}
	template <typename T, class Alloc>
	typename vector<T, Alloc>::reference		vector<T, Alloc>::front()
	{
		return (*(this->_array));
	}
	template <typename T, class Alloc>
	typename vector<T, Alloc>::const_reference	vector<T, Alloc>::front() const
	{
		return (*(this->_array));
	}
	template <typename T, class Alloc>
	typename vector<T, Alloc>::reference		vector<T, Alloc>::back()
	{
		return (*(this->_array + _size - 1));
	}
	template <typename T, class Alloc>
	typename vector<T, Alloc>::const_reference	vector<T, Alloc>::back() const
	{
		return (*(this->_array + _size - 1));
	}

	//=======================Modifers=====================
	template <typename T, class Alloc>
	template <class InputIterator>
	void						vector<T, Alloc>::assign(InputIterator first, InputIterator last,
								typename enable_if<!is_integral<InputIterator>::value >::type*) 
	//설명 : is__integral에 int * 형 넣으면 enable_if<1>::type*= 0임.
	//설명 : enable_if<1>은 true이므로 type이 있으므로 assign이 정상적으로 작동 . 
	{
		Array_clear_free(_size, _capacity, _array, _alloc);
		ptrdiff_t distan_value = distance2<InputIterator>(first, last);
		_size = distan_value;
		_capacity = distan_value;
		_array = _alloc.allocate(distan_value);
		for(int i = 0; first != last; i++)
		{
			_alloc.construct(_array + i, *first);
			first++;
		}
	}
	template <typename T, class Alloc>
	void						vector<T, Alloc>::assign(size_type n, const value_type& val)
	{
		Array_clear_free(_size, _capacity, _array, _alloc);
		_size = n;
		_capacity = n;
		_array = _alloc.allocate(n);
		for(size_type i = 0; i < n; i++)
		{
			_alloc.construct(_array + i, val);
		}
	}
	template <typename T, class Alloc>
	vector<T, Alloc>&			vector<T, Alloc>::operator=(const vector<T, Alloc>& rhd)
	{
		if(this == &rhd)
			return (*this);
		Array_clear_free(_size, _capacity, _array, _alloc);
		this->_size = rhd._size;
		this->_alloc = rhd._alloc;
		this->_capacity = rhd._capacity;
		_array = _alloc.allocate(rhd._capacity);
		for (size_t i = 0; i < rhd._size; i++)
			_alloc.construct(_array + i, rhd._array[i]);
		return (*this);
	}
	template <typename T, class Alloc>
	void						vector<T, Alloc>::push_back(const value_type& val)
	{
		if(_size + 1 > _capacity)
		{
			reserve(increase_capacity(_size, 1, _capacity));
		}
		_alloc.construct(_array + _size, val);
		_size++;
	}
	template <typename T, class Alloc>
	void						vector<T, Alloc>::pop_back ()
	{
		if(_size != 0)
			_size--;
		_alloc.destroy(_array + _size);
	}
	template <typename T, class Alloc>
	typename					vector<T, Alloc>::iterator vector<T, Alloc>::insert
								(iterator position, const value_type& val)
	{
		size_t								idx;
		int									put_position_ptr_flag = 0; 

		_capacity = increase_capacity(_size, 0, _capacity); 
		T* tmp = _alloc.allocate(_capacity);
		for(size_t i = 0; i < _size + 1; i++)
		{
			if(put_position_ptr_flag == 0 && _array + i == position._ptr)
			{
				_alloc.construct(tmp + i, val);
				put_position_ptr_flag = 1;
				idx = i;
			}
			else
				_alloc.construct(tmp + i, *(_array + i - put_position_ptr_flag));
		}
		Array_clear_free(_size, _capacity, _array, _alloc);
		_array = tmp;
		_size = _size + 1;
		return (iterator(this->begin() + idx));
	}
	template <typename T, class Alloc>
	void						vector<T, Alloc>::insert
								(iterator position, size_type n, const value_type& val)
	{
		if (n != 0)
		{
			size_t							j = 0;
			int								put_position_ptr_flag = 0;

			_capacity = increase_capacity(_size, n, _capacity);
			T* tmp = _alloc.allocate(_capacity);
			for(size_t i = 0; i < _size + n + 1; i++)
			{
				if(put_position_ptr_flag == 0 && _array + i == position._ptr)
				{
					for(j = 0; j < n; j++)
					{
						_alloc.construct(tmp + i + j, val);
					}
					put_position_ptr_flag = 1;
					i = i + j; 
					//수정 : 인덱스 조정.
				}
				else
				{
					_alloc.construct(tmp + i - put_position_ptr_flag, *(_array + (i - j) - put_position_ptr_flag));
				}
			}
			Array_clear_free(_size, _capacity, _array, _alloc);
			_array = tmp;
			_size = _size + n;
		}
	}
	template <typename T, class Alloc>
	template <class InputIterator>
		void					vector<T, Alloc>::insert
								(iterator position, InputIterator first, InputIterator last,
								typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type*)
	{
		int										put_position_ptr_flag = 0;
		int										j = 0;

		difference_type cnt = distance2<T, InputIterator>(first, last);
		_capacity = increase_capacity(_size, cnt, _capacity);
		T* tmp = _alloc.allocate(_capacity);
		for(size_t i = 0; i < _size + cnt + 1; i++)
		{
			if(put_position_ptr_flag != 1 && _array + i == position._ptr)
			{
				for(j = 0; first != last; first++)
				{
					_alloc.construct(tmp + i + j, *first);
					j++;
				}
				put_position_ptr_flag = 1;
				i = i + j;
			}
			else
				_alloc.construct(tmp + i - put_position_ptr_flag, *(_array + (i - j) - put_position_ptr_flag));
		}
		Array_clear_free(_size, _capacity, _array, _alloc);
		_array = tmp;
		_size = _size + cnt;
	}
	template <typename T, class Alloc>
	typename vector<T, Alloc>::iterator	vector<T, Alloc>::erase(iterator position)
	{
		size_t									idx = 0;

		T* tmp = _array;
		for(size_t i = 0; i < _size; i++)
		{
			if(tmp == position._ptr)
			{
				idx = i;
				_alloc.destroy(_array + i);
				for(; i < _size; i++)
				{
					_alloc.construct(_array + i, *(_array + i + 1));
					_alloc.destroy(tmp + i);
				}
				_size--;
			}
			tmp++;
		}
		return (iterator(_array + idx));
	}
	template <typename T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last)
	{
		size_t									idx = 0;

		T* tmp = _array;
		difference_type length = last - first;
		if(length > 0)
		{
			for(size_t i = 0; i < _size; i++)
			{
				if(tmp == first._ptr)
				{
					idx = i;
					for(int j = 0; first != last; first++, j++)
						_alloc.destroy(_array + i + j);
					for(; i < _size - length; i++)
					{
						_alloc.construct(_array + i, *(_array + i + length));
						_alloc.destroy(_array + i + length);
					}	
					_size = _size - length;
				}
				tmp++;
			}
		}
		return iterator(_array + idx);
	}
	template <typename T, class Alloc>
	void									vector<T, Alloc>::clear()
	{
		for(size_t i = 0; i < _size; i++)
		{
			_alloc.destroy(_array + _size);
		}
		_size = 0;
	}
	template <typename T, class Alloc>
	typename::ft::vector<T, Alloc>::allocator_type				vector<T, Alloc>::get_allocator() const
	{
		return (_alloc);
	}

	template <typename T, class Alloc>
	void						vector<T, Alloc>::swap(vector& x)
	{
		allocator_type										tmp_alloc = _alloc;
		T*													tmp_array = _array;
		size_type											tmp_size = _size;
		size_type											tmp_capacity = _capacity;
		
		_alloc = x._alloc;
		_array = x._array;
		_size = x._size;
		_capacity = x._capacity;
		
		x._alloc = tmp_alloc;
		x._array = tmp_array;
		x._size = tmp_size;
		x._capacity = tmp_capacity;
	}

	//=======================Non-member function overloads=====================
	template <class T, class Alloc>
	bool operator== (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{ return ( equal_check(lhs, rhs) ? 1 : 0); }
	template <class T, class Alloc>
	bool operator!= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{ return ( equal_check(lhs, rhs) ? 0 : 1); }
	template <class T, class Alloc>
	bool operator<	(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{ return ( right_compare_check(lhs, rhs) ?  1 : 0); }
	template <class T, class Alloc>
	bool operator<= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{ return ( all_check(lhs, rhs, right_compare_check<const ft::vector<T,Alloc>, const ft::vector<T,Alloc> >) ? 1 : 0); }
	template <class T, class Alloc>
	bool operator>  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{return ( ft::left_compare_check(lhs, rhs) ?  1 : 0); }
	template <class T, class Alloc>
	bool operator>= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{ return ( ft::all_check(lhs, rhs, ft::left_compare_check<const ft::vector<T,Alloc> , const ft::vector<T,Alloc> >) ? 1 : 0); }

}

#endif