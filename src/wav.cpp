#include "wav.h"

#include <cstdio>
#include <cstring>

#define UNCOMPRESSED_PCM 1

#define CHUNK_HEADER_SIZE 8
#define FMT_CHUNK_SIZE 16
#define RIFF_TYPE_SIZE 4

WavHeader WavHeader::init(i32 data_size,
                          i16 n_channels,
                          i32 sample_rate,
                          i32 bit_depth)
{
    WavHeader h;

    memcpy(h.main_chunk_ID, "RIFF", 4);
    h.chunk_size = RIFF_TYPE_SIZE + CHUNK_HEADER_SIZE + FMT_CHUNK_SIZE +
                   CHUNK_HEADER_SIZE + data_size;
    memcpy(h.riff_type, "WAVE", 4);

    memcpy(h.fmt_chunk_ID, "fmt ", 4);
    h.fmt_chunk_size = FMT_CHUNK_SIZE;
    h.audio_format = UNCOMPRESSED_PCM;
    h.n_channels = n_channels;
    h.sample_rate = sample_rate;
    h.bit_depth = bit_depth;
    h.byte_rate = n_channels * sample_rate * (bit_depth / 8);
    h.block_align = n_channels * (bit_depth / 8);

    memcpy(h.data_chunk_ID, "data", 4);
    h.data_size = data_size;

    return h;
}

WavFile WavFile::init(const char* name, WavHeader* header, void* data)
{
    WavFile f;

    f.name = name;
    f.header = header;
    f.data = data;

    return f;
}

bool WavFile::write()
{
    FILE* file = fopen(name, "w+b");
    if (!file)
        return false;

    fwrite(header, sizeof(*header), 1, file);
    fwrite(data, header->data_size, 1, file);

    fclose(file);

    return true;
}
