#include "../header/I2P2_iterator.h"

namespace I2P2 {
  /* Your definition for the iterator class goes here */
  /*************************/
  /* class vector_iterator */                                                  
  /*************************/
  vector_iterator::vector_iterator():vector_pt(nullptr){}

  iterator_impl_base & vector_iterator::operator++(){
    vector_pt++;
    return *this;
  }
  
  iterator_impl_base & vector_iterator::operator--(){
    vector_pt--;
    return *this;
  }

  iterator_impl_base & vector_iterator::operator+=(difference_type offset){
    vector_pt += offset;
    return *this;
  }

  iterator_impl_base & vector_iterator::operator-=(difference_type offset){
    vector_pt -= offset;
    return *this;
  }

  bool vector_iterator::operator==(const iterator_impl_base &rhs) const{
    const vector_iterator* temp_pt;
    if (dynamic_cast<const vector_iterator*>(&rhs)){
        temp_pt = dynamic_cast<const vector_iterator*>(&rhs);
        return vector_pt == (temp_pt->vector_pt);
    }
    return 0;
  }

  bool vector_iterator::operator!=(const iterator_impl_base &rhs) const{
    if (*this == rhs) return false;
    else return true;
  }

  bool vector_iterator::operator<(const iterator_impl_base &rhs) const{
    const vector_iterator* temp_pt;
    if (dynamic_cast<const vector_iterator*>(&rhs)){
        temp_pt = dynamic_cast<const vector_iterator*>(&rhs);
        return vector_pt < (temp_pt->vector_pt);
    }
    return 0;
  }

  bool vector_iterator::operator>(const iterator_impl_base &rhs) const{
    if (*this == rhs || *this < rhs) return false;
    else return true;
  }

  bool vector_iterator::operator<=(const iterator_impl_base &rhs) const{
    if (*this > rhs) return false;
    else return true;
  }

  bool vector_iterator::operator>=(const iterator_impl_base &rhs) const{
    if (*this < rhs) return false;
    else return true;
  }

  difference_type vector_iterator::operator-(const iterator_impl_base &rhs) const{
    const vector_iterator* temp_pt;
    if (dynamic_cast<const vector_iterator*>(&rhs)){
        temp_pt = dynamic_cast<const vector_iterator*>(&rhs);
        return vector_pt - (temp_pt->vector_pt);
    }
    return 0;
  }

  pointer vector_iterator::operator->() const{
    return vector_pt;
  }

  reference vector_iterator::operator*() const{
    return *vector_pt;
  }

  reference vector_iterator::operator[](difference_type offset) const{
    return *(vector_pt + offset);
  }

  vector_iterator::vector_iterator(pointer pt):vector_pt(pt){}

  iterator_impl_base* vector_iterator::clone(){return new vector_iterator(vector_pt);}

  /***********************/
  /* class list_iterator */                                                  
  /***********************/
  Node::Node():_next(nullptr), _prev(nullptr){}

  Node::Node(value_type data, difference_type idx):_next(nullptr), _prev(nullptr), data(data), index(idx){}

  list_iterator::list_iterator():list_pt(nullptr){}

  iterator_impl_base & list_iterator::operator++(){
    list_pt = list_pt->_next;
    return *this;
  }

  iterator_impl_base & list_iterator::operator--(){
    list_pt = list_pt->_prev;
    return *this;
  }

  iterator_impl_base & list_iterator::operator+=(difference_type offset){
    int i;
    for (i=0; i<offset; i++){
      list_pt = list_pt->_next;
    }
    return *this;
  }

  iterator_impl_base & list_iterator::operator-=(difference_type offset){
    int i;
    for (i=0; i<offset; i++){
      list_pt = list_pt->_prev;
    }
    return *this;
  }

  bool list_iterator::operator==(const iterator_impl_base &rhs) const{
    const list_iterator* temp_pt;
    if (dynamic_cast<const list_iterator*>(&rhs)){
        temp_pt = dynamic_cast<const list_iterator*>(&rhs);
        return (list_pt == (temp_pt->list_pt));
    }
    return 0;
  }

  bool list_iterator::operator!=(const iterator_impl_base &rhs) const{
    const list_iterator* temp_pt;
    if (dynamic_cast<const list_iterator*>(&rhs)){
        temp_pt = dynamic_cast<const list_iterator*>(&rhs);
        return (list_pt != (temp_pt->list_pt));
    }
    return 0;
  }

  bool list_iterator::operator<(const iterator_impl_base &rhs) const{
    if ((*this) - rhs < 0) return true;
    else return false;
  }

  bool list_iterator::operator>(const iterator_impl_base &rhs) const{
    if ((*this) - rhs > 0) return true;
    else return false;
  }

  bool list_iterator::operator<=(const iterator_impl_base &rhs) const{
    if ((*this) - rhs <= 0) return true;
    else return false;
  }

  bool list_iterator::operator>=(const iterator_impl_base &rhs) const{
    if ((*this) - rhs >= 0) return true;
    else return false;
  }

