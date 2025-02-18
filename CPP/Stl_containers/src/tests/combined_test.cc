
#include "../s21_containers.h"
#include <map>
#include <set>
#include <gtest/gtest.h>

TEST(map_tests, initializer_list){
  s21::Map<int,int> my = {{1,5},{3,6},{2,2}, {3,3}};
  std::map<int,int> orig = {{1,5},{3,6},{2,2},{3,3}};
  
  EXPECT_EQ(my.size(), orig.size());
  EXPECT_EQ(my.at(1), orig.at(1));
  EXPECT_EQ(my.at(2), orig.at(2));
  EXPECT_EQ(my.at(3), orig.at(3));
}

TEST(map_tests, empty){
  s21::Map<int,int> my;
  std::map<int,int> orig;

  EXPECT_EQ(my.size(), orig.size());
}

TEST(map_tests, copy_constructor){
  s21::Map<int,int> my1 = {{1,5},{3,6},{2,2}, {3,3}};
  std::map<int,int> orig1 = {{1,5},{3,6},{2,2},{3,3}};

  s21::Map<int,int> my2(my1);
  std::map<int,int> orig2(orig1);

  EXPECT_EQ(my1.size(), orig1.size()); //when copy, my1 set must save all data
  EXPECT_EQ(my2.size(), orig2.size());

  EXPECT_EQ(my2.at(1), orig2.at(1));
  EXPECT_EQ(my2.at(2), orig2.at(2));
  EXPECT_EQ(my2.at(3), orig2.at(3));
}

TEST(map_tests, move_operator_assing){
  s21::Map<int,int> my1 = {{1,5},{3,6},{2,2}, {3,3}};
  std::map<int,int> orig1 = {{1,5},{3,6},{2,2},{3,3}};

  s21::Map<int,int> my2 =  std::move(my1); // moving
  std::map<int,int> orig2 = std::move(orig1);  

  EXPECT_EQ(my1.size(), orig1.size()); //when move, my1 map must become empty
  EXPECT_EQ(my2.size(), orig2.size());

  EXPECT_EQ(my2.at(1), orig2.at(1));
  EXPECT_EQ(my2.at(2), orig2.at(2));
  EXPECT_EQ(my2.at(3), orig2.at(3));

}


TEST(map_tests, is_empty){
  s21::Map<int,int> my1 = {{1,5},{3,6},{2,2}, {3,3}};
  std::map<int,int> orig1 = {{1,5},{3,6},{2,2},{3,3}};
  
  EXPECT_EQ(my1.empty(), orig1.empty());
}


TEST(map_tests, size){
  s21::Map<int,int> my1 = {{1,5},{3,6},{2,2}, {3,3}};
  std::map<int,int> orig1 = {{1,5},{3,6},{2,2},{3,3}};

  EXPECT_EQ(my1.size(), orig1.size());

  s21::Map<int,int> my2;
  std::map<int,int> orig2;

  EXPECT_EQ(my2.size(), orig2.size());
}


TEST(map_tests, clear){
  s21::Map<int,int> my1 = {{1,5},{3,6},{2,2}, {3,3}};
  std::map<int,int> orig1 = {{1,5},{3,6},{2,2},{3,3}};

  my1.clear();
  orig1.clear();

  EXPECT_EQ(my1.size(), orig1.size());

  s21::Map<int,int> my2;
  std::map<int,int> orig2;

  my2.clear();
  orig2.clear();

  EXPECT_EQ(my2.size(), orig2.size());
}

/* // in original this type of insert doesnt work
TEST(map_tests, insert_key_obj){
  s21::Map<int,char> my;
  std::map<int,char> orig;

  my.insert(5,'4');
  my.insert(4,'f');

  orig.insert(5,'4');
  orig.insert(4,'f');

  EXPECT_EQ(my.size(), orig.size());

  EXPECT_EQ(my.at(5), orig.at(5));
  EXPECT_EQ(my[4], orig[4]);
}
*/


TEST(map_tests, insert_pair){
  s21::Map<int,char> my;
  std::map<int,char> orig;

  std::pair<int,char> p1 = {1, 'd'};
  std::pair<int,char> p2 = {1, '&'};
  std::pair<int,char> p3 = {5, '4'};

  my.insert(p1);
  my.insert(p2);
  my.insert(p3);

  orig.insert(p1);
  orig.insert(p2);
  orig.insert(p3);

  EXPECT_EQ(my.size(), orig.size());

  EXPECT_EQ(my.at(1), orig.at(1));
  EXPECT_EQ(my[5], orig[5]);
}

