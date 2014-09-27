#include "vector.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <cassert>

int main() {
    //MyVector *myVector = (MyVector*) malloc(sizeof(MyVector));

    MyVector myVec2;
    ctor(&myVec2);

    assert(myVec2.size(&myVec2) == 0);
    assert(myVec2.empty(&myVec2) == true);

    const int size = 20;
    for(int i = 0; i < size; i++) {
        myVec2.push_back(&myVec2, i);
    }

    assert(myVec2.size(&myVec2) == size);
 
    for(int i = 0; i < size; i++) {
        assert(myVec2.at(&myVec2, i) == i);
    }

{
    int j = 0;
    for(MyVectorIterator iter = myVec2.begin(&myVec2); 
        !iter.equal(&iter, myVec2.end(&myVec2)); iter.inc(&iter)) {
        assert(iter.deref(&iter) == j);
        ++j;
    }
}

{
    MyVectorIterator iter = myVec2.end(&myVec2);
    iter.dec(&iter);
    int j = myVec2.size(&myVec2) - 1;
    do {
        assert(iter.deref(&iter) == j);
        --j;
        iter.dec(&iter);
    } while(!iter.equal(&iter, myVec2.begin(&myVec2)));
}

    assert(myVec2.empty(&myVec2) == false);
    myVec2.dtor(&myVec2);
    return 0;
}

