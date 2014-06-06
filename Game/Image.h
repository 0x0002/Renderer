#ifndef IMAGE_H
#define IMAGE_H

#include "Core/StdTypes.h"
#include "Container/FilePath.h"

void WritePPM( FilePath const &path, uint32_t width, uint32_t height, float const *data );

#endif // IMAGE_H