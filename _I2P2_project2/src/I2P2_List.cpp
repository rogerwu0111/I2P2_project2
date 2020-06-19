#include "../header/I2P2_List.h"

namespace I2P2 {
  /* Your definition for the List class goes here */
  List::~List(){
    clear();
    delete _head;
  }

  List::List():_size(0){
    _head = new Node();
    _head->_next = _head;
    _head->_prev = _head;
    _head->Is_head = true;
  }

  List::List(const List &rhs){
    Node* curr = _head;
    Node*curr_rhs = (rhs._head)->_next;
    while(curr_rhs != rhs._head){
      curr->_next = new Node(curr_rhs->data);
      curr->_next->_prev = curr;
      curr = curr->_next;
      curr_rhs = curr_rhs->_next;
    }
    curr->_next = _head;
    _head->_prev = curr;

    _size = rhs._size;
  }

  List & List::operator=(const List &rhs){return *(new List(rhs));}

  iterator List::begin(){return iterator(new list_iterator(_head->_next));}

  const_iterator List::begin() const{return iterator(new list_iterator(_head->_next));}

  iterator List::end(){return iterator(new list_iterator(_head));}

  const_iterator List::end() const{return iterator(new list_iterator(_head));}

  reference List::front(){return _head->_next->data;}

  const_reference List::front() const{return _head->_next->data;}
  
  reference List::back(){return _head->_prev->data;}

  const_reference List::back() const{return _head->_prev->data;}

  size_type List::size() const{return _size;}

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
    _size = 0;
  }

  bool List::empty() const{return (_size == 0);}

  void List::erase(const_iterator pos){
    Node* curr = find_Node_addr(&(*pos));
    Node* pre = curr->_prev;
    Node* nex = curr->_next;
    pre->_next = nex;
    nex->_prev = pre;
    delete curr;
    _size--;
  }

  void List::erase(const_iterator begin, const_iterator end){
    Node* curr = find_Node_addr(&(*begin));
    Node* end_node = find_Node_addr(&(*end));
    Node* pre_begin = curr->_prev;
    Node* temp;
    while(curr != end_node){
      temp = curr;
      curr = curr->_next;
      delete temp;
      _size--;
    }
    pre_begin->_next = end_node;
    end_node->_prev = pre_begin;
  }

  void List::insert(const_iterator pos, size_type count, const_reference val){
    Node* curr = find_Node_addr(&(*pos));
    curr = curr->_prev;
    Node* nex_curr = curr->_next;
    size_type i;
    for (i=0; i<count; i++){
      curr->_next = new Node(val);
      curr->_next->_prev = curr;
      curr = curr->_next;
    }
    curr->_next = nex_curr;
    nex_curr->_prev = curr;

    _size += count;
  }

  void List::insert(const_iterator pos, const_iterator begin, const_iterator end){
    Node* curr = find_Node_addr(&(*pos));
    curr = curr->_prev;
    Node* nex_curr = curr->_next;
    difference_type offset = end - begin;
    const_iterator it = begin;
    while(it != end){
      curr->_next = new Node(*(it));
      curr->_next->_prev = curr;
      curr = curr->_next;
      ++it;
    }
    curr->_next = nex_curr;
    nex_curr->_prev = curr;

    _size += offset;
  }

  void List::pop_back(){
    if (empty()) return;
    Node* pre_head = _head->_prev;
    Node* pre_pre_head = pre_head->_prev;
    delete pre_head;
    pre_pre_head->_next = _head;
    _head->_prev = pre_pre_head;

    _size--;
  }

  void List::pop_front(){
    if (empty()) return;
    Node* nex_head = _head->_next;
    Node* nex_nex_head = nex_head->_next;
    delete nex_head;
    nex_nex_head->_prev = _head;
    _head->_next = nex_nex_head;

    _size--;
  }

  void List::push_back(const_reference val){
    Node* pre = _head->_prev;
    Node* curr = new Node(val);
    curr->_prev = pre;
    pre->_next = curr;

    curr->_next = _head;
    _head->_prev = curr;

    _size++;
  }

  void List::push_front(const_reference val){
    Node* nex = _head->_next;
    Node* curr = new Node(val);
    curr->_prev = _head;
    _head->_next = curr;

    curr->_next = nex;
    nex->_prev = curr;

    _size++;
  }

  Node* List::find_Node_addr(const value_type* data_pt){
    Node* base_pointer = (Node*) 0;
    uintptr_t temp = reinterpret_cast<uintptr_t>(&(base_pointer->data));
    uintptr_t offset = temp - reinterpret_cast<uintptr_t>(base_pointer);
    uintptr_t res = reinterpret_cast<uintptr_t>(data_pt) - offset;
    return reinterpret_cast<Node*>(res);
  }
}  // namespace I2P2
