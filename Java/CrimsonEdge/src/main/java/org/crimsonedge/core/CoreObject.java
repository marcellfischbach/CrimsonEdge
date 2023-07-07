package org.crimsonedge.core;

import org.crimsonedge.core.entity.JEntityState;

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
        if (JEntityState.class.isAssignableFrom(cls)) {
            try {
                return cls.getConstructor().newInstance();
            }
            catch (Exception e) {
                throw new CEInstantiationException(cls);
            }
        }

        CEClass ceClass = cls.getAnnotation(CEClass.class);
        if (ceClass == null) {
            throw new NoCEClassDefinedException(cls);
        }


        Object obj = nNew(ceClass.value());
        if (obj == null) {
            throw new CEInstantiationException(cls);
        }
        if (!cls.isInstance(obj)) {
            throw new ClassCastException("Unable to cast " + obj.getClass() + " to " + cls);
        }

        return cls.cast(obj);
    }
}
