#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>

namespace sjtu {
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
template<typename T>
class vector {
public:
    /**
     * TODO
     * a type for actions of the elements of a vector, and you should write
     *   a class named const_iterator with same interfaces.
     */
    
    /**
     * you can see RandomAccessIterator at CppReference for help.
     */
    class const_iterator;
    class iterator {
    private:
        /**
         * TODO add data members
         *   just add whatever you want.
         */
        T* t;
    public:
        /**
         * return a new iterator which pointer n-next elements
         * as well as operator-
         */
        iterator operator+(const int &n) const {
            //TODO
            iterator iter =*this;
            iter.t+=n;
            return iter;
        }
        iterator operator-(const int &n) const {
            //TODO
            iterator iter =*this;
            iter.t-=n;
            return iter;
        }
        // return the distance between two iterators,
        // if these two iterators point to different vectors, throw invaild_iterator.
        int operator-(const iterator &rhs) const {
            //TODO
            return rhs.t-t;   
        }
        iterator& operator+=(const int &n) {
            return t+=n;
            //TODO
        }
        iterator& operator-=(const int &n) {
            //TODO
            return t-=n;
        }
        /**
         * TODO iter++
         */
        iterator operator++(int) {
            iterator iter=*this;
            t++;
            return iter;
        }
        /**
         * TODO ++iter
         */
        iterator& operator++() {
            t++;
            return *this;
        }
        /**
         * TODO iter--
         */
        iterator operator--(int) {
            iterator iter=*this;
            t--;
            return iter;
        }
        /**
         * TODO --iter
         */
        iterator& operator--() {
            t--;
            return *this;
        }
        /**
         * TODO *it
         */
        T& operator*() const{
            return *t;
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory address).
         */
        bool operator==(const iterator &rhs) const {
            return rhs.t!=t;
        }
        bool operator==(const const_iterator &rhs) const {
            return rhs.t!=t;
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {
            return rhs.t==t;
        }
        bool operator!=(const const_iterator &rhs) const {
            return rhs.t==t;
        }
    };
    /**
     * TODO
     * has same function as iterator, just for a const object.
     */
    class const_iterator {
    private:
        /**
         * TODO add data members
         *   just add whatever you want.
         */
        T* t;
    public:
        /**
         * return a new iterator which pointer n-next elements
         * as well as operator-
         */
        const_iterator operator+(const int &n) const {
            //TODO
            const_iterator iter =*this;
            iter.t+=n;
            return iter;
        }
        const_iterator operator-(const int &n) const {
            //TODO
            const_iterator iter =*this;
            iter.t-=n;
            return iter;
        }
        // return the distance between two iterators,
        // if these two iterators point to different vectors, throw invaild_iterator.
        int operator-(const iterator &rhs) const {
            //TODO
            return rhs.t-t;   
        }
        const_iterator& operator+=(const int &n) {
            return t+=n;
            //TODO
        }
        const_iterator& operator-=(const int &n) {
            //TODO
            return t-=n;
        }
        /**
         * TODO iter++
         */
        const_iterator operator++(int) {
            const_iterator iter=*this;
            t++;
            return iter;
        }
        /**
         * TODO ++iter
         */
        const_iterator& operator++() {
            t++;
            return *this;
        }
        /**
         * TODO iter--
         */
        const_iterator operator--(int) {
            const_iterator iter=*this;
            t--;
            return iter;
        }
        /**
         * TODO --iter
         */
        const_iterator& operator--() {
            t--;
            return *this;
        }
        /**
         * TODO *it
         */
        T& operator*() const{
            return *t;
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory address).
         */
        bool operator==(const iterator &rhs) const {
            return rhs.t!=t;
        }
        bool operator==(const const_iterator &rhs) const {
            return rhs.t!=t;
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {
            return rhs.t==t;
        }
        bool operator!=(const const_iterator &rhs) const {
            return rhs.t==t;
        }
    };
    /**
     * TODO Constructs
     * Atleast two: default constructor, copy constructor
     */
    vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{}
    vector(const vector &other) {
        _start = _finish = new T[other.size()];
		_endofstorage = _start + other.size();
		T* it = other.begin();
		while (_finish != _endofstorage) {
			*_finish = *it;
			_finish++;
			it++;
		}
    }
    /**
     * TODO Destructor
     */
    ~vector() {
        clear();
    }
    /**
     * TODO Assignment operator
     */
    vector &operator=(const vector &other) {
        _start = _finish = new T[other.size()];
		_endofstorage = _start + other.size();
		T* it = other.begin();
		while (_finish != _endofstorage) {
			*_finish = *it;
			_finish++;
			it++;
		}
    }
    /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     */
    T & at(const size_t &pos) {
        if(pos>size()){
            throw std::string("index_out_of_bound");
            return NULL;
        }
        return _start+pos;
    }
    const T & at(const size_t &pos) const {
        f(pos>size()){
            throw std::string("index_out_of_bound");
            return NULL;
        }
        return _start+pos;
    }
    /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     * !!! Pay attentions
     *   In STL this operator does not check the boundary but I want you to do.
     */
    T & operator[](const size_t &pos) {
        return *(_finish + pos);
    }
    const T & operator[](const size_t &pos) const {
        return *(_finish + pos);
    }
    /**
     * access the first element.
     * throw container_is_empty if size == 0
     */
    const T & front() const {
        return _start;
    }
    /**
     * access the last element.
     * throw container_is_empty if size == 0
     */
    const T & back() const {
        return _finish-1;
    }
    /**
     * returns an iterator to the beginning.
     */
    iterator begin() {
        return _start;
        }
    const_iterator cbegin() const {
        return _start;
        }
    /**
     * returns an iterator to the end.
     */
    iterator end() {
        return _finish;
    }
    const_iterator cend() const {
        return _finish;
    }
    /**
     * checks whether the container is empty
     */
    bool empty() const {
        return _start == _finish;
    }
    /**
     * returns the number of elements
     */
    size_t size() const {
        return _finish - _start;
    }
    /**
     * clears the contents
     */
    void clear() {
		if (_start == nullptr) {
			return;
		}
		delete[] _start;
		_start = _endofstorage = _finish = nullptr;
	}
    /**
     * inserts value before pos
     * returns an iterator pointing to the inserted value.
     */
    size_t capacity()const {
			return _endofstorage - _start;
		}
    void reserve(size_t n) {
			size_t oldsize = size();
			if (n <= capacity()) {
				return;
			}
			T* p = new T[n];
			memcpy(p, _start, sizeof(T)*size());
			delete[] _start;
			_start = p;
			_finish = p + oldsize;
			_endofstorage = _start + n;
		}

