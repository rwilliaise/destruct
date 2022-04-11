#pragma once

#include <tinyxml2.h>
#include "sh_reader.h"

using namespace tinyxml2;

class XMLReader : Reader {
public:
    explicit XMLReader(const char* filename) {
        doc.LoadFile(filename);
    }

private:
    XMLDocument doc;
};
