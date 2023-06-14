package org.crimsonedge.core.entity;

import org.crimsonedge.core.math.Matrix4;

public class SpatialState extends EntityState {


    public SpatialState() {
    }

    private static native void nSetLocalMatrix(long refID, float[] matrix);
    public void setLocalMatrix(Matrix4 mat) {
        nSetLocalMatrix(getNatPtr(), mat.m);
    }


    @Override
    public String toString() {
        return "SpatialState :-)";
    }
}
