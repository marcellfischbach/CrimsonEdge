package org.crimsonedge.core;

public class NoCEClassDefinedException extends RuntimeException {

    private final Class<? extends CoreObject> cls;

    public NoCEClassDefinedException(Class<? extends CoreObject> cls) {
        super ("No CEClass defined for " + cls);
        this.cls = cls;
    }

    public Class<? extends CoreObject> getCls() {
        return cls;
    }
}
