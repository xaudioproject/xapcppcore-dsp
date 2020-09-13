//
//  Copyright 2019 - 2020 The XOrange Studio. All rights reserved.
//  Use of this source code is governed by a BSD-style license that can be
//  found in the LICENSE.md file.
//

//
//  Imports.
//
#include <cmath>
#include <cstdlib>
#include <xap/dsp/amplify.h>
#include <xap/dsp/error.h>

namespace xap {
namespace dsp{

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
    const bool rounding
) {
    //
    //  Parameter(s) check.
    //
    if (threshold < 0) {
        throw xap::dsp::Exception(
            "threshold < 0",
            xap::dsp::ERROR_PARAMETER
        );
    }
    if (amp_min_value >= 0) {
        throw xap::dsp::Exception(
            "amp_min_value >= 0",
            xap::dsp::ERROR_PARAMETER
        );
    }
    if (amp_max_value <= 0) {
        throw xap::dsp::Exception(
            "amp_max_value <= 0",
            xap::dsp::ERROR_PARAMETER
        );
    }
    
    //  Fast path for empty audio.
    if (sample_count == 0U) {
        return;
    }

    //  Get the min/max sample audio.
    bool silent = true;
    int16_t i_min_value = sample[0];
    int16_t i_max_value = sample[0];
    for (size_t i = 1U; i < sample_count; ++i) {
        int16_t value = sample[i];
        if (silent) {
            if (std::abs(value) >= threshold) {
                silent = false;
            }
        }
        if (value < i_min_value) {
            i_min_value = value;
        } else if (value > i_max_value) {
            i_max_value = value;
        }
    }

    //  Do NOT amplify if the audio is silent.
    if (silent) {
        return;
    }

    //  Get the amplify ratio.
    double ratio = 0.0;
    if (i_max_value > 0) {
        ratio = 
            static_cast<double>(amp_max_value) / 
            static_cast<double>(i_max_value);
    }
    if (i_min_value < 0) {
        double ratio_neg = 
            static_cast<double>(amp_min_value) / 
            static_cast<double>(i_min_value);
        if (ratio == 0.0 || ratio_neg < ratio) {
            ratio = ratio_neg;
        }
    }
    if (ratio == 0.0) {
        ratio = 1.0;
    }

    //  Do amplification.
    double amp_min_double_value = static_cast<double>(amp_min_value);
    double amp_max_double_value = static_cast<double>(amp_max_value);
    for (size_t i = 0U; i < sample_count; ++i) {
        double value = static_cast<double>(sample[i]) * ratio;
        if (rounding) {
            value = std::round(value);
        }
        if (value < amp_min_double_value) {
            value = amp_min_double_value;
        } else if (value > amp_max_double_value) {
            value = amp_max_double_value;
        }
        sample[i] = static_cast<int16_t>(value);
    }
}
 
}  //  namespace dsp
}  //  namespace xap