/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Jan Kelling
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

///\file
///\brief Defines functions to dynamically output to different streams.

#pragma once

#include <nytl/misc.hpp>

#include <iostream>
#include <string>

namespace nytl
{

///Class to easily write output to a dynamically assigned stream.
class Logger
{
public:
    std::string prefix {};
    std::string name {"log"};
    std::ostream* stream {nullptr};

public:
    Logger() = default;
    Logger(std::ostream& os) : stream(&os){};
    Logger(const std::string& pre, const std::string& strm, std::ostream& str = std::cout) 
		: prefix(pre), name(strm), stream(&str) {}

	///Outputs the given args to the ostream if valid.
    template<typename... Args> inline
    void output(Args&&... args) const 
		{  if(stream) printVars(*stream, prefix, name, ": ", std::forward<Args>(args)..., "\n"); }

	///Operator wrapper for output().
    template<typename... Args> inline
    void operator()(Args&&... args) const 
		{ output(std::forward<Args>(args)...); }
};

}
