package org.crimsonedge.core.entity;

import org.crimsonedge.core.CEClass;
import org.crimsonedge.core.CoreObject;

@CEClass("ce::World")
public class World extends CoreObject {


    private static native void nAttach(long world, long entity);
    public void attach(Entity entity) {
        if (entity != null) {
            nAttach(getNatRef(), entity.getNatRef());
        }
    }

    private static native void nDetach(long world, long entity);
    public void detach(Entity entity) {
        if (entity != null) {
            nDetach(getNatRef(), entity.getNatRef());
        }

    }
}
