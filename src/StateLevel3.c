#include "Banks/SetAutoBank.h"
#include <gbdk/platform.h>
#include "ZGBMain.h"
#include "Music.h"
#include "Scroll.h"
#include "Sound.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "../src/GlobalVars.h"

IMPORT_MAP (level3map);
IMPORT_MAP (hud);

UINT16 level3counter = 0;

UINT8 anim_water_counter3 = 0;
UINT8 anim_flag_counter3 = 0;
UINT8 flagpole_activated3 = 0;
UINT8 flagpole_stars3 = 0;
UINT8 endlevel_counter3 = 0;

//pink color palette
const UWORD pal_pink3[] = { RGB(31, 31, 31), RGB(19, 26, 30), RGB(28, 19, 30), RGB(0,  0,  0) };

const UINT8 collision_tiles_level3[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,95,96,97,98, 0};
const UINT8 collision_tiles_down_level3[] = {29,30,31,32};

DECLARE_MUSIC(quickstart);
DECLARE_MUSIC(mushrooms);
DECLARE_MUSIC(flagpole);
DECLARE_MUSIC(quickdeath);

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
extern Sprite * spr_nutmeg;
//extern Sprite * spr_nutmeg2;
extern Sprite * spr_camera;
//struct Sprite * spr_nutmegbow;

//water tiles are stored in 1A, 1B, and 1C
//in GBTD, water is 26, 27, 28
const unsigned char level3_water1[] = {
	0x00,0x08,0x08,0x3c,0x3c,0xff,0xff,0xfb,
	0xff,0xdf,0xf7,0xff,0x7f,0xff,0xfd,0xff
};
const unsigned char level3_water2[] = {
	0x00,0x20,0x20,0xf3,0xf3,0xff,0xff,0xff,
	0xdf,0xff,0xff,0xf7,0x7f,0xff,0xfd,0xff
};
const unsigned char level3_water3[] = {
	0x00,0x82,0x82,0xcf,0xcf,0xff,0xff,0xfb,
	0xdf,0xff,0xff,0xf7,0x7f,0xff,0xfd,0xff
};

/*
//water anim data locations
const unsigned char level_water_anim1[] = { 0x1A };
const unsigned char level_water_anim2[] = { 0x1B };
const unsigned char level_water_anim3[] = { 0x1C };
*/

//grey top
const unsigned char grey3_33[] = {
	0xff,0x3c,0xc3,0x46,0x81,0x81,0x81,0x81,
	0x81,0xe1,0x81,0xf9,0x81,0xff,0x81,0xff
};
const unsigned char grey3_34[] = {
	0xff,0x3c,0xc3,0x7e,0x81,0x9f,0x81,0x87,
	0x81,0x81,0x81,0x81,0x81,0xe1,0x81,0xf9
};
const unsigned char grey3_35[] = {
	0xff,0x3c,0xc3,0x7a,0x81,0xff,0x81,0xff,
	0x81,0x9f,0x81,0x87,0x81,0x81,0x81,0x81
};
const unsigned char grey3_36[] = {
	0xff,0x3c,0xc3,0x42,0x81,0xe1,0x81,0xf9,
	0x81,0xff,0x81,0xff,0x81,0x9f,0x81,0x87
};

//pink top
const unsigned char pink3_37[] = {
	0xff,0x3c,0xc3,0x42,0x81,0x87,0x81,0x9f,
	0x81,0xff,0x81,0xff,0x81,0xf9,0x81,0xe1
};
const unsigned char pink3_38[] = {
	0xff,0x3c,0xc3,0x5e,0x81,0xff,0x81,0xff,
	0x81,0xf9,0x81,0xe1,0x81,0x81,0x81,0x81
};
const unsigned char pink3_39[] = {
	0xff,0x3c,0xc3,0x7e,0x81,0xf9,0x81,0xe1,
	0x81,0x81,0x81,0x81,0x81,0x87,0x81,0x9f
};
const unsigned char pink3_40[] = {
	0xff,0x3c,0xc3,0x62,0x81,0x81,0x81,0x81,
	0x81,0x87,0x81,0x9f,0x81,0xff,0x81,0xff
};