TEST(map_tests, insert_or_assign){
  s21::Map<int,char> my;
  std::map<int,char> orig;

  my.insert_or_assign(1, 'd');
  my.insert_or_assign(1, '&');
  my.insert_or_assign(5, '4');

  orig.insert_or_assign(1, 'd');
  orig.insert_or_assign(1, '&');
  orig.insert_or_assign(5, '4');

  EXPECT_EQ(my.size(), orig.size());

  EXPECT_EQ(my.at(1), orig.at(1));
  EXPECT_EQ(my.at(5), orig.at(5));
}


TEST(map_tests, erase){
  s21::Map<int,int> my1 = {{1,5},{3,6},{2,2}, {3,3}};
  std::map<int,int> orig1 = {{1,5},{3,6},{2,2},{3,3}};

  EXPECT_EQ(my1.size(), orig1.size());

  s21::Map<int,int>::iterator m_it = my1.find(1);
  std::map<int,int>::iterator o_it = orig1.find(1);
  my1.erase(m_it);
  orig1.erase(o_it);

  EXPECT_EQ(my1.size(), orig1.size());
}


/* // -------- doest work in original ------------------------
  // erasing not existing key node
TEST(map_tests, erase_not_existing_key){
  s21::Map<int,int> my1 = {{1,5},{3,6},{2,2}, {3,3}};
  std::map<int,int> orig1 = {{1,5},{3,6},{2,2},{3,3}};

  EXPECT_EQ(my1.size(), orig1.size());
  
  s21::Map<int,int>::iterator m_it = my1.find(98);
  std::map<int,int>::iterator o_it = orig1.find(98);
  my1.erase(m_it);
  orig1.erase(o_it);

  EXPECT_EQ(my2.size(), orig2.size());
}
*/



TEST(map_tests, swap){
  s21::Map<int,int> my1 = {{1,5},{3,6},{2,2}, {3,3}};
  std::map<int,int> orig1 = {{1,5},{3,6},{2,2},{3,3}};

  s21::Map<int,int> my2 = {{5,42}, {3,44}, {2,41}, {6,3}};
  std::map<int,int> orig2 = {{5,42}, {3,44}, {2,41}, {6,3}};
 
  EXPECT_EQ(my1.size(), orig1.size());
  EXPECT_EQ(my1.size(), orig1.size());

  my1.swap(my2);
  orig1.swap(orig2);

  EXPECT_EQ(my1.size(), orig1.size());
  EXPECT_EQ(my2.size(), orig2.size());

  EXPECT_EQ(my1[5], orig1[5]);
  EXPECT_EQ(my1[3], orig1[3]);
  EXPECT_EQ(my1[2], orig1[2]);

  EXPECT_EQ(my2[1], orig2[1]);
  EXPECT_EQ(my2[3], orig2[3]);
  EXPECT_EQ(my2[2], orig2[2]);
}


TEST(map_tests, swap_empty){
  s21::Map<int,int> my1 = {{1,5},{3,6},{2,2}, {3,3}};
  std::map<int,int> orig1 = {{1,5},{3,6},{2,2},{3,3}};

  s21::Map<int,int> my2;
  std::map<int,int> orig2;

  my1.swap(my2);
  orig1.swap(orig2);  

  EXPECT_EQ(my1.size(), orig1.size()); //my1 and orig1 must be empty
  EXPECT_EQ(my2.size(), orig2.size());

  EXPECT_EQ(my2[1], orig2[1]);
  EXPECT_EQ(my2[3], orig2[3]);
  EXPECT_EQ(my2[2], orig2[2]);
}


TEST(map_tests, merge){
  s21::Map<int,int> my1 = {{1,5},{3,6},{2,2}, {3,3}};
  std::map<int,int> orig1 = {{1,5},{3,6},{2,2},{3,3}};

  s21::Map<int,int> my2 = {{5,42}, {3,44}, {2,41}, {6,3}};
  std::map<int,int> orig2 = {{5,42}, {3,44}, {2,41}, {6,3}};

  my1.merge(my2);
  orig1.merge(orig2);  

  EXPECT_EQ(my1.size(), orig1.size());

  EXPECT_EQ(my1[5], orig1[5]);
  EXPECT_EQ(my1[3], orig1[3]);
  EXPECT_EQ(my1[2], orig1[2]);
  EXPECT_EQ(my1[6], orig1[6]);
}

TEST(map_tests, merge_empty){
  s21::Map<int,int> my1 = {{1,5},{3,6},{2,2}, {3,3}};
  std::map<int,int> orig1 = {{1,5},{3,6},{2,2},{3,3}};

  s21::Map<int,int> my2;
  std::map<int,int> orig2;

  my1.merge(my2);
  orig1.merge(orig2);  

  EXPECT_EQ(my1.size(), orig1.size());

  EXPECT_EQ(my1[5], orig1[5]);
  EXPECT_EQ(my1[3], orig1[3]);
  EXPECT_EQ(my1[2], orig1[2]);

  my2.merge(my1);
  orig2.merge(orig1);  
  EXPECT_EQ(my2.size(), orig2.size());

  EXPECT_EQ(my2[5], orig2[5]);
  EXPECT_EQ(my2[3], orig2[3]);
  EXPECT_EQ(my2[2], orig2[2]);
}

