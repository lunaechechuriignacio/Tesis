package com.test.firsttestfirebase.model;

public class PirSensor extends Component {
    private boolean automatic;
    private int timeSeconds;

    public PirSensor() {
        super("pir_sensor");
        this.componentStatus = ComponentStatus.ON;

        this.automatic = false;
        this.timeSeconds = 0;
    }

    public boolean isAutomatic() {
        return automatic;
    }

    public void setAutomatic(boolean automatic) {
        this.automatic = automatic;
    }

    public int getTimeSeconds() {
        return timeSeconds;
    }

    public void setTimeSeconds(int timeSeconds) {
        this.timeSeconds = timeSeconds;
    }
}
