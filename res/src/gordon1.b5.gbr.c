#pragma bank 5
const unsigned char gordon1CGB[] = {
	0x00,0x00,0x00,0x00
};

const unsigned char gordon1_tiles[] = {
	//Frame 0
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x19,0x19,0x12,0x1f,0x26,0x3d,0x4a,0x7d,
	0x40,0x7f,0x3c,0x3b,0x1c,0x1f,0x20,0x3f,
	0x40,0x7f,0x30,0x3f,0x0e,0x19,0x2f,0x30,
	0x2e,0x31,0x37,0x29,0x11,0x1f,0x3e,0x3e,
	
	//Frame 1
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x19,0x19,0x12,0x1f,0x26,0x3d,0x4a,0x7d,
	0x40,0x7f,0x3c,0x3b,0x1c,0x1f,0x20,0x3f,
	0x40,0x7f,0x30,0x3f,0x1f,0x18,0x2e,0x31,
	0x36,0x29,0x11,0x1f,0x3f,0x3f,0x00,0x00,
	
	//Frame 2
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x19,0x19,0x12,0x1f,0x26,0x3d,
	0x4a,0x7d,0x40,0x7f,0x3c,0x3b,0x20,0x3f,
	0x40,0x7f,0x30,0x3f,0x0e,0x19,0x2f,0x30,
	0x2e,0x31,0x37,0x29,0x11,0x1f,0x3e,0x3e,
	
	//Frame 3
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x19,0x19,0x12,0x1f,0x26,0x3d,0x4a,0x7d,
	0x40,0x7f,0x3c,0x3b,0x1c,0x1f,0x20,0x3f,
	0x40,0x7f,0x30,0x3f,0x0e,0x19,0x2f,0x30,
	0x2f,0x31,0x37,0x29,0x10,0x1e,0x3e,0x3e
};

#include "TilesInfo.h"
const struct TilesInfoInternal gordon1_internal = {
	16, //width
	16, //height
	4, //num_tiles
	gordon1_tiles, //tiles
	gordon1CGB, //CGB palette
};
struct TilesInfo gordon1 = {
	5, //bank
	&gordon1_internal, //data
};