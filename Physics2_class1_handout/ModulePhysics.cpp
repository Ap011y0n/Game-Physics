#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"

// TODO 1: Include Box 2 header and library
#include "Box2D/Box2D/Box2D.h"
#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#endif
#ifndef _DEBUG
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif


ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled) 
{

debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
	
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");
	b2Vec2 gravity(0.0f, PIXELS_TO_METERS(2));
	world = new b2World(gravity);
	// TODO 2: Create a private variable for the world
	// - You need to send it a default gravity
	// - You need init the world in the constructor
	// - Remember to destroy the world after using it
	
	
	// TODO 4: Create a a big static circle as "ground"

	b2BodyDef bodyDef;	
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(PIXELS_TO_METERS(500), PIXELS_TO_METERS(400));
	b2Body* body = world->CreateBody(&bodyDef);
	b2CircleShape bigStaticCircle;
	bigStaticCircle.m_radius = PIXELS_TO_METERS(270);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &bigStaticCircle;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);

	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position.Set(PIXELS_TO_METERS(0), PIXELS_TO_METERS(SCREEN_HEIGHT));
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(100));
	b2FixtureDef fixtureDef2;
	fixtureDef2.shape = &groundBox;
	fixtureDef2.density = 1.0f;
	fixtureDef2.friction = 0.3f;
	groundBody->CreateFixture(&fixtureDef2);

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	// TODO 3: Update the simulation ("step" the world)
	float32 timeStep = 1.0f / 60.0f;
	
	for (int32 i = 0; i < 60; ++i)
	{
		world->Step(timeStep, 8, 3);
		
	}

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	// TODO 5: On space bar press, create a circle on mouse position
	// - You need to transform the position / radius
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(PIXELS_TO_METERS(App->input->GetMouseX()), PIXELS_TO_METERS(App->input->GetMouseY()));
		b2Body* body = world->CreateBody(&bodyDef);
		b2CircleShape circle;
		circle.m_radius = PIXELS_TO_METERS(rand()%100);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circle;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.9f;
		body->CreateFixture(&fixtureDef);

	}
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;
				case b2Shape::e_polygon:
				{
					b2PolygonShape* shape = (b2PolygonShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					SDL_Rect rect;
						rect.x = METERS_TO_PIXELS(pos.x);
						rect.y = METERS_TO_PIXELS(pos.y);
						rect.w = METERS_TO_PIXELS(1000);
						rect.h = -METERS_TO_PIXELS(10);

					App->renderer->DrawQuad(rect, 255, 255, 255, 255, false);
				}
				break;
				// You will have to add more cases to draw boxes, edges, and polygons ...
			}
		}
	}

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");
	delete world;
	// Delete the whole physics world!

	return true;
}
