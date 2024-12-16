#include "linked_list.hpp"
#include <iostream>

/*********************************************************************
** Function: copy constructor
** Description: copies a node to a new node
** Parameters: const linked_list& other, referencing a new node object
** Returns: N/A
** Side-Effects: N/A
********************************************************************/
linked_list::linked_list(const linked_list& other) {
	node* new_node = other.head;
	while(new_node != nullptr) {
		push_back(new_node->val);
		new_node = new_node->next;
	}
}

/*********************************************************************
** Function: assignment operator
** Description: performs a deep copy of a node
** Parameters: const linked_list& other, referencing a new node object
** Returns: N/A
** Side-Effects: N/A
********************************************************************/
void linked_list::operator=(const linked_list& other) {
	if (this == &other) {
		return;
	}

	clear();

	node* new_node = other.head;
	while(new_node != nullptr) {
		push_back(new_node->val);
		new_node = new_node->next;
	}
}

/*********************************************************************
** Function: Destructor
** Description: clears the linked list and deletes memory
** Parameters: N/A
** Returns: N/A
** Side-Effects: Calls the clear function
********************************************************************/
linked_list::~linked_list() {
	clear();
}

/*********************************************************************
** Function: get length
** Description: Loops through the list and keeps a count of the length
** Parameters: N/A
** Returns: count
** Side-Effects: N/A
********************************************************************/
int linked_list::get_length() {
	int count = 0;
	if(head == nullptr) {
		return count;
	}

	node* new_node = head;
	while(new_node != nullptr) {
		count++;
		new_node = new_node->next;
	}
	return count;
}

/*********************************************************************
** Function: print
** Description: prints out the list and its values
** Parameters: N/A
** Returns: N/A
** Side-Effects: calls get length function to loop through
********************************************************************/
void linked_list::print() {
	node* new_node = head;
	length = get_length();

	for(int i = 0; i < length; i++) {
		std::cout << new_node->val << " ";
		new_node = new_node->next;
	}
	std::cout << std::endl;
}

/*********************************************************************
** Function: clear
** Description: loops through and clears each node
** Parameters: N/A
** Returns: N/A
** Side-Effects: calls the pop front function
********************************************************************/
void linked_list::clear() {
	while(head != nullptr) {
		pop_front();
	}
}

/*********************************************************************
** Function: push front
** Description: makes a new node and sets it at the front of the list
** Parameters: 
		value(int): value of the node
** Returns: N/A
** Side-Effects: creates a new node in the heap
********************************************************************/
void linked_list::push_front(int value) {
	node* new_node = new node{value, head};
	head = new_node;
	length++;
}

/*********************************************************************
** Function: push back
** Description: adds a new node at the end of the list
** Parameters: 
		value(int): value of the node
** Returns: N/A
** Side-Effects: creates new memory in the heap and incremnets the length member variable
********************************************************************/
void linked_list::push_back(int value) {
	node* new_node = new node{value, nullptr};
	if(head == nullptr) {
		head = new_node;
	} else {
		node* new_node2 = head;
		while(new_node2->next != nullptr){
			new_node2 = new_node2->next;
		}
		new_node2->next = new_node;
	}
	length++;
}

/*********************************************************************
** Function: insert
** Description:
** Parameters:
		value(int): value of the node
		index(int): an index within the list to insert a value
** Returns: N/A
** Side-Effects: calls the push back and front function
********************************************************************/
void linked_list::insert(int value, int index) {
	if(index < 0 || index > length) {return;}

	if(index == 0) {
		push_front(value);
	} else if(index == length) {
		push_back(value);
	} else {
		node* new_node = new node{value, nullptr};
		node* new_node2 = head;
		for(int i = 0; i < index - 1; i++) {
			new_node2 = new_node2->next;
		}
		new_node->next = new_node2->next;
		new_node2->next = new_node;
		length++;
	}
}

/*********************************************************************
** Function: pop front
** Description: deletes the first node
** Parameters: N/A
** Returns: N/A
** Side-Effects: decrements the length
********************************************************************/
void linked_list::pop_front() {
	if(head != nullptr) {
		node* new_node = head;
		head = head->next;
		delete new_node;
		length--;
	}
	
}

