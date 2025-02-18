#include "gtest/gtest.h"

#include <vector>
#include <stack>
#include <queue>

#include "../s21_containers.h"

// vector 

TEST(VectorTest, DefaultConstructor) {
    s21::Vector<int> v1;
    std::vector<int> v2;
    
    EXPECT_EQ(v1.Size(), v2.size());
    EXPECT_EQ(v1.Capacity(), v2.capacity());
}

TEST(VectorTest, ConstructorWithSize) {
    const size_t size = 5;
    s21::Vector<int> v1(size);
    std::vector<int> v2(size, 0); 
    
    EXPECT_EQ(v1.Size(), v2.size());
    EXPECT_EQ(v1.Capacity(), v2.capacity());
}

TEST(VectorTest, ConstructorWithInitializerList) {
    s21::Vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {1, 2, 3, 4, 5}; 
    
    EXPECT_EQ(v1.Size(), v2.size());
    EXPECT_EQ(v1.Capacity(), v2.capacity());
    for (size_t i = 0; i < v1.Size(); i++) {
        EXPECT_EQ(v1[i], v2[i]);
    }
}

TEST(VectorTest, CopyConstructor) {
    s21::Vector<int> v1 = {1, 2, 3};
    s21::Vector<int> v2(v1);

    std::vector<int> v3 = {1, 2, 3};
    std::vector<int> v4(v3);

    EXPECT_EQ(v2.Size(), v4.size());
    for (size_t i = 0; i < v1.Size(); i++) {
        EXPECT_EQ(v2[i], v4[i]);
    }
}

TEST(VectorTest, MoveConstructor) {
    s21::Vector<int> v1{1, 2, 3};
    std::vector<int> v2{1, 2, 3};

    s21::Vector<int> v1_copy = v1;
    std::vector<int> v2_copy = v2;

    s21::Vector<int> v1_moved(std::move(v1));
    std::vector<int> v2_moved(std::move(v2));

    EXPECT_EQ(v1_moved.Size(), v1_copy.Size());
    EXPECT_EQ(v1_moved.Capacity(), v1_copy.Capacity());
    EXPECT_EQ(v2_moved.size(), v2_copy.size());
    EXPECT_EQ(v2_moved.capacity(), v2_copy.capacity());

    EXPECT_TRUE(v1.Empty());
    EXPECT_TRUE(v2.empty());
}

TEST(VectorTest, MoveAssignmentOperAtor) {
    s21::Vector<int> v1 = {1, 2, 3};
    s21::Vector<int> v2 = {4, 5, 6};

    v1 = std::move(v2);

    EXPECT_EQ(v1.Size(), 3UL);
    EXPECT_EQ(v2.Size(), 0UL);
    EXPECT_EQ(v1[0], 4);
    EXPECT_EQ(v1[1], 5);
    EXPECT_EQ(v1[2], 6);
}

TEST(VectorTest, AtFunction) {
  s21::Vector<double> v1{1.3, 2, 3.09, 4, 5};
  std::vector<double> v2{1.3, 2, 3.09, 4, 5};

  EXPECT_EQ(v1.At(0), v2.at(0));
  EXPECT_EQ(v1.At(1), v2.at(1));
  EXPECT_EQ(v1.At(2), v2.at(2));
  EXPECT_EQ(v1.At(3), v2.at(3));
  EXPECT_EQ(v1.At(4), v2.at(4));
}

TEST(VectorTest, AtOutOfRange) {
    s21::Vector<int> v = {1, 2, 3};

    EXPECT_EQ(v.At(0), 1);
    EXPECT_EQ(v.At(1), 2);
    EXPECT_EQ(v.At(2), 3);

    EXPECT_THROW(v.At(3), std::out_of_range);
}

TEST(VectorTest, IndexOperAtor) {
    s21::Vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2, 3};

    EXPECT_EQ(v1[0], v2[0]);
    EXPECT_EQ(v1[1], v2[1]);
    EXPECT_EQ(v1[2], v2[2]);
}

TEST(VectorTest, Front) {
    s21::Vector<double> v1;
    std::vector<double> v2;
    v1.PushBack(3.14);
    v1.PushBack(2.71);

    v2.push_back(3.14);
    v2.push_back(2.71);
    EXPECT_EQ(v1.Front(), v2.front());
}

