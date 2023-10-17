//
// Created by zackHu on 2023/10/16.
//

#ifndef MALLOC_LINKEDLIST_H
#define MALLOC_LINKEDLIST_H

#include <string>

struct Node {
    int address;
    int size;
    Node* next;
    Node(int address, int size) : address(address), size(size) {}

    Node* splitNode(int size) {
        if (size == this->size) {
            return this;
        } else {
            auto* newNode = new Node(this->address, size);
            newNode->next = this;
            this->address = this->address + size;
            this->size = this->size - size;
            return newNode;
        }
    }
};

class LinkedList {
public:
    Node* head;
    int length;
    LinkedList();
    void addNode(Node* node);
    void print();
    Node* applyWorstFit(int size, int* searchCnt);

};


#endif //MALLOC_LINKEDLIST_H
