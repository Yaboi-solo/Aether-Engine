#include <Aether.h>

class Sandbox : public Aether::Application
{
public:
	Sandbox()
	{
		
	}
	~Sandbox()
	{

	}

};

Aether::Application* Aether::CreateApplication()
{
	return new Sandbox();
}