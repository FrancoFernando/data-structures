#include <functional>
#include <memory>
#include <mutex>

template <class T>
class RingBuffer {

  using DataPtr = std::unique_ptr<T[], std::function<void(T*)>>;

 public:

  RingBuffer(size_t size) :
      mCapacity(size+1),
      mData(static_cast<T*>(operator new ((size+1)*sizeof(T))), deleter)
  {

  }

  ~RingBuffer()
  {
    if (mData != nullptr)
    {
      // Destroy all elements in buffer
      for (std::size_t i = mHead; i != mTail; i = (i + 1) % mCapacity)
      {
        mData[i].~T();
      }
    }
  }


  RingBuffer(const RingBuffer& src) : mHead(src.mHead), mTail(src.mTail), mCapacity(src.mCapacity),
                                      mData(static_cast<T*>(operator new ((src.mCapacity)*sizeof(T))), deleter)
  {
    for (std::size_t i = mHead; i != mTail; i = (i+1) % mCapacity)
    {
      new (mData.get()+i) T(src.mData[i]);
    }
  }

  RingBuffer& operator= (const RingBuffer& rhs) {

    if (this == &rhs) return *this;

    for (std::size_t i = mHead; i != mTail; i = (i+1) % mCapacity)
    {
      mData[i].~T();
    }

    mData.reset(reinterpret_cast<T*>(new char[(rhs.mCapacity)*sizeof(T)]));

    mCapacity = rhs.mCapacity;
    mHead = rhs.mHead;
    mTail = rhs.mTail;

    // Constuct a copy of rhs
    for (std::size_t i = mHead; i != mTail; i = (i + 1) % mCapacity)
    {
      new (mData.get()+i) T(rhs.mData[i]);
    }

    return *this;
  }

  RingBuffer(RingBuffer&& rhs)
      : mHead(rhs.mHead), mTail(rhs.mTail), mCapacity(rhs.mCapacity), mData(std::move(rhs.mData))
  {

  }

  RingBuffer& operator =(RingBuffer&& rhs)
  {

    if (&rhs != this)
    {
      mHead = rhs.mHead;
      mTail = rhs.mTail;
      mData = std::move(rhs.mData);
    }
    return *this;
  }

  bool empty() const
  {
    //if head and tail are equal the container is empty
    return (mHead == mTail);
  }

  bool full() const
  {
    //If tail is ahead the head by 1 the container is full
    return (mHead == ((mTail+1)%mCapacity));
  }

  void put(const T& item)
  {
    std::lock_guard<std::mutex> lock(mMutex);
    if (full()) mHead = (mHead+1) % mCapacity;
    new(mData.get() + mTail) T(item);
    mTail = (mTail+1) % mCapacity;
  }

  T get()
  {
    std::lock_guard<std::mutex> lock(mMutex);

    if(empty())
    {
      return T();
    }

    //Read mData and advance the head
    auto ret = mData[mHead];
    mData[mHead].~T();
    mHead = (mHead+1) % mCapacity;
    return ret;
  }

  size_t capacity() const
  {
    return mCapacity;
  }

  size_t size() const
  {
    return (mTail >= mHead) ? (mTail - mHead) : (mCapacity - mHead + mTail);

  }

 private:
  std::mutex mMutex;
  size_t mHead = 0;
  size_t mTail = 0;
  size_t mCapacity;
  std::function<void(T*)> deleter = [](T *m){operator delete(m);};
  DataPtr mData;
};
