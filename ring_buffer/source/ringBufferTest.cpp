#include "ringBuffer.h"
#include <gtest/gtest.h>
#include <string>

TEST(RingBufferTest, testEmpty) {
  RingBuffer<int> rb (5);
  ASSERT_EQ(true, rb.empty());
}

TEST(RingBufferTest, testFull) {
  const int val = 12;
  RingBuffer<int> rb (5);
  ASSERT_EQ(false, rb.full());

  for (size_t i = 0; i < 5; ++i) {
    rb.put(val+i);
  }

  ASSERT_EQ(true, rb.full());
  rb.put(100);
  ASSERT_EQ(true, rb.full());
  rb.get();
  ASSERT_EQ(false, rb.full());
}

TEST(RingBufferTest, testPut) {
  RingBuffer<double> rb (5);
  ASSERT_EQ(true, rb.empty());
  rb.put(12);
  ASSERT_EQ(false, rb.empty());
}

TEST(RingBufferTest, testGet) {
  const int val = 12;
  RingBuffer<double> rb (5);
  ASSERT_EQ(true, rb.empty());
  rb.put(val);
  ASSERT_EQ(false, rb.empty());
  ASSERT_EQ(val, rb.get());
}

TEST(RingBufferTest, testPutAndGet) {
  const int val = 12;
  const size_t capacity = 5;
  RingBuffer<int> rb (capacity);
  ASSERT_EQ(true, rb.empty());
  for (size_t i = 0; i < capacity; ++i) {
    ASSERT_EQ(false, rb.full());
    rb.put(val+i);
  }
  ASSERT_EQ(true, rb.full());
}

TEST(RingBufferTest, testCopyConstructor) {
  const int val = 12;
  const size_t capacity = 5;
  RingBuffer<int> rb (capacity);

  for (size_t i = 0; i < capacity; ++i) {
    rb.put(val+i);
  }

  RingBuffer<int> rbCopy = rb; //same as RingBuffer<int> rbCopy(rb);

  for (size_t i = 0; i < capacity; ++i) {
    ASSERT_EQ(rbCopy.get(),val+i);
  }
}

TEST(RingBufferTest, testAssignment) {
  const int val = 12;
  const size_t capacity = 5;
  RingBuffer<int> rb (capacity);

  for (size_t i = 0; i < capacity; ++i) {
    rb.put(val+i);
  }

  RingBuffer<int> rbCopy(capacity*2);
  rbCopy = rb;

  for (size_t i = 0; i < capacity; ++i) {
    ASSERT_EQ(rbCopy.get(),val+i);
  }
}

TEST(RingBufferTest, testMoveConstructor) {
  const int val = 12;
  const size_t capacity = 5;
  RingBuffer<int> rb (capacity);

  for (size_t i = 0; i < capacity; ++i) {
    rb.put(val+i);
  }

  RingBuffer<int> rbCopy(std::move(rb));

  for (size_t i = 0; i < capacity; ++i) {
    ASSERT_EQ(rbCopy.get(),val+i);
  }
}

TEST(RingBufferTest, testMoveAssignment) {
  const int val = 12;
  const size_t capacity = 5;
  RingBuffer<int> rb (capacity);

  for (size_t i = 0; i < capacity; ++i) {
    rb.put(val+i);
  }

  RingBuffer<int> rbCopy(10);
  rbCopy = std::move(rb);

  for (size_t i = 0; i < capacity; ++i) {
    ASSERT_EQ(rbCopy.get(),val+i);
  }
}

TEST(RingBufferTest, testSize) {
  const int val = 12;
  const size_t capacity = 5;
  RingBuffer<int> rb (capacity);

  for (size_t i = 0; i < capacity; ++i) {
    ASSERT_EQ(rb.size(), i);
    rb.put(val+i);
  }

  ASSERT_EQ(rb.size(), capacity);
  rb.put(val);
  ASSERT_EQ(rb.size(), capacity);
}

TEST(RingBufferTest, testWithString) {

  RingBuffer<std::string> rb(5);

  for (size_t i = 0; i < 4; ++i) {
    rb.put("abc");
  }
}


int main (int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