TEST(VectorTest, FrontOutOfRange) {
    s21::Vector<int> v;
    EXPECT_THROW(v.Front(), std::out_of_range);
}

TEST(VectorTest, Back) {
    s21::Vector<int> v1{1, 2, 3};
    std::vector<int> v2{1, 2, 3};
    EXPECT_EQ(v1.Back(), v2.back());
}

TEST(VectorTest, BackEmptyVector) {
    s21::Vector<int> v;
    EXPECT_THROW(v.Back(), std::out_of_range);
}

TEST(VectorTest, Data) {
    s21::Vector<int> v1{1, 2, 3};
    std::vector<int> v2{1, 2, 3};
    EXPECT_EQ(*v1.Data(), *v2.data());
}

TEST(VectorTest, Begin) {
    s21::Vector<int> v1{1, 2, 3};
    std::vector<int> v2{1, 2, 3};
    EXPECT_EQ(*v1.Begin(), *v2.begin());
}

TEST(VectorTest, End) {
    s21::Vector<int> v1{1, 2, 3};
    std::vector<int> v2{1, 2, 3};
    EXPECT_EQ(*v1.End(), *v2.end());
}

TEST(VectorTest, Empty) {
    s21::Vector<int> v1;
    std::vector<int> v2;
    EXPECT_TRUE(v1.Empty());
    EXPECT_TRUE(v2.empty());
}

// На Win тест не работает, а на Mac все хорошо (несовместиость OS)
// TEST(VectorTest, MaxSize) {
//     s21::Vector<int> v1;
//     std::vector<int> v2;
//     auto maxSize1 = v1.MaxSize();
//     auto maxSize2 = v2.max_size();
//     EXPECT_EQ(maxSize1, maxSize2);
// }

TEST(VectorTest, Reserve) {
    s21::Vector<int> v1;
    std::vector<int> v2;

    v1.Reserve(10);
    v2.reserve(10);

    EXPECT_EQ(v1.Capacity(), 10UL);
    EXPECT_EQ(v2.capacity(), 10UL);
}

TEST(VectorTest, ShrinkToFit) {
    s21::Vector<int> v1;
    std::vector<int> v2;

    for (int i = 0; i < 10; ++i) {
        v1.PushBack(i);
        v2.push_back(i);
    }

    for (int i = 0; i < 5; ++i) {
        v1.PopBack();
        v2.pop_back();
    }

    v1.ShrinkToFit();
    v2.shrink_to_fit();

    EXPECT_EQ(v1.Size(), v2.size());
    EXPECT_EQ(v1.Capacity(), v2.capacity());
}

TEST(VectorTest, ShrinkToFitReturn) {
    s21::Vector<int> v1{1, 2, 3};
    std::vector<int> v2{1, 2, 3};
    
    v1.ShrinkToFit();
    v2.shrink_to_fit();

    EXPECT_EQ(v1.Size(), v2.size());
    EXPECT_EQ(v1.Capacity(), v2.capacity());
}

TEST(VectorTest, Clear) {
    s21::Vector<int> v1{1, 2, 3};
    std::vector<int> v2{1, 2, 3};

    v1.Clear();
    v2.clear();

    EXPECT_EQ(v1.Size(), 0UL);
    EXPECT_EQ(v2.size(), 0UL);
}

TEST(VectorTest, Insert) {
    s21::Vector<int> v1{1, 2, 3};
    std::vector<int> v2{1, 2, 3};

    auto v1_iter = v1.Insert(v1.Begin() + 1, 10);
    auto v2_iter = v2.insert(v2.begin() + 1, 10);

    EXPECT_EQ(v1.Size(), v2.size());
    EXPECT_EQ(*v1_iter, *v2_iter);

    for (size_t i = 0; i < v1.Size(); ++i) {
        EXPECT_EQ(v1[i], v2[i]);
    }
}

TEST(VectorTest, InsertOutOfRange) {
    s21::Vector<int> v1{1, 2, 3};
    EXPECT_THROW(v1.Insert(v1.End() + 1, 10), std::out_of_range);
}

