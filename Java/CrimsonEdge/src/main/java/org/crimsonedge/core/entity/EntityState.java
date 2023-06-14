package org.crimsonedge.core.entity;

import org.crimsonedge.core.BaseObject;

public class EntityState extends BaseObject {


    private static native SpatialState nGetRoot(long cppPtr);
    public SpatialState getRoot() {
        return nGetRoot(getNatPtr());
    }
}
