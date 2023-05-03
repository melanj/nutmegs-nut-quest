#include "Banks/SetAutoBank.h"

#include <gbdk/platform.h>

#include "..\res\src\gameovertiles.h"
#include "..\res\src\gameovermap.h"

#include "ZGBMain.h"
#include "Music.h"
#include "Scroll.h"
#include "Sound.h"
#include "Keys.h"
#include "SpriteManager.h"

//#include "../res/src/nutmeg.h"
//#include "../res/src/acorn.h"
//#include "../res/src/puff.h"
#include "Palette.h"

#include "../src/GlobalVars.h"

IMPORT_MAP (gameovermap);

const UINT16 bg_palette_gameover[] = {
	PALETTE_FROM_HEADER(gameovertiles)
};

/*
const UINT16 sprites_palette_gameover[] = {
	PALETTE_INDEX (nutmeg, 0),
	PALETTE_INDEX (acorn, 1),
	PALETTE_INDEX (puff, 3)
};
*/

const UWORD pal_white[] = {
	RGB(31, 31, 31),
	RGB(31, 31, 31),
	RGB(31, 31, 31),
	RGB(31, 31, 31)
};

const UWORD pal_nutmegdark[] = {
	RGB(0, 0, 0),
	RGB(31, 27, 23),
	RGB(31, 17, 6),
	RGB(8, 8, 8)
};

const UINT8 collision_tiles_gameover[] = {10,0};

//extern UINT8* gameover_mod_Data[];
DECLARE_MUSIC(gameover);

//extern struct Sprite * spr_nutmeg1;
//extern struct Sprite * spr_nutmeg2;
//extern struct Sprite * spr_camera;
extern Sprite * spr_nutmeg;
//extern Sprite * spr_nutmeg2;
extern Sprite * spr_camera;

void Start_StateGameOver() {
	SPRITES_8x16;

	PlayMusic(gameover, 1);

	//SetPalette (BG_PALETTE, 0, 8, bg_palette_gameover, bank_StateGameOver);
	//SetPalette (SPRITES_PALETTE, 0, 8, sprites_palette_gameover, bank_StateGameOver);

	//SpriteManagerLoad(2);  //acorn
	//SpriteManagerLoad(5);  //camera
	//SpriteManagerLoad(35); //nutmeg
	//SpriteManagerLoad(12); //puff
	//SpriteManagerLoad(13); //puff

	//scroll_target = spr_camera = SpriteManagerAdd(SpriteCamera, 4, 49);
	spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 16, 49);
	//spr_nutmeg2 = SpriteManagerAdd(SpriteNutmeg2, 20, 49);
	
	SpriteManagerAdd(SpriteAcorn, 136, 72);

	InitScrollTiles(0, &gameovertiles);
	//InitScroll(&gameovermap, collision_tiles_gameover, 0);
	InitScroll(BANK(gameovermap), &gameovermap, collision_tiles_gameover, 0);

	cutscenemode = disabled;
	isAcornMoving = true; //yes, it is moving

	SHOW_SPRITES;
	SHOW_BKG;
	HIDE_WIN;
}

void Update_StateGameOver() {
	//set_sprite_palette (0, 1, pal_nutmegdark);
	SetPalette(SPRITES_PALETTE, 0, 1, pal_nutmegdark, _current_bank);
	//SetPalette(SPRITES_PALETTE, 3, 1, pal_nutmegdark, _current_bank);
	//set_sprite_palette_entry (0, 3, RGB(8, 8, 8)); //nutmeg light outline
	//set_sprite_palette_entry (1, 3, RGB(8, 8, 8)); //acorn light outline

	if (KEY_PRESSED(J_START)) {
		SetState(StateIncube8);
	}
}