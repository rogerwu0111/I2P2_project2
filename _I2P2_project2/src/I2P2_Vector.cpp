#include "../header/I2P2_Vector.h"

namespace I2P2 {
  /* Your definition for the Vector class goes here */
  Vector::~Vector(){clear();}

  Vector::Vector():_begin(nullptr), _end(nullptr), _last(nullptr){}

  Vector::Vector(const Vector &rhs){
    if (rhs.capacity() <= 0){
      _begin = _end = _last = nullptr;
      return;
    }
    _begin = new value_type[rhs.capacity()];
    _end = _begin + rhs.capacity();
    _last = _begin + rhs.size();

    difference_type i;
    for (i=0; i<rhs.size(); i++){
      *(_begin + i) = *(rhs._begin + i);
    }
  }

  Vector & Vector::operator=(const Vector &rhs){
    if (_begin != nullptr) delete [] _begin;
    if (rhs.capacity() <= 0){
      _begin = _end = _last = nullptr;
      return *this;
    }
    _begin = new value_type[rhs.capacity()];
    _end = _begin + rhs.capacity();
    _last = _begin + rhs.size();

    difference_type i;
    for (i=0; i<rhs.size(); i++){
      *(_begin + i) = *(rhs._begin + i);
    }
    return *this;
  }

  iterator Vector::begin(){return iterator(new vector_iterator(_begin));}

  const_iterator Vector::begin() const{return const_iterator(new vector_iterator(_begin));}

  iterator Vector::end(){return iterator(new vector_iterator(_last));}

  const_iterator Vector::end() const{return iterator(new vector_iterator(_last));}

  reference Vector::front(){return *_begin;}

  const_reference Vector::front() const{ return *_begin;}

  reference Vector::back(){return *(_last-1);}

  const_reference Vector::back() const{return *(_last-1);}

  reference Vector::operator[](size_type pos){return *(_begin + pos);}

  const_reference Vector::operator[](size_type pos) const{return *(_begin + pos);}

  size_type Vector::capacity() const{return _end-_begin;}

  size_type Vector::size() const{return _last-_begin;}

  void Vector::clear(){
    if (_begin != nullptr) delete [] _begin;
    _begin = nullptr;
    _end = nullptr;
    _last = nullptr;
  }

  bool Vector::empty() const{return (_begin == _last);}

  void Vector::erase(const_iterator pos){
    _last--;
    pointer last = _last; // last points the last element of vector
    pointer it = _begin; // 
    it += (pos - begin()); // it = pos
    for ( ; it != last; ++it){
        *it = *(it+1);
    }
  }

  void Vector::erase(const_iterator begin, const_iterator end){
    difference_type offset = end - begin; // offset is the number of data we delete
    _last -= offset;

    pointer last = _last;
    pointer it = _begin;
    it += (begin - this->begin()); // it = begin
    
    for ( ; it != last; ++it){
      *it = *(it + offset);
    }
  }

  void Vector::insert(const_iterator pos, size_type count, const_reference val){
    if (count <= 0) return;
    difference_type offset = pos - begin();

    if (size() + count > capacity()){
      size_type new_capacity = size() + count;
      new_capacity = (new_capacity+1 > new_capacity*2) ? new_capacity+1 : new_capacity*2;
      reserve(new_capacity);
    }

    pointer _pos = _begin + offset; // _pos = pos

    // move
    pointer it1 = _last-1; // it1 points the last element of vector
    for ( ; it1 != _pos-1; --it1){ // move [_pos, _last-1]
      *(it1 + count) = *it1;
    }

    // insert
    pointer it2 = _pos; // it2 = pos
    for ( ; it2 != _pos + count; ++it2){
      *it2 = val;
    }
    
    _last += count;
  }

  void Vector::insert(const_iterator pos, const_iterator begin, const_iterator end){
    if (end <= begin) return;
    difference_type offset = end - begin;
    pointer temp = new value_type[offset];

    difference_type i;
    for (i=0; i<offset; i++){
      *(temp + i) = *(begin + i);
    }
    difference_type pos_diff = pos - (this->begin());
  
    if (size() + offset > capacity()){
      size_type new_capacity = size() + offset;
      new_capacity = (new_capacity+1 > new_capacity*2) ? new_capacity+1 : new_capacity*2;
      reserve(new_capacity);
    }

    pointer _pos = _begin + pos_diff;  // _pos = pos

    // move
    pointer it1 = _last-1; // it1 points the last element of vector
    for ( ; it1 != _pos-1; --it1){ // move [_pos, _last-1]
      *(it1 + offset) = *it1;
    }

    // insert
    difference_type diff = 0;
    while(diff < offset){
      *(_pos + diff) = *(temp + diff);
      ++diff;
    }

    _last += offset;

    delete [] temp;
  }

  void Vector::pop_back(){
    if (empty()) return;
    _last--;
  }

  void Vector::pop_front(){
    if (empty()) return;
    pointer curr;
    for (curr = _begin; curr != _last-1; ++curr){
      *curr = *(curr+1);
    }
    _last--;
  }

  void Vector::push_back(const_reference val){
    if (size() == capacity()){
      size_type new_capacity = (capacity()+1 > capacity()*2) ? capacity()+1 : capacity()*2;
      reserve(new_capacity);
    }

    *_last = val;
    _last++;
  }

  void Vector::push_front(const_reference val){
    if (size() == capacity()){
      size_type new_capacity = (capacity()+1 > capacity()*2) ? capacity()+1 : capacity()*2;
      reserve(new_capacity);
    }
    pointer curr;
    for (curr = _last; curr != _begin; --curr){
      *curr = *(curr-1);
    }
    *_begin = val;
    _last++;
  }

  void Vector::reserve(size_type new_capacity){
    if (new_capacity <= capacity()) return;
    if (new_capacity <= 0) return;
    pointer _new_begin = new value_type[new_capacity];
    pointer _new_end = _new_begin + new_capacity;
    pointer _new_last = _new_begin + size();

    difference_type offset = 0;

    while(_new_begin + offset != _new_last){
      *(_new_begin + offset) = *(_begin + offset);
      ++offset;
    }

    if (_begin != nullptr) delete [] _begin;
    _begin = _new_begin;
    _end = _new_end;
    _last = _new_last;
  }

  void Vector::shrink_to_fit(){
    if (capacity() == size()) return;
    if (size() <= 0){
      _begin = _end = _last = nullptr;
      return;
    }
    pointer _new_begin = new value_type[size()];
    pointer _new_end = _new_begin + size();
    pointer _new_last = _new_begin + size();

    difference_type offset = 0;
    while (_new_begin + offset != _new_last){
      *(_new_begin + offset) = *(_begin + offset);
      ++offset;
    }

    if (_begin != nullptr) delete [] _begin;
    _begin = _new_begin;
    _end = _new_end;
    _last = _new_last;
  }
}  // namespace I2P2

