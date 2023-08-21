#pragma once
#include <d3d9.h>
#include <string>
#include <functional>


namespace gui
{
	enum class eRequestType {
		kGETRequest = 0,
		kPOSTRequest = 1,
		kDELETERequest = 2,
		kPUTRequest = 3,
		kUnknownRequest = 4
	};

	inline bool newWindow = false;
	constexpr int WIDTH = 1200;
	constexpr int HEIGHT = 1000;
	inline std::string result = "";
	inline bool exit = true;
	inline HWND window = nullptr;
	inline WNDCLASSEXA windowClass = { };
	inline int selectedMethod = 0;
	void sendRequest(eRequestType requestType, const std::string& url);
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
