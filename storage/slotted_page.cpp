#include "slotted_page.h"

namespace db {

int Page::CURR_PAGE_ID = 0;

Page::Page() {
  page_mem_loc = (Page*) malloc(PAGE_SIZE);
  page_id = CURR_PAGE_ID++;
}

Tuple Page::getTuple(std::pair<int, int> tid) {
  // check if tuple is not within this page
  if (tid.first != page_id || tid.second >= num_tuples) return Tuple();

  // return tuple using slot array
  return slot_array[tid.second];
}

std::vector<Tuple> Page::getTuples() const {
  return slot_array;
}

bool Page::canAddTuple(std::vector<std::string> values, std::vector<int> primary_key) {
  size_t tup_size = 2 * sizeof(int);
  for (auto &val : values) tup_size += (val.size());
  for (auto &key : primary_key) tup_size += sizeof(int);
  return page_mem_remaining >= tup_size;
}

void Page::addTuple(std::vector<std::string> values, std::vector<int> primary_key) {
  // generate tuple id = (page_id, slot_arr_idx)
  std::pair<int, int> tid = {page_id, num_tuples++};

  // compute tuple size, and deduct from remaining page memory (not really correct)
  Tuple tup(tid, values, primary_key);
  if (page_mem_remaining < tup.size()) return;
  page_mem_remaining -= tup.size();
  // TODO: place tuple at location tup_mem_loc within page
  // TODO: allow tuples to be added at locations with deleted tuples

  // add tuple memloc to slot array
  slot_array.push_back(tup);
  std::cout << "Tuple with size " << tup.size()
    << " and id " << tup.getTid().first << ":" << tup.getTid().second << " added to page.\n";
  std::cout << "num_tuples: " << num_tuples << "\n";
}

void Page::removeTuple(std::pair<int, int> tid) {
  // check if tuple is not within this page
  if (tid.first != page_id || tid.second >= num_tuples) return;

  // remove tuple from slot array and add details to empty slot array
  size_t tup_size = slot_array[tid.second].size();
  slot_array[tid.second] = Tuple();
  empty_slots.push_back({tid.second, tup_size});
  std::cout << "Tuple with id " << tid.first << ":" << tid.second << " removed from page.\n";
}

void Page::removeTuple(Tuple t) {
  // check if tuple is not within this page
  std::pair<int, int> tid = t.getTid();
  if (tid.first != page_id || tid.second >= num_tuples) return;

  // remove tuple from slot array and add details to empty slot array
  slot_array[tid.second] = Tuple();
  empty_slots.push_back({tid.second, t.size()});
  std::cout << "Tuple with id " << tid.first << ":" << tid.second << " removed from page.\n";
}

bool Page::empty() {
  return num_tuples - empty_slots.size() == 0;
}

}