  difference_type list_iterator::operator-(const iterator_impl_base &rhs) const{
    const list_iterator* temp_pt;
    if (dynamic_cast<const list_iterator*>(&rhs)){
      temp_pt = dynamic_cast<const list_iterator*>(&rhs);
      return (this->list_pt->index) - (temp_pt->list_pt->index);
    }
    return 0;
  }

  pointer list_iterator::operator->() const{
    return &(list_pt->data);
  }

  reference list_iterator::operator*() const{
    return (list_pt->data);
  }

  reference list_iterator::operator[](difference_type offset) const{
    Node* curr = list_pt;
    int i;
    for (i=0; i<offset; i++){
      curr = curr->_next;
    }
    return (curr->data);
  }

  list_iterator::list_iterator(Node* pt):list_pt(pt){}

  iterator_impl_base* list_iterator::clone(){return new list_iterator(list_pt);}

  /************************/
  /* class const_iterator */                                                  
  /************************/
  const_iterator::~const_iterator(){delete p_;}

  const_iterator::const_iterator():p_(nullptr){}

  const_iterator::const_iterator(const const_iterator &rhs){
    p_ = rhs.p_->clone();
  }

  const_iterator::const_iterator(iterator_impl_base *p):p_(p){}

  const_iterator & const_iterator::operator=(const const_iterator &rhs){
    if (p_ == nullptr) delete p_;
    p_ = rhs.p_->clone();
    return *this;
  }

  const_iterator & const_iterator::operator++(){
    ++(*p_);
    return *this;
  }

  const_iterator const_iterator::operator++(int){
    const_iterator* copy = new const_iterator(*this);
    ++(*p_);
    return *copy;
  }

  const_iterator & const_iterator::operator--(){
    --(*p_);
    return *this;
  }

  const_iterator const_iterator::operator--(int){
    const_iterator* copy = new const_iterator(*this);
    --(*p_);
    return *copy;
  }

  const_iterator & const_iterator::operator+=(difference_type offset){
    (*p_) += offset;
    return *this;
  }

  const_iterator const_iterator::operator+(difference_type offset) const{
    const_iterator copy(*this);
    (*(copy.p_)) += offset;
    return copy;
  }

  const_iterator & const_iterator::operator-=(difference_type offset){
    (*p_) -= offset;
    return *this;
  }

  const_iterator const_iterator::operator-(difference_type offset) const{
    const_iterator copy(*this);
    (*(copy.p_)) -= offset;
    return copy;
  }

  difference_type const_iterator::operator-(const const_iterator &rhs) const{
    return (*p_) - (*(rhs.p_));
  }

  const_pointer const_iterator::operator->() const{
    return p_->operator->();
  }

  const_reference const_iterator::operator*() const{
    return p_->operator*();
  }

  const_reference const_iterator::operator[](difference_type offset) const{
    return p_->operator[](offset);
  }

  bool const_iterator::operator==(const const_iterator &rhs) const{
    return (*p_ == *(rhs.p_));
  }

  bool const_iterator::operator!=(const const_iterator &rhs) const{
    return (*p_ != *(rhs.p_));
  }

  bool const_iterator::operator<(const const_iterator &rhs) const{
    return (*p_ < *(rhs.p_));
  }

  bool const_iterator::operator>(const const_iterator &rhs) const{
    return (*p_ > *(rhs.p_));
  }

  bool const_iterator::operator<=(const const_iterator &rhs) const{
    return (*p_ <= *(rhs.p_));
  }

  bool const_iterator::operator>=(const const_iterator &rhs) const{
    return (*p_ >= *(rhs.p_));
  }

  /******************/
  /* class iterator */                                                  
  /******************/
  iterator::iterator():const_iterator(){}

  iterator::iterator(iterator_impl_base *p):const_iterator(p){}

  iterator::iterator(const iterator &rhs):const_iterator(rhs){}

  iterator & iterator::operator++(){
    ++(*p_);
    return *this;
  }

  iterator iterator::operator++(int){
    iterator copy(*this);
    ++(*p_);
    return copy;
  }

  iterator & iterator::operator--(){
    --(*p_);
    return *this;
  }

  iterator iterator::operator--(int){
    iterator copy(*this);
    --(*p_);
    return copy;
  }

  iterator & iterator::operator+=(difference_type offset){
    (*p_) += offset;
    return *this;
  }

  iterator iterator::operator+(difference_type offset) const{
    iterator copy(*this);
    (*(copy.p_)) += offset;
    return copy;
  }

  iterator & iterator::operator-=(difference_type offset){
    (*p_) -= offset;
    return *this;
  }

  iterator iterator::operator-(difference_type offset) const{
    iterator copy(*this);
    (*(copy.p_)) -= offset;
    return copy;
  }

  difference_type iterator::operator-(const iterator &rhs) const{
    return *p_ - *(rhs.p_);
  }

  pointer iterator::operator->() const{
    return p_->operator->();
  }

  reference iterator::operator*() const{
    return p_->operator*();
  }

  reference iterator::operator[](difference_type offset) const{
    return p_->operator[](offset);
  }
}  // namespace I2P2

