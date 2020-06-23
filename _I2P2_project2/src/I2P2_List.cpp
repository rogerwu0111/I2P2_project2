#include "../header/I2P2_List.h"

namespace I2P2 {
  /* Your definition for the List class goes here */
  List::~List(){
    clear();
    delete _head;
  }

  List::List(){
    _head = new Node();
    _head->_next = _head;
    _head->_prev = _head;
    _head->index = 0;
  }

  List::List(const List &rhs){
    _head = new Node;
    Node* curr = _head;
    Node* curr_rhs = (rhs._head)->_next;
    while(curr_rhs != rhs._head){
      curr->_next = new Node(curr_rhs->data, curr_rhs->index);
      curr->_next->_prev = curr;
      curr = curr->_next;
      curr_rhs = curr_rhs->_next;
    }
    curr->_next = _head;
    _head->_prev = curr;

    _head->index = (rhs._head)->index;
  }

  List & List::operator=(const List &rhs){
    clear();
    Node* curr = _head;
    Node* curr_rhs = (rhs._head)->_next;
    while(curr_rhs != rhs._head){
      curr->_next = new Node(curr_rhs->data, curr_rhs->index);
      curr->_next->_prev = curr;
      curr = curr->_next;
      curr_rhs = curr_rhs->_next;
    }
    curr->_next = _head;
    _head->_prev = curr;

    _head->index = (rhs._head)->index;
    return *this;
  }

  iterator List::begin(){return iterator(new list_iterator(_head->_next));}

  const_iterator List::begin() const{return iterator(new list_iterator(_head->_next));}

  iterator List::end(){return iterator(new list_iterator(_head));}

  const_iterator List::end() const{return iterator(new list_iterator(_head));}

  reference List::front(){return _head->_next->data;}

  const_reference List::front() const{return _head->_next->data;}
  
  reference List::back(){return _head->_prev->data;}

  const_reference List::back() const{return _head->_prev->data;}

  size_type List::size() const{return _head->index;}

  void List::clear(){
    Node* curr = _head->_next;
    Node* temp;
    while(curr != _head){
      temp = curr;
      curr = curr->_next;
      delete temp;
    }
    _head->_next = _head;
    _head->_prev = _head;
    _head->index = 0;
  }

  bool List::empty() const{return (_head->index) == 0;}

  void List::erase(const_iterator pos){
    // move data
    Node* curr = find_Node_addr(&(*pos));
    while(curr != _head->_prev){
      curr->data = curr->_next->data;
      curr = curr->_next;
    }

    // delete Node
    Node* pre_head = _head->_prev;
    Node* nex_head = _head->_next;
    pre_head->_next = nex_head;
    nex_head->_prev = pre_head;
    delete _head;
    _head = pre_head;
  }

  void List::erase(const_iterator begin, const_iterator end){
    difference_type offset = end - begin;
    Node* curr1 = find_Node_addr(&(*begin));
    Node* curr2 = find_Node_addr(&(*end));
    // move data
    while(curr2 != _head){
      curr1->data = curr2->data;
      curr1 = curr1->_next;
      curr2 = curr2->_next;
    }
    // delete Node
    Node* nex_head = _head->_next;
    Node* curr = _head;
    Node* temp;
    difference_type i = 0;
    while(i < offset){
      temp = curr;
      curr = curr->_prev;
      delete temp;
      ++i;
    }
    curr->_next = nex_head;
    nex_head->_prev = curr;

    _head = curr;
  }