    iterator insert(iterator pos, const T &value) {
        if (_finish == _endofstorage) {
				reserve(capacity() * 2);
			}
			auto it = _finish();
			while (it != pos) {
				*it = *(it - 1);
				it--;
			}
			*it = value;
			++_finish;
			return pos;
    }
    /**
     * inserts value at index ind.
     * after inserting, this->at(ind) == value
     * returns an iterator pointing to the inserted value.
     * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
     */
    iterator insert(const size_t &ind, const T &value) {
        if(ind>size()){
            throw std::string("index_out_of_bound");
            return NULL;
        }
        if (_finish == _endofstorage) {
				reserve(capacity() * 2);
			}
			auto it = _finish();
			while (it != ind) {
				*it = *(it - 1);
				it--;
			}
            this->at(ind) == value;
			*it = value;
			++_finish;
			return ind;
    }
    /**
     * removes the element at pos.
     * return an iterator pointing to the following element.
     * If the iterator pos refers the last element, the end() iterator is returned.
     */
    iterator erase(iterator pos) {
        auto it = pos;
			while (it != _finish) {
				*it = *(it + 1);
				it++;
			}
			--_finish;
			return pos;
    }
    /**
     * removes the element with index ind.
     * return an iterator pointing to the following element.
     * throw index_out_of_bound if ind >= size
     */
    iterator erase(const size_t &ind) {
        if(ind>=size()){
            throw std::string("index_out_of_bound");
            return NULL;
        }
        auto it = ind;
			while (it != _finish) {
				*it = *(it + 1);
				it++;
			}
			--_finish;
			return ind;
    }
    /**
     * adds an element to the end.
     */
    void push_back(const T &value) {
        if (_finish == _endofstorage) {
				reserve(size() * 2);
			}
			*_finish = value;
			_finish++;
    }
    /**
     * remove the last element from the end.
     * throw container_is_empty if size() == 0
     */
    void pop_back() {
        _finish--;
        if((_finish-1)<=_start)
            throw std::string("index_out_of_bound");
    }
    private:
        T* _start,_finish,_endofstorage;
};


}

#endif