package HexagonalMap;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;


public class FieldController {
    private FieldViewer viewer;
    private FieldModel model;
    private class Mymouse extends MouseAdapter {
        @Override
        public void mouseClicked(MouseEvent e) {
            if(SwingUtilities.isRightMouseButton(e)){
                if(model.findUpCell() != null) {
                    model.getCell(model.findUpCell().getXY().x, model.findUpCell().getXY().y).setState(false);
                    viewer.repaint();
                }else{
                    return;
                }
            }else {
                Point point = new Point(viewer.getHex().getHexCoordinate(e.getX(), e.getY()));
                if (point.x < 0 | point.y < 0 | point.x >= FieldModel.SIZE | point.y >= FieldModel.SIZE)
                    return;
                model.setUserPoint(point);
            }
        }
    }

    public FieldController(FieldModel model, FieldViewer viewer){
        this.viewer = viewer;
        this.model = model;
        Mymouse mouse = new Mymouse();
        viewer.addMouseListener(mouse);
    }
}

