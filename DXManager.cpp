#include "DXManager.h"
#include "gdef.h"


DXManager::DXManager(void)
{
	m_videoCardMemory = 0;
	m_swapChain = NULL;
	m_device = NULL;
	m_deviceContext = NULL;
	m_renderTargetView = NULL;
	m_depthStencilBuffer = NULL;
	m_depthStencilState = NULL;
	m_depthStencilView = NULL;
	m_rasterState = NULL;
	m_alphaDisableBlendingState = NULL;
	m_alphaEnableBlendingState = NULL;
	m_depthDisabledStencilState = NULL;
	vsync_enabled = false;

}

DXManager::~DXManager(void)
{
	if (m_swapChain)
	{
		m_swapChain->SetFullscreenState(false, NULL);
	}
	if (m_alphaDisableBlendingState)
	{
		(void)m_alphaDisableBlendingState->Release();
		m_alphaDisableBlendingState = NULL;
	}
	if (m_device)
	{
		(void)m_device->Release();
			m_device = NULL;
	}
	if (m_deviceContext)
	{
		(void)m_deviceContext->Release();
		m_deviceContext = NULL;
	}
	if (m_renderTargetView)
	{
		(void)m_renderTargetView->Release();
		m_renderTargetView = NULL;
	}
	if (m_depthStencilBuffer)
	{
		(void)m_depthStencilBuffer->Release();
		m_depthStencilBuffer = NULL;
	}
	if (m_depthStencilState)
	{
		(void)m_depthStencilState->Release();
		m_depthStencilState = NULL;
	}
	if (m_depthStencilView)
	{
		(void)m_depthStencilView->Release();
		m_depthStencilView = NULL;
	}
	if (m_rasterState)
	{
		(void)m_rasterState->Release();
		m_rasterState = NULL;
	}
	if (m_depthDisabledStencilState)
	{
		(void)m_depthDisabledStencilState->Release();
		m_depthDisabledStencilState = NULL;
	}
	if (m_alphaEnableBlendingState)
	{
		(void)m_alphaEnableBlendingState->Release();
		m_alphaEnableBlendingState = NULL;
	}



}

bool DXManager::Initialize( int32 screenWidth,  int32 screenHeight,bool fullscreen, HWND hwnd,bool vsync)
{
	HRESULT result;
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	uint32 numModes =0u, numerator = 0u, denominator = 0u;
	size_t stringLength;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	int error;
	ID3D11Texture2D* backBufferPtr;

	vsync_enabled = vsync;

	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(result))
	{
		return false;
	}

	result = factory->EnumAdapters(0, &adapter);
	if (FAILED(result))
	{
		return false;
	}
	result = adapter->EnumOutputs(0, &adapterOutput);
		if (FAILED(result))
		{
			return false;
	}

		result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
		if (FAILED(result))
		{
			return false;
		}
		//if (numModes > (sizeof(unsigned int) * 56))numModes = (sizeof(unsigned int) * 56);
		displayModeList = new DXGI_MODE_DESC[numModes];

		result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes,displayModeList);
		if (FAILED(result))
		{
			return true;
		}

		for (UINT i = 0u; i < numModes; ++i)
		{
			if (displayModeList[i].Width == (UINT)screenWidth)
			{
				if (displayModeList[i].Height == (UINT)screenHeight)
				{
					numerator = displayModeList[i].RefreshRate.Numerator;
					denominator = displayModeList[i].RefreshRate.Denominator;
				}
			}
		}

		if (numerator == 0u && denominator == 0u)
		{
			return false;
		}

		result = adapter->GetDesc(&adapterDesc);
		if (FAILED(result))
		{
			return false;
		}

		m_videoCardMemory = ( int32)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);
		error = wcstombs_s(&stringLength,m_videoCardDescription ,128,adapterDesc.Description, 128);

		if (error != 0)
		{
			return false;
		}

		if (displayModeList)
		{
			delete[] displayModeList;
			displayModeList = NULL;
		}

		if (adapterOutput)
		{
			(void)adapterOutput->Release();
			adapterOutput = NULL;
		}

		if (adapter)
		{
			(void)adapter->Release();
			adapter = NULL;
		}

		if (factory)
		{
			(void)factory->Release();
			factory = NULL;
		}


		if (!InitializeSwapChain(hwnd, fullscreen, screenWidth, screenHeight, numerator, denominator))
		{
			return false;
		}

		result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
		if(FAILED(result))
		{
			return false;
		}

		result = m_device->CreateRenderTargetView(backBufferPtr, NULL, &m_renderTargetView);
		if (FAILED(result))
		{
			return false;
		}

		if (backBufferPtr)
		{
			(void)backBufferPtr->Release();
			backBufferPtr = NULL;
		}
		

		if (!InitializeDepthBuffer(screenWidth, screenHeight))
		{
			return false;
		}

		if (!InitializeDepthStencilBuffer())
		{
			return false;
		}

		if (!InitializeStencilView())
		{
			return false;
		}

		m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
		if (!InitializeRasterizerState())
		{
			return false;
		}

		InitializeViewport(screenWidth,screenHeight);
		if (!InitializeAlphaBlending())
		{
			return false;
		}

		if (!InitializeZBuffer())
		{
			return false;
		}

	return true;
}

