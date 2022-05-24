#pragma once

#include <string>
#include <utility>
#include <vector>

namespace db {

class Tuple {
  friend class Page;

  public:
    // copy constructor
    Tuple(const Tuple &other);

    // destructor
    ~Tuple() = default;

    // returns tuple id
    inline std::pair<int, int> getTid() const { return tuple_id; }

    // returns tuple data
    inline std::vector<std::string> getValues() const { return values; }

    // checks whether tuple is empty
    bool empty();

    // returns tuple size
    size_t size();

  protected:
    // default constructor (for dummy tuples)
    Tuple();

    // parameterized constructor
    explicit Tuple(std::pair<int, int> tid, std::vector<std::string> values, std::vector<int> primary_key);

  private:
    std::pair<int, int> tuple_id;
    std::vector<std::string> values;
    std::vector<int> primary_key;
};

}