/***************************************************************************
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
// Success doesn't come to you�you go to it.
#pragma once 

#include "nova_error.h"
#include "nova_gzstreams.h"
#include "nova_fstream.h"

namespace nova
{

class NOVA_EXPORT CFilesPackage : public CBase
{
private:

	nstring mPackageName;
	CDataStream *mFile;
	bool mIsOpened;
	bool mWritePackage;
	bool mSelfOpen;
	nova::nUInt32 mVersion;

#pragma pack(push, 1)
	typedef struct PackageHeader
	{
		nova::nUInt32 m_signature;
		nova::nUInt32 version;
		nova::nUInt32 v_signature;
		char package_name[50];
	} TPackageHeader;

	typedef struct FileHeader
	{
		nova::nUInt32 number;
		size_t size;
		size_t pos;
		char file_name[150];
		char ext[10];
		char resource_group[50];
	} TFileHeader;
#pragma pack(pop)

protected:

	stl<nstring, TFileHeader>::map mPackageMap;
	TPackageHeader mPackageHeader;

	bool InFileList(const nstring & name);

public:

	CFilesPackage();

	~CFilesPackage();

	void OpenPackage(const nstring & pkg, bool write);

	void OpenPackage(CDataStream *pkgstream, bool write);

	void ClosePackage(void);

	nova::stl<nstring>::vector GetFileList(void) const;

	nova::nstring GetFileExt(const nstring & name) const ;

	CMemoryBuffer GetFile(const nstring & name) const ;

	bool IsOpened(void) const;

	void PutFile(const CMemoryBuffer &buf , const nstring & name, const nstring & ext, const nstring &grs); 

};


}