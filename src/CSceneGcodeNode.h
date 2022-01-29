/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * gcodeirrlicht.h
 * Copyright (C) 2021 sylvain <sylvain@debian>
 *
 * gcode is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gcode is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _GCODEIRRLICHT_H_
#define _GCODEIRRLICHT_H_

#include <irrlicht/irrlicht.h>
#include <vector>
#include <eigen3/Eigen/Dense>
#include "gcodeobjet.h"

namespace irr
{
namespace scene
{
class CSceneGcodeNode : public irr::scene::ISceneNode
{
	 public :
		 CSceneGcodeNode (irr::scene::ISceneNode* parent, irr::scene::ISceneManager* scene, irr::s32 id=0);

		 virtual void OnRegisterSceneNode();
		 virtual void render();

		 virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
		 virtual irr::u32 getMaterialCount() const;
		 virtual irr::video::SMaterial& getMaterial(irr::u32 i);

		 void getGcode(Gcodeobjet* model);

	 private :
		 irr::core::aabbox3d<irr::f32> m_box;
		 irr::video::SMaterial m_material;
		 std::vector<irr::core::vector3df> posA;
		 std::vector<irr::core::vector3df> posB;
		 int p; // nombre de vecteur
		 
};
}
}

#endif // _GCODEIRRLICHT_H_

