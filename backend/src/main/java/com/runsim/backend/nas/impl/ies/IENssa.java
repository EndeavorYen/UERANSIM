package com.runsim.backend.nas.impl.ies;

import com.runsim.backend.exceptions.DecodingException;
import com.runsim.backend.nas.Decoder;
import com.runsim.backend.nas.core.ies.InformationElement4;
import com.runsim.backend.utils.OctetInputStream;

import java.util.ArrayList;

public class IENssa extends InformationElement4 {

    public IESNssa[] sNssas;

    @Override
    protected InformationElement4 decodeIE4(OctetInputStream stream, int length) {
        var list = new ArrayList<IESNssa>();
        var res = new IENssa();
        int read = 0;

        while (read < length) {
            int subLength = stream.peekOctetI();
            list.add(Decoder.ie4(stream, false, IESNssa.class));
            read += subLength + 1;
        }

        if (read > length)
            throw new DecodingException("read length exceeds the ie length");

        res.sNssas = list.toArray(new IESNssa[0]);
        return res;
    }
}
