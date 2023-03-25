package com.test.firsttestfirebase.model;

public class PirSensor extends Component {
    private Boolean automatic;
    private Integer timeSeconds;

    public PirSensor(Boolean isAutomatic, Integer timeSeconds) {
        super("pir_sensor");

        this.setAutomatic(isAutomatic);
        this.setTimeSeconds(timeSeconds);
    }

    public Boolean isAutomatic() {
        return automatic;
    }

    public void setAutomatic(Boolean automatic) {
        this.automatic = automatic;
    }

    public Integer getTimeSeconds() {
        return timeSeconds;
    }

    public void setTimeSeconds(Integer timeSeconds) {
        this.timeSeconds = timeSeconds;
    }
}
