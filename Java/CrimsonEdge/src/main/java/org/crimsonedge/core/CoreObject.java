package org.crimsonedge.core;

public class CoreObject implements ICoreObject{

    private long natRef;

    @Override
    public long getNatRef() {
        return natRef;
    }

    @Override
    public void setNatRef(long natRef) {
        this.natRef = natRef;
    }


    public static native Object nNew(String cls);
    public static <T extends CoreObject> T create(Class<T> cls) {

        CEClass ceClass = cls.getAnnotation(CEClass.class);
        if (ceClass == null) {
            throw new NoCEClassDefinedException(cls);
        }


        Object obj = nNew(ceClass.value());
        if (!cls.isInstance(obj)) {
            return null;
        }

        return cls.cast(obj);
    }
}
