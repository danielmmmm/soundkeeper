#pragma once

#include <mmdeviceapi.h>
#include <audioclient.h>

class CKeepSession;
#include "CSoundKeeper.h"

//
// Play silence via WASAPI
//

class CKeepSession : IAudioSessionEvents
{
public:

	enum RenderSampleType
	{
		SampleTypeFloat,
		SampleType16BitPCM,
	};

protected:

	LONG    _RefCount;
	//
	//  Core Audio Rendering member variables.
	//
	CSoundKeeper* SoundKeeper;
	IMMDevice* _Endpoint;
	IAudioClient* _AudioClient;
	IAudioRenderClient* _RenderClient;

	HANDLE      _RenderThread;
	HANDLE      _ShutdownEvent;
	WAVEFORMATEX* _MixFormat;
	UINT32      _FrameSize;
	RenderSampleType _RenderSampleType;
	UINT32      _BufferSizeInFrames;

	IAudioSessionControl *  _AudioSessionControl;
	UINT32 BufferSizeInMs;

	~CKeepSession(void);

public:

	CKeepSession(CSoundKeeper* soundkeeper, IMMDevice* endpoint);
	bool Initialize();
	void Shutdown();

private:

	//
	//  Render buffer management.
	//
	static DWORD __stdcall WASAPIRenderThread(LPVOID Context);
	DWORD CKeepSession::DoRenderThread();

	STDMETHOD(OnDisplayNameChanged) (LPCWSTR /*NewDisplayName*/, LPCGUID /*EventContext*/) { return S_OK; };
	STDMETHOD(OnIconPathChanged) (LPCWSTR /*NewIconPath*/, LPCGUID /*EventContext*/) { return S_OK; };
	STDMETHOD(OnSimpleVolumeChanged) (float /*NewSimpleVolume*/, BOOL /*NewMute*/, LPCGUID /*EventContext*/);
	STDMETHOD(OnChannelVolumeChanged) (DWORD /*ChannelCount*/, float /*NewChannelVolumes*/[], DWORD /*ChangedChannel*/, LPCGUID /*EventContext*/) { return S_OK; };
	STDMETHOD(OnGroupingParamChanged) (LPCGUID /*NewGroupingParam*/, LPCGUID /*EventContext*/) { return S_OK; };
	STDMETHOD(OnStateChanged) (AudioSessionState /*NewState*/) { return S_OK; };
	STDMETHOD(OnSessionDisconnected) (AudioSessionDisconnectReason DisconnectReason);

	//
	// IUnknown
	//

public:

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID Iid, void **Object);
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();
};
