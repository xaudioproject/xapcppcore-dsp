//
//  Copyright 2019 - 2021 The XOrange Studio. All rights reserved.
//  Use of this source code is governed by a BSD-style license that can be
//  found in the LICENSE.md file.
//

#ifndef XAP_DSP_ERROR_H__
#define XAP_DSP_ERROR_H__

//
//  Imports.
//
#include <exception>
#include <string>

namespace xap {
namespace dsp {

//
//  Constants.
//

//  Error code.
const static uint16_t ERROR_PARAMETER        = 5101U;

//
//  Classes.
//

class Exception: public std::exception {
public:
    //
    //  Constructor & destructor.
    //

    /**
     *  Construct the object.
     * 
     *  @param message
     *      The error message.
     *  @param code
     *      The error code.
     */
    Exception(
        const char     *message,
        const uint16_t  code
    );

    /**
     *  Construct (Copy) the object.
     * 
     *  @param src
     *      The source object.
     */
    Exception(
        const Exception &src
    );

    /**
     *  Destruct the object.
     */
    virtual ~Exception() noexcept;

    /**
     *  Get the error message.
     * 
     *  @return
     *      The error message.
     */
    virtual const char* what() const noexcept;

    /**
     *  Get the error code.
     * 
     *  @return
     *      The error code.
     */
    virtual uint16_t get_code() const noexcept;

private:
    //
    //  Members.
    //

    //  The error message.
    std::string m_message;
    uint16_t    m_code;
};

}  //  namespace dsp
}  //  namespace xap

#endif  //  #ifndef XAP_DSP_ERROR_H__