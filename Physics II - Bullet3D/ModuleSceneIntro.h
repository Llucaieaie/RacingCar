#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2
#define INITIAL_TIME 60

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void LoadMap();

public:
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	PhysBody3D* roadSensor;
	Cube road;
	Cube wall[10];
	vec3 posroad;
	p2List<Cube> map;
	Cube ramp1;
	Cube ramp2;
	Cube ramp3;

	PhysBody3D* boostSensor;
	Cube boost[20];
	int passedBoost;

	PhysBody3D* grassSensor;
	Cube grass;

	PhysBody3D* checkpointSensor;
	Cube checkpoint;

	uint secondsSinceInit;
	uint timer = INITIAL_TIME;
	uint frames = 0;
};
