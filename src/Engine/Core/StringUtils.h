#pragma once
#ifndef __H_STRING_UTILS__
#define __H_STRING_UTILS__

#include <string>
#include <vector>
#include <Windows.h>
#include <sstream>
#include <stdio.h>

namespace core
{
    void FormatString(std::string& output, const char* format, ...);
    std::vector<std::string>& Split(const std::string& s, char delim, std::vector<std::string>& elems);
    std::vector<std::string> Split(const std::string& s, char delim);
    std::string GetFilenameExtension(const std::string& aFilename);
}

#endif