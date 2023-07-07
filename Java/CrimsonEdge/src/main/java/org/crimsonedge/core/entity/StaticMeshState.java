package org.crimsonedge.core.entity;

import org.crimsonedge.core.CEClass;
import org.crimsonedge.core.graphics.Mesh;

@CEClass("ce::StaticMeshState")
public class StaticMeshState extends SpatialState {



    public void setMesh (Mesh mesh) {
        if (mesh == null) {
            return;
        }

        nSetMesh(getNatRef(), mesh.getNatRef());
    }

    public Mesh getMesh () {
        return nGetMesh(getNatRef());
    }



    private static native void nSetMesh (long ref, long meshRef);

    private static native Mesh nGetMesh (long ref);
}
