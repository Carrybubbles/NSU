package pMenu;

import java.util.ArrayList;

/**
 * Created by artem on 19.03.16.
 */
public class GameModel {
    enum Modes{PVP,PVE;
    };
    private Modes modes;
    public GameModel(){
        modes = modes.PVE;
    }
    public void setMode(Modes mode){
        modes = mode;
    }
}
