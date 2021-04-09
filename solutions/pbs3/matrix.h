#pragma once

void** mat_init(unsigned N, unsigned M, unsigned unit_size);

void mat_free(void** mat);