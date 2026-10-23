#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include "string.h"
template <typename T>
class BinaryTree{
  private:
    BinaryTree<T> *leftNode;
    BinaryTree<T>* rightNode;
    T* pData;
  public:
    void insert(const char* code, const T& value);
    const T* find(const char*code) const;
    BinaryTree();
    ~BinaryTree();
};

template <typename T>
BinaryTree<T>::BinaryTree():leftNode(nullptr),rightNode(nullptr),
pData(nullptr){}

template <typename T>
BinaryTree<T>::~BinaryTree(){
  delete leftNode;
  delete rightNode;
  delete pData;
}

template <typename T>
void BinaryTree<T>::insert(const char* code, const T& value){
    BinaryTree<T>* node = this;
    
    for(size_t i = 0;  i < strlen(code); i++){
      if(code[i] == '.')
      {
        if(node->leftNode == nullptr)
          node->leftNode = new BinaryTree<T>();
        node = node->leftNode;
      }
      else if(code[i] == '-')
      {
        if(node->rightNode == nullptr)
          node->rightNode = new BinaryTree<T>();
        node = node->rightNode;
      }
      else{
       // Serial.print("Cod invalid\n");
        return;
      }
    }
    delete node->pData;
    node->pData = new T(value);
}

template <typename T>
const T* BinaryTree<T>::find(const char*code) const{
  const BinaryTree<T>* node = this;
  for(size_t i = 0; i < strlen(code); i++){
    if(code[i] == '.')
    {
      if(node->leftNode == nullptr){
        return nullptr;
      }
      else{
        node = node->leftNode;
      }
    }
    else{
      if(node->rightNode == nullptr){
        return nullptr;
      }
      else{
        node = node->rightNode;
      }
    }
  }

  return node->pData;
}


#endif
