#pragma once
#include "Body_data.h"
#include "Vec_core.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

namespace Body
{
	void init(Factory *a, int array_size)
	{
		a->array_size = array_size;
		a->n_bodies = 0;

		a->vel = (Vec2D::Vec2D*)malloc(sizeof(Vec2D::Vec2D)*a->array_size);
		a->force = (Vec2D::Vec2D*)malloc(sizeof(Vec2D::Vec2D)*a->array_size);
		a->pos = (Vec2D::Vec2D*)malloc(sizeof(Vec2D::Vec2D)*a->array_size);
		a->last_pos = (Vec2D::Vec2D*)malloc(sizeof(Vec2D::Vec2D)*a->array_size);
		a->mass = (float*)malloc(sizeof(float)*a->array_size);
	}

	void resize(Factory *a)
	{
		a->array_size += a->array_size >> 1;
		a->vel = (Vec2D::Vec2D*)realloc(a->vel, sizeof(Vec2D::Vec2D)*a->array_size);
		a->force = (Vec2D::Vec2D*)realloc(a->force, sizeof(Vec2D::Vec2D)*a->array_size);
		a->pos = (Vec2D::Vec2D*)realloc(a->pos, sizeof(Vec2D::Vec2D)*a->array_size);
		a->last_pos = (Vec2D::Vec2D*)realloc(a->pos, sizeof(Vec2D::Vec2D)*a->array_size);
		a->mass = (float*)realloc(a->mass, sizeof(float)*a->array_size);
	}

	void clear_Forces(Factory *a)
	{
		memset(a->force, 0, sizeof(Vec2D::Vec2D)*a->n_bodies);
	}

	int make_Instance(Factory *a)
	{
		if (a->n_bodies >= a->array_size)
		{
			resize(a);
		}
		++a->n_bodies;
		return a->n_bodies - 1;
	}

	void modify(int index, Factory *a, Vec2D::Vec2D *pos, float mass)
	{
		a->vel[index] = {};
		a->force[index] = {};
		a->last_pos[index] = *pos;
		a->pos[index] = *pos;
		a->mass[index] = mass;
	}

	void add_Force(int index, Factory *a, const Vec2D::Vec2D *f)
	{
		Vec2D::add(&a->force[index], f);
	}

	void update_Vel(int index, Factory *a, float dt)
	{
		//implicit euler
		Vec2D::Vec2D accel = { dt*a->force[index].x / a->mass[index],dt*a->force[index].y / a->mass[index] };
		Vec2D::add(&a->vel[index], &accel);
	}

	void update_Pos(int index, Factory *a, float dt)
	{
		Vec2D::Vec2D t = a->vel[index];
		t.x *= dt;
		t.y *= dt;
		a->last_pos[index] = a->pos[index];
		Vec2D::add(&a->pos[index], &t);
	}

	void apply_Friction(int index, const Vec2D::Vec2D *friction, Factory *a)
	{
		a->vel[index].x *= 1.0 - friction->x;
		a->vel[index].y *= 1.0 - friction->y;
	}

}