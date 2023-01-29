#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");


	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 1.1, 4);
	car.chassis_offset.Set(0, 1.1, 0);
	car.mass = 400.0f;
	car.suspensionStiffness = 5.8f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 1.0f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 10.8f;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.0f;
	float wheel_radius = 0.5f;
	float wheel_width = 0.4f;
	float suspensionRestLength = 1.0f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(-246.0f, 0, -200.0f);
	vehicle->collision_listeners.add(this);
	vehicle->SetId(1);

	boostTimer = 0;
	killerCountDown = 60;
	contadorIniciado = false;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		if (grass)
		{
			acceleration = GRASS_ACCELERATION;
			car.suspensionStiffness = 10.0f;
			car.frictionSlip = 8.3f;
		}
		else
		{
			acceleration = MAX_ACCELERATION;
			car.suspensionStiffness = 5.8f;
			car.frictionSlip = 10.8f;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
		LOG("turn = %f", turn);
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		if (vehicle->GetKmh() > 0.5f) {
			brake = BRAKE_POWER;
		}
		else if (vehicle->GetKmh() <= 0.1f) {
			acceleration = -MAX_ACCELERATION/3;
		}
	}

	if (boostTimer > 0)
	{
		acceleration = MAX_ACCELERATION * 20;
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	//Variables para camara detrás del player
	forwardVector = vehicle->vehicle->getForwardVector().normalize();
	camPos = vehicle->body->getCenterOfMassPosition();

	//Ejecuta la función para poner la camara detrás del player
	if (AerialCam == true)
		CameraAerial(dt);
	else if (SideCam == true)
		CameraSide(dt);
	else
		CameraPlayer(dt);

	vehicle->Render();

	if (check)
	{
		LOG("AAA--------------A--AAA-AAA--A-A-A--A-A--AAAA------AAA------AAAA");
		//App->scene_intro->checkpointSensor->body->~btRigidBody();
		App->scene_intro->checkpoint.color = { 1.0f,1.0f,1.0f,0.5f };
		brake = 1000000000000000.0f;
		respawn = 1;
	}

	/*if (grass)
	{
		if (respawn == 1)
		{
			vehicle->SetPos(-125, 1.8, -110);
			vehicle->angle = 90;
			vehicle->rotated = false;
			grass = false;
		}
		if (respawn == 0)
		{
			vehicle->SetPos(-246.0f, 0, -200.0f);
			vehicle->angle = 0;
			vehicle->rotated = false;
			grass = false;
		}


	}*/

	secondsSinceInit = INITIAL_TIME - timer;

	if (killerCountDown > -1 && contadorIniciado) 
	{
		killerCountDown -= dt;
		if (killerCountDown == 0 && victoria == false)
		{
			char title[80];
			sprintf_s(title, "HAS PERDIDO");
			App->window->SetTitle(title);
		}
	}

	

	char title[80];
	sprintf_s(title, "%.1f Km/h, Timer: %.2f", vehicle->GetKmh(), killerCountDown);
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}

void ModulePlayer::CameraPlayer(float dt) 
{
	if (!App->GetDebugMode()) //Si esto es true la camara no sigue al jugador y se queda libre, F1 para hacerlo
	{
		vec3 myCamera;
		vec3 myCameraLook;
		float distanceCamara2CM = -12;

		//Se posiciona la camara detrás del jugador
		myCamera.x = camPos.getX() + forwardVector.getX() * distanceCamara2CM;
		myCamera.y = camPos.getY() + forwardVector.getY() + 6;
		myCamera.z = camPos.getZ() + forwardVector.getZ() * distanceCamara2CM;

		lastCam = myCamera;

		if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)LOG("Position Player \n x: %f \t z: %f ", myCamera.x, myCamera.z);

		//Se orienta la cámara para que mire al jugador
		myCameraLook.x = vehicle->body->getCenterOfMassPosition().getX();
		myCameraLook.y = vehicle->body->getCenterOfMassPosition().getY() + 4;
		myCameraLook.z = vehicle->body->getCenterOfMassPosition().getZ();

		//Utilizo la variable myCamera para setear la posición de la cámara	
		App->camera->Position = myCamera;
		//Utilizo la variable myCameraLook para setear la orientación de la cámara
		App->camera->LookAt(myCameraLook);

		//Utilizo la variable myCamera para setear la posición de la cámara	
		App->camera->Position = myCamera;
		//Utilizo la variable myCameraLook para setear la orientación de la cámara
		App->camera->LookAt(myCameraLook);
	}
}

//Camera aérea, se activa con f2
void ModulePlayer::CameraAerial(float dt)
{
		vec3 myCamera;
		vec3 myCameraLook;
		float distanceCamara2CM = -12;

		myCamera.x = vehicle->body->getCenterOfMassPosition().getX();
		myCamera.y = 300;
		myCamera.z = vehicle->body->getCenterOfMassPosition().getZ();

		lastCam = myCamera;

		myCameraLook.x = vehicle->body->getCenterOfMassPosition().getX();
		myCameraLook.y = vehicle->body->getCenterOfMassPosition().getY();
		myCameraLook.z = vehicle->body->getCenterOfMassPosition().getZ() + 10;

		App->camera->Position = myCamera;
		App->camera->LookAt(myCameraLook);
}

//camara de lado, se activa con f3
void ModulePlayer::CameraSide(float dt)
{
	vec3 myCamera;
	vec3 myCameraLook;
	float distanceCamara2CM = -12;

	//Se posiciona la camara detrás del jugador
	myCamera.x = camPos.getX() + forwardVector.getX()+12;
	myCamera.y = camPos.getY() + forwardVector.getY() + 1;
	myCamera.z = camPos.getZ() + forwardVector.getZ();

	lastCam = myCamera;

	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)LOG("Position Player \n x: %f \t z: %f ", myCamera.x, myCamera.z);

	//Se orienta la cámara para que mire al jugador
	myCameraLook.x = vehicle->body->getCenterOfMassPosition().getX();
	myCameraLook.y = vehicle->body->getCenterOfMassPosition().getY() + 1;
	myCameraLook.z = vehicle->body->getCenterOfMassPosition().getZ();

	//Utilizo la variable myCamera para setear la posición de la cámara	
	App->camera->Position = myCamera;
	//Utilizo la variable myCameraLook para setear la orientación de la cámara
	App->camera->LookAt(myCameraLook);

	//Utilizo la variable myCamera para setear la posición de la cámara	
	App->camera->Position = myCamera;
	//Utilizo la variable myCameraLook para setear la orientación de la cámara
	App->camera->LookAt(myCameraLook);
}

void ModulePlayer::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body2->id == 2) boostTimer = 2;
	if (body2->id == 3) grass = true;
	if (body2->id == 4) vehicle->SetPos(-246.0f, 0, -200.0f);
	if (body2->id == 5) contadorIniciado = true, victoria = false;
	if (body2->id == 55)
	{
		check = true;
	}
}
