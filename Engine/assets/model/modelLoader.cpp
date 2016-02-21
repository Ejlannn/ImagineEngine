//Imagine Engine
//Copyright (c) 2016 Szymon 'skprime' Krygier
//
//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "modelLoader.h"

#include <iostream>
#include <fstream>
#include <algorithm>

ModelAsset *ModelLoader::loadOBJModel(FilePath *objFile)
{
	ModelAsset *modelAsset = new ModelAsset();

	std::ifstream file(objFile->getPath());

	std::vector<std::string*> lines;

	std::string tempLine;

	while(std::getline(file, tempLine))
	{
			lines.push_back(new std::string(tempLine));
	}

	for(U32 i = 0; i < lines.size(); i++)
	{
		if((*lines[i])[0] == '#') continue;
		else if((*lines[i])[0] == 'v' && (*lines[i])[1] == ' ')
		{
			F32 tempX, tempY, tempZ;
			sscanf(lines[i]->c_str(), "v %f %f %f", &tempX, &tempY, &tempZ);

			modelAsset->vertices.push_back(new Vector3(tempX, tempY, tempZ));
		}
		else if((*lines[i])[0] == 'v' && (*lines[i])[1] == 'n')
		{
			F32 tempX, tempY, tempZ;
			sscanf(lines[i]->c_str(), "vn %f %f %f", &tempX, &tempY, &tempZ);

			modelAsset->normalVectors.push_back(new Vector3(tempX, tempY, tempZ));
		}
		else if((*lines[i])[0] == 'v' && (*lines[i])[1] == 't')
		{
			F32 tempX, tempY;
			sscanf(lines[i]->c_str(), "vt %f %f", &tempX, &tempY);

			modelAsset->textureVectors.push_back(new Vector2(tempX, tempY));
		}
		else if((*lines[i])[0] == 'f')
		{
			U16 counter = std::count(lines[i]->begin(), lines[i]->end(), '/');

			if(counter == 0)
			{
				U64 v1, v2, v3;
				sscanf(lines[i]->c_str(), "f %ld %ld %ld", &v1, &v2, &v3);

				modelAsset->faces.push_back(new Face(v1, v2, v3));
			}
			else if(counter == 3)
			{
				U64 v1, v2, v3;
				U64 vt1, vt2, vt3;
				sscanf(lines[i]->c_str(), "f %ld/%ld %ld/%ld %ld/%ld", &v1, &vt1, &v2, &vt2, &v3, &vt3);

				modelAsset->faces.push_back(new Face(v1, v2, v3, vt1, vt2, vt3));
			}
			else if(counter == 6)
			{
				if(lines[i]->find("//") != std::string::npos)
				{
					U64 v1, v2, v3;
					U64 vn;
					sscanf(lines[i]->c_str(), "f %ld//%ld %ld//%ld %ld//%ld", &v1, &vn, &v2, &vn, &v3, &vn);

					modelAsset->faces.push_back(new Face(v1, v2, v3, vn));
				}
				else
				{
					U64 v1, v2, v3;
					U64 vn;
					U64 vt1, vt2, vt3;
					sscanf(lines[i]->c_str(), "f %ld/%ld/%ld %ld/%ld/%ld %ld/%ld/%ld", &v1, &vt1, &vn, &v2, &vt2, &vn, &v3, &vt3, &vn);

					modelAsset->faces.push_back(new Face(v1, v2, v3, vt1, vt2, vt3, vn));
				}
			}
		}
	}

	modelAsset->load();

	return modelAsset;
}
