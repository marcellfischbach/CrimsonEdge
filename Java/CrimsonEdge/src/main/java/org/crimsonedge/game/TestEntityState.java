package org.crimsonedge.game;

import org.crimsonedge.core.entity.JEntityState;
import org.crimsonedge.core.entity.SpatialState;
import org.crimsonedge.core.math.Matrix4;
import org.crimsonedge.core.math.Vector3;

public class TestEntityState extends JEntityState {

    private float x;
    private float y;
    private float z;

    private float animationValue = 0.0f;
    private float animationSpeed = 1.0f;
    private float distance = 1.0f;

    private Matrix4 mat = new Matrix4();


    public TestEntityState(float x, float y, float z, float distance, float speed) {
        this.x = x;
        this.y = y;
        this.z = z;
        this.distance = distance;
        this.animationSpeed = speed;
    }

    @Override
    public void update(float tpf) {
        try {
            animationValue += tpf * animationSpeed;
            SpatialState root = getRoot();
            if (root != null) {
                mat.setTranslation(new Vector3(
                        this.x + (float) Math.cos(animationValue) * distance,
                        this.y,
                        this.z + (float) Math.sin(animationValue * 1.3) * distance

                ));

                root.setLocalMatrix(mat);

            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }
}
