//
// Created by chocolate-magnate on 12/6/24.
//

#ifndef QUASAR_ITERATION_HPP
#define QUASAR_ITERATION_HPP

namespace quasar {
  template<typename Derived, typename T>
class IteratorBase {
    public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    // Standard iterator operations
    Derived& operator++() {
      static_cast<Derived*>(this)->increment();
      return *static_cast<Derived*>(this);
    }

    T& operator*() {
      return static_cast<Derived*>(this)->dereference();
    }

    bool operator==(const Derived& other) const {
      return static_cast<const Derived*>(this)->equal(other);
    }

    bool operator!=(const Derived& other) const {
      return !(*this == other);
    }
  };

  // Range-enabled container base
  template<typename Derived, typename T>
  class RangeBase {
    public:
    // Iterator type that this container will use
    class Iterator : public IteratorBase<Iterator, T> {
      const Derived* container;
      size_t index;

      public:
      Iterator(const Derived* c, size_t i) : container(c), index(i) {}

      void increment() { ++index; }
      bool equal(const Iterator& other) const { return index == other.index; }
      T& dereference() const { return container->at(index); }
    };

    // Required begin() and end() for range-based for
    Iterator begin() const {
      return Iterator(static_cast<const Derived*>(this), 0);
    }

    Iterator end() const {
      return Iterator(static_cast<const Derived*>(this),
                     static_cast<const Derived*>(this)->size());
    }
  };
}

#endif //QUASAR_ITERATION_HPP
