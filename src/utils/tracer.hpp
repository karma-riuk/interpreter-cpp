#pragma once
#include <iostream>
#include <string>

namespace {
    struct FunctionTracer {
        std::string name;
        inline static int tab_counter = 0;

        FunctionTracer(const std::string& func): name(func) {
            std::cout << std::string(tab_counter++, '\t') << "BEGIN " << name
                      << std::endl;
        }

        ~FunctionTracer() {
            std::cout << std::string(--tab_counter, '\t') << "Exiting " << name
                      << std::endl;
        }
    };
} // namespace

#ifndef TRACE
#define TRACE 0
#endif

#if TRACE
#define TRACE_FUNCTION FunctionTracer tracer(__FUNCTION__);
#else
#define TRACE_FUNCTION
#endif
