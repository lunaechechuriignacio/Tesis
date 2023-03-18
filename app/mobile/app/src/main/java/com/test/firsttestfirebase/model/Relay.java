package com.test.firsttestfirebase.model;

public class Relay extends Component {
    private final String path = "relays";

    private int number;
    private String startTime;
    private String endTime;
    private boolean automatic;

    public Relay(int number) {
        super("relay_" + number);
        this.componentStatus = ComponentStatus.OFF;

        this.number = number;
        this.startTime = "";
        this.endTime = "";
        this.automatic = false;
    }

    public String getPath() {
        return path;
    }

    public int getNumber() {
        return number;
    }

    public void setNumber(int number) {
        this.number = number;
    }

    public String getStartTime() {
        return startTime;
    }

    public void setStartTime(String startTime) {
        this.startTime = startTime;
    }

    public String getEndTime() {
        return endTime;
    }

    public void setEndTime(String endTime) {
        this.endTime = endTime;
    }

    public boolean isAutomatic() {
        return automatic;
    }

    public void setAutomatic(boolean automatic) {
        this.automatic = automatic;
    }
}
