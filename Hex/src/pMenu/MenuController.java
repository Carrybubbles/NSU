package pMenu;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import Audio.SoundJLayer;

public class MenuController{
    private MenuModel model;
    private MenuViewer viewer;

    private class MyActionListener implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() == viewer.getPVP()) {
                model.setMode(MenuModel.Modes.PVP);
                new SoundJLayer("src/resources/fight.mp3").play();
                model.StartGame();
            } else if (e.getSource() == viewer.getPVE()) {
                model.setMode(MenuModel.Modes.PVE);
                new SoundJLayer("src/resources/fight.mp3").play();
                model.StartGame();
            } else if(e.getSource() == viewer.getQuit()){
                model.quitGame();
            }
        }
    }

    public MenuController(MenuModel model, MenuViewer viewer){
        this.viewer = viewer;
        this.model = model;
        MyActionListener action = new MyActionListener();
        viewer.getPVP().addActionListener(action);
        viewer.getPVE().addActionListener(action);
        viewer.getQuit().addActionListener(action);
    }
}
