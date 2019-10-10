#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	for (int j = 0; j < cNum; j++) {
		delete Circle[j];
	}
	for (int j = 0; j < bNum; j++) {
		delete Box[j];
	}
	for (int j = 0; j < chNum; j++) {
		delete Chain[j];
	}
	

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	
	// TODO 5: Move all creation of bodies on 1,2,3 key press here in the scene
	// On space bar press, create a circle on mouse position
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		Circle[cNum] = App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25);
		if (cNum <MAX_CIRCLES){
			cNum++;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		// TODO 1: When pressing 2, create a box on the mouse position
		Box[bNum] = App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 50, 25);
		if (bNum < MAX_BOXES) {
			bNum++;
		}

		// TODO 2: To have the box behave normally, set fixture's density to 1.0f
	}

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// TODO 3: Create a chain shape using those vertices
		// remember to convert them from pixels to meters!
		Chain[chNum] = App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head);
		if (chNum < MAX_CHAINS) {
			chNum++;
		}
	}
	// TODO 7: Draw all the circles using "circle" texture
	for (int j = 0; j < cNum; j++) {
		Circle[j]->ReturnPosition();
		App->renderer->Blit(circle,Circle[j]->x-Circle[j]->radius, Circle[j]->y - Circle[j]->radius, NULL, NULL,Circle[j]->GetRotation());
	}

	for (int j = 0; j < bNum; j++) {
		Box[j]->ReturnPosition();
		App->renderer->Blit(box, Box[j]->x - Box[j]->w, Box[j]->y - Box[j]->h, NULL, NULL, Box[j]->GetRotation());
	}

	for (int j = 0; j < chNum; j++) {
		Chain[j]->ReturnPosition();
		App->renderer->Blit(rick, Chain[j]->x, Chain[j]->y);
	}
	return UPDATE_CONTINUE;
}
