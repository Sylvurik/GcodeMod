/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * gcodeirrlicht.cc
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

#include "CSceneGcodeNode.h"
#include "gcodeobjet.h"
#include <irrlicht/irrlicht.h>
#include <vector>
#include <eigen3/Eigen/Dense>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

CSceneGcodeNode::CSceneGcodeNode(ISceneNode* parent, ISceneManager* scene, s32 id)
: ISceneNode(parent, scene, id)
{
	m_material.Lighting = true;
	m_material.BackfaceCulling = true;
	m_material.FrontfaceCulling = false;
	m_material.EmissiveColor = SColor(0,0,0,0);
	p = 0;
}

void CSceneGcodeNode::OnRegisterSceneNode ()
{
	if (IsVisible)
	{
		SceneManager->registerNodeForRendering(this);
	}
	ISceneNode::OnRegisterSceneNode ();
}

void CSceneGcodeNode::render()
{
	vector3df vectorA;
	vector3df vectorB;

	// render the objet
	IVideoDriver* driver = SceneManager->getVideoDriver();

	driver->setTransform(irr::video::ETS_WORLD, AbsoluteTransformation);
	driver->draw3DBox(m_box, SColor(255,0,0,0));
	driver->setMaterial(m_material);

	for (int i(0) ; i < p ; i += 1)
	{
		vectorA = posA.at(i);
		vectorB = posB.at(i);
		driver->draw3DLine(vectorA, vectorB, SColor(0,75,75,75));
	}
}

void CSceneGcodeNode::getGcode(Gcodeobjet* model)
{
	int i(0);
	std::vector<Eigen::VectorXd>* table = NULL;

	if ( model->haxis() == 3)
	{
		m_box = aabbox3d<f32>(model->min(0), model->min(2), model->min(1),
		                      model->max(0), model->max(2), model->max(1));

		table = model->getTable ();

		while (i+1 < model->hline ())
		{
			if (table->at(i) != table->at(i+1))
			{
				posA.push_back(vector3df(table->at(i).x(), table->at(i).z(), table->at(i).y()));
				posB.push_back(vector3df(table->at(i+1).x(), table->at(i+1).z(), table->at(i+1).y()));
				p++;
			}
			i++;
		}
	}
}

const aabbox3d<f32>& CSceneGcodeNode::getBoundingBox() const
{
	return m_box;
}

u32 CSceneGcodeNode::getMaterialCount () const
{
	return 1;
}

SMaterial& CSceneGcodeNode::getMaterial(u32 i)
{
	return m_material;
}
