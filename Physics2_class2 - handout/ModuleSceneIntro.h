#pragma once
#include "Module.h"
#include "p2List.h"
#include "Globals.h"
#define MAX_CIRCLES 10000
#define MAX_BOXES 10000
#define MAX_CHAINS 10000

class PhysBody;
class circleClass;
class boxClass;
class chainClass;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	circleClass* Circle[MAX_CIRCLES];
	boxClass* Box[MAX_CIRCLES];
	chainClass *Chain[MAX_CHAINS];
	int cNum = 0;
	int bNum = 0;
	int chNum = 0;
	int rick_head[70] = {
	42, 0,
	75, 33,
	88, 5,
	94, 24,
	94, 40,
	112, 36,
	103, 58,
	106, 62,
	116, 66,
	108, 75,
	110, 82,
	105, 92,
	109, 99,
	102, 105,
	99, 115,
	106, 122,
	103, 126,
	98, 126,
	95, 135,
	88, 147,
	71, 149,
	56, 144,
	46, 132,
	35, 136,
	41, 126,
	25, 125,
	33, 115,
	11, 103,
	29, 91,
	1, 77,
	17, 68,
	30, 63,
	13, 35,
	42, 39,
	43, 18
	};
};
