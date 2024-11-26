#pragma once
#include <iostream>
#include <string>

#ifndef DIST
#define SQ_LOG(X) std::cout << X << std::endl;
#endif


#ifdef DIST

#define SQ_LOG(X)

#endif
