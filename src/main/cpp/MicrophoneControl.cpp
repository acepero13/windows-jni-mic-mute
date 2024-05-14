#include <iostream>
#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include "com_acepero13_research_audio_windows_WindowsMicrophoneControl.h"

class MicrophoneControl {
public:
    MicrophoneControl() {
        CoInitialize(nullptr);  // Initialize COM library
        deviceEnumerator = nullptr;
        HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, IID_PPV_ARGS(&deviceEnumerator));
        if (FAILED(hr)) {
            std::cerr << "Failed to create device enumerator, HRESULT: " << hr << std::endl;
            exit(1);
        }
    }

    ~MicrophoneControl() {
        if (deviceEnumerator)
            deviceEnumerator->Release(); // Release the device enumerator
        CoUninitialize(); // Uninitialize COM library
    }

   

    void tryTomuteMicrophone(bool mute) {
        IMMDeviceCollection* deviceCollection = nullptr;
        HRESULT hr = deviceEnumerator->EnumAudioEndpoints(eCapture, DEVICE_STATE_ACTIVE, &deviceCollection);
        if (FAILED(hr)) {
            std::cerr << "Failed to enumerate audio endpoints, HRESULT: " << hr << std::endl;
            return;
        }

        UINT deviceCount;
        hr = deviceCollection->GetCount(&deviceCount);
        if (FAILED(hr)) {
            std::cerr << "Failed to get device count, HRESULT: " << hr << std::endl;
            deviceCollection->Release();
            return;
        }

        for (UINT i = 0; i < deviceCount; ++i) {
            IMMDevice* device = nullptr;
            hr = deviceCollection->Item(i, &device);
            if (FAILED(hr)) {
                std::cerr << "Failed to get device, HRESULT: " << hr << std::endl;
                continue;
            }

            muteMicrophone(device, mute);
            device->Release();
        }

        deviceCollection->Release();
    }


private:
    IMMDeviceEnumerator* deviceEnumerator;


    void muteMicrophone(IMMDevice* device, bool mute) {
        IAudioEndpointVolume* endpointVolume = nullptr;
        HRESULT hr = device->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, nullptr, reinterpret_cast<void**>(&endpointVolume));
        if (FAILED(hr)) {
            std::cerr << "Failed to activate endpoint volume, HRESULT: " << hr << std::endl;
            return;
        }

        hr = endpointVolume->SetMute(mute, NULL);
        if (FAILED(hr)) {
            std::cerr << "Failed to set mute, HRESULT: " << hr << std::endl;
        } else {
            std::cout << "Mute set to " << (mute ? "MUTED" : "UN-MUTED") << std::endl;
        }

        endpointVolume->Release();
    }
};

extern "C"
JNIEXPORT void JNICALL Java_com_acepero13_research_audio_windows_WindowsMicrophoneControl_muteMicrophone(JNIEnv *env, jobject obj, jboolean mute) {
    MicrophoneControl micController;
    micController.tryTomuteMicrophone(mute);
}

