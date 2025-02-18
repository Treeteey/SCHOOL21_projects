#include <gtest/gtest.h>
#include <list>
#include "../s21_containers.h"

using namespace s21;
using namespace std;

TEST(ConstructorTest, ConstructorListTest_1) {
  list<int> std_list;
  auto std_it = std_list.begin();
  List<int> s21_list;
  for (auto it = s21_list.Begin(); it != s21_list.End(); it++) {
    ASSERT_EQ(*it, *std_it);
  }
  ASSERT_EQ(std_list.size(), s21_list.Size());
}

TEST(ConstructorTest, ConstructorListTest_2) {
  list<int> std_list(3);
  auto std_it = std_list.begin();
  List<int> s21_list(3);
  for (auto it = s21_list.Begin(); it != s21_list.End(); it++) {
    ASSERT_EQ(*it, *std_it);
  }
  ASSERT_EQ(std_list.size(), s21_list.Size());
}

TEST(ConstructorTest, ConstructorListTest_3) {
  list<int> std_list{1, 2, 3, 4};
  auto std_it = std_list.begin();
  List<int> s21_list{1, 2, 3, 4};
  for (auto it = s21_list.Begin(); it != s21_list.End(); it++) {
    ASSERT_EQ(*it, *std_it);
    std_it++;
  }
  ASSERT_EQ(std_list.size(), s21_list.Size());
}

TEST(ConstructorTest, ConstructorListTest_4) {
  list<int> std_list{1, 2, 3, 4};
  auto std_it = std_list.begin();
  List<int> s21_list2;
  List<int> s21_list{1, 2, 3, 4};
  s21_list2 = s21_list;
  for (auto it = s21_list2.Begin(); it != s21_list2.End(); it++) {
    ASSERT_EQ(*it, *std_it);
    std_it++;
  }
  ASSERT_EQ(std_list.size(), s21_list2.Size());
}

TEST(ConstructorTest, ConstructorListTest_5) {
  list<int> std_list{1, 2, 3, 4};
  auto std_it = std_list.begin();
  List<int> s21_list{1, 2, 3, 4};
  List<int> s21_list2(s21_list);
  for (auto it = s21_list2.Begin(); it != s21_list2.End(); it++) {
    ASSERT_EQ(*it, *std_it);
    std_it++;
  }
  ASSERT_EQ(std_list.size(), s21_list2.Size());
}

TEST(ConstructorTest, ConstructorListTest_6) {
  list<int> std_list{1, 2, 3, 4};
  list<int> std_list2(move(std_list));
  auto std_it = std_list2.begin();
  List<int> s21_list{1, 2, 3, 4};
  List<int> s21_list2(move(s21_list));
  for (auto it = s21_list2.Begin(); it != s21_list2.End(); it++) {
    ASSERT_EQ(*it, *std_it);
    std_it++;
  }
  ASSERT_EQ(std_list2.size(), s21_list2.Size());
}

TEST(ConstructorTest, ConstructorListTest_7) {
  list<int> std_list(0);
  auto std_it = std_list.begin();
  List<int> s21_list(0);
  for (auto it = s21_list.Begin(); it != s21_list.End(); it++) {
    ASSERT_EQ(*it, *std_it);
  }
  ASSERT_EQ(std_list.size(), s21_list.Size());
}

TEST(FrontTests, FrontTest_1) {
  list<int> std_list{34, 3, 312, 4};
  List<int> s21_list{34, 3, 312, 4};
  ASSERT_EQ(std_list.front(), s21_list.Front());
}

TEST(BackTests, BackTest_1) {
  list<int> std_list{34, 3, 312, 4};
  List<int> s21_list{34, 3, 312, 4};
  ASSERT_EQ(std_list.back(), s21_list.Back());
}

TEST(EmptyTests, EmptyTest_1) {
  List<int> s21_list;
  EXPECT_TRUE(s21_list.Empty());
}

TEST(EmptyTests, EmptyTest_2) {
  List<int> s21_list{34, 3, 312, 4};
  List<int> s21_list2(move(s21_list));
  EXPECT_TRUE(s21_list.Empty());
}

TEST(ClearTests, ClearTest_1) {
  List<int> s21_list{34, 3, 312, 4};
  s21_list.Clear();
  EXPECT_TRUE(s21_list.Empty());
}

