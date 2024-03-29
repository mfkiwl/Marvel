#include "mvPointCloud.h"
#include <imgui.h>
#include "mvGraphics.h"
#include "mvCommonBindables.h"
#include "Sphere.h"
#include "mvTechnique.h"

namespace Marvel {

	mvPointCloud::mvPointCloud(mvGraphics& graphics, const std::string& name, glm::vec3 color)
	{

		// create vertex layout
		mvVertexLayout vl;
		vl.append(ElementType::Position3D);

		// create vertex buffer
		m_vertexBuffer = std::make_shared<mvVertexBuffer>(graphics, name, std::vector<float>{0.0f, 0.0f, 0.0f}, vl, true);

		// create index buffer
		m_indexBuffer = mvBufferRegistry::Request<mvIndexBuffer>(graphics, name, std::vector<unsigned int>{0u}, true);

		mvStep step("lambertian");

		mvBufferLayout layout(std::make_shared<mvBufferLayoutEntry>(Struct));
		auto& root = layout.getRoot();
		root->add(Float3, std::string("materialColor"));
		root->finalize(0);

		std::unique_ptr<mvDynamicBuffer> bufferRaw = std::make_unique<mvDynamicBuffer>(std::move(layout));

		bufferRaw->getElement("materialColor").setIfExists(color);

		std::shared_ptr<mvPixelConstantBuffer> buf = std::make_shared<mvPixelConstantBuffer>(graphics, *root.get(), 1, bufferRaw.get());

		step.addBuffer(buf);

		step.addBuffer(mvBufferRegistry::GetBuffer("transCBuf"));

		mvPipelineInfo pipeline;

		pipeline.vertexShader = graphics.getShaderRoot() + "Solid_VS.hlsl";
		pipeline.pixelShader = graphics.getShaderRoot() + "Solid_PS.hlsl";
		pipeline.geometryShader = "";
		pipeline.topology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
		pipeline.vertexLayout = vl;
		pipeline.rasterizerStateCull = false;
		pipeline.rasterizerStateHwPCF = false;
		pipeline.blendStateFlags = mvBlendStateFlags::OFF;

		step.registerPipeline(graphics, pipeline);

		mvTechnique technique;
		technique.addStep(step);
		addTechnique(technique);

	}

	std::vector<float>& mvPointCloud::getVertices()
	{
		return m_vertexBuffer->getData();
	}

	std::vector<unsigned int>& mvPointCloud::getIndices()
	{
		return m_indexBuffer->getData();
	}

	glm::mat4 mvPointCloud::getTransform() const
	{
		return glm::translate(glm::vec3{ m_x, m_y, m_z }) *
			glm::rotate(m_zangle, glm::vec3{ 0.0f, 0.0f, 1.0f }) *
			glm::rotate(m_yangle, glm::vec3{ 0.0f, 1.0f, 0.0f }) *
			glm::rotate(m_xangle, glm::vec3{ 1.0f, 0.0f, 0.0f });
	}

	void mvPointCloud::show_imgui_windows(const char* name)
	{
		if (ImGui::Begin(name))
		{
			ImGui::SliderFloat("X-Pos", &m_x, -50.0f, 50.0f);
			ImGui::SliderFloat("Y-Pos", &m_y, -50.0f, 50.0f);
			ImGui::SliderFloat("Z-Pos", &m_z, -50.0f, 50.0f);
			ImGui::SliderFloat("X-Angle", &m_xangle, -50.0f, 50.0f);
			ImGui::SliderFloat("Y-Angle", &m_yangle, -50.0f, 50.0f);
			ImGui::SliderFloat("Z-Angle", &m_zangle, -50.0f, 50.0f);
		}
		ImGui::End();
	}

	void mvPointCloud::setPosition(float x, float y, float z)
	{
		m_x = x;
		m_y = y;
		m_z = z;
	}

	void mvPointCloud::setRotation(float x, float y, float z)
	{
		m_xangle = x;
		m_yangle = y;
		m_zangle = z;
	}

}