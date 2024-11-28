//package APT QUIZ.APT QUIZ 1;

import java.util.HashMap;
public class AuctionHouse{
    public int revenue(String[] bids, String filter){
        @SuppressWarnings({ "rawtypes", "unchecked" })
        HashMap <String,Integer> mappingItemFromBidWithPrice = new HashMap();
        int totalMoney =0;
        for(String bid: bids){
            String []itemList = bid.split(":");
            String itemBeingConsidered = itemList[0];
            int priceOfitemBeingConsidered = Integer.parseInt(itemList[1]);
            //put in map and update price 
            if (!mappingItemFromBidWithPrice.containsKey(itemBeingConsidered) || priceOfitemBeingConsidered> mappingItemFromBidWithPrice.get(itemBeingConsidered)){
                mappingItemFromBidWithPrice.put(itemBeingConsidered, priceOfitemBeingConsidered);
            }
        }
        String []filterWithNoSpaces = filter.split(" ");
        for(String something: filterWithNoSpaces){
            if(mappingItemFromBidWithPrice.containsKey(something)){
                totalMoney += mappingItemFromBidWithPrice.get(something);
            }

        }


        return totalMoney;
    }

    
    
}
//return total amount of money that items in filter sell for 
// bids is a bis consisting of items being bid on and its price, delimeter for regex : 
//items can have multiple bids, sells for highest price 

//filter consists of items whose price to include  

// Given a filter parameter, find all elements of bid within filter and sum their highest prices 
//match items with prices for duplicates
//map??