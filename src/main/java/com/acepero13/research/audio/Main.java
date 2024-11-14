package com.acepero13.research.audio;

import com.acepero13.research.audio.windows.WindowsMicrophoneControl;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        System.out.println("Test method running!");
        WindowsMicrophoneControl micControl = WindowsMicrophoneControl.getInstance();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.print("Enter command (m/u/q): ");
            String input = scanner.nextLine().toLowerCase().trim();

            switch (input) {
                case "m":
                    System.out.println("Muting microphone...");
                    micControl.mute();
                    break;
                case "u":
                    System.out.println("Unmuting microphone...");
                    micControl.unMute();
                    break;
                case "q":
                    System.out.println("Exiting program...");
                    scanner.close();
                    micControl.cleanupCOM();
                    return;
                default:
                    System.out.println("Invalid command! Use 'm' for mute, 'u' for unmute, or 'q' to quit");
            }
        }
    }
}