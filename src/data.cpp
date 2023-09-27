#include "data.h"

FloatData::FloatData(u32 size_)
{
    size = size_;
    data = new float[size];

    for (u32 i = 0; i < size; i++)
        data[i] = 0.0f;
}

FloatData::~FloatData()
{
    delete[] data;
}

void FloatData::normalize(void)
{
    float max_abs = 0.0f;
    float current;

    for (u32 i = 0; i < size; i++)
    {
        current = fabs(data[i]);
        if (isgreater(current, max_abs))
            max_abs = current;
    }

    if (max_abs == 0.0f)
        return;

    for (u32 i = 0; i < size; i++)
    {
        data[i] = data[i] / max_abs;
    }
}

void FloatData::write_to_csv(void)
{
    std::ofstream csv;
    csv.open("float_data.csv");
    for (u32 i = 0; i < size; i++)
    {
        csv << data[i] << ",";
    }
    csv << std::endl;
    csv.close();
}
