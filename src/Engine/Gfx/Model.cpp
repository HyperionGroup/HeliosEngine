#include "Gfx.h"

#include "Model.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "Vertex.h"
#include "Buffer.h"
#include "Geometry.h"

#include "Engine/Engine.h"

static core::CStr sModelsFilename = "models/";

namespace gfx
{
    void CModel::Load(const core::CStr& _filename)
    {
        /*
        mFilename = sModelsFilename + _filename;
        // Create an instance of the Importer class
        Assimp::Importer importer;
        // And have it read the given file with some example postprocessing
        // Usually - if speed is not the most important aspect for you - you'll 
        // propably to request more postprocessing than we do in this example.
        const aiScene* scene = importer.ReadFile( mFilename,
                                                  aiProcess_CalcTangentSpace |
                                                  aiProcess_Triangulate |
                                                  aiProcess_JoinIdenticalVertices |
                                                  aiProcess_SortByPType);

        // If the import failed, report it
        if (scene)
        {
            uint32 lNumMeshes = scene->mNumMeshes;

            const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

            mGeometries.resize(lNumMeshes);

            CDevice& lDevice = CDevice::GetInstance();

            for (uint32 iMeshes = 0, lMeshesCount = scene->mNumMeshes; iMeshes < lMeshesCount; ++iMeshes)
            {
                aiMesh* lCurrentMesh = scene->mMeshes[iMeshes];

                uint32 lMaterialIdx = lCurrentMesh->mMaterialIndex;
                if (lMaterialIdx > 0)
                    --lMaterialIdx;

                uint32 lNumVertices = lCurrentMesh->mNumVertices;
                std::vector< CMeshVertex > lGeometryData(lNumVertices);
                for (uint32 i = 0; i < lCurrentMesh->mNumVertices; ++i)
                {
                    const aiVector3D* pPos = &(lCurrentMesh->mVertices[i]);
                    const aiVector3D* pNormal = &(lCurrentMesh->mNormals[i]);
                    const aiVector3D* pTangent = &(lCurrentMesh->mTangents[i]);
                    const aiVector3D* pBintangent = &(lCurrentMesh->mBitangents[i]);
                    const aiVector3D* pTexCoord = lCurrentMesh->HasTextureCoords(0) ? &(lCurrentMesh->mTextureCoords[0][i]) : &Zero3D;
                    
                    lGeometryData[i].position = Float3(pPos->x, pPos->y, pPos->z);
                    lGeometryData[i].normal   = Float3(pNormal->x, pNormal->y, pNormal->z);
                    lGeometryData[i].tangent  = Float4(pTangent->x, pTangent->y, pTangent->z, 1);
                    lGeometryData[i].binormal = Float4(pBintangent->x, pBintangent->y, pBintangent->z, 1);
                    lGeometryData[i].uv       = Float2(pTexCoord->x, pTexCoord->y);
                }

                uint32 lNumFaces = lCurrentMesh->mNumFaces;
                std::vector< uint32 > lIndices;
                for (unsigned int i = 0; i < lCurrentMesh->mNumFaces; i++)
                {
                    const aiFace& Face = lCurrentMesh->mFaces[i];
                    assert(Face.mNumIndices == 3);
                    lIndices.push_back(Face.mIndices[0]);
                    lIndices.push_back(Face.mIndices[1]);
                    lIndices.push_back(Face.mIndices[2]);
                }

                CVertexBuffer< CMeshVertex >* lVB = new CVertexBuffer< CMeshVertex >();
                CIndexBuffer *lIB = new CIndexBuffer();
                lVB->Initialize(lDevice.Device(), lGeometryData.data(), lNumVertices );
                lIB->Initialize(lDevice.Device(), lIndices.data(), static_cast<uint32>(lIndices.size() ) );
                mGeometries[iMeshes] = new CTemplatedIndexedGeometry< CMeshVertex >(lVB, lIB, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
            }
        }
        else
        {
            LOG_ERROR_APPLICATION("Error importing model %s, %s", mFilename.c_str(), importer.GetErrorString());
        }
        */
    }
}
