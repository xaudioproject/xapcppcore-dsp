//
//  Copyright 2019 - 2021 The XOrange Studio. All rights reserved.
//  Use of this source code is governed by a BSD-style license that can be
//  found in the LICENSE.md file.
//

#ifndef XAP_DSP_IO_H__
#define XAP_DSP_IO_H__

//
//  Imports.
//
#include <stdint.h>
#include <stdlib.h>

namespace xap {
namespace dsp {

//
//  Public functions.
//

/**
 *  Read PCM data (signed, little-endian, 16-bits) to audio sample rate.
 * 
 *  @throw xap::dsp::Exception
 *      Raised in the following situations:
 *      
 *          - xap::dsp::ERROR_PARAMETER:
 *              src_data == nullptr
 * 
 *          - xap::dsp::ERROR_PARAMETER:
 *              dst_data == nullptr
 * 
 *          - xap::dsp::ERROR_PARAMETER:
 *              src_count > dst_count * 2U
 * 
 *  @param src_data
 *      The PCM data.
 *  @param src_count
 *      The count of unsigned 8-bit integer.
 *  @param dst_data
 *      The audio sample data
 *  @param dst_count
 *      The count of signed 16-bit integer.
 */
void read_data_s16_le(
    const uint8_t *src_data,
    const size_t src_count,
    int16_t *dst_data,
    const size_t dst_count 
);

/**
 *  Write audio sample data to PCM data (signed , little-endian, 16-bits).
 * 
 *  @throw xap::dsp::Exception:
 *      Raised in the following situations:
 * 
 *          - xap::dsp::ERROR_PARAMETER:
 *              src_data == nullptr
 * 
 *          - xap::dsp::ERROR_PARAMETER:
 *              dsp_data == nullptr
 * 
 *          - xap::dsp::ERROR_PARAMETER:
 *              src_count * 2U > dst_count
 * 
 *  @param src_data
 *      The audio sample data.
 *  @param src_count
 *      The count of signed 16-bit integer.
 *  @param dst_data
 *      The PCM data.
 *  @param dst_count
 *      The count of unsigned 8-bit integer.
 */
void write_data_s16_le(
    const int16_t *src_data,
    const size_t src_count,
    uint8_t *dst_data,
    const size_t dst_count
);

}  //  namespace dsp
}  //  namespace xap

#endif  //  #ifndef XAP_DSP_IO_H__