#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "Color.h"
#include "ModulePhysics3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	LoadMap();

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	//Activar/desactivar DebugMode
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)App->SetDebugMode();

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)App->player->AerialCam = !App->player->AerialCam;

	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)App->player->SideCam = !App->player->SideCam;

	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Scale(2.0f, 2.0f, 2.0f);
	p.SetPos(-80.0f, 0.0f, -200.0f);
	p.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::LoadMap()
{
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------- PAREDES ----------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------- EXTERIORES ----------------------------------------------------------------------------------------------

	wall.size = { 0.0f,50.0f,500.0f };
	wall.SetPos(-300.0f,wall.size.y/2,-100.0f);
	App->physics->AddBody(wall, 0);

	wall.size = { 0.0f,50.0f,500.0f };
	wall.SetPos(180.0f, wall.size.y / 2, -100.0f);
	App->physics->AddBody(wall, 0);

	wall.size = { 550.0f,50.0f,0.0f };
	wall.SetPos(-50.0f, wall.size.y / 2, -340.0f);
	App->physics->AddBody(wall, 0);

	wall.size = { 550.0f,50.0f,0.0f };
	wall.SetPos(-50.0f, wall.size.y / 2, 0.0f);
	App->physics->AddBody(wall, 0);

	//------------------------------------------------------------------------------------- INTERIORES ----------------------------------------------------------------------------------------------

	wall.size = { 200.0f,10.0f,10.0f };
	wall.SetPos(25.0f, wall.size.y / 2, -240.0f);
	App->physics->AddBody(wall, 0);

	wall.size = { 150.0f,10.0f,10.0f };
	wall.SetPos(110.0f, wall.size.y / 2, -180.0f);
	App->physics->AddBody(wall, 0);

	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------- CIRCUITO ----------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	road.size = { 10.0f, 0.05f, 10.0f };
	float posx, posy, posz;
	posx = -70.0f;
	posy = road.size.y/2;
	posz = -60.0f;
	float scale = 3.0f;
	// Cube colors
	//road.color = (255,0,0);
	// 
	//------------------------------------------------------------------------------------- INICIO ----------------------------------------------------------------------------------------------
	for (uint i = 0; i < 12; i++)
	{

		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 1.0f;
		posz -= 0.5f;
	}

	//-------------------------------------------------------------------------------------- PRIMERA CURVA ---------------------------------------------------------------------------------------------
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.9f;
		posz -= 0.6f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.8f;
		posz -= 0.7f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.6f;
		posz -= 0.8f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.3f;
		posz -= 0.9f;
	}	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.0f;
		posz -= 1.0f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.2f;
		posz -= 0.9f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.4f;
		posz -= 0.8f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.6f;
		posz -= 0.6f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.7f;
		posz -= 0.4f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.8f;
		posz -= 0.2f;
	}
	for (uint i = 0; i < 12; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.9f;
		posz += 0.0f;
	}

	//----------------------------------------------------------------------------------- PRIMERA RECTA ------------------------------------------------------------------------------------------------

	for (uint i = 0; i < 12; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.9f;
		posz += 0.1f;
	}
	for (uint i = 0; i < 12; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.9f;
		posz += 0.15f;
	}
	for (uint i = 0; i < 12; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.9f;
		posz += 0.2f;
	}
	for (uint i = 0; i < 12; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.9f;
		posz += 0.3f;
	}
	for (uint i = 0; i < 12; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.9f;
		posz += 0.4f;
	}

	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 1.0f;
		posz += 0.5f;
	}

	//------------------------------------------------------------------------------------ SEGUNDA CURVA -----------------------------------------------------------------------------------------------
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 1.0f;
		posz += 0.4f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 1.0f;
		posz += 0.2f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 1.0f;
		posz += 0.0f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 1.0f;
		posz -= 0.2f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 1.0f;
		posz -= 0.4f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 1.0f;
		posz -= 0.5f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 1.0f;
		posz -= 0.6f;
	}

	//------------------------------------------------------------------------------------ TERCERA CURVA -----------------------------------------------------------------------------------------------
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.9f;
		posz -= 0.4f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.9f;
		posz -= 0.2f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.9f;
		posz += 0.1f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.6f;
		posz += 0.4f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.4f;
		posz += 0.6f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.3f;
		posz += 0.7f;
	}
	for (uint i = 0; i < 4; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.0f;
		posz += 1.0f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.4f;
		posz += 0.9f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.7f;
		posz += 0.7f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.9f;
		posz += 0.4f;
	}
	for (uint i = 0; i < 10; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 1.0f;
		posz += 0.2f;
	}
	for (uint i = 0; i < 10; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 1.0f;
		posz += 0.0f;
	}
	for (uint i = 0; i < 8; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 1.0f;
		posz -= 0.1f;
	}
	for (uint i = 0; i < 8; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 1.0f;
		posz -= 0.2f;
	}

	//------------------------------------------------------------------------------------ TERCERA CURVA -----------------------------------------------------------------------------------------------
	for (uint i = 0; i < 4; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.9f;
		posz += 0.1f;
	}
	for (uint i = 0; i < 4; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.7f;
		posz += 0.4f;
	}
	for (uint i = 0; i < 4; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.5f;
		posz += 0.7f;
	}
	for (uint i = 0; i < 4; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.1f;
		posz += 0.9f;
	}
	for (uint i = 0; i < 4; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.2f;
		posz += 1.0f;
	}
	for (uint i = 0; i < 4; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.5f;
		posz += 1.0f;
	}
	for (uint i = 0; i < 4; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.8f;
		posz += 1.0f;
	}
	for (uint i = 0; i < 4; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 1.0f;
		posz += 1.0f;
	}

	//------------------------------------------------------------------------------------ TERCERA CURVA -----------------------------------------------------------------------------------------------

	for (uint i = 0; i < 12; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 1.0f;
		posz += 0.7f;
	}
	for (uint i = 0; i < 12; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.8f;
		posz += 0.5f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.65f;
		posz += 0.75f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.5f;
		posz += 0.5f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.25f;
		posz += 0.75f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx += 0.0f;
		posz += 1.0f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.25f;
		posz += 0.75f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.5f;
		posz += 0.5f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.75f;
		posz += 0.5f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 1.0f;
		posz += 0.2f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 1.0f;
		posz -= 0.1f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.8f;
		posz -= 0.3f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.7f;
		posz -= 0.5f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.6f;
		posz -= 0.8f;
	}
	for (uint i = 0; i < 24; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.4f;
		posz -= 1.0f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.6f;
		posz -= 0.8f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.8f;
		posz -= 0.5f;
	}

	//------------------------------------------------------------------------------------ �LTIMA CURVA -----------------------------------------------------------------------------------------------

	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 1.0f;
		posz -= 0.2f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 1.0f;
		posz += 0.1f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.9f;
		posz += 0.4f;
	}
	for (uint i = 0; i < 12; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.8f;
		posz += 0.7f;
	}
	for (uint i = 0; i < 4; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.8f;
		posz += 0.4f;
	}
	for (uint i = 0; i < 4; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 1.0f;
		posz += 0.1f;
	}
	for (uint i = 0; i < 4; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.8f;
		posz -= 0.4f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.5f;
		posz -= 0.7f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.2f;
		posz -= 0.9f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.1f;
		posz -= 0.9f;
	}
	for (uint i = 0; i < 6; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 0.4f;
		posz -= 0.5f;
	}
	for (uint i = 0; i < 12; i++)
	{
		road.SetPos(posx * scale, posy, posz * scale);
		App->physics->AddBody(road, 0);
		map.add(road);
		posx -= 1.0f;
		posz -= 0.4f;
	}
}