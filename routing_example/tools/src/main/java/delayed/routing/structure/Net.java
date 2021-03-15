package delayed.routing.structure;

import org.apache.commons.collections4.IteratorUtils;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Net {
    public Net(List<Segment> segments) {
        var segList = new ArrayList<>(segments);

        Set<Integer> allXPos = segList.stream().flatMap(seg -> Stream.of(seg.srow(), seg.trow()))
                .collect(Collectors.toSet());
        Set<Integer> allYPos = segList.stream().flatMap(seg -> Stream.of(seg.scol(), seg.tcol()))
                .collect(Collectors.toSet());

        int xSize = allXPos.size(), ySize = allYPos.size();
        int[][] tmpGrid = new int[xSize][ySize];

        ArrayList<Integer> allXPosList = new ArrayList<>(allXPos);
        ArrayList<Integer> allYPosList = new ArrayList<>(allYPos);
        Collections.sort(allXPosList);
        Collections.sort(allYPosList);

        // xPos and yPos stores a list of positions
        Integer[] xPos = (Integer[]) allXPosList.toArray();
        Integer[] yPos = (Integer[]) allYPosList.toArray();
        // posX and poxY maps those positions back to indices
        Map<Integer, Integer> posX = new HashMap<>();
        Map<Integer, Integer> posY = new HashMap<>();

        for (int i = 0; i < xPos.length; ++i) {
            posX.put(xPos[i], i);
        }

        for (int i = 0; i < yPos.length; ++i) {
            posY.put(yPos[i], i);
        }

        assert posX.size() == xSize && posY.size() == ySize;

        int[][] grid = new int[xSize][ySize];

        // TODO: lay down the paint
    }

    public Net(Iterable<Segment> segments) {
        this(segments.iterator());
    }

    public Net(Iterator<Segment> segments) {
        this(IteratorUtils.toList(segments));
    }

    public Net(Segment[] segments) {
        this(Arrays.asList(segments));
    }
}
