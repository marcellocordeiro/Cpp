#ifndef __queue_hpp_included__
#define __queue_hpp_included__

#include "list.hpp"

template <typename T>
class queue: private list<T> {
	public:
		inline bool empty () const {
			return list<T>::empty();
		}

		inline typename list<T>::size_type size () const {
			return list<T>::size();
		}

		inline T front () const {
			return list<T>::front();
		}

		inline T back () const {
			return list<T>::back();
		}

		inline void push (T value) {
			list<T>::push_back(value);
		}

		inline void pop () {
			list<T>::pop_front();
		}
};

#endif