//
// Created by Lennard Kittner on 08.03.18.
//

#include "Quicksorter.h"
#include "Node.h"

void Quicksorter::sort(std::vector<int>* a){
    sort(a, 0, (*a).size()-1);
}

void Quicksorter::sort(std::vector<int>* a,int li, int re){
    if (li < re) {
        int k = partition(a, li, re);

        sort(a, li, k - 1);
        sort(a, k + 1, re);
    }
}

int Quicksorter::partition(std::vector<int>* a, int li, int re){
    int pivot = re;
    int j = li-1;

    for (int i = li;i < re;i++) {
        if ((*a)[pivot] >= (*a)[i]) {
            j++;
            int tmp = (*a)[i];
            (*a)[i] = (*a)[j];
            (*a)[j] = tmp;
        }
    }

    int tmp = (*a)[re];
    (*a)[re] = (*a)[j+1];
    (*a)[j+1] = tmp;

    return j+1;
}

void Quicksorter::sort(std::vector<Node*>* a){
    sort(a, 0, a->size()-1);
}

void Quicksorter::sort(std::vector<Node*>* a,int li, int re){
    if (li < re) {
        int k = partition(a, li, re);

        sort(a, li, k - 1);
        sort(a, k + 1, re);
    }
}

int Quicksorter::partition(std::vector<Node*>* a, int li, int re){
    /*
    int pivot = re;
    int j = li-1;

    for (int i = li;i < re;i++) {
        if ((*a)[pivot]->compareTo(*((*a)[i])) >= 0) {
            j++;
            Node* tmp = (*a)[i];
            (*a)[i] = (*a)[j];
            (*a)[j] = tmp;
        }
    }

    Node* tmp = (*a)[re];
    (*a)[re] = (*a)[j+1];
    (*a)[j+1] = tmp;

    return j+1;
     */
}

Quicksorter::~Quicksorter() {}