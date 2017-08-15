/*
 * LinkedListNode.h
 *
 *  Created on: Jul 13, 2017
 *      Author: garrett
 */

#ifndef SRC_UTILS_LINKED_LIST_LINKEDLISTNODE_H_
#define SRC_UTILS_LINKED_LIST_LINKEDLISTNODE_H_

template<class T>
class LinkedListNode {
	private:
		LinkedListNode<T>*_next;
		T _data;
	public:
		LinkedListNode( );
		LinkedListNode(T data){
			_data = data;
		}
		void next(LinkedListNode<T>* next){
			_next = next;
		}
		LinkedListNode<T>* next(){
			return _next;
		}
		T data(){
			return _data;
		}
		void data(T data){
			_data = data;
		}
};

#endif /* SRC_UTILS_LINKED_LIST_LINKEDLISTNODE_H_ */