//grey mid/bottom
const unsigned char grey3_41[] = {
	0x81,0x9f,0x81,0x87,0x81,0x81,0x81,0x81,
	0x81,0xe1,0x81,0xf9,0x81,0xff,0x81,0xff
};
const unsigned char grey3_42[] = {
	0x81,0xff,0x81,0xff,0x81,0x9f,0x81,0x87,
	0x81,0x81,0x81,0x81,0x81,0xe1,0x81,0xf9
};
const unsigned char grey3_43[] = {
	0x81,0xe1,0x81,0xf9,0x81,0xff,0x81,0xff,
	0x81,0x9f,0x81,0x87,0x81,0x81,0x81,0x81
};
const unsigned char grey3_44[] = {
	0x81,0x81,0x81,0x81,0x81,0xe1,0x81,0xf9,
	0x81,0xff,0x81,0xff,0x81,0x9f,0x81,0x87
};

//pink mid/bottom
const unsigned char pink3_45[] = {
	0x81,0x81,0x81,0x81,0x81,0x87,0x81,0x9f,
	0x81,0xff,0x81,0xff,0x81,0xf9,0x81,0xe1
};
const unsigned char pink3_46[] = {
	0x81,0x87,0x81,0x9f,0x81,0xff,0x81,0xff,
	0x81,0xf9,0x81,0xe1,0x81,0x81,0x81,0x81
};
const unsigned char pink3_47[] = {
	0x81,0xff,0x81,0xff,0x81,0xf9,0x81,0xe1,
	0x81,0x81,0x81,0x81,0x81,0x87,0x81,0x9f
};
const unsigned char pink3_48[] = {
	0x81,0xf9,0x81,0xe1,0x81,0x81,0x81,0x81,
	0x81,0x87,0x81,0x9f,0x81,0xff,0x81,0xff
};

/*
//flagpole data locations
const unsigned char flagpole1[] = { 0x21 };
const unsigned char flagpole2[] = { 0x29 };
const unsigned char flagpole3[] = { 0x2A };
*/

//Level Start! Text
const unsigned char UpperL3[] = {
	0xff,0x00,0xff,0x20,0xff,0x20,0xff,0x20,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x1c
};
const unsigned char LowerE3[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x24,0xff,0x38,0xff,0x20,0xff,0x1c
};
const unsigned char LowerV3[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x44,
	0xff,0x44,0xff,0x28,0xff,0x28,0xff,0x10
};
const unsigned char LowerL3[] = {
	0xff,0x00,0xff,0x00,0xff,0x20,0xff,0x20,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x38
};
const unsigned char UpperS3[] = {
	0xff,0x00,0xff,0x18,0xff,0x24,0xff,0x20,
	0xff,0x18,0xff,0x04,0xff,0x24,0xff,0x18
};
const unsigned char LowerT3[] = {
	0xff,0x00,0xff,0x00,0xff,0x20,0xff,0x20,
	0xff,0x78,0xff,0x20,0xff,0x20,0xff,0x1c
};
const unsigned char LowerA3[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x04,0xff,0x1c,0xff,0x24,0xff,0x1a
};
const unsigned char LowerR3[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x20
};
const unsigned char Exclam3[] = {
	0xff,0x00,0xff,0x10,0xff,0x10,0xff,0x10,
	0xff,0x10,0xff,0x10,0xff,0x00,0xff,0x10
};
const unsigned char BlankSky3[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00,
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00
};

const unsigned char Letter1_3[]  = { 0x54 }; //54-5E
const unsigned char Letter2_3[]  = { 0x55 };
const unsigned char Letter3_3[]  = { 0x56 };
const unsigned char Letter4_3[]  = { 0x57 };
const unsigned char Letter5_3[]  = { 0x58 };
const unsigned char Letter6_3[]  = { 0x59 };
const unsigned char Letter7_3[]  = { 0x5A };
const unsigned char Letter8_3[]  = { 0x5B };
const unsigned char Letter9_3[]  = { 0x5C };
const unsigned char Letter10_3[] = { 0x5D };
const unsigned char Letter11_3[] = { 0x5E };

//timer counter
UINT16 timerlevel3;
UINT8 timerclock3;

