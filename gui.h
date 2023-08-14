#pragma once
#include <d3d9.h>
#include <string>
#include <functional>


namespace gui
{
	// Remember to clean up the code it's a mess, request type gets defined here but it's also passed to a function
	// So we are using 2 different variables for the same thing and it looks awfull
	inline bool newWindow = false;
	constexpr int WIDTH = 700;
	constexpr int HEIGHT = 500;
	inline std::string result = "";
	inline bool exit = true;
	inline HWND window = nullptr;
	inline WNDCLASSEXA windowClass = { };
	inline std::string requestType = "GET";
	void sendRequest(std::string requestType);
	inline std::string url = "";

	inline POINTS position = { };

	inline PDIRECT3D9 d3d = nullptr;
	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline D3DPRESENT_PARAMETERS presentParameters = { };

	void CreateHWindow(
		const char* windowName,
		const char* className) noexcept;
	void DestroyHWindow() noexcept;

	void RenderNewWindow() noexcept;
	bool CreateDevice() noexcept;
	void ResetDevice() noexcept;
	void DestroyDevice() noexcept;

	void CreateImGui() noexcept;
	void DestroyImGui() noexcept;

	void BeginRender() noexcept;
	void EndRender() noexcept;
	void Render() noexcept;
}
