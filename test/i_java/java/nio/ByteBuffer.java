package java.nio;

import android.os.Build;

@SimpleCClassName
public class ByteBuffer {
    public static ByteBuffer allocate(int capacity);
    public static ByteBuffer allocateDirect(int capacity);
    public final  Buffer     limit(int newLimit);

    public double getDouble();
}
