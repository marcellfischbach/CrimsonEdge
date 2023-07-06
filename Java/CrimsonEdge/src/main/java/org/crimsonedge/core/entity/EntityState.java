package org.crimsonedge.core.entity;

import org.crimsonedge.core.CoreObject;

public class EntityState extends CoreObject {


    private static native SpatialState nGetRoot(long cppPtr);
    public SpatialState getRoot() {
        return nGetRoot(getNatRef());
    }
}
