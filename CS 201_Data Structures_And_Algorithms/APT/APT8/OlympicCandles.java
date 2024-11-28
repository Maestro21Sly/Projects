import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.PriorityQueue;

public class OlympicCandles {
    public int numberOfNights(int[] candles){
        PriorityQueue<Integer> queueToKeepCandleHeights = new PriorityQueue<>(Collections.reverseOrder());
        for (int candle : candles) {
            queueToKeepCandleHeights.add(candle);
        }
        int nights = 0;
        while (true){
            List<Integer> temp = new ArrayList<>();
            for (int i = 0; i < nights + 1; i++) {
                if (queueToKeepCandleHeights.isEmpty()) {
                    return nights;
                }
                int candle = queueToKeepCandleHeights.poll();
                if (candle > 1) {
                    temp.add(candle - 1);
                }
            }
            queueToKeepCandleHeights.addAll(temp);
            nights++;
        }
    }
}
