/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DSALIB_H
#define DSA191_A1_DSALIB_H
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class DSAException
{
    int _error;
    string _text;

public:
    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char *text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string &getErrorText() { return _text; }
};

template <class T>
struct L1Item
{
    T data;
    L1Item<T> *pNext;
    L1Item() : pNext(NULL) {}
    L1Item(T &a) : data(a), pNext(NULL) {}
};

template <class T>
class L1List
{
    L1Item<T> *_pHead; // The head pointer of linked list
    size_t _size;      // number of elements in this list
    int idMax;         // maximum id in dataset
public:
    L1List() : _pHead(NULL), _size(0), idMax(-1) {}
    ~L1List();

    void clean();
    bool isEmpty()
    {
        return _pHead == NULL;
    }
    size_t getSize()
    {
        return _size;
    }
    int getIdMax()
    {
        return idMax;
    }
    void setIdMax(int _id)
    {
        if (_id > idMax)
            idMax = _id;
    }

    T &at(int i);         // give the reference to the element i-th in the list
    T &operator[](int i); // give the reference to the element i-th in the list

    bool find(T &a, int &idx); // find an element similar to a in the list. Set the found index to idx, set idx to -1 if failed. Return true if success.
    int insert(int i, T &a);   // insert an element into the list at location i. Return 0 if success, -1 otherwise
    int remove(int i);         // remove an element at position i in the list. Return 0 if success, -1 otherwise.

    int push_back(T &a);  // insert to the end of the list
    int insertHead(T &a); // insert to the beginning of the list

    int removeHead(); // remove the beginning element of the list
    int removeLast(); // remove the last element of the list

    L1Item<T> *getItem(int i); // get an element at position i in the list. Return 0 if success, -1 otherwise

    void reverse();

    void traverse(void (*op)(T &))
    {
        // TODO: Your code goes here
    }
    void traverse(void (*op)(T &, void *), void *pParam)
    {
        // TODO: Your code goes here
    }
};

template <class T>
L1List<T>::~L1List()
{
    this->clean();
}

///  Clear linked list
template <class T>
void L1List<T>::clean()
{
    L1Item<T> *pTmp;
    while (this->_pHead != NULL)
    {
        pTmp = this->_pHead;
        this->_pHead = this->_pHead->pNext;
        delete pTmp;
    }
    this->_size = 0;
}

/// Insert an element into the list at location i
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::insert(int i, T &a)
{
    if (i < 0 || i > this->_size)
        return -1;

    L1Item<T> *pNew, *pPre;
    pNew = new L1Item<T>(a);
    if (pNew == NULL)
        return -1;

    if (_pHead == NULL)
    {
        _pHead = pNew;
        pNew->pNext = NULL;
    }
    else if (i == 0)
    {
        pNew->pNext = _pHead;
        _pHead = pNew;
    }
    else
    {
        pPre = this->_pHead;

        for (int j = 0; j < i - 1; j++)
            pPre = pPre->pNext;

        pNew->pNext = pPre->pNext;
        pPre->pNext = pNew;
    }

    this->_size++;
    return 0;
}

/// Remove an element at position i in the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::remove(int i)
{
    if (i < 0 || i > this->_size)
        return -1;

    L1Item<T> *pDel, *pPre;
    if (i == 0)
    {
        pDel = _pHead;
        _pHead = _pHead->pNext;
    }
    else
    {
        pPre = this->_pHead;

        for (int j = 0; j < i - 1; j++)
            pPre = pPre->pNext;

        pDel = pPre->pNext;
        pPre->pNext = pDel->pNext;
    }

    delete pDel;
    this->_size--;
    return 0;
}

/// Insert item to the end of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::push_back(T &a)
{
    // TODO: Your code goes here
    return this->insert(this->_size, a);
}

/// Insert item to the front of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::insertHead(T &a)
{
    // TODO: Your code goes here
    return this->insert(0, a);
}

/// Remove the first item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeHead()
{
    // TODO: Your code goes here
    return this->remove(0);
}

/// Remove the last item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeLast()
{
    // TODO: Your code goes here
    return this->remove(this->_size);
}

/// Get an element at position i in the list
/// Return 0 if success, -1 otherwise
template <class T>
L1Item<T> *L1List<T>::getItem(int i)
{
    L1Item<T> *dataOut;
    if (i < 0 || i > this->_size)
        return 0;

    L1Item<T> *pCurr;

    if (_pHead == NULL)
    {
        return 0;
    }
    else if (i == 0)
    {
        pCurr = _pHead;
        dataOut = pCurr;
    }
    else
    {
        pCurr = this->_pHead;

        for (int j = 0; j < i - 1; j++)
            pCurr = pCurr->pNext;

        dataOut = pCurr;
    }
    return dataOut;
}

#endif //DSA191_A1_DSALIB_H
