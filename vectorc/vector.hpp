#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <cassert>
#include <stdio.h>
#include <stdlib.h>

struct MyVectorIterator;

struct MyVector {
    int *mData;
    size_t mSize;
    size_t mCapacity;

    void (*ctor)(MyVector*);
    void (*dtor)(MyVector*);
    size_t (*size)(const MyVector*);
    void (*clear)(MyVector*);
    bool (*empty)(const MyVector*);
    bool (*full)(const MyVector*);
    void (*push_back)(MyVector*, const int &number);
    const int& (*at)(const MyVector*, size_t index);
    MyVectorIterator (*begin)(const MyVector*);
    MyVectorIterator (*end)(const MyVector*);
};


struct MyVectorIterator {
    size_t mIndex;
    const MyVector* mVector;

    void (*inc) (MyVectorIterator*);
    void (*dec) (MyVectorIterator*);
    const int& (*deref)(const MyVectorIterator*);
    bool (*equal)(const MyVectorIterator*, const MyVectorIterator);
};
 

void dtor(MyVector* vector) {
    free(vector->mData);
    vector->mSize = 0;
}

size_t size(const MyVector* vector) {
    return vector->mSize;
}

void clear(MyVector* vector) {
    vector->mSize = 0;
}


bool empty(const MyVector* vector) {
    if(vector->mSize == 0) {
        return true;
    } else {
        return false;
    }
}


bool full(const MyVector* vector) {
    return vector->mSize == vector->mCapacity;
}

void push_back(MyVector* vector, const int &number) {
    if(vector->full(vector)) {
        //double memory size
        vector->mCapacity = vector->mCapacity * 2;
        vector->mData = (int*) realloc(vector->mData, 
                                       sizeof(int) * vector->mCapacity);
    }
    vector->mData[vector->mSize] = number;
    vector->mSize = vector->mSize + 1;
}


const int& at(const MyVector* vector, size_t index) {
   if(index >= vector->mSize) {
        assert(false);//throw arrayOutOfBounds Exception
   } else {
        return vector->mData[index];
   }
}

void inc (MyVectorIterator* iter) {
    iter->mIndex = iter->mIndex + 1;
}

void dec (MyVectorIterator* iter) {
    iter->mIndex = iter->mIndex - 1;
}

const int& deref(const MyVectorIterator* iter) {
    return iter->mVector->at(iter->mVector, iter->mIndex);
}

bool equal(const MyVectorIterator* iter, const MyVectorIterator other) {
    return (iter->mVector == other.mVector && iter->mIndex == other.mIndex);
}

MyVectorIterator getDefaultIter(const MyVector* vector) {
    /* MyVectorIterator *iter = (MyVectorIterator*) malloc(
                              sizeof(MyVectorIterator));
    iter->mVector = vector;
    iter->mIndex = 0;
    iter->inc = inc;
    iter->dec = dec;
    iter->deref = deref;
    iter->equal = equal;
    */
    MyVectorIterator iter;
    iter.mVector = vector;
    iter.mIndex = 0;
    iter.inc = inc;
    iter.dec = dec;
    iter.deref = deref;
    iter.equal = equal;
    return iter; 
}

MyVectorIterator begin(const MyVector* vector) {
    MyVectorIterator iter = getDefaultIter(vector);
    iter.mIndex = 0;
    return iter;
}

MyVectorIterator end(const MyVector* vector) {
    MyVectorIterator iter = getDefaultIter(vector);
    iter.mIndex = vector->mSize;
    return iter;
}

void ctor(MyVector* vector) {
    //assign function pointers
    vector->dtor = dtor;
    vector->size = size;
    vector->clear = clear;
    vector->full = full;
    vector->empty = empty;
    vector->at = at;
    vector->begin = begin;
    vector->end = end;
    vector->push_back = push_back;

    //initialize array
    vector->mSize = 0;
    vector->mCapacity = 10;
    vector->mData = (int*) malloc(sizeof(int) * vector->mCapacity);
}

#endif //MY_VECTOR_H
