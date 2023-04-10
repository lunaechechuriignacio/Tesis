package com.test.firsttestfirebase.model;

public abstract class Component {
    protected String alias;

    public Component(String alias) {
        this.alias = alias;
    }

    public String getAlias() {
        return alias;
    }
}
