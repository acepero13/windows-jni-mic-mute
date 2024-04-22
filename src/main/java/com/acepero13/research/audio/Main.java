package com.acepero13.research.audio;

import com.acepero13.research.audio.windows.WindowsMicrophoneControl;

public class Main {
    public static void main(String[] args) {
        System.out.println("Test method running!");
        WindowsMicrophoneControl micControl = new WindowsMicrophoneControl();
        // Mute the microphone
        micControl.mute();
        // Optionally, unmute later
        micControl.unMute();
    }
}