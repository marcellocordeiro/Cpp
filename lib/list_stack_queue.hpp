#ifndef __list_stack_queue_hpp_included__
#define __list_stack_queue_hpp_included__

namespace ll { // linked list
	template <typename T>
	struct node {
		T data;
		node<T> *prev;
		node<T> *next;

		node (): prev(nullptr), next(nullptr) {}

		node (T value, node<T> *prev, node<T> *next): data(value), prev(prev), next(next) {}
	};
}

template <typename T>
class list {
	protected:
		typedef ll::node<T>* _iterator;
		using size_type = unsigned int;

		ll::node<T> *head;
		ll::node<T> *tail;
		size_type _size;


	private:
		void erase (ll::node<T> *ptr) {
			ll::node<T> *temp = ptr;

			if (ptr->next != nullptr)
				ptr->next->prev = ptr->prev;

			ptr->prev->next = ptr->next;

			delete temp;

			_size--;
		}

		void insert (T value, ll::node<T> *ptr) {
			ll::node<T> *temp = new ll::node<T>(value, ptr, ptr->next);

			if (ptr->next != nullptr)
				ptr->next->prev = temp;

			ptr->next = temp;

			_size++;
		}
		
		void delete_list (ll::node<T> *ptr) {
			if (ptr == nullptr)
				return;

			delete_list(ptr->next);

			delete ptr;
		}

	public:
		struct iterator {
			_iterator ptr;

			iterator () {}
			iterator (_iterator it): ptr(it) {}

			_iterator &operator= (_iterator rhs) {
				ptr = rhs;
				return ptr;
			}

			bool operator!= (iterator rhs) {
				return !(ptr == rhs.ptr);
			}

			T &operator* () {
				return ptr->data;
			}

			iterator &operator++ (int) {
				ptr = ptr->next;
				return *this;
			}

			iterator &operator++ () {
				ptr = ptr->next;
				return *this;
			}
		};

		list (): _size(0) {
			head = new ll::node<T>;
			tail = head;
		}

		~list () {
			delete_list(head);
		}

		size_type size () {
			return _size;
		}

		iterator begin () {
			return iterator(head->next);
		}

		iterator end () {
			return iterator(nullptr);
		}

		T front () {
			return head->next->data;
		}

		T back () {
			return tail->data;
		}

		void push_front (T value) {
			insert(value, head);

			if (_size == 1)
				tail = head->next;
		}

		void push_back (T value) {
			insert(value, tail);

			tail = tail->next;
		}

		void pop_front () {
			if (_size == 0)
				return;

			erase(head->next);

			if (_size == 0)
				tail = head;
		}

		void pop_back () {
			if (_size == 0)
				return;

			tail = tail->prev;

			erase(tail->next);
		}

		friend std::ostream& operator<< (std::ostream &os, list<T> &l) {
			for (auto it = l.head->next; it != nullptr; it = it->next) {
				if (it->prev == l.head)
					os << "(prev: S) ";
				else
					os << "(prev: " << (it->prev->data) << ") ";

				os << "(cur: " << (it->data) << ") ";

				if (it->next == nullptr)
					os << "(next: N) ";
				else
					os << "(next: " << (it->next->data) << ") ";

				os << std::endl;				
			}

			return os;
		}

		/*
		 * todo:
		 *  search by value
		 *  search by pos
		 */
};

template <typename T>
class stack: private list<T> {
	public:
		T top () {
			return list<T>::front();
		}

		typename list<T>::size_type size () {
			return list<T>::_size;
		}

		void push (T value) {
			list<T>::push_front(value);
		}

		void pop () {
			list<T>::pop_front();
		}
};

template <typename T>
class queue: private list<T> {
	public:
		T top () {
			return list<T>::front();
		}

		typename list<T>::size_type size () {
			return list<T>::_size;
		}

		void push (T value) {
			list<T>::push_back(value);
		}

		void pop () {
			list<T>::pop_front();
		}
};

#endif