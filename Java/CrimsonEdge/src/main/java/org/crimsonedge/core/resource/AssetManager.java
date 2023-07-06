package org.crimsonedge.core.resource;

import org.crimsonedge.core.CEClass;

public class AssetManager {

    private native Object nGet (String cls, String locator);

    public <T> T get (Class<T> cls, ResourceLocator locator) {
        CEClass ceClass = cls.getAnnotation(CEClass.class);
        if (ceClass == null) {
            return null;
        }
        Object obj = nGet(ceClass.value(), locator.getLocator());
        return cls.isInstance(obj)
                ? cls.cast(obj)
                : null;
    }




    private AssetManager() {
    }

    private static AssetManager instance = null;

    public static AssetManager instance() {
        if (instance == null) {
            instance = new AssetManager();
        }
        return instance;
    }


}
