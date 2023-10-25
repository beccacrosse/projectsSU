#include "LeapfrogHashTable.h"
#include "GUI/SimpleTest.h"
using namespace std;


LeapfrogHashTable::LeapfrogHashTable(HashFunction<string> hashFn) {
    /* TODO: Delete this comment and the line below it, then implement this function.
    (void) hashFn; */
    elems = new Slot[hashFn.numSlots()];
    ourHash = hashFn;
    totalSize = hashFn.numSlots();
    logicalSize = 0;
    for(int i = 0; i < totalSize; i++ ){
        elems[i].link = NOT_LINKED;
        elems[i].type = SlotType::EMPTY;
    }

}

LeapfrogHashTable::~LeapfrogHashTable() {
    delete  [] elems;
}

bool LeapfrogHashTable::contains(const string& key) const {
    /* TODO: Delete this comment and the lines below it, then implement this function.
    (void) key;
    return false;*/
    //find inital location of element
    int index = ourHash(key);
    //if found return true;
    if(elems[index].value == key)
        return true;
    //otherwise check each link until there are no more links
    int checked = 0;
    while(elems[index %  totalSize].link != NOT_LINKED || checked >= totalSize){
        index = elems[index %  totalSize].link;
        //if elem is found at a linkd location return true
        if(elems[index].value == key){
            return true;
        }
        checked ++;
    }
    //if element not found after search is completed return false
    return false;
}

bool LeapfrogHashTable::insert(const string& key) {
    /* TODO: Delete this comment and the lines below it, then implement this function.
    (void) key;
    return false;*/
    if(contains(key) || logicalSize == totalSize)
        return false;
    //find inital location of element
    int index = ourHash(key);
    int checked = 0;
    while(elems[index %  totalSize].link != NOT_LINKED || checked >= totalSize){
        index = elems[index %  totalSize].link;
        //if elem is found at a linkd location return true
        if(elems[index].value == key){
            return true;
        }
        checked ++;
    }
    //variable keeps track of value outside of last linked value
    int index2 = index;
    while(true){
        //moves index to next slot
        index2 ++;
        if(elems[index2 % totalSize].type == SlotType::EMPTY){
            //key's location linked to last linked location
            elems[index].link = index2;
            //key's slot becomes unlinked
            elems[index2].link = NOT_LINKED;
            //update logical size
            logicalSize ++;
            //return true that it is possible to insert
            return true;
        }
    }
    //there was no space
    return false;
}

int LeapfrogHashTable::size() const {
    return logicalSize;
}

bool LeapfrogHashTable::isEmpty() const {
    /* TODO: Delete this comment and the line below it, then implement this function. */
    return size() == 0;
}

void LeapfrogHashTable::printDebugInfo() const {
    /* TODO: Delete this comment, then optionally add code to this function. */
}

/* Space for test cases. You are not required to write any test cases, but you
 * are encouraged to do so because our test coverage is not as extensive as what
 * you saw in Assignment 7.
 */
