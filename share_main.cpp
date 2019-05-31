#include <iostream>

template < typename T > class shared_ptr {
  T * ptr;
  int * count;

  void decrease() {
    --( * count);
  }
  void increase() {
    ++( * count);
  }

  public:

    shared_ptr(T * temp) {
      ptr = temp;
      count = new int(1);
    }

  shared_ptr(const shared_ptr < T > & oth) {
    ptr = oth.ptr;
    count = oth.count;
    increase();
  }

  shared_ptr < T > & operator = (const shared_ptr < T > & oth) {
      //Shoudl happen only if count != nullptr
      if (count != nullptr) {
        decrease();
        if ( * count == 0) {
          delete count;
          delete ptr;
        }
      }
      ptr = oth.ptr;
      count = oth.count;
      increase();
      return *this;
    }

    ~shared_ptr() {
      if (count != nullptr) {
        decrease();
        if ( * count == 0) {
          delete ptr;
          delete count;
        }
      }
    }

  int getCount() const {
    return *count;
  }

  T * operator * () {
    return ptr;
  }

  T * operator - > () {
    return ptr;
  }
};

class A {
  public:
    int i;
  explicit A(int temp): i(temp) {}~A() {
    std::cout << "Deleting\n";
  }
};

//some func
shared_ptr < A > makeA() {
  shared_ptr < A > a(new A(100));
  return a;
}

int main() {
  shared_ptr < A > a = makeA();
  shared_ptr < A > b = a;
  shared_ptr < A > c = a;
  shared_ptr < A > d = makeA();
  b = d;

  std::cout << a.getCount() << std::endl;
  std::cout << b.getCount() << std::endl;
  std::cout << c.getCount() << std::endl;
  std::cout << d.getCount() << std::endl;
}
