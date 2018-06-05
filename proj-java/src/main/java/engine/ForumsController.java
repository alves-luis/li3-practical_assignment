package engine;

import li3.ForumsView;

/**
 * Controller of MVC
 *
 * @author (seu nome)
 * @version 2018-05-23
 */
public class ForumsController {
    private ForumsModel model;
    private ForumsView viewTxt;

    public ForumsController(ForumsModel model) {
      model = model;
      viewTxt = new ForumsView();
    }

    public void setModel(ForumsModel forums) {
      model = forums;
    }

    public void setView(ForumsView txtMenus) {
      viewTxt = txtMenus;
    }

    public void startFlow() {

    }
    /*public void startFlow() {
      long before, after;
      try {
        before = System.currentTimeMillis();
        model.load(args[0]);
      }
    }*/

}
