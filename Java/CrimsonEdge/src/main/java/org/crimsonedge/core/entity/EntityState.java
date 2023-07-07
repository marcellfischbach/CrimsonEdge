package org.crimsonedge.core.entity;

import org.crimsonedge.core.CEClass;
import org.crimsonedge.core.CoreObject;
import org.crimsonedge.core.graphics.Mesh;

@CEClass("ce::EntityState")
public class EntityState extends CoreObject {

    public void setName(String name) {
        nSetName(getNatRef(), name);
    }

    public String getName() {
        return nGetName(getNatRef());
    }


    public SpatialState getRoot() {
        return nGetRoot(getNatRef());
    }


    private static native void nSetName(long ref, String name);

    private static native String nGetName(long ref);

    private static native SpatialState nGetRoot(long cppPtr);

}
