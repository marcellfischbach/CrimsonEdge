package org.crimsonedge.game;

import org.crimsonedge.core.entity.JEntityState;

public class TestEntityState extends JEntityState {

    @Override
    public void update(float tpf) {
        System.out.println("TestEntityState.update(" + tpf + ")");
    }
}
