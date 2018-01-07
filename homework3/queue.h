/*
   "It is better to feel good than to feel bad." --Dr. Ray Toal November 2017
   Written by: John Hardy and Jordan Sanders
*/

#include <iostream>

using namespace std;


template<typename T>
class Node {
private:
	T data;
	Node* next;

public:
	explicit Node(const T& d): data(d), next(nullptr) {}

	~Node() { delete next; }

	Node* get_next() {
		return next;
	}

	void change_next(Node* n) {
		next = n;
	}

	T get_data() {
		return data;
	}
};

template<typename T>
class Queue {
public:
	Node<T>* startNode;
	Node<T>* endNode;
	int size;

	friend ostream& operator<< (ostream &os, Queue& q) {
		Node<T>* current = q.get_start_node();
		Node<T>* end = q.get_end_node();
		while (current != nullptr) {
			os << current->get_data();
			if (current != end) {
				os << " ";
			}
			current = current->get_next();
		}
	  return os;
	}

	explicit Queue(): startNode(nullptr), endNode(nullptr), size(0) {}

	//Copy constructor
  Queue(const Queue& q) = delete;

	//Copy assignment operator
  Queue& operator= (const Queue& q) = delete;

	//Move constructor
	Queue(Queue&& other): startNode(other.startNode), endNode(other.endNode), size(other.get_size()) {
		other.startNode = nullptr;
		other.endNode = nullptr;
	}

	//Move assignment operator
	Queue& operator= (Queue&& other) {
		if (&other != this) {
			size = other.size;
			other.size = 0;
			startNode = other.startNode;
			endNode = other.endNode;
			other.startNode = nullptr;
			other.endNode = nullptr;
		}
		return *this;
	}

	//Destructor
	~Queue() {
		while (size != 0) {
			dequeue();
		}
		delete startNode;
		delete endNode;
	}

	void enqueue(const T& value) {
		Node<T>* newNodePointer = new Node<T>(value);
		if (size > 0) {
			endNode->change_next(newNodePointer);
		} else {
			startNode = newNodePointer;
		}
		endNode = newNodePointer;
		size++;
	}

	T dequeue() {
		if (size < 1) {
			throw std::underflow_error("You can't delete from an empty queue... Duh!😞");
		}

		Node<T>* nodeToDelete = startNode;
		T dataToReturn = nodeToDelete->get_data();

		startNode = startNode->get_next();
		nodeToDelete->change_next(nullptr);
		if (size == 1) {
			endNode = nullptr;
		}
		size--;
		delete nodeToDelete;
		return dataToReturn;
	}

	Node<T>* get_start_node() {
		return startNode;
	}

	Node<T>* get_end_node() {
		return endNode;
	}

	int get_size() {
		return size;
	}
};
