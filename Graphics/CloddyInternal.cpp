//
//#include "Graphics/TikiHeightmap.h"
//
//#include "Graphics/Shader.h"
//
//#include "Graphics/TerrainIndexBuffer.h"
//#include "Graphics/TerrainVertexBuffer.h"
//#include "Graphics/TerrainTriangulationCallback.h"
//
//namespace TikiEngine
//{
//	namespace Graphics
//	{
//		#pragma region TerrainIndexBuffer
//		TerrainIndexBuffer::TerrainIndexBuffer(int32 size)
//			: size(size), indexCount(0)
//		{
//			data = TIKI_TIKI_NEW UInt32[size];
//			indexBuffer = TIKI_TIKI_NEW DynamicBuffer<UInt32, TIKI_INDEX_BUFFER>(DllMain::Engine);
//		}
//
//		TerrainIndexBuffer::~TerrainIndexBuffer()
//		{
//			delete[](data);
//			SafeRelease(&indexBuffer);
//		}
//
//		UInt32 TerrainIndexBuffer::GetCount()
//		{
//			return indexCount;
//		}
//
//		void TerrainIndexBuffer::Apply()
//		{
//			indexBuffer->Apply();
//		}
//
//		int32 TerrainIndexBuffer::GetCapacity()
//		{
//			return size;
//		}
//
//		void TerrainIndexBuffer::SetIndices(int32 bufferIndex, Array<int32> indices, int32 indicesOffset, int32 indicesCount)
//		{
//			memcpy(
//				data + bufferIndex,
//				((int32*)indices) + indicesOffset,
//				sizeof(int32) * indicesCount
//			);
//
//			if (bufferIndex + indicesCount > indexCount)
//				indexCount = bufferIndex + indicesCount;
//
//			UInt32* bdata = indexBuffer->Map(size);
//			memcpy(
//				bdata,
//				data,
//				sizeof(int32) * size
//			);	
//			indexBuffer->Unmap();
//		}
//
//		void TerrainIndexBuffer::DisposeManaged()
//		{
//		}
//
//		void TerrainIndexBuffer::DisposeUnmanaged()
//		{
//		}
//		#pragma endregion
//
//		#pragma region TerrainVertexBuffer
//		#pragma region Class
//		TerrainVertexBuffer::TerrainVertexBuffer(int32 size)
//			: size(size), buffer(0)
//		{
//			dataVertices = TIKI_TIKI_NEW CloddyVertex[size];
//			vertexBuffer = TIKI_TIKI_NEW DynamicBuffer<CloddyVertex, TIKI_VERTEX_BUFFER>(DllMain::Engine);
//		}
//
//		TerrainVertexBuffer::~TerrainVertexBuffer()
//		{
//			delete[](dataVertices);
//			SafeRelease(&vertexBuffer);
//		}
//		#pragma endregion
//
//		#pragma region Member
//		void TerrainVertexBuffer::Apply()
//		{
//			vertexBuffer->Apply();
//		}
//		#pragma endregion
//
//		#pragma region Member - Get
//		int32 TerrainVertexBuffer::GetCapacity()
//		{
//			return size;
//		}
//
//		int32 TerrainVertexBuffer::GetVertexSize()
//		{
//			return sizeof(Vector3);
//		}
//		#pragma endregion
//
//		#pragma region Member - VertexBuffer
//		void TerrainVertexBuffer::LockBuffer(int32 min, int32 max, int32 count, void* userData, BufferLock* bufferLock)
//		{	
//			buffer = ByteBuffer::Allocate(
//				sizeof(CloddyVertex) * count
//			);
//
//			lockMin = min;
//			lockMax = max;
//			bufferLock->Locked(buffer);
//		}
//
//		void TerrainVertexBuffer::Unlock()
//		{
//			memcpy(
//				dataVertices + lockMin,
//				buffer->GetRawPointer(),
//				(PInt)buffer->GetCapacity()
//			);
//
//			CloddyVertex* bdata = vertexBuffer->Map(this->size);
//			memcpy(bdata, dataVertices, this->size * sizeof(CloddyVertex));
//			vertexBuffer->Unmap();
//
//			buffer = 0;
//		}
//		#pragma endregion
//
//		#pragma region Protected Member
//		void TerrainVertexBuffer::DisposeManaged()
//		{
//		}
//
//		void TerrainVertexBuffer::DisposeUnmanaged()
//		{
//			// hier code
//		}
//		#pragma endregion
//		#pragma endregion
//
//		#pragma region TerrainTriangulationCallback
//		TerrainTriangulationCallback::TerrainTriangulationCallback(TerrainIndexBuffer* indexBuffer, TerrainVertexBuffer* vertexBuffer)
//			: indexBufferCloddy(indexBuffer), vertexBuffer(vertexBuffer)
//		{
//			this->indexBuffer = TIKI_TIKI_NEW DynamicBuffer<Int32, TIKI_INDEX_BUFFER>(DllMain::Engine);
//		}
//
//		TerrainTriangulationCallback::~TerrainTriangulationCallback()
//		{
//
//		}
//
//		void TerrainTriangulationCallback::BeginTriangulation(void* userData)
//		{
//		}
//
//		void TerrainTriangulationCallback::EndTriangulation()
//		{
//		}
//
//		void TerrainTriangulationCallback::TriangleStripChunk(codex_Array<codex_int32> indices, codex_int32 count, codex_int32 min, codex_int32 max)
//		{
//			DllMain::Context->IASetInputLayout(layout);
//			vertexBuffer->Apply();
//
//			Int32* data = indexBuffer->Map(count);
//			memcpy(data, indices, sizeof(int32) * count);
//			indexBuffer->Unmap();
//			indexBuffer->Apply();
//
//			DllMain::Context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//			DllMain::Context->DrawIndexed(count, 0, 0);
//		}
//
//		void TerrainTriangulationCallback::SetMaterial(Material* mat)
//		{
//			material = mat;
//
//			TDX_Input_Element_desc layoutDescription[] =
//			{
//				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, TIKI_VERTEXLAYOUT_APPEND_ALIGNED_ELEMENT, TIKI_VERTEXLAYOUT_INPUT_PER_VERTEX_DATA, 0 },
//				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, TIKI_VERTEXLAYOUT_APPEND_ALIGNED_ELEMENT, TIKI_VERTEXLAYOUT_INPUT_PER_VERTEX_DATA, 0 },
//				{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, TIKI_VERTEXLAYOUT_APPEND_ALIGNED_ELEMENT, TIKI_VERTEXLAYOUT_INPUT_PER_VERTEX_DATA, 0 },
//				{ "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM,  0, TIKI_VERTEXLAYOUT_APPEND_ALIGNED_ELEMENT, TIKI_VERTEXLAYOUT_INPUT_PER_VERTEX_DATA, 0 },
//			};
//
//			Shader* shader = (Shader*)material->GetShader();
//			shader->CreateLayout(layoutDescription, 4, &layout, 0);
//		}
//
//		void TerrainTriangulationCallback::DisposeManaged()
//		{
//		}
//
//		void TerrainTriangulationCallback::DisposeUnmanaged()
//		{
//		}
//		#pragma endregion
//
//		#pragma region TikiHeightmap
//		TikiHeightmap::TikiHeightmap(int size)
//			: size(size), color(0), detail(0), elevation(0)
//		{
//			this->InitializeCube(size);
//		}
//
//		TikiHeightmap::~TikiHeightmap()
//		{
//			if (color != 0) color->Dispose();
//			if (detail != 0) detail->Dispose();
//			if (elevation != 0) elevation->Dispose();
//		}
//
//		void TikiHeightmap::SetColor(IHeightmap* color)
//		{
//			this->color = color->Scale(size);
//		}
//
//		void TikiHeightmap::SetDetail(IHeightmap* detail)
//		{
//			this->detail = detail->Scale(size);
//		}
//
//		void TikiHeightmap::SetElevation(IHeightmap* elevation)
//		{
//			this->elevation = elevation->Scale(size);
//		}
//
//		HeightmapLayer TikiHeightmap::GetLayerMask()
//		{
//			return HeightmapLayer_None;
//		}
//
//		void TikiHeightmap::Get(Int32 x, Int32 y, HeightmapSample* sample)
//		{
//			this->Get(x, y, 0, sample);
//		}
//
//		void TikiHeightmap::Get(Int32 x, Int32 y, Int32 z, HeightmapSample* sample)
//		{
//			//HeightmapSample tmp = HeightmapSample();
//
//			//color->Get(x, y, z, &tmp);
//			//sample->Diffuse = RGB(x, y, z) || 0xFF000000; // 0xFF0000FF;
//
//			elevation->Get(x, y, z, sample);
//			//sample->Elevation = tmp.Elevation;
//
//			//detail->Get(x, y, z, &tmp);
//			//sample->Detail0 = tmp.Detail0;
//			//sample->Detail1 = tmp.Detail1;
//			//sample->Detail2 = tmp.Detail2;
//			//sample->Detail3 = tmp.Detail3;
//		}
//
//		void TikiHeightmap::DisposeUnmanaged()
//		{
//			Disposable::DisposeUnmanaged();
//		}
//
//		void TikiHeightmap::DisposeManaged()
//		{
//			Disposable::DisposeManaged();
//		}
//		#pragma endregion
//	}
//}