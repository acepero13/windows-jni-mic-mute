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
        IMMDevice* defaultDevice = nullptr;
        IAudioEndpointVolume* endpointVolume = nullptr;
        HRESULT hr = deviceEnumerator->GetDefaultAudioEndpoint(eCapture, eCommunications, &defaultDevice);
        if (FAILED(hr)) {
            std::cerr << "Failed to get default audio endpoint, HRESULT: " << hr << std::endl;
            return;
        }

        if (defaultDevice) {
            hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, nullptr, reinterpret_cast<void**>(&endpointVolume));
            if (FAILED(hr)) {
                std::cerr << "Failed to activate endpoint volume, HRESULT: " << hr << std::endl;
                defaultDevice->Release();
                return;
            }

            if (endpointVolume) {
                hr = endpointVolume->SetMute(mute, NULL);
                if (FAILED(hr)) {
                    std::cerr << "Failed to set mute, HRESULT: " << hr << std::endl;
                } else {
                    std::cout << "Mute set to " << (mute ? "ON" : "OFF") << std::endl;
                }
                endpointVolume->Release();
            }
            defaultDevice->Release();
        }
    }


private:
    IMMDeviceEnumerator* deviceEnumerator;
};

extern "C"
JNIEXPORT void JNICALL Java_com_acepero13_research_audio_windows_WindowsMicrophoneControl_muteMicrophone(JNIEnv *env, jobject obj, jboolean mute) {
    MicrophoneControl micController;
    micController.tryTomuteMicrophone(mute);
}