TEST(map_tests, contains){
  s21::Map<int,int> my1 = {{1,5},{3,6},{2,2}, {3,3}};
  std::map<int,int> orig1 = {{1,5},{3,6},{2,2},{3,3}};

  EXPECT_EQ(my1.contains(5), orig1.contains(5));
  EXPECT_EQ(my1.contains(6), orig1.contains(6));
}




TEST(set_tests, initializer_list){
  s21::Set<int> my = {1,5,3,6,2,2,4};
  std::set<int> orig = {1,5,3,6,2,2,4};

  EXPECT_EQ(my.size(), orig.size());

  auto m_it = my.begin();
  auto o_it = orig.begin();
  
  for (size_t i = 0; i < my.size(); ++i) {
    EXPECT_EQ(*m_it, *o_it);
    ++m_it;
    ++o_it;
  }
}


TEST(set_tests, empty){
  s21::Set<int> my;
  std::set<int> orig;
  
  EXPECT_EQ(my.size(), orig.size());
}

TEST(set_tests, copy_constructor){
  s21::Set<int> my1 = {1,4};
  std::set<int> orig1 = {1,4};

  s21::Set<int> my2(my1);
  std::set<int> orig2(orig1);

  EXPECT_EQ(my1.size(), orig1.size()); // Проверяем, что данные остались в my1 после копирования
  EXPECT_EQ(my2.size(), orig2.size());

  auto m_it = my2.begin();
  auto o_it = orig2.begin();
  while (m_it != my2.end() && o_it != orig2.end()) {
    EXPECT_EQ(*m_it, *o_it);
    ++m_it;
    ++o_it;
  }
}

TEST(set_tests, move_operator_assing){
  s21::Set<int> my1 = {1,4};
  std::set<int> orig1 = {1,4};

  s21::Set<int> my2 = std::move(my1); // Перемещение данных из my1 в my2. my1 должен стать пустым
  std::set<int> orig2 = std::move(orig1);

  EXPECT_TRUE(my1.empty()); // Проверка, что my1 пуст после перемещения
  EXPECT_TRUE(orig1.empty()); // Проверка, что orig1 пуст после перемещения
  EXPECT_EQ(my2.size(), orig2.size());

  auto m_it = my2.begin();
  auto o_it = orig2.begin();
  while (m_it != my2.end() && o_it != orig2.end()) {
    EXPECT_EQ(*m_it, *o_it);
    ++m_it;
    ++o_it;
  }
}


TEST(set_tests, iterator_begin){
  s21::Set<int> my1 = {1,4};
  std::set<int> orig1 = {1,4};

  s21::Set<int>::iterator m_it = my1.begin();
  std::set<int>::iterator o_it = orig1.begin();

  EXPECT_EQ(*m_it, *o_it);//data after dereferencing iterator must be same 1=1

  m_it++;
  o_it++;

  EXPECT_EQ(*m_it, *o_it);//data after dereferencing iterator must be same 4=4
}

TEST(set_tests, iterator_end){
  s21::Set<int> my1 = {1,4};
  std::set<int> orig1 = {1,4};

  s21::Set<int>::iterator m_it = my1.end();
  std::set<int>::iterator o_it = orig1.end();

  m_it--;
  o_it--;

  EXPECT_EQ(*m_it, *o_it);//data after dereferencing iterator must be same 4=4

  --m_it;
  --o_it;

  EXPECT_EQ(*m_it, *o_it);//data after dereferencing iterator must be same 1=1
}

TEST(set_tests, is_empty){
  s21::Set<int> my1 = {1,4};
  std::set<int> orig1 = {1,4};

  EXPECT_EQ(my1.empty(), orig1.empty());

  s21::Set<int> my2;
  std::set<int> orig2;

  EXPECT_EQ(my2.empty(), orig2.empty());
}


TEST(set_tests, size){
  s21::Set<int> my1 = {1,4};
  std::set<int> orig1 = {1,4};

  EXPECT_EQ(my1.size(), orig1.size());

  s21::Set<int> my2;
  std::set<int> orig2;

  EXPECT_EQ(my2.size(), orig2.size());
}


