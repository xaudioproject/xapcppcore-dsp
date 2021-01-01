//
//  Copyright 2019 - 2021 The XOrange Studio. All rights reserved.
//  Use of this source code is governed by a BSD-style license that can be
//  found in the LICENSE.md file.
//

//
//  Imports.
//
#include <xap/dsp/error.h>
#include <xap/dsp/io.h>

namespace xap {
namespace dsp {

//
//  Declare.
//

/**
 *  Read signed 16-bit integer with little-endian.
 * 
 *  @param src_data
 *      The source data.
 *  @return
 *      The signed 16-bit integer.
 */
static int16_t read_sint16_le(const uint8_t *src_data);

/**
 *  Write signed 16-bit integer with little-endian.
 * 
 *  @param src_data
 *      The source signed 16-bit integer.
 *  @param dst_data
 *      The destination data
 */
static void write_sint16_le(const int16_t *src_data, uint8_t *dst_data);

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
) {
    //
    //  Parameter(s) check.
    //
    if (src_data == nullptr) {
        throw xap::dsp::Exception(
            "src_data == nullptr",
            xap::dsp::ERROR_PARAMETER
        );
    }
    if (dst_data == nullptr) {
        throw xap::dsp::Exception(
            "dst_data == nullptr",
            xap::dsp::ERROR_PARAMETER
        );
    }
    if (src_count > dst_count * 2U) {
        throw xap::dsp::Exception(
            "src_count > dst_count * 2U", 
            xap::dsp::ERROR_PARAMETER
        );
    }

    const size_t read_count = src_count / 2U;
    for (size_t i = 0U; i < read_count; ++i) {
        dst_data[i] = read_sint16_le(src_data + i * 2U);
    }
}

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
    const int16_t  *src_data,
    const size_t     src_count,
    uint8_t         *dst_data,
    size_t           dst_count
) {
    //
    //  Parameter(s) check.
    //
    if (src_data == nullptr) {
        throw xap::dsp::Exception(
            "src_data == nullptr",
            xap::dsp::ERROR_PARAMETER
        );
    }
    if (dst_data == nullptr) {
        throw xap::dsp::Exception(
            "dsp_data == nullptr",
            xap::dsp::ERROR_PARAMETER
        );
    }
    if (src_count * 2U > dst_count) {
        throw xap::dsp::Exception(
            "src_count * 2U > dst_count",
            xap::dsp::ERROR_PARAMETER
        );
    }

    const size_t write_count = src_count;
    for (size_t i = 0U; i < write_count; ++i) {
        write_sint16_le(src_data + i, dst_data + i * 2U);
    }
}

//
//  Private functions.
//

/**
 *  Read signed 16-bit integer with little-endian.
 * 
 *  @param src_data
 *      The source data.
 *  @return
 *      The signed 16-bit integer.
 */
static int16_t read_sint16_le(const uint8_t *src_data) {
    return (
        static_cast<int16_t>(src_data[0]) |
        (static_cast<int16_t>(src_data[1]) << 8U)
    );
}

/**
 *  Write signed 16-bit integer with little-endian.
 * 
 *  @param src_data
 *      The source signed 16-bit integer.
 *  @param dst_data
 *      The destination data
 */
static void write_sint16_le(const int16_t *src_data, uint8_t *dst_data) {
    dst_data[0] = static_cast<uint8_t>(
        src_data[0] & 0x00FF
    );
    dst_data[1] = static_cast<uint8_t>(
        (src_data[0] >> 8U) & 0x00FF
    );
}

}  //  namespace dsp
}  //  namespace xap