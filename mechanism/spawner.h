#ifndef SPAWNER_H
#define SPAWNER_H

#include <engine/core/varmap.h>
#include <engine/physics/physical.h>
#include <engine/mechanism/marker.h>

template <typename nodeType>
class Spawner : public Marker{
private:


	bool use_total_spawns;
	bool use_period;

	/*counts either total spans or period, either way
	it counts down one tick on the counter every time
	the update is called. When the counter hits 0, a
	drawable is spawned and the counter resets at the
	iteration value.*/
	int counter;
	int interval;

	/*whenever the counter reaches 0, the spawns left
	variable counts down one. It stops spawning after
	the spawns_left has reaced 0. If the number of
	spawns is time based, it is generated based on the
	starting number of ticks and the tick interval
	between spawns.*/
	int spawns_left;
	//mesh m;

	/*the amount that the velocity of the spawner at
	the creation of a spawnee is inherited by the
	spawnee. 0 is spawnee starts out with zero speed,
	1, is spawnee is created with 100% of the velocity
	of the spawner. negitive values shoot the spawnee
	out in the opposite direction of the spawner, etc.*/
	double velocity_multiplier;
	double3 spawn_velocity;

	/*the amount the velocity is randomized.*/
	double3 randomize_velocity;

protected:

	/**\brief an overridable function provied from the
	spawner parent class to allow any inheriting classes
	the chance to interact with what they spawn before their
	spawn is let loose into the world.

	The spawn is sent as a node, so any interaction should be
	through the sendMessage() function of the node() class,
	unless you're feeling like a hunk and want to chance casting
	the new node as something specific.

	Actually, I was lying. I forgot that this class was a
	template class so this function could dynamically decide
	which type of object it was dealing with. With that said,
	it does nothing by default, but can be overwritten by any
	inheriting classes and stuff can be done with it, whatever
	the template class type allows.**/
	virtual void OnSpawn(nodeType *node){
	}

	void OnSetSettings(){
	    cout << ">spawner";
        Marker::OnSetSettings();
	}


public:

/*
	Spawner(VarMap settings){

    if(settings.IsSet("interval")){
        interval = settings.get<int>("interval");
    } else {
        interval = 1;
    }*/
    //interval = setup::getInt(settings,"interval",1000);
    //cout << "spawner :: interval = " << interval << endl;
    //spawns_left = setup::getInt(settings,"total-spawns",(setup::getInt(settings,"duration",-interval)/interval));
    //cout << "spawner :: spawns left = " << spawns_left << endl;
    //velocity_multiplier = setup::getDouble(settings,"inherit-velocity",0);
    //cout << "spawner :: spawner velocity multiplier = " << velocity_multiplier << endl;
    //cout << "spawns left : " << spawns_left << endl;
    //spawn_velocity = setup::getDouble3(settings,"velocity",double3(0,0,0));
    //cout << "spawner :: initial velocity = " << spawn_velocity.x << "," << spawn_velocity.y << "," << spawn_velocity.z << "\n";
    //randomize_velocity = setup::getDouble3(settings,"randomize-velocity",double3(0,0,0));
    //cout << "spawner :: velocity rand() = " << randomize_velocity.x << "," << randomize_velocity.y << "," << randomize_velocity.z << "\n";
    //counter = 0;
    /*setup shape that is drawn by the engine
    //m = glShape::sphere(10,10,10);

    interval = 1;
    spawns_left = 1000;
    velocity_multiplier = 1;
    spawn_velocity = double3(0,1,0);
    randomize_void Spawner::SetSpawnInterval(int newInterval){
    interval = newInterval;
}*/

    ~Spawner(){
    }


    void SetVelocityRandomization(double3 amount){
        randomize_velocity = amount;
    }

    void SetVelocityRandomization(double amount){
        randomize_velocity = double3(amount,amount,amount);
    }

    void SetInitialVelocity(double3 velocity){
        spawn_velocity = velocity;
    }

    void SetSpawnsLeft(int spawnsLeft){
        spawns_left = spawnsLeft;
    }

    int IntervalBeforeNextSpawn(){
        return counter;
    }


	/**\brief update the spawner.

	Depending on how the spawner is set up, it will count down or
	up through its timers and generate things when they should be
	generated.

	When it is finished, it kills itself**/
	void Update(){
	}

	/**\brief allow the interval between spawns to be set at
	runtime.

	This is essential for any classes inheriting the spawner
	class that have generic settings that may be different from
	the default spawner setting, but are common enough that forcing
	the user to put the new setting in the config file is stuff.**/
    void SetSpawnInterval(int newInterval){
        interval = newInterval;
    }

};




#endif // SPAWNER_H
