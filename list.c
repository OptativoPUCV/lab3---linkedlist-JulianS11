#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List * list = (List *)malloc(sizeof(List));
    assert(list != NULL);
    list->head = list->tail = list->current = NULL;
    return list;
}
/*Programe la funcions void * firstList(List * list) debe retornar el dato del primer nodo de la lista (head) y actualiza el current para que apunte a ese nodo.*/
void * firstList(List * list) {
    if (list->head == NULL) {
        return NULL;
    }
    list->current = list->head;
    return list->head->data;
    
}

/*Programe la funcione void * nextList(List * list) retorna el dato del nodo a continuación del current y actualiza el current para que apunte a ese nodo. */

void * nextList(List * list) {
    if (list->current == NULL){
        return NULL;
    }
    if (list->current->next == NULL){
        return NULL;
    }
    list->current = list->current->next;
    return list->current->data;

}
/*Programe la funcion void * lastList(List * list) retorna el dato del último elemento en la lista y actualiza el current al nodo correspondiente.*/
void * lastList(List * list) {
    if (list->tail == NULL) {
        return NULL;
    }
    list->current = list->tail;
    return list->tail->data;
}
/*Programe la funcion void * prevList(List * list) retorna el dato del nodo anterior a current y actualiza el current para que apunte a ese nodo. */
void * prevList(List * list) {
    if (list->current == NULL){
        return NULL;
    }
    if (list->current->prev == NULL){
        return NULL;
    }
    list->current = list->current->prev;
    return list->current->data;
}
/* Programe la función void pushFront(List * list, void * data), la cual agrega un dato al comienzo de la lista.*/
void pushFront(List * list, void * data) {
    Node * nuevoN = createNode(data);
    if (list->head == NULL){
        list->head = nuevoN;
        list->tail = nuevoN;
    }
    else{
        nuevoN->next = list->head;
        list->head->prev = nuevoN;
        list->head = nuevoN;
    }
  
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node * nuevoN = createNode(data);
    if (list->current == NULL){
        list->head = nuevoN;
        list->tail = nuevoN;
    }
    else{
        nuevoN->next = list->current->next;
        nuevoN->prev = list->current;
        list->current->next = nuevoN;
        if (nuevoN->next != NULL){
            nuevoN->next->prev = nuevoN;
        }
        else{
            list->tail = nuevoN;
        }
    }
  
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

/*Programe la función void* popCurrent(List * list), la cual elimina el nodo que está en la posición del current de la lista enlazada, y además retorna el dato del nodo eliminado.
Además el current debe quedar apuntando al nodo siguiente del eliminado.*/
void * popCurrent(List * list) {
    if (list->current == NULL) {
        return NULL;
    }
    if (list->current->prev == NULL){
        list->head = list->current->next;
    }
    else{
        list->current->prev->next = list->current->next;
    }
  if (list->current->next == NULL){
    list->tail = list->current->prev;
  }
  else{
    list->current->next->prev = list->current->prev;
  }
  void * data = list->current->data;
  free(list->current);
  list->current = NULL;
  return data;
  
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}