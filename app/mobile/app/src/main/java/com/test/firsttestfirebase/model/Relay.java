package com.test.firsttestfirebase.model;

public class Relay extends Component {
    private final String path = "relays";

    private Integer number;
    private Boolean automatic;
    protected RelayStatus relayStatus;

    public Relay(Integer number, Boolean isAutomatic, RelayStatus relayStatus) {
        super("relay_" + number);

        this.number = number;
        this.setAutomatic(isAutomatic);
        this.setRelayStatus(relayStatus);
    }

    public String getPath() {
        return path;
    }

    public Integer getNumber() {
        return number;
    }

    public Boolean isAutomatic() {
        return automatic;
    }

    public void setAutomatic(Boolean automatic) {
        this.automatic = automatic;
    }

    public RelayStatus getRelayStatus() {
        return relayStatus;
    }

    public void setRelayStatus(RelayStatus relayStatus) {
        this.relayStatus = relayStatus;
    }
}