TEST(ClearTests, ClearTest_2) {
  List<char> s21_list{'a', 'b', 'c', 'd'};
  s21_list.Clear();
  EXPECT_TRUE(s21_list.Empty());
}

TEST(ClearTests, ClearTest_3) {
  List<char> s21_list;
  s21_list.Clear();
  ASSERT_TRUE(s21_list.Empty());
}

TEST(InsertTests, InsertTest_1) {
  list<double> std_list{1, 2, 4, 5, 66};
  auto std_it = std_list.begin();
  std_it++;
  auto std_ret_it = std_list.insert(std_it, 432);

  List<double> s21_list{1, 2, 4, 5, 66};
  auto s21_it = s21_list.Begin();
  s21_it++;
  auto s21_ret_it = s21_list.Insert(s21_it, 432);

  ASSERT_EQ(*std_ret_it, *s21_ret_it);
  auto std_iter = std_list.begin();
  for (auto it = s21_list.Begin(); it != s21_list.End(); it++) {
    ASSERT_EQ(*it, *std_iter);
    std_iter++;
  }
  ASSERT_EQ(std_list.size(), s21_list.Size());
}

TEST(InsertTests, InsertTest_2) {
  list<double> std_list;
  auto std_it = std_list.begin();
  auto std_ret_it = std_list.insert(std_it, 432);

  List<double> s21_list;
  auto s21_it = s21_list.Begin();
  auto s21_ret_it = s21_list.Insert(s21_it, 432);

  ASSERT_EQ(*std_ret_it, *s21_ret_it);
  auto std_iter = std_list.begin();
  for (auto it = s21_list.Begin(); it != s21_list.End(); it++) {
    ASSERT_EQ(*it, *std_iter);
    std_iter++;
  }
  ASSERT_EQ(std_list.size(), s21_list.Size());
}

TEST(InsertTests, InsertTest_3) {
  list<double> std_list{31, 35, 3 , 6 , 7};
  auto std_it = std_list.begin();
  std_it++;
  std_it++;
  auto std_ret_it = std_list.insert(std_it, 1);

  List<double> s21_list{31, 35, 3 , 6 , 7};
  auto s21_it = s21_list.Begin();
  s21_it++;
  s21_it++;
  auto s21_ret_it = s21_list.Insert(s21_it, 1);

  ASSERT_EQ(*std_ret_it, *s21_ret_it);
  auto std_iter = std_list.begin();
  for (auto it = s21_list.Begin(); it != s21_list.End(); it++) {
    ASSERT_EQ(*it, *std_iter);
    std_iter++;
  }
  ASSERT_EQ(std_list.size(), s21_list.Size());
}

TEST(InsertTests, InsertTest_4) {
  list<string> std_list{"first", "second", "third", "last"};
  auto std_it = std_list.end();
  auto std_ret_it = std_list.insert(std_it, "very_last");

  List<string> s21_list{"first", "second", "third", "last"};
  auto s21_it = s21_list.End();
  auto s21_ret_it = s21_list.Insert(s21_it, "very_last");

  ASSERT_EQ(*std_ret_it, *s21_ret_it);
  auto std_iter = std_list.begin();
  for (auto it = s21_list.Begin(); it != s21_list.End(); it++) {
    ASSERT_EQ(*it, *std_iter);
    std_iter++;
  }
  ASSERT_EQ(std_list.size(), s21_list.Size());
}

TEST(InsertTests, InsertTest_5) {
  list<string> std_list;
  auto std_it = std_list.begin();
  auto std_ret_it = std_list.insert(std_it, "very_first");

  List<string> s21_list;
  auto s21_it = s21_list.Begin();
  auto s21_ret_it = s21_list.Insert(s21_it, "very_first");

  ASSERT_EQ(*std_ret_it, *s21_ret_it);
  auto std_iter = std_list.begin();
  for (auto it = s21_list.Begin(); it != s21_list.End(); it++) {
    ASSERT_EQ(*it, *std_iter);
    std_iter++;
  }
  ASSERT_EQ(std_list.size(), s21_list.Size());
}

