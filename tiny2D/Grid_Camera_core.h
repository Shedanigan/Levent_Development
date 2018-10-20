#pragma once
#include "Vec2D_core.h"
#include "Grid_Camera_data.h"
#include "Grid_core.h"


namespace Grid_Camera
{
	void init(Grid_Camera *c, int screen_width,int screen_height)
	{
		*c = {};
		c->init.screen_width = screen_width;
		c->init.screen_height = screen_height;
	}

	//if this camera was placed on a grid, which cells of the grid would be under its grid_coord?
	void get_Grid_Region_Covered(Grid::Region *a, const Grid_Camera *c)
	{
		Grid::get_Region_Under_Shape(a, &c->grid_coord);
	}

	void grid_to_Screen(Shape::Rect *screen_coord,const Shape::Rect *grid_coord, const Grid_Camera *c)
	{
		screen_coord->x = c->init.screen_width*(grid_coord->x - c->grid_coord.x) / c->grid_coord.w;
		screen_coord->y = c->init.screen_height*(grid_coord->y - c->grid_coord.y) / c->grid_coord.h;
		screen_coord->w = c->init.screen_width*grid_coord->w / c->grid_coord.w;
		screen_coord->h = c->init.screen_height*grid_coord->h / c->grid_coord.h;
	}

	void screen_to_Grid(Vec2D::Vec2D *grid_point, Vec2D::Vec2D *screen_point, const Grid_Camera *c)
	{
		
		grid_point->x = c->grid_coord.x + c->grid_coord.w*(screen_point->x / c->init.screen_width);
		grid_point->y = c->grid_coord.y + c->grid_coord.h*(screen_point->y / c->init.screen_height);
	}

	//must perform this if camera width or height changes
	//given a grid region that the camera grid_coord covers, recalculate tile data
	void calibrate(Calibration *c, const Grid_Camera *cam,const Grid::Region *a)
	{
		c->tile_w = ceil(cam->init.screen_width / cam->grid_coord.w);
		c->tile_h = ceil(cam->init.screen_height / cam->grid_coord.h);
		c->tile_x = ((float)a->x0 - cam->grid_coord.x) * c->tile_w;
		c->tile_y = ((float)a->y0 - cam->grid_coord.y) * c->tile_h;
	}
}