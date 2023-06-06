package org.crimsonedge.core.entity;

import org.crimsonedge.core.math.Matrix4;

public class SpatialState extends EntityState {


    public void setLocalMatrix(Matrix4 mat) {
        setLocalMatrix(refID, mat.m);
    }

    private static native void setLocalMatrix(long refID, float[] matrix);

}
