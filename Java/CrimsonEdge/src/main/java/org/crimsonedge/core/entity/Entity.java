package org.crimsonedge.core.entity;

import org.crimsonedge.core.CoreObject;

public class Entity extends CoreObject {


    private static native void nSetName(long ref, String name);

    private static native String nGetName(long ref);

    private static native boolean nAttach(long thisRef, long entityRef, long parentStateRef);

    private static native boolean nDetach(long thisRef, long entityRef);

    public void setName(String name) {
        nSetName(getNatRef(), name);
    }

    public String getName() {
        return nGetName(getNatRef());
    }

    public boolean attach(Entity entity) {
        return attach(entity, null);
    }

    public boolean attach(Entity entity, SpatialState parentState) {
        return nAttach(getNatRef(),
                entity.getNatRef(),
                parentState != null ? parentState.getNatRef() : 0L);
    }

    public boolean detach(Entity entity) {
        return nDetach(getNatRef(), entity.getNatRef());
    }
}
