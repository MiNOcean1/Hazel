#pragma once
#ifdef  HZ_PLATFORM_WINDOWS
extern Hazel::Application* Hazel::CreateApplication();
int main(int argc,char** argv) {
	Hazel::Log::Init();
	HZ_CORE_WARN("initialized log !");
	HZ_INFO("hello! Var={0}",4);
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif //  HZ_PLATFORM_WINDOWS
