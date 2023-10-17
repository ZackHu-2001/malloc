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

    Node* current = head;
    while (current != nullptr) {
//        std::cout << "addr: " << current->address << "\n";
        outputString.append(" [ addr:")
                .append(std::to_string(current->address))
                .append(" sz:")
                .append(std::to_string(current->size))
                .append(" ]");
        current = current->next;
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
                Node* current = head;
                while (current->next != nullptr) {
                    if (current->next->address >= node->address + node->size) {
                        node->next = current->next;
                        current->next = node;
                        return;
                    }
                    current = current->next;
                }
                current->next = node;
            }
        }
        length += 1;
    }
}

Node* LinkedList::applyWorstFit(int size, int* searchCnt) {
    Node* current = head;
    Node* before = nullptr;
    Node* maxSizedNode = nullptr;
    Node* beforeMaxSizedNode = nullptr;
    int maxSize = 0;
    while (current != nullptr) {
        if (current->size > maxSize) {
            maxSizedNode = current;
            beforeMaxSizedNode = before;
            maxSize = current->size;
        }
        before = current;
        current = current->next;
        *searchCnt += 1;
    }
    if (maxSizedNode != nullptr || size <= maxSize) {
        if (size == maxSize) {
            if (beforeMaxSizedNode == nullptr) {
                head = maxSizedNode->next;
            } else {
                beforeMaxSizedNode->next = maxSizedNode->next;
            }
            return maxSizedNode;
        } else {
            return maxSizedNode->splitNode(size);
        }
    } else {
        // fail to find a place to allocate
        std::cout << "failed to find a place to fit in\n";
        return nullptr;
    }
}


Node* LinkedList::applyFirstFit(int size, int* searchCnt) {
    Node* current = head;
    Node* before = nullptr;
    while (current != nullptr) {
        if (current->size >= size) {
            break;
        } else {
            before = current;
            current = current->next;
            *searchCnt += 1;
        }
    }
    if (current != nullptr) {
        if (current->size == size) {
            if (before == nullptr) {
                head = current->next;
            } else {
                before->next = current->next;
            }
            return current;
        } else {
            return current->splitNode(size);
        }
    } else {
        // fail to find a place to allocate
        std::cout << "failed to find a place to fit in\n";
        return nullptr;
    }
}

//Node* LinkedList::applyBestFit(int size, int* searchCnt) {
//    Node* current = head;
//    Node* maxSizedNode = nullptr;
//    int suitableSize = 0;
//    while (current != nullptr) {
//        if (current->size > size && current->size > suitableSize) {
//            maxSizedNode = current;
//            suitableSize = current->size;
//        }
//        current = current->next;
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

