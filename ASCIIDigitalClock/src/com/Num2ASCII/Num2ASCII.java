package com.Num2ASCII;

import java.util.ArrayList;

public class Num2ASCII {
    public Num2ASCII() {

    }

    public static ArrayList<String> convertNumtoASCII(int num) {
        ArrayList<String> result = new ArrayList<>();
        switch (num) {
            case 0:
                result.add("##########");
                result.add("#        #");
                result.add("#        #");
                result.add("#        #");
                result.add("#        #");
                result.add("#        #");
                result.add("##########");
                break;
            case 1:
                result.add("     #    ");
                result.add("   # #    ");
                result.add("  #  #    ");
                result.add("     #    ");
                result.add("     #    ");
                result.add("     #    ");
                result.add("##########");
                break;
            case 2:
                result.add("##########");
                result.add("         #");
                result.add("         #");
                result.add("##########");
                result.add("#         ");
                result.add("#         ");
                result.add("##########");
                break;
            case 3:
                result.add("##########");
                result.add("         #");
                result.add("         #");
                result.add("##########");
                result.add("         #");
                result.add("         #");
                result.add("##########");
                break;
            case 4:
                result.add("#        #");
                result.add("#        #");
                result.add("#        #");
                result.add("##########");
                result.add("         #");
                result.add("         #");
                result.add("         #");
                break;
            case 5:
                result.add("##########");
                result.add("#         ");
                result.add("#         ");
                result.add("##########");
                result.add("         #");
                result.add("         #");
                result.add("##########");
                break;
            case 6:
                result.add("##########");
                result.add("#         ");
                result.add("#         ");
                result.add("##########");
                result.add("#        #");
                result.add("#        #");
                result.add("##########");
                break;
            case 7:
                result.add("##########");
                result.add("         #");
                result.add("         #");
                result.add("         #");
                result.add("         #");
                result.add("         #");
                result.add("         #");
                break;
            case 8:
                result.add("##########");
                result.add("#        #");
                result.add("#        #");
                result.add("##########");
                result.add("#        #");
                result.add("#        #");
                result.add("##########");
                break;
            case 9:
                result.add("##########");
                result.add("#        #");
                result.add("#        #");
                result.add("##########");
                result.add("         #");
                result.add("         #");
                result.add("##########");
                break;
        }
        return result;
    }

    public static ArrayList<String> convertChartoASCII(char ch) {
        ArrayList<String> result = new ArrayList<>();
        switch (ch) {
            case ':':
                result.add("          ");
                result.add("    ##    ");
                result.add("    ##    ");
                result.add("          ");
                result.add("    ##    ");
                result.add("    ##    ");
                result.add("          ");
                break;
        }
        return result;
    }
}
