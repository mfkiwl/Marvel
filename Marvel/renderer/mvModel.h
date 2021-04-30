#pragma once
#include "mvGraphics.h"
#include <string>
#include <vector>
#include <memory>
#include "mvNode.h"
#include "mvMesh.h"
#include "mvSolidSphere.h"

//-----------------------------------------------------------------------------
// forward declarations
//-----------------------------------------------------------------------------
struct aiNode;

namespace Marvel {

	//-----------------------------------------------------------------------------
	// forward declarations
	//-----------------------------------------------------------------------------
	class mvRenderGraph;
	class mvModelProbe;

	//-----------------------------------------------------------------------------
	// mvModel
	//-----------------------------------------------------------------------------
	class mvModel
	{
	public:
		mvModel(mvGraphics& graphics, const std::string& pathString, float scale = 1.0f);

		void    submit          (mvRenderGraph& graph) const;
		void    linkTechniques  (mvRenderGraph& graph);
		void    draw            (mvGraphics& graphics) const;
		void    setRootTransform(glm::mat4 tf);
		void    accept          (mvModelProbe& probe);
		mvNode* getNode         (const std::string& name);
		mvSolidSphere& getSphere() { return m_mesh; }

	private:

		mvNode* parseNode(int& id, const aiNode& node, float scale);

	private:

		std::shared_ptr<mvNode>              m_root;
		std::vector<std::shared_ptr<mvMesh>> m_meshes;
		mvSolidSphere                        m_mesh;
	};
}