#pragma once
#include "mvBindable.h"
#include "mvGraphics.h"
#include "mvShader.h"
#include "mvVertexLayout.h"
#include <vector>

namespace Marvel {

	class mvInputLayout : public mvBindable
	{

	public:

		mvInputLayout(mvGraphics& graphics, mvVertexLayout vertexLayout);

		void init(mvShader& shader);
		void bind(mvGraphics& graphics) override;
		void unbind(mvGraphics& graphics) override;

	private:

		mvVertexLayout                      m_layout;
		GLuint                              m_vao;

	};

}