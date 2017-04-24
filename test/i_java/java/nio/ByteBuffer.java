package java.nio;

import android.os.Build;

@SimpleCClassName
public class ByteBuffer {
    public static ByteBuffer allocate(int capacity);
    public static ByteBuffer allocateDirect(int capacity);
    public final  Buffer     limit(int newLimit);

    public char   getChar();
    public short  getShort();
    public int    getInt();
    public long   getLong();
    public float  getFloat();
    public double getDouble();

    public ByteBuffer putChar(char value);
    public ByteBuffer putShort(short value);
    public ByteBuffer putInt(int value);
    public ByteBuffer putLong(long value);
    public ByteBuffer putFloat(float value);
    public ByteBuffer putDouble(double value);
}
