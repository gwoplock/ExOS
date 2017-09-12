/*
 * LinkedList.h
 *
 *  Created on: Jul 13, 2017
 *      Author: garrett
 */

#ifndef SRC_UTILS_LINKEDLIST_H_
#define SRC_UTILS_LINKEDLIST_H_

#include "Global.h"
#include "utils/linked_list/LinkedListNode.h"

template<class T>
class LinkedList {
	private:
		LinkedListNode<T>* _head;
		LinkedListNode<T>* _tail;
	public:
		LinkedList( ){
			_head =nullptr;
		}
		T operator [](size_t index){
			LinkedListNode<T>* node = _head;
			for (size_t i = 0; i < index; i++){
				node->next();
			}
			return node;
		}
		void add(T toAdd){
			add(new LinkedListNode<T>(toAdd));
		}
		void add(LinkedListNode<T>* toAdd){
			if(_head == nullptr){
				_head = toAdd;
				_tail = toAdd;
			}else{
				_tail->next(toAdd);
			}

		}
		auto head(){
			return _head;
		}
		//TODO delete
};

#endif /* SRC_UTILS_LINKEDLIST_H_ */
