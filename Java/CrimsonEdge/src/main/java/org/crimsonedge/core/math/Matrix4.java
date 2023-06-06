package org.crimsonedge.core.math;

public class Matrix4 {

    private static final int M00 = 0;
    private static final int M01 = 1;
    private static final int M02 = 2;
    private static final int M03 = 3;
    private static final int M10 = 4;
    private static final int M11 = 5;
    private static final int M12 = 6;
    private static final int M13 = 7;
    private static final int M20 = 8;
    private static final int M21 = 9;
    private static final int M22 = 10;
    private static final int M23 = 11;
    private static final int M30 = 12;
    private static final int M31 = 13;
    private static final int M32 = 14;
    private static final int M33 = 15;


    public final float[] m = new float[16];

    public Matrix4() {
        m[M00] = 1.0f;
        m[M01] = 0.0f;
        m[M02] = 0.0f;
        m[M03] = 0.0f;
        m[M10] = 0.0f;
        m[M11] = 1.0f;
        m[M12] = 0.0f;
        m[M13] = 0.0f;
        m[M20] = 0.0f;
        m[M21] = 0.0f;
        m[M22] = 1.0f;
        m[M23] = 0.0f;
        m[M30] = 0.0f;
        m[M31] = 0.0f;
        m[M32] = 0.0f;
        m[M33] = 1.0f;
    }

    public void setTranslation (Vector3 translation) {
        m[M30] = translation.x;
        m[M31] = translation.y;
        m[M32] = translation.z;
    }
}
