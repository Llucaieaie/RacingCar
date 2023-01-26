#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

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
	p.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::LoadMap()
{
	//wall[0].SetPos(0, 0, 10);
	//wall[0].size.x = 1.0f;
	//wall[0].size.y = 1.0f;
	//wall[0].size.z = 1.0f;
	//wall[0].axis = false;
	//wall[0].color.Set(255, 255, 0);
	//App->physics->AddBody(wall[0], 0);
	//Cubes.add(wall[0]);
}