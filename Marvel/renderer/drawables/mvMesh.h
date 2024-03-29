#pragma once
#include <filesystem>
#include <memory>
#include "mvDrawable.h"
#include "mvMaterial.h"

//-----------------------------------------------------------------------------
// forward declarations
//-----------------------------------------------------------------------------
struct aiMesh;
struct aiMaterial;

namespace Marvel {

	//-----------------------------------------------------------------------------
	// forward declarations
	//-----------------------------------------------------------------------------
	class mvGraphics;
	class mvRenderGraph;

	//-----------------------------------------------------------------------------
	// mvMesh
	//-----------------------------------------------------------------------------
	class mvMesh : public mvDrawable
	{

	public:

		mvMesh(mvGraphics& graphics, const std::string& name, const aiMesh& mesh, const aiMaterial& material, const std::filesystem::path& path, float scale = 1.0f);

		// propagates through graph submitting jobs
		// mesh -> technique -> step -> pass
		void submit(mvRenderGraph& graph, glm::mat4 accumulatedTranform) const;
		
		glm::mat4 getTransform() const override;

	private:

		mutable glm::mat4 m_transform = glm::identity<glm::mat4>();

	};

}