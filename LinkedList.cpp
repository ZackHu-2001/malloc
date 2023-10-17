//
// Created by zackHu on 2023/10/16.
//

#include <iostream>
#include "LinkedList.h"

LinkedList::LinkedList() : head(nullptr), length(0) {}

void LinkedList::print() {
    std::string outputString = "";
    outputString.append("Free List [ Size ")
    .append(std::to_string(this->length))
    .append(" ]:");

    Node* tmp = head;
    while (tmp != nullptr) {
        outputString.append(" [ addr:")
                .append(std::to_string(tmp->address))
                .append(" sz:")
                .append(std::to_string(tmp->size))
                .append(" ]");
        tmp = tmp->next;
    }
    std::cout << outputString <<"\n";
}

void LinkedList::addNode(Node *node) {
    if (node == nullptr) {
        return;
    } else {
        if (head == nullptr) {
            head = node;
        } else {
            if (head->address > node->address) {
                node->next = head;
                head = node;
            } else {
                Node* tmp = head;
                while (tmp->next != nullptr) {
                    if (tmp->next->address >= node->address + node->size) {
                        node->next = tmp->next;
                        tmp->next = node;
                        return;
                    }
                    tmp = tmp->next;
                }
                tmp->next = node;
            }
        }
        length += 1;
    }
}

Node* LinkedList::applyWorstFit(int size, int* searchCnt) {
    Node* tmp = head;
    Node* maxSizedNode = nullptr;
    int maxSize = 0;
    while (tmp != nullptr) {
        if (tmp->size > maxSize) {
            maxSizedNode = tmp;
            maxSize = tmp->size;
        }
        tmp = tmp->next;
        *searchCnt += 1;
    }
    if (maxSizedNode != nullptr || size <= maxSize) {
        return maxSizedNode->splitNode(size);
    } else {
        // fail to find a place to allocate
        std::cout << "failed to find a place to fit in\n";
        return nullptr;
    }
}

//
//Node* LinkedList::applyFirstFit(int size, int* searchCnt) {
//    Node* tmp = head;
//    Node* maxSizedNode = nullptr;
//    int maxSize = 0;
//    while (tmp != nullptr) {
//        if (tmp->size > maxSize) {
//            maxSizedNode = tmp;
//            maxSize = tmp->size;
//        }
//        tmp = tmp->next;
//        *searchCnt += 1;
//    }
//    if (maxSizedNode != nullptr || size <= maxSize) {
//        return maxSizedNode->splitNode(size);
//    } else {
//        // fail to find a place to allocate
//        std::cout << "failed to find a place to fit in\n";
//        return nullptr;
//    }
//}
//
//Node* LinkedList::applyBestFit(int size, int* searchCnt) {
//    Node* tmp = head;
//    Node* maxSizedNode = nullptr;
//    int suitableSize = 0;
//    while (tmp != nullptr) {
//        if (tmp->size > size && tmp->size > suitableSize) {
//            maxSizedNode = tmp;
//            suitableSize = tmp->size;
//        }
//        tmp = tmp->next;
//        *searchCnt += 1;
//    }
//    if (maxSizedNode != nullptr || size <= suitableSize) {
//        return maxSizedNode->splitNode(size);
//    } else {
//        // fail to find a place to allocate
//        std::cout << "failed to find a place to fit in\n";
//        return nullptr;
//    }
//}

