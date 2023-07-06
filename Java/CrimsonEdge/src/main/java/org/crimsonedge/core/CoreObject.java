package org.crimsonedge.core;

public class CoreObject implements ICoreObject{

    private long natRef;

    @Override
    public long getNatRef() {
        return natRef;
    }

    @Override
    public void setNatRef(long natRef) {
        this.natRef = natRef;
    }
}