TEST(VectorTest, Erase) {
    s21::Vector<int> v1{1, 2, 3};
    std::vector<int> v2{1, 2, 3};

    v1.Erase(v1.Begin() + 1);
    v2.erase(v2.begin() + 1);

    EXPECT_EQ(v1.Size(), v2.size());

    for (size_t i = 0; i < v1.Size(); ++i) {
        EXPECT_EQ(v1[i], v2[i]);
    }
}

TEST(VectorTest, EraseOutOfRange) {
    s21::Vector<int> v1{1, 2, 3};
    EXPECT_THROW(v1.Erase(v1.End() + 1), std::out_of_range);
}

TEST(VectorTest, Swap) {
    s21::Vector<int> v1{1, 2, 3};
    s21::Vector<int> v2{1, 2, 3, 4, 5, 6};

    std::vector<int> std_v1{1, 2, 3};
    std::vector<int> std_v2{1, 2, 3, 4, 5, 6};

    v2.Swap(v1);
    std_v2.swap(std_v1);

    EXPECT_EQ(v1.Size(), std_v1.size());
    EXPECT_EQ(v1.Capacity(), std_v1.capacity());

    EXPECT_EQ(v2.Size(), std_v2.size());
    EXPECT_EQ(v2.Capacity(), std_v2.capacity());
}


// stack

TEST(StackTest, DefaultConstructor) {
    s21::Stack<int> stack1;
    std::stack<int> stack2;
    EXPECT_EQ(stack1.Size(), stack2.size());
}

TEST(StackTest, ConstructorWithInitializerList) {
  s21::Stack<int> stack1 = {1, 2, 3};
  std::stack<int> stack2;
  stack2.push(1);
  stack2.push(2);
  stack2.push(3);
  EXPECT_EQ(stack1.Top(), stack2.top());
}

TEST(StackTest, CopyConstructor) {
  s21::Stack<int> stack1 = {1, 2, 3};
  s21::Stack<int> stack1_copy(stack1);
  std::stack<int> stack2;
  stack2.push(1);
  stack2.push(2);
  stack2.push(3);
  std::stack<int> stack2_copy(stack2);
  EXPECT_EQ(stack1_copy.Top(), stack2_copy.top());
}

TEST(StackTest, MoveConstructor) {
    s21::Stack<int> stack1 = {1, 2, 3};
    s21::Stack<int> stack1_moved(std::move(stack1));
    std::stack<int> stack2;
    stack2.push(1);
    stack2.push(2);
    stack2.push(3);
    std::stack<int> stack2_moved(std::move(stack2));
    EXPECT_EQ(stack1_moved.Top(), stack2_moved.top());
    
    EXPECT_TRUE(stack1.Empty());
    EXPECT_TRUE(stack2.empty());
}

TEST(StackTest, MoveAssignmentOperAtor) {
    s21::Stack<int> stack1 = {1, 2, 3}; 
    s21::Stack<int> stack2;

    std::stack<int> stack3; 
    std::stack<int> stack4;
    stack3.push(1);
    stack3.push(2);
    stack3.push(3);

    stack2 = std::move(stack1);
    stack4 = std::move(stack3);

    EXPECT_EQ(stack2.Top(), stack4.top());
    EXPECT_TRUE(stack1.Empty());
    EXPECT_TRUE(stack3.empty());
}

TEST(StackTest, PushString) {
    s21::Stack<std::string> stack1;
    std::stack<std::string> stack2;

    stack1.Push("apple");
    stack2.push("apple");

    EXPECT_EQ(stack1.Top(), stack2.top());
    EXPECT_EQ(stack1.Top(), "apple");

    stack1.Push("banana");
    stack2.push("banana");

    EXPECT_EQ(stack1.Top(), stack2.top());
    EXPECT_EQ(stack1.Top(), "banana");

    stack1.Push("orange");
    stack2.push("orange");

    EXPECT_EQ(stack1.Top(), stack2.top());
    EXPECT_EQ(stack1.Top(), "orange");
}

TEST(StackTest, PushDouble) {
    s21::Stack<double> stack1;
    std::stack<double> stack2;

    stack1.Push(3.14);
    stack2.push(3.14);

    EXPECT_EQ(stack1.Top(), stack2.top());
    EXPECT_DOUBLE_EQ(stack1.Top(), 3.14);

    stack1.Push(2.718);
    stack2.push(2.718);

    EXPECT_EQ(stack1.Top(), stack2.top());
    EXPECT_DOUBLE_EQ(stack1.Top(), 2.718);

    stack1.Push(1.618);
    stack2.push(1.618);

    EXPECT_EQ(stack1.Top(), stack2.top());
    EXPECT_DOUBLE_EQ(stack1.Top(), 1.618);
}

