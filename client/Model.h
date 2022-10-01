
#ifndef DESTRUCT_MODEL_H
#define DESTRUCT_MODEL_H

#include "Render.h"
#include <string>

namespace r {

	class Model : r::VaoOwner {
	public:
		Model(uint32_t vertexCount): vertexCount(vertexCount) {
		}

		friend void LoadObj(std::string, Model&);

		static Model fromFilename(std::string filename);

	private:
		uint32_t vertexCount;
	};

	void LoadObj(std::string filename, Model& mdl);
	
} // r

#endif // DESTRUCT_MODEL_H
