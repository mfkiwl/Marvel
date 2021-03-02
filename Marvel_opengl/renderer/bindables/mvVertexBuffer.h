#pragma once
#include <memory>
#include "mvBindable.h"
#include "mvVertexLayout.h"

namespace Marvel
{
	class mvVertexBuffer : public mvBindable
	{

	public:

		mvVertexBuffer(mvGraphics& graphics, const mvDynamicVertexBuffer& vbuf);

		void bind(mvGraphics& graphics) override;
		void unbind(mvGraphics& graphics) override;

	private:

		unsigned int m_buffer;

	};
}