TEST(EraseTests, EraseTest_1) {
  list<string> std_list{"first", "second", "third", "last"};
  auto std_it = std_list.end();
  std_it--;
  std_list.erase(std_it);

  List<string> s21_list{"first", "second", "third", "last"};
  auto s21_it = s21_list.End();
  s21_it--;
  s21_list.Erase(s21_it);

  auto std_iter = std_list.begin();
  for (auto it = s21_list.Begin(); it != s21_list.End(); it++) {
    ASSERT_EQ(*it, *std_iter);
    std_iter++;
  }
  ASSERT_EQ(std_list.size(), s21_list.Size());
}

TEST(EraseTests, EraseTest_2) {
  list<string> std_list{"first", "second", "third", "last"};
  auto std_it = std_list.begin();
  std_it++;
  std_list.erase(std_it);

  List<string> s21_list{"first", "second", "third", "last"};
  auto s21_it = s21_list.Begin();
  s21_it++;
  s21_list.Erase(s21_it);

  auto std_iter = std_list.begin();
  for (auto it = s21_list.Begin(); it != s21_list.End(); it++) {
    ASSERT_EQ(*it, *std_iter);
    std_iter++;
  }
  ASSERT_EQ(std_list.size(), s21_list.Size());
}

TEST(EraseTests, EraseTest_3) {
  list<int> std_list{1, 2, 3, 4, 5, 6};
  auto std_it = std_list.begin();
  std_it++;
  std_it++;
  std_it++;
  std_list.erase(std_it);

  List<int> s21_list{1, 2, 3, 4, 5, 6};
  auto s21_it = s21_list.Begin();
  s21_it++;
  s21_it++;
  s21_it++;
  s21_list.Erase(s21_it);

  auto std_iter = std_list.begin();
  for (auto it = s21_list.Begin(); it != s21_list.End(); it++) {
    ASSERT_EQ(*it, *std_iter);
    std_iter++;
  }
}

TEST(EraseTests, EraseTest_4) {
  list<string> std_list{"first", "second", "third", "last"};
  auto std_it = std_list.begin();
  std_list.erase(std_it);

  List<string> s21_list{"first", "second", "third", "last"};
  auto s21_it = s21_list.Begin();
  s21_list.Erase(s21_it);

  auto std_iter = std_list.begin();
  for (auto it = s21_list.Begin(); it != s21_list.End(); it++) {
    ASSERT_EQ(*it, *std_iter);
    std_iter++;
  }
  ASSERT_EQ(std_list.size(), s21_list.Size());
}

TEST(PushBackTests, PushBackTest_1) {
  list<int> std_list{1, 2, 3, 4, 5, 6};
  std_list.push_back(9);

  List<int> s21_list{1, 2, 3, 4, 5, 6};
  s21_list.PushBack(9);

  auto std_iter = std_list.begin();
  for (auto it = s21_list.Begin(); it != s21_list.End(); it++) {
    ASSERT_EQ(*it, *std_iter);
    std_iter++;
  }
}

TEST(PushBackTests, PushBackTest_2) {
  list<string> std_list{"f", "s", "t"};
  std_list.push_back("last");

  List<string> s21_list{"f", "s", "t"};
  s21_list.PushBack("last");

  auto std_iter = std_list.begin();
  for (auto it = s21_list.Begin(); it != s21_list.End(); it++) {
    ASSERT_EQ(*it, *std_iter);
    std_iter++;
  }
}

TEST(PushFrontTests, PushFrontTest_1) {
  list<int> std_list{1, 2, 3, 4, 5, 6};
  std_list.push_front(9);

  List<int> s21_list{1, 2, 3, 4, 5, 6};
  s21_list.PushFront(9);

  auto std_iter = std_list.begin();
  for (auto it = s21_list.Begin(); it != s21_list.End(); it++) {
    ASSERT_EQ(*it, *std_iter);
    std_iter++;
  }
}

TEST(PushFrontTests, PushFrontTest_2) {
  list<string> std_list{"f", "s", "t"};
  std_list.push_front("first");

  List<string> s21_list{"f", "s", "t"};
  s21_list.PushFront("first");

  auto std_iter = std_list.begin();
  for (auto it = s21_list.Begin(); it != s21_list.End(); it++) {
    ASSERT_EQ(*it, *std_iter);
    std_iter++;
  }
  ASSERT_EQ(s21_list.Front(), std_list.front());
}

