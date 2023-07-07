package org.crimsonedge.game;

import org.crimsonedge.core.CoreObject;
import org.crimsonedge.core.entity.Entity;
import org.crimsonedge.core.entity.StaticMeshState;
import org.crimsonedge.core.entity.World;
import org.crimsonedge.core.graphics.Mesh;

public class Game {


    public void setup () {
        System.out.println("Game.setup");
    }

    public static long createTestEntityState (float x, float y, float z, float distance, float speed) {
        TestEntityState tes = new TestEntityState(x, y, z, distance, speed);

        return tes.getNatRef();
    }

    public static void createTestWorld(World world, Mesh mesh) {

        System.out.println("Create test world");
        try {
            for (int a = 0, i = 0; i < 100; i++) {
                for (int j = 0; j < 100; j++, a++) {

                    Entity entity = CoreObject.create(Entity.class);
                    entity.setName("Sphere: " + (i + 1) + ":" + (j + 1));

                    StaticMeshState meshStateSphere = CoreObject.create(StaticMeshState.class);
                    meshStateSphere.setName("Mesh");
                    meshStateSphere.setMesh(mesh);
                    entity.attach(meshStateSphere);



                    float rnd = (float) Math.random();
                    TestEntityState testState = new TestEntityState(i - 50.0f, 0.25f, j - 50.0f, 0.25f, 0.5f + rnd);
                    entity.attach(testState);


                    world.attach(entity);
                }
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }

}
