#include <iostream>
#include "BinarySearchTree.h"

void testBinarySearchTree() {
    BinarySearchTree<int> bst;

    bst.insert(4);
    bst.insert(2);
    bst.insert(8);
    bst.insert(5);
    bst.insert(1);
    bst.insert(7);
    bst.insert(6);
    bst.insert(10);
    bst.insert(11);
    bst.printTree();
    BinarySearchTree<int> bst_1 = bst;
    BinarySearchTree<int> bst_2 = bst;
    BinarySearchTree<int> bst_3 = bst;
    BinarySearchTree<int> bst_4 = bst;
    BinarySearchTree<int> bst_5 = bst;
    BinarySearchTree<int> bst_6;
    // 测试删除功能 
    std::cout << "Delete a node with no child : " << std::endl;
    bst_1.remove(1);
    bst_1.printTree();

    std::cout << "Delete a node with a left child : " << std::endl;
    bst_2.remove(2);
    bst_2.printTree();

    std::cout << "Delete a node with a right child : " << std::endl;
    bst_3.remove(10);
    bst_3.printTree();

    std::cout << "Delete a node with both right and left child : "<< std::endl;
    bst_4.remove(8);
    bst_4.printTree();
    std::cout << "Delete a node twice : "<< std::endl;
    bst_4.remove(8);
    bst_4.printTree();

    std::cout << "Delete a nonexisting node : "<< std::endl;
    bst.remove(111);
    bst.printTree();
    
    std::cout << "Delete a root node : "<< std::endl;
    bst_5.remove(4);
    bst_5.printTree();
    
    std::cout << "Delete a node of an empty tree : " << std::endl;
    std::cout << "Before deletion : " << std::endl;
    bst_6.printTree();
    std::cout << "After deletion : " << std::endl;
    bst_6.remove(1);
    bst_6.printTree();
}
int main() {
    testBinarySearchTree();
    return 0;
}