package delayed.routing.structure;

import org.apache.commons.lang3.BooleanUtils;

public record Segment(int srow, int scol, int slay, int trow, int tcol, int tlay) {
    public Segment {
        if (srow > trow) {
            throw new IllegalArgumentException("srow <= trow");
        }
        if (scol > tcol) {
            throw new IllegalArgumentException("scol <= tcol");
        }
        if (slay > tlay) {
            throw new IllegalArgumentException("slay <= tlay");
        }

        int rowEq = BooleanUtils.toInteger(srow == trow);
        int colEq = BooleanUtils.toInteger(scol == tcol);
        int layEq = BooleanUtils.toInteger(slay == tlay);

        assert rowEq + colEq + layEq == 2;
    }

    public static Segment ordered(int srow, int scol, int slay, int trow, int tcol, int tlay) {
        if (srow < trow) {
            int tmp = srow;
            srow = trow;
            trow = tmp;
        }

        if (scol < tcol) {
            int tmp = scol;
            scol = tcol;
            tcol = tmp;
        }

        if (slay < tlay) {
            int tmp = slay;
            slay = tlay;
            tlay = tmp;
        }

        return new Segment(srow, scol, slay, trow, tcol, tlay);
    }
}
