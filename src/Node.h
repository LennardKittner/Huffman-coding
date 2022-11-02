//
// Created by Lennard Kittner on 10.03.18.
//

#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H


#include <iostream>
#include <memory>

struct Node {
    int count;
    char content;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node(int count, char content) {
        this->count = count;
        this->content = content;
    }

    Node(int count, char content, std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
        this->count = count;
        this->content = content;
        this->left = left;
        this->right = right;
    }

    Node(Node const &node) {
        this->count = node.count;
        this->content = node.content;
        this->left = node.left;
        this->right = node.right;
    }
};


#endif //HUFFMAN_NODE_H