void UpdateHud3() {
	//health system DISPLAY
	//health first number:
	switch (nutmeglives - (nutmeglives % 10)) {
		case 0:  UPDATE_HUD_TILE (3, 0, 6);  break;
		case 10: UPDATE_HUD_TILE (3, 0, 7);  break;
		case 20: UPDATE_HUD_TILE (3, 0, 8);  break;
		case 30: UPDATE_HUD_TILE (3, 0, 9);  break;
		case 40: UPDATE_HUD_TILE (3, 0, 10); break;
		case 50: UPDATE_HUD_TILE (3, 0, 11); break;
		case 60: UPDATE_HUD_TILE (3, 0, 12); break;
		case 70: UPDATE_HUD_TILE (3, 0, 13); break;
		case 80: UPDATE_HUD_TILE (3, 0, 14); break;
		case 90: UPDATE_HUD_TILE (3, 0, 15); break;
	}
	//health second number:
	switch (nutmeglives % 10) {
		case 0: UPDATE_HUD_TILE (4, 0, 6);  break;
		case 1: UPDATE_HUD_TILE (4, 0, 7);  break;
		case 2: UPDATE_HUD_TILE (4, 0, 8);  break;
		case 3: UPDATE_HUD_TILE (4, 0, 9);  break;
		case 4: UPDATE_HUD_TILE (4, 0, 10); break;
		case 5: UPDATE_HUD_TILE (4, 0, 11); break;
		case 6: UPDATE_HUD_TILE (4, 0, 12); break;
		case 7: UPDATE_HUD_TILE (4, 0, 13); break;
		case 8: UPDATE_HUD_TILE (4, 0, 14); break;
		case 9: UPDATE_HUD_TILE (4, 0, 15); break;
	}

	//acorns:
	//acorns first number:
	switch (acorncounter - (acorncounter % 10)) {
		case 0:  UPDATE_HUD_TILE (17, 0, 6);  break;
		case 10: UPDATE_HUD_TILE (17, 0, 7);  break;
		case 20: UPDATE_HUD_TILE (17, 0, 8);  break;
		case 30: UPDATE_HUD_TILE (17, 0, 9);  break;
		case 40: UPDATE_HUD_TILE (17, 0, 10); break;
		case 50: UPDATE_HUD_TILE (17, 0, 11); break;
		case 60: UPDATE_HUD_TILE (17, 0, 12); break;
		case 70: UPDATE_HUD_TILE (17, 0, 13); break;
		case 80: UPDATE_HUD_TILE (17, 0, 14); break;
		case 90: UPDATE_HUD_TILE (17, 0, 15); break;
	}
	//acorns second number:
	switch (acorncounter % 10) {
		case 0: UPDATE_HUD_TILE (18, 0, 6);  break;
		case 1: UPDATE_HUD_TILE (18, 0, 7);  break;
		case 2: UPDATE_HUD_TILE (18, 0, 8);  break;
		case 3: UPDATE_HUD_TILE (18, 0, 9);  break;
		case 4: UPDATE_HUD_TILE (18, 0, 10); break;
		case 5: UPDATE_HUD_TILE (18, 0, 11); break;
		case 6: UPDATE_HUD_TILE (18, 0, 12); break;
		case 7: UPDATE_HUD_TILE (18, 0, 13); break;
		case 8: UPDATE_HUD_TILE (18, 0, 14); break;
		case 9: UPDATE_HUD_TILE (18, 0, 15); break;
	}

	if (timerclock3 <= 25 && cutscenemode == disabled) timerclock3 ++; //25 seems good

	if (timerclock3 == 25) {
		timerclock3 = 0;
		timerlevel3--;
	}

	//timer:
	//timer 100s digit:
	if (timerlevel3 == 300) UPDATE_HUD_TILE (10, 0, 9);
	if (timerlevel3 < 300 && timerlevel3 >= 200) UPDATE_HUD_TILE (10, 0, 8);
	if (timerlevel3 < 200 && timerlevel3 >= 100) UPDATE_HUD_TILE (10, 0, 7);
	if (timerlevel3 < 100) UPDATE_HUD_TILE (10, 0, 6);
	//timer 10s digit:
	if (timerlevel3 < 300 && timerlevel3 >= 200) {
		switch (timerlevel3 - 200 - (timerlevel3 % 10)) {
			case 0:  UPDATE_HUD_TILE (11, 0, 6);  break;
			case 10: UPDATE_HUD_TILE (11, 0, 7);  break;
			case 20: UPDATE_HUD_TILE (11, 0, 8);  break;
			case 30: UPDATE_HUD_TILE (11, 0, 9);  break;
			case 40: UPDATE_HUD_TILE (11, 0, 10); break;
			case 50: UPDATE_HUD_TILE (11, 0, 11); break;
			case 60: UPDATE_HUD_TILE (11, 0, 12); break;
			case 70: UPDATE_HUD_TILE (11, 0, 13); break;
			case 80: UPDATE_HUD_TILE (11, 0, 14); break;
			case 90: UPDATE_HUD_TILE (11, 0, 15); break;
		}
	}
	else if (timerlevel3 < 200 && timerlevel3 >= 100) {
		switch (timerlevel3 - 100 - (timerlevel3 % 10)) {
			case 0:  UPDATE_HUD_TILE (11, 0, 6);  break;
			case 10: UPDATE_HUD_TILE (11, 0, 7);  break;
			case 20: UPDATE_HUD_TILE (11, 0, 8);  break;
			case 30: UPDATE_HUD_TILE (11, 0, 9);  break;
			case 40: UPDATE_HUD_TILE (11, 0, 10); break;
			case 50: UPDATE_HUD_TILE (11, 0, 11); break;
			case 60: UPDATE_HUD_TILE (11, 0, 12); break;
			case 70: UPDATE_HUD_TILE (11, 0, 13); break;
			case 80: UPDATE_HUD_TILE (11, 0, 14); break;
			case 90: UPDATE_HUD_TILE (11, 0, 15); break;
		}
	}
	switch (timerlevel3 - (timerlevel3 % 10)) {
		case 0:  UPDATE_HUD_TILE (11, 0, 6);  break;
		case 10: UPDATE_HUD_TILE (11, 0, 7);  break;
		case 20: UPDATE_HUD_TILE (11, 0, 8);  break;
		case 30: UPDATE_HUD_TILE (11, 0, 9);  break;
		case 40: UPDATE_HUD_TILE (11, 0, 10); break;
		case 50: UPDATE_HUD_TILE (11, 0, 11); break;
		case 60: UPDATE_HUD_TILE (11, 0, 12); break;
		case 70: UPDATE_HUD_TILE (11, 0, 13); break;
		case 80: UPDATE_HUD_TILE (11, 0, 14); break;
		case 90: UPDATE_HUD_TILE (11, 0, 15); break;
	}
	//timer 1s digit:
	switch (timerlevel3 % 10) {
		case 0: UPDATE_HUD_TILE (12, 0, 6);  break;
		case 1: UPDATE_HUD_TILE (12, 0, 7);  break;
		case 2: UPDATE_HUD_TILE (12, 0, 8);  break;
		case 3: UPDATE_HUD_TILE (12, 0, 9);  break;
		case 4: UPDATE_HUD_TILE (12, 0, 10); break;
		case 5: UPDATE_HUD_TILE (12, 0, 11); break;
		case 6: UPDATE_HUD_TILE (12, 0, 12); break;
		case 7: UPDATE_HUD_TILE (12, 0, 13); break;
		case 8: UPDATE_HUD_TILE (12, 0, 14); break;
		case 9: UPDATE_HUD_TILE (12, 0, 15); break;
	}
}

