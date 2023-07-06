package org.crimsonedge.core.graphics.material;

import org.crimsonedge.core.CEClass;
import org.crimsonedge.core.ICoreObject;
import org.crimsonedge.core.graphics.EFillMode;
import org.crimsonedge.core.graphics.ERenderQueue;
import org.crimsonedge.core.graphics.EShadingMode;
import org.crimsonedge.core.math.Color4;
import org.crimsonedge.core.math.Vector2;
import org.crimsonedge.core.math.Vector3;
import org.crimsonedge.core.math.Vector4;

@CEClass("ce::iMaterial")
public interface IMaterial extends ICoreObject {

    EFillMode getFillMode ();
    ERenderQueue getRenderQueue();
    EShadingMode getShadingMode ();

    int indexOf(String attribute);

    void set(int idx, float value);
    void set(int idx, Vector2 value);
    void set(int idx, Vector3 value);
    void set(int idx, Vector4 value);
    void set(int idx, Color4 value);
    void set(int idx, int value);
}