TEST(PushFrontTests, PushFrontTest_3) {
  list<string> std_list;
  std_list.push_front("first");

  List<string> s21_list;
  s21_list.PushFront("first");

  auto std_iter = std_list.begin();
  for (auto it = s21_list.Begin(); it != s21_list.End(); it++) {
    ASSERT_EQ(*it, *std_iter);
    std_iter++;
  }
  ASSERT_EQ(s21_list.Front(), std_list.front());
}

TEST(PopBackTests, PopBackTest_1) {
  list<string> std_list{"f", "s", "t"};
  std_list.pop_back();

  List<string> s21_list{"f", "s", "t"};
  s21_list.PopBack();

  auto std_iter = std_list.begin();
  for (auto it = s21_list.Begin(); it != s21_list.End(); it++) {
    ASSERT_EQ(*it, *std_iter);
    std_iter++;
  }
  ASSERT_EQ(s21_list.Back(), std_list.back());
}

TEST(PopBackTests, PopBackTest_2) {
  list<double> std_list{1, 2.33, 31 , 1};
  std_list.pop_back();

  List<double> s21_list{1, 2.33, 31 , 1};
  s21_list.PopBack();

  auto std_iter = std_list.begin();
  for (auto it = s21_list.Begin(); it != s21_list.End(); it++) {
    ASSERT_EQ(*it, *std_iter);
    std_iter++;
  }
  ASSERT_EQ(s21_list.Back(), std_list.back());
}

TEST(PopFrontTests, PopFrontTest_1) {
  list<string> std_list{"f", "s", "t"};
  std_list.pop_front();

  List<string> s21_list{"f", "s", "t"};
  s21_list.PopFront();

  auto std_iter = std_list.begin();
  for (auto it = s21_list.Begin(); it != s21_list.End(); it++) {
    ASSERT_EQ(*it, *std_iter);
    std_iter++;
  }
  ASSERT_EQ(s21_list.Front(), std_list.front());
  ASSERT_EQ(s21_list.Back(), std_list.back());
}

TEST(PopFrontTests, PopFrontTest_2) {
  list<double> std_list{1, 2.33, 31 , 1};
  std_list.pop_front();

  List<double> s21_list{1, 2.33, 31 , 1};
  s21_list.PopFront();

  auto std_iter = std_list.begin();
  for (auto it = s21_list.Begin(); it != s21_list.End(); it++) {
    ASSERT_EQ(*it, *std_iter);
    std_iter++;
  }
  ASSERT_EQ(s21_list.Front(), std_list.front());
  ASSERT_EQ(s21_list.Back(), std_list.back());
}

TEST(SwapTests, SwapTest_1) {
  list<double> std_list1{1, 2.33, 31 , 1};
  list<double> std_list2{500};
  std_list1.swap(std_list2);

  List<double> s21_list1{1, 2.33, 31 , 1};
  List<double> s21_list2{500};
  s21_list1.Swap(s21_list2);

  auto std_iter1 = std_list1.begin();
  for (auto it1 = s21_list1.Begin(); it1 != s21_list1.End(); it1++) {
    ASSERT_EQ(*it1, *std_iter1);
    std_iter1++;
  }

  auto std_iter2 = std_list2.begin();
  for (auto it2 = s21_list2.Begin(); it2 != s21_list2.End(); it2++) {
    ASSERT_EQ(*it2, *std_iter2);
    std_iter2++;
  }
  ASSERT_EQ(s21_list1.Size(), std_list1.size());
  ASSERT_EQ(s21_list2.Size(), std_list2.size());
  ASSERT_EQ(s21_list1.Front(), std_list1.front());
  ASSERT_EQ(s21_list2.Front(), std_list2.front());
  ASSERT_EQ(s21_list1.Back(), std_list1.back());
  ASSERT_EQ(s21_list2.Back(), std_list2.back());
}

