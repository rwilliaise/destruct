
#include "Model.h"
#include <cstdio>

namespace r {

	void LoadObj(std::string filename, Model &mdl) {
		std::FILE *f = fopen(filename.c_str(), "r");

		if (f == NULL) {
			return;
		}

		float tmp[3];


		
	}
} // r

