
#include "Model.h"
#include <cstdio>

namespace r {

	void LoadObj(std::string filename, Model &mdl) {
		std::FILE *f = fopen(filename.c_str(), "r");

		if (f == NULL) {
			return;
		}

		float tmp[3];

		for (int i = 0; i < fileSize; ++i) {
			char c = p[i];
			
			if (c == '\n') {
				tmp[0] = 0; tmp[1] = 0; tmp[2] = 0;
				continue;
			}
		}

		
	}
} // r

