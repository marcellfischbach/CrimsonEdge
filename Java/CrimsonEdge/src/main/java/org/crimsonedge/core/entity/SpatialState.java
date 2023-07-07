package org.crimsonedge.core.entity;

import org.crimsonedge.core.CEClass;
import org.crimsonedge.core.math.Matrix4;

@CEClass("ce::SpatialState")
public class SpatialState extends EntityState {


    public SpatialState() {
    }

    private static native void nSetLocalMatrix(long refID, float[] matrix);
    public void setLocalMatrix(Matrix4 mat) {
        nSetLocalMatrix(getNatRef(), mat.m);
    }



}