TEST(StackTest, Pop) {
    s21::Stack<double> stack1;
    stack1.Push(11.3);
    stack1.Push(2.981);
    stack1.Push(3.3333);
    stack1.Pop();

    std::stack<double> stack2;
    stack2.push(11.3);
    stack2.push(2.981);
    stack2.push(3.3333);
    stack2.pop();

    EXPECT_EQ(stack1.Top(), stack2.top());
    EXPECT_DOUBLE_EQ(stack1.Top(), 2.981);

    stack1.Pop();
    stack2.pop();

    EXPECT_EQ(stack1.Top(), stack2.top());
    EXPECT_DOUBLE_EQ(stack1.Top(), 11.3);

    stack1.Push(2.718);
    stack2.push(2.718);

    EXPECT_EQ(stack1.Top(), stack2.top());
    EXPECT_DOUBLE_EQ(stack1.Top(), 2.718);

    stack1.Pop();
    stack2.pop();

    EXPECT_EQ(stack1.Top(), stack2.top());
    EXPECT_DOUBLE_EQ(stack1.Top(), 11.3);
}

TEST(StackTest, Swap) {
    s21::Stack<double> stack1 = {3.14, 2.718};
    s21::Stack<double> stack2 = {1.618};

    std::stack<double> stack3;
    stack3.push(3.14);
    stack3.push(2.718);
    std::stack<double> stack4;
    stack4.push(1.618);

    stack1.Swap(stack2);
    stack3.swap(stack4);

    EXPECT_DOUBLE_EQ(stack1.Top(), stack3.top());
    EXPECT_DOUBLE_EQ(stack2.Top(), stack4.top());

    EXPECT_DOUBLE_EQ(stack1.Top(), 1.618);
    EXPECT_DOUBLE_EQ(stack2.Top(), 2.718);
    EXPECT_DOUBLE_EQ(stack2.Size(), 2);
    EXPECT_DOUBLE_EQ(stack1.Size(), 1);
}

// queue

TEST(QueueTest, DefaultConstructor) {
    s21::Queue<int> queue1;
    std::queue<int> queue2;
    EXPECT_EQ(queue1.Size(), queue2.size());
    EXPECT_TRUE(queue1.Empty());
    EXPECT_TRUE(queue2.empty());
}

TEST(QueueTest, ConstructorWithInitializerList) {
  s21::Queue<int> queue1 = {1, 2, 3};
  std::queue<int> queue2;
  queue2.push(1);
  queue2.push(2);
  queue2.push(3);
  EXPECT_EQ(queue1.Front(), queue2.front());
  EXPECT_EQ(queue1.Back(), queue2.back());
}

TEST(QueueTest, CopyConstructor) {
  s21::Queue<int> queue1 = {1, 2, 3};
  s21::Queue<int> queue1_copy(queue1);
  std::queue<int> queue2;
  queue2.push(1);
  queue2.push(2);
  queue2.push(3);
  std::queue<int> queue2_copy(queue2);
  EXPECT_EQ(queue1.Front(), queue2.front());
  EXPECT_EQ(queue1.Back(), queue2.back());
}

TEST(QueueTest, MoveConstructor) {
    s21::Queue<int> queue1 = {1, 2, 3};
    s21::Queue<int> queue1_moved(std::move(queue1));
    std::queue<int> queue2;
    queue2.push(1);
    queue2.push(2);
    queue2.push(3);
    std::queue<int> queue2_moved(std::move(queue2));
    EXPECT_EQ(queue1_moved.Front(), queue2_moved.front());
    EXPECT_EQ(queue1_moved.Back(), queue2_moved.back());
   
    EXPECT_TRUE(queue1.Empty());
    EXPECT_TRUE(queue2.empty());
}

