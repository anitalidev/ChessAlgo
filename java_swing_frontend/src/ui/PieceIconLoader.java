package ui;

import java.util.HashMap;
import java.util.Map;

import javax.swing.ImageIcon;

public class PieceIconLoader {

    private static final Map<String, ImageIcon> cache = new HashMap<>();

    public static ImageIcon getIcon(String code) {
        if (cache.containsKey(code)) {
            return cache.get(code);
        }

        String fileName =
                (Character.isUpperCase(code.charAt(0)) ? "w" : "b")
                + Character.toLowerCase(code.charAt(0))
                + ".png";

        String path = "resources/" + fileName;

        ImageIcon icon = new ImageIcon(path);

        cache.put(code, icon);
        return icon;
    }
}