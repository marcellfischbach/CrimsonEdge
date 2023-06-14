package org.crimsonedge.game;

public class Game {


    public void setup () {
        System.out.println("Game.setup");
    }

    public static long createTestEntityState (float x, float y, float z, float distance, float speed) {
        TestEntityState tes = new TestEntityState(x, y, z, distance, speed);

        return tes.getNatPtr();
    }

}
