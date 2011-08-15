/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2010, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */
#pragma once
#include <stdexcept>
#include <cstdarg>
#include <cstdio>
#include <sstream>

#define THROW_PCL_EXCEPTION(format,...) throwPCLException( __PRETTY_FUNCTION__, __FILE__, __LINE__, format , ##__VA_ARGS__ )
namespace pcl
{
  /**
   * @class PCLException
   * @brief A base class for all pcl exceptions which inherits from std::runtime_error
   */
  class PCLException : public std::runtime_error
  {
  public:

    PCLException (const std::string& error_description,
                  const std::string& file_name = "",
                  const std::string& function_name = "" ,
                  unsigned line_number = 0) throw ()
    : std::runtime_error (error_description)
    , file_name_ (file_name)
    , function_name_ (function_name)
    , line_number_ (line_number)
 { }

    virtual ~PCLException () throw ()
    {}

    const std::string&
    getFileName () const throw ()
    {
      return file_name_;
    }

    const std::string&
    getFunctionName () const throw ()
    {
      return function_name_;
    }

    unsigned
    getLineNumber () const throw ()
    {
      return line_number_;
    }

    std::string detailedMessage () const throw ()
    {
      std::stringstream sstream;
      if (function_name_ != "")
        sstream << function_name_ << " ";

      if (file_name_ != "")
      {
        sstream << "in " << file_name_ << " ";
        if (line_number_ != 0)
          sstream << "@ " << line_number_ << " ";
      }
      sstream << ":" << what ();

      return sstream.str ();
    }

  protected:
    std::string file_name_;
    std::string function_name_;
    unsigned line_number_;
  } ;

  inline void throwPCLException (const char* function, const char* file, unsigned line, const char* format, ...)
  {
    char msg[1024];
    va_list args;
    va_start (args, format);
    vsprintf (msg, format, args);

    throw PCLException (msg, file, function, line);
  }
}
