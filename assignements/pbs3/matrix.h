#pragma once

/**
* Allocates memory for N by M matrix that contain elements of unit_size bytes
*/ 
void** mat_init(unsigned N, unsigned M, unsigned unit_size);

/**
* Frees the memory allocated by mat_init
*/
void mat_free(void** mat);