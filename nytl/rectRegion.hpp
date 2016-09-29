// Copyright (c) 2016 nyorain 
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt

///\file
///\brief Defines the RectRegion template class for representing an area consisting of Rects.

#pragma once

#ifndef NYTL_INCLUDE_RECTREGION_HPP
#define NYTL_INCLUDE_RECTREGION_HPP

#include <nytl/vec.hpp>
#include <nytl/rect.hpp>
#include <nytl/triangle.hpp>
#include <nytl/line.hpp>

#include <vector>

namespace nytl
{

//typedef
template<std::size_t D, typename P> class RectRegion;

template<class P> using RectRegion2 = RectRegion<2, P>;
template<class P> using RectRegion3 = RectRegion<3, P>;
template<class P> using RectRegion4 = RectRegion<4, P>;

using RectRegion2i = RectRegion<2, int>;
using RectRegion2ui = RectRegion<2, unsigned int>;
using RectRegion2d = RectRegion<2, double>;
using RectRegion2f = RectRegion<2, float>;

using RectRegion3i = RectRegion<3, int>;
using RectRegion3ui = RectRegion<3, unsigned int>;
using RectRegion3d = RectRegion<3, double>;
using RectRegion3f = RectRegion<3, float>;

using RectRegion4i = RectRegion<4, int>;
using RectRegion4ui = RectRegion<4, unsigned int>;
using RectRegion4d = RectRegion<4, double>;
using RectRegion4f = RectRegion<4, float>;

///\ingroup math
///Region composed of Rectangles.
template<std::size_t D, typename P>
class RectRegion
{
public:
	//naming conformance
	using Precision = P;
	using Size = std::size_t;
	constexpr static Size dim = D;

	using Reference = Precision&;
	using ConstReference = const Precision&;
	using Pointer = Precision*;
	using ConstPointer = const Precision*;

	using RectRegionType = RectRegion;
	using VecType = Vec<dim, Precision>;
	using RectType = Rect<dim, Precision>;
	using LineType = Line<dim, Precision>;

	//stl conformance
	using value_type = Precision;
	using size_type = Size;
	using reference = Reference;
	using const_reference = ConstReference;
	using pointer = Pointer;
	using const_pointer = ConstPointer;


public:
	std::vector<RectType> rects_ {};

public:
	RectRegion(const std::vector<RectType>& rects) : rects_(rects) {};
	RectRegion() noexcept = default;
	~RectRegion() noexcept = default;

	RectRegion(const RectRegionType& other) = default;
	RectRegion& operator=(const RectRegionType& other) = default;

	RectRegion(RectRegionType&& other) noexcept = default;
	RectRegion& operator=(RectRegionType&& other) noexcept = default;

	//change the RectRegion
	void add(const RectType& r);
	void add(const RectRegionType& r);

	void addNoCheck(const RectType& r);
	void addNoCheck(const RectRegionType& r);

	void subtract(const RectType& r);
	void subtract(const RectRegionType& r);

	//operator
	RectRegion& operator|=(const RectType& r);
	RectRegion& operator|=(const RectRegionType& r);

	RectRegion& operator&=(const RectType& r);
	RectRegion& operator&=(const RectRegionType& r);

	RectRegion& operator^=(const RectType& r);
	RectRegion& operator^=(const RectRegionType& r);

	//
	RectType extents() const;

	const std::vector<RectType>& rects() const { return rects_; }
	std::vector<RectType>& rects() { return rects_; }

	template<Size OD, typename OP>
	operator RectRegion<OD, OP>() const
	{
		auto ret = RectRegion<OD, OP>{};
		ret.rects_.insert(ret.rects_.cend(), rects_.cbegin(), rects_.cend());
		return ret;
	}
};

//operators
#include <nytl/bits/rectRegion.inl>

}

#endif //header guard
