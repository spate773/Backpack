#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <random>

#include "bstmap.h"

using namespace std;
using namespace testing;

namespace {

class Random {
 private:
  static mt19937 rng;

 public:
  static void seed(int s) {
    Random::rng.seed(s);
  }

  /**
   * Generate a random integer in the range 0 (inclusive) to `max` (exclusive)
   */
  static int randInt(int max) {
    // Even though mt19937 is standardized, STL distributions aren't!
    // So, unfortunately, even though this is biased, we're forced to
    // do something like this. Technically uint32_fast_t isn't...
    // totally consistent across platforms? But within reason it works.
    return rng() % (max + 1);
  }
};

std::mt19937 Random::rng;

TEST(BSTMapCore, StartsEmpty) {
  BSTMap<int, string> bst;
  EXPECT_TRUE(bst.empty());
  EXPECT_EQ(bst.size(), 0);
}

TEST(BSTMapCore, InsertOne) {
  BSTMap<int, string> bst;
  bst.insert(42, "hello");
  EXPECT_FALSE(bst.empty());
  EXPECT_EQ(bst.size(), 1);
}

TEST(BSTMapCore, InsertMany) {
  BSTMap<int, string> bst;
  bst.insert(1, "one");
  bst.insert(2, "two");
  bst.insert(3, "three");

  EXPECT_EQ(bst.at(1), "one");
  EXPECT_EQ(bst.at(2), "two");
  EXPECT_EQ(bst.at(3), "three");
}

TEST(BSTMapCore, NoOverwrite) {
  BSTMap<int, string> bst;
  bst.insert(5, "first");
  bst.insert(5, "second");
  EXPECT_EQ(bst.at(5), "first");
  EXPECT_EQ(bst.size(), 1);
}

TEST(BSTMapCore, CheckContains) {
  BSTMap<int, string> bst;
  bst.insert(10, "ten");
  bst.insert(20, "twenty");

  EXPECT_TRUE(bst.contains(10));
  EXPECT_TRUE(bst.contains(20));
  EXPECT_FALSE(bst.contains(99));
}

TEST(BSTMapCore, AtThrows) {
  BSTMap<int, string> bst;
  bst.insert(7, "seven");
  EXPECT_THROW(bst.at(100), out_of_range);
}

TEST(BSTMapCore, ClearWorks) {
  BSTMap<int, string> bst;
  bst.insert(1, "a");
  bst.insert(2, "b");
  bst.clear();

  EXPECT_TRUE(bst.empty());
  EXPECT_EQ(bst.size(), 0);
  EXPECT_FALSE(bst.contains(1));
}

TEST(BSTMapCore, ToStringMatch) {
  BSTMap<int, string> bst;
  bst.insert(3, "c");
  bst.insert(1, "a");
  bst.insert(2, "b");

  string expected =
      "1: a\n"
      "2: b\n"
      "3: c\n";

  EXPECT_EQ(bst.to_string(), expected);
}

TEST(BSTMapCore, CopyWorks) {
  BSTMap<int, string> bst;
  bst.insert(4, "four");
  bst.insert(5, "five");

  BSTMap<int, string> copy(bst);
  EXPECT_EQ(copy.size(), 2);
  EXPECT_EQ(copy.at(4), "four");
  EXPECT_EQ(copy.at(5), "five");
}

TEST(BSTMapCore, AssignWorks) {
  BSTMap<int, string> bst;
  bst.insert(6, "six");

  BSTMap<int, string> other;
  other = bst;
  EXPECT_EQ(other.size(), 1);
  EXPECT_EQ(other.at(6), "six");
}

TEST(BSTMapCore, SelfAssign) {
  BSTMap<int, string> bst;
  bst.insert(9, "nine");

  BSTMap<int, string>& ref = bst;
  bst = ref;

  EXPECT_EQ(bst.size(), 1);
  EXPECT_EQ(bst.at(9), "nine");
}


TEST(BSTMapCore, CopyOfEmpty) {
 
  BSTMap<int, string> bst;
  BSTMap<int, string> copy(bst);  // copy constructor on empty map

  EXPECT_TRUE(copy.empty());
  EXPECT_EQ(copy.size(), 0);

  
  bst.insert(1, "one");
  EXPECT_TRUE(copy.empty());
}

TEST(BSTMapCore, AssignOfEmpty) {
  // assigning from an empty BSTMap clears the target
  BSTMap<int, string> bst;
  BSTMap<int, string> other;
  other.insert(2, "two");
  other.insert(3, "three");

  other = bst;  // assign from empty map
  EXPECT_TRUE(other.empty());
  EXPECT_EQ(other.size(), 0);
  EXPECT_FALSE(other.contains(2));
  EXPECT_FALSE(other.contains(3));

  // empty should also be fine
  BSTMap<int, string> another;
  another = bst;
  EXPECT_TRUE(another.empty());
  EXPECT_EQ(another.size(), 0);
}

}  // namespace