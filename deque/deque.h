#pragma once

#include <iostream>
#include <utility>

/**
@brief Deque
@detailed Double linked list 
@tparam elemType
*/
template<class elemType>//

class deque {
private:
	/**
	@brief Element struct
	*/
	struct elem {
		elemType value;
		elem *prev;
		elem *next;
	};
	elem *head;
	elem *tail;

public:
	/**
	@brief Deque iterator
	*/
	class dqIterator {
	private:
		elem* element;
	public:

		/**
		* Deque head constructor 
		* @param d is deque const reference to create iterator
		*/
		dqIterator(const deque& d) : element(d->head) {};
		/**
		* Element constructor
		* @param e is element pointer to iterator
		*/
		dqIterator(elem* e) : element(e) {};
		
		/**
	 * Shift iterator to next element
	 * @warning iterator 'nullptr' pointer
	 */
		void dqNext() {
			if(element == nullptr)
				throw std::exception("Error iterator");
			element = element->next;
		}

		/**
		* Shift iterator to prev element
		* @warning iterator 'nullptr' pointer
		*/
		void dqPrev() {
			if (element == nullptr)
				throw std::exception("Error iterator");
			element = element->prev;
		}

		/**
		* Equality copy operator for iterator
		* @param d is deque iterator const reference
		*/
		dqIterator& operator=(const dqIterator& d) {
			element = d->element;
			return *this;
		}

		/**
		* Equality operator for deque iterator
		* @param d is deque iterator const reference
		*/
		bool operator==(const dqIterator& d) {
			if(element == d.element)
				return true;
			return false;
		}

		/**
		* Inequality operator for deque iterator
		* @param d is deque iterator const reference
		*/
		bool operator!=(const dqIterator& d) {
			if (element != d.element)
				return true;
			return false;
		}
		
		/**
		* Get value of deque iterator's element
		* @warniing 'nullptr' iterator
		*/
		elemType& getElem() {
			if(element == nullptr)
				throw std::exception("Null iterator");
			return element->value;
		}
	};
	
	/**
	* Get deque head
	* @return deque head point iterator
	*/
	dqIterator dqHead() const {
		return dqIterator(head);
	}

	/**
	* Get element after deque tail
	* @return deque tail point iterator
	*/
	dqIterator dqTail() const {
		return dqIterator(nullptr);
	}

	/**
	* Default deque constructor
	*/
	deque() : head(nullptr), tail(nullptr) {};
	
	/**
	* Deque constructor with initialiezer list
	* @param listValue is list of 'elemType' values
	*/
	deque(std::initializer_list<elemType> listValue) : head(nullptr), tail(nullptr) {
		for (auto& value : listValue)
			dqPushTail(value);
	}

	/**
	* Copy deque constructor
	* @param d is deque const reference to copy
	*/
	deque(const deque& d) : head(nullptr), tail(nullptr) {
		for( dqIterator dqI = d.dqHead(); dqI != d.dqTail(); dqI.dqNext())
			dqPushTail(dqI.getElem());
	}

	/**
	* Move deque constructor
	* @param d is deque conns reference
	*/
	deque(deque&& d) : head(nullptr), tail(nullptr) {
		head = d.head;
		tail = d.tail;

		d.head = d.tail = nullptr;
	}

	/**
		* Empty deque check
		* @return true if deque is empty, else false
	*/
	bool dqEmpty() const {
		if(head == nullptr)
			return true;
		return false;
	}


	/**
		* Push element to deque head without move semantic
		* @warning Error in memory when add new element
		* @param value is const reference to value
	*/
	void dqPushHead(const elemType& value) {
		elem* newElem = new elem;

		if(!newElem)
			throw std::exception("Error in memory");

		newElem->prev = nullptr;
		newElem->value = value;
		newElem->net = head;

		if(head)
			head->prev = newElem;
		head = newElem;
		if(!tail)
			tail = newElem;
	}

	/**
		* Push element to deque head with move semantic
		* @warning Error in memory when add new element
		* @param value is rValue reference to value
	*/
	void dqPushHead(elemType&& value) {
		elem* newElem = new elem;
		if (!newElem)
			throw std::exception("Error in memory");

		newElem->prev = nullptr;
		newElem->value = std::move(value);
		newElem->next = head;

		if (head)
			head->prev = newElem;
		head = newElem;

		if (!tail)
			tail = newElem;
	}
	
	/**
		* Push element to deque tail without move semantic
		* @warning Error in memory when add new element
		* @param value is const reference to value
	*/
	void dqPushTail(const elemType& value) {
		elem* newElem = new elem;
		if (!newElem)
			throw std::exception("Error in memory");

		newElem->next = nullptr;
		newElem->value = value;
		newElem->prev = tail;

		if(tail)
			tail->next = newElem;
		tail = newElem;

		if(!head)
			head = newElem;
	}