/*********************************************************************
** Function: pop back
** Description: deletes the last node
** Parameters: N/A
** Returns: N/A
** Side-Effects: decrements the length variable
********************************************************************/
void linked_list::pop_back() {
	if(head != nullptr) {
		if(head->next == nullptr) {
			delete head;
			head = nullptr;
		} else {
			node* new_node = head;
			while(new_node->next != nullptr && new_node->next->next != nullptr) {
				new_node = new_node->next;
			}
			delete new_node->next;
			new_node->next = nullptr;
		}
		length--;
	}
}

/*********************************************************************
** Function: remove
** Description: removes a node at an index
** Parameters:
		index(int): an index within the list to insert a value
** Returns: N/A
** Side-Effects: deletes memory and decrements the length
********************************************************************/
void linked_list::remove(int index) {
	if(index < 0 || index > length) {return;}

	if(index == 0) {
		pop_front();
	} else if(index == length) {
		pop_back();
	} else {
		node* new_node = head;
		for(int i = 0; i < index - 1; i++) {
			new_node = new_node->next;
		}
		node* remove_node = new_node->next;
		new_node->next = remove_node->next;
		delete remove_node;
		length--;
	}
}

/*********************************************************************
** Function: sort ascending
** Description: calls the merge function and sorts the list
** Parameters: N/A
** Returns: N/A
** Side-Effects: calls merge function
********************************************************************/
void linked_list::sort_ascending() {
	merge(&head);

}

/*********************************************************************
** Function: sort descending
** Description: calls the mergedown function and sorts the list
** Parameters: N/A
** Returns: N/A
** Side-Effects: calls the mergedown function
********************************************************************/
void linked_list::sort_descending() {
	mergedown(&head);
}

/*********************************************************************
** Function: split
** Description: splits the list into two parts
** Parameters:
	front(node double pointer): pointer to pointer to front half of list
	back(node double pointer): pointer to pointer to back half of list
	head(node pointer): head pointer of original list
** Returns: N/A
** Side-Effects:  N/A
********************************************************************/
void split(node** front, node** back, node* head){
	node* one = head;
	node* two = head->next;

	while(two != nullptr) {
		two = two->next;
		if(two != nullptr) {
			one = one->next;
			two = two->next;
		}
	}
	*front = head;
	*back = one->next;
	one->next = nullptr;
}

/*********************************************************************
** Function: Sort
** Description: sorts the list in ascending order
** Parameters: 
	i(node*): the head of the first linked list
	j(node*): the head of the second linked list
** Returns: N/A
** Side-Effects: N/A
********************************************************************/
node* sort(node* i, node* j){
	node* sorted = nullptr;
	if(i == nullptr){
		return j;
	}
	if(j == nullptr){
		return i;
	}

	if(i->val <= j->val){
		sorted = i;
		sorted->next = sort(i->next, j);
	} else{
		sorted = j;
		sorted->next = sort(i, j->next);
	}
	return sorted;
}

/*********************************************************************
** Function: sortdown
** Description: sorts the list in descending order
** Parameters:
	i(node*): the head of the first linked list
	j(node*): the head of the second linked list
** Returns: N/A
** Side-Effects: N/A
********************************************************************/
node* sortdown(node* i, node* j) {
	node* sorted = nullptr;
	if(i == nullptr){
		return j;
	}
	if(j == nullptr){
		return i;
	}

	if(i->val >= j->val){
		sorted = i;
		sorted->next = sortdown(i->next, j);
	} else{
		sorted = j;
		sorted->next = sortdown(i, j->next);
	}
	return sorted;
}

/*********************************************************************
** Function: Merge
** Description: splits, sorts, and merges the lists
** Parameters:
	header(node**): points to the head of original linked list
** Returns: N/A
** Side-Effects: Calls other functions
********************************************************************/
void merge(node** header) {
	node* head = *header;
	node* i;
	node* j;
	if(head == nullptr || head->next == nullptr){
		return;
	}
	split(&i, &j, head);
	merge(&i);
	merge(&j);
	*header = sort(i, j);
}

/*********************************************************************
** Function: mergedown
** Description: splits, sorts, and merges the lists
** Parameters:
	header(node**): points to the head of original linked list
** Returns: N/A
** Side-Effects: Calls other functions
********************************************************************/
void mergedown(node** header) {
	node* head = *header;
	node* i;
	node* j;
	if(head == nullptr || head->next == nullptr){
		return;
	}
	split(&i, &j, head);
	mergedown(&i);
	mergedown(&j);
	*header = sortdown(i, j);
}