TEST(set_tests, insert){
  s21::Set<int> my;
  std::set<int> orig;

  my.insert(5);
  my.insert(4);

  orig.insert(5);
  orig.insert(4);

  EXPECT_EQ(my.size(), orig.size());

  auto m_it = my.begin();
  auto o_it = orig.begin();
  
  for (size_t i = 0; i < my.size(); ++i) {
    EXPECT_EQ(*m_it, *o_it);
    ++m_it;
    ++o_it;
  }
}


// TEST(set_tests, erase){
//   s21::Set<int> my = {4,2,1,5,5};
//   std::set<int> orig = {4,2,1,5,5};

//   // Удаляем элементы
//   my.erase(my.find(5));
//   my.erase(my.find(4));
//   orig.erase(orig.find(5));
//   orig.erase(orig.find(4));

//   // Проверяем размеры контейнеров
//   EXPECT_EQ(my.size(), orig.size());

//   // Перебираем контейнеры и сравниваем элементы
//   auto m_it = my.begin();
//   auto o_it = orig.begin();
//   while (m_it != my.end() && o_it != orig.end()) {
//     EXPECT_EQ(*m_it, *o_it);
//     ++m_it;
//     ++o_it;
//   }
// }


TEST(set_tests, swap){
  s21::Set<int> my1 = {4,2,1,5,5};
  std::set<int> orig1 = {4,2,1,5,5};

  s21::Set<int> my2 = {6,4,77};
  std::set<int> orig2 = {6,4,77};

  my1.swap(my2);
  orig1.swap(orig2);  

  EXPECT_EQ(my1.size(), orig1.size());
  auto m_it1 = my1.begin();
  auto o_it1 = orig1.begin();
  while (m_it1 != my1.end() && o_it1 != orig1.end()) {
    EXPECT_EQ(*m_it1, *o_it1);
    ++m_it1;
    ++o_it1;
  }

  EXPECT_EQ(my2.size(), orig2.size());
  auto m_it2 = my2.begin();
  auto o_it2 = orig2.begin();
  while (m_it2 != my2.end() && o_it2 != orig2.end()) {
    EXPECT_EQ(*m_it2, *o_it2);
    ++m_it2;
    ++o_it2;
  }
}


TEST(set_tests, swap_empty){
  s21::Set<int> my1 = {4,2,1,5,5};
  std::set<int> orig1 = {4,2,1,5,5};

  s21::Set<int> my2;
  std::set<int> orig2;

  my1.swap(my2);
  orig1.swap(orig2);  

  EXPECT_EQ(my1.size(), orig1.size()); // my1 and orig1 must be empty

  auto m_it2 = my2.begin();
  auto o_it2 = orig2.begin();

  EXPECT_EQ(my2.size(), orig2.size());

  while (m_it2 != my2.end() && o_it2 != orig2.end()) {
    EXPECT_EQ(*m_it2, *o_it2);
    ++m_it2;
    ++o_it2;
  }  
}


TEST(set_tests, merge){
  s21::Set<int> my1 = {4,2,1,5,5};
  std::set<int> orig1 = {4,2,1,5,5};

  s21::Set<int> my2 = {6,4,77};
  std::set<int> orig2 = {6,4,77};

  my1.merge(my2);
  orig1.merge(orig2);  

  EXPECT_EQ(my1.size(), orig1.size());

  auto m_it1 = my1.begin();
  auto o_it1 = orig1.begin();
  while (m_it1 != my1.end() && o_it1 != orig1.end()) {
    EXPECT_EQ(*m_it1, *o_it1);
    ++m_it1;
    ++o_it1;
  }
}


TEST(set_tests, merge_empty){
  s21::Set<int> my1 = {4,2,1,5,5};
  std::set<int> orig1 = {4,2,1,5,5};

  s21::Set<int> my2;
  std::set<int> orig2;

  my1.merge(my2);
  orig1.merge(orig2);  

  EXPECT_EQ(my1.size(), orig1.size());

  auto m_it1 = my1.begin();
  auto o_it1 = orig1.begin();
  while (m_it1 != my1.end() && o_it1 != orig1.end()) {
    EXPECT_EQ(*m_it1, *o_it1);
    ++m_it1;
    ++o_it1;
  }
}


TEST(set_tests, contains){
  s21::Set<int> my1 = {4,2,1,5,5};
  std::set<int> orig1 = {4,2,1,5,5};

  EXPECT_EQ(my1.contains(5), orig1.contains(5));
  EXPECT_EQ(my1.contains(6), orig1.contains(6));
}


TEST(set_tests, clear){
  s21::Set<int> my1 = {4,2,1,5,5};
  std::set<int> orig1 = {4,2,1,5,5};

  my1.clear();
  orig1.clear();

  EXPECT_EQ(my1.size(), orig1.size());
}


int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  
}