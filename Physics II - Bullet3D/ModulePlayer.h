#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "PhysBody3D.h"
#include "PhysVehicle3D.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 100.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	//VehicleInfo car;

	void CameraPlayer(float dt);

	void CameraAerial(float dt);
	bool AerialCam = false;

	void CameraSide(float dt);
	bool SideCam = false;


public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;

	btVector3 forwardVector;
	btVector3 camPos;
	vec3 lastCam;

};