	/**
		* Push element to deque tail with move semantic
		* @warning Error in memory when add new element
		* @param value is rValue reference to value
	*/
	void dqPushTail(elemType&& value) {
		elem* newElem = new elem;
		if (!newElem)
			throw std::exception("Error in memory");

		newElem->next = nullptr;
		newElem->value = std::move(value);
		newElem->prev = tail;

		if (tail)
			tail->next = newElem;
		tail = newElem;

		if (!head)
			head = newElem;
	}
	
	/**
		* Pop element to deque head
		* @warning Empty deque
		* @return value of head element
	*/
	elemType& dqPopHead() {
		if (!head)
			throw std::exception("Empty deque");
		else
			return head->value;
	}

	/**
	* Delete element to deque head
	*/
	void dqDeleteHead() {
		if(!head && !tail)
			return;
		else {
			elem* deleteElem = head;
			head = head->next;
			if(!head)
				tail = nullptr;
			else
				head->prev = nullptr;
			delete(deleteElem);
		}
	}

	/**
		* Pop element to deque tail
		* @warning Empty deque
		* @param value of tail element
	*/
	elemType& dqPopTail() {
		if (!tail)
			throw std::exception("Empty deque");
		else
			return tail->value;
	}

	/**
		* Delete deque tail
	*/
	void dqDeleteTail() {
		if(!head && !tail)
			return;
		else {
			elem* deleteElem = tail;
			tail = tail->prev;
			if(!tail)
				head = nullptr;
			else
				tail->next = nullptr;
			delete(deleteElem);
		}
	}
	/**
	* Union two deque
	* @param d is deque reference deque to union
	*/
	void dqUnion(const deque& d) {
		if (&d == this) {
			deque<elemType> newDeque(d);
			for(dqIterator dqI = newDeque.dqHead() ; dqI != newDeque.dqTail(); dqI.dqNext())
				dqPushTail(dqI.getElem());
			newDeque.dqClear();
		}
		else {
			for (dqIterator dqI = d.dqHead(); dqI != d.dqTail(); dqI.dqNext())
				dqPushTail(dqI.getElem());
		}
	}
	
	/**
	* Union two deque
	* @param d is deque rValue reference deque to union
	*/
	void dqUnion(deque&& d) {
		if (!d.head)
			return;
		else if (!head) {
			head = d.head;
			tail = d.tail;
			d.head = d.tail = nullptr;
		}
		else {
			tail->next = d.head;
			d.head->prev = tail;

			tail = d.tail;
			d.head = d.tail = nullptr;
		}
	}

	/**
	* Equality copy operator
	* @param d is deque const reference to copy
	*/
	deque& operator=(const deque& d) {
		if (&d != this) {
			dqClear();
			head = tail = nullptr;
			for(dqIterator dqI = d.dqHead(); dqI != d.dqTail(); dqI.dqNext())
				dqPushTail(dqI.getElem());
		}
		return *this;
	}

	/**
	* Equality move operator
	* @param d is deque rVlaue reference to copy
	*/
	deque& operator=(deque&& d) {
		dqClear();
		head = tail = nullptr;

		head = d.head;
		tail = d.tail;
		tail = d.tail;

		d.head = d.tail = nullptr;
		return *this;
	}
	
	/**
		* Operator push element to deque head
		* @param value is const reference to value
		* @return deque with new element
	*/
	deque& operator+(const elemType& value) {
		dqPushTail(value);
		return *this;
	}

	/**
		* Operator push element to deque head
		* @param value is rValue reference to value
		* @return deque with new element
	*/
	deque& operator+(elemType&& value) {
		dqPushTail(value);
		return *this;
	}
	/**
	* Operator union two deque
	* @param d is deque const reference deque to union
	*/
	deque& operator+(const deque& d) {
		if (&d == this) {
			deque<elemType> newDeque(d);
			for (dqIterator dqI = newDeque.dqHead(); dqI != newDeque.dqTail(); dqI.dqNext())
				dqPushTail(dqI.getElem());
			newDeque.dqClear();
		}
		else {
			for (dqIterator dqI = d.dqHead(); dqI != d.dqTail(); dqI.dqNext())
				dqPushTail(dqI.getElem());
		}
		return *this;
	}

	/**
	* Operator union two deque
	* @param d is deque rValue reference deque to union
	*/
	deque& operator+(deque&& d) {
		if (!d.head)
			return *this;
		else if (!head) {
			head = d.head;
			tail = d.tail;
			d.head = d.tail = nullptr;
		}
		else {
			tail->next = d.head;
			d.head->prev = tail;

			tail = d.tail;

			d.head = d.tail = nullptr;
		}
		return *this;
	}

	/**
	* Clear deque
	*/
	void dqClear() {
		while(!dqEmpty())
			dqDeleteHead();
	}
	/**
	* Deque destructor
	*/
	~deque() {
		dqClear();
	}
};