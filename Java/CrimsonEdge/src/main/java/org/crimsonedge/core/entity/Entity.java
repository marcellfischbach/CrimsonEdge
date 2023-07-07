package org.crimsonedge.core.entity;

import org.crimsonedge.core.CEClass;
import org.crimsonedge.core.CoreObject;

@CEClass("ce::Entity")
public class Entity extends CoreObject {


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


    public boolean attach (EntityState state) {
        if (state == null) {
            return false;
        }
        return nAttachState(getNatRef(), state.getNatRef());
    }

    public boolean detach (EntityState state) {
        if (state == null) {
            return false;
        }
        return nDetachState(getNatRef(), state.getNatRef());
    }

    public void setRoot(SpatialState rootState) {
        if (rootState == null) {
            return;
        }
        nSetRoot(getNatRef(), rootState.getNatRef());
    }

    public SpatialState getRoot() {
        return nGetRoot(getNatRef());
    }



    private static native void nSetName(long ref, String name);

    private static native String nGetName(long ref);

    private static native boolean nAttach(long thisRef, long entityRef, long parentStateRef);

    private static native boolean nDetach(long thisRef, long entityRef);

    private static native boolean nAttachState(long thisRef, long entitStateRef);
    private static native boolean nDetachState(long thisRef, long entitStateRef);

    private static native void nSetRoot(long thisRef, long spatialStateRef);
    private static native SpatialState nGetRoot(long thisRef);

}
