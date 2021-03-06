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
#include "nova_stable_precompiled_headers.h"

#include "nova_scene_manager.h"
#include "nova_octree_scene_node.h"

namespace nova
{

void CSceneNode::ValidateNode(void)
{
	for(nova::nUInt32 i = 0; i < GetListenersCount(); i++)
	{
		CSceneNodeListener * lis = 
			dynamic_cast<CSceneNodeListener *>(GetListener(i));
		lis->ValidateNodeListener(this);
	}

	ValidateNodeImpl();
	isValidated = true;
}

bool CSceneNode::IsValidated(void)
{
	return isValidated;
}

void CSceneNode::InValidateNode(void)
{
	for(nova::nUInt32 i = 0; i < GetListenersCount(); i++)
	{
		CSceneNodeListener * lis = 
			dynamic_cast<CSceneNodeListener *>(GetListener(i));
		lis->InValidateNodeListener(this);
	}

	InValidateNodeImpl();
	isValidated = false;
}

void CSceneNode::ReleaseNode(void)
{
	for(nova::nUInt32 i = 0; i < GetListenersCount(); i++)
	{
		CSceneNodeListener * lis = 
			dynamic_cast<CSceneNodeListener *>(GetListener(i));
		lis->ReleaseNodeListener(this);
	}

	InValidateNode();
}

CBoundingBox &CSceneNode::GetBoundingBox(void)
{
	return mBoundingBox;
}

void CSceneNode::SetBoundingBox(const CBoundingBox &box)
{
	mBoundingBox = box;
}

void CSceneNode::PrepareNode(void)
{
	for(nova::nUInt32 i = 0; i < GetListenersCount(); i++)
	{
		CSceneNodeListener * lis = 
			dynamic_cast<CSceneNodeListener *>(GetListener(i));
		lis->PrepareNodeListener(this);
	}

	PrepareNodeImpl();
}

CSceneManager::CSceneManager(const nstring & scene_name, const nstring & group)
{
	//ClearObjects(); // Error R6025: Pure virual function call ..fuck =)
	mRegisterGroup = group;
	mSceneName = scene_name;
	isEnabled = true;
}

CSceneManager::~CSceneManager()
{
	//ClearObjects(); // Error R6025: Pure virual function call ..fuck =)
} 

nInt32 CSceneManager::GetRenderedBatches(void)
{
	return mRenderedBatches;
}

nInt32 CSceneManager::GetRenderedFaces(void)
{
	return mRenderedFaces;
}

void CSceneManager::RenderScene(CCamera *camera, CViewPort *view)
{
	if(!camera || !view)
		return;

	for(nova::nUInt32 i = 0; i < GetListenersCount(); i++)
	{
		CSceneManagerListener * lis = 
			dynamic_cast<CSceneManagerListener *>(GetListener(i));
		lis->SceneRenderBeginListener(this);
	}

	mRenderedFaces = 0;
	mRenderedBatches = 0;
	mCurCamera = camera;
	mCurView = view;

	RenderSceneImpl();
	RenderСompoundObjects();

	for(nova::nUInt32 i = 0; i < GetListenersCount(); i++)
	{
		CSceneManagerListener * lis = 
			dynamic_cast<CSceneManagerListener *>(GetListener(i));
		lis->SceneRenderEndListener(this);
	}
}

nstring CSceneManager::GetSceneName(void)
{
	return mSceneName;
}

CTreeNode<CSceneNode*> *CSceneManager::ConstactSpecifiedNode()
{
	return NULL;
}

CTreeNode<CSceneNode*> *CSceneManager::GetRootElement(void)
{
	return mSceneTree.GetRootElement();
}

void CSceneManager::SetRootElement(CSceneNode *elem)
{
	mSceneTree.CreateRoot(elem);
}

CTree<CSceneNode*> *CSceneManager::GetSceneTreePtr(void)
{
	return &mSceneTree;
}

nstring CSceneManager::GetSceneSlavesGroup(void)
{
	return mRegisterGroup;
}

void CSceneManager::PrepareScene(void)
{
	for(nova::nUInt32 i = 0; i < GetListenersCount(); i++)
	{
		CSceneManagerListener * lis = 
			dynamic_cast<CSceneManagerListener *>(GetListener(i));
		lis->PrepareSceneListener(this);
	}

	PrepareSceneImpl();
}

nInt32 CSceneManager::PrepareRenderQueue(void)
{
	return PrepareRenderQueueImpl();
}

void CSceneManager::PrepareSceneFrame(void)
{
	for(nova::nUInt32 i = 0; i < GetListenersCount(); i++)
	{
		CSceneManagerListener * lis = 
			dynamic_cast<CSceneManagerListener *>(GetListener(i));
		lis->PrepareSceneFrameListener(this);
	}

	PrepareSceneFrameImpl();
}

void CSceneManager::BuildScene(void)
{
	for(nova::nUInt32 i = 0; i < GetListenersCount(); i++)
	{
		CSceneManagerListener * lis = 
			dynamic_cast<CSceneManagerListener *>(GetListener(i));
		lis->BuildSceneListener(this);
	}

	BuildSceneImpl();
}

void CSceneManager::DestroyScene(void)
{
	for(nova::nUInt32 i = 0; i < GetListenersCount(); i++)
	{
		CSceneManagerListener * lis = 
			dynamic_cast<CSceneManagerListener *>(GetListener(i));
		lis->DestroySceneListener(this);
	}

	
	DestroySceneNode(GetRootElement());
	mSceneTree.FreeAll();
}

void CSceneManager::DestroySceneNode(CTreeNode<CSceneNode*> *node)
{
	if(node)
	{
		for(nInt32 i = 0; i < node->GetChildrenLen(); i++)
			DestroySceneNode(node->GetNode(i));

		if(node->GetData())
			delete node->GetData();
	}
}

void CSceneManager::ClearObjects(void)
{
	ClearObjectsImpl();
}

CRenderableObject *CSceneManager::AddRenderableResourceToScene(const nstring &resource_name)
{
	return NULL;
}

}