TEST(QueueTest, MoveAssignmentOperAtor) {
    s21::Queue<int> queue1 = {1, 2, 3}; 
    s21::Queue<int> queue2;

    std::queue<int> queue3; 
    std::queue<int> queue4;
    queue3.push(1);
    queue3.push(2);
    queue3.push(3);

    queue2 = std::move(queue1);
    queue4 = std::move(queue3);

    EXPECT_EQ(queue2.Front(), queue4.front());
    EXPECT_EQ(queue2.Back(), queue4.back());

    EXPECT_TRUE(queue1.Empty());
    EXPECT_TRUE(queue3.empty());
}

TEST(QueueTest, PushString) {
    s21::Queue<std::string> queue1;
    std::queue<std::string> queue2;

    queue1.Push("apple");
    queue2.push("apple");

    EXPECT_EQ(queue1.Front(), queue2.front());
    EXPECT_EQ(queue1.Back(), queue2.back());
    EXPECT_EQ(queue1.Front(), "apple");

    queue1.Push("banana");
    queue2.push("banana");

    EXPECT_EQ(queue1.Front(), queue2.front());
    EXPECT_EQ(queue1.Back(), queue2.back());
    EXPECT_EQ(queue1.Back(), "banana");

    queue1.Push("orange");
    queue2.push("orange");

    EXPECT_EQ(queue1.Front(), queue2.front());
    EXPECT_EQ(queue1.Back(), queue2.back());
    EXPECT_EQ(queue1.Back(), "orange");
}

TEST(QueueTest, PushDouble) {
    s21::Queue<double> queue1;
    std::queue<double> queue2;

    queue1.Push(3.14);
    queue2.push(3.14);

    EXPECT_EQ(queue1.Front(), queue2.front());
    EXPECT_EQ(queue1.Back(), queue2.back());
    EXPECT_DOUBLE_EQ(queue1.Back(), 3.14);

    queue1.Push(2.718);
    queue2.push(2.718);

    EXPECT_EQ(queue1.Front(), queue2.front());
    EXPECT_EQ(queue1.Back(), queue2.back());
    EXPECT_DOUBLE_EQ(queue1.Back(), 2.718);

    queue1.Push(1.618);
    queue2.push(1.618);

    EXPECT_EQ(queue1.Front(), queue2.front());
    EXPECT_EQ(queue1.Back(), queue2.back());
    EXPECT_DOUBLE_EQ(queue1.Back(), 1.618);
}

TEST(QueueTest, Pop) {
    s21::Queue<double> queue1;
    queue1.Push(11.3);
    queue1.Push(2.981);
    queue1.Push(3.3333);
    queue1.Push(7.12);
    queue1.Pop();

    std::queue<double> queue2;
    queue2.push(11.3);
    queue2.push(2.981);
    queue2.push(3.3333);
    queue2.push(7.12);
    queue2.pop();

    EXPECT_EQ(queue1.Front(), queue2.front());
    EXPECT_EQ(queue1.Back(), queue2.back());
    EXPECT_DOUBLE_EQ(queue1.Front(), 2.981);

    queue1.Pop();
    queue2.pop();

    EXPECT_EQ(queue1.Front(), queue2.front());
    EXPECT_EQ(queue1.Back(), queue2.back());
    EXPECT_DOUBLE_EQ(queue1.Front(), 3.3333);

    queue1.Push(2.718);
    queue2.push(2.718);

    EXPECT_EQ(queue1.Front(), queue2.front());
    EXPECT_EQ(queue1.Back(), queue2.back());
    EXPECT_DOUBLE_EQ(queue1.Front(), 3.3333);

    queue1.Pop();
    queue2.pop();

    EXPECT_EQ(queue1.Front(), queue2.front());
    EXPECT_EQ(queue1.Back(), queue2.back());
    EXPECT_DOUBLE_EQ(queue1.Front(), 7.12);
}

TEST(QueueTest, Swap) {
    s21::Queue<double> queue1 = {3.14, 2.718};
    s21::Queue<double> queue2 = {1.618};

    std::queue<double> queue3;
    queue3.push(3.14);
    queue3.push(2.718);
    std::queue<double> queue4;
    queue4.push(1.618);

    queue1.Swap(queue2);
    queue3.swap(queue4);

    EXPECT_EQ(queue2.Front(), queue4.front());
    EXPECT_EQ(queue2.Back(), queue4.back());

    EXPECT_EQ(queue1.Size(), queue3.size());
    EXPECT_EQ(queue2.Size(), queue4.size());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}