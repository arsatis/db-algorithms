#include "tuple.h"

namespace db {

Tuple::Tuple() {
  tuple_id = {-1, -1};
}

Tuple::Tuple(std::pair<int, int> tid, std::vector<std::string> values, std::vector<int> primary_key) {
  this->tuple_id = tid;
  this->values = values;
  this->primary_key = primary_key;
}

Tuple::Tuple(const Tuple &other) {
  tuple_id = other.tuple_id;
  for (auto &val : other.values) {
    values.push_back(val.c_str()); // deep copy of each string
  }
  for (auto &key : other.primary_key) {
    primary_key.push_back(key);
  }
}

bool Tuple::empty() {
  return values.empty();
}

size_t Tuple::size() {
  size_t tup_size = sizeof(tuple_id);
  for (auto &val : values) tup_size += (val.size());
  for (auto &key : primary_key) tup_size += sizeof(int);
  return tup_size;
}

}