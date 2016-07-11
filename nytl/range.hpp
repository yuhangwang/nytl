/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 nyorain
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <nytl/bits/range.inl>

namespace nytl
{

///The Range class represents a part of a non-owned contigous sequence.
///Can be useful to pass mulitple parameters (without size limitations) to a function.
///Does not allocate any additional memory on the heap since it simply references the
///sequence it was constructed with. Therefore one must assure that the sequence will live longer
///than the Range object.
///Alternative names: span, array_view
template<typename T>
class Range
{
public:
	using Value = std::remove_const_t<T>;
	using Pointer = Value*;
	using ConstPointer = const Value*;
	using Reference = Value&;
	using ConstReference = const Value&;
	using Size = std::size_t;
	using Iterator = ConstPointer;
	using ConstIterator = ConstPointer;
	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	using value_type = Value;
	using pointer = Pointer;
	using const_pointer = ConstPointer;
	using reference = Reference;
	using const_reference = ConstReference;
	using iterator = Iterator;
	using const_iterator = ConstIterator;
	using reverse_iterator = ReverseIterator;
	using const_reverse_iterator = ConstReverseIterator;
	using size_type = Size;
	using difference_type = std::ptrdiff_t;

public:
	constexpr Range() noexcept = default;
	constexpr Range(std::nullptr_t ptr, std::size_t size = 1) noexcept : data_(nullptr), size_(0) {}
	constexpr Range(const T& value, std::size_t size = 1) noexcept : data_(&value), size_(size) {}
	constexpr Range(const T* value, std::size_t size = 1) noexcept : data_(value), size_(size) {}
	template<std::size_t N> constexpr Range(const T (&value)[N]) noexcept : data_(value), size_(N) {}

	template<typename C, typename = detail::ValidContainer<T, C>>
	Range(const C& con) noexcept : data_(&(*con.begin())), size_(con.end() - con.begin()) {}

	constexpr ConstPointer data() const noexcept { return data_; }
	constexpr std::size_t size() const noexcept { return size_; }
	constexpr bool empty() const noexcept { return size() == 0; }
	constexpr Size max_size() const noexcept { return size(); }

	constexpr Iterator begin() noexcept { return data_; }
	constexpr Iterator end() { return data_ + size_; }

	constexpr Iterator begin() const { return data_; }
	constexpr Iterator end() const { return data_ + size_; }

	constexpr ConstIterator cbegin() const { return data_; }
	constexpr ConstIterator cend() const { return data_ + size_; }

	constexpr ReverseIterator rbegin() const { return {end()}; }
	constexpr ReverseIterator rend() const { return {begin()}; }

	constexpr ConstReverseIterator crbegin() const { return {cend()}; }
	constexpr ConstReverseIterator crend() const { return {cbegin()}; }

	constexpr ConstReference operator[](Size i) const noexcept { return *(data_ + i); }
	constexpr ConstReference at(Size i) const
		{ if(i >= size_) throw std::out_of_range("Range::at"); return data_[i]; }

	ConstReference front() const { return *data_; }
	ConstReference back() const { return *(data_ + size_); }

	constexpr Range<T> slice(Size pos, Size size) const noexcept { return{data_ + pos, size}; }

protected:
	ConstPointer data_ = nullptr;
	Size size_ = 0;
};

///\{
///Utility functions for easily constructing a range object.
///Only needed until c++17.
template<typename T> Range<T>
makeRange(const T& value, std::size_t size){ return Range<T>(value, size); }

template<typename T> Range<T>
makeRange(const T* value, std::size_t size){ return Range<T>(value, size); }

template<template<class...> typename C, typename T, typename... TA> Range<T>
makeRange(const C<T, TA...>& container){ return Range<T>(container); }

template<typename T, std::size_t N> Range<T>
makeRange(const T (&array)[N]) { return Range<T>(array); }
///\}

}