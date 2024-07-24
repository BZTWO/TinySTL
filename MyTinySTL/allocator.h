#ifndef MYTINYSTL_ALLOCATOR_H_
#define MYTINYSTL_ALLOCATOR_H_

// 这个头文件包含一个模板类 allocator，用于管理内存的分配、释放，对象的构造、析构

#include "construct.h"
#include "util.h"

namespace mystl
{

// 模板类：allocator
// 模板函数代表数据类型
template <class T>
class allocator
{
public:
  typedef T            value_type;
  typedef T*           pointer;
  typedef const T*     const_pointer;
  typedef T&           reference;
  typedef const T&     const_reference;
  typedef size_t       size_type;
  typedef ptrdiff_t    difference_type;

public:
  static T*   allocate();
  static T*   allocate(size_type n);

  static void deallocate(T* ptr);
  static void deallocate(T* ptr, size_type n);

  static void construct(T* ptr);
  static void construct(T* ptr, const T& value);
  static void construct(T* ptr, T&& value);

  template <class... Args>
  static void construct(T* ptr, Args&& ...args);

  static void destroy(T* ptr);
  static void destroy(T* first, T* last);
};

// 分配一个 T 类型对象的内存
template <class T>
T* allocator<T>::allocate()
{
  return static_cast<T*>(::operator new(sizeof(T)));
}

//分配 n 个 T 类型对象的内存
template <class T>
T* allocator<T>::allocate(size_type n)
{
  if (n == 0)
    return nullptr;
  return static_cast<T*>(::operator new(n * sizeof(T)));
}

// 释放一个 T 类型对象的内存
template <class T>
void allocator<T>::deallocate(T* ptr)
{
  if (ptr == nullptr)
    return;
  ::operator delete(ptr);
}

// 释放 n 个 T 类型对象的内存
template <class T>
void allocator<T>::deallocate(T* ptr, size_type /*size*/)
{
  if (ptr == nullptr)
    return;
  ::operator delete(ptr);
}

// 构造一个 T 类型对象
template <class T>
void allocator<T>::construct(T* ptr)
{
  mystl::construct(ptr);
}

// 构造一个 T 类型对象，并初始化为 value
template <class T>
void allocator<T>::construct(T* ptr, const T& value)
{
  mystl::construct(ptr, value);
}

// 构造一个 T 类型对象，并初始化为 value，使用 move 语义
template <class T>
 void allocator<T>::construct(T* ptr, T&& value)
{
  mystl::construct(ptr, mystl::move(value));
}

// 使用参数包构造对象，完美转发参数
template <class T>
template <class ...Args>
 void allocator<T>::construct(T* ptr, Args&& ...args)
{
  mystl::construct(ptr, mystl::forward<Args>(args)...);
}

// 析构一个 T 类型对象
template <class T>
void allocator<T>::destroy(T* ptr)
{
  mystl::destroy(ptr);
}

// 析构多个对象
template <class T>
void allocator<T>::destroy(T* first, T* last)
{
  mystl::destroy(first, last);
}

} // namespace mystl
#endif // !MYTINYSTL_ALLOCATOR_H_

