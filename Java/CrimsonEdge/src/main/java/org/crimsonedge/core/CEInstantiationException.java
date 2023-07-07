package org.crimsonedge.core;

public class CEInstantiationException extends RuntimeException {

    private final Class<? extends CoreObject> cls;

    public CEInstantiationException(Class<? extends CoreObject> cls) {
        super ("Unable to instantiate " + cls.getName());
        this.cls = cls;
    }

    public Class<? extends CoreObject> getCls() {
        return cls;
    }
}