void DXManager::SetFullScreen(bool fullscreen)
{
	if (m_swapChain)
		m_swapChain->SetFullscreenState(fullscreen, nullptr);
}

void DXManager::BeginScrene(float r, float g, float b, float a)
{
	float color[4];
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;

	m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);

	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.f, 0);
}

void DXManager::BeginScrene(float* color)
{
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);

	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.f, 0);
}

void DXManager::EndScene()
{
		m_swapChain->Present(vsync_enabled, 0);
}

void DXManager::EnableAlphaBlending(bool enable)
{
	const float blendFactor[4]{};

	if (enable)
	{
		m_deviceContext->OMSetBlendState(m_alphaEnableBlendingState, blendFactor, 0xffffffff);
	}
	else
	{
		m_deviceContext->OMSetBlendState(m_alphaDisableBlendingState, blendFactor, 0xffffffff);
	}
}

void DXManager::EnableZBuffer(bool enable)
{
	if (enable)
	{
		m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);
	}
	else
	{
		m_deviceContext->OMSetDepthStencilState(m_depthDisabledStencilState, 1);
	}
}

void DXManager::Release()
{
	delete(this);
}

ID3D11Device * DXManager::GetDevice()
{
	return m_device;
}

ID3D11DeviceContext * DXManager::GetDeviceContext()
{
	return m_deviceContext;
}

bool DXManager::InitializeSwapChain(HWND hwnd, bool fullscreen,  int32 screenWidth,  int32 screenHeight, uint32 numerator, uint32 denominator)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D_FEATURE_LEVEL featureLevel;
	HRESULT result;

	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	swapChainDesc.BufferCount = 1;

	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;

	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	if (vsync_enabled)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	swapChainDesc.OutputWindow = hwnd;

	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = !fullscreen;

	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	swapChainDesc.Flags = 0;

	featureLevel = D3D_FEATURE_LEVEL_11_0;

	result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1,
		D3D11_SDK_VERSION,&swapChainDesc,&m_swapChain,&m_device,NULL,&m_deviceContext);
	if (FAILED(result))
	{
		return false;
	}



	return true;
}

bool DXManager::InitializeDepthBuffer(
	const int screenWidth,
	const int screenHeight
)
{
	struct D3D11_TEXTURE2D_DESC depthBufferDesc;
	HRESULT result;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
	depthBufferDesc.Width = screenWidth;
	depthBufferDesc.Height = screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	result = m_device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool DXManager::InitializeStencilView()
{
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	HRESULT result;

	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	result = m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);
	if (FAILED(result))
	{
		return false;
	}


	return true;
}

bool DXManager::InitializeDepthStencilBuffer()
{
	struct D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	HRESULT result;

	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthDisabledStencilState);
	if (FAILED(result))
	{
		return false;
	}

	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

	return true;
}

bool DXManager::InitializeRasterizerState()
{
	struct D3D11_RASTERIZER_DESC rasterDesc;
	HRESULT result;

	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = false;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	result = m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
	if (FAILED(result))
	{
		return false;
	}

	m_deviceContext->RSSetState(m_rasterState);

	return true;
}

void DXManager::InitializeViewport( int32 screenWidth,  int32 screenHeight)
{
	D3D11_VIEWPORT viewport;

	viewport.Width = static_cast<float>(screenWidth);
	viewport.Height = static_cast<float>(screenHeight);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	m_deviceContext->RSSetViewports(1, &viewport);



}

bool DXManager::InitializeAlphaBlending()
{
	D3D11_BLEND_DESC blendStateDesc;

	HRESULT result;
	ZeroMemory(&blendStateDesc, sizeof(D3D11_BLEND_DESC));
	blendStateDesc.RenderTarget[0].BlendEnable = true;
	blendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;


	result = m_device->CreateBlendState(&blendStateDesc, &m_alphaEnableBlendingState);
	if (FAILED(result))
	{
		return false;
	}

	blendStateDesc.RenderTarget[0].BlendEnable = false;

	result = m_device->CreateBlendState(&blendStateDesc, &m_alphaDisableBlendingState);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool DXManager::InitializeZBuffer()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	HRESULT result;

	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));


	depthStencilDesc.DepthEnable = false;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthDisabledStencilState);
	if (FAILED(result))
	{
		return false;
	}



	return true;
}
