#pragma once

#include "Data.h"
#include "utils/cool_ints.h"

struct WavHeader
{
    WavHeader() = default;
    WavHeader(const Data& data);
    void init(i32 data_size, i16 n_channels, i32 sample_rate, i32 bit_depth);
    // the main chunk
    unsigned char main_chunk_ID[4];
    u32 chunk_size;
    unsigned char riff_type[4];

    // sub chunk 1 "fmt "
    unsigned char fmt_chunk_ID[4];
    u32 fmt_chunk_size;
    u16 audio_format;
    u16 n_channels;
    u32 sample_rate;
    u32 byte_rate;
    u16 block_align;
    u16 bit_depth;

    // sub chunk 2 "data"
    unsigned char data_chunk_ID[4];
    u32 data_size;

    // then comes the data!
};

struct WavFile
{
    WavFile() = delete;
    WavFile(const Data& data) : header{WavHeader(data)}, data{data} {};
    bool write(const char* name);

    WavHeader header;
    const Data& data;
};
