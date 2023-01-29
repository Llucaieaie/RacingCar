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

	Cube p;
	p.size = { 800, 0, 800 };
	p.axis = true;
	p.SetPos(-80.0f, 0.0f, -200.0f);
	p.color = { 2.0f,2.0f,0 };
;	p.Render();

	for (int i = 0; i < 9; i++)
	{
		wall[i].Render();
	}

	secondsSinceInit = INITIAL_TIME - timer;

	if (frames % 60 == 0)
	{
		if (App->player->boostTimer > 0)
		{
			App->player->boostTimer--;
		}
		timer--;
	}

	ramp1.Render();
	ramp2.Render();
	ramp3.Render();

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
	for (int i = 0; i < 9; i++)
		wall[i].color.Set(1.0f, 0.0f, 0.0f);

	//------------------------------------------------------------------------------------- EXTERIORES ----------------------------------------------------------------------------------------------

	wall[0].size = { 0.0f,50.0f,500.0f };
	wall[0].SetPos(-300.0f, wall[0].size.y / 2, -100.0f);
	App->physics->AddBody(wall[0], 0);

	wall[1].size = { 0.0f,50.0f,500.0f };
	wall[1].SetPos(180.0f, wall[0].size.y / 2, -100.0f);
	App->physics->AddBody(wall[1], 0);

	wall[2].size = { 550.0f,50.0f,0.0f };
	wall[2].SetPos(-50.0f, wall[0].size.y / 2, -340.0f);
	App->physics->AddBody(wall[2], 0);

	wall[3].size = { 550.0f,50.0f,0.0f };
	wall[3].SetPos(-50.0f, wall[0].size.y / 2, 0.0f);
	App->physics->AddBody(wall[3], 0);

	//------------------------------------------------------------------------------------- INTERIORES ----------------------------------------------------------------------------------------------
	vec3 axis = { 0,1,0 };
	wall[4].size = { 200.0f,10.0f,10.0f };
	wall[4].SetPos(25.0f, wall[4].size.y / 2, -240.0f);
	wall[4].SetRotation(10, axis);
	App->physics->AddBody(wall[4], 0);

	wall[5].size = { 150.0f,10.0f,10.0f };
	wall[5].SetPos(110.0f, wall[5].size.y / 2, -180.0f);
	wall[5].SetRotation(0, axis);
	App->physics->AddBody(wall[5], 0);

	wall[6].size = { 200.0f,10.0f,10.0f };
	wall[6].SetPos(15.0f, wall[6].size.y / 2, -120.0f);
	wall[6].SetRotation(-45, axis);
	App->physics->AddBody(wall[6], 0);

	wall[7].size = { 10.0f,10.0f,80.0f };
	wall[7].SetPos(-120.0f, wall[7].size.y / 2, -170.0f);
	wall[7].SetRotation(-25, axis);
	App->physics->AddBody(wall[7], 0);

	wall[8].size = { 220.0f,10.0f,60.0f };
	wall[8].SetPos(-140.0f, wall[8].size.y / 2, -240.0f);
	wall[8].SetRotation(-20, axis);
	App->physics->AddBody(wall[8], 0);
	
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------- CIRCUITO ----------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	road.size = { 10.0f, 0.8f, 10.0f };
	float posx, posy, posz;
	posx = -70.0f;
	posy = road.size.y/2;
	posz = -60.0f;
	float scale = 3.0f;
	roadSensor = App->physics->AddBody(road, 0);
	roadSensor->SetAsSensor(true);
	roadSensor->SetId(3);

	// Cube colors
	road.color = { 1.0f,1.0f,0.0f };
	
	checkpoint.SetRotation(45, axis);
	checkpoint.SetPos(-113, 0.5, -120);
	checkpoint.size.x = 5;
	checkpoint.size.y = 10;
	checkpoint.size.z = 20;
	checkpoint.axis = false;
	checkpoint.wire = false;
	checkpoint.color.Set(225, 225, 0);

	checkpointSensor = App->physics->AddBody(checkpoint, 0);
	checkpointSensor->SetAsSensor(true);
	checkpointSensor->SetId(55);
	checkpoint.color = { 1.0f,1.0f,0.0f };

	//-------------------------------------------------------------------------------------- GRASS -----------------------------------------------------------------------------------------------
	//grass.size = { 2000.0f, 0.01f, 2000.0f };
	grass.SetPos(0, 0.7, -180);
	grass.size.x = 600;
	grass.size.y = 0.01;
	grass.size.z = 350;
	grass.axis = false;
	grass.wire = false;

	grassSensor = App->physics->AddBody(grass, 0);
	grassSensor->SetAsSensor(true);
	grassSensor->SetId(3);


	//Plataforma que se mueve
	Cube* cube;
	
	timer2 = new Timer;

	//cube = new Cube();
	//cube->SetPos(posx * scale, 10, posz * scale);
	//cube->size = { 10,1.5,80 };
	//cube->color.Set(0.5f, 0.5f, 1.0f);
	//cubes.add(cube);
	//physBodyCubes.add(App->physics->AddBody(*cube, 0));
	//physBodyCubes.getLast()->data->body->setFriction(0.00f);



	cubeMove = new Cube();
	cubeMove->SetPos(posx * scale, 10, posz* scale);
	cubeMove->size = { 10,2,10 };
	cubeMove->color.Set(0.5f, 1.0f, 0.5f);
	cubeMovBody = App->physics->AddBody(*cubeMove, 0);

	//cube = new Cube();
	//cube->SetPos(posx* scale, 10, posz* scale);
	//cube->size = { 139.9,2,10 };
	//cube->color.Set(0.5f, 0.5f, 1.0f);
	//cubes.add(cube);
	//physBodyCubes.add(App->physics->AddBody(*cube, 0));
	//physBodyCubes.getLast()->data->body->setFriction(0.00f);

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
	//cuidado que aqui venen els fuyms matematics
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
	
	//BOOST
	boost[0].SetPos(posx * scale, posy, posz * scale);
	boost[0].size.x = 1;
	boost[0].size.y = 15;
	boost[0].size.z = 40;
	boost[0].axis = false;
	boost[0].wire = false;
	boost[0].color.Set(225, 225, 0);
	boostSensor = App->physics->AddBody(boost[0], 0);
	boostSensor->SetAsSensor(true);
	boostSensor->SetId(2);

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

	//BOOST
	boost[0].SetPos(posx* scale, posy, posz* scale);
	boost[0].size.x = 1;
	boost[0].size.y = 15;
	boost[0].size.z = 40;
	boost[0].axis = false;
	boost[0].wire = false;
	boost[0].color.Set(225, 225, 0);
	boostSensor = App->physics->AddBody(boost[0], 0);
	boostSensor->SetAsSensor(true);
	boostSensor->SetId(2);

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

	//BOOST
	boost[0].SetPos(posx* scale, posy, posz* scale);
	boost[0].size.x = 1;
	boost[0].size.y = 15;
	boost[0].size.z = 40;
	boost[0].axis = false;
	boost[0].wire = false;
	boost[0].color.Set(225, 225, 0);
	boostSensor = App->physics->AddBody(boost[0], 0);
	boostSensor->SetAsSensor(true);
	boostSensor->SetId(2);

	//------------------------------------------------------------------------------------ ÚLTIMA CURVA -----------------------------------------------------------------------------------------------

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

	//---------------------------------------------------------------------------------------RAMPAS--------------------------------------------------------------------------------------------
	
	ramp1.color.Set(1.0f, 0.0f, 0.0f);
	ramp1.size = { 20.0f,10.0f,10.0f };
	ramp1.SetPos(-100.0f, 0.0f, -145.0f);
	ramp1.SetRotation(30, { 0,-0.5,-1 });
	App->physics->AddBody(ramp1, 0);

	ramp2.color.Set(1.0f, 0.0f, 0.0f);
	ramp2.size = { 10.0f,10.0f,20.0f };
	ramp2.SetPos(155.0f, 0.0f, -205.0f);
	ramp2.SetRotation(30, { -1,-0.35f,0 });
	App->physics->AddBody(ramp2, 0);

	ramp3.color.Set(1.0f, 0.0f, 0.0f);
	ramp3.size = { 20.0f,30.0f,100.0f };
	ramp3.SetPos(-300.0f, -5.0f, -260.0f);
	ramp3.SetRotation(45, { 0,0,1 });
	App->physics->AddBody(ramp3, 0);
}

void ModuleSceneIntro::CubeMoveRender()
{

	cubeMove->Render();
	cubeMove->color.Set(cX, cY, cZ);

	posMoveY = cubeMove->GetPos().y;
	if ((posMoveY <= 90.25 + offsetOfFloor) && moveToUp)
	{
		posMoveY += 0.10;
		cubeMove->SetPos(cubeMove->GetPos().x, posMoveY, cubeMove->GetPos().z);
		cubeMovBody->SetPos(cubeMove->GetPos().x, posMoveY, cubeMove->GetPos().z);

	}
	else if ((posMoveY >= 15 + offsetOfFloor) && !moveToUp)
	{
		posMoveY -= 0.16;
		cubeMove->SetPos(cubeMove->GetPos().x, posMoveY, cubeMove->GetPos().z);
		cubeMovBody->SetPos(cubeMove->GetPos().x, posMoveY, cubeMove->GetPos().z);
	}
	else
	{
		// Utilizo un timer para que espere 3 segundos antes de volver a moverse
		if (!timerStarted)
		{
			timerStarted = true;
			timer2->Start();
		}
		if (timer2->Read() > 3000)
		{
			timerStarted = false;
			moveToUp = !moveToUp;
		}

	}
}