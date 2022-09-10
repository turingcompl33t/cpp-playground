/**
 * @file BitVector.hpp
 * @author Kyle Dotterrer
 * @brief Simplified implementation of std::vector<bool>.
 * @version 0.1
 * @date 2022-09-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <cassert>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstring>
#include <memory>
#include <stdexcept>

#define ASSERT(expr, message) assert((expr) && (message))

/** The underlying representation for elements of the vector */
using BitType = unsigned long;

/**
 * @brief A proxy object that represents a reference
 * to an individual bit in the BitVector. The proxy
 * allows both reads and writes to the underlying vector.
 */
class BitRef {
  /** The 'bucket' in which the bit is located */
  BitType* const bucket_;
  /** The mask to isolate the target bit */
  BitType const mask_;

public:
  /** @brief Construct a new Bit Ref object */
  BitRef()
      : bucket_{nullptr}
      , mask_{0} {}

  /**
   * @brief Construct a new BitRef object.
   * @param bucket A pointer to the underlying storage.
   * @param mask The mask to select the bit of interest
   */
  BitRef(BitType* bucket, BitType const mask)
      : bucket_{bucket}
      , mask_{mask} {}

  /**
   * @brief Get the boolean value of the target bit.
   * @return The value
   */
  operator bool() const { return !!(*bucket_ & mask_); }

  /**
   * @brief Assignment from boolean value.
   * @param val The source value
   * @return this
   */
  auto operator=(bool const val) -> BitRef& {
    if (val) {
      *bucket_ |= mask_;
    } else {
      *bucket_ &= ~mask_;
    }
    return *this;
  }

  /**
   * @brief Assignment from BitRef.
   * @param ref The source BitReference
   * @return BitRef&
   */
  auto operator=(BitRef const& ref) -> BitRef& {
    *this = static_cast<bool>(ref);
    return *this;
  }

  /**
   * @brief Equality comparison.
   * @param rhs The right operand
   * @return Comparison result
   */
  auto operator==(BitRef const& rhs) -> bool {
    return static_cast<bool>(*this) == static_cast<bool>(rhs);
  }

  /**
   * @brief Less-than comparison.
   * @param rhs The right operand
   * @return Comparison result
   */
  auto operator<(BitRef const& rhs) -> bool {
    return !static_cast<bool>(*this) && static_cast<bool>(rhs);
  }

  /** @brief Flip the target bit. */
  auto flip() -> void { *bucket_ ^= mask_; }
};

class BitIterator {};

class BitVector {
private:
  /** The number of elements in the vector */
  std::size_t size_;
  /** The total capacity of the vector */
  std::size_t capacity_;
  /** The underlying storage */
  std::unique_ptr<BitType[]> storage_;

public:
  /** @brief Construct a new BitVector object. */
  BitVector()
      : size_{0}
      , capacity_{0}
      , storage_{nullptr} {}

  /**
   * @brief Copy construct a BitVector object.
   * @param other The source BitVector
   */
  BitVector(BitVector& other)
      : size_{other.size_}
      , capacity_{other.capacity_}
      , storage_{nullptr} {
    storage_ = std::make_unique<BitType[]>(other.capacity_ / sizeof(BitType));
    std::memset(storage_.get(), 0, capacity_ / CHAR_BIT);
    std::memcpy(storage_.get(), other.storage_.get(),
                (other.size_ + CHAR_BIT) / CHAR_BIT);
  }

  /**
   * @brief Copy-assign a BitVector object.
   * @param rhs The source BitVector
   * @return BitVector& this
   */
  auto operator=(BitVector& rhs) -> BitVector& {
    if (storage_) {
      storage_.release();
    }

    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    storage_ = std::make_unique<BitType[]>(rhs.capacity_ / sizeof(BitType));
    std::memset(storage_.get(), 0, capacity_ / CHAR_BIT);
    std::memcpy(storage_.get(), rhs.storage_.get(),
                (rhs.size_ + CHAR_BIT) / CHAR_BIT);

    return *this;
  }

  /**
   * @brief Move construct a BitVector object.
   * @param other The source BitVector
   */
  BitVector(BitVector&& other)
      : size_{other.size_}
      , capacity_{other.capacity_}
      , storage_{std::move(other.storage_)} {
    other.storage_ = nullptr;
  }

  /**
   * @brief Move-assign a BitVector object.
   * @param rhs The source BitVector
   * @return BitVector& this
   */
  auto operator=(BitVector&& rhs) -> BitVector& {
    if (storage_) {
      storage_.release();
    }

    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    storage_ = std::move(rhs.storage_);
    rhs.storage_ = nullptr;
    return *this;
  }

  /** @brief Destroy the BitVector object. */
  ~BitVector() = default;

  /**
   * @brief Return the number of elements in the vector.
   * @return The size
   */
  auto Size() const -> std::size_t { return size_; }

  /**
   * @brief Return the capacity of the vector (in elements).
   * @return The capacity
   */
  auto Capacity() const -> std::size_t { return capacity_; }

  /**
   * @brief Push a new value onto the vector.
   * @param val The boolean value
   */
  auto PushBack(bool const val) -> void {
    if (size_ == capacity_) {
      Expand();
    }
    ASSERT(capacity_ > size_, "Broken invariant.");
    if (val) {
      // The 'bucket' in which new bit is set
      auto const bucket = size_ / sizeof(BitType);
      storage_[bucket] |= (1UL << size_ % sizeof(BitType));
    }
    size_++;
  }

  /**
   * @brief Get the value at the specified index.=
   * @param index The index of interest
   * @return The value
   */
  auto operator[](std::size_t index) -> BitRef {
    if (index >= size_) {
      throw std::out_of_range("Index out of range.");
    }
    ASSERT(index < size_, "Broken precondition.");
    auto* bucket = &storage_[index / sizeof(BitType)];
    const auto mask = 1UL << index % sizeof(BitType);
    return BitRef{bucket, mask};
  }

  /**
   * @brief Get a reference to the first element.
   * @return A reference to the first element
   */
  auto Front() -> BitRef {
    if (size_ == 0) {
      throw std::out_of_range("Out of range.");
    }
    return BitRef{&storage_[0], 1UL};
  }

  /**
   * @brief Get a reference to the last element.
   * @return A reference to the last element
   */
  auto Back() -> BitRef {
    if (size_ == 0) {
      throw std::out_of_range("Out of range.");
    }
    return BitRef{&storage_[(size_ - 1) / sizeof(BitType)],
                  1UL << ((size_ - 1) % sizeof(BitType))};
  }

private:
  /**
   * @brief Expand the size of the underlying storage.
   */
  auto Expand() -> void {
    // Expand by doubling in size in the common case,
    // begin with a capacity of 8 elements for initial allocation.
    std::size_t const new_capacity = capacity_ == 0 ? 8 : 2 * capacity_;
    auto new_storage =
        std::make_unique<BitType[]>(new_capacity / sizeof(BitType));
    std::memset(new_storage.get(), 0, new_capacity / CHAR_BIT);
    if (storage_) {
      std::memcpy(new_storage.get(), storage_.get(),
                  (size_ + CHAR_BIT) / CHAR_BIT);
      storage_.release();
    }
    storage_ = std::move(new_storage);
    capacity_ = new_capacity;
  }
};
