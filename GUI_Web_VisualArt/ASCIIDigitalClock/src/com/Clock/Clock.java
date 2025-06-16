package com.Clock;
import com.Num2ASCII.Num2ASCII;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

public class Clock {
    public Clock() {

    }
    public void showTime() {
        Date currDate = new Date();
        SimpleDateFormat sdf = new SimpleDateFormat("HH:mm");
        String formattedDate = sdf.format(currDate);
        ArrayList<ArrayList<String>> ASCII = new ArrayList<>();
        for (int i = 0; i < formattedDate.length(); i++) {
            if (formattedDate.charAt(i) == ':') {
                ASCII.add(Num2ASCII.convertChartoASCII(formattedDate.charAt(i)));
            } else {
                ASCII.add(Num2ASCII.convertNumtoASCII(formattedDate.charAt(i) - '0'));
            }
        }
        for(int line = 0; line < 7; ++line) {
            for (ArrayList<String> strings : ASCII) {
                System.out.print(strings.get(line) + " ");
            }
            System.out.println();
        }
    }
}
