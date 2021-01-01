//
//  Copyright 2019 - 2021 The XOrange Studio. All rights reserved.
//  Use of this source code is governed by a BSD-style license that can be
//  found in the LICENSE.md file.
//

#ifndef XAP_DSP_AMPLIFY_H__
#define XAP_DSP_AMPLIFY_H__

//
//  Imports.
// 
#include <stdint.h>
#include <stdlib.h>

namespace xap {
namespace dsp {

/**
 *  Amplify an audio.
 * 
 *  @param sample
 *      The source audio sample data.
 *  @param sample_count
 *      The count of signed 16-bit integer.
 *  @param threshold
 *      The silent threshold (must be non-negative).
 *  @param amp_min_value
 *      The minimum amplified value (must be negative).
 *  @param amp_max_value
 *      The maximum amplified value (must be positive).
 *  @param rounding
 *      True if rounding.
 */
void amplify(
    int16_t *sample,
    const size_t sample_count,
    const int16_t threshold,
    const int16_t amp_min_value,
    const int16_t amp_max_value,
    const bool rounding = false
);

}  //  namespace dsp
}  //  namepsace xap

#endif  //  #ifndef XAP_DSP_AMPLIFY_H__