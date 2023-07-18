#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <shellapi.h>

// avoid conflicts with <algorithm> min and max
#if defined(min)
#undef min
#endif

#if defined(max)
#undef max
#endif

#if defined(CreateWindow)
#undef CreateWindow
#endif

// comPtr
#include <wrl.h>
using namespace Microsoft::WRL;

//dx
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <d3dx12.h>

//STL
#include <algorithm>
#include <cassert>
#include <chrono>

#include "Helpers.h"

// the number of swap chain back buffers.
const uint8_t g_NumFrames = 3;
// use WARP adapter (fallback to software rasterization)
bool g_UseWarp = false;

uint32_t g_ClientWidth = 1280;
uint32_t g_ClientHeight = 720;

// set to true once the DX12 objects have been initialized.
bool g_IsInitialized = false;

// window
HWND g_hWnd;
RECT g_WindowRect;

// dx objects
ComPtr<ID3D12Device2> g_Device;
ComPtr<ID3D12CommandQueue> g_CommandQueue;
ComPtr<IDXGISwapChain4> g_SwapChain;
ComPtr<ID3D12Resource> g_BackBuffers[g_NumFrames];
ComPtr<ID3D12GraphicsCommandList> g_CommandList;
ComPtr<ID3D12CommandAllocator> g_CommandAllocators[g_NumFrames];
ComPtr<ID3D12DescriptorHeap> g_RTVDescriptorHeap; // swapchains backbuffer descriptors
UINT g_RTVDescriptorSize; // size of a single descriptor
UINT g_CurrentBackBufferIndex; // current backbuffer index

//sync objects
ComPtr<ID3D12Fence> g_Fence;
uint64_t g_FenceValue = 0;
uint64_t g_FrameFenceValues[g_NumFrames] = {};
HANDLE g_FenceEvent;

// swapchains present mode
// vsync will block the present methode until the next vertical refresh.
// gsync will give control to the graphics application to determine when a vertical refresh can happen
bool g_VSync = true;
bool g_TearingSupported = false;
bool g_Fullscreen = false;

// window callback function.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int main()
{
	return 0;
}