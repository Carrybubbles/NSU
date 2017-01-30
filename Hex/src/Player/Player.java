package Player;

import HexagonalMap.FieldModel;

public interface Player {
    int ONE = 0;
    int TWO = 1;
    boolean haveSteps();
    int getNumberOfCells();
    void makeStep();
    boolean getTurn();
    void setTurn(boolean turn);
    void resScore();
    void refreshField(FieldModel fieldModel);


}
