#include "Data.h"

Data32::Data32()
{
    data = nullptr;
}

Data32::~Data32()
{
    delete[] data;
}
