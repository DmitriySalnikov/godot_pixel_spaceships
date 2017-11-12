/* register_types.cpp */

#include "register_types.h"
#include "class_db.h"
#include "pixel_spaceships.h"

void register_pixel_spaceships_types() {
	ClassDB::register_class<PixelSpaceshipsOptions>();
	ClassDB::register_class<PixelSpaceshipsMask>();
	ClassDB::register_class<PixelSpaceships>();
}

void unregister_pixel_spaceships_types() {

}