void Start_StateLevel3() {
	level3counter = 0;
	timerlevel3 = 300;
	timerclock3 = 0;
	levelorientation = vertical;
	SPRITES_8x16;

	nut_region = 0;
	pitdeathactive = false;

	deathmusicplayed = false;

	PlayMusic(quickstart, 1);

	scroll_target = spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 4, 49); //36

	InitScrollTiles(0, &level1tiles);
	InitScroll(BANK(level3map), &level3map, collision_tiles_level3, collision_tiles_down_level3);
	INIT_HUD(hud);

	cutscenemode = enabled;
	isAcornMoving = true; //yes, it is moving
	flagpole_activated3 = 0;
	endlevel_counter3 = 0;

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateLevel3() {
	UpdateHud3();

	if (timerlevel3 <= 0) nutmeg_death = true;

	if (nutmeg_death == true) {
		if (deathmusicplayed == false) {
			__critical { PlayMusic(quickdeath, 1); }
			deathmusicplayed = true;
		}

		if (nutmegdeathtimer >= 125) {
			if (GameOver == true) {
				SetState(StateGameOver);
			}
			else if (GameOver == false) {
				SetState(StateOverworld1); // change to correct world
			}
		}

		nutmegdeathtimer++;
	}
	
	if (cutscenemode == enabled) {
		//Level Start!
		//Make Nutmeg Walk In
		if (level3counter == 0) {
			cutscenewalkright = true;
		}
		else if (level3counter >= 36) {
			cutscenewalkright = false;
			//but leave cutscene mode enabled still until Level Start! goes away
		}
		if (level3counter >= 10 && level3counter < 40) {
			set_bkg_data (0x54, 1, UpperL3);
			set_bkg_data (0x55, 1, LowerE3);
			set_bkg_data (0x56, 1, LowerV3);
			set_bkg_data (0x57, 1, LowerE3);
			set_bkg_data (0x58, 1, LowerL3);
			set_bkg_data (0x59, 1, UpperS3);
			set_bkg_data (0x5A, 1, LowerT3);
			set_bkg_data (0x5B, 1, LowerA3);
			set_bkg_data (0x5C, 1, LowerR3);
			set_bkg_data (0x5D, 1, LowerT3);
			set_bkg_data (0x5E, 1, Exclam3);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_3); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_3);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_3);
			set_bkg_tiles (10, 5, 1, 1, Letter4_3);
			set_bkg_tiles (11, 5, 1, 1, Letter5_3);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_3);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_3);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_3);
			set_bkg_tiles (10, 6, 1, 1, Letter9_3);
			set_bkg_tiles (11, 6, 1, 1, Letter10_3);
			set_bkg_tiles (12, 6, 1, 1, Letter11_3);
		}
		else if (level3counter >= 40 && level3counter < 70) {
			set_bkg_data (0x54, 1, BlankSky3);
			set_bkg_data (0x55, 1, BlankSky3);
			set_bkg_data (0x56, 1, BlankSky3);
			set_bkg_data (0x57, 1, BlankSky3);
			set_bkg_data (0x58, 1, BlankSky3);
			set_bkg_data (0x59, 1, BlankSky3);
			set_bkg_data (0x5A, 1, BlankSky3);
			set_bkg_data (0x5B, 1, BlankSky3);
			set_bkg_data (0x5C, 1, BlankSky3);
			set_bkg_data (0x5D, 1, BlankSky3);
			set_bkg_data (0x5E, 1, BlankSky3);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_3); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_3);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_3);
			set_bkg_tiles (10, 5, 1, 1, Letter4_3);
			set_bkg_tiles (11, 5, 1, 1, Letter5_3);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_3);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_3);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_3);
			set_bkg_tiles (10, 6, 1, 1, Letter9_3);
			set_bkg_tiles (11, 6, 1, 1, Letter10_3);
			set_bkg_tiles (12, 6, 1, 1, Letter11_3);
		}
		else if (level3counter >= 70 && level3counter < 100) {
			set_bkg_data (0x54, 1, UpperL3);
			set_bkg_data (0x55, 1, LowerE3);
			set_bkg_data (0x56, 1, LowerV3);
			set_bkg_data (0x57, 1, LowerE3);
			set_bkg_data (0x58, 1, LowerL3);
			set_bkg_data (0x59, 1, UpperS3);
			set_bkg_data (0x5A, 1, LowerT3);
			set_bkg_data (0x5B, 1, LowerA3);
			set_bkg_data (0x5C, 1, LowerR3);
			set_bkg_data (0x5D, 1, LowerT3);
			set_bkg_data (0x5E, 1, Exclam3);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_3); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_3);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_3);
			set_bkg_tiles (10, 5, 1, 1, Letter4_3);
			set_bkg_tiles (11, 5, 1, 1, Letter5_3);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_3);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_3);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_3);
			set_bkg_tiles (10, 6, 1, 1, Letter9_3);
			set_bkg_tiles (11, 6, 1, 1, Letter10_3);
			set_bkg_tiles (12, 6, 1, 1, Letter11_3);
		}
		else if (level3counter >= 100 && level3counter < 101) {
			set_bkg_data (0x54, 1, BlankSky3);
			set_bkg_data (0x55, 1, BlankSky3);
			set_bkg_data (0x56, 1, BlankSky3);
			set_bkg_data (0x57, 1, BlankSky3);
			set_bkg_data (0x58, 1, BlankSky3);
			set_bkg_data (0x59, 1, BlankSky3);
			set_bkg_data (0x5A, 1, BlankSky3);
			set_bkg_data (0x5B, 1, BlankSky3);
			set_bkg_data (0x5C, 1, BlankSky3);
			set_bkg_data (0x5D, 1, BlankSky3);
			set_bkg_data (0x5E, 1, BlankSky3);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_3); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_3);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_3);
			set_bkg_tiles (10, 5, 1, 1, Letter4_3);
			set_bkg_tiles (11, 5, 1, 1, Letter5_3);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_3);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_3);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_3);
			set_bkg_tiles (10, 6, 1, 1, Letter9_3);
			set_bkg_tiles (11, 6, 1, 1, Letter10_3);
			set_bkg_tiles (12, 6, 1, 1, Letter11_3);

			cutscenemode = disabled;

			if (flagpole_activated3 == 0) {
				PlayMusic(mushrooms,  1);
			}
		}

		if (level3counter < 105) level3counter++;
	}

	//animate water
	if (anim_water_counter3 >= 0 && anim_water_counter3 < 10) {
		set_bkg_data (0x1A, 1, level3_water1);
		set_bkg_data (0x1B, 1, level3_water2);
		set_bkg_data (0x1C, 1, level3_water3);
	}
	else if (anim_water_counter3 >= 10 && anim_water_counter3 < 20) {
		set_bkg_data (0x1A, 1, level3_water2);
		set_bkg_data (0x1B, 1, level3_water3);
		set_bkg_data (0x1C, 1, level3_water1);
	}
	else if (anim_water_counter3 >= 20 && anim_water_counter3 < 30) {
		set_bkg_data (0x1A, 1, level3_water3);
		set_bkg_data (0x1B, 1, level3_water1);
		set_bkg_data (0x1C, 1, level3_water2);
	}
	anim_water_counter3++;
	if (anim_water_counter3 >= 30) anim_water_counter3 = 0;

	//animate grey flagpole
	if (flagpole_activated3 == 0) {
		if (anim_flag_counter3 >= 0 && anim_flag_counter3 < 12) {
			set_bkg_data (0x21, 1, grey3_33);
			set_bkg_data (0x29, 1, grey3_41);
			set_bkg_data (0x2A, 1, grey3_41);
		}
		else if (anim_flag_counter3 >= 12 && anim_flag_counter3 < 24) {
			set_bkg_data (0x21, 1, grey3_34);
			set_bkg_data (0x29, 1, grey3_42);
			set_bkg_data (0x2A, 1, grey3_42);
		}
		else if (anim_flag_counter3 >= 24 && anim_flag_counter3 < 36) {
			set_bkg_data (0x21, 1, grey3_35);
			set_bkg_data (0x29, 1, grey3_43);
			set_bkg_data (0x2A, 1, grey3_43);
		}
		else if (anim_flag_counter3 >= 36 && anim_flag_counter3 < 48) {
			set_bkg_data (0x21, 1, grey3_36);
			set_bkg_data (0x29, 1, grey3_44);
			set_bkg_data (0x2A, 1, grey3_44);
		}
		anim_flag_counter3++;
		if (anim_flag_counter3 >= 48) anim_flag_counter3 = 0;
	}
	//animate pink flagpole
	else if (flagpole_activated3 == 1) {
		cutscenemode = enabled;
		
		//change for this level because it's vertical not horizontal!!!
		if (spr_nutmeg->x > 248) {
			cutscenewalkright = true;
			cutscenewalkleft = false;
		}
		else if (spr_nutmeg->x < 1956) {
			cutscenewalkright = true;
			cutscenewalkleft = false;
		}
		else if (spr_nutmeg->x == 1956) {
			cutscenewalkright = true;
			cutscenewalkleft = false;
		}

		if (endlevel_counter3 == 10) {
			SpriteManagerAdd(SpriteStarLeft, 248, 960);
			SpriteManagerAdd(SpriteStarRight, 264, 960);
		}
		else if (endlevel_counter3 == 30) {
			SpriteManagerAdd(SpriteStarLeft, 248, 944);
			SpriteManagerAdd(SpriteStarRight, 264, 944);
		}
		else if (endlevel_counter3 == 50) {
			SpriteManagerAdd(SpriteStarLeft, 248, 928);
			SpriteManagerAdd(SpriteStarRight, 264, 928);
		}
		else if (endlevel_counter3 >= 100) {
			//endlevel_counter3 = 0;
			//cutscenewalkleft = false;
			//cutscenewalkright = false;
			//cutscenemode = disabled;

			SetState(StateOverworld1);
		}

		if (endlevel_counter3 < 250) endlevel_counter3++;

		//spawn some stars
		/*
		if (flagpole_stars3 < 1) {
			SpriteManagerAdd(SpriteStarLeft, spr_nutmeg->x, spr_nutmeg->y);
			SpriteManagerAdd(SpriteStarRight, spr_nutmeg->x, spr_nutmeg->y);

			//SpriteManagerAdd(SpriteStarLeft, 244, 10);
			//SpriteManagerAdd(SpriteStarRight, 244, 10);
		}
		else if (flagpole_stars3 >= 5 && flagpole_stars3 < 10) {
			SpriteManagerAdd(SpriteStarLeft, 244, 10);
			SpriteManagerAdd(SpriteStarRight, 244, 10);
		}
		else if (flagpole_stars3 >= 10 && flagpole_stars3 < 20) {
			SpriteManagerAdd(SpriteStarLeft, 244, 7);
			SpriteManagerAdd(SpriteStarRight, 244, 7);
		}
		*/

		//change flagpole color palette to pink
		//set_bkg_palette (1, 1, pal_pink3);
		SetPalette(BG_PALETTE, 1, 1, pal_pink3, _current_bank);

		if (anim_flag_counter3 >= 0 && anim_flag_counter3 < 5) {
			set_bkg_data (0x21, 1, pink3_37);
			set_bkg_data (0x29, 1, pink3_45);
			set_bkg_data (0x2A, 1, pink3_45);
		}
		else if (anim_flag_counter3 >= 5 && anim_flag_counter3 < 10) {
			set_bkg_data (0x21, 1, pink3_38);
			set_bkg_data (0x29, 1, pink3_46);
			set_bkg_data (0x2A, 1, pink3_46);
		}
		else if (anim_flag_counter3 >= 10 && anim_flag_counter3 < 15) {
			set_bkg_data (0x21, 1, pink3_39);
			set_bkg_data (0x29, 1, pink3_47);
			set_bkg_data (0x2A, 1, pink3_47);
		}
		else if (anim_flag_counter3 >= 15 && anim_flag_counter3 < 20) {
			set_bkg_data (0x21, 1, pink3_40);
			set_bkg_data (0x29, 1, pink3_48);
			set_bkg_data (0x2A, 1, pink3_48);
		}
		anim_flag_counter3++;
		if (anim_flag_counter3 >= 20) anim_flag_counter3 = 0;

		if (flagpole_stars3 < 20) flagpole_stars3++;
	}

	if (spr_nutmeg->x >= 256 && spr_nutmeg->x < 280 && spr_nutmeg->y > 904 && spr_nutmeg->y < 968 && flagpole_activated3 == 0 && nutmeg_death == false) {
		flagpole_activated3 = 1;
		levelbeat = true;
		endlevel_counter3 = 0;
		cutscenemode = enabled;
		cutscenewalkright = true;
		__critical { PlayMusic(flagpole, 1); }
		//distance = 0;
		//SetState(StateOverworld1);
	}

	/*
	//starshooter
	if (KEY_PRESSED(J_A)) {
		if (starshooter == 0) {
			SpriteManagerAdd(SpriteStarLeft, spr_nutmeg->x, spr_nutmeg->y);
			starshooter = 1;
		}
    }
	if (starshooter > 0) starshooter++;
	if (starshooter >= 5) starshooter = 0;
	*/
	
	/*
	if (KEY_PRESSED(J_START)) {
        SetState(StateOverworld1);
    }
	*/

	/*  REGIONS  */
	// 0 = 0-250
	// 1 = 251-500
	// 2 = 501-750
	// 3 = 751-1000
	// 4 = 1001-1250
	// 5 = 1251-1500
	// 6 = 1501-1750
	// 7 = 1751-2000

	// 0 = 0-32
	// 1 = 32-63
	// 2 = 63-94
	// 3 = 94-125
	// 4 = 125-156
	// 5 = 156-188
	// 6 = 188-219
	// 7 = 219-250

	// * * * * * * * * * * * * * * * * * * * * * * * * //
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	//  Need to update this section to spr_nutmeg->y  //
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	// * * * * * * * * * * * * * * * * * * * * * * * * //

	// 0-63:
	if (spr_nutmeg->y > 0 && spr_nutmeg->y <= 125 && nut_region <= 0) {
		SpriteManagerAdd(EnemyBunny, 16*8, 13*8);
		SpriteManagerAdd(SpriteAcorn, 28*8, 6*8);
		SpriteManagerAdd(SpriteAcorn, 28*8, 10*8);
		SpriteManagerAdd(SpriteAcorn, 28*8, 14*8);
		nut_region = 1;
	}
	// Up to 94:
	else if (spr_nutmeg->y > 125 && spr_nutmeg->y <= 250 && nut_region <= 1) {
		SpriteManagerAdd(EnemyTopSpike, 8*8, 28*8);
		//SpriteManagerAdd(EnemyTopSpike, 20*8, 28*8);
		SpriteManagerAdd(EnemyTopSpike, 18*8, 28*8);
    	nut_region = 2;
	}
	// Up to 125:
	else if (spr_nutmeg->y > 250 && spr_nutmeg->y <= 375 && nut_region <= 2) {
		SpriteManagerAdd(EnemyRockith, 20*8, 33*8);
		SpriteManagerAdd(SpriteRock, 20*8, 32*8);
		SpriteManagerAdd(SpriteRock, 26*8, 32*8);
		SpriteManagerAdd(EnemyTopSpike, 12*8, 38*8);
		SpriteManagerAdd(EnemyBatty, 26*8, 40*8);
		SpriteManagerAdd(SpriteRock, 10*8, 41*8);
	    nut_region = 3;
	}
	// Up to 156:
	else if (spr_nutmeg->y > 375 && spr_nutmeg->y <= 500 && nut_region <= 3) {
		SpriteManagerAdd(EnemyButterfly, 10*8, 57*8);
		SpriteManagerAdd(SpriteAcorn, 6*8, 59*8);
	    nut_region = 4;
	}
	// Up to 188:
	else if (spr_nutmeg->y > 500 && spr_nutmeg->y <= 625 && nut_region <= 4) {
	    SpriteManagerAdd(SpriteAcorn, 28*8, 66*8);
		SpriteManagerAdd(SpriteAcorn, 28*8, 70*8);
		SpriteManagerAdd(SpriteAcorn, 28*8, 74*8);
		SpriteManagerAdd(SpriteAcorn, 28*8, 78*8);
		nut_region = 5;
	}
	// Up to 219:
	else if (spr_nutmeg->y > 625 && spr_nutmeg->y <= 750 && nut_region <= 5) {
		SpriteManagerAdd(SpriteRock, 22*8, 82*8);
		SpriteManagerAdd(EnemyRockith, 20*8, 92*8);
		SpriteManagerAdd(SpriteRock, 26*8, 91*8);
		//SpriteManagerAdd(SpriteRock, 10*8, 91*8);
		SpriteManagerAdd(SpriteAcorn, 4*8, 79*8);
		SpriteManagerAdd(SpriteAcorn, 4*8, 83*8);
		SpriteManagerAdd(SpriteAcorn, 4*8, 87*8);
		//SpriteManagerAdd(SpriteAcorn, 4*8, 91*8);
	    nut_region = 6;
	}
	// Up to 250:
	else if (spr_nutmeg->y > 750 && spr_nutmeg->y <= 875 && nut_region <= 6) {
		SpriteManagerAdd(SpriteAcorn, 29*8, 103*8);
		SpriteManagerAdd(SpriteAcorn, 26*8, 106*8);
		SpriteManagerAdd(SpriteAcorn, 23*8, 109*8);
	    nut_region = 7;
	}
	else if (spr_nutmeg->y > 875 && spr_nutmeg->y <= 1000 && nut_region <= 7) {
		SpriteManagerAdd(EnemyBunny, 16*8, 120*8);
	    nut_region = 8;
	}
}