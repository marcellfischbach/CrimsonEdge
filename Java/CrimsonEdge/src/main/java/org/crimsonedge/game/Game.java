package org.crimsonedge.game;

public class Game {


    public void setup () {
        System.out.println("Game.setup");
    }

    public static long createTestEntityState () {
        System.out.println("Game.createTestEntityState");
        TestEntityState tes = new TestEntityState();

        return tes.ref();
    }

}
