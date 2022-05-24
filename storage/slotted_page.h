#pragma once

#include <string>
#include <utility>
#include <vector>
#include "tuple.h"

#include <iostream>

namespace db {

class Page {
  public:
    // default constructor
    explicit Page();

    // destructor
    ~Page() { free(page_mem_loc); };

    // returns page id
    inline int getPid() const { return page_id; }

    // returns tuple with the given id, returns default (invalid) tuple if id not in page
    Tuple getTuple(std::pair<int, int> tid);

    // returns all tuples in this page
    std::vector<Tuple> getTuples() const;

    // returns whether the tuple can be added to the page
    bool canAddTuple(std::vector<std::string> values, std::vector<int> primary_key);

    // adds tuple to page if space permits
    void addTuple(std::vector<std::string> values, std::vector<int> primary_key);

    // removes tuple with given tid from page, does nothing if id not in page
    void removeTuple(std::pair<int, int> tid);

    // removes tuple from page, does nothing if tuple not in page
    void removeTuple(Tuple t);

    // checks whether page is empty
    bool empty();

    // returns number of tuples in page
    int size() const { return num_tuples - empty_slots.size(); }

  protected:
    static int CURR_PAGE_ID;
    const static int PAGE_SIZE = 4000;

  private:
    Page *page_mem_loc;
    int page_id;
    int num_tuples = 0;
    std::vector<Tuple> slot_array; // TODO: change to vector of Tuple ptrs after implementing pages properly
    std::vector<std::pair<int, size_t>> empty_slots;
    int page_mem_remaining = PAGE_SIZE; // to remove after implementing pages properly
};

}