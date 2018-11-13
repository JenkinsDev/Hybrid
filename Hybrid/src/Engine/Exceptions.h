#ifndef __JINX_EXCEPTIONS_H_
#define __JINX_EXCEPTIONS_H_

#include <exception>

struct GameEngineInitializationException : public std::exception {};
struct GLFWResourceFailedException : public std::exception {};

#endif
