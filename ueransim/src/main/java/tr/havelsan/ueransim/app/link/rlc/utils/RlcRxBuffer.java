package tr.havelsan.ueransim.app.link.rlc.utils;

import tr.havelsan.ueransim.app.link.rlc.pdu.RxPdu;
import tr.havelsan.ueransim.utils.OctetOutputStream;
import tr.havelsan.ueransim.utils.octets.OctetString;

import java.util.LinkedList;

public class RlcRxBuffer<T extends RxPdu> {

    private final ISnCompare snCompare;
    private final LinkedList<T> list;
    private final int maxSize;
    private int currentSize;

    public RlcRxBuffer(ISnCompare snCompare, int maxSize) {
        this.snCompare = snCompare;
        this.maxSize = maxSize;
        this.list = new LinkedList<>();
    }

    public void add(T rxPdu) {
        RlcUtils.insertSortedLinkedList(list, rxPdu, (a, b) -> {
            if (a.sn == b.sn)
                return Integer.compare(a.so, b.so);
            return snCompare.compare(a.sn, b.sn);
        });

        // No check for max size, it should be done externally using hasRoomFor method.
        currentSize += rxPdu.data.length;
    }

    public boolean hasRoomFor(int size) {
        return currentSize + size <= maxSize;
    }

    public boolean hasRoomFor(T rxPdu) {
        return hasRoomFor(rxPdu.data.length);
    }

    public void clear() {
        list.clear();
        currentSize = 0;
    }

    public boolean hasMissingBytes(int sn) {
        var it = list.listIterator();

        T cursor;
        do {
            // No such a PDU, therefore we don't have a missing segment.
            if (!it.hasNext())
                return false;
            cursor = it.next();
        } while (cursor.sn != sn);

        if (cursor._isProcessed) {
            // The related SN is already processed, therefore we don't have a missing segment.
            return false;
        }

        int lastByte = -1;
        while (true) {
            if (cursor.sn != sn)
                break;

            if (cursor.so > lastByte + 1)
                return true;
            int newLastByte = cursor.so + cursor.data.length - 1;
            if (newLastByte > lastByte)
                lastByte = newLastByte;

            if (it.hasNext())
                cursor = it.next();
            else
                break;
        }

        return false;
    }

    public boolean isAllSegmentsReceived(int sn) {
        var it = list.listIterator();

        T cursor;
        do {
            if (!it.hasNext())
                return false;
            cursor = it.next();
        } while (cursor.sn != sn);

        // WARNING: Check if it is already reassembled and delivered. Returning false if it is
        //  already processes. Because no need to reprocess it. We can consider this method as
        //  "ready to reassemble and deliver" instead of "is all segments received?"
        if (cursor._isProcessed)
            return false;

        int lastByte = -1;
        while (true) {
            if (cursor.sn != sn)
                break;

            if (cursor.so > lastByte + 1)
                return false;
            if (cursor.si.hasLast())
                return true;
            int newLastByte = cursor.so + cursor.data.length - 1;
            if (newLastByte > lastByte)
                lastByte = newLastByte;

            if (it.hasNext())
                cursor = it.next();
            else
                break;
        }

        return false;
    }

    public OctetString reassemble(int sn) {
        var it = list.listIterator();

        T cursor;
        do {
            if (!it.hasNext())
                return null;
            cursor = it.next();
        } while (cursor.sn != sn);

        var stream = new OctetOutputStream();
        stream.writeOctetString(cursor.data);

        while (it.hasNext()) {
            cursor = it.next();
            if (cursor.sn == sn) {
                stream.writeOctetString(cursor.data);
                cursor._isProcessed = true;
                currentSize -= cursor.data.length;
            } else {
                break;
            }
        }

        if (stream.length() == 0)
            return null;

        return stream.toOctetString();
    }
}
