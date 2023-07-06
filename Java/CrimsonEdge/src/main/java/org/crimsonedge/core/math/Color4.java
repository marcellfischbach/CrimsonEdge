package org.crimsonedge.core.math;

public class Color4 {

    public float r;

    public float g;

    public float b;

    public float a;

    public Color4() {
        this(0.0f, 0.0f, 0.0f, 1.0f);
    }

    public Color4(float r, float g, float b, float a) {
        this.r = r;
        this.g = g;
        this.b = b;
        this.a = a;
    }
}