TEST(SwapTests, SwapTest_2) {
  list<double> std_list1{1, 2.33, 31 , 1};
  list<double> std_list2;
  std_list1.swap(std_list2);

  List<double> s21_list1{1, 2.33, 31 , 1};
  List<double> s21_list2;
  s21_list1.Swap(s21_list2);

  auto std_iter1 = std_list1.begin();
  for (auto it1 = s21_list1.Begin(); it1 != s21_list1.End(); it1++) {
    ASSERT_EQ(*it1, *std_iter1);
    std_iter1++;
  }

  auto std_iter2 = std_list2.begin();
  for (auto it2 = s21_list2.Begin(); it2 != s21_list2.End(); it2++) {
    ASSERT_EQ(*it2, *std_iter2);
    std_iter2++;
  }
  ASSERT_EQ(s21_list1.Size(), std_list1.size());
  ASSERT_EQ(s21_list2.Size(), std_list2.size());
  ASSERT_EQ(s21_list1.Front(), std_list1.front());
  ASSERT_EQ(s21_list2.Front(), std_list2.front());
  ASSERT_EQ(s21_list1.Back(), std_list1.back());
  ASSERT_EQ(s21_list2.Back(), std_list2.back());
}

TEST(SwapTests, SwapTest_3) {
  list<string> std_list1;
  list<string> std_list2{"da", "adad", "gfgfb", "fbvf"};
  std_list1.swap(std_list2);

  List<string> s21_list1;
  List<string> s21_list2{"da", "adad", "gfgfb", "fbvf"};
  s21_list1.Swap(s21_list2);

  auto std_iter1 = std_list1.begin();
  for (auto it1 = s21_list1.Begin(); it1 != s21_list1.End(); it1++) {
    ASSERT_EQ(*it1, *std_iter1);
    std_iter1++;
  }
  auto std_iter2 = std_list2.begin();
  for (auto it2 = s21_list2.Begin(); it2 != s21_list2.End(); it2++) {
    ASSERT_EQ(*it2, *std_iter2);
    std_iter2++;
  }
  ASSERT_EQ(s21_list1.Size(), std_list1.size());
  ASSERT_EQ(s21_list2.Size(), std_list2.size());
  ASSERT_EQ(s21_list1.Front(), std_list1.front());
  ASSERT_EQ(s21_list1.Back(), std_list1.back());
}

TEST(SwapTests, SwapTest_4) {
  list<int> std_list1;
  list<int> std_list2;
  std_list1.swap(std_list2);

  List<int> s21_list1;
  List<int> s21_list2;
  s21_list1.Swap(s21_list2);

  auto std_iter1 = std_list1.begin();
  for (auto it1 = s21_list1.Begin(); it1 != s21_list1.End(); it1++) {
    ASSERT_EQ(*it1, *std_iter1);
    std_iter1++;
  }
  auto std_iter2 = std_list2.begin();
  for (auto it2 = s21_list2.Begin(); it2 != s21_list2.End(); it2++) {
    ASSERT_EQ(*it2, *std_iter2);
    std_iter2++;
  }
  ASSERT_TRUE(s21_list1.Empty());
  ASSERT_TRUE(s21_list2.Empty());
  ASSERT_TRUE(std_list1.empty());
  ASSERT_TRUE(std_list2.empty());
  ASSERT_EQ(s21_list1.Size(), std_list1.size());
  ASSERT_EQ(s21_list2.Size(), std_list2.size());
}

TEST(MergeTests, MergeTest_1) {
  list<string> std_list1;
  list<string> std_list2{"da", "adad", "gfgfb", "fbvf"};
  std_list1.merge(std_list2);

  List<string> s21_list1;
  List<string> s21_list2{"da", "adad", "gfgfb", "fbvf"};
  s21_list1.Merge(s21_list2);

  auto std_iter1 = std_list1.begin();
  for (auto it1 = s21_list1.Begin(); it1 != s21_list1.End(); it1++) {
    ASSERT_EQ(*it1, *std_iter1);
    std_iter1++;
  }
  auto std_iter2 = std_list2.begin();
  for (auto it2 = s21_list2.Begin(); it2 != s21_list2.End(); it2++) {
    ASSERT_EQ(*it2, *std_iter2);
    std_iter2++;
  }
  ASSERT_EQ(s21_list1.Size(), std_list1.size());
  ASSERT_EQ(s21_list2.Size(), std_list2.size());
  ASSERT_EQ(s21_list1.Front(), std_list1.front());
  ASSERT_EQ(s21_list1.Back(), std_list1.back());
}

