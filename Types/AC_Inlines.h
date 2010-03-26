#pragma once

// Include this later

inline void QuadCopy (void* from, void* to, int n) // be sure it has four bytes
{
   unsigned char* b = reinterpret_cast<unsigned char*>(from);
   unsigned char* a = reinterpret_cast<unsigned char*>(to);
   a[0] = b[0];   // most cpus will load all four of these into the int pipes
   a[1] = b[1];   // or the optimized compiler will fix it.
   a[2] = b[2];
   a[3] = b[3];
}