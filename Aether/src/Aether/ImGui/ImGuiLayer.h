#pragma once

#include "Aether/Layer.h"
#include <Aether/Events/MouseEvent.h>
#include <Aether/Events/KeyEvent.h>
#include <Aether/Events/ApplicationEvent.h>

namespace Aether {

	class AETHER_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}