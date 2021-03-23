#include "mvLambertianPass.h"
#include "mvGraphics.h"
#include "mvCommonBindables.h"

namespace Marvel {

	mvLambertianPass::mvLambertianPass(mvGraphics& graphics)
		:
		mvPass("Lambertian")
	{
		addBindable(std::make_shared<mvStencil>(graphics, mvStencil::Mode::Off));
	}

	void mvLambertianPass::execute(mvGraphics& graphics) const
	{
		for (auto& bind : m_bindables)
			bind->bind(graphics);

		for (const auto& j : m_jobs)
			j.execute(graphics);
	}

}