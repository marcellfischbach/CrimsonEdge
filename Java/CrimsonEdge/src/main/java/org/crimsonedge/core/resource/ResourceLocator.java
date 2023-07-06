package org.crimsonedge.core.resource;

@SuppressWarnings("unused")
public class ResourceLocator {

    private final String m_locator;

    private final String m_proto;
    private final String m_path;
    private final String m_filename;
    private final String m_extension;
    private final String m_encoded;


    public ResourceLocator(String encoded) {
        m_locator = encoded;
        m_proto = extractProto(encoded);
        m_path = extractPath(encoded);
        m_filename = extractFilename(encoded);
        m_extension = extractExtension(encoded);
        m_encoded = m_path + m_filename;
    }


    public String getLocator() {
        return m_locator;
    }

    public String getProto() {
        return m_proto;
    }

    public String getPath() {
        return m_path;
    }

    public String getFilename() {
        return m_filename;
    }

    public String getExtension() {
        return m_extension;
    }

    public String getEncoded() {
        return m_encoded;
    }


    private String extractProto(String locator) {
        if (locator.startsWith("file://")) {
            return "file://";
        }
        else if (locator.startsWith("bundle://")) {
            return "bundle://";
        }
        else {
            return "file://";
        }
    }

    private String extractPath(String locator) {
        int endPos = locator.lastIndexOf('/');
        if (endPos == -1) {
            return "";
        }

        int startPos = 0;
        if (locator.startsWith("file://")) {
            startPos = 7;
        }
        else if (locator.startsWith("bundle://")) {
            startPos = 9;
        }

        if (startPos > endPos) {
            return "";
        }

        return locator.substring(startPos, endPos - startPos + 1);
    }

    private String extractFilename(String locator) {
        int pos = locator.lastIndexOf('/');
        if (pos == -1) {
            pos = 0;
        }
        else {
            pos++;
        }
        return locator.substring(pos);
    }

    private String extractExtension(String locator) {
        int idx = locator.lastIndexOf(".");
        if (idx != -1) {
            return locator.substring(idx + 1).toUpperCase();
        }
        return "";
    }
}
