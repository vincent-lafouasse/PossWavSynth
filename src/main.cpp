#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define WAV_PATH "wave.wav"
#define BUFFER_SIZE 1024

typedef uint32_t u32;
typedef int32_t i32;
typedef uint16_t u16;
typedef int16_t i16;

struct WavHeader
{
	static WavHeader init(i32 data_size, i16 n_channels, i32 sample_rate, i32 bit_depth);
	//the main chunk
	unsigned char chunk_ID[4];
	u32 chunk_size;
	unsigned char format[4];

	//sub chunk 1 "fmt "
	unsigned char fmt_chunk_ID[4];
	u32 fmt_chunk_size;
	u16 audio_format;
	u16 n_channels;
	u32 sample_rate;
	u32 byte_rate;
	u16 block_align;
	u16 bit_depth;

	//sub chunk 2 "data"
	unsigned char data_chunk_ID[4];
	u32 data_chunk_size;

 	//then comes the data!
};

WavHeader WavHeader::init(i32 data_size, i16 n_channels, i32 sample_rate, i32 bit_depth)
{
	WavHeader h;

	memcpy(h.chunk_ID, "RIFF", 4);
	h.chunk_size = 36 + data_size;
	memcpy(h.format, "WAVE", 4);

	memcpy(h.fmt_chunk_ID, "fmt", 4);
	h.fmt_chunk_size = 16;
	h.audio_format = 1;
	h.n_channels = n_channels;
	h.sample_rate = sample_rate;
	h.bit_depth = bit_depth;
	h.byte_rate = n_channels * sample_rate * (bit_depth / 8);
	h.block_align = n_channels * (bit_depth / 8);
	
	memcpy(h.data_chunk_ID, "data", 4);
	h.data_chunk_size = data_size;

	return h;
}

struct WavFile
{
	static WavFile init(const char *name, WavHeader *header, void *data);
	bool write(void);

	const char* name;
	WavHeader* header;
	void* data;
};

WavFile WavFile::init(const char *name, WavHeader *header, void *data)
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

	fwrite(&header, sizeof(*header), 1, file);
	fwrite(data, header->data_chunk_size, 1, file);

	fclose(file);

	return true;
}

int main()
{
	int sample_rate = 44100;
	int n_channels = 1;
	int n_seconds = 4;

	i32 data_size = sample_rate * n_seconds * n_channels;
	i32* data = new int[data_size];
	u16 bit_depth = 32;

	i32 frequency = 440;

	i32 period = sample_rate / frequency;

	i32 sample_value = 0;
	for (int i = 0; i < data_size; i++)
	{
		if (i % period == 0)
			sample_value = 0;
		data[i] = sample_value;
		sample_value += 8000;
		std::cout << sample_value << std::endl;
	}

	WavHeader header = WavHeader::init(data_size, n_channels, sample_rate, bit_depth);

	WavFile wav_file = WavFile::init("wave.wav", &header, data);
	
	if (wav_file.write())
		std::cout << "success" << std::endl;
	else
		std::cout << "rip" << std::endl;

	delete[] data;
}
