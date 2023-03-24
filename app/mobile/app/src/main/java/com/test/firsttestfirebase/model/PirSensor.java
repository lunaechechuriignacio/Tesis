package com.test.firsttestfirebase.model;

public class PirSensor extends Component {
    private Boolean automatic;
    private Integer timeSeconds;

    public PirSensor() {
        super("pir_sensor");
        this.componentStatus = ComponentStatus.ON;

        this.automatic = false;
        this.timeSeconds = 0;
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
