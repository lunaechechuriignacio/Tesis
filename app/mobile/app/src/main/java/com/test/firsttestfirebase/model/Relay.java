package com.test.firsttestfirebase.model;

public class Relay extends Component {
    private final String path = "relays";

    private Integer number;
    private String startTime;
    private String endTime;
    private Boolean automatic;

    public Relay(Integer number) {
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

    public Integer getNumber() {
        return number;
    }

    public void setNumber(Integer number) {
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

    public Boolean isAutomatic() {
        return automatic;
    }

    public void setAutomatic(Boolean automatic) {
        this.automatic = automatic;
    }
}
