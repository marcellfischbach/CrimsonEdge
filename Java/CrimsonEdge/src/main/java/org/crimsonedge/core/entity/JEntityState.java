package org.crimsonedge.core.entity;

public class JEntityState extends EntityState {

    private long m_ref;

    public JEntityState() {
        try {
            System.out.println("JEntityState.JEntityState");
            m_ref = createJEntity(this);
            System.out.println("JEntityState.JEntityState: " + m_ref);
        }
        catch (Exception e) {
            System.out.println("Caught exception: " + e.getMessage());
        }
    }

    public void update(float tpf)
    {

    }


    public long ref () {
        return m_ref;
    }

    public static native long createJEntity(JEntityState entityState);
}
