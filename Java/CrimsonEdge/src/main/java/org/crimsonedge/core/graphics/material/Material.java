package org.crimsonedge.core.graphics.material;

import org.crimsonedge.core.CoreObject;
import org.crimsonedge.core.graphics.EFillMode;
import org.crimsonedge.core.graphics.ERenderQueue;
import org.crimsonedge.core.graphics.EShadingMode;
import org.crimsonedge.core.math.Color4;
import org.crimsonedge.core.math.Vector2;
import org.crimsonedge.core.math.Vector3;
import org.crimsonedge.core.math.Vector4;

public class Material extends CoreObject implements IMaterial {

    private native int nGetFillMode (long ptr);
    @Override
    public EFillMode getFillMode() {
        return null;
    }

    @Override
    public ERenderQueue getRenderQueue() {
        return null;
    }

    @Override
    public EShadingMode getShadingMode() {
        return null;
    }

    @Override
    public int indexOf(String attribute) {
        return 0;
    }

    @Override
    public void set(int idx, float value) {

    }

    @Override
    public void set(int idx, Vector2 value) {

    }

    @Override
    public void set(int idx, Vector3 value) {

    }

    @Override
    public void set(int idx, Vector4 value) {

    }

    @Override
    public void set(int idx, Color4 value) {

    }

    @Override
    public void set(int idx, int value) {

    }
}
