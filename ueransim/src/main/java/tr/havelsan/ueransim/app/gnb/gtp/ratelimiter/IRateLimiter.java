package tr.havelsan.ueransim.app.gnb.gtp.ratelimiter;

import tr.havelsan.ueransim.app.common.PduSessionResource;
import tr.havelsan.ueransim.utils.octets.OctetString;

/**
 * Interface for RateLimiter.
 */
public interface IRateLimiter {
    /**
     * Handles downlink IP packets.
     * @param pduSession the PDU session of which packets must be managed
     * @param ipPacket the single IP packet.
     */
    void handleDownlinkPacket(PduSessionResource pduSession, OctetString ipPacket);

    /**
     * Handles uplink IP packets.
     * @param pduSession the PDU session of which packets must be managed
     * @param ipPacket the single IP packet.
     */
    void handleUplinkPacket(PduSessionResource pduSession, OctetString ipPacket);

    /**
     * Insert or update bucket based on the new PDU session established.
     * @param pduSession the new PDU session.
     */
    void insertOrUpdateBucket(PduSessionResource pduSession);
}
