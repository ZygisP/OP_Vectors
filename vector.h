#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <iostream>
#include <vector>
#include <chrono>
template<class ForwardIt, class T>
void uninitialized_fill(ForwardIt first, ForwardIt last, const T& value)
{
    typedef typename std::iterator_traits<ForwardIt>::value_type Value;
    ForwardIt current = first;
    try
    {
        for (; current != last; ++current)
        {
            ::new (static_cast<void*>(std::addressof(*current))) Value(value);
        }
    }
    catch (...)
    {
        for (; first != current; ++first)
        {
            first->~Value();
        }
        throw;
    }
}
// Copies elements from the range [first, last) to an uninitialized memory area beginning at d_first
template<class InputIt, class ForwardIt>
ForwardIt uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first)
{
    typedef typename std::iterator_traits<ForwardIt>::value_type Value;
    ForwardIt current = d_first;
    try
    {
        for (; first != last; ++first, (void) ++current)
        {
            ::new (static_cast<void*>(std::addressof(*current))) Value(*first);
        }
        return current;
    }
    catch (...)
    {
        for (; d_first != current; ++d_first)
        {
            d_first->~Value();
        }
        throw;
    }
}
//template<class T> class allocator {
//public:
// T* allocate(size_t); // išskirti `raw` atmintį
// void deallocate(T*, size_t); // atlaisvinti atmintį
// void construct(T*, const T&); // sukonstruoti 1 objektą
// void destroy(T*); // sunaikinti 1 objektą
// // ...
//};
template <class T> class Vec
{
public: // interfeisas
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;
    typedef T value_type;
    int growCounter=0;
// rule of three
    Vec()
    {
        create();
    }
    explicit Vec(size_type n, const T& t = T{})
    {
        create(n, t);
    }
    Vec(const Vec& v)
    {
        create(v.begin(), v.end());
    }
    Vec& operator=(const Vec&);
    ~Vec()
    {
        uncreate();
    }
    T& operator[](size_type i)
    {
        return data[i];
    }
    const T& operator[](size_type i) const
    {
        return data[i];
    }
    void clear()
    {
        uncreate();
    }
    void push_back(const T& t)
    {
        if (avail == limit)
        {
            grow();
            growCounter++;
        }

        unchecked_append(t);
    }
    size_type size() const
    {
        return avail - data;
    }
    size_type capacity() const 
    {
        return limit - data;
    }
    iterator begin()
    {
        return data;
    }
    const_iterator begin() const
    {
        return data;
    }
    iterator end()
    {
        return avail;
    }
    const_iterator end() const
    {
        return avail;
    }

private:
    iterator data;
    iterator avail; 
    iterator limit; 
    std::allocator<T> alloc; // objektas atminties valdymui
// išskirti atmintį (array) ir ją inicializuoti
    void create()
    {
        data = avail = limit = nullptr;
    }
    void create(size_type n, const T& val)
    {
        data = alloc.allocate(n); // grąžina ptr į array pirmą elementą
        limit = avail = data + n; // sustato rodykles į vietas
        uninitialized_fill(data, limit, val); // inicializuoja elementus val reikšme
    }
    void create(const_iterator i, const_iterator j)
    {
        data = alloc.allocate(j - i); // išskirti vietos j-i elementams
        limit = avail = uninitialized_copy(i, j, data); // nukopijuoja elementus iš intervalo
    }
// sunaikinti elementus array ir atlaisvinti atmintį
    void uncreate()
    {
        if (data)
        {
// sunaikinti (atbuline tvarka) sukonstruotus elementus
            iterator it = avail;
            while (it != data)
                alloc.destroy(--it);
// atlaisvinti išskirtą atmintį. Turi būti data != nullptr
            alloc.deallocate(data, limit - data);
        }
// reset'inam pointer'iuss - Vector'ius tuščias
        data = limit = avail = nullptr;
    }
// pagalbinės funkcijos push_back realizacijai
    void grow()
    {
// dvigubai daugiau vietos, nei buvo
        size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));
// išskirti naują vietą ir perkopijuoti egzistuojančius elementus
        iterator new_data = alloc.allocate(new_size);
        iterator new_avail = uninitialized_copy(data, avail, new_data);
// atlaisvinti seną vietą
        uncreate();
// reset'int rodykles į naujai išskirtą vietą
        data = new_data;
        avail = new_avail;
        limit = data + new_size;
    }
    void unchecked_append(const T& val)
    {
        alloc.construct(avail++, val);
    }
};
template <class T> Vec<T>& Vec<T>::operator=(const Vec& rhs) {
  if (&rhs != this) {
  uncreate();
  create(rhs.begin(), rhs.end());
  }
  return *this;
}
#endif // VECTOR_H_INCLUDED