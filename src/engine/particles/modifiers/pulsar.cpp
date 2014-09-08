#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a pulsar.
 */
struct pulsar : public particle_modifier_implementation
{

public:

	static pulsar& instance()
	{
		static pulsar _instance;
		return _instance;
	}
	virtual ~pulsar() { }

	/**
	 * Attracts particles.
	 */
	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		gravity = pm_inst->attributes["gravity"] * sin(ps.particlemillis / 1000.0);
		// conoutf("gravity: %3.3f", gravity);
		mass = pm_inst->attributes["mass"];
		dx = p_inst->pos->o.x - pm_inst->positions[0]->o.x;
		dy = p_inst->pos->o.y - pm_inst->positions[0]->o.y;
		dz = p_inst->pos->o.z - pm_inst->positions[0]->o.z;
		distance = sqrtf(dx * dx + dy * dy + dz * dz);
		if (distance == 0.0f) distance = 0.00000000001f;
		force = -(p_inst->mass) * mass * gravity / (distance * distance);
		p_inst->vel.x += (force * dx) / (distance * p_inst->mass);
		p_inst->vel.y += (force * dy) / (distance * p_inst->mass);
		p_inst->vel.z += (force * dz) / (distance * p_inst->mass);
	}

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime) { }

	inline void modify(int elapsedtime) { }

	void render_edit_overlay(particle_modifier_instance *entity_instance) { }

private:

	float gravity;
	float mass;
	float distance;
	float force;
	float dx, dy, dz;

	pulsar() : particle_modifier_implementation("pulsar") {
		ps.add_modifier_implementation(this);
		gravity = 0.0f;
		mass = 0.0f;
		distance = 0.0f;
		force = 0.0f;
		dx = 0.0f;
		dy = 0.0f;
		dz = 0.0f;
	}
	pulsar( const pulsar& );
	pulsar & operator = (const pulsar &);

};

pulsar& ps_modifier_pulsar = pulsar::instance();
