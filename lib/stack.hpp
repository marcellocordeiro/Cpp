#ifndef __stack_hpp_included__
#define __stack_hpp_included__

#include "list.hpp"

template <typename T>
class stack: private list<T> {
	public:
		inline bool empty () const {
			return list<T>::empty();
		}
		
		inline typename list<T>::size_type size () const {
			return list<T>::size();
		}

		inline T top () const {
			return list<T>::front();
		}

		inline void push (T value) {
			list<T>::push_front(value);
		}

		inline void pop () {
			list<T>::pop_front();
		}
};

#endif