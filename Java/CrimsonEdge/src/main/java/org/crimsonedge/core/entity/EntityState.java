package org.crimsonedge.core.entity;

import org.crimsonedge.core.CoreObject;

public class EntityState extends CoreObject {

    private static native void nSetName(long ref, String name);
    public void setName (String name) {
        nSetName(getNatRef(), name);
    }

    private static native String nGetName (long ref);
    public String getName () {
        return nGetName(getNatRef());
    }


    private static native SpatialState nGetRoot(long cppPtr);
    public SpatialState getRoot() {
        return nGetRoot(getNatRef());
    }
}
