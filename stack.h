#include "hashmap.h"

struct hashNode{
  struct hashmap data;
  struct hashNode* next;
};

void push(struct hashNode **top, struct hashmap dataIn){
  struct hashNode* node = (struct hashNode*)malloc(sizeof(struct hashNode));
  node->data = dataIn;
  node->next = *top;
  *top = node;
}

struct hashmap peek(struct hashNode *top){
  return top->data;
}

void pop(struct hashNode **top){
  struct hashNode *node = *top;
  *top = (*top)->next;
  free(node);
}