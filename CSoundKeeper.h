#pragma once

#include <mmdeviceapi.h>
#include <audiopolicy.h>

class CSoundKeeper;
#include "CKeepSession.h"

class CSoundKeeper : public IMMNotificationClient
{
protected:

	LONG _cRef;

	~CSoundKeeper();

public:

	CSoundKeeper();

	// IUnknown methods

	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, VOID **ppvInterface);

	// Callback methods for device-event notifications.

	HRESULT STDMETHODCALLTYPE OnDefaultDeviceChanged(EDataFlow flow, ERole role, LPCWSTR pwstrDeviceId);
	HRESULT STDMETHODCALLTYPE OnDeviceAdded(LPCWSTR pwstrDeviceId);
	HRESULT STDMETHODCALLTYPE OnDeviceRemoved(LPCWSTR pwstrDeviceId);
	HRESULT STDMETHODCALLTYPE OnDeviceStateChanged(LPCWSTR pwstrDeviceId, DWORD dwNewState);
	HRESULT STDMETHODCALLTYPE OnPropertyValueChanged(LPCWSTR pwstrDeviceId, const PROPERTYKEY key);

protected:

	IMMDeviceEnumerator *DevEnumerator;
	bool IsStarted;
	CKeepSession** Keepers;
	UINT KeepersCount;
	HANDLE ShutdownEvent;
	HANDLE RestartEvent;

	HRESULT Start();
	HRESULT Stop();
	HRESULT Restart();

public:

	void FireRestart();
	void FireShutdown();
	HRESULT Main();
};
