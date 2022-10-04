
#ifndef DESTRUCT_ENTITY_H
#define DESTRUCT_ENTITY_H

#include <LinearMath/btVector3.h>

namespace sh {

	class Entity {
	public:
		Entity();
		
	private:
		btVector3 pos;

	};
} // sh

#endif // DESTRUCT_ENTITY_H
