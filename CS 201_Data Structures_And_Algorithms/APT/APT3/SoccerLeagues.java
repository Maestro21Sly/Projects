//package APT.APT3 ;

public class SoccerLeagues {
    public int []points (String [] matches){
        int [] gamePoints = new int[matches.length];
        for (int t= 0; t<matches.length; t++){
            String matchResults =matches[t];
            
            for (int j=0; j< matchResults.length(); j++){
                char gameResult= matchResults.charAt(j);

                if(gameResult =='W'){
                    gamePoints[t]+= 3;
                }
                else if (gameResult =='D'){
                    gamePoints[t]+=1;
                    gamePoints[j]+=1;
                }

                else if(gameResult =='L'){
                    gamePoints[j] += 3; 
                }  
            }

        }
        return gamePoints;

    }
    
}
