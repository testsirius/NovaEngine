﻿/***************************************************************************
 *   Copyright (C) 2009 by Sirius										   *
 *	 Vdov Nikita Sergeevich	(c)											   *
 *	 siriusnick@gmail.com												   *
 *																		   *
 *	 This source file is part of NovaEngine								   *
 *	 (Object-oriented Game Development Engine)							   *
 *																		   *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program;					                           *
 ***************************************************************************/
// Wild Magic Source Code
// David Eberly
// http://www.geometrictools.com
// Copyright (c) 1998-2008
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or (at
// your option) any later version.  The license is available for reading at
// either of the locations:
//     http://www.gnu.org/copyleft/lgpl.html
//     http://www.geometrictools.com/License/WildMagicLicense.pdf
#include "nova_stable_precompiled_headers.h"

#include "nova_quaternion.h"

namespace nova
{


template<> const CQuaternion<nReal>
    CQuaternion<nReal>::IDENTITY(1.0f,0.0f,0.0f,0.0f);
template<> const CQuaternion<nReal>
    CQuaternion<nReal>::ZERO(0.0f,0.0f,0.0f,0.0f);
template<> int CQuaternion<nReal>::ms_iNext[3] = { 1, 2, 0 };
template<> nReal CQuaternion<nReal>::ms_fTolerance = 1e-06f;
template<> nReal CQuaternion<nReal>::ms_fRootTwo = (nReal)sqrt(2.0);
template<> nReal CQuaternion<nReal>::ms_fRootHalf = (nReal)sqrt(0.5);


}