//
//  Copyright 2019 - 2020 The XOrange Studio. All rights reserved.
//  Use of this source code is governed by a BSD-style license that can be
//  found in the LICENSE.md file.
//

//
//  Imports.
//
#include <stdio.h>
#include <xap/dsp/io.h>

//
//  Entry.
//
int main() {
    const uint8_t pcm_data[16] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10
    };
    int16_t audio_data[8] = { 0x0000 };
    const int16_t expected_sample[8] = {
        0x0201, 0x0403, 0x0605, 0x0807,
        0x0A09, 0x0C0B, 0x0E0D, 0x100F
    };
    
    xap::dsp::read_data_s16_le(
        pcm_data, 
        16U,
        audio_data,
        8U
    );
    for (size_t i = 0U; i < 8U; ++i) {
        if (audio_data[i] != expected_sample[i]) {
            printf("Read unexpected audio sample data.\n");
            abort();
        }
    }

    uint8_t sample[16];
    xap::dsp::write_data_s16_le(
        expected_sample,
        8U,
        sample,
        16U
    );
    for (size_t i = 0U; i < 16U; ++i) {
        if (sample[i] != pcm_data[i]) {
            printf("Write unexpected PCM data.\n");
            abort();
        }
    }

    return 0;
}