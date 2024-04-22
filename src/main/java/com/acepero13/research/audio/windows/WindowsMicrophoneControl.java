package com.acepero13.research.audio.windows;

import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;

public class WindowsMicrophoneControl {
    static {
        try {
            Path libFolder = copyResourceToTemp();
            System.load(libFolder.toAbsolutePath().toString());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private static Path copyResourceToTemp() throws IOException {
        Path tempFile = Files.createTempDirectory("muter").resolve("MicrophoneControl.dll");
        // Obtain resource as InputStream
        InputStream resourceStream = WindowsMicrophoneControl.class.getResourceAsStream("/com/acepero13/research/audio/windows/lib/MicrophoneControl.dll");

        try (resourceStream) {
            if (resourceStream == null) {
                throw new IllegalArgumentException("Resource not found: " + "/com/acepero13/research/audio/windows/lib/MicrophoneControl.dll");
            }

            // Copy resource to the temp file
            Files.copy(resourceStream, tempFile, StandardCopyOption.REPLACE_EXISTING);
            return tempFile;
        }
    }

    native void muteMicrophone(boolean mute);

    public void mute() {
        muteMicrophone(true);
    }

    public void unMute() {
        muteMicrophone(false);
    }



}
