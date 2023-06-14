package org.crimsonedge.core.entity;

public class JEntityState extends EntityState {

    public JEntityState() {
        try {
            setNatPtr(nCreateJEntity(this));
        }
        catch (Exception e) {
            System.out.println("Caught exception: " + e.getMessage());
        }
    }

    public void update(float tpf)
    {

    }

    public static native long nCreateJEntity(JEntityState entityState);
}
