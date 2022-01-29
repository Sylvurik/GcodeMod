/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * trackball.h
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

#ifndef _TRACKBALL_H_
#define _TRACKBALL_H_

// la classe permet de créer des caméra trackball pour irrlicht
#include <irrlicht/irrlicht.h>

class CSceneNodeAnimatorCameraTrackball : public irr::scene::ISceneNodeAnimator
{

public :

    CSceneNodeAnimatorCameraTrackball(irr::video::IVideoDriver *driver,
                                      irr::gui::ICursorControl *cursorControl,
                                      irr::f32 radius,
                                      irr::f32 moveSpeed,
                                      irr::f32 rotateSpeed);

	virtual void animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs);
	virtual bool OnEvent(const irr::SEvent& event);
	virtual irr::scene::ISceneNodeAnimator* createClone(irr::scene::ISceneNode* node, irr::scene::ISceneManager* newManager = 0);
	 
	virtual irr::f32 getMoveSpeed() const { return m_moveSpeed; }
	virtual irr::f32 getRotateSpeed() const { return m_rotateSpeed; }
	virtual bool isEventReceiverEnabled() const { return true; }


private :

	irr::video::IVideoDriver *m_driver;             // pointer to video driver
	irr::gui::ICursorControl *m_cursorControl;      // allow operations on cursor
	irr::f32 m_radius;                              // distance from target
	irr::f32 m_moveSpeed;                           // movements's speed to the target
	irr::f32 m_rotateSpeed;                         // speed of fake world rotation
	bool m_isPressed;                               // is the left mouse button clicked
	bool m_wheel;                                   // did the wheel moved
	irr::core::position2d<irr::f32> m_cursorMove;   // contain changes on cursor position
	irr::core::position2d<irr::f32> m_cursorPos;    // contain the cursor position
	irr::core::vector3df m_rotation;                // contain changes on camera position
};

#endif // _TRACKBALL_H_

