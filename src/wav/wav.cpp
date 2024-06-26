#include "wav.h"

#include <cstdio>
#include <cstring>

#define UNCOMPRESSED_PCM 1

#define CHUNK_HEADER_SIZE 8
#define FMT_CHUNK_SIZE 16

#define N_CHANNELS_FOR_NOW 1

static void fill_four_char_code(void* dest, const char fourcc[4]);

WavHeader::WavHeader(const Data& data)
{
    init(data.size * data.sample_size_byte, N_CHANNELS_FOR_NOW,
         data.sample_rate, data.bit_depth);
}

void WavHeader::init(i32 data_size,
                     i16 n_channels,
                     i32 sample_rate,
                     i32 bit_depth)
{
    fill_four_char_code(this->main_chunk_ID, "RIFF");
    this->chunk_size = (sizeof(WavHeader) - CHUNK_HEADER_SIZE) + data_size;
    fill_four_char_code(this->riff_type, "WAVE");

    fill_four_char_code(this->fmt_chunk_ID, "fmt ");
    this->fmt_chunk_size = FMT_CHUNK_SIZE;
    this->audio_format = UNCOMPRESSED_PCM;
    this->n_channels = n_channels;
    this->sample_rate = sample_rate;
    this->bit_depth = bit_depth;
    this->byte_rate = n_channels * sample_rate * (bit_depth / 8);
    this->block_align = n_channels * (bit_depth / 8);

    fill_four_char_code(this->data_chunk_ID, "data");
    this->data_size = data_size;
}

bool WavFile::write(const char* name)
{
    FILE* file = fopen(name, "w+b");
    if (!file)
        return false;

    fwrite(&header, sizeof(header), 1, file);
    data.write(file, header.data_size);

    fclose(file);

    return true;
}

static void fill_four_char_code(void* dest, const char fourcc[4])
{
    memcpy(dest, fourcc, 4);
}