TEST(MergeTests, MergeTest_2) {
  list<unsigned> std_list1{6,7,8};
  list<unsigned> std_list2{1,2,3,4};
  std_list1.merge(std_list2);

  List<unsigned> s21_list1{6,7,8};
  List<unsigned> s21_list2{1,2,3,4};
  s21_list1.Merge(s21_list2);

  auto std_iter1 = std_list1.begin();
  for (auto it1 = s21_list1.Begin(); it1 != s21_list1.End(); it1++) {
    ASSERT_EQ(*it1, *std_iter1);
    std_iter1++;
  }
  auto std_iter2 = std_list2.begin();
  for (auto it2 = s21_list2.Begin(); it2 != s21_list2.End(); it2++) {
    ASSERT_EQ(*it2, *std_iter2);
    std_iter2++;
  }
  ASSERT_EQ(s21_list1.Size(), std_list1.size());
  ASSERT_EQ(s21_list2.Size(), std_list2.size());
  ASSERT_EQ(s21_list1.Front(), std_list1.front());
  ASSERT_EQ(s21_list1.Back(), std_list1.back());
}

TEST(MergeTests, MergeTest_3) {
  list<unsigned> std_list1{6,7,8};
  list<unsigned> std_list2;
  std_list1.merge(std_list2);

  List<unsigned> s21_list1{6,7,8};
  List<unsigned> s21_list2;
  s21_list1.Merge(s21_list2);

  auto std_iter1 = std_list1.begin();
  for (auto it1 = s21_list1.Begin(); it1 != s21_list1.End(); it1++) {
    ASSERT_EQ(*it1, *std_iter1);
    std_iter1++;
  }
  auto std_iter2 = std_list2.begin();
  for (auto it2 = s21_list2.Begin(); it2 != s21_list2.End(); it2++) {
    ASSERT_EQ(*it2, *std_iter2);
    std_iter2++;
  }
  ASSERT_EQ(s21_list1.Size(), std_list1.size());
  ASSERT_EQ(s21_list2.Size(), std_list2.size());
  ASSERT_EQ(s21_list1.Front(), std_list1.front());
  ASSERT_EQ(s21_list1.Back(), std_list1.back());
}

TEST(MergeTests, MergeTest_4) {
  list<unsigned> std_list1{6,7,8};
  std_list1.merge(std_list1);

  List<unsigned> s21_list1{6,7,8};
  s21_list1.Merge(s21_list1);

  auto std_iter1 = std_list1.begin();
  for (auto it1 = s21_list1.Begin(); it1 != s21_list1.End(); it1++) {
    ASSERT_EQ(*it1, *std_iter1);
    std_iter1++;
  }
  ASSERT_EQ(s21_list1.Size(), std_list1.size());
  ASSERT_EQ(s21_list1.Front(), std_list1.front());
  ASSERT_EQ(s21_list1.Back(), std_list1.back());
}

TEST(SpliceTests, SpliceTest_1) {
  list<unsigned> std_list1{6,7,8};
  list<unsigned> std_list2{1,2,3,4,5,6,7};
  std_list1.splice(std_list1.begin() ,std_list2);

  List<unsigned> s21_list1{6,7,8};
  List<unsigned> s21_list2{1,2,3,4,5,6,7};
  s21_list1.Splice(s21_list1.Begin() , s21_list2);

  auto std_iter1 = std_list1.begin();
  for (auto it1 = s21_list1.Begin(); it1 != s21_list1.End(); it1++) {
    ASSERT_EQ(*it1, *std_iter1);
    std_iter1++;
  }
  auto std_iter2 = std_list2.begin();
  for (auto it2 = s21_list2.Begin(); it2 != s21_list2.End(); it2++) {
    ASSERT_EQ(*it2, *std_iter2);
    std_iter2++;
  }
  ASSERT_EQ(s21_list1.Size(), std_list1.size());
  ASSERT_EQ(s21_list1.Front(), std_list1.front());
  ASSERT_EQ(s21_list1.Back(), std_list1.back());
}