  void List::insert(const_iterator pos, size_type count, const_reference val){
    Node* _pos = find_Node_addr(&(*pos));
    difference_type number_to_move = (_head->index) - (_pos->index);  
    Node* original_head = _head;
    // increase Node
    Node* nex_head = _head->_next;
    Node* curr = _head;
    difference_type i = 0;
    difference_type idx = _head->index + 1;
    while(i < count){
      curr->_next = new Node;
      curr->_next->index = idx;
      curr->_next->_prev = curr;
      curr = curr->_next;
      ++idx;
      ++i;
    }
    curr->_next = nex_head;
    nex_head->_prev = curr;
    
    _head = curr;
    // move data
    Node* curr1 = _head->_prev;
    Node* curr2 = original_head->_prev;
    i = 0;
    while(i < number_to_move){
      curr1->data = curr2->data;
      curr1 = curr1->_prev;
      curr2 = curr2->_prev;
      i++;
    }
    // insert value
    i = 0;
    while (i < count){
      _pos->data = val;
      _pos = _pos->_next;
      i++;
    }
  }

  void List::insert(const_iterator pos, const_iterator begin, const_iterator end){
    Node* _pos = find_Node_addr(&(*pos));
    difference_type number_to_move = (_head->index) - (_pos->index);
    difference_type number_to_insert = end - begin;
    Node* original_head = _head;
    // increase Node
    Node* nex_head = _head->_next;
    Node* curr = _head;
    difference_type i = 0;
    difference_type idx = _head->index + 1;
    while(i < number_to_insert){
      curr->_next = new Node;
      curr->_next->index = idx;
      curr->_next->_prev = curr;
      curr = curr->_next;
      ++idx;
      ++i;
    }
    curr->_next = nex_head;
    nex_head->_prev = curr;
    
    _head = curr;
    // move data
    Node* curr1 = _head->_prev;
    Node* curr2 = original_head->_prev;
    i = 0;
    while(i < number_to_move){
      curr1->data = curr2->data;
      curr1 = curr1->_prev;
      curr2 = curr2->_prev;
      i++;
    }
    // insert value
    i = 0;
    const_iterator it = begin;
    while(i < number_to_insert){
      _pos->data = *it;
      _pos = _pos->_next;
      ++it;
      ++i;
    }
  }

  void List::pop_back(){
    if (empty()) return;
    Node* pre_head = _head->_prev;
    Node* nex_head = _head->_next;
    pre_head->_next = nex_head;
    nex_head->_prev = pre_head;
    delete _head;
    _head = pre_head;
  }

  void List::pop_front(){
    if (empty()) return;
    // move data
    Node* curr = _head->_next;
    while(curr != _head->_prev){
      curr->data = curr->_next->data;
      curr = curr->_next;
    }
    // delete Node
    Node* pre_head = _head->_prev;
    Node* nex_head = _head->_next;
    pre_head->_next = nex_head;
    nex_head->_prev = pre_head;
    delete _head;
    _head = pre_head;
  }

  void List::push_back(const_reference val){
    Node* nex_head = _head->_next;
    _head->_next = new Node;
    _head->_next->_prev = _head;
    _head->_next->index = _head->index + 1;
    _head->data = val;

    _head = _head->_next;

    _head->_next = nex_head;
    nex_head->_prev = _head;
  }

  void List::push_front(const_reference val){
    // increase Node
    Node* nex_head = _head->_next;
    _head->_next = new Node;
    _head->_next->_prev = _head;
    _head->_next->index = _head->index + 1;

    _head = _head->_next; // set new head

    _head->_next = nex_head;
    nex_head->_prev = _head;
    // move data
    Node* curr = _head->_prev;
    while(curr != _head->_next){
      curr->data = curr->_prev->data;
      curr = curr->_prev;
    }
    // insert data
    _head->_next->data = val;
  }

  Node* List::find_Node_addr(const value_type* data_pt){
    Node* base_pointer = (Node*) 0;
    uintptr_t temp = reinterpret_cast<uintptr_t>(&(base_pointer->data));
    uintptr_t offset = temp - reinterpret_cast<uintptr_t>(base_pointer);
    uintptr_t res = reinterpret_cast<uintptr_t>(data_pt) - offset;
    return reinterpret_cast<Node*>(res);
  }
}  // namespace I2P2
