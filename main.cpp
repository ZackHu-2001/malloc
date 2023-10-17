#include <iostream>
#include <vector>
#include <map>
#include "LinkedList.h"


void printMap(std::map<int, Node*> map) {
    for (const auto& entry : map) {
        std::cout << entry.first << ": addr " << entry.second->address << std::endl;
    }
}

int main() {
    int baseAddr = 1000;
    int heapSize = 100;
//    int allocs[] = {1,2,3,4,5,6,-0,-1,-2,-3,-4,-5};
    int allocs[] = {1,0,2,-1,3,-2,4,-3,5,-4,6,-5};

    Node firstNode = Node(baseAddr, heapSize);

    LinkedList* linkedList = new LinkedList();
    linkedList->addNode(&firstNode);

    std::map<int, Node*> mallocedMap;

    int allocCnt = 0;
    for (int i: allocs) {
        if (i > 0) {
            int searchCnt = 0;
            Node* tmp = linkedList->applyWorstFit(i, &searchCnt);
            mallocedMap[allocCnt] = tmp;
            std::cout << "ptr[" << allocCnt << "] = Alloc(" << i <<") returned " << tmp->address;
            std::cout << " (searched " << searchCnt << " elements)\n";
            allocCnt += 1;
        } else {
            auto it = mallocedMap.find(-i);
            if (it != mallocedMap.end()) {
                Node* tmp = (Node*) mallocedMap[-i];
                tmp->next = nullptr;
                linkedList->addNode(tmp);
                mallocedMap.erase(it);
                std::cout << "Free(ptr[" << -i << "])\n";
            } else {
                std::cout << "Failed to free ptr[" << -i <<"]\n";
            }
        }

        linkedList->print();
        std::cout << "\n";
    }

}