TEST(SpliceTests, SpliceTest_2) {
  list<unsigned> std_list1{6,7,8};
  list<unsigned> std_list2;
  std_list1.splice(std_list1.begin() ,std_list2);

  List<unsigned> s21_list1{6,7,8};
  List<unsigned> s21_list2;
  s21_list1.Splice(s21_list1.Begin() , s21_list2);

  auto std_iter1 = std_list1.begin();
  for (auto it1 = s21_list1.Begin(); it1 != s21_list1.End(); it1++) {
    ASSERT_EQ(*it1, *std_iter1);
    std_iter1++;
  }
  auto std_iter2 = std_list2.begin();
  for (auto it2 = s21_list2.Begin(); it2 != s21_list2.End(); it2++) {
    ASSERT_EQ(*it2, *std_iter2);
    std_iter2++;
  }
  ASSERT_EQ(s21_list1.Size(), std_list1.size());
  ASSERT_EQ(s21_list1.Front(), std_list1.front());
  ASSERT_EQ(s21_list1.Back(), std_list1.back());
}

TEST(SpliceTests, SpliceTest_3) {
  list<unsigned> std_list1{6,7,8};
  list<unsigned> std_list2;
  std_list2.splice(std_list2.begin() ,std_list1);

  List<unsigned> s21_list1{6,7,8};
  List<unsigned> s21_list2;
  s21_list2.Splice(s21_list2.Begin() , s21_list1);

  auto std_iter1 = std_list1.begin();
  for (auto it1 = s21_list1.Begin(); it1 != s21_list1.End(); it1++) {
    ASSERT_EQ(*it1, *std_iter1);
    std_iter1++;
  }
  auto std_iter2 = std_list2.begin();
  for (auto it2 = s21_list2.Begin(); it2 != s21_list2.End(); it2++) {
    ASSERT_EQ(*it2, *std_iter2);
    std_iter2++;
  }
  ASSERT_EQ(s21_list1.Size(), std_list1.size());
  ASSERT_EQ(s21_list1.Front(), std_list1.front());
  ASSERT_EQ(s21_list1.Back(), std_list1.back());
}

TEST(SpliceTests, SpliceTest_4) {
  list<unsigned> std_list1{6,7,8};
  list<unsigned> std_list2;
  std_list2.splice(std_list2.begin() ,std_list1);

  List<unsigned> s21_list1{6,7,8};
  List<unsigned> s21_list2;
  s21_list2.Splice(s21_list2.Begin() , s21_list1);

  auto std_iter1 = std_list1.begin();
  for (auto it1 = s21_list1.Begin(); it1 != s21_list1.End(); it1++) {
    ASSERT_EQ(*it1, *std_iter1);
    std_iter1++;
  }
  auto std_iter2 = std_list2.begin();
  for (auto it2 = s21_list2.Begin(); it2 != s21_list2.End(); it2++) {
    ASSERT_EQ(*it2, *std_iter2);
    std_iter2++;
  }
  ASSERT_EQ(s21_list1.Size(), std_list1.size());
  ASSERT_EQ(s21_list1.Front(), std_list1.front());
  ASSERT_EQ(s21_list1.Back(), std_list1.back());
}

TEST(ReverseTests, ReverseTest_1) {
  list<int> std_list1{6,7,8,12,44};
  std_list1.reverse();

  List<int> s21_list1{6,7,8,12,44};
  s21_list1.Reverse();

  auto std_iter1 = std_list1.begin();
  for (auto it1 = s21_list1.Begin(); it1 != s21_list1.End(); it1++) {
    ASSERT_EQ(*it1, *std_iter1);
    std_iter1++;
  }
  ASSERT_EQ(s21_list1.Size(), std_list1.size());
  ASSERT_EQ(s21_list1.Front(), std_list1.front());
  ASSERT_EQ(s21_list1.Back(), std_list1.back());
}

TEST(ReverseTests, ReverseTest_2) {
  list<string> std_list1{"dadav", "daef", "yhjk", "6tgiu"};
  std_list1.reverse();

  List<string> s21_list1{"dadav", "daef", "yhjk", "6tgiu"};
  s21_list1.Reverse();

  auto std_iter1 = std_list1.begin();
  for (auto it1 = s21_list1.Begin(); it1 != s21_list1.End(); it1++) {
    ASSERT_EQ(*it1, *std_iter1);
    std_iter1++;
  }
  ASSERT_EQ(s21_list1.Size(), std_list1.size());
  ASSERT_EQ(s21_list1.Front(), std_list1.front());
  ASSERT_EQ(s21_list1.Back(), std_list1.back());
}

