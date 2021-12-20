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
    T *array;
    size_t vsize;
    size_t capacity;
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
        int pos;
    public:
        /**
         * return a new iterator which pointer n-next elements
         * as well as operator-
         */
        iterator(T *t0,int pos0):t(t0),pos(pos0){}
        iterator operator+(const int &n) const {
            //TODO
            iterator iter(t,pos);
            iter.pos+=n;
            return iter;
        }
        iterator operator-(const int &n) const {
            //TODO
            iterator iter(t,pos);
            iter.pos-=n;
            return iter;
        }
        // return the distance between two iterators,
        // if these two iterators point to different vectors, throw invaild_iterator.
        int operator-(const iterator &rhs) const {
            //TODO
            if(this->t!=rhs.t){
                throw invalid_iterator();
            }
            else{
                return rhs.pos-this->pos;
            }  
        }
        iterator& operator+=(const int &n) {
            //TODO
            this->pos+=n;
            return *this;
        }
        iterator& operator-=(const int &n) {
            //TODO
            this->pos-=n;
            return *this;
        }
        /**
         * TODO iter++
         */
        iterator operator++(int) {
            iterator iter(t,pos);
            this->pos++;
            return iter;
        }
        /**
         * TODO ++iter
         */
        iterator& operator++() {
            this->pos++;
            return *this;
        }
        /**
         * TODO iter--
         */
        iterator operator--(int) {
            iterator iter(t,pos);
            this->pos--;
            return iter;
        }
        /**
         * TODO --iter
         */
        iterator& operator--() {
            this->pos--;
            return *this;
        }
        /**
         * TODO *it
         */
        T& operator*() const{
            return t[pos];
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory address).
         */
        bool operator==(const iterator &rhs) const {
            return t==rhs.t&&pos==rhs.pos;
            }
        bool operator==(const const_iterator &rhs) const {
            return t==rhs.t&&pos==rhs.pos;
            }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {
            return t!=rhs.t||pos!=rhs.pos;
            }
        bool operator!=(const const_iterator &rhs) const {
            return t!=rhs.t||pos!=rhs.pos;
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
        int pos;
    public:
        /**
         * return a new iterator which pointer n-next elements
         * as well as operator-
         */
        const_iterator(T *t0,int pos0):t(t0),pos(pos0){}
        const_iterator operator+(const int &n) const {
            //TODO
            const_iterator iter(t,pos);
            iter.pos+=n;
            return iter;
        }
        const_iterator operator-(const int &n) const {
            //TODO
            const_iterator iter(t,pos);
            iter.pos-=n;
            return iter;
        }
        // return the distance between two iterators,
        // if these two iterators point to different vectors, throw invaild_iterator.
        int operator-(const const_iterator &rhs) const {
            //TODO
            if(t!=rhs.t){
                throw invalid_iterator();
            }
            else{
                return rhs.pos-pos;
            }  
        }
        const_iterator& operator+=(const int &n) {
            //TODO
            this->pos+=n;
            return *this;
        }
        const_iterator& operator-=(const int &n) {
            //TODO
            this->pos-=n;
            return *this;
        }
        /**
         * TODO iter++
         */
        const_iterator operator++(int) {
            const_iterator iter(t,pos);
            pos++;
            return iter;
        }
        /**
         * TODO ++iter
         */
        const_iterator& operator++() {
            this->pos++;
            return *this;
        }
        /**
         * TODO iter--
         */
        const_iterator operator--(int) {
            const_iterator iter(t,pos);
            pos--;
            return iter;
        }
        /**
         * TODO --iter
         */
        const_iterator& operator--() {
            this->pos--;
            return *this;
        }
        /**
         * TODO *it
         */
        T& operator*() const{
            return t[pos];
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory address).
         */
        bool operator==(const iterator &rhs) const {
            return t==rhs.t&&pos==rhs.pos;
            }
        bool operator==(const const_iterator &rhs) const {
            return t==rhs.t&&pos==rhs.pos;
            }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {
            return t!=rhs.t||pos!=rhs.pos;
            }
        bool operator!=(const const_iterator &rhs) const {
            return t!=rhs.t||pos!=rhs.pos;
            }
    };
    /**
     * TODO Constructs
     * Atleast two: default constructor, copy constructor
     */
    vector(){
        vsize=0,capacity=10;
        array=(T*)malloc(capacity*sizeof(T));
    }
    vector(const vector &other){
        vsize=other.vsize,capacity=other.capacity;
        array=(T*)malloc(capacity*sizeof(T));
        for(size_t i=0;i<vsize;i++) 
            array[i]=other.array[i];
    }
    /**
     * TODO Destructor
     */
    ~vector(){
        clear();
    }
    /**
     * TODO Assignment operator
     */
    vector &operator=(const vector &other){
        if(this==&other) 
            return *this;
        clear();
        array=(T*)malloc(other.capacity*sizeof(T));
        vsize=other.vsize,capacity=other.capacity;
        for(size_t i=0;i<vsize;i++) 
            array[i]=other.array[i];
        return *this;
    }
    /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     */
    T & at(const size_t &pos){
        if(pos>=vsize||pos<0) 
            throw index_out_of_bound();
        else return array[pos];
    }
    const T & at(const size_t &pos) const {
        if(pos>=vsize||pos<0) 
            throw index_out_of_bound();
        else return array[pos];
    }
    /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     * !!! Pay attentions
     *   In STL this operator does not check the boundary but I want you to do.
     */
    T & operator[](const size_t &pos) {
        if(pos>=vsize||pos<0) 
            throw index_out_of_bound();
        else return array[pos];
    }
    const T & operator[](const size_t &pos) const {
        if(pos>=vsize||pos<0) 
            throw index_out_of_bound();
        else return array[pos];
    }
    /**
     * access the first element.
     * throw container_is_empty if size == 0
     */
    const T & front() const {
        if(vsize==0) 
            throw container_is_empty();
        else return array[0];
    }
    /**
     * access the last element.
     * throw container_is_empty if size == 0
     */
    const T & back() const {
        if(vsize==0) 
            throw container_is_empty();
        else return array[vsize-1];
    }
    /**
     * returns an iterator to the beginning.
     */
    iterator begin() {
        iterator iter(array,0);
        return iter;
        }
    const_iterator cbegin() const {
        const_iterator iter(array,0);
        return iter;
        }
    /**
     * returns an iterator to the end.
     */
    iterator end() {
        iterator iter(array,vsize);
        return iter;
    }
    const_iterator cend() const {
        const_iterator iter(array,vsize);
        return iter;
    }
    /**
     * checks whether the container is empty
     */
    bool empty() const {
        if(vsize==0) return 1;
        else return 0;
    }
    /**
     * returns the number of elements
     */
    size_t size() const {
        return vsize;
    }
    /**
     * clears the contents
     */
    void clear() {
		for(size_t i=0;i<vsize;i++) 
            array[i].~T();
        free(array);
	}
    /**
     * inserts value before pos
     * returns an iterator pointing to the inserted value.
     */
    void ds(){
        T *tmp;
        tmp=array,capacity*=2;
        array=(T*)malloc(capacity*sizeof(T));
        for(size_t i=0;i<vsize;i++){
            //array[i]=tmp[i];
            new(&array[i]) T(tmp[i]);
            //tmp[i].~T();
        }
        free(tmp);
    }
    iterator insert(iterator pos, const T &value) {
        if(vsize+1>=capacity) 
            ds();
        size_t i;
        for(i=vsize;i>=0;i--){
            iterator iter(array,i);
            if(pos==iter) 
                break;
            array[i]=array[i-1];
        }
        array[i]=value,vsize++;
        iterator iter(array,i);
        return iter;
    }
    /**
     * inserts value at index ind.
     * after inserting, this->at(ind) == value
     * returns an iterator pointing to the inserted value.
     * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
     */
    iterator insert(const size_t &ind, const T &value) {
        if(ind>vsize) 
            throw index_out_of_bound();
        if(vsize+1>=capacity) 
            ds();
        for(size_t i=vsize;i>ind;i--) 
            array[i]=array[i-1];
        array[ind]=value,vsize++;
        iterator iter(array,ind);
        return iter;
    }
    /**
     * removes the element at pos.
     * return an iterator pointing to the following element.
     * If the iterator pos refers the last element, the end() iterator is returned.
     */
    iterator erase(iterator pos) {
        size_t k=--vsize;
        for(k=vsize;k>=0;k--){
            iterator iter(array,k);
            if(iter==pos) break;
        }
        for(size_t i=k;i<vsize;i++) 
            array[i]=array[i+1];
        array[vsize].~T();
        if(k==vsize) 
            return end();
        iterator iter(array,k);
        return iter;
    }
    /**
     * removes the element with index ind.
     * return an iterator pointing to the following element.
     * throw index_out_of_bound if ind >= size
     */
    iterator erase(const size_t &ind) {
        if(ind>=vsize) 
            throw index_out_of_bound();
        for(size_t i=ind;i<vsize-1;i++) 
            array[i]=array[i+1];
        array[--vsize].~T();
        if(ind==vsize-1) 
            return end();
        iterator iter(array,ind);
        return iter;
    }
    /**
     * adds an element to the end.
     */
    void push_back(const T &value) {
        if(vsize+1>=capacity) 
            ds();
        new(&array[vsize]) T(value);
        vsize++;
        //array[vsize]=value,vsize++;
    }
    /**
     * remove the last element from the end.
     * throw container_is_empty if size() == 0
     */
    void pop_back() {
        if(vsize==0) 
            throw container_is_empty();
        vsize-=1;
        array[vsize].~T();
    }
};///


}

#endif