package com.test.firsttestfirebase;

public class Relay {
    int relayNumber;
    int status;
    int time;
    String time_start;
    String time_finish;
    boolean automatic;


    public Relay() {

        relayNumber = 0;
        status = 0;
        time = 0;
        time_start = "";
        time_finish = "";
        automatic = false;

    }

    int getRelayNumber() {
        return relayNumber;
    }

    void setRelayNumber(int newNumber) {
        relayNumber = newNumber;
    }

    int getStatus() {
        return status;
    }

    void setStatus(int Status) {
        this.status = status;
    }

    String getStartTime() {
        return time_start;
    }

    void setStartTime(String time) {
        time_start = time;
    }

    String getEndTime() {
        return time_finish;
    }

    void setEndTime(String time) {
        time_finish = time;
    }

    boolean getAutomatic() {
        return this.automatic;
    }

    void setAutomatic(boolean automatic) {
        this.automatic = automatic;

    }
}