TEST(UniqueTests, UniqueTest_1) {
  list<string> std_list1{"dadav", "dadav", "daef", "yhjk", "6tgiu", "dadav"};
  std_list1.unique();

  List<string> s21_list1{"dadav", "dadav", "daef", "yhjk", "6tgiu", "dadav"};
  s21_list1.Unique();

  auto std_iter1 = std_list1.begin();
  for (auto it1 = s21_list1.Begin(); it1 != s21_list1.End(); it1++) {
    ASSERT_EQ(*it1, *std_iter1);
    std_iter1++;
  }
}

TEST(UniqueTests, UniqueTest_2) {
  list<int> std_list1{1,1,3,1,4,4,5,6,6,5};
  std_list1.unique();

  List<int> s21_list1{1,1,3,1,4,4,5,6,6,5};
  s21_list1.Unique();

  auto std_iter1 = std_list1.begin();
  for (auto it1 = s21_list1.Begin(); it1 != s21_list1.End(); it1++) {
    ASSERT_EQ(*it1, *std_iter1);
    std_iter1++;
  }
  ASSERT_EQ(s21_list1.Size(), std_list1.size());
  ASSERT_EQ(s21_list1.Front(), std_list1.front());
  ASSERT_EQ(s21_list1.Back(), std_list1.back());
}

TEST(UniqueTests, UniqueTest_3) {
  list<int> std_list1;
  std_list1.unique();

  List<int> s21_list1;
  s21_list1.Unique();

  auto std_iter1 = std_list1.begin();
  for (auto it1 = s21_list1.Begin(); it1 != s21_list1.End(); it1++) {
    ASSERT_EQ(*it1, *std_iter1);
    std_iter1++;
  }
  ASSERT_EQ(s21_list1.Size(), std_list1.size());
  ASSERT_EQ(s21_list1.Front(), std_list1.front());
  ASSERT_EQ(s21_list1.Back(), std_list1.back());
}

TEST(SortTests, SortTest_1) {
  list<int> std_list1;
  std_list1.sort();

  List<int> s21_list1;
  s21_list1.Sort();

  auto std_iter1 = std_list1.begin();
  for (auto it1 = s21_list1.Begin(); it1 != s21_list1.End(); it1++) {
    ASSERT_EQ(*it1, *std_iter1);
    std_iter1++;
  }
  ASSERT_EQ(s21_list1.Size(), std_list1.size());
  ASSERT_EQ(s21_list1.Front(), std_list1.front());
  ASSERT_EQ(s21_list1.Back(), std_list1.back());
}

TEST(SortTests, SortTest_2) {
  list<int> std_list1{9,8,8,4,2,3,1,7,5,4};
  std_list1.sort();

  List<int> s21_list1{9,8,8,4,2,3,1,7,5,4};
  s21_list1.Sort();

  auto std_iter1 = std_list1.begin();
  for (auto it1 = s21_list1.Begin(); it1 != s21_list1.End(); it1++) {
    ASSERT_EQ(*it1, *std_iter1);
    std_iter1++;
  }
  ASSERT_EQ(s21_list1.Size(), std_list1.size());
  ASSERT_EQ(s21_list1.Front(), std_list1.front());
  ASSERT_EQ(s21_list1.Back(), std_list1.back());
}

TEST(SortTests, SortTest_3) {
  list<string> std_list1{"dadav", "dadav", "daef", "yhjk", "6tgiu", "dadav"};
  std_list1.sort();

  List<string> s21_list1{"dadav", "dadav", "daef", "yhjk", "6tgiu", "dadav"};
  s21_list1.Sort();

  auto std_iter1 = std_list1.begin();
  for (auto it1 = s21_list1.Begin(); it1 != s21_list1.End(); it1++) {
    ASSERT_EQ(*it1, *std_iter1);
    std_iter1++;
  }
  ASSERT_EQ(s21_list1.Size(), std_list1.size());
  ASSERT_EQ(s21_list1.Front(), std_list1.front());
  ASSERT_EQ(s21_list1.Back(), std_list1.back());
}

TEST(MaxSizeTests, MaxSizeTests_1) {
  list<string> std_list1{"dadav", "dadav", "daef", "yhjk", "6tgiu", "dadav"};

  List<string> s21_list1{"dadav", "dadav", "daef", "yhjk", "6tgiu", "dadav"};

  ASSERT_EQ(std_list1.max_size(), s21_list1.MaxSize());
}




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
