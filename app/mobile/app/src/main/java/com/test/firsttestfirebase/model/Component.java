package com.test.firsttestfirebase.model;

public abstract class Component {
    protected String alias;
    protected ComponentStatus componentStatus;

    public Component(String alias) {
        this.alias = alias;
    }

    public String getAlias() {
        return alias;
    }

    public void setAlias(String alias) {
        this.alias = alias;
    }

    public ComponentStatus getComponentStatus() {
        return componentStatus;
    }

    public void setComponentStatus(ComponentStatus componentStatus) {
        this.componentStatus = componentStatus;
    }
}
