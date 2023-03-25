package com.test.firsttestfirebase.model;

public class PirSensor extends Component {
    private Integer timeSeconds;

    public PirSensor(Integer timeSeconds) {
        super("pir_sensor");
        this.setTimeSeconds(timeSeconds);
    }

    public Integer getTimeSeconds() {
        return timeSeconds;
    }

    public void setTimeSeconds(Integer timeSeconds) {
        this.timeSeconds = timeSeconds;
    }
}
