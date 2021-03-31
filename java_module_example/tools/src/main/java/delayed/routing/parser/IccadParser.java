package delayed.routing.parser;

import java.nio.file.Path;
import java.util.Iterator;

public class IccadParser extends Parser {
    private long numRows, numCols;

    public IccadParser(String path) {
        super(path);
    }

    public IccadParser(Path path) {
        super(path);
    }

    @Override
    protected void parse(Iterable<String> iterable) {
        var iterator = iterable.iterator();

        parse(iterator);
    }

    protected void parse(Iterator<String> iterator) {
        String keyword;
        int number;

        // MaxCellMove <maxMoveCount>
        keyword = iterator.next();
        assert keyword.equals("MaxCellMove");
        parseInt(iterator);

        // GGridBoundaryIdx <rowBeginIdx> <colBeginIdx> <rowEndIdx> <colEndIdx>
        keyword = iterator.next();

        // start and end are both equal to 1
        assert keyword.equals("GGridBoundaryIdx");
        number = parseInt(iterator);
        assert number == 1;
        number = parseInt(iterator);
        assert number == 1;
        numRows = parseInt(iterator);
        numCols = parseInt(iterator);

        // NumLayer <LayerCount>
        keyword = iterator.next();
        assert keyword.equals("NumLayer");
        int numLayers = parseInt(iterator);

        // Lay <layerName> <Idx> <RoutingDirection> <defaultSupplyOfOneGGrid>
        for (int i = 0; i < numLayers; ++i) {
            keyword = iterator.next();
            assert keyword.equals("Lay");
            iterator.next();
            parseInt(iterator);
            iterator.next();
            parseInt(iterator);
        }

        // NumNonDefaultSupplyGGrid <nonDefaultSupplyGGridCount>
        keyword = iterator.next();
        assert keyword.equals("NumNonDefaultSupplyGGrid");
        int numNonDefault = parseInt(iterator);

        // <rowIdx> <colIdx> <LayIdx> <incrOrDecrValue>
        for (int i = 0; i < numNonDefault; ++i) {
            parseInt(iterator);
            parseInt(iterator);
            parseInt(iterator);
            parseInt(iterator);
        }

        // NumMasterCell <masterCellCount>
        keyword = iterator.next();
        assert keyword.equals("NumMasterCell");
        int mcCount = parseInt(iterator);

        // MasterCell <masterCellName> <pinCount> <blockageCount>
        for (int i = 0; i < mcCount; ++i) {
            keyword = iterator.next();
            assert keyword.equals("MasterCell");
            iterator.next();
            int pinCount = parseInt(iterator);
            int blkgCount = parseInt(iterator);

            // Pin <pinName> <pinLayer>
            for (int j = 0; j < pinCount; ++j) {
                keyword = iterator.next();
                assert keyword.equals("Pin");
                iterator.next();
                iterator.next();
            }

            // Blkg <blockageName> <blockageLayer> <demand>
            for (int j = 0; j < blkgCount; ++j) {
                keyword = iterator.next();
                assert keyword.equals("Blkg");
                iterator.next();
                iterator.next();
                parseInt(iterator);
            }
        }

        // NumNeighborCellExtraDemand <count>
        keyword = iterator.next();
        assert keyword.equals("NumNeighborCellExtraDemand");
        int extraCount = parseInt(iterator);

        // sameGGrid <masterCellName1> <masterCellName2> <layerName> <demand>
        // adjHGGrid <masterCellName1> <masterCellName2> <layerName> <demand>
        for (int i = 0; i < extraCount; ++i) {
            keyword = iterator.next();

            switch (keyword) {
                case "sameGGrid":
                case "adjHGGrid":
                    break;
                default:
                    assert false;
            }

            iterator.next();
            iterator.next();
            iterator.next();
            parseInt(iterator);
        }

        // NumCellInst <cellInstCount>
        keyword = iterator.next();
        assert keyword.equals("NumCellInst");
        int cellCount = parseInt(iterator);

        // CellInst <instName> <masterCellName> <gGridRowIdx> <gGridColIdx>
        // <movableCstr>
        for (int i = 0; i < cellCount; ++i) {
            keyword = iterator.next();
            assert keyword.equals("CellInst");
            iterator.next();
            iterator.next();
            parseInt(iterator);
            parseInt(iterator);
            iterator.next();
        }

        // NumNets <netCount>
        keyword = iterator.next();
        assert keyword.equals("NumNets");
        int netCount = parseInt(iterator);

        // Net <netName> <numPins> <minRoutingLayConstraint>
        for (int i = 0; i < netCount; ++i) {
            keyword = iterator.next();
            assert keyword.equals("Net");
            String netName = iterator.next();
            assert netName.substring(0, 1).equals("N");
            int netId = parseInt(netName.substring(1)) - 1;
            assert netId == i;

            int numPins = parseInt(iterator);
            iterator.next();

            // Pin <instName>/<masterPinName>
            for (int j = 0; j < numPins; ++j) {
                keyword = iterator.next();
                assert keyword.equals("Pin");
                String[] bothNames = iterator.next().split("/");
                assert bothNames.length == 2;
                int cellId = parseInt(bothNames[0].substring(1)) - 1;
            }
        }

        // NumRoutes <routeSegmentCount>
        keyword = iterator.next();
        assert keyword.equals("NumRoutes");
        int rsCount = parseInt(iterator);

        // <sRowIdx> <sColIdx> <sLayIdx> <eRowIdx> <eColIdx> <eLayIdx> <netName>
        for (int i = 0; i < rsCount; ++i) {
            int sRow = parseInt(iterator);
            int sCol = parseInt(iterator);
            int sLay = parseInt(iterator);
            int eRow = parseInt(iterator);
            int eCol = parseInt(iterator);
            int eLay = parseInt(iterator);
            assert sRow == eRow || sCol == eCol || sLay == eLay;
            iterator.next();
        }

        assert !iterator.hasNext();
    